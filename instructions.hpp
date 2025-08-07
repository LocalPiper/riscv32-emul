#pragma once
#include <cstdint>

void execute_r_type(uint32_t inst, uint32_t regs[32]);
void execute_i_type(uint32_t inst, uint32_t regs[32]);
