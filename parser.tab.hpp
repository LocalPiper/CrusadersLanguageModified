/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUMBER = 258,                  /* NUMBER  */
    DOUBLE = 259,                  /* DOUBLE  */
    IDENTIFIER = 260,              /* IDENTIFIER  */
    STRING = 261,                  /* STRING  */
    PLUS = 262,                    /* PLUS  */
    MINUS = 263,                   /* MINUS  */
    STAR = 264,                    /* STAR  */
    SLASH = 265,                   /* SLASH  */
    MOD = 266,                     /* MOD  */
    OP = 267,                      /* OP  */
    CP = 268,                      /* CP  */
    EOL = 269,                     /* EOL  */
    PRINT = 270,                   /* PRINT  */
    ASSIGN = 271,                  /* ASSIGN  */
    VAR = 272,                     /* VAR  */
    EQ = 273,                      /* EQ  */
    LT = 274,                      /* LT  */
    GT = 275,                      /* GT  */
    LEQ = 276,                     /* LEQ  */
    GEQ = 277,                     /* GEQ  */
    NEQ = 278,                     /* NEQ  */
    AND = 279,                     /* AND  */
    OR = 280,                      /* OR  */
    NOT = 281,                     /* NOT  */
    TRUE = 282,                    /* TRUE  */
    FALSE = 283,                   /* FALSE  */
    IF = 284,                      /* IF  */
    ELSE = 285,                    /* ELSE  */
    OB = 286,                      /* OB  */
    CB = 287,                      /* CB  */
    WHILE = 288,                   /* WHILE  */
    FOR = 289,                     /* FOR  */
    BREAK = 290,                   /* BREAK  */
    CONTINUE = 291,                /* CONTINUE  */
    FUNCTION = 292,                /* FUNCTION  */
    LAMBDA = 293,                  /* LAMBDA  */
    COMMA = 294,                   /* COMMA  */
    RETURN = 295,                  /* RETURN  */
    QUESTION = 296,                /* QUESTION  */
    COLON = 297                    /* COLON  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 99 "parser.y"

  int num;
  double dnum;
  char* str;
  ExpressionNode* expr;
  StatementNode* stmt;
  BlockNode* blk;
  vector<string>* strList;
  vector<ExpressionNode*>* exprList;

#line 117 "parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */
