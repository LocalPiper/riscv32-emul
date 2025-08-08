#pragma once

#include <cmath>
#include <cstdint>

namespace opcodes {

constexpr uint8_t OPCODE_R = 0x33;        // R-type
constexpr uint8_t OPCODE_I = 0x13;        // I-type
constexpr uint8_t OPCODE_J = 0x6F;        // J-type
constexpr uint8_t OPCODE_B = 0x63;        // B-type
constexpr uint8_t OPCODE_I_LOAD = 0x03;   // I-type
constexpr uint8_t OPCODE_S = 0x23;        // S-type
constexpr uint8_t OPCODE_I_SYSTEM = 0x73; // ecall, ebreak

} // namespace opcodes

inline constexpr uint8_t get_opcode(uint32_t inst) { return inst & 0x7f; }
inline constexpr uint8_t get_rd(uint32_t inst) { return (inst >> 7) & 0x1f; }
inline constexpr uint8_t get_funct3(uint32_t inst) {
  return (inst >> 12) & 0x7;
}
inline constexpr uint8_t get_rs1(uint32_t inst) { return (inst >> 15) & 0x1f; }
inline constexpr uint8_t get_rs2(uint32_t inst) { return (inst >> 20) & 0x1f; }

// R-type
inline constexpr uint8_t get_funct7(uint32_t inst) {
  return (inst >> 25) & 0x7f;
}

// I-type
inline constexpr int32_t get_imm_i(uint32_t inst) {
  return static_cast<int32_t>(inst) >> 20;
}
