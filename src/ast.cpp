#include "ast.hpp"
#include "array.hpp"
#include "callable.hpp"
#include "environment.hpp"
#include "function.hpp"
#include "operations.hpp"
#include "semantic.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

Value VariableNode::evaluate() const { return getVar(name); }

Value BinaryOpNode::evaluate() const {
  Value lval = left->evaluate();
  if (op == "&&") {
    return isTruthy(lval) ? right->evaluate() : lval;
  }
  if (op == "||") {
    return isTruthy(lval) ? lval : right->evaluate();
  }
  Value rval = right->evaluate();
  return applyBinaryOp(op, lval, rval);
}

Value UnaryOpNode::evaluate() const {
  Value result = right->evaluate();
  return applyUnaryOp(op, result);
}

void PrintNode::evaluate() const {
  Value result = expression->evaluate();
  if (holds_alternative<int>(result)) {
    cout << "Milord proclaimeth: " << get<int>(result) << "!\n";
  } else if (holds_alternative<double>(result)) {
    cout << "Milord proclaimeth: " << get<double>(result) << "!\n";
  } else if (holds_alternative<string>(result)) {
    cout << "Milord proclaimeth: \"" << get<string>(result) << "\"!\n";
  }
}

Value AssignmentNode::evaluate() const {
  Value result = expression->evaluate();
  setVar(name, result);
  return result;
}

Value CreationNode::evaluate() const {
  Value result = expression->evaluate();
  createVar(name, result);
  return result;
}

void IfNode::evaluate() const {
  if (isTruthy(condition->evaluate())) {
    thenBlock->evaluate();
    return;
  } else if (elseBlock) {
    elseBlock->evaluate();
    return;
  }
}

Value TernaryIfNode::evaluate() const {
  if (isTruthy(condition->evaluate())) {
    return thenExpr->evaluate();
  }
  return elseExpr->evaluate();
}

void BlockNode::evaluate() const {
  enterScope();
  try {
    for (auto &statement : statements) {
      statement->evaluate();
    }
  } catch (...) {
    exitScope();
    throw;
  }
  exitScope();
}

void WhileNode::evaluate() const {
  while (isTruthy(condition->evaluate())) {
    try {
      block->evaluate();
      if (step != nullptr)
        step->evaluate();
    } catch (BreakException &) {
      break;
    } catch (ContinueException &) {
      if (step !=
          nullptr) // if for loop, we evaluate step and only then continue
        step->evaluate();
      continue;
    }
  }
}

void FunctionDeclarationNode::evaluate() const {
  createVar(name, make_shared<CrusaderFunction>(parameters, body));
}

Value FunctionCallNode::evaluate() const {
  vector<Value> argValues;
  for (auto *arg : arguments)
    argValues.push_back(arg->evaluate());

  Value calleeValue;
  if (callee) {
    calleeValue = callee->evaluate();
  } else {
    calleeValue = getVar(name);
  }

  if (auto func = get_if<shared_ptr<CrusaderCallable>>(&calleeValue)) {
    return (*func)->call(argValues);
  }

  if (auto str = get_if<string>(&calleeValue)) {
    auto wrapper = make_shared<StringWrapper>(name, *str);
    return wrapper->call(argValues);
  }
  throw runtime_error("Error: Tried to call a non-function value");
}

Value LambdaNode::evaluate() const {
  return make_shared<CrusaderFunction>(params, body);
}

void ReturnNode::evaluate() const {
  if (val == nullptr) {
    throw ReturnException(0);
  }
  throw ReturnException(val->evaluate());
}

void BreakNode::evaluate() const { throw BreakException(); }

void ContinueNode::evaluate() const { throw ContinueException(); }

void ExpressionStatementNode::accept(Visitor &v) const {
  v.visitExpressionStatementNode(this);
}

void DoubleNode::accept(Visitor &v) const { v.visitDoubleNode(this); }

void NumberNode::accept(Visitor &v) const { v.visitNumberNode(this); }

void StringNode::accept(Visitor &v) const { v.visitStringNode(this); }

void VariableNode::accept(Visitor &v) const { v.visitVariableNode(this); }

void BinaryOpNode::accept(Visitor &v) const { v.visitBinaryOpNode(this); }

void UnaryOpNode::accept(Visitor &v) const { v.visitUnaryOpNode(this); }

void PrintNode::accept(Visitor &v) const { v.visitPrintNode(this); }

void AssignmentNode::accept(Visitor &v) const { v.visitAssignmentNode(this); }

void CreationNode::accept(Visitor &v) const { v.visitCreationNode(this); }

void IfNode::accept(Visitor &v) const { v.visitIfNode(this); }

void TernaryIfNode::accept(Visitor &v) const { v.visitTernaryIfNode(this); }

void BlockNode::accept(Visitor &v) const { v.visitBlockNode(this); }

void WhileNode::accept(Visitor &v) const { v.visitWhileNode(this); }

void FunctionDeclarationNode::accept(Visitor &v) const {
  v.visitFunctionDeclarationNode(this);
}

void FunctionCallNode::accept(Visitor &v) const {
  v.visitFunctionCallNode(this);
}

void LambdaNode::accept(Visitor &v) const { v.visitLambdaNode(this); }

void ReturnNode::accept(Visitor &v) const { v.visitReturnNode(this); }

void BreakNode::accept(Visitor &v) const { v.visitBreakNode(this); }

void ContinueNode::accept(Visitor &v) const { v.visitContinueNode(this); }
