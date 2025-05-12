#include "../include/tokenizer.hpp"

namespace PLY
{
    std::vector<Token> Tokenizer::tokenize(){
    std::string buffer;
    while(peek().has_value()){
      if(std::isalpha(peek().value())){
        buffer.push_back(pullchar());
        while(peek().has_value() && std::isalnum(peek().value())){
          buffer.push_back(pullchar());
        }
        if(buffer == "exit"){
            tokens.push_back(Token());
            tokens.back().type = TokenType::_exit;
            buffer.clear();
          }
      }
      else if(std::isspace(peek().value()))
        pullchar();
      else if(std::isdigit(peek().value())){
        buffer.push_back(pullchar());
        while(peek().has_value() && std::isdigit(peek().value()))
          buffer.push_back(pullchar());
        tokens.push_back(Token());
        tokens.back().type = TokenType::int_lit;
        tokens.back().value = buffer;
        buffer.clear();
      }
      else if(peek().value() == ';'){
        pullchar();
        tokens.push_back(Token());
        tokens.back().type = TokenType::semi;
        continue;
      }
      else{
        exit(5);
      }
  }
}
  std::optional<char> Tokenizer::peek(int ahead) const{
    if(index_+ ahead > str_.length())
      return {};
    return str_[index_];
  }
  char Tokenizer::pullchar(){
    return str_[index_++];
  }

}