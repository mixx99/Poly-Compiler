#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>
#include <string>
#include <stdexcept>

#define FAIL_EXIT {std::cerr << "Invalid syntax!"; throw std::runtime_error("Invalid syntax");}

enum class TokenType{
  _return,
  int_lit,
  semi
};

struct Token{
  TokenType type;
  std::optional<std::string> value;
};

std::string token_to_asm(std::vector<Token> tokens){
  std::stringstream output;
  output << "global start\n_start:\n";
for(int i = 0; i < tokens.size(); ++i){
  Token token = tokens[i];
  if(token.type == TokenType::_return){
    if(i + 2 > tokens.size() || i + 1 > tokens.size())
      FAIL_EXIT;
    if(tokens[i+1].type != TokenType::int_lit)
      FAIL_EXIT;
    if(tokens[i+2].type != TokenType::semi)
      FAIL_EXIT;
    output << "    mov rax, 60\n";
    output << "    mov rdi, " << tokens[i+1].value.value() << '\n';
    output << "syscall";
    }
  }
  return output.str();
}


std::vector<Token> tokenize(const std::string& str){
  std::vector<Token> result;
  std::string buffer;
  for(int i = 0;i < str.length(); i++){
    buffer.clear();

    if(std::isalpha(str[i])){
      while(std::isalnum(str[i])){
        buffer.push_back(str[i]);
        i++;
      }
      i--;
      if(buffer == "return"){
        result.push_back(Token());
        result.back().type = TokenType::_return;
      } else std::cout << "FUCKED UP\n";
      buffer.clear();
    }
    if(std::isdigit(str[i])){
      while(std::isdigit(str[i])){
        buffer.push_back(str[i]);
        i++;
      }
      i--;
      result.push_back(Token());
      result.back().type = TokenType::int_lit;
      result.back().value = buffer;
      buffer.clear();
    }
    if(str[i] == ';'){
      result.push_back(Token());
      result.back().type = TokenType::semi;
    }
  }
  return result;
}


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

  std::vector<Token> tokens = tokenize(content);

  std::fstream output_file("out.asm", std::ios::out);
  output_file << token_to_asm(tokens);
  output_file.close();

  system("nasm -felf64 out.asm");
  system("ld -o out out.o");

  return EXIT_SUCCESS;
}