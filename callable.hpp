#ifndef CALLABLE_HPP
#define CALLABLE_HPP

#include "value.hpp"
#include <vector>

class CrusaderCallable {
public:
  virtual Value call(const std::vector<Value> &args) = 0;
  virtual ~CrusaderCallable() = default;
};

#endif // CALLABLE_HPP
