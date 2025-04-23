#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "ast.hpp"
#include <unordered_map>
#include <vector>
using namespace std;

class CrusaderFunction {
  string functionName;
  vector<string> params;
  BlockNode *body;

public:
  CrusaderFunction() : functionName(""), params(), body(nullptr) {}
  CrusaderFunction(string name, vector<string> params, BlockNode *body)
      : functionName(name), params(params), body(body) {}
  Value call(const vector<Value> &args) const;
};

extern unordered_map<string, CrusaderFunction> functionTable;
#endif // FUNCTION_HPP
