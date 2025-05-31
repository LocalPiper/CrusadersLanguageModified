#ifndef CALLABLE_HPP
#define CALLABLE_HPP

#include "value.hpp"
#include <memory>
#include <vector>

class CrusaderCallable {
public:
  virtual std::string getType() const = 0;
  virtual std::shared_ptr<CrusaderCallable> clone() const = 0;
  virtual Value call(const std::vector<Value> &args) = 0;
  virtual ~CrusaderCallable() = default;
};

#endif // CALLABLE_HPP
