#include "ir.hpp"
#include "ast.hpp"

std::string IRGenerator::newTemp() {
  return "%t" + std::to_string(tempCounter++);
}

std::string IRGenerator::newLabel() {
  return "L" + std::to_string(labelCounter++);
}

void IRGenerator::visit(const ExpressionNode *expr) {
  expr->accept(*this);
}

void IRGenerator::visit(const StatementNode *stmt) {
  stmt->accept(*this);
}

void IRGenerator::visitExpressionStatementNode(const ExpressionStatementNode *node) {
  visit(node->expr);
}

void IRGenerator::visitDoubleNode(const DoubleNode *node) {
  lastValue = newTemp();
  code.emplace_back(IROpcode::LOAD_CONST, lastValue, std::to_string(node->value));
}

void IRGenerator::visitNumberNode(const NumberNode *node) {
  lastValue = newTemp();
  code.emplace_back(IROpcode::LOAD_CONST, lastValue, std::to_string(node->value));
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
  code.emplace_back(IROpcode::BINARY_OP, lastValue, leftVal, rightVal, node->op);
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
  if (node->elseBlock) visit(node->elseBlock);
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
  std::string endLabel = newLabel();

  code.emplace_back(IROpcode::LABEL, startLabel);
  visit(node->condition);
  code.emplace_back(IROpcode::JUMP_IF_FALSE, "", lastValue, endLabel);
  visit(node->block);
  if (node->step) visit(node->step);
  code.emplace_back(IROpcode::JUMP, "", startLabel);
  code.emplace_back(IROpcode::LABEL, endLabel);
}

void IRGenerator::visitFunctionDeclarationNode(const FunctionDeclarationNode *node) {
  visit(node->body);
}

void IRGenerator::visitFunctionCallNode(const FunctionCallNode *node) {
  if (node->callee) visit(node->callee);

  for (auto arg : node->arguments) {
    visit(arg);
  }
  lastValue = newTemp();
  code.emplace_back(IROpcode::CALL, lastValue, lastValue);
}

void IRGenerator::visitLambdaNode(const LambdaNode *node) {
  visit(node->body);
}

void IRGenerator::visitReturnNode(const ReturnNode *node) {
  visit(node->val);
  code.emplace_back(IROpcode::RETURN, "", lastValue);
}

void IRGenerator::visitBreakNode(const BreakNode *node) {
  return;
}

void IRGenerator::visitContinueNode(const ContinueNode *node) {
  return;
}
