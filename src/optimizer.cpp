#include "optimizer.hpp"
#include "ir_struct.hpp"
#include "operations.hpp"
#include "value.hpp"
#include <algorithm>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>

IR constantFold(const IR &code) {
  IR output;
  std::unordered_map<std::string, Value> constants;

  for (const auto &instr : code) {
    switch (instr.opcode) {

    case IROpcode::LOAD_CONST: {
      Value val;
      const std::string &raw = instr.arg1;

      if (std::regex_match(raw, std::regex(R"(^-?\d+$)"))) {
        val = std::stoi(raw);
      } else if (std::regex_match(raw, std::regex(R"(^-?\d*\.\d+(f?)$)"))) {
        val = std::stod(raw);
      } else {
        val = raw;
      }

      constants[instr.result] = val;
      output.push_back(instr);
      break;
    }

    case IROpcode::BINARY_OP: {
      auto it1 = constants.find(instr.arg1);
      auto it2 = constants.find(instr.arg2);

      if (it1 != constants.end() && it2 != constants.end()) {

        const Value &lhs = it1->second;
        const Value &rhs = it2->second;

        Value res;
        if (instr.op == "&&") {
          res = isTruthy(lhs) ? rhs : lhs;
        } else if (instr.op == "||") {
          res = isTruthy(lhs) ? lhs : rhs;
        } else {
          res = applyBinaryOp(instr.op, lhs, rhs);
        }

        std::string valStr;
        if (std::holds_alternative<int>(res)) {
          valStr = std::to_string(std::get<int>(res));
        } else if (std::holds_alternative<double>(res)) {
          valStr = std::to_string(std::get<double>(res));
        } else if (std::holds_alternative<std::string>(res)) {
          valStr = std::get<std::string>(res);
        }
        output.emplace_back(IROpcode::LOAD_CONST, instr.result, valStr);
        constants[instr.result] = res;
      } else {
        output.push_back(instr);
      }
      break;
    }

    case IROpcode::UNARY_OP: {
      auto it = constants.find(instr.arg1);
      if (it != constants.end()) {
        const Value &rhs = it->second;
        const Value &res = applyUnaryOp(instr.op, rhs);

        std::string valStr;
        if (std::holds_alternative<int>(res)) {
          valStr = std::to_string(std::get<int>(res));
        } else if (std::holds_alternative<double>(res)) {
          valStr = std::to_string(std::get<double>(res));
        } else if (std::holds_alternative<std::string>(res)) {
          valStr = std::get<std::string>(res);
        }
        output.emplace_back(IROpcode::LOAD_CONST, instr.result, valStr);
        constants[instr.result] = res;
      } else {
        output.push_back(instr);
      }
      break;
    }
    default:
      output.push_back(instr);
      if (!instr.result.empty()) {
        constants.erase(instr.result);
      }
      break;
    }
  }
  return output;
}

IR deadCodeElim(const IR &code) {
  std::unordered_set<std::string> live;
  IR output;

  auto hasSideEffect = [](const IRInstruction &instr) -> bool {
    switch (instr.opcode) {
    case IROpcode::PRINT:
    case IROpcode::CALL:
    case IROpcode::RETURN:
    case IROpcode::JUMP:
    case IROpcode::JUMP_IF_FALSE:
    case IROpcode::LABEL:
    case IROpcode::FUNC_BEGIN:
    case IROpcode::FUNC_END:
    case IROpcode::MAKE_FUNC:
      return true;
    default:
      return false;
    }
  };

  for (auto it = code.rbegin(); it != code.rend(); ++it) {
    const IRInstruction &instr = *it;

    if (instr.opcode == IROpcode::STORE_VAR) {
      if (live.count(instr.arg1)) {
        if (!instr.arg2.empty())
          live.insert(instr.arg2);
        output.push_back(instr);
      }
      continue;
    }

    bool isLive = !instr.result.empty() && live.count(instr.result);
    if (isLive || hasSideEffect(instr)) {
      if (!instr.arg1.empty())
        live.insert(instr.arg1);
      if (!instr.arg2.empty())
        live.insert(instr.arg2);
      output.push_back(instr);
    }
  }

  std::reverse(output.begin(), output.end());
  return output;
}

IR optimize(IR code) {
  code = constantFold(code);
  code = deadCodeElim(code);
  return code;
}
