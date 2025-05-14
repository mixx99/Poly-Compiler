#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>
#include <string>
#include <stdexcept>

#include "../include/generation.hpp"

using namespace PLY;


int main(const int argc, const char** argv){
  if(argc == 1){
    std::cerr << "Empty input file. Use poly <input.pl>" << std::endl;
    return EXIT_FAILURE;
  }

  std::fstream file(argv[1], std::ios::in);
  std::stringstream contents_stream;
  contents_stream << file.rdbuf();
  std::string content = contents_stream.str();
  file.close();

  Tokenizer tokenizer(content);

  std::vector<Token> tokens = tokenizer.tokenize();
  Parser parser(tokens);
  std::optional<NodeExit> tree = parser.parse();

  if(!tree.has_value())
    throw std::runtime_error("No exit statement found");

  Generator generator(tree.value());
  {
    std::fstream file("out.asm", std::ios::out);
    file << generator.generate();
  }
  system("nasm -felf64 out.asm");
  system("ld -o out out.o");

  return EXIT_SUCCESS;
}