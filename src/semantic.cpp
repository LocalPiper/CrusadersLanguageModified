#include "semantic.hpp"
#include "ast.hpp"

using namespace std;

void Visitor::visit(const ExpressionNode *expr) {
  expr->accept(*this);
}

void Visitor::visit(const StatementNode *stmt) {
  stmt->accept(*this);
}

void Visitor::visitExpressionStatementNode(const ExpressionStatementNode *node) {
  visit(node->expr);
}

void Visitor::visitDoubleNode(const DoubleNode *node) {
  return;
}

void Visitor::visitNumberNode(const NumberNode *node) {
  return;
}

void Visitor::visitStringNode(const StringNode *node) {
  return;
}

void Visitor::visitVariableNode(const VariableNode *node) {
  return;
}

void Visitor::visitBinaryOpNode(const BinaryOpNode *node) {
  visit(node->left);
  visit(node->right);
}

void Visitor::visitUnaryOpNode(const UnaryOpNode *node) {
  visit(node->right);
}

void Visitor::visitPrintNode(const PrintNode *node) {
  visit(node->expression);
}

void Visitor::visitAssignmentNode(const AssignmentNode *node) {
  visit(node->expression);
}

void Visitor::visitCreationNode(const CreationNode *node) {
  visit(node->expression);
}

void Visitor::visitIfNode(const IfNode *node) {
  visit(node->condition);
  visit(node->thenBlock);
  if (node->elseBlock) visit(node->elseBlock);
}

void Visitor::visitTernaryIfNode(const TernaryIfNode *node) {
  visit(node->condition);
  visit(node->thenExpr);
  visit(node->elseExpr);
}

void Visitor::visitBlockNode(const BlockNode *node) {
  for (auto stmt : node->statements) {
    visit(stmt);
  }
}

void Visitor::visitWhileNode(const WhileNode *node) {
  visit(node->condition);
  visit(node->block);
  if (node->step) visit(node->step);
}

void Visitor::visitFunctionDeclarationNode(const FunctionDeclarationNode *node) {
  visit(node->body);
}

void Visitor::visitFunctionCallNode(const FunctionCallNode *node) {
  if (node->callee) visit(node->callee);
  for (auto arg : node->arguments) {
    visit(arg);
  }
}

void Visitor::visitLambdaNode(const LambdaNode *node) {
  visit(node->body);
}

void Visitor::visitReturnNode(const ReturnNode *node) {
  visit(node->val);
}

void Visitor::visitBreakNode(const BreakNode *node) {
  return;
}

void Visitor::visitContinueNode(const ContinueNode *node) {
  return;
}
