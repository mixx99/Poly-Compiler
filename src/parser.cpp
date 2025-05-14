#include "../include/parser.hpp"
#include <stdexcept>

namespace PLY{
    Parser::Parser(const std::vector<Token>& tokens) : tokens_(tokens){}

    Token Parser::pullToken(){
      return tokens_[index_++];
    }

    std::optional<NodeExit> Parser::parse(){
      std::optional<NodeExit> exit_node;
      while(peek().has_value()){
        if(peek().value().type == TokenType::_exit){
          pullToken();
          if(auto node_expr = parse_expr()){
            NodeExit tempNodeExit;
            tempNodeExit.expr = node_expr.value();
            exit_node = tempNodeExit;
          }
          else
            throw std::runtime_error("Invalid expression");
          if(peek().has_value() && peek().value().type == TokenType::semi)
            pullToken();
          else
            throw std::runtime_error("Missing semicolomn");
        }
      }
      index_ = 0;
      return exit_node;
    }

    std::optional<Token> Parser::peek(int ahead){
      if(index_ + ahead > tokens_.size())
        return {};
      return tokens_[index_];
    }
    std::optional<NodeExpr> Parser::parse_expr(){
      if(peek().has_value() && peek().value().type == TokenType::int_lit){
        NodeExpr nodeexpr;
        nodeexpr.int_lit = pullToken();
        return nodeexpr;
      }
      return {};
    }
}