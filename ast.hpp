#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <variant>
#include <vector>

using namespace std;
using Value = std::variant<int, string>;

class ASTNode {
public:
  virtual ~ASTNode() = default;
  virtual Value evaluate() const = 0;
};

class NumberNode : public ASTNode {
public:
  int value;
  NumberNode(int val) : value(val) {}
  Value evaluate() const override { return value; }
};

class StringNode : public ASTNode {
public:
  string value;
  StringNode(string val) : value(val) {}
  Value evaluate() const override { return value; }
};

class VariableNode : public ASTNode {
public:
  string name;
  VariableNode(const string &n) : name(n) {}
  Value evaluate() const override;
};

class BinaryOpNode : public ASTNode {
public:
  string op;
  ASTNode *left;
  ASTNode *right;

  BinaryOpNode(const string &o, ASTNode *l, ASTNode *r)
      : op(o), left(l), right(r) {}

  Value evaluate() const override;
};

class UnaryOpNode : public ASTNode {
public:
  string op;
  ASTNode *right;

  UnaryOpNode(const string &o, ASTNode *r) : op(o), right(r) {}

  Value evaluate() const override;
};

class PrintNode : public ASTNode {
public:
  ASTNode *expression;
  PrintNode(ASTNode *expr) : expression(expr) {}
  Value evaluate() const override;
};

class AssignmentNode : public ASTNode {
public:
  string name;
  ASTNode *expression;
  AssignmentNode(const string &n, ASTNode *expr) : name(n), expression(expr) {}
  Value evaluate() const override;
};

class CreationNode : public ASTNode {
public:
  string name;
  ASTNode *expression;
  CreationNode(const string &n, ASTNode *expr) : name(n), expression(expr) {}
  Value evaluate() const override;
};

class IfNode : public ASTNode {
public:
  ASTNode *condition;
  ASTNode *thenBlock;
  ASTNode *elseBlock;
  IfNode(ASTNode *cond, ASTNode *thenB, ASTNode *elseB = nullptr)
      : condition(cond), thenBlock(thenB), elseBlock(elseB) {}
  Value evaluate() const override;
};

class BlockNode : public ASTNode {
public:
  vector<ASTNode *> statements;
  void addStatement(ASTNode *stmt) { statements.push_back(stmt); }
  Value evaluate() const override;
};

class WhileNode : public ASTNode {
public:
  ASTNode *condition;
  ASTNode *block;
  WhileNode(ASTNode *cond, ASTNode *blk) : condition(cond), block(blk) {}
  Value evaluate() const override;
};

#endif // AST_HPP
