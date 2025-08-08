#include "cpu.hpp"
#include "memory.hpp"

int main() {
  Memory mem;
  CPU cpu(mem);

  mem.load_binary("program.bin");
  cpu.run();

  return 0;
}
