#pragma once
#include "parser.hpp"
#include <string>

namespace PLY{
class Generator{
  const NodeExit root_;
public:
  Generator(NodeExit root) :root_(root) {}
  std::string generate();
};
}