#include "../include/cpu.hpp"
#include "../include/memory.hpp"

int main(int argc, char** argv) {
  Memory mem;
  CPU cpu(mem);

  if (argc > 1 && std::string(argv[1]) == "--test") {
    mem.load_stdin();
  } else {
    mem.load_binary("program.bin");
  }

  cpu.run();

  return 0;
}
