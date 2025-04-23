#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <variant>
#include <vector>

using namespace std;
using Value = std::variant<int, double, string>;

class ASTNode {
public:
  virtual ~ASTNode() = default;
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
};

class DoubleNode : public ExpressionNode {
public:
  double value;
  DoubleNode(double val) : value(val) {}
  Value evaluate() const override { return value; }
};

class NumberNode : public ExpressionNode {
public:
  int value;
  NumberNode(int val) : value(val) {}
  Value evaluate() const override { return value; }
};

class StringNode : public ExpressionNode {
public:
  string value;
  StringNode(string val) : value(val) {}
  Value evaluate() const override { return value; }
};

class VariableNode : public ExpressionNode {
public:
  string name;
  VariableNode(const string &n) : name(n) {}
  Value evaluate() const override;
};

class BinaryOpNode : public ExpressionNode {
public:
  string op;
  ExpressionNode *left;
  ExpressionNode *right;

  BinaryOpNode(const string &o, ExpressionNode *l, ExpressionNode *r)
      : op(o), left(l), right(r) {}

  Value evaluate() const override;
};

class UnaryOpNode : public ExpressionNode {
public:
  string op;
  ExpressionNode *right;

  UnaryOpNode(const string &o, ExpressionNode *r) : op(o), right(r) {}

  Value evaluate() const override;
};

class PrintNode : public StatementNode {
public:
  ExpressionNode *expression;
  PrintNode(ExpressionNode *expr) : expression(expr) {}
  void evaluate() const override;
};

class AssignmentNode : public ExpressionNode {
public:
  string name;
  ExpressionNode *expression;
  AssignmentNode(const string &n, ExpressionNode *expr)
      : name(n), expression(expr) {}
  Value evaluate() const override;
};

class CreationNode : public ExpressionNode {
public:
  string name;
  ExpressionNode *expression;
  CreationNode(const string &n, ExpressionNode *expr)
      : name(n), expression(expr) {}
  Value evaluate() const override;
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
};

class BlockNode : public StatementNode {
public:
  vector<StatementNode *> statements;
  void addStatement(StatementNode *stmt) { statements.push_back(stmt); }
  void evaluate() const override;
};

class WhileNode : public StatementNode {
public:
  ExpressionNode *condition;
  StatementNode *block;
  WhileNode(ExpressionNode *cond, StatementNode *blk)
      : condition(cond), block(blk) {}
  void evaluate() const override;
};

#endif // AST_HPP
