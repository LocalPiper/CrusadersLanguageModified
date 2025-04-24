#include "function.hpp"
#include "environment.hpp"
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
using namespace std;

unordered_map<string, shared_ptr<CrusaderCallable>> functionTable;

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
  try {
    body->evaluate();
  } catch (ReturnException &ret) {
    exitScope();
    return ret.value;
  }

  exitScope();
  return 0;
}
