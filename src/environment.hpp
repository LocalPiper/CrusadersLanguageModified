#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "value.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

extern vector<unordered_map<string, shared_ptr<Value>>> scopes;

void enterScope();

void exitScope();

Value getVar(const string &name);

void createVar(const string &name, Value value);

void setVar(const string &name, Value value);

#endif // ENVIRONMENT_HPP
