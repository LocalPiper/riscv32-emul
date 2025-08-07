#pragma once

#include "memory.hpp"
class CPU {
public:
  CPU(Memory &mem);
  void run();

  // debug methods
  void print_pc() const;
  void print_regs() const;
  void print_mem(uint32_t start, uint32_t end) const;

private:
  uint32_t regs[32]{};
  uint32_t pc = 0;
  Memory &memory;

  void execute(uint32_t inst);
};
