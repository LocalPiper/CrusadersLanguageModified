#include "environment.hpp"
#include <iostream>
#include <memory>
using namespace std;

vector<unordered_map<string, shared_ptr<Value>>> scopes = {{}};

void enterScope() { scopes.push_back({}); }

void exitScope() {
  if (!scopes.empty())
    scopes.pop_back();
}

Value getVar(const string &name) {
  for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
    if (it->count(name))
      return *((*it)[name]);
  }
  cerr << "Error: Undefined variable " << name << endl;
  return 0;
}

void createVar(const string &name, Value value) {
  scopes.back()[name] = make_shared<Value>(value);
}

void setVar(const string &name, Value value) {
  for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
    if (it->count(name)) {
      *((*it)[name]) = value;
      return;
    }
  }
  cerr << "Error: Undefined variable " << name << endl;
}
