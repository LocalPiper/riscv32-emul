#include "../include/instructions.hpp"
#include "../include/instruction_defs.hpp"

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

  if (funct3 == 0x0) { // lb rd, imm(rs1)
    regs[rd] = static_cast<int8_t>(mem.load_byte(regs[rs1] + imm)); 
  } else if (funct3 == 0x1) { // lh rd, imm(rs1)
    regs[rd] = static_cast<int16_t>(mem.load_half(regs[rs1] + imm));
  } else if (funct3 == 0x2) { // lw rd, imm(rs1)
    regs[rd] = mem.load_word(regs[rs1] + imm);
  } else if (funct3 == 0x4) { // lbu rd, imm(rs1)
    regs[rd] = mem.load_byte(regs[rs1] + imm);
  } else if (funct3 == 0x5) { // lhu rd, imm(rs1)
    regs[rd] = mem.load_half(regs[rs1] + imm);
  }
}