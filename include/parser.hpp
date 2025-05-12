#pragma once
#include "tokenizer.hpp"
#include <vector>
#include <optional>

namespace PLY{

struct NodeExpr {
    Token int_lit;
};

struct NodeExit {
    NodeExpr expr;
};


  class Parser{
    const std::vector<Token> tokens_;
    int index_ = 0;
  public:
    Parser(const std::vector<Token>& tokens);
    Token pullToken();
    std::optional<NodeExit> parse();
    std::optional<Token> peek(int ahead = 1);
    std::optional<NodeExpr> parse_expr();


  };
}