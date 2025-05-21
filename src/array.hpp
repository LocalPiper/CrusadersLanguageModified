#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "callable.hpp"
#include "environment.hpp"
#include "value.hpp"
#include <memory>
#include <stdexcept>

using namespace std;

class CrusaderArray : public CrusaderCallable {
  vector<Value> contents;
  Value getByIdx(int &index) {
    if (index < contents.size()) {
      return contents[index];
    }
    throw runtime_error("Error: index out of bounds");
  }

  void setByIdx(int &index, Value newVal) {
    if (index < contents.size()) {
      contents[index] = newVal;
      return;
    }
    throw runtime_error("Error: index out of bounds");
  }

public:
  CrusaderArray(vector<Value> &contents) : contents(contents) {}
  Value call(const vector<Value> &args) override {
    if (args.size() < 1 || args.size() > 2) {
      throw runtime_error("Error: illegal number of arguments for array");
    }
    int index = get<int>(args[0]);
    if (args.size() == 1) {
      return getByIdx(index);
    } else if (args.size() == 2) {
      setByIdx(index, args[1]);
    }
    return 0;
  }

  std::shared_ptr<CrusaderCallable> clone() const override {
    std::vector<Value> copied_elements;

    for (const auto &val : contents) {
      if (std::holds_alternative<std::shared_ptr<CrusaderCallable>>(val)) {
        auto callable = std::get<std::shared_ptr<CrusaderCallable>>(val);
        if (callable->getType() == "array") {
          copied_elements.push_back(callable->clone());
        } else {
          copied_elements.push_back(callable);
        }
      } else {
        copied_elements.push_back(val);
      }
    }

    return std::make_shared<CrusaderArray>(copied_elements);
  }

  int size() { return contents.size(); }

  string getType() const override { return "array"; }
};

class StringWrapper : public CrusaderCallable {
  const string &varName;
  string &str;

public:
  StringWrapper(const string &varName, string &str)
      : varName(varName), str(str) {}

  Value call(const vector<Value> &args) {
    if (args.size() == 1) {
      int index = get<int>(args[0]);
      if (index < 0 || index >= str.size())
        throw runtime_error("Error: index out of bounds");
      return string(1, str[index]);
    }
    if (args.size() == 2) {
      int index = get<int>(args[0]);
      const auto &newVal = args[1];
      if (!holds_alternative<string>(newVal) || get<string>(newVal).size() != 1)
        throw runtime_error(
            "Error: second argument must be a single-character string");
      str[index] = get<string>(newVal)[0];
      setVar(varName, str);
      return str;
    }
    throw runtime_error("Error: illegal number of arguments for string");
  }
  std::shared_ptr<CrusaderCallable> clone() const {
    return std::make_shared<StringWrapper>(*this);
  }

  int size() { return str.size(); }
  string getType() const { return "string"; }
};

#endif // ARRAY_HPP
