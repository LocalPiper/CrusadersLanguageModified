#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "ast.hpp"
#include "callable.hpp"
#include "environment.hpp"
#include <exception>
#include <functional>
#include <memory>
#include <utility>
using namespace std;

class CrusaderFunction : public CrusaderCallable {
  vector<string> params;
  BlockNode *body;
  vector<unordered_map<string, shared_ptr<Value>>> capturedScopes;

public:
  CrusaderFunction(vector<string> params, BlockNode *body)
      : params(params), body(body), capturedScopes(scopes) {}
  Value call(const vector<Value> &args);
  std::shared_ptr<CrusaderCallable> clone() const;
  string getType() const;
};

class BuiltinFunction : public CrusaderCallable {
public:
  function<Value(const vector<Value> &)> func;
  BuiltinFunction(function<Value(const vector<Value> &)> func)
      : func(std::move(func)) {}

  Value call(const vector<Value> &args) override { return func(args); }

  string getType() const override { return "builtin"; }
  std::shared_ptr<CrusaderCallable> clone() const override {
    return std::make_shared<BuiltinFunction>(*this);
  }
};

class ReturnException : public exception {
public:
  Value value;
  ReturnException(const Value &val) : value(val) {}
  const char *what() const noexcept override { return "Function returned"; }
};

class BreakException : public exception {
public:
  const char *what() const noexcept override { return "Breaking out of loop"; }
};

class ContinueException : public exception {
public:
  const char *what() const noexcept override { return "Continuing loop"; }
};

#endif // FUNCTION_HPP
