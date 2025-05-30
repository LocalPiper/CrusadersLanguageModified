#include "operations.hpp"
#include <stdexcept>
#include <variant>
enum class TypeRank { INT = 1, DOUBLE = 2, STRING = 3 };

TypeRank getTypeRank(const Value &val) {
  if (std::holds_alternative<int>(val))
    return TypeRank::INT;
  if (std::holds_alternative<double>(val))
    return TypeRank::DOUBLE;
  if (std::holds_alternative<std::string>(val))
    return TypeRank::STRING;
  throw std::runtime_error("Unknown type in Value");
}

// type promotion
// we assume these rules
// TYPE A     TYPE B     RESULT
// int        int        int
// int        double     double
// double     double     double
// int        string     string
// double     string     string
// string     string     string
//
// so as we can see, RESULT = MAX(TYPE A, TYPE B)
TypeRank promote(const Value &a, const Value &b) {
  return std::max(getTypeRank(a), getTypeRank(b));
}

bool isTruthy(const Value &val) {
  if (std::holds_alternative<int>(val))
    return std::get<int>(val) != 0;
  if (std::holds_alternative<double>(val))
    return std::get<double>(val) !=
           0; // this is not good, i should probably test it
  if (std::holds_alternative<std::string>(val))
    return !std::get<std::string>(val).empty();
  return false;
}

bool isValidOperation(const std::string &op, TypeRank type) {
  switch (type) {
  case TypeRank::INT:
    return op == "+" || op == "-" || op == "*" || op == "/" || op == "%" ||
           op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" ||
           op == ">=";
  case TypeRank::DOUBLE:
    return op == "+" || op == "-" || op == "*" || op == "/" || op == "==" ||
           op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=";
  case TypeRank::STRING:
    return op == "+" || op == "==" || op == "!=";
  default:
    return false;
  }
}

Value applyBinaryOp(const std::string &op, const Value &lval,
                    const Value &rval) {
  TypeRank resultingRank = promote(lval, rval);
  if (!isValidOperation(op, resultingRank)) {
    throw std::runtime_error("Error: Operation '" + op +
                             "' not valid for provided types.");
  }

  switch (resultingRank) {
  case TypeRank::INT: {
    int l = std::get<int>(lval), r = std::get<int>(rval);
    if (op == "+")
      return l + r;
    if (op == "-")
      return l - r;
    if (op == "*")
      return l * r;
    if (op == "/") {
      if (r == 0)
        throw std::runtime_error("Error: division by 0");
      return l / r;
    }
    if (op == "%") {
      if (r == 0)
        throw std::runtime_error("Error: modulo of 0");
      return l % r;
    }
    if (op == "==")
      return l == r;
    if (op == "!=")
      return l != r;
    if (op == "<")
      return l < r;
    if (op == ">")
      return l > r;
    if (op == "<=")
      return l <= r;
    if (op == ">=")
      return l >= r;
    break;
  }
  case TypeRank::DOUBLE: {
    double l = std::holds_alternative<double>(lval) ? std::get<double>(lval)
                                                    : std::get<int>(lval);
    double r = std::holds_alternative<double>(rval) ? std::get<double>(rval)
                                                    : std::get<int>(rval);
    if (op == "+")
      return l + r;
    if (op == "-")
      return l - r;
    if (op == "*")
      return l * r;
    if (op == "/") {
      if (r == 0.0)
        throw std::runtime_error("Error: division by 0");
      return l / r;
    }
    if (op == "==")
      return l == r;
    if (op == "!=")
      return l != r;
    if (op == "<")
      return l < r;
    if (op == ">")
      return l > r;
    if (op == "<=")
      return l <= r;
    if (op == ">=")
      return l >= r;
    break;
  }
  case TypeRank::STRING: {
    std::string l, r;

    if (std::holds_alternative<std::string>(lval)) {
      l = std::get<std::string>(lval);
    } else if (std::holds_alternative<double>(lval)) {
      l = std::to_string(std::get<double>(lval));
    } else if (std::holds_alternative<int>(lval)) {
      l = std::to_string(std::get<int>(lval));
    }

    if (std::holds_alternative<std::string>(rval)) {
      r = std::get<std::string>(rval);
    } else if (std::holds_alternative<double>(rval)) {
      r = std::to_string(std::get<double>(rval));
    } else if (std::holds_alternative<int>(rval)) {
      r = std::to_string(std::get<int>(rval));
    }

    if (op == "+") {
      return l + r;
    } else if (op == "==") {
      return l == r;
    } else if (op == "!=") {
      return l != r;
    }
    break;
  }
  }
  throw std::runtime_error("Error: Unhandled binary operation.");
}

Value applyUnaryOp(const std::string &op, const Value &rval) {
  if (op == "-") {
    if (std::holds_alternative<double>(rval))
      return -std::get<double>(rval);
    if (std::holds_alternative<int>(rval))
      return -std::get<int>(rval);
    throw std::runtime_error(
        "Error: Unary '-' can only be applied to numbers.");
  } else if (op == "!") {
    return !isTruthy(rval);
  }
  throw std::runtime_error("Error: Unknown or invalid unary operator " + op);
}
