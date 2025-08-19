#include "../include/instructions.hpp"
#include "../include/instruction_defs.hpp"
#include <cstdint>

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
      // TODO: this one is tricky, will implement later
    }
  } else if (funct3 == 0x2) { // slt rd, rs1, rs2
    regs[rd] = (regs[rs1] < regs[rs2]) ? 1 : 0;
  } else if (funct3 == 0x3) { // sltu rd, rs1, rs2
    // TODO: not sure that unsigned slt is the same
  }
}

void execute_i_type(uint32_t inst, uint32_t regs[32]) {
  const uint8_t rd = get_rd(inst);
  const uint8_t rs1 = get_rs1(inst);
  const uint8_t funct3 = get_funct3(inst);
  const int32_t imm = get_imm_i(inst);

  if (funct3 == 0x0) // addi rd, rs1, imm
    regs[rd] = regs[rs1] + imm;
}
