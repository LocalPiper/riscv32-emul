
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

std::vector<uint8_t> RAM(65536);

uint32_t regs[32] = {0};

uint32_t pc = 0x0000;

void load_binary(const std::string &filename) {
  std::ifstream f(filename, std::ios::binary);
  f.read(reinterpret_cast<char *>(&RAM[0]), RAM.size());
}

uint32_t fetch(uint32_t pc) {
  return RAM[pc] | (RAM[pc + 1] << 8) | (RAM[pc + 2] << 16) |
         (RAM[pc + 3] << 24);
}

void execute(uint32_t inst) {
  uint32_t opcode = inst & 0x7f;

  if (opcode == 0x13) { // ADDI
    uint32_t rd = (inst >> 7) & 0x1f;
    uint32_t funct3 = (inst >> 12) & 0x7;
    uint32_t rs1 = (inst >> 15) & 0x1f;
    int32_t imm = (int32_t)(inst) >> 20;

    if (funct3 == 0x0) { // ADDI
      regs[rd] = regs[rs1] + imm;
    }
  } else if (opcode == 0x33) { // ADD
    uint32_t rd = (inst >> 7) & 0x1f;
    uint32_t funct3 = (inst >> 12) & 0x7;
    uint32_t rs1 = (inst >> 15) & 0x1f;
    uint32_t rs2 = (inst >> 20) & 0x1f;
    uint32_t funct7 = (inst >> 25);

    if (funct3 == 0x0 && funct7 == 0x00) { // ADD
      regs[rd] = regs[rs1] + regs[rs2];
    }
  } else if (opcode == 0x6f) { // JAL
    std::cout << "Register a2: " << regs[12] << "\n";
    exit(0);
  }
}

int main() {
  load_binary("program.bin");

  while (true) {
    uint32_t inst = fetch(pc);
    execute(inst);
    pc += 4;
    regs[0] = 0;
  }
}
