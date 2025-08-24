#include "../include/instructions.hpp"
#include "../include/instruction_defs.hpp"
#include <iomanip>
#include <ios>
#include <sstream>
#include <stdexcept>

inline std::string to_hex(uint32_t value) {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(8) << std::right << std::hex << value;
    return oss.str();
}

inline bool boundary_check(int32_t addr, int32_t offset) {
  return (addr + offset) >= 0 && (addr + offset) <= static_cast<int32_t>(Memory::MEM_SIZE - 1);
}

void execute_r_type(uint32_t inst, uint32_t regs[32]) {
  const uint8_t rd = get_rd(inst);
  const uint8_t rs1 = get_rs1(inst);
  const uint8_t rs2 = get_rs2(inst);
  const uint8_t funct3 = get_funct3(inst);
  const uint8_t funct7 = get_funct7(inst);

  if (funct3 == 0x0) {
    if (funct7 == 0x00) { // add rd, rs1, rs2
      regs[rd] = regs[rs1] + regs[rs2];
    } else if (funct7 == 0x20) { // sub rd, rs1, rs2
      regs[rd] = regs[rs1] - regs[rs2];
    }
  } else if (funct3 == 0x4) { // xor rd, rs1, rs2
    regs[rd] = regs[rs1] ^ regs[rs2];
  } else if (funct3 == 0x6) { // or rd, rs1, rs2
    regs[rd] = regs[rs1] | regs[rs2];
  } else if (funct3 == 0x7) { // and rd, rs1, rs2
    regs[rd] = regs[rs1] & regs[rs2];
  } else if (funct3 == 0x1) { // sll rd, rs1, rs2
    regs[rd] = regs[rs1] << regs[rs2];
  } else if (funct3 == 0x5) {
    if (funct7 == 0x00) { // srl rd, rs1, rs2
      regs[rd] = regs[rs1] >> regs[rs2];
    } else if (funct7 == 0x20) { // sra rd, rs1, rs2
      regs[rd] = (regs[rs1] & 0x80000000) ?
       (regs[rs1] >> regs[rs2]) | (0xFFFFFFFF << (32 - regs[rs2])) 
       : regs[rs1] >> regs[rs2];
    }
  } else if (funct3 == 0x2) { // slt rd, rs1, rs2
    regs[rd] = (static_cast<int32_t>(regs[rs1]) < static_cast<int32_t>(regs[rs2])) ? 1 : 0;
  } else if (funct3 == 0x3) { // sltu rd, rs1, rs2
    regs[rd] = (regs[rs1] < regs[rs2]) ? 1 : 0;
  }
}

void execute_i_type(uint32_t inst, uint32_t regs[32]) {
  const uint8_t rd = get_rd(inst);
  const uint8_t rs1 = get_rs1(inst);
  const uint8_t funct3 = get_funct3(inst);
  const int32_t imm = get_imm_i(inst);

  const uint8_t shamt = imm & 0x1F; // imm[4:0]
  const uint8_t funct7 = (imm >> 5) & 0x7F; // imm[11:5]

  if (funct3 == 0x0) { // addi rd, rs1, imm
    regs[rd] = regs[rs1] + imm;
  } else if (funct3 == 0x4) { // xori rd, rs1, imm
    regs[rd] = regs[rs1] ^ imm;
  } else if (funct3 == 0x6) { // ori rd, rs1, imm
    regs[rd] = regs[rs1] | imm;
  } else if (funct3 == 0x7) { // andi rd, rs1, imm
    regs[rd] = regs[rs1] & imm;
  } else if (funct3 == 0x1 && funct7 == 0x00) { // slli rd, rs1, imm
    regs[rd] = regs[rs1] << shamt;
  } else if (funct3 == 0x5) {
    if (funct7 == 0x00) { // srli rd, rs1, imm
      regs[rd] = regs[rs1] >> shamt;
    } else if (funct7 == 0x20) { // srai rd, rs1, imm
      regs[rd] = static_cast<uint32_t>(static_cast<int32_t>(regs[rs1]) >> shamt);
    }
  } else if (funct3 == 0x2) { // slti rd, rs1, imm
    regs[rd] = (static_cast<int32_t>(regs[rs1]) < imm)? 1 : 0;
  } else if (funct3 == 0x3) { // sltiu rd, rs1, imm
    regs[rd] = (regs[rs1] < static_cast<uint32_t>(imm))? 1 : 0;
  }
}

void execute_i_type_load(uint32_t inst, uint32_t regs[32], Memory& mem) {
  const uint8_t rd = get_rd(inst);
  const uint8_t rs1 = get_rs1(inst);
  const uint8_t funct3 = get_funct3(inst);
  const int32_t imm = get_imm_i(inst);

  const uint32_t addr = regs[rs1] + imm;
  if (!boundary_check(regs[rs1], imm)) throw std::runtime_error("Load access fault at address 0x" + to_hex(addr));

  if (funct3 == 0x0) { // lb rd, imm(rs1)
    regs[rd] = static_cast<int8_t>(mem.load_byte(addr)); 
  } else if (funct3 == 0x1) { // lh rd, imm(rs1)
    if (addr % 2 != 0) throw std::runtime_error("Misaligned load (lh) at address 0x" + to_hex(addr)); 
    regs[rd] = static_cast<int16_t>(mem.load_half(addr));
  } else if (funct3 == 0x2) { // lw rd, imm(rs1)
    if (addr % 4 != 0) throw std::runtime_error("Misaligned load (lw) at address 0x" + to_hex(addr)); 
    regs[rd] = mem.load_word(addr);
  } else if (funct3 == 0x4) { // lbu rd, imm(rs1)
    regs[rd] = mem.load_byte(addr);
  } else if (funct3 == 0x5) { // lhu rd, imm(rs1)
    if (addr % 2 != 0) throw std::runtime_error("Misaligned load (lhu) at address 0x" + to_hex(addr)); 
    regs[rd] = mem.load_half(addr);
  }
}

void execute_s_type(uint32_t inst, uint32_t regs[32], Memory& mem) {
  const uint8_t funct3 = get_funct3(inst);
  const uint8_t rs1 = get_rs1(inst);
  const uint8_t rs2 = get_rs2(inst);

  const int32_t imm = get_imm_s(inst);

  const uint32_t addr = regs[rs1] + imm;
  if (!boundary_check(regs[rs1], imm)) throw std::runtime_error("Store access fault at address 0x" + to_hex(addr));

  if (funct3 == 0x0) { // sb rs2, imm(rs1)
    mem.store_byte(addr, static_cast<uint8_t>(regs[rs2]));
  } else if (funct3 == 0x1) { // sh rs2, imm(rs1)
    if (addr % 2 != 0) throw std::runtime_error("Misaligned store (sh) at address 0x" + to_hex(addr)); 
    mem.store_half(addr, static_cast<uint16_t>(regs[rs2]));
  } else if (funct3 == 0x2) { // sw rs2, imm(rs1)
    if (addr % 4 != 0) throw std::runtime_error("Misaligned store (sw) at address 0x" + to_hex(addr)); 
    mem.store_word(addr, regs[rs2]);
  }
}

void execute_b_type(uint32_t inst, uint32_t *regs, uint32_t &pc) {
  const uint8_t funct3 = get_funct3(inst);
  const uint8_t rs1 = get_rs1(inst);
  const uint8_t rs2 = get_rs2(inst);

  const int32_t imm = get_imm_b(inst);

  if (funct3 == 0x0) { // beq rs1, rs2, imm
    if (static_cast<int32_t>(regs[rs1]) == static_cast<int32_t>(regs[rs2])) pc += imm;
  } else if (funct3 == 0x1) { // bne rs1, rs2, imm
    if (static_cast<int32_t>(regs[rs1]) != static_cast<int32_t>(regs[rs2])) pc += imm;
  } else if (funct3 == 0x4) { // blt rs1, rs2, imm
    if (static_cast<int32_t>(regs[rs1]) < static_cast<int32_t>(regs[rs2])) pc += imm;
  } else if (funct3 == 0x5) { // bge rs1, rs2, imm
    if (static_cast<int32_t>(regs[rs1]) >= static_cast<int32_t>(regs[rs2])) pc += imm;
  } else if (funct3 == 0x6) { // bltu rs1, rs2, imm
    if (regs[rs1] < regs[rs2]) pc += imm;
  } else if (funct3 == 0x7) { // bgeu rs1, rs2, imm
    if (regs[rs1] >= regs[rs2]) pc += imm;
  }
}