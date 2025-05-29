#include "optimizer.hpp"
#include "cfg.hpp"
#include "ir_struct.hpp"
#include "operations.hpp"
#include "value.hpp"
#include <algorithm>
#include <iostream>
#include <optional>
#include <ostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

std::optional<Value> parseLiteral(const std::string &raw) {
  try {
    if (std::regex_match(raw, std::regex(R"(^-?\d+$)"))) {
      return std::stoi(raw);
    }

    if (std::regex_match(raw, std::regex(R"(^-?\d*\.\d+(f?)$)"))) {
      return std::stod(raw);
    }

    if (!raw.empty() && raw.front() == '"' && raw.back() == '"') {
      return raw.substr(1, raw.size() - 2);
    }

    return std::nullopt;
  } catch (...) {
    return std::nullopt;
  }
}

std::string valueToString(const Value &val) {
  if (std::holds_alternative<int>(val)) {
    return std::to_string(std::get<int>(val));
  } else if (std::holds_alternative<double>(val)) {
    return std::to_string(std::get<double>(val));
  } else {
    const auto &s = std::get<std::string>(val);
    return "\"" + s + "\"";
  }
}

static bool hasSideEffect(const IRInstruction &instr) {
  switch (instr.opcode) {
  case IROpcode::PRINT:
  case IROpcode::CALL:
  case IROpcode::RETURN:
  case IROpcode::JUMP:
  case IROpcode::JUMP_IF_FALSE:
  case IROpcode::LABEL:
  case IROpcode::MAKE_FUNC:
    return true;
  default:
    return false;
  }
}

void copyPropagation(std::vector<BasicBlock *> &cfg) {
  std::unordered_map<std::string, std::string> globalCopies;

  for (auto *block : cfg) {
    std::unordered_map<std::string, std::string> copies = globalCopies;

    auto resolve = [&](const std::string &name) {
      std::string current = name;
      while (copies.count(current)) {
        current = copies[current];
      }
      return current;
    };

    for (auto &instr : block->instructions) {
      switch (instr.opcode) {
      case IROpcode::LOAD_VAR:
      case IROpcode::LOAD_CONST:
      case IROpcode::CALL:
      case IROpcode::MAKE_FUNC:
        instr.arg1 = resolve(instr.arg1);
        copies[instr.result] = instr.arg1;
        break;
      case IROpcode::LOAD_STRING:
        instr.arg1 = resolve(instr.arg1);
        copies[instr.result] = "\"" + instr.arg1 + "\"";
        break;
      case IROpcode::STORE_VAR: {
        std::string resolved = resolve(instr.arg2);
        instr.arg2 = resolved;
        copies[instr.arg1] = resolved;
        break;
      }
      case IROpcode::UNARY_OP:
        instr.arg1 = resolve(instr.arg1);
        break;
      case IROpcode::BINARY_OP:
        instr.arg1 = resolve(instr.arg1);
        instr.arg2 = resolve(instr.arg2);
        break;
      case IROpcode::PRINT:
      case IROpcode::RETURN:
      case IROpcode::JUMP_IF_FALSE:
        instr.arg1 = resolve(instr.arg1);
        break;
      default:
        break;
      }
    }
  }
}

void constantFold(const std::vector<BasicBlock *> &cfg) {
  using ConstMap = std::unordered_map<std::string, Value>;
  std::unordered_map<BasicBlock *, ConstMap> inConsts, outConsts;
  std::unordered_map<BasicBlock *, bool> visited;

  std::vector<BasicBlock *> worklist(cfg.begin(), cfg.end());

  auto parseLiteral = [](const std::string &raw) -> std::optional<Value> {
    if (std::regex_match(raw, std::regex(R"(^-?\d+$)")))
      return std::stoi(raw);
    if (std::regex_match(raw, std::regex(R"(^-?\d*\.\d+f?$)")))
      return std::stod(raw);
    return std::nullopt;
  };

  auto intersectConsts = [](const std::vector<ConstMap> &consts) -> ConstMap {
    if (consts.empty())
      return {};

    ConstMap result = consts.front();
    for (size_t i = 1; i < consts.size(); ++i) {
      for (auto it = result.begin(); it != result.end();) {
        if (!consts[i].count(it->first) ||
            consts[i].at(it->first) != it->second)
          it = result.erase(it);
        else
          ++it;
      }
    }
    return result;
  };

  while (!worklist.empty()) {
    BasicBlock *block = worklist.back();
    worklist.pop_back();

    std::vector<ConstMap> predConsts;
    for (auto *pred : block->pred)
      predConsts.push_back(outConsts[pred]);
    ConstMap in = intersectConsts(predConsts);

    if (visited[block] && in == inConsts[block])
      continue;

    inConsts[block] = in;
    visited[block] = true;

    ConstMap out = in;

    for (IRInstruction &instr : block->instructions) {
      auto getVal = [&](const std::string &s) -> std::optional<Value> {
        if (out.count(s))
          return out[s];
        return parseLiteral(s);
      };

      switch (instr.opcode) {
      case IROpcode::LOAD_CONST: {
        auto parsed = parseLiteral(instr.arg1);
        out[instr.result] = parsed ? *parsed : Value(instr.arg1);
        break;
      }
      case IROpcode::LOAD_VAR: {
        if (out.count(instr.arg1)) {
          instr.opcode = IROpcode::LOAD_CONST;
          instr.arg1 = valueToString(out[instr.arg1]);
        } else {
          out.erase(instr.result);
        }
        break;
      }
      case IROpcode::STORE_VAR: {
        if (out.count(instr.arg2)) {
          out[instr.arg1] = out[instr.arg2];
        } else {
          out.erase(instr.arg1);
        }
        break;
      }
      case IROpcode::BINARY_OP: {
        auto lhs = getVal(instr.arg1);
        auto rhs = getVal(instr.arg2);
        if (lhs && rhs) {
          Value res;
          if (instr.op == "&&") {
            res = isTruthy(*lhs) ? *rhs : *lhs;
          } else if (instr.op == "||") {
            res = isTruthy(*lhs) ? *lhs : *rhs;
          } else {
            res = applyBinaryOp(instr.op, *lhs, *rhs);
          }
          instr.opcode = IROpcode::LOAD_CONST;
          instr.arg1 = valueToString(res);
          instr.arg2.clear();
          instr.op.clear();
          out[instr.result] = res;
        } else {
          out.erase(instr.result);
        }
        break;
      }
      case IROpcode::UNARY_OP: {
        auto rhs = getVal(instr.arg1);
        if (rhs) {
          Value res = applyUnaryOp(instr.op, *rhs);
          instr.opcode = IROpcode::LOAD_CONST;
          instr.arg1 = valueToString(res);
          instr.op.clear();
          out[instr.result] = res;
        } else {
          out.erase(instr.result);
        }
        break;
      }
      default:
        if (!instr.result.empty())
          out.erase(instr.result);
        break;
      }
    }

    if (outConsts[block] != out) {
      outConsts[block] = out;
      for (BasicBlock *succ : block->succ)
        worklist.push_back(succ);
    }
  }
}

void deadCodeElimination(std::vector<BasicBlock *> &cfg) {
  using StrSet = std::unordered_set<std::string>;

  struct UD {
    StrSet use, def;
  };
  std::unordered_map<BasicBlock *, UD> B;
  for (auto *block : cfg) {
    UD &ud = B[block];
    for (auto &instr : block->instructions) {
      if (instr.opcode == IROpcode::STORE_VAR) {
        ud.def.insert(instr.arg1);
        if (!instr.arg2.empty())
          ud.use.insert(instr.arg2);
      } else {
        if (!instr.arg1.empty())
          ud.use.insert(instr.arg1);
        if (!instr.arg2.empty())
          ud.use.insert(instr.arg2);
        if (!instr.result.empty())
          ud.def.insert(instr.result);
      }
    }
  }

  std::unordered_map<BasicBlock *, StrSet> liveIn, liveOut;
  bool changed = true;
  while (changed) {
    changed = false;
    for (auto it = cfg.rbegin(); it != cfg.rend(); ++it) {
      BasicBlock *block = *it;
      StrSet newOut;
      for (BasicBlock *s : block->succ)
        newOut.insert(liveIn[s].begin(), liveIn[s].end());
      StrSet newIn = B[block].use;
      for (auto &v : newOut)
        if (!B[block].def.count(v))
          newIn.insert(v);

      if (newOut != liveOut[block] || newIn != liveIn[block]) {
        liveOut[block] = std::move(newOut);
        liveIn[block] = std::move(newIn);
        changed = true;
      }
    }
  }

  for (auto *block : cfg) {
    StrSet live = liveOut[block];
    IR newInstrs;
    for (auto it = block->instructions.rbegin();
         it != block->instructions.rend(); ++it) {
      IRInstruction &instr = *it;
      bool keep = false;

      if (hasSideEffect(instr)) {
        keep = true;
        if (!instr.arg1.empty())
          live.insert(instr.arg1);
        if (!instr.arg2.empty())
          live.insert(instr.arg2);

      } else if (instr.opcode == IROpcode::STORE_VAR) {
        if (live.count(instr.arg1)) {
          keep = true;
          if (!instr.arg2.empty())
            live.insert(instr.arg2);
        }
        live.erase(instr.arg1);

      } else if (!instr.result.empty()) {
        if (live.count(instr.result)) {
          keep = true;
          if (!instr.arg1.empty())
            live.insert(instr.arg1);
          if (!instr.arg2.empty())
            live.insert(instr.arg2);
        }
        live.erase(instr.result);
      }

      if (keep)
        newInstrs.push_back(instr);
    }

    std::reverse(newInstrs.begin(), newInstrs.end());
    block->instructions.swap(newInstrs);
  }
}

IR optimize(IR code) {
  std::vector<BasicBlock *> cfg = buildCFG(code);

  copyPropagation(cfg);
  std::cout << "after CP: " << std::endl;
  printIR(flattenCFG(cfg));
  constantFold(cfg);
  std::cout << "\nafter CF: " << std::endl;
  printIR(flattenCFG(cfg));
  deadCodeElimination(cfg);
  std::cout << "\nafter DCE: " << std::endl;
  return flattenCFG(cfg);
}
