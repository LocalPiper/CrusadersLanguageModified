#include "ir.hpp"
#include "ast.hpp"
#include "ir_struct.hpp"
#include <string>
#include <utility>
#include <vector>

struct LoopContext {
  std::string startLabel;
  std::string stepLabel;
  std::string endLabel;
};

std::vector<LoopContext> loopStack;

std::string IRGenerator::newTemp() {
  return "%t" + std::to_string(tempCounter++);
}

std::string IRGenerator::newLabel() {
  return "L" + std::to_string(labelCounter++);
}

std::string IRGenerator::newFunc() {
  return "fn_" + std::to_string(funcCounter++);
}

void IRGenerator::visit(const ExpressionNode *expr) { expr->accept(*this); }

void IRGenerator::visit(const StatementNode *stmt) { stmt->accept(*this); }

void IRGenerator::visitExpressionStatementNode(
    const ExpressionStatementNode *node) {
  visit(node->expr);
}

void IRGenerator::visitDoubleNode(const DoubleNode *node) {
  lastValue = newTemp();
  code.emplace_back(IROpcode::LOAD_CONST, lastValue,
                    std::to_string(node->value));
}

void IRGenerator::visitNumberNode(const NumberNode *node) {
  lastValue = newTemp();
  code.emplace_back(IROpcode::LOAD_CONST, lastValue,
                    std::to_string(node->value));
}

void IRGenerator::visitStringNode(const StringNode *node) {
  lastValue = newTemp();
  code.emplace_back(IROpcode::LOAD_STRING, lastValue, node->value);
}

void IRGenerator::visitVariableNode(const VariableNode *node) {
  lastValue = newTemp();
  code.emplace_back(IROpcode::LOAD_VAR, lastValue, node->name);
}

void IRGenerator::visitBinaryOpNode(const BinaryOpNode *node) {
  visit(node->left);
  std::string leftVal = lastValue;
  visit(node->right);
  std::string rightVal = lastValue;

  lastValue = newTemp();
  code.emplace_back(IROpcode::BINARY_OP, lastValue, leftVal, rightVal,
                    node->op);
}

void IRGenerator::visitUnaryOpNode(const UnaryOpNode *node) {
  visit(node->right);
  std::string rightVal = lastValue;

  lastValue = newTemp();
  code.emplace_back(IROpcode::UNARY_OP, lastValue, rightVal, "", node->op);
}

void IRGenerator::visitPrintNode(const PrintNode *node) {
  visit(node->expression);
  code.emplace_back(IROpcode::PRINT, "", lastValue);
}

void IRGenerator::visitAssignmentNode(const AssignmentNode *node) {
  visit(node->expression);
  code.emplace_back(IROpcode::STORE_VAR, "", node->name, lastValue);
}

void IRGenerator::visitCreationNode(const CreationNode *node) {
  visit(node->expression);
  code.emplace_back(IROpcode::STORE_VAR, "", node->name, lastValue);
}

void IRGenerator::visitIfNode(const IfNode *node) {
  visit(node->condition);
  std::string condVal = lastValue;
  std::string elseLabel = newLabel();
  std::string endLabel = newLabel();

  code.emplace_back(IROpcode::JUMP_IF_FALSE, "", condVal, elseLabel);
  visit(node->thenBlock);
  code.emplace_back(IROpcode::JUMP, "", endLabel);
  code.emplace_back(IROpcode::LABEL, elseLabel);
  if (node->elseBlock)
    visit(node->elseBlock);
  code.emplace_back(IROpcode::LABEL, endLabel);
}

void IRGenerator::visitTernaryIfNode(const TernaryIfNode *node) {
  visit(node->condition);
  std::string condVal = lastValue;
  std::string elseLabel = newLabel();
  std::string endLabel = newLabel();
  std::string resultTemp = newTemp();

  code.emplace_back(IROpcode::JUMP_IF_FALSE, "", condVal, elseLabel);
  visit(node->thenExpr);
  code.emplace_back(IROpcode::STORE_VAR, "", resultTemp, lastValue);
  code.emplace_back(IROpcode::JUMP, "", endLabel);
  code.emplace_back(IROpcode::LABEL, elseLabel);
  visit(node->elseExpr);
  code.emplace_back(IROpcode::STORE_VAR, "", resultTemp, lastValue);
  code.emplace_back(IROpcode::LABEL, endLabel);

  lastValue = resultTemp;
}

void IRGenerator::visitBlockNode(const BlockNode *node) {
  for (auto stmt : node->statements) {
    visit(stmt);
  }
}

void IRGenerator::visitWhileNode(const WhileNode *node) {
  std::string startLabel = newLabel();
  std::string stepLabel = newLabel();
  std::string endLabel = newLabel();

  loopStack.push_back({startLabel, stepLabel, endLabel});
  code.emplace_back(IROpcode::LABEL, startLabel);
  visit(node->condition);
  code.emplace_back(IROpcode::JUMP_IF_FALSE, "", lastValue, endLabel);
  visit(node->block);
  code.emplace_back(IROpcode::LABEL, stepLabel);
  if (node->step)
    visit(node->step);
  code.emplace_back(IROpcode::JUMP, "", startLabel);
  code.emplace_back(IROpcode::LABEL, endLabel);
  loopStack.pop_back();
}

void IRGenerator::visitFunctionDeclarationNode(
    const FunctionDeclarationNode *node) {
  std::string funcLabel = newFunc();
  deferredFunctions.emplace_back(funcLabel, node->body);

  std::string temp = newTemp();
  code.emplace_back(IROpcode::MAKE_FUNC, temp, funcLabel);
  code.emplace_back(IROpcode::STORE_VAR, "", node->name, temp);
}

void IRGenerator::visitFunctionCallNode(const FunctionCallNode *node) {
  std::string calleeTemp;
  if (node->callee) {
    visit(node->callee);
    calleeTemp = lastValue;
  } else {
    calleeTemp = newTemp();
    code.emplace_back(IROpcode::LOAD_VAR, calleeTemp, node->name);
  }

  std::vector<std::string> argTemps;
  for (auto arg : node->arguments) {
    visit(arg);
    argTemps.push_back(lastValue);
  }

  std::string callTemp = newTemp();
  code.emplace_back(IROpcode::CALL, callTemp, calleeTemp);
  lastValue = callTemp;

  callMetadata.push_back(CallMetadata{
      .callResult = callTemp, .callee = calleeTemp, .argumentTemps = argTemps});
}

void IRGenerator::visitLambdaNode(const LambdaNode *node) {
  std::string funcLabel = newFunc();
  deferredFunctions.emplace_back(funcLabel, node->body);

  std::string temp = newTemp();
  code.emplace_back(IROpcode::MAKE_FUNC, temp, funcLabel);
  lastValue = temp;
}

void IRGenerator::visitReturnNode(const ReturnNode *node) {
  visit(node->val);
  code.emplace_back(IROpcode::RETURN, "", lastValue);
}

void IRGenerator::visitBreakNode(const BreakNode *node) {
  code.emplace_back(IROpcode::JUMP, "", loopStack.back().endLabel);
}

void IRGenerator::visitContinueNode(const ContinueNode *node) {
  code.emplace_back(IROpcode::JUMP, "", loopStack.back().stepLabel);
}

void IRGenerator::emitDeferredFunctions() {
  std::vector<std::pair<std::string, const BlockNode *>> queue =
      deferredFunctions;
  deferredFunctions.clear();

  while (!queue.empty()) {
    auto [label, body] = queue.back();
    queue.pop_back();

    code.emplace_back(IROpcode::FUNC_BEGIN, label);
    visit(body);
    code.emplace_back(IROpcode::RETURN, "", "0");
    code.emplace_back(IROpcode::FUNC_END, label);

    for (auto &f : deferredFunctions) {
      queue.push_back(f);
    }
    deferredFunctions.clear();
  }
}
