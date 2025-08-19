#pragma once

#include <string>
#include <vector>
#include <cstdint>

class Memory {
public:
  static constexpr size_t MEM_SIZE = 64 * 1024;
  void load_binary(const std::string &filename);
  void load_stdin();
  uint32_t load_word(uint32_t addr) const;
  void store_word(uint32_t addr, uint32_t value);

  // debug methods
  uint8_t read8(uint32_t addr) { return mem[addr]; }

private:
  std::vector<uint8_t> mem = std::vector<uint8_t>(MEM_SIZE, 0);
};
