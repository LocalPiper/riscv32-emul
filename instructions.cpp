#include "instructions.hpp"
#include "instruction_defs.hpp"
#include <cstdint>

void execute_r_type(uint32_t inst, uint32_t regs[32]) {
  const uint8_t rd = get_rd(inst);
  const uint8_t rs1 = get_rs1(inst);
  const uint8_t rs2 = get_rs2(inst);
  const uint8_t funct3 = get_funct3(inst);
  const uint8_t funct7 = get_funct7(inst);

  if (funct3 == 0x0) {
    if (funct7 == 0x00) // add rd, rs1, rs2
      regs[rd] = regs[rs1] + regs[rs2];
    else if (funct7 == 0x20) // sub rd, rs1, rs2
      regs[rd] = regs[rs1] - regs[rs2];
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
