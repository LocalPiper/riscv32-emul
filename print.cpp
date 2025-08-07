#include "cpu.hpp"
#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>

void CPU::print_pc() const {
  std::cout << std::left << std::setw(10) << "pc" << ": 0x" << std::hex
            << std::setw(8) << std::setfill('0') << pc << "\n";
}

inline constexpr std::array<const char *, 32> regs_aliases = {
    "zero", "ra", "sp", "gp", "tp",  "t0",  "t1", "t2", "s0", "s1", "a0",
    "a1",   "a2", "a3", "a4", "a5",  "a6",  "a7", "s2", "s3", "s4", "s5",
    "s6",   "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};

void CPU::print_regs() const {
  std::cout << "Registers:\n";
  for (int i = 0; i < 32; ++i) {
    std::ostringstream line;

    line << std::left << std::setw(5) << regs_aliases[i];

    if (i < 16) {
      line << "(x0" << std::hex << static_cast<unsigned>(i) << ")";
    } else {
      line << "(x" << std::hex << static_cast<unsigned>(i) << ")";
    }

    line << ": 0x" << std::setw(8) << std::setfill('0')
         << static_cast<uint32_t>(regs[i]);

    std::cout << line.str() << "\n";
  }
}

void CPU::print_mem(uint32_t start, uint32_t end) const {
  std::cout << "Memory [0x" << std::hex << start << " - 0x" << std::hex << end
            << "]:\n";
  for (uint32_t addr = start; addr < end; addr += 16) {
    std::cout << "0x" << std::setw(8) << std::setfill('0') << addr << ": ";

    for (int i = 0; i < 16; ++i) {
      if (addr + i < end) {
        std::cout << std::setw(2) << std::setfill('0')
                  << static_cast<int>(memory.read8(addr + i)) << " ";
      } else {
        std::cout << "   ";
      }
    }

    std::cout << "\n";
  }
}
