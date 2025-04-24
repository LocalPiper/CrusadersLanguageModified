#include "function.hpp"
#include "environment.hpp"
#include <iostream>
#include <vector>
using namespace std;

Value CrusaderFunction::call(const vector<Value> &args) {
  if (args.size() != params.size()) {
    cerr << "Error: Function expected " << params.size() << " arguments, got "
         << args.size() << ".\n";
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
