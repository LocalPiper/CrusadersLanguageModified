#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

#include "value.hpp"
#include <string>
Value applyBinaryOp(const std::string &op, const Value &lval,
                    const Value &rval);

Value applyUnaryOp(const std::string &op, const Value &rval);

bool isTruthy(const Value &val);

#endif // !OPERATIONS_HPP
