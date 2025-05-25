#ifndef SEMANTIC_HPP
#define SEMANTIC_HPP
#include <string>

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

class Visitor {
public:
  std::string scopeType;
  virtual bool checkScope(const char c);

  virtual void visit(const ExpressionNode *expr);
  virtual void visit(const StatementNode *stmt);

  virtual void visitExpressionStatementNode(const ExpressionStatementNode *node);
  virtual void visitDoubleNode(const DoubleNode *node);
  virtual void visitNumberNode(const NumberNode *node);
  virtual void visitStringNode(const StringNode *node);
  virtual void visitVariableNode(const VariableNode *node);
  virtual void visitBinaryOpNode(const BinaryOpNode *node);
  virtual void visitUnaryOpNode(const UnaryOpNode *node);
  virtual void visitPrintNode(const PrintNode *node);
  virtual void visitAssignmentNode(const AssignmentNode *node);
  virtual void visitCreationNode(const CreationNode *node);
  virtual void visitIfNode(const IfNode *node);
  virtual void visitTernaryIfNode(const TernaryIfNode *node);
  virtual void visitBlockNode(const BlockNode *node);
  virtual void visitWhileNode(const WhileNode *node);
  virtual void visitFunctionDeclarationNode(const FunctionDeclarationNode *node);
  virtual void visitFunctionCallNode(const FunctionCallNode *node);
  virtual void visitLambdaNode(const LambdaNode *node);
  virtual void visitReturnNode(const ReturnNode *node);
  virtual void visitBreakNode(const BreakNode *node);
  virtual void visitContinueNode(const ContinueNode *node);
}; 
#endif // SEMANTIC_HPP 
