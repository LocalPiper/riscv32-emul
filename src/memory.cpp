#include "memory.hpp"
#include <cstdint>
#include <fstream>
#include <stdexcept>

void Memory::load_binary(const std::string &filename) {
  std::ifstream file(filename, std::ios::binary);
  if (!file)
    throw std::runtime_error("Failed to open binary file");

  file.read(reinterpret_cast<char *>(mem.data()), mem.size());
}

uint32_t Memory::load_word(uint32_t addr) const {
  return mem[addr] | (mem[addr + 1] << 8) | (mem[addr + 2] << 16) |
         (mem[addr + 3] << 24);
}

void Memory::store_word(uint32_t addr, uint32_t value) {
  mem[addr] = value & 0xFF;
  mem[addr + 1] = (value >> 8) & 0xFF;
  mem[addr + 2] = (value >> 16) & 0xFF;
  mem[addr + 3] = (value >> 24) & 0xFF;
}
