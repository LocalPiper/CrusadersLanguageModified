#include "builtin.hpp"
#include "ast.hpp"
#include "function.hpp"
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

  int N = get<int>(args[0]);
  Value arr[N];
  for (int i = 1; i <= N; ++i)
    arr[i - 1] = args[i];
  return "created array of size " + to_string(N);
}

void initialize_builtins() {
  functionTable["array"] = make_shared<BuiltinFunction>("array", builtin_array);
}
