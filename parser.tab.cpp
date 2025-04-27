/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "parser.y"

#include <iostream>
#include <unordered_map>
#include <vector>
#include "ast.hpp"
#include "builtin.hpp"
#include "environment.hpp"

extern int currentLine;  // Переменная для отслеживания текущей строки
extern char* yytext;     // Переменная для получения текста токена

using namespace std;

int yylex();

void yyerror(const char* s) {
  if (*yytext != '\n')
  cerr << "Error at line " << currentLine << ": "
       << s << " (before token: '" << yytext << "')" << endl;
}

ASTNode* root = nullptr;

// Распыление foreach в while
StatementNode* desugarForEach(const std::string &varName, ExpressionNode *collection, BlockNode *body) {
  BlockNode* outer = new BlockNode();
  // инициализация итератора и индекса
  outer->addStatement(new ExpressionStatementNode(
    new CreationNode("__iterable", collection)
  ));
  outer->addStatement(new ExpressionStatementNode(
    new CreationNode("__index", new NumberNode(0))
  ));

  ExpressionNode* condition = new BinaryOpNode(
    "<",
    new VariableNode("__index"),
    new FunctionCallNode("size", { new VariableNode("__iterable") })
  );

  BlockNode* whileBody = new BlockNode();
  // тело цикла: присвоение varName и вложенные statements
  whileBody->addStatement(new ExpressionStatementNode(
    new CreationNode(
      varName,
      new FunctionCallNode(
        new VariableNode("__iterable"),
        { new VariableNode("__index") }
      )
    )
  ));
  for (auto stmt : body->statements) whileBody->addStatement(stmt);
  // инкремент индекса
  whileBody->addStatement(new ExpressionStatementNode(
    new AssignmentNode(
      "__index",
      new BinaryOpNode(
        "+",
        new VariableNode("__index"),
        new NumberNode(1)
      )
    )
  ));

  outer->addStatement(new WhileNode(condition, whileBody));
  return outer;  // обязательно вернуть
}

#line 140 "parser.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUMBER = 3,                     /* NUMBER  */
  YYSYMBOL_DOUBLE = 4,                     /* DOUBLE  */
  YYSYMBOL_IDENTIFIER = 5,                 /* IDENTIFIER  */
  YYSYMBOL_STRING = 6,                     /* STRING  */
  YYSYMBOL_PLUS = 7,                       /* PLUS  */
  YYSYMBOL_MINUS = 8,                      /* MINUS  */
  YYSYMBOL_STAR = 9,                       /* STAR  */
  YYSYMBOL_SLASH = 10,                     /* SLASH  */
  YYSYMBOL_MOD = 11,                       /* MOD  */
  YYSYMBOL_OP = 12,                        /* OP  */
  YYSYMBOL_CP = 13,                        /* CP  */
  YYSYMBOL_EOL = 14,                       /* EOL  */
  YYSYMBOL_PRINT = 15,                     /* PRINT  */
  YYSYMBOL_ASSIGN = 16,                    /* ASSIGN  */
  YYSYMBOL_VAR = 17,                       /* VAR  */
  YYSYMBOL_EQ = 18,                        /* EQ  */
  YYSYMBOL_LT = 19,                        /* LT  */
  YYSYMBOL_GT = 20,                        /* GT  */
  YYSYMBOL_LEQ = 21,                       /* LEQ  */
  YYSYMBOL_GEQ = 22,                       /* GEQ  */
  YYSYMBOL_NEQ = 23,                       /* NEQ  */
  YYSYMBOL_AND = 24,                       /* AND  */
  YYSYMBOL_OR = 25,                        /* OR  */
  YYSYMBOL_NOT = 26,                       /* NOT  */
  YYSYMBOL_TRUE = 27,                      /* TRUE  */
  YYSYMBOL_FALSE = 28,                     /* FALSE  */
  YYSYMBOL_IF = 29,                        /* IF  */
  YYSYMBOL_ELSE = 30,                      /* ELSE  */
  YYSYMBOL_OB = 31,                        /* OB  */
  YYSYMBOL_CB = 32,                        /* CB  */
  YYSYMBOL_WHILE = 33,                     /* WHILE  */
  YYSYMBOL_FOR = 34,                       /* FOR  */
  YYSYMBOL_BREAK = 35,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 36,                  /* CONTINUE  */
  YYSYMBOL_FUNCTION = 37,                  /* FUNCTION  */
  YYSYMBOL_LAMBDA = 38,                    /* LAMBDA  */
  YYSYMBOL_COMMA = 39,                     /* COMMA  */
  YYSYMBOL_RETURN = 40,                    /* RETURN  */
  YYSYMBOL_QUESTION = 41,                  /* QUESTION  */
  YYSYMBOL_COLON = 42,                     /* COLON  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_program = 44,                   /* program  */
  YYSYMBOL_45_1 = 45,                      /* $@1  */
  YYSYMBOL_statements = 46,                /* statements  */
  YYSYMBOL_statement = 47,                 /* statement  */
  YYSYMBOL_block = 48,                     /* block  */
  YYSYMBOL_print_statement = 49,           /* print_statement  */
  YYSYMBOL_expression_statement = 50,      /* expression_statement  */
  YYSYMBOL_if_statement = 51,              /* if_statement  */
  YYSYMBOL_while_statement = 52,           /* while_statement  */
  YYSYMBOL_for_statement = 53,             /* for_statement  */
  YYSYMBOL_break_statement = 54,           /* break_statement  */
  YYSYMBOL_continue_statement = 55,        /* continue_statement  */
  YYSYMBOL_function_declaration = 56,      /* function_declaration  */
  YYSYMBOL_return_statement = 57,          /* return_statement  */
  YYSYMBOL_expression = 58,                /* expression  */
  YYSYMBOL_assignment = 59,                /* assignment  */
  YYSYMBOL_logical_or = 60,                /* logical_or  */
  YYSYMBOL_logical_and = 61,               /* logical_and  */
  YYSYMBOL_equalty = 62,                   /* equalty  */
  YYSYMBOL_comparison = 63,                /* comparison  */
  YYSYMBOL_term = 64,                      /* term  */
  YYSYMBOL_factor = 65,                    /* factor  */
  YYSYMBOL_unary = 66,                     /* unary  */
  YYSYMBOL_primary = 67,                   /* primary  */
  YYSYMBOL_function_call = 68,             /* function_call  */
  YYSYMBOL_arguments = 69,                 /* arguments  */
  YYSYMBOL_parameters = 70,                /* parameters  */
  YYSYMBOL_lambda = 71                     /* lambda  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  63
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   275

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  147

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   104,   104,   105,   105,   113,   117,   122,   126,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   145,
     148,   156,   160,   164,   165,   169,   173,   180,   186,   190,
     194,   201,   202,   206,   207,   211,   212,   213,   217,   218,
     222,   223,   227,   228,   229,   233,   234,   235,   236,   237,
     241,   242,   243,   247,   248,   249,   250,   254,   255,   256,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   272,
     273,   277,   278,   279,   283,   284,   285,   289
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER", "DOUBLE",
  "IDENTIFIER", "STRING", "PLUS", "MINUS", "STAR", "SLASH", "MOD", "OP",
  "CP", "EOL", "PRINT", "ASSIGN", "VAR", "EQ", "LT", "GT", "LEQ", "GEQ",
  "NEQ", "AND", "OR", "NOT", "TRUE", "FALSE", "IF", "ELSE", "OB", "CB",
  "WHILE", "FOR", "BREAK", "CONTINUE", "FUNCTION", "LAMBDA", "COMMA",
  "RETURN", "QUESTION", "COLON", "$accept", "program", "$@1", "statements",
  "statement", "block", "print_statement", "expression_statement",
  "if_statement", "while_statement", "for_statement", "break_statement",
  "continue_statement", "function_declaration", "return_statement",
  "expression", "assignment", "logical_or", "logical_and", "equalty",
  "comparison", "term", "factor", "unary", "primary", "function_call",
  "arguments", "parameters", "lambda", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-81)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     199,   -81,   -81,     0,   -81,   237,     1,   -81,     1,    14,
     237,   -81,   -81,    34,   123,    36,    39,   -81,   -81,    21,
      48,     1,    54,    30,    18,   -81,   -81,   -81,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,    28,    60,    70,   -81,
       2,    92,    62,   -81,   -81,    90,   -81,     1,     1,    91,
     -81,    94,   -81,   101,   -81,     1,    76,   161,     1,    78,
      98,   113,   -81,   -81,   105,   107,   108,   -81,     1,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,     1,    84,   117,   -81,   -81,     1,   119,   -81,
     -81,   121,   131,   100,   113,   102,   129,   -81,   -81,   -81,
     114,    70,   -81,   -81,   -81,    62,    62,    80,    80,    80,
      80,   -81,   -81,   -81,   130,     1,   -81,   -81,   115,   115,
      -5,     1,   132,   113,   115,   -81,     1,   -81,   -81,   118,
     -81,     1,   116,   115,   -81,   -81,   -81,   115,   134,     1,
     -81,   -81,   115,   140,   -81,   115,   -81
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    62,    63,    64,    65,     0,     0,     8,     0,     0,
       0,    61,    60,     0,     0,     0,     0,    28,    29,     0,
       0,    32,     0,     0,     0,    16,     9,    10,    11,    12,
      13,    14,    15,    17,    18,    22,    34,    37,    39,    41,
      44,    49,    52,    56,    59,    67,    68,    73,     0,    64,
      57,     0,    21,     0,    58,     0,     0,     0,     0,     0,
       0,    76,    31,     1,     0,     0,     0,     7,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    73,    71,     0,    35,    66,     0,     0,    20,
      19,     0,     0,     0,    76,    74,     0,     3,     6,     5,
       0,    38,    40,    42,    43,    50,    51,    45,    46,    48,
      47,    53,    54,    55,     0,    73,    70,    36,     0,     0,
       0,     0,     0,    76,     0,     4,     0,    69,    72,    24,
      25,     0,     0,     0,    75,    77,    33,     0,     0,     0,
      30,    23,     0,     0,    27,     0,    26
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -81,   -81,   -81,   154,   -13,   -44,   -81,   -81,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,    -6,   -47,   -81,   103,   104,
      20,   -54,    23,    -2,   -81,   -81,   -65,   -80,   -81
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    22,   125,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    84,    96,    46
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,    85,    52,    50,     1,     2,     3,     4,    54,     5,
      66,    87,    47,     6,   122,    62,    48,   114,     9,    53,
      71,   107,   108,   109,   110,    72,    60,    10,    11,    12,
      -2,    65,    67,     1,     2,     3,     4,   131,     5,    20,
     117,    83,     6,   134,    66,     8,    55,     9,    58,    88,
     128,    59,    91,    93,    63,    64,    10,    11,    12,    13,
      61,    14,   100,    15,    16,    17,    18,    19,    20,    68,
      21,    79,    80,    81,   129,   130,    83,   111,   112,   113,
     135,     1,     2,     3,     4,    69,     5,    73,    74,   140,
       6,   103,   104,   141,    70,    92,   105,   106,   144,    73,
      74,   146,    82,    47,    10,    11,    12,    86,    89,    83,
      94,    75,    76,    77,    78,   132,    20,    87,    95,    97,
     136,    98,    99,   115,    56,   138,     1,     2,     3,     4,
     116,     5,   118,   143,   119,     6,   120,     7,     8,   121,
       9,   123,   124,   127,   126,   133,    14,   142,   137,    10,
      11,    12,    13,   145,    14,   139,    15,    16,    17,    18,
      19,    20,    65,    21,     1,     2,     3,     4,    57,     5,
       0,     0,   101,     6,   102,     0,     8,     0,     9,     0,
       0,     0,     0,     0,     0,     0,     0,    10,    11,    12,
      13,     0,    14,    90,    15,    16,    17,    18,    19,    20,
       0,    21,     1,     2,     3,     4,     0,     5,     0,     0,
       0,     6,     0,     7,     8,     0,     9,     0,     0,     0,
       0,     0,     0,     0,     0,    10,    11,    12,    13,     0,
      14,     0,    15,    16,    17,    18,    19,    20,     0,    21,
       1,     2,    49,     4,     0,     5,     0,     0,     0,     6,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    10,    11,    12,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    20
};

static const yytype_int16 yycheck[] =
{
       6,    48,     8,     5,     3,     4,     5,     6,    10,     8,
      23,    16,    12,    12,    94,    21,    16,    82,    17,     5,
      18,    75,    76,    77,    78,    23,     5,    26,    27,    28,
       0,     1,    14,     3,     4,     5,     6,    42,     8,    38,
      87,    47,    12,   123,    57,    15,    12,    17,    12,    55,
     115,    12,    58,    59,     0,     1,    26,    27,    28,    29,
      12,    31,    68,    33,    34,    35,    36,    37,    38,    41,
      40,     9,    10,    11,   118,   119,    82,    79,    80,    81,
     124,     3,     4,     5,     6,    25,     8,     7,     8,   133,
      12,    71,    72,   137,    24,    17,    73,    74,   142,     7,
       8,   145,    12,    12,    26,    27,    28,    13,    32,   115,
      12,    19,    20,    21,    22,   121,    38,    16,     5,    14,
     126,    14,    14,    39,     1,   131,     3,     4,     5,     6,
      13,     8,    13,   139,    13,    12,     5,    14,    15,    39,
      17,    39,    13,    13,    30,    13,    31,    13,    30,    26,
      27,    28,    29,    13,    31,    39,    33,    34,    35,    36,
      37,    38,     1,    40,     3,     4,     5,     6,    14,     8,
      -1,    -1,    69,    12,    70,    -1,    15,    -1,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    -1,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    40,     3,     4,     5,     6,    -1,     8,    -1,    -1,
      -1,    12,    -1,    14,    15,    -1,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,    -1,
      31,    -1,    33,    34,    35,    36,    37,    38,    -1,    40,
       3,     4,     5,     6,    -1,     8,    -1,    -1,    -1,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     8,    12,    14,    15,    17,
      26,    27,    28,    29,    31,    33,    34,    35,    36,    37,
      38,    40,    44,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    71,    12,    16,     5,
      66,    58,    58,     5,    66,    12,     1,    46,    12,    12,
       5,    12,    58,     0,     1,     1,    47,    14,    41,    25,
      24,    18,    23,     7,     8,    19,    20,    21,    22,     9,
      10,    11,    12,    58,    69,    59,    13,    16,    58,    32,
      32,    58,    17,    58,    12,     5,    70,    14,    14,    14,
      58,    61,    62,    63,    63,    65,    65,    64,    64,    64,
      64,    66,    66,    66,    69,    39,    13,    59,    13,    13,
       5,    39,    70,    39,    13,    45,    30,    13,    69,    48,
      48,    42,    58,    13,    70,    48,    58,    30,    58,    39,
      48,    48,    13,    58,    48,    13,    48
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    45,    44,    46,    46,    46,    46,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    48,
      48,    49,    50,    51,    51,    52,    53,    53,    54,    55,
      56,    57,    57,    58,    58,    59,    59,    59,    60,    60,
      61,    61,    62,    62,    62,    63,    63,    63,    63,    63,
      64,    64,    64,    65,    65,    65,    65,    66,    66,    66,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    68,
      68,    69,    69,    69,    70,    70,    70,    71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     4,     3,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     2,     1,     7,     5,     5,     9,     8,     1,     1,
       6,     2,     1,     5,     1,     3,     4,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     1,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     4,
       4,     1,     3,     0,     1,     3,     0,     5
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3: /* $@1: %empty  */
#line 105 "parser.y"
                        {
        yyerror("syntax error in program, skipping to end of line");
        yyerrok; yyclearin;
      }
#line 1592 "parser.tab.cpp"
    break;

  case 4: /* program: program error EOL $@1  */
#line 109 "parser.y"
    { root = (yyvsp[-3].blk); }
#line 1598 "parser.tab.cpp"
    break;

  case 5: /* statements: statements statement EOL  */
#line 113 "parser.y"
                               {
        (yyval.blk) = (yyvsp[-2].blk);
        (yyval.blk)->addStatement((yyvsp[-1].stmt));
      }
#line 1607 "parser.tab.cpp"
    break;

  case 6: /* statements: statements error EOL  */
#line 117 "parser.y"
                           {
        yyerror("syntax error in statements, skipping to end of line");
        yyerrok; yyclearin;
        (yyval.blk) = (yyvsp[-2].blk);
      }
#line 1617 "parser.tab.cpp"
    break;

  case 7: /* statements: statement EOL  */
#line 122 "parser.y"
                    {
        (yyval.blk) = new BlockNode();
        (yyval.blk)->addStatement((yyvsp[-1].stmt));
      }
#line 1626 "parser.tab.cpp"
    break;

  case 8: /* statements: EOL  */
#line 126 "parser.y"
          {
        (yyval.blk) = new BlockNode();
      }
#line 1634 "parser.tab.cpp"
    break;

  case 16: /* statement: block  */
#line 139 "parser.y"
                          { (yyval.stmt) = (yyvsp[0].blk); }
#line 1640 "parser.tab.cpp"
    break;

  case 19: /* block: OB statements CB  */
#line 145 "parser.y"
                       {
        (yyval.blk) = (yyvsp[-1].blk);
      }
#line 1648 "parser.tab.cpp"
    break;

  case 20: /* block: OB error CB  */
#line 148 "parser.y"
                  {
        yyerror("syntax error in block, skipping to closing brace");
        yyerrok; yyclearin;
        (yyval.blk) = new BlockNode();
      }
#line 1658 "parser.tab.cpp"
    break;

  case 21: /* print_statement: PRINT expression  */
#line 156 "parser.y"
                       { (yyval.stmt) = new PrintNode((yyvsp[0].expr)); }
#line 1664 "parser.tab.cpp"
    break;

  case 22: /* expression_statement: expression  */
#line 160 "parser.y"
                 { (yyval.stmt) = new ExpressionStatementNode((yyvsp[0].expr)); }
#line 1670 "parser.tab.cpp"
    break;

  case 23: /* if_statement: IF OP expression CP block ELSE block  */
#line 164 "parser.y"
                                           { (yyval.stmt) = new IfNode((yyvsp[-4].expr), (yyvsp[-2].blk), (yyvsp[0].blk)); }
#line 1676 "parser.tab.cpp"
    break;

  case 24: /* if_statement: IF OP expression CP block  */
#line 165 "parser.y"
                                             { (yyval.stmt) = new IfNode((yyvsp[-2].expr), (yyvsp[0].blk), nullptr); }
#line 1682 "parser.tab.cpp"
    break;

  case 25: /* while_statement: WHILE OP expression CP block  */
#line 169 "parser.y"
                                   { (yyval.stmt) = new WhileNode((yyvsp[-2].expr), (yyvsp[0].blk)); }
#line 1688 "parser.tab.cpp"
    break;

  case 26: /* for_statement: FOR OP expression COMMA expression COMMA expression CP block  */
#line 173 "parser.y"
                                                                   {
        BlockNode* body = (yyvsp[0].blk);
        BlockNode* loop = new BlockNode();
        loop->addStatement(new ExpressionStatementNode((yyvsp[-6].expr)));
        loop->addStatement(new WhileNode((yyvsp[-4].expr), body, (yyvsp[-2].expr)));
        (yyval.stmt) = loop;
      }
#line 1700 "parser.tab.cpp"
    break;

  case 27: /* for_statement: FOR OP VAR IDENTIFIER COLON expression CP block  */
#line 180 "parser.y"
                                                      {
        (yyval.stmt) = desugarForEach((yyvsp[-4].str), (yyvsp[-2].expr), (yyvsp[0].blk));
      }
#line 1708 "parser.tab.cpp"
    break;

  case 28: /* break_statement: BREAK  */
#line 186 "parser.y"
            { (yyval.stmt) = new BreakNode(); }
#line 1714 "parser.tab.cpp"
    break;

  case 29: /* continue_statement: CONTINUE  */
#line 190 "parser.y"
               { (yyval.stmt) = new ContinueNode(); }
#line 1720 "parser.tab.cpp"
    break;

  case 30: /* function_declaration: FUNCTION IDENTIFIER OP parameters CP block  */
#line 194 "parser.y"
                                                 {
        (yyval.stmt) = new FunctionDeclarationNode((yyvsp[-4].str), *(yyvsp[-2].strList), (yyvsp[0].blk));
        delete (yyvsp[-2].strList);
      }
#line 1729 "parser.tab.cpp"
    break;

  case 31: /* return_statement: RETURN expression  */
#line 201 "parser.y"
                        { (yyval.stmt) = new ReturnNode((yyvsp[0].expr)); }
#line 1735 "parser.tab.cpp"
    break;

  case 32: /* return_statement: RETURN  */
#line 202 "parser.y"
                        { (yyval.stmt) = new ReturnNode(); }
#line 1741 "parser.tab.cpp"
    break;

  case 33: /* expression: assignment QUESTION expression ELSE expression  */
#line 206 "parser.y"
                                                     { (yyval.expr) = new TernaryIfNode((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1747 "parser.tab.cpp"
    break;

  case 34: /* expression: assignment  */
#line 207 "parser.y"
                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1753 "parser.tab.cpp"
    break;

  case 35: /* assignment: IDENTIFIER ASSIGN assignment  */
#line 211 "parser.y"
                                        { (yyval.expr) = new AssignmentNode((yyvsp[-2].str), (yyvsp[0].expr)); }
#line 1759 "parser.tab.cpp"
    break;

  case 36: /* assignment: VAR IDENTIFIER ASSIGN assignment  */
#line 212 "parser.y"
                                        { (yyval.expr) = new CreationNode((yyvsp[-2].str), (yyvsp[0].expr)); }
#line 1765 "parser.tab.cpp"
    break;

  case 37: /* assignment: logical_or  */
#line 213 "parser.y"
                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 1771 "parser.tab.cpp"
    break;

  case 38: /* logical_or: logical_or OR logical_and  */
#line 217 "parser.y"
                                        { (yyval.expr) = new BinaryOpNode("||", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1777 "parser.tab.cpp"
    break;

  case 39: /* logical_or: logical_and  */
#line 218 "parser.y"
                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 1783 "parser.tab.cpp"
    break;

  case 40: /* logical_and: logical_and AND equalty  */
#line 222 "parser.y"
                                        { (yyval.expr) = new BinaryOpNode("&&", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1789 "parser.tab.cpp"
    break;

  case 41: /* logical_and: equalty  */
#line 223 "parser.y"
                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 1795 "parser.tab.cpp"
    break;

  case 42: /* equalty: comparison EQ comparison  */
#line 227 "parser.y"
                                        { (yyval.expr) = new BinaryOpNode("==", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1801 "parser.tab.cpp"
    break;

  case 43: /* equalty: comparison NEQ comparison  */
#line 228 "parser.y"
                                        { (yyval.expr) = new BinaryOpNode("!=", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1807 "parser.tab.cpp"
    break;

  case 44: /* equalty: comparison  */
#line 229 "parser.y"
                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 1813 "parser.tab.cpp"
    break;

  case 45: /* comparison: term LT term  */
#line 233 "parser.y"
                                        { (yyval.expr) = new BinaryOpNode("<", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1819 "parser.tab.cpp"
    break;

  case 46: /* comparison: term GT term  */
#line 234 "parser.y"
                                        { (yyval.expr) = new BinaryOpNode(">", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1825 "parser.tab.cpp"
    break;

  case 47: /* comparison: term GEQ term  */
#line 235 "parser.y"
                                        { (yyval.expr) = new BinaryOpNode(">=", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1831 "parser.tab.cpp"
    break;

  case 48: /* comparison: term LEQ term  */
#line 236 "parser.y"
                                        { (yyval.expr) = new BinaryOpNode("<=", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1837 "parser.tab.cpp"
    break;

  case 49: /* comparison: term  */
#line 237 "parser.y"
                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 1843 "parser.tab.cpp"
    break;

  case 50: /* term: term PLUS factor  */
#line 241 "parser.y"
                                        { (yyval.expr) = new BinaryOpNode("+", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1849 "parser.tab.cpp"
    break;

  case 51: /* term: term MINUS factor  */
#line 242 "parser.y"
                                        { (yyval.expr) = new BinaryOpNode("-", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1855 "parser.tab.cpp"
    break;

  case 52: /* term: factor  */
#line 243 "parser.y"
                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 1861 "parser.tab.cpp"
    break;

  case 53: /* factor: factor STAR unary  */
#line 247 "parser.y"
                                        { (yyval.expr) = new BinaryOpNode("*", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1867 "parser.tab.cpp"
    break;

  case 54: /* factor: factor SLASH unary  */
#line 248 "parser.y"
                                        { (yyval.expr) = new BinaryOpNode("/", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1873 "parser.tab.cpp"
    break;

  case 55: /* factor: factor MOD unary  */
#line 249 "parser.y"
                                        { (yyval.expr) = new BinaryOpNode("%", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1879 "parser.tab.cpp"
    break;

  case 56: /* factor: unary  */
#line 250 "parser.y"
                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 1885 "parser.tab.cpp"
    break;

  case 57: /* unary: MINUS unary  */
#line 254 "parser.y"
                                        { (yyval.expr) = new UnaryOpNode("-", (yyvsp[0].expr)); }
#line 1891 "parser.tab.cpp"
    break;

  case 58: /* unary: NOT unary  */
#line 255 "parser.y"
                                        { (yyval.expr) = new UnaryOpNode("!", (yyvsp[0].expr)); }
#line 1897 "parser.tab.cpp"
    break;

  case 59: /* unary: primary  */
#line 256 "parser.y"
                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 1903 "parser.tab.cpp"
    break;

  case 60: /* primary: FALSE  */
#line 260 "parser.y"
                                        { (yyval.expr) = new NumberNode(0); }
#line 1909 "parser.tab.cpp"
    break;

  case 61: /* primary: TRUE  */
#line 261 "parser.y"
                                        { (yyval.expr) = new NumberNode(1); }
#line 1915 "parser.tab.cpp"
    break;

  case 62: /* primary: NUMBER  */
#line 262 "parser.y"
                                        { (yyval.expr) = new NumberNode((yyvsp[0].num)); }
#line 1921 "parser.tab.cpp"
    break;

  case 63: /* primary: DOUBLE  */
#line 263 "parser.y"
                                        { (yyval.expr) = new DoubleNode((yyvsp[0].dnum)); }
#line 1927 "parser.tab.cpp"
    break;

  case 64: /* primary: IDENTIFIER  */
#line 264 "parser.y"
                                        { (yyval.expr) = new VariableNode((yyvsp[0].str)); }
#line 1933 "parser.tab.cpp"
    break;

  case 65: /* primary: STRING  */
#line 265 "parser.y"
                                        { (yyval.expr) = new StringNode((yyvsp[0].str)); }
#line 1939 "parser.tab.cpp"
    break;

  case 66: /* primary: OP expression CP  */
#line 266 "parser.y"
                                        { (yyval.expr) = (yyvsp[-1].expr); }
#line 1945 "parser.tab.cpp"
    break;

  case 67: /* primary: function_call  */
#line 267 "parser.y"
                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 1951 "parser.tab.cpp"
    break;

  case 68: /* primary: lambda  */
#line 268 "parser.y"
                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 1957 "parser.tab.cpp"
    break;

  case 69: /* function_call: function_call OP arguments CP  */
#line 272 "parser.y"
                                         { (yyval.expr) = new FunctionCallNode((yyvsp[-3].expr), *(yyvsp[-1].exprList)); delete (yyvsp[-1].exprList); }
#line 1963 "parser.tab.cpp"
    break;

  case 70: /* function_call: IDENTIFIER OP arguments CP  */
#line 273 "parser.y"
                                         { (yyval.expr) = new FunctionCallNode((yyvsp[-3].str), *(yyvsp[-1].exprList)); delete (yyvsp[-1].exprList); }
#line 1969 "parser.tab.cpp"
    break;

  case 71: /* arguments: expression  */
#line 277 "parser.y"
                                       { (yyval.exprList) = new vector<ExpressionNode*>({ (yyvsp[0].expr) }); }
#line 1975 "parser.tab.cpp"
    break;

  case 72: /* arguments: expression COMMA arguments  */
#line 278 "parser.y"
                                       { (yyval.exprList) = new vector<ExpressionNode*>(*((yyvsp[0].exprList))); (yyval.exprList)->insert((yyval.exprList)->begin(), (yyvsp[-2].expr)); delete (yyvsp[0].exprList); }
#line 1981 "parser.tab.cpp"
    break;

  case 73: /* arguments: %empty  */
#line 279 "parser.y"
                                       { (yyval.exprList) = new vector<ExpressionNode*>(); }
#line 1987 "parser.tab.cpp"
    break;

  case 74: /* parameters: IDENTIFIER  */
#line 283 "parser.y"
                                       { (yyval.strList) = new vector<string>({ (yyvsp[0].str) }); }
#line 1993 "parser.tab.cpp"
    break;

  case 75: /* parameters: IDENTIFIER COMMA parameters  */
#line 284 "parser.y"
                                       { (yyval.strList) = new vector<string>(*((yyvsp[0].strList))); (yyval.strList)->insert((yyval.strList)->begin(), (yyvsp[-2].str)); delete (yyvsp[0].strList); }
#line 1999 "parser.tab.cpp"
    break;

  case 76: /* parameters: %empty  */
#line 285 "parser.y"
                                       { (yyval.strList) = new vector<string>(); }
#line 2005 "parser.tab.cpp"
    break;

  case 77: /* lambda: LAMBDA OP parameters CP block  */
#line 289 "parser.y"
                                      { (yyval.expr) = new LambdaNode(*(yyvsp[-2].strList), (yyvsp[0].blk)); delete (yyvsp[-2].strList); }
#line 2011 "parser.tab.cpp"
    break;


#line 2015 "parser.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 292 "parser.y"


int main() {
  if (yyparse() == 0 && root) {
    enterScope();
    initialize_builtins();
    dynamic_cast<StatementNode*>(root)->evaluate();
    exitScope();
  }
  return 0;
}
