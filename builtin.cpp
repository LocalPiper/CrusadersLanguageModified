#include "builtin.hpp"
#include "array.hpp"
#include "environment.hpp"
#include "function.hpp"
#include "value.hpp"
#include <memory>
#include <stdexcept>
#include <string>
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

void initialize_builtins() {
  createVar("array", make_shared<BuiltinFunction>(builtin_array));
}
