#include "../include/cpu.hpp"
#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>

void CPU::print_pc() const {
  std::cout << std::left << std::setw(14) << "pc" << ": 0x" << std::hex
            << std::setw(8) << std::setfill('0') << std::right << pc << "\n";
}

inline constexpr std::array<const char *, 32> regs_aliases = {
    "zero", "ra", "sp", "gp", "tp",  "t0",  "t1", "t2", "s0", "s1", "a0",
    "a1",   "a2", "a3", "a4", "a5",  "a6",  "a7", "s2", "s3", "s4", "s5",
    "s6",   "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};

void CPU::print_regs() const {
  std::cout << "Registers:\n";
  for (int i = 0; i < 32; ++i) {
    std::ostringstream line;

    line << "REG " << std::left << std::setw(5) << regs_aliases[i];

    if (i < 10) {
      line << "(x0" << std::dec << static_cast<unsigned>(i) << ")";
    } else {
      line << "(x" << std::dec << static_cast<unsigned>(i) << ")";
    }

    line << ": 0x";

    uint32_t reg_val = regs[i];
    line << std::setfill('0') << std::setw(8) << std::right << std::hex << reg_val;

    std::cout << line.str() << "\n";
  }
}

void CPU::print_mem(uint32_t start, uint32_t end) const {
    std::cout << "Memory [0x" << std::hex << start << " - 0x" << end << "]:\n";

    for (uint32_t addr = start; addr <= end; addr += 16) {
      std::cout << "0x" << std::setfill('0') << std::setw(8) << std::right << std::hex << addr << ": ";

      for (uint32_t i = 0; i < 4; ++i) {
        std::cout << std::setfill('0') << std::setw(8) << std::right << std::hex << memory.load_word(addr + (i << 2)) << " ";
      }

      std::cout << "\n";
    }
}
