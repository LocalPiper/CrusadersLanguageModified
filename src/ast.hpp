#ifndef AST_HPP
#define AST_HPP

#include "value.hpp"
#include <string>
#include <vector>

using namespace std;

class Visitor;

class ASTNode {
public:
  virtual ~ASTNode() = default;
  virtual void accept(Visitor &v) const = 0;
};

class ExpressionNode : public ASTNode {
public:
  virtual Value evaluate() const = 0;
};

class StatementNode : public ASTNode {
public:
  virtual void evaluate() const = 0;
};

class ExpressionStatementNode : public StatementNode {
public:
  ExpressionNode *expr;
  ExpressionStatementNode(ExpressionNode *e) : expr(e) {}
  void evaluate() const override { expr->evaluate(); }
  void accept(Visitor &v) const override;
};

class DoubleNode : public ExpressionNode {
public:
  double value;
  DoubleNode(double val) : value(val) {}
  Value evaluate() const override { return value; }
  void accept(Visitor &v) const override;
};

class NumberNode : public ExpressionNode {
public:
  int value;
  NumberNode(int val) : value(val) {}
  Value evaluate() const override { return value; }
  void accept(Visitor &v) const override;
};

class StringNode : public ExpressionNode {
public:
  string value;
  StringNode(string val) : value(val) {}
  Value evaluate() const override { return value; }
  void accept(Visitor &v) const override;
};

class VariableNode : public ExpressionNode {
public:
  string name;
  VariableNode(const string &n) : name(n) {}
  Value evaluate() const override;
  void accept(Visitor &v) const override;
};

class BinaryOpNode : public ExpressionNode {
public:
  string op;
  ExpressionNode *left;
  ExpressionNode *right;

  BinaryOpNode(const string &o, ExpressionNode *l, ExpressionNode *r)
      : op(o), left(l), right(r) {}

  Value evaluate() const override;
  void accept(Visitor &v) const override;
};

class UnaryOpNode : public ExpressionNode {
public:
  string op;
  ExpressionNode *right;

  UnaryOpNode(const string &o, ExpressionNode *r) : op(o), right(r) {}

  Value evaluate() const override;
  void accept(Visitor &v) const override;
};

class PrintNode : public StatementNode {
public:
  ExpressionNode *expression;
  PrintNode(ExpressionNode *expr) : expression(expr) {}
  void evaluate() const override;
  void accept(Visitor &v) const override;
};

class AssignmentNode : public ExpressionNode {
public:
  string name;
  ExpressionNode *expression;
  AssignmentNode(const string &n, ExpressionNode *expr)
      : name(n), expression(expr) {}
  Value evaluate() const override;
  void accept(Visitor &v) const override;
};

class CreationNode : public ExpressionNode {
public:
  string name;
  ExpressionNode *expression;
  CreationNode(const string &n, ExpressionNode *expr)
      : name(n), expression(expr) {}
  Value evaluate() const override;
  void accept(Visitor &v) const override;
};

class IfNode : public StatementNode {
public:
  ExpressionNode *condition;
  StatementNode *thenBlock;
  StatementNode *elseBlock;
  IfNode(ExpressionNode *cond, StatementNode *thenB,
         StatementNode *elseB = nullptr)
      : condition(cond), thenBlock(thenB), elseBlock(elseB) {}
  void evaluate() const override;
  void accept(Visitor &v) const override;
};

class TernaryIfNode : public ExpressionNode {
public:
  ExpressionNode *condition;
  ExpressionNode *thenExpr;
  ExpressionNode *elseExpr;
  TernaryIfNode(ExpressionNode *cond, ExpressionNode *then, ExpressionNode *els)
      : condition(cond), thenExpr(then), elseExpr(els) {}
  Value evaluate() const override;
  void accept(Visitor &v) const override;
};

class BlockNode : public StatementNode {
public:
  vector<StatementNode *> statements;
  void addStatement(StatementNode *stmt) { statements.push_back(stmt); }
  void evaluate() const override;
  void accept(Visitor &v) const override;
};

class WhileNode : public StatementNode {
public:
  ExpressionNode *condition;
  StatementNode *block;
  ExpressionNode *step = nullptr; // a surprise tool that will help me later
  WhileNode(ExpressionNode *cond, StatementNode *blk)
      : condition(cond), block(blk) {}
  WhileNode(ExpressionNode *cond, StatementNode *blk, ExpressionNode *step)
      : condition(cond), block(blk), step(step) {}
  void evaluate() const override;
  void accept(Visitor &v) const override;
};

class FunctionDeclarationNode : public StatementNode {
public:
  string name;
  vector<string> parameters;
  BlockNode *body;
  FunctionDeclarationNode(const string &n, const vector<string> &params,
                          BlockNode *b)
      : name(n), parameters(params), body(b) {}
  void evaluate() const override;
  void accept(Visitor &v) const override;
};

class FunctionCallNode : public ExpressionNode {
public:
  string name;
  ExpressionNode *callee = nullptr;
  vector<ExpressionNode *> arguments;
  FunctionCallNode(const string &n, const vector<ExpressionNode *> &args)
      : name(n), arguments(args) {}
  FunctionCallNode(ExpressionNode *callee, const vector<ExpressionNode *> &args)
      : callee(callee), arguments(args) {}
  Value evaluate() const override;
  void accept(Visitor &v) const override;
};

class LambdaNode : public ExpressionNode {
  vector<string> params;

public:
  BlockNode *body;
  LambdaNode(vector<string> params, BlockNode *body)
      : params(std::move(params)), body(body) {}
  Value evaluate() const override;
  void accept(Visitor &v) const override;
};

class ReturnNode : public StatementNode {
public:
  ExpressionNode *val;
  ReturnNode() {}
  ReturnNode(ExpressionNode *val) : val(val) {}
  void evaluate() const override;
  void accept(Visitor &v) const override;
};

class BreakNode : public StatementNode {
public:
  void evaluate() const override;
  void accept(Visitor &v) const override;
};

class ContinueNode : public StatementNode {
public:
  void evaluate() const override;
  void accept(Visitor &v) const override;
};

#endif // AST_HPP
