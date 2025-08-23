#include "../include/cpu.hpp"
#include "../include/memory.hpp"
#include <iostream>
#include <stdexcept>

int main(int argc, char** argv) {
  Memory mem;
  CPU cpu(mem);

  if (argc > 1 && std::string(argv[1]) == "--test") {
    mem.load_stdin();
  } else {
    mem.load_binary("program.bin");
  }

  try {
    cpu.run();
  } catch (std::runtime_error& err) {
    std::cerr << err.what() << "\n";
    return 1;
  }

  return 0;
}
