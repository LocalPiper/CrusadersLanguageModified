%{
#include <iostream>
#include <unordered_map>
#include <vector>
#include "ast.hpp"
using namespace std;

int yylex();

void yyerror(const char* s) {
  cerr << "Error: " << s << endl;
}

extern char* yytext;


ASTNode* root = nullptr;

%}

%union {
  int num;
  char* str;
  ASTNode *node;
}

%token <num> NUMBER
%token <str> IDENTIFIER STRING
%token PLUS MINUS STAR SLASH OP CP EOL PRINT ASSIGN VAR
%token EQ LT GT LEQ GEQ NEQ AND OR NOT TRUE FALSE
%token IF ELSE OB CB WHILE
%type <node> program statements statement expression_statement print_statement
%type <node> expression assignment logical_or logical_and equalty comparison term factor unary primary
%type <node> if_statement block while_statement

%nonassoc IF
%nonassoc ELSE
%%

program:
       statements { root = $1; }
       ;

statements:
          statement statements { 
            $$ = new BlockNode(); 
            dynamic_cast<BlockNode*>($$)->addStatement($1); 
            dynamic_cast<BlockNode*>($$)->addStatement($2); 
          }
          | statement { 
            $$ = new BlockNode(); 
            dynamic_cast<BlockNode*>($$)->addStatement($1); 
          }
          ;

statement:
         print_statement EOL { $$ = $1; }
         | expression_statement EOL { $$ = $1; }
         | if_statement { $$ = $1; }
         | while_statement { $$ = $1; }
         | block { $$ = $1; }
         ;

block:
     OB EOL statements CB EOL { $$ = $3; }
     ;

print_statement:
               PRINT expression { $$ = new PrintNode($2); }
               ;

expression_statement:
                    expression { $$ = $1; }
                    ;


if_statement:
            IF OP expression CP block ELSE block { $$ = new IfNode($3, $5, $7); }
            | IF OP expression CP block { $$ = new IfNode($3, $5, nullptr); }
            ;

while_statement:
               WHILE OP expression CP block { $$ = new WhileNode($3, $5); }

expression:
          assignment { $$ = $1; }
          ;

assignment:
          IDENTIFIER ASSIGN assignment { $$ = new AssignmentNode($1, $3); }
          | VAR IDENTIFIER ASSIGN assignment { $$ = new CreationNode($2, $4); }
          | logical_or { $$ = $1; }
          ;

logical_or:
          logical_and OR logical_and { $$ = new BinaryOpNode("||", $1, $3); }
          | logical_and { $$ = $1; }
          ;

logical_and:
           equalty AND equalty { $$ = new BinaryOpNode("&&", $1, $3); }
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
       | IDENTIFIER { $$ = new VariableNode($1); }
       | STRING { $$ = new StringNode($1); }
       | OP expression CP { $$ = $2; }
       ;

%%


int main() {
    if (yyparse() == 0 && root) {
      root->evaluate();
    }
    return 0;
}

