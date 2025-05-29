#ifndef CFG_HPP
#define CFG_HPP

#include "ir_struct.hpp"
#include <string>
#include <vector>
struct BasicBlock {
  std::string name;
  IR instructions;
  std::vector<BasicBlock *> pred;
  std::vector<BasicBlock *> succ;
};

std::vector<BasicBlock *> buildCFG(const IR &code);

IR flattenCFG(const std::vector<BasicBlock *> &cfg);

#endif // !CFG_HPP
