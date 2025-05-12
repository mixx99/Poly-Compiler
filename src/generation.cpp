#include "../include/generation.hpp"
#include <sstream>

namespace PLY{
  std::string Generator::generate(){
    std::stringstream output;
    output << "global _start\n_start:\n";
    output << "    mov rax, 60\n";
    output << "    mov rdi, " << root_.expr.int_lit.value.value() << "\n";
    output << "    syscall";
    return output.str();
  }
}