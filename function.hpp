#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "ast.hpp"
#include "callable.hpp"
#include <exception>
#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

class CrusaderFunction : public CrusaderCallable {
  string functionName;
  vector<string> params;
  BlockNode *body;

public:
  CrusaderFunction() : functionName(""), params(), body(nullptr) {}
  CrusaderFunction(string name, vector<string> params, BlockNode *body)
      : functionName(name), params(params), body(body) {}
  Value call(const vector<Value> &args) const;
};

class BuiltinFunction : public CrusaderCallable {
public:
  string functionName;
  function<Value(const vector<Value> &)> func;
  BuiltinFunction(const string &name,
                  function<Value(const vector<Value> &)> func)
      : functionName(name), func(std::move(func)) {}

  Value call(const vector<Value> &args) { return func(args); }
};

class ReturnException : public exception {
public:
  Value value;
  ReturnException(const Value &val) : value(val) {}
  const char *what() const noexcept override { return "Function returned"; }
};

extern unordered_map<string, shared_ptr<CrusaderCallable>> functionTable;
#endif // FUNCTION_HPP
