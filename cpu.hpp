#pragma once

#include "memory.hpp"
class CPU {
public:
  CPU(Memory &mem);
  void run();

private:
  uint32_t regs[32]{};
  uint32_t pc = 0;
  Memory &memory;

  void execute(uint32_t inst);
};
