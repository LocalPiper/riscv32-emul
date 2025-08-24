#pragma once
#include "memory.hpp"
#include "memory.hpp"
#include <cstdint>

void execute_r_type(uint32_t inst, uint32_t regs[32]);
void execute_i_type(uint32_t inst, uint32_t regs[32]);
void execute_i_type_load(uint32_t inst, uint32_t regs[32], Memory& mem);
void execute_s_type(uint32_t inst, uint32_t regs[32], Memory& mem);
void execute_b_type(uint32_t inst, uint32_t regs[32], uint32_t& pc);
void execute_j_type(uint32_t inst, uint32_t regs[32], uint32_t& pc);
