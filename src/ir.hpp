#ifndef IR_HPP
#define IR_HPP
#include "ir_struct.hpp"
#include "semantic.hpp"

class ExpressionNode;
class StatementNode;
class ExpressionStatementNode;
class DoubleNode;
class NumberNode;
class StringNode;
class VariableNode;
class BinaryOpNode;
class UnaryOpNode;
class PrintNode;
class AssignmentNode;
class CreationNode;
class IfNode;
class TernaryIfNode;
class BlockNode;
class WhileNode;
class FunctionDeclarationNode;
class FunctionCallNode;
class LambdaNode;
class ReturnNode;
class BreakNode;
class ContinueNode;

class IRGenerator : public Visitor {
public:
  IR code;
  int tempCounter = 0;
  int labelCounter = 0;
  std::string lastValue;

  std::string newTemp();
  std::string newLabel();

  void visit(const ExpressionNode *expr) override;
  void visit(const StatementNode *stmt) override;

  void
  visitExpressionStatementNode(const ExpressionStatementNode *node) override;
  void visitDoubleNode(const DoubleNode *node) override;
  void visitNumberNode(const NumberNode *node) override;
  void visitStringNode(const StringNode *node) override;
  void visitVariableNode(const VariableNode *node) override;
  void visitBinaryOpNode(const BinaryOpNode *node) override;
  void visitUnaryOpNode(const UnaryOpNode *node) override;
  void visitPrintNode(const PrintNode *node) override;
  void visitAssignmentNode(const AssignmentNode *node) override;
  void visitCreationNode(const CreationNode *node) override;
  void visitIfNode(const IfNode *node) override;
  void visitTernaryIfNode(const TernaryIfNode *node) override;
  void visitBlockNode(const BlockNode *node) override;
  void visitWhileNode(const WhileNode *node) override;
  void
  visitFunctionDeclarationNode(const FunctionDeclarationNode *node) override;
  void visitFunctionCallNode(const FunctionCallNode *node) override;
  void visitLambdaNode(const LambdaNode *node) override;
  void visitReturnNode(const ReturnNode *node) override;
  void visitBreakNode(const BreakNode *node) override;
  void visitContinueNode(const ContinueNode *node) override;
};

#endif // IR_HPP
