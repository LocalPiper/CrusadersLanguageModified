#include "semantic.hpp"
#include "ast.hpp"
#include <stdexcept>

using namespace std;

bool Visitor::checkScope(const char c) {
  for (auto it = scopeType.rbegin(); it != scopeType.rend(); --it) {
    if ((*it) == c) return true;
  }
  return false;
}

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
  scopeType.push_back('I');
  visit(node->condition);
  visit(node->thenBlock);
  if (node->elseBlock) visit(node->elseBlock);
  scopeType.pop_back();
}

void Visitor::visitTernaryIfNode(const TernaryIfNode *node) {
  scopeType.push_back('I');
  visit(node->condition);
  visit(node->thenExpr);
  visit(node->elseExpr);
  scopeType.pop_back();
}

void Visitor::visitBlockNode(const BlockNode *node) {
  for (auto stmt : node->statements) {
    visit(stmt);
  }
}

void Visitor::visitWhileNode(const WhileNode *node) {
  scopeType.push_back('W');
  visit(node->condition);
  visit(node->block);
  if (node->step) visit(node->step);
  scopeType.pop_back();
}

void Visitor::visitFunctionDeclarationNode(const FunctionDeclarationNode *node) {
  if (checkScope('I') || checkScope('W') || checkScope('L')) throw runtime_error("Error: function can only be declared outside or inside another non-lambda function");
  scopeType.push_back('F');
  visit(node->body);
  scopeType.pop_back();
}

void Visitor::visitFunctionCallNode(const FunctionCallNode *node) {
  if (node->callee) visit(node->callee);
  for (auto arg : node->arguments) {
    visit(arg);
  }
}

void Visitor::visitLambdaNode(const LambdaNode *node) {
  scopeType.push_back('L');
  visit(node->body);
  scopeType.pop_back();
}

void Visitor::visitReturnNode(const ReturnNode *node) {
  if (!checkScope('F') && !checkScope('L')) throw runtime_error("Error: return outside function declaration");
  visit(node->val);
}

void Visitor::visitBreakNode(const BreakNode *node) {
  if (!checkScope('W')) throw runtime_error("Error: break outside loop");
  return;
}

void Visitor::visitContinueNode(const ContinueNode *node) {
  if (!checkScope('W')) throw runtime_error("Error: continue outside loop");
  return;
}
