#include "../include/cpu.hpp"
#include "../include/instruction_defs.hpp"
#include "../include/instructions.hpp"
#include "../include/utils.hpp"
#include <iostream>
#include <stdexcept>

CPU::CPU(Memory &mem) : memory(mem) {}

void CPU::run() {
  while (true) {
    if (!boundary_check(pc)) throw std::runtime_error("Instruction access fault at address 0x" + to_hex(pc));
    uint32_t inst = memory.load_word(pc);
    execute(inst);
  }
}

void CPU::execute(uint32_t inst) {
  const uint8_t opcode = get_opcode(inst);
  const uint32_t prev_pc = pc;
  using namespace opcodes;
  switch (opcode) {
  case OPCODE_R:
    execute_r_type(inst, regs);
    break;
  case OPCODE_I:
    execute_i_type(inst, regs);
    break;
  case OPCODE_I_LOAD:
    execute_i_type_load(inst, regs, memory);
    break;
  case OPCODE_S:
    execute_s_type(inst, regs, memory);
    break;
  case OPCODE_B:
    execute_b_type(inst, regs, pc);
    break;
  case OPCODE_J:
    print_pc();
    print_regs();
    print_mem(0x0000, 0x0100);
    std::exit(0); // for now
  default:
    std::cerr << "Unknown opcode: " << std::hex << +opcode << "\n";
    std::exit(1);
  }

  regs[0] = 0; // x0 is always zero
  if (prev_pc == pc) {
    pc += 4;     // instructions are always uint32_t words, and memory consists of
  }              // uint8_t words
}
