#include "function.hpp"
#include "environment.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

unordered_map<string, CrusaderFunction> functionTable;

Value CrusaderFunction::call(const vector<Value> &args) const {
  if (args.size() != params.size()) {
    cerr << "Error: Function '" << functionName << "' expected "
         << params.size() << " arguments, got " << args.size() << ".\n";
    return 0;
  }

  enterScope();

  for (int i = 0; i < params.size(); ++i) {
    createVar(params[i], args[i]);
  }

  body->evaluate();

  exitScope();

  return 0;
}
