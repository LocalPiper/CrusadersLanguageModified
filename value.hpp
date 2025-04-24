#ifndef VALUE_HPP
#define VALUE_HPP

#include <memory>
#include <string>
#include <variant>

class CrusaderCallable;

using Value =
    std::variant<int, double, std::string, std::shared_ptr<CrusaderCallable>>;

#endif // VALUE_HPP
