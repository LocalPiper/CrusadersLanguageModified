%{
#include <iostream>
#include <unordered_map>
#include <vector>
#include "ast.hpp"
#include "builtin.hpp"
#include "environment.hpp"
using namespace std;

int yylex();

void yyerror(const char* s) {
  cerr << "Error: " << s << endl;
}

extern char* yytext;


ASTNode* root = nullptr;


// how to desugar 'forEach' into 'while'
// here is how it looks in normal state:
// for (var x : arr) {
//    ...
// }
// here is how it looks in desugared state:
// {
//    var __iterable = arr;
//    var __index = 0;
//    while (__index < size(__iterable)) {
//      var x = __iterable(__index);
//      ...
//      __index = __index + 1;
//    }
// }

StatementNode* desugarForEach(const std::string &varName, ExpressionNode *collection, BlockNode *body) {
  BlockNode* outer = new BlockNode();
  // var __iterable = collection
  outer->addStatement(new ExpressionStatementNode(new CreationNode("__iterable", collection)));
  // var __index = 0;
  outer->addStatement(new ExpressionStatementNode(new CreationNode("__index", new NumberNode(0))));
  // __index < size(__iterable)
  ExpressionNode* condition = new BinaryOpNode(
    "<",
    new VariableNode("__index"),
    new FunctionCallNode("size", { new VariableNode("__iterable") })
  );
  BlockNode* whileBody = new BlockNode();

  // var varName = __iterable(__index)
  whileBody->addStatement(new ExpressionStatementNode(new CreationNode(
              varName, 
              new FunctionCallNode(
                new VariableNode("__iterable"), 
                { new VariableNode("__index") }
              )
          )));
  for (auto stmt : body->statements) whileBody->addStatement(stmt);

  // __index = __index + 1
  whileBody->addStatement(new ExpressionStatementNode(
    new AssignmentNode(
      "__index",
      new BinaryOpNode("+", new VariableNode("__index"), new NumberNode(1))
    )
  ));

  outer->addStatement(new WhileNode(condition, whileBody));
  
  return outer;
}

%}

%union {
  int num;
  double dnum;
  char* str;
  ExpressionNode* expr;
  StatementNode* stmt;
  BlockNode* blk;
  vector<string>* strList;
  vector<ExpressionNode*>* exprList;
}

%token <num> NUMBER
%token <dnum> DOUBLE
%token <str> IDENTIFIER STRING
%token PLUS MINUS STAR SLASH MOD OP CP EOL PRINT ASSIGN VAR
%token EQ LT GT LEQ GEQ NEQ AND OR NOT TRUE FALSE
%token IF ELSE OB CB WHILE FOR BREAK CONTINUE FUNCTION COMMA RETURN QUESTION COLON
%type <stmt> program
%type <stmt> if_statement while_statement for_statement statement expression_statement print_statement function_declaration return_statement break_statement continue_statement
%type <expr> expression assignment logical_or logical_and equalty comparison term factor unary primary function_call
%type <blk> block statements
%type <strList> parameters
%type <exprList> arguments

%nonassoc IF
%nonassoc ELSE
%nonassoc RETURN

%start program
%%

program:
       statements { root = $1; }
       ;

statements:
          statement EOL statements { 
            $$ = new BlockNode();
            $$->addStatement($1);
            for (auto s : $3->statements) $$->addStatement(s);
            delete $3;
          }
          | statement EOL { 
            $$ = new BlockNode(); 
            $$->addStatement($1); 
          }
          | EOL statements { $$ = $2; }
          | EOL { $$ = new BlockNode(); }
          ;

statement:
         print_statement
         | expression_statement
         | if_statement
         | while_statement
         | for_statement
         | break_statement
         | continue_statement
         | block { $$ = $1; }
         | function_declaration
         | return_statement
         ;

function_declaration:
                    FUNCTION IDENTIFIER OP parameters CP block {
                    $$ = new FunctionDeclarationNode($2, *$4, $6);
                    delete $4;
                    }
                    ;

return_statement:
                RETURN expression { $$ = new ReturnNode($2); }
                | RETURN { $$ = new ReturnNode(); }
                ;

parameters:
          IDENTIFIER { $$ = new vector<string>({ $1 }); }
          | IDENTIFIER COMMA parameters {
            $$ = new vector<string>(*($3));
            $$->insert($$->begin(), $1);
            delete $3;
          }
          | /* empty */ { $$ = new vector<string>(); }
          ;

block:
     OB statements CB { $$ = $2; }
     ;

print_statement:
               PRINT expression { $$ = new PrintNode($2); }
               ;

expression_statement:
                    expression { $$ = new ExpressionStatementNode($1); }
                    ;


if_statement:
            IF OP expression CP block ELSE block { $$ = new IfNode($3, $5, $7); }
            | IF OP expression CP block { $$ = new IfNode($3, $5, nullptr); }
            ;

while_statement:
               WHILE OP expression CP block { $$ = new WhileNode($3, $5); }
               ;

for_statement:
             FOR OP expression COMMA expression COMMA expression CP block {
                BlockNode* body = $9;
                BlockNode* loop = new BlockNode();
                loop->addStatement(new ExpressionStatementNode($3));
                loop->addStatement(new WhileNode($5, body, $7));
                $$ = loop;
             }
             | FOR OP VAR IDENTIFIER COLON expression CP block {
                $$ = desugarForEach($4, $6, $8);
             } 
             ;

break_statement:
               BREAK { $$ = new BreakNode(); }
               ;

continue_statement:
                  CONTINUE { $$ = new ContinueNode(); }
                  ;

expression:
          assignment QUESTION expression ELSE expression { $$ = new TernaryIfNode($1, $3, $5); }
          | assignment { $$ = $1; }
          ;

assignment:
          IDENTIFIER ASSIGN assignment { $$ = new AssignmentNode($1, $3); }
          | VAR IDENTIFIER ASSIGN assignment { $$ = new CreationNode($2, $4); }
          | logical_or { $$ = $1; }
          ;

logical_or:
          logical_or OR logical_and { $$ = new BinaryOpNode("||", $1, $3); }
          | logical_and { $$ = $1; }
          ;

logical_and:
           logical_and AND equalty { $$ = new BinaryOpNode("&&", $1, $3); }
           | equalty { $$ = $1; }
           ;

equalty:
       comparison EQ comparison { $$ = new BinaryOpNode("==", $1, $3); }
       | comparison NEQ comparison { $$ = new BinaryOpNode("!=", $1, $3); }
       | comparison { $$ = $1; }
       ;

comparison:
          term LT term { $$ = new BinaryOpNode("<", $1, $3); }
          | term GT term { $$ = new BinaryOpNode(">", $1, $3); }
          | term GEQ term { $$ = new BinaryOpNode(">=",$1, $3); }
          | term LEQ term { $$ = new BinaryOpNode("<=",$1, $3); }
          | term { $$ = $1; }
          ;

term:
    term PLUS factor { $$ = new BinaryOpNode("+", $1, $3); }
    | term MINUS factor { $$ = new BinaryOpNode("-", $1, $3); }
    | factor { $$ = $1; }
    ;

factor:
      factor STAR unary { $$ = new BinaryOpNode("*", $1, $3); }
      | factor SLASH unary { $$ = new BinaryOpNode("/", $1, $3); }
      | factor MOD unary { $$ = new BinaryOpNode("%", $1, $3); }
      | unary { $$ = $1; }
      ;

unary:
     MINUS unary { $$ = new UnaryOpNode("-", $2); }
     | NOT unary { $$ = new UnaryOpNode("!", $2); }
     | primary { $$ = $1; }
     ;

primary:
       FALSE { $$ = new NumberNode(0); }
       | TRUE { $$ = new NumberNode(1); }
       | NUMBER { $$ = new NumberNode($1); }
       | DOUBLE { $$ = new DoubleNode($1); }
       | IDENTIFIER { $$ = new VariableNode($1); }
       | STRING { $$ = new StringNode($1); }
       | OP expression CP { $$ = $2; }
       | function_call { $$ = $1; };
       ;

function_call:
             function_call OP arguments CP {
              $$ = new FunctionCallNode($1, *$3);
              delete $3;
             }
             | IDENTIFIER OP arguments CP {
             $$ = new FunctionCallNode($1, *$3);
             delete $3;
             }
             ;

arguments:
         expression { $$ = new vector<ExpressionNode*>({ $1 });}
         | expression COMMA arguments {
          $$ = new vector<ExpressionNode*>(*($3));
          $$->insert($$->begin(), $1);
          delete $3;
         }
         | /* empty */ { $$ = new vector<ExpressionNode*>(); }
         ;

%%


int main() {
    if (yyparse() == 0 && root) {
      enterScope();
      initialize_builtins();
      dynamic_cast<StatementNode*>(root)->evaluate();
      exitScope();
    }
    return 0;
}

