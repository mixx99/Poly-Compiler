#pragma once

#include <string>
#include <iostream>
#include <optional>
#include <vector>

namespace PLY
{

enum class TokenType{
  _exit,
  int_lit,
  semi
};

struct Token{
  TokenType type;
  std::optional<std::string> value;
};

class Tokenizer{
  std::string str_;
  size_t index_ = 0;
public:
  std::vector<Token> tokens;

public: // ctors
  Tokenizer(const std::string& other) : str_(other){}
  Tokenizer(const std::string&& other) : str_(other){}
public:
  std::vector<Token> tokenize();
private:
  std::optional<char> peek(int ahead = 1) const;
  char pullchar();

};
} // namespace PLY