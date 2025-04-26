#include "function.hpp"
#include "environment.hpp"
#include <iostream>
#include <memory>
using namespace std;

std::shared_ptr<CrusaderCallable> CrusaderFunction::clone() const {
  return std::make_shared<CrusaderFunction>(*this);
}

string CrusaderFunction::getType() const { return "function"; }

Value CrusaderFunction::call(const vector<Value> &args) {
  if (args.size() != params.size()) {
    cerr << "Error: Function expected " << params.size() << " arguments, got "
         << args.size() << ".\n";
    return 0;
  }

  for (const auto &captured : capturedScopes) {
    scopes.push_back(captured);
  }

  enterScope();

  for (int i = 0; i < params.size(); ++i) {
    createVar(params[i], args[i]);
  }
  try {
    body->evaluate();
  } catch (ReturnException &ret) {
    exitScope();
    for (int i = 0; i < capturedScopes.size(); ++i) {
      scopes.pop_back();
    }
    return ret.value;
  }

  exitScope();
  for (int i = 0; i < capturedScopes.size(); ++i) {
    scopes.pop_back();
  }

  return 0;
}
