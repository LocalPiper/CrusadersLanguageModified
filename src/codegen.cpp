#include "codegen.hpp"
#include "ir_struct.hpp"
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::string> generate(const IR &code) {
  std::vector<std::string> asmLines;
  // x1:x30 - variables
  // x31 - stack pointer

  int currReg = 1;

  std::unordered_map<std::string, int> varToReg;
  for (const auto instr : code) {
    switch (instr.opcode) {
    case IROpcode::STORE_VAR:
      if (varToReg.find(instr.arg1) == varToReg.end()) {
        varToReg[instr.arg1] = currReg++;
      }
      break;
    case IROpcode::LOAD_STRING:
    case IROpcode::LOAD_CONST:
    case IROpcode::LOAD_VAR:
    case IROpcode::UNARY_OP:
    case IROpcode::BINARY_OP: {
      if (varToReg.find(instr.result) == varToReg.end()) {
        varToReg[instr.result] = currReg++;
      }
      break;
    }
    default:
      break;
    }
  }

  std::vector<int> usedRegs(32);
  for (const auto instr : code) {
    switch (instr.opcode) {
    case IROpcode::LOAD_STRING:
    case IROpcode::LOAD_CONST: {
      if (!usedRegs[varToReg[instr.result]]) {
        usedRegs[varToReg[instr.result]] = 1;
        asmLines.push_back(" li x" + std::to_string(varToReg[instr.result]) +
                           ", " + instr.arg1);
      } else {
        asmLines.push_back(" addi x" + std::to_string(varToReg[instr.result]) +
                           ", x" + std::to_string(varToReg[instr.arg1]) +
                           ", 0");
      }
      break;
    }
    case IROpcode::LOAD_VAR: {
      asmLines.push_back(" addi x" + std::to_string(varToReg[instr.result]) +
                         ", x" + std::to_string(varToReg[instr.arg1]) + ", 0");
      break;
    }
    case IROpcode::STORE_VAR: {
      asmLines.push_back(" addi x" + std::to_string(varToReg[instr.arg1]) +
                         ", x" + std::to_string(varToReg[instr.arg2]) + ", 0");
      break;
    }
    case IROpcode::UNARY_OP: {
      if (instr.op == "-") {
        asmLines.push_back(" sub x" + std::to_string(varToReg[instr.result]) +
                           ", x0, x" + std::to_string(varToReg[instr.arg1]));
      } else if (instr.op == "!") {
        asmLines.push_back(" xor x" + std::to_string(varToReg[instr.result]) +
                           ", x" + std::to_string(varToReg[instr.arg1]) +
                           ", -1");
      }
      break;
    }
    case IROpcode::BINARY_OP: {
      if (instr.op == "+") {
        asmLines.push_back(" add x" + std::to_string(varToReg[instr.result]) +
                           ", x" + std::to_string(varToReg[instr.arg1]) +
                           ", x" + std::to_string(varToReg[instr.arg2]));
      } else if (instr.op == "-") {
        asmLines.push_back(" sub x" + std::to_string(varToReg[instr.result]) +
                           ", x" + std::to_string(varToReg[instr.arg1]) +
                           ", x" + std::to_string(varToReg[instr.arg2]));
      } else if (instr.op == "|") {
        asmLines.push_back(" or x" + std::to_string(varToReg[instr.result]) +
                           ", x" + std::to_string(varToReg[instr.arg1]) +
                           ", x" + std::to_string(varToReg[instr.arg2]));
      } else if (instr.op == "||") {
        asmLines.push_back(" or x" + std::to_string(varToReg[instr.result]) +
                           ", x" + std::to_string(varToReg[instr.arg1]) +
                           ", x" + std::to_string(varToReg[instr.arg2]));
      } else if (instr.op == "&&") {
        asmLines.push_back(" and x" + std::to_string(varToReg[instr.result]) +
                           ", x" + std::to_string(varToReg[instr.arg1]) +
                           ", x" + std::to_string(varToReg[instr.arg2]));
      } else if (instr.op == "*") {
        asmLines.push_back(" mul x" + std::to_string(varToReg[instr.result]) +
                           ", x" + std::to_string(varToReg[instr.arg1]) +
                           ", x" + std::to_string(varToReg[instr.arg2]));
      } else if (instr.op == "/") {
        asmLines.push_back(" div x" + std::to_string(varToReg[instr.result]) +
                           ", x" + std::to_string(varToReg[instr.arg1]) +
                           ", x" + std::to_string(varToReg[instr.arg2]));
      } else if (instr.op == "%") {
        asmLines.push_back(" rem x" + std::to_string(varToReg[instr.result]) +
                           ", x" + std::to_string(varToReg[instr.arg1]) +
                           ", x" + std::to_string(varToReg[instr.arg2]));
      } else if (instr.op == "==") {
        asmLines.push_back(" seq x" + std::to_string(varToReg[instr.result]) +
                           ", x" + std::to_string(varToReg[instr.arg1]) +
                           ", x" + std::to_string(varToReg[instr.arg2]));
      } else if (instr.op == "!=") {
        asmLines.push_back(" sne x" + std::to_string(varToReg[instr.result]) +
                           ", x" + std::to_string(varToReg[instr.arg1]) +
                           ", x" + std::to_string(varToReg[instr.arg2]));
      } else if (instr.op == "<") {
        asmLines.push_back(" slt x" + std::to_string(varToReg[instr.result]) +
                           ", x" + std::to_string(varToReg[instr.arg1]) +
                           ", x" + std::to_string(varToReg[instr.arg2]));
      } else if (instr.op == ">") {
        asmLines.push_back(" slt x" + std::to_string(varToReg[instr.result]) +
                           ", x" + std::to_string(varToReg[instr.arg2]) +
                           ", x" + std::to_string(varToReg[instr.arg1]));
      } else if (instr.op == "<=") {
        asmLines.push_back(" sge x" + std::to_string(varToReg[instr.result]) +
                           ", x" + std::to_string(varToReg[instr.arg2]) +
                           ", x" + std::to_string(varToReg[instr.arg1]));
      } else if (instr.op == ">=") {
        asmLines.push_back(" sge x" + std::to_string(varToReg[instr.result]) +
                           ", x" + std::to_string(varToReg[instr.arg1]) +
                           ", x" + std::to_string(varToReg[instr.arg2]));
      }
      break;
    }
    case IROpcode::LABEL: {
      asmLines.push_back(instr.result + ":");
      break;
    }
    case IROpcode::JUMP_IF_FALSE: {
      asmLines.push_back(" beq x" + std::to_string(varToReg[instr.arg1]) +
                         ", x0, " + instr.arg2);
      break;
    }
    case IROpcode::JUMP: {
      asmLines.push_back(" jal x0, " + instr.arg1);
      break;
    }
    default:
      break;
    }
  }

  asmLines.push_back(" ebreak");
  return asmLines;
}

void writeAsm(const IR &code) {
  std::ofstream outFile("out.s");

  const auto asmLines = generate(code);

  for (const auto &line : asmLines) {
    outFile << line << "\n";
  }

  outFile.close();
}
