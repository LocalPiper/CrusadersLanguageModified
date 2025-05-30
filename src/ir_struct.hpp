#ifndef IR_STRUCT_HPP
#define IR_STRUCT_HPP
#include <iostream>
#include <string>
#include <vector>

enum class IROpcode {
  LOAD_CONST,
  LOAD_STRING,
  LOAD_VAR,
  STORE_VAR,
  BINARY_OP,
  UNARY_OP,
  PRINT,
  JUMP,
  JUMP_IF_FALSE,
  LABEL,
  CALL,
  RETURN,

  FUNC_BEGIN,
  FUNC_END,
  MAKE_FUNC
};

struct IRInstruction {
  IROpcode opcode;
  std::string result;
  std::string arg1;
  std::string arg2;
  std::string op;

  IRInstruction(IROpcode op_, std::string res = "", std::string a1 = "",
                std::string a2 = "", std::string opStr = "")
      : opcode(op_), result(std::move(res)), arg1(std::move(a1)),
        arg2(std::move(a2)), op(std::move(opStr)) {}
};

struct CallMetadata {
  std::string callResult;
  std::string callee;
  std::vector<std::string> argumentTemps;
};

using IR = std::vector<IRInstruction>;

inline void printIR(const IR &ir) {
  for (const auto &instr : ir) {
    switch (instr.opcode) {
    case IROpcode::LOAD_CONST:
    case IROpcode::LOAD_VAR:
      std::cout << instr.result << " = " << instr.arg1 << "\n";
      break;
    case IROpcode::LOAD_STRING:
      std::cout << instr.result << " = \"" << instr.arg1 << "\"\n";
      break;
    case IROpcode::STORE_VAR:
      std::cout << instr.arg1 << " = " << instr.arg2 << "\n";
      break;
    case IROpcode::BINARY_OP:
      std::cout << instr.result << " = " << instr.arg1 << " " << instr.op << " "
                << instr.arg2 << "\n";
      break;
    case IROpcode::UNARY_OP:
      std::cout << instr.result << " = " << instr.op << instr.arg1 << "\n";
      break;
    case IROpcode::PRINT:
      std::cout << "print " << instr.arg1 << "\n";
      break;
    case IROpcode::JUMP:
      std::cout << "goto " << instr.arg1 << "\n";
      break;
    case IROpcode::JUMP_IF_FALSE:
      std::cout << "ifFalse " << instr.arg1 << " goto " << instr.arg2 << "\n";
      break;
    case IROpcode::LABEL:
      std::cout << instr.result << ":\n";
      break;
    case IROpcode::CALL:
      std::cout << instr.result << " = call " << instr.arg1 << "\n";
      break;
    case IROpcode::RETURN:
      std::cout << "return " << instr.arg1 << "\n";
      break;
    case IROpcode::FUNC_BEGIN:
      std::cout << "# begin func " << instr.result << "\n";
      break;
    case IROpcode::FUNC_END:
      std::cout << "# end func " << instr.result << "\n";
      break;
    case IROpcode::MAKE_FUNC:
      std::cout << instr.result << " = function " << instr.arg1 << "\n";
      break;
    }
  }
}

#endif // IR_STRUCT_HPP
