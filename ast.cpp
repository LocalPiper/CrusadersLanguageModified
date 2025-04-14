#include "ast.hpp"
#include <iostream>
#include <unordered_map>
#include <variant>
#include <vector>

using namespace std;

using Value = variant<int, string>;

vector<unordered_map<string, Value>> scopes = {{}};

void enterScope() { scopes.push_back({}); }

void exitScope() {
  if (scopes.size() > 1) {
    scopes.pop_back();
  }
}

Value getVar(const string &name) {
  for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
    if (it->count(name))
      return (*it)[name];
  }
  cerr << "Error: Undefined variable " << name << endl;
  return 0;
}

void createVar(const string &name, Value value) { scopes.back()[name] = value; }

void setVar(const string &name, Value value) {
  for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
    if (it->count(name)) {
      (*it)[name] = value;
      return;
    }
  }
  cerr << "Error: Undefined variable " << name << endl;
}

bool isTruthy(const Value &val) {
  if (holds_alternative<int>(val))
    return get<int>(val) != 0;
  if (holds_alternative<string>(val))
    return !get<string>(val).empty();
  return false;
}

Value VariableNode::evaluate() const { return getVar(name); }

Value BinaryOpNode::evaluate() const {
  Value leftVal = left->evaluate();
  Value rightVal = right->evaluate();

  if (holds_alternative<int>(leftVal) && holds_alternative<int>(rightVal)) {
    int l = get<int>(leftVal);
    int r = get<int>(rightVal);

    if (op == "+")
      return l + r;
    if (op == "-")
      return l - r;
    if (op == "*")
      return l * r;
    if (op == "/")
      return r != 0 ? l / r : 0;
    if (op == ">")
      return l > r;
    if (op == "<")
      return l < r;
    if (op == ">=")
      return l >= r;
    if (op == "<=")
      return l <= r;
    if (op == "==")
      return l == r;
    if (op == "!=")
      return l != r;
    if (op == "||")
      return l || r;
    if (op == "&&")
      return l && r;
  }

  if ((op == "+" || op == "==" || op == "!=") &&
      (holds_alternative<string>(leftVal) ||
       holds_alternative<string>(rightVal))) {
    string l = holds_alternative<int>(leftVal) ? to_string(get<int>(leftVal))
                                               : get<string>(leftVal);
    string r = holds_alternative<int>(rightVal) ? to_string(get<int>(rightVal))
                                                : get<string>(rightVal);
    if (op == "+") {
      return l + r;
    } else if (op == "==") {
      return l == r;
    } else if (op == "!=") {
      return l != r;
    }
  }

  cerr << "Error: Invalid operation for the given types." << endl;
  return 0;
}

Value UnaryOpNode::evaluate() const {
  Value result = right->evaluate();

  if (op == "-") {
    if (holds_alternative<int>(result))
      return -get<int>(result);
    cerr << "Error: Unary '-' can only be applied to integers." << endl;
  } else if (op == "!") {
    return !isTruthy(result);
  }
  cerr << "Error: Unknown or invalid unary operator " << op << endl;
  return 0;
}

Value PrintNode::evaluate() const {
  Value result = expression->evaluate();
  if (holds_alternative<int>(result)) {
    cout << "Milord proclaimeth: " << get<int>(result) << "!\n";
  } else if (holds_alternative<string>(result)) {
    cout << "Milord proclaimeth: \"" << get<string>(result) << "\"!\n";
  }
  return result;
}

Value AssignmentNode::evaluate() const {
  Value result = expression->evaluate();
  setVar(name, result);
  return result;
}

Value CreationNode::evaluate() const {
  Value result = expression->evaluate();
  createVar(name, result);
  return result;
}

Value IfNode::evaluate() const {
  if (isTruthy(condition->evaluate())) {
    return thenBlock->evaluate();
  } else if (elseBlock) {
    return elseBlock->evaluate();
  }
  return 0;
}

Value BlockNode::evaluate() const {
  enterScope();
  Value result = 0;
  for (auto &statement : statements) {
    result = statement->evaluate();
  }
  exitScope();
  return result;
}

Value WhileNode::evaluate() const {
  while (isTruthy(condition->evaluate())) {
    block->evaluate();
  }
  return 0;
}
