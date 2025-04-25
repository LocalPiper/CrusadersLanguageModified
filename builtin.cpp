#include "builtin.hpp"
#include "array.hpp"
#include "environment.hpp"
#include "function.hpp"
#include "value.hpp"
#include <memory>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

using namespace std;

// very dumb array
Value builtin_array(const vector<Value> &args) {
  if (args.size() < 1) {
    throw runtime_error("'array' expects at least 1 argument, " +
                        to_string((int)args.size()) + " were given.");
  }

  vector<Value> arr;
  for (int i = 0; i <= args.size(); ++i)
    arr.push_back(args[i]);
  return make_shared<CrusaderArray>(arr);
}

Value builtin_generate_array(const vector<Value> &args) {
  if (args.size() != 2) {
    throw runtime_error("'generate_array' expects exactly 2 arguments, " +
                        to_string(args.size()) + " were given.");
  }
  int sz = get<int>(args[0]);
  vector<Value> arr;
  for (int i = 0; i < sz; ++i) {
    const Value &element = args[1];
    if (holds_alternative<shared_ptr<CrusaderCallable>>(element)) {
      auto callable = get<shared_ptr<CrusaderCallable>>(element);
      if (callable->getType() == "array") {
        arr.push_back(callable->clone());
      } else {
        arr.push_back(callable);
      }
    } else {
      arr.push_back(element);
    }
  }
  return make_shared<CrusaderArray>(arr);
}
void initialize_builtins() {
  createVar("array", make_shared<BuiltinFunction>(builtin_array));
  createVar("generate_array",
            make_shared<BuiltinFunction>(builtin_generate_array));
}
