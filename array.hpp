#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "callable.hpp"
#include "value.hpp"
#include <stdexcept>
#include <vector>

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
  Value call(const vector<Value> &args) {
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
};

#endif // ARRAY_HPP
