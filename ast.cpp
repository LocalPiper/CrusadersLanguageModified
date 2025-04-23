#include "ast.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

using namespace std;

using Value = variant<int, double, string>;
enum class TypeRank { INT = 1, DOUBLE = 2, STRING = 3 };

TypeRank getTypeRank(const Value &val) {
  if (holds_alternative<int>(val))
    return TypeRank::INT;
  if (holds_alternative<double>(val))
    return TypeRank::DOUBLE;
  if (holds_alternative<string>(val))
    return TypeRank::STRING;
  throw runtime_error("Unknown type in Value");
}

// type promotion
// we assume these rules
// TYPE A     TYPE B     RESULT
// int        int        int
// int        double     double
// double     double     double
// int        string     string
// double     string     string
// string     string     string
//
// so as we can see, RESULT = MAX(TYPE A, TYPE B)
TypeRank promote(const Value &a, const Value &b) {
  return max(getTypeRank(a), getTypeRank(b));
}

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
  if (holds_alternative<double>(val))
    return get<double>(val) != 0; // this is not good, i should probably test it
  if (holds_alternative<string>(val))
    return !get<string>(val).empty();
  return false;
}

Value VariableNode::evaluate() const { return getVar(name); }

bool isValidOperation(const string &op, TypeRank type) {
  switch (type) {
  case TypeRank::INT:
  case TypeRank::DOUBLE:
    return op == "+" || op == "-" || op == "*" || op == "/" || op == "==" ||
           op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=";
  case TypeRank::STRING:
    return op == "+" || op == "==" || op == "!=";
  default:
    return false;
  }
}

Value applyBinaryOp(const string &op, const Value &lval, const Value &rval) {
  TypeRank resultingRank = promote(lval, rval);
  if (!isValidOperation(op, resultingRank)) {
    cerr << "Error: Operation '" << op << "' not valid for types." << endl;
  }

  switch (resultingRank) {
  case TypeRank::INT: {
    int l = get<int>(lval), r = get<int>(rval);
    if (op == "+")
      return l + r;
    if (op == "-")
      return l - r;
    if (op == "*")
      return l * r;
    if (op == "/")
      return r != 0 ? l / r : 0;
    if (op == "==")
      return l == r;
    if (op == "!=")
      return l != r;
    if (op == "<")
      return l < r;
    if (op == ">")
      return l > r;
    if (op == "<=")
      return l <= r;
    if (op == ">=")
      return l >= r;
    break;
  }
  case TypeRank::DOUBLE: {
    double l =
        holds_alternative<double>(lval) ? get<double>(lval) : get<int>(lval);
    double r =
        holds_alternative<double>(rval) ? get<double>(rval) : get<int>(rval);
    if (op == "+")
      return l + r;
    if (op == "-")
      return l - r;
    if (op == "*")
      return l * r;
    if (op == "/")
      return r != 0.0 ? l / r : 0.0;
    if (op == "==")
      return l == r;
    if (op == "!=")
      return l != r;
    if (op == "<")
      return l < r;
    if (op == ">")
      return l > r;
    if (op == "<=")
      return l <= r;
    if (op == ">=")
      return l >= r;
    break;
  }
  case TypeRank::STRING: {
    string l, r;

    if (holds_alternative<string>(lval)) {
      l = get<string>(lval);
    } else if (holds_alternative<double>(lval)) {
      l = to_string(get<double>(lval));
    } else if (holds_alternative<int>(lval)) {
      l = to_string(get<int>(lval));
    }

    if (holds_alternative<string>(rval)) {
      r = get<string>(rval);
    } else if (holds_alternative<double>(rval)) {
      r = to_string(get<double>(rval));
    } else if (holds_alternative<int>(rval)) {
      r = to_string(get<int>(rval));
    }

    if (op == "+") {
      return l + r;
    } else if (op == "==") {
      return l == r;
    } else if (op == "!=") {
      return l != r;
    }
    break;
  }
  }
  cerr << "Unhandled binary operation. \n";
  return 0;
}

Value BinaryOpNode::evaluate() const {
  Value lval = left->evaluate();
  if (op == "&&") {
    return isTruthy(lval) ? right->evaluate() : lval;
  }
  if (op == "||") {
    return isTruthy(lval) ? lval : right->evaluate();
  }
  Value rval = right->evaluate();
  return applyBinaryOp(op, lval, rval);
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

void PrintNode::evaluate() const {
  Value result = expression->evaluate();
  if (holds_alternative<int>(result)) {
    cout << "Milord proclaimeth: " << get<int>(result) << "!\n";
  } else if (holds_alternative<double>(result)) {
    cout << "Milord proclaimeth: " << get<double>(result) << "!\n";
  } else if (holds_alternative<string>(result)) {
    cout << "Milord proclaimeth: \"" << get<string>(result) << "\"!\n";
  }
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

void IfNode::evaluate() const {
  if (isTruthy(condition->evaluate())) {
    thenBlock->evaluate();
    return;
  } else if (elseBlock) {
    elseBlock->evaluate();
    return;
  }
}

void BlockNode::evaluate() const {
  enterScope();
  Value result = 0;
  for (auto &statement : statements) {
    statement->evaluate();
  }
  exitScope();
}

void WhileNode::evaluate() const {
  while (isTruthy(condition->evaluate())) {
    block->evaluate();
  }
}
