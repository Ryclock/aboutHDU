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
#line 1 "sysy_parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 256

extern int yylineno;

int yylex(void);

int error_flag=0;

int yyerror(const char* msg) {
    error_flag = 1;
    fprintf(stderr, "Error type B at line %d: %s\n", yylineno, msg);
    return 0;
}

struct TreeNode {
    char* nodeType;
    char* attribute;
    int lineno;
    struct TreeNode* child;
    struct TreeNode* sibling;
};

struct TreeNode* createNode(const char* nodeType, const char* attribute, int lineno) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    node->nodeType = strdup(nodeType);
    if (node->nodeType == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    node->attribute = attribute? strdup(attribute):NULL;
    node->lineno = lineno;
    node->child = NULL;
    node->sibling = NULL;

    return node;
}

void printTree(struct TreeNode* root,int indent) {
    if (root == NULL) {
        return;
    }

    if (strcmp(root->nodeType, "empty") == 0){
        printTree(root->sibling, indent);
        return;
    }

    for (int i = 0; i < indent; i++) {
        printf("  ");
    }

    if (root->attribute) {
        printf("%s: %s\n",root->nodeType, root->attribute);
    }else if (strncmp(root->nodeType, "KW_", 3) == 0){
        printf("%s\n", root->nodeType);
    }else{
        printf("%s (%d)\n", root->nodeType, root->lineno);
    }

    printTree(root->child, indent + 1);
    printTree(root->sibling, indent);
}


#line 145 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
    INT_CONST = 258,               /* INT_CONST  */
    FLOAT_CONST = 259,             /* FLOAT_CONST  */
    IDENTIFIER = 260,              /* IDENTIFIER  */
    KW_CONST = 261,                /* KW_CONST  */
    KW_INT = 262,                  /* KW_INT  */
    KW_FLOAT = 263,                /* KW_FLOAT  */
    KW_VOID = 264,                 /* KW_VOID  */
    KW_IF = 265,                   /* KW_IF  */
    KW_ELSE = 266,                 /* KW_ELSE  */
    KW_WHILE = 267,                /* KW_WHILE  */
    KW_BREAK = 268,                /* KW_BREAK  */
    KW_CONTINUE = 269,             /* KW_CONTINUE  */
    KW_RETURN = 270,               /* KW_RETURN  */
    LEQ = 271,                     /* LEQ  */
    GEQ = 272,                     /* GEQ  */
    EQ = 273,                      /* EQ  */
    NEQ = 274,                     /* NEQ  */
    AND = 275,                     /* AND  */
    OR = 276                       /* OR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define INT_CONST 258
#define FLOAT_CONST 259
#define IDENTIFIER 260
#define KW_CONST 261
#define KW_INT 262
#define KW_FLOAT 263
#define KW_VOID 264
#define KW_IF 265
#define KW_ELSE 266
#define KW_WHILE 267
#define KW_BREAK 268
#define KW_CONTINUE 269
#define KW_RETURN 270
#define LEQ 271
#define GEQ 272
#define EQ 273
#define NEQ 274
#define AND 275
#define OR 276

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 78 "sysy_parser.y"

    int int_val;
    float float_val;
    char* str_val;
    struct TreeNode* treeNode;

#line 247 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT_CONST = 3,                  /* INT_CONST  */
  YYSYMBOL_FLOAT_CONST = 4,                /* FLOAT_CONST  */
  YYSYMBOL_IDENTIFIER = 5,                 /* IDENTIFIER  */
  YYSYMBOL_KW_CONST = 6,                   /* KW_CONST  */
  YYSYMBOL_KW_INT = 7,                     /* KW_INT  */
  YYSYMBOL_KW_FLOAT = 8,                   /* KW_FLOAT  */
  YYSYMBOL_KW_VOID = 9,                    /* KW_VOID  */
  YYSYMBOL_KW_IF = 10,                     /* KW_IF  */
  YYSYMBOL_KW_ELSE = 11,                   /* KW_ELSE  */
  YYSYMBOL_KW_WHILE = 12,                  /* KW_WHILE  */
  YYSYMBOL_KW_BREAK = 13,                  /* KW_BREAK  */
  YYSYMBOL_KW_CONTINUE = 14,               /* KW_CONTINUE  */
  YYSYMBOL_KW_RETURN = 15,                 /* KW_RETURN  */
  YYSYMBOL_16_ = 16,                       /* '+'  */
  YYSYMBOL_17_ = 17,                       /* '-'  */
  YYSYMBOL_18_ = 18,                       /* '*'  */
  YYSYMBOL_19_ = 19,                       /* '/'  */
  YYSYMBOL_20_ = 20,                       /* '%'  */
  YYSYMBOL_21_ = 21,                       /* '<'  */
  YYSYMBOL_22_ = 22,                       /* '>'  */
  YYSYMBOL_LEQ = 23,                       /* LEQ  */
  YYSYMBOL_GEQ = 24,                       /* GEQ  */
  YYSYMBOL_EQ = 25,                        /* EQ  */
  YYSYMBOL_NEQ = 26,                       /* NEQ  */
  YYSYMBOL_AND = 27,                       /* AND  */
  YYSYMBOL_OR = 28,                        /* OR  */
  YYSYMBOL_29_ = 29,                       /* '!'  */
  YYSYMBOL_30_ = 30,                       /* '='  */
  YYSYMBOL_31_ = 31,                       /* '{'  */
  YYSYMBOL_32_ = 32,                       /* '}'  */
  YYSYMBOL_33_ = 33,                       /* '['  */
  YYSYMBOL_34_ = 34,                       /* ']'  */
  YYSYMBOL_35_ = 35,                       /* '('  */
  YYSYMBOL_36_ = 36,                       /* ')'  */
  YYSYMBOL_37_ = 37,                       /* ';'  */
  YYSYMBOL_38_ = 38,                       /* ','  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_Start = 40,                     /* Start  */
  YYSYMBOL_Node_const = 41,                /* Node_const  */
  YYSYMBOL_Node_if = 42,                   /* Node_if  */
  YYSYMBOL_Node_else = 43,                 /* Node_else  */
  YYSYMBOL_Node_while = 44,                /* Node_while  */
  YYSYMBOL_Node_jumpout = 45,              /* Node_jumpout  */
  YYSYMBOL_Node_return = 46,               /* Node_return  */
  YYSYMBOL_Node_ID = 47,                   /* Node_ID  */
  YYSYMBOL_Node_open_brace = 48,           /* Node_open_brace  */
  YYSYMBOL_Node_close_brace = 49,          /* Node_close_brace  */
  YYSYMBOL_Node_open_bracket = 50,         /* Node_open_bracket  */
  YYSYMBOL_Node_close_bracket = 51,        /* Node_close_bracket  */
  YYSYMBOL_Node_open_paren = 52,           /* Node_open_paren  */
  YYSYMBOL_Node_close_paren = 53,          /* Node_close_paren  */
  YYSYMBOL_Node_semicolon = 54,            /* Node_semicolon  */
  YYSYMBOL_Node_comma = 55,                /* Node_comma  */
  YYSYMBOL_Node_mul_div_mod = 56,          /* Node_mul_div_mod  */
  YYSYMBOL_Node_lgeq = 57,                 /* Node_lgeq  */
  YYSYMBOL_Node_eqn = 58,                  /* Node_eqn  */
  YYSYMBOL_Node_and = 59,                  /* Node_and  */
  YYSYMBOL_Node_or = 60,                   /* Node_or  */
  YYSYMBOL_Node_assign = 61,               /* Node_assign  */
  YYSYMBOL_BType = 62,                     /* BType  */
  YYSYMBOL_UnaryOp = 63,                   /* UnaryOp  */
  YYSYMBOL_CompUnitList = 64,              /* CompUnitList  */
  YYSYMBOL_CompUnit = 65,                  /* CompUnit  */
  YYSYMBOL_Decl = 66,                      /* Decl  */
  YYSYMBOL_ConstDecl = 67,                 /* ConstDecl  */
  YYSYMBOL_ConstDefList = 68,              /* ConstDefList  */
  YYSYMBOL_ConstDef = 69,                  /* ConstDef  */
  YYSYMBOL_ConstExpList = 70,              /* ConstExpList  */
  YYSYMBOL_ConstInitVal = 71,              /* ConstInitVal  */
  YYSYMBOL_ConstInitValList = 72,          /* ConstInitValList  */
  YYSYMBOL_VarDecl = 73,                   /* VarDecl  */
  YYSYMBOL_VarDefList = 74,                /* VarDefList  */
  YYSYMBOL_VarDef = 75,                    /* VarDef  */
  YYSYMBOL_InitVal = 76,                   /* InitVal  */
  YYSYMBOL_InitValList = 77,               /* InitValList  */
  YYSYMBOL_FuncDef = 78,                   /* FuncDef  */
  YYSYMBOL_FuncFParams = 79,               /* FuncFParams  */
  YYSYMBOL_FuncFParam = 80,                /* FuncFParam  */
  YYSYMBOL_ExpList = 81,                   /* ExpList  */
  YYSYMBOL_Block = 82,                     /* Block  */
  YYSYMBOL_BlockItemList = 83,             /* BlockItemList  */
  YYSYMBOL_BlockItem = 84,                 /* BlockItem  */
  YYSYMBOL_StmtOther = 85,                 /* StmtOther  */
  YYSYMBOL_StmtMustELSE = 86,              /* StmtMustELSE  */
  YYSYMBOL_Stmt = 87,                      /* Stmt  */
  YYSYMBOL_Exp = 88,                       /* Exp  */
  YYSYMBOL_Cond = 89,                      /* Cond  */
  YYSYMBOL_LVal = 90,                      /* LVal  */
  YYSYMBOL_PrimaryExp = 91,                /* PrimaryExp  */
  YYSYMBOL_UnaryExp = 92,                  /* UnaryExp  */
  YYSYMBOL_FuncRParams = 93,               /* FuncRParams  */
  YYSYMBOL_MulExp = 94,                    /* MulExp  */
  YYSYMBOL_AddExp = 95,                    /* AddExp  */
  YYSYMBOL_RelExp = 96,                    /* RelExp  */
  YYSYMBOL_EqExp = 97,                     /* EqExp  */
  YYSYMBOL_LAndExp = 98,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 99,                    /* LOrExp  */
  YYSYMBOL_ConstExp = 100                  /* ConstExp  */
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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   333

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  130
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  214

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   276


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
       2,     2,     2,    29,     2,     2,     2,    20,     2,     2,
      35,    36,    18,    16,    38,    17,     2,    19,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    37,
      21,    30,    22,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    33,     2,    34,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    32,     2,     2,     2,     2,
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
      15,    23,    24,    25,    26,    27,    28
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   107,   107,   109,   113,   117,   121,   125,   127,   131,
     135,   139,   143,   147,   151,   155,   159,   163,   167,   171,
     173,   175,   179,   181,   183,   185,   189,   191,   195,   199,
     203,   207,   210,   213,   218,   221,   224,   229,   234,   239,
     242,   247,   250,   255,   265,   276,   282,   287,   294,   301,
     308,   321,   324,   330,   342,   348,   353,   362,   372,   378,
     383,   390,   395,   399,   404,   407,   413,   425,   431,   436,
     445,   455,   460,   465,   475,   487,   493,   500,   505,   508,
     513,   519,   531,   536,   541,   544,   549,   555,   563,   566,
     570,   576,   579,   586,   590,   595,   599,   605,   612,   620,
     622,   633,   635,   644,   653,   658,   663,   667,   672,   677,
     680,   689,   700,   703,   709,   714,   720,   725,   730,   733,
     740,   743,   753,   756,   763,   766,   773,   776,   783,   786,
     793
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
  "\"end of file\"", "error", "\"invalid token\"", "INT_CONST",
  "FLOAT_CONST", "IDENTIFIER", "KW_CONST", "KW_INT", "KW_FLOAT", "KW_VOID",
  "KW_IF", "KW_ELSE", "KW_WHILE", "KW_BREAK", "KW_CONTINUE", "KW_RETURN",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'<'", "'>'", "LEQ", "GEQ", "EQ",
  "NEQ", "AND", "OR", "'!'", "'='", "'{'", "'}'", "'['", "']'", "'('",
  "')'", "';'", "','", "$accept", "Start", "Node_const", "Node_if",
  "Node_else", "Node_while", "Node_jumpout", "Node_return", "Node_ID",
  "Node_open_brace", "Node_close_brace", "Node_open_bracket",
  "Node_close_bracket", "Node_open_paren", "Node_close_paren",
  "Node_semicolon", "Node_comma", "Node_mul_div_mod", "Node_lgeq",
  "Node_eqn", "Node_and", "Node_or", "Node_assign", "BType", "UnaryOp",
  "CompUnitList", "CompUnit", "Decl", "ConstDecl", "ConstDefList",
  "ConstDef", "ConstExpList", "ConstInitVal", "ConstInitValList",
  "VarDecl", "VarDefList", "VarDef", "InitVal", "InitValList", "FuncDef",
  "FuncFParams", "FuncFParam", "ExpList", "Block", "BlockItemList",
  "BlockItem", "StmtOther", "StmtMustELSE", "Stmt", "Exp", "Cond", "LVal",
  "PrimaryExp", "UnaryExp", "FuncRParams", "MulExp", "AddExp", "RelExp",
  "EqExp", "LAndExp", "LOrExp", "ConstExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-135)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-100)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     188,  -135,  -135,  -135,  -135,    20,   206,    54,   188,  -135,
    -135,  -135,  -135,  -135,  -135,    54,  -135,   141,    63,  -135,
    -135,    36,    67,  -135,  -135,  -135,  -135,   298,   155,   295,
      36,    39,  -135,  -135,  -135,    54,   295,    36,    39,  -135,
      54,  -135,  -135,  -135,  -135,  -135,    48,   298,   298,  -135,
    -135,  -135,   219,   151,    51,  -135,    62,    54,    50,    65,
    -135,   290,  -135,  -135,   151,   298,   295,  -135,    36,  -135,
     290,  -135,  -135,   295,  -135,  -135,   298,   256,    90,    50,
     151,   180,   -22,    80,   105,  -135,  -135,  -135,  -135,   298,
     298,  -135,  -135,   218,  -135,    90,    62,   206,  -135,  -135,
    -135,   128,    51,  -135,  -135,  -135,   128,  -135,    53,  -135,
      65,    50,   298,  -135,  -135,  -135,  -135,  -135,   298,  -135,
    -135,   298,  -135,   298,  -135,   298,  -135,   219,  -135,  -135,
    -135,  -135,  -135,   103,   103,    69,   183,  -135,  -135,    54,
    -135,  -135,   218,  -135,  -135,  -135,    74,   111,    51,  -135,
    -135,  -135,   295,  -135,  -135,   295,    51,  -135,   298,  -135,
      79,   151,   180,   -22,    80,   298,   298,    39,  -135,    39,
    -135,    78,  -135,  -135,    39,  -135,   298,    90,  -135,  -135,
    -135,  -135,    51,  -135,    50,    50,  -135,  -135,    39,  -135,
    -135,    81,    90,  -135,   253,   253,  -135,    39,  -135,   103,
     135,   137,  -135,  -135,  -135,   298,  -135,   253,    50,  -135,
     253,   137,   253,  -135
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,    32,    33,    31,     0,     0,     0,     2,    38,
      39,    41,    42,    40,     1,     0,    10,    63,     0,    59,
      37,     0,     0,    46,    30,    13,    15,     0,     0,     0,
      62,     0,    17,    18,    56,     0,     0,     0,     0,    43,
       0,   110,   111,    34,    35,    36,   107,     0,     0,   109,
     112,   118,   120,   130,     0,    16,     0,     0,     0,    72,
      11,     0,    61,    64,   104,     0,     0,    57,    63,    58,
       0,    48,    51,     0,    44,    45,     0,     0,   106,     0,
     122,   124,   126,   128,   105,   115,    19,    20,    21,     0,
       0,    14,    50,     0,    70,    75,     0,     0,    12,    66,
      68,     0,     0,    60,    53,    55,     0,    47,     0,   114,
     117,     0,     0,   108,    22,    23,    24,    25,     0,    26,
      27,     0,    28,     0,    29,     0,   119,   121,     4,     6,
       7,     8,     9,     0,     0,     0,     0,    81,    88,     0,
      84,    91,     0,    83,   101,    85,     0,   109,     0,    69,
      71,    65,     0,    49,    52,     0,     0,    77,     0,   113,
       0,   123,   125,   127,   129,     0,     0,     0,    93,     0,
      95,     0,    80,    82,     0,    89,     0,    74,    67,    54,
      79,   116,     0,    76,     0,     0,    96,    98,     0,    94,
      90,     0,    73,    78,     0,     0,    97,     0,    86,     0,
     101,     0,   103,    92,    87,     0,     5,     0,     0,   102,
       0,     0,     0,   100
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -135,  -135,  -135,  -121,   -61,  -135,  -135,  -135,    10,   -10,
     -58,   -23,    29,   -17,   -49,   -16,    55,  -135,  -135,  -135,
    -135,  -135,    -3,     5,   -40,  -135,   149,   -77,  -135,  -135,
     130,   152,   -12,  -135,  -135,  -135,   143,   -20,  -135,  -135,
      86,  -135,    13,   -18,  -135,    56,   -86,  -116,    -2,   -24,
    -134,   -85,  -135,     1,    49,   116,   -26,    88,    93,    92,
    -135,     9
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,   133,   207,   134,   135,   136,    46,    93,
      99,    27,    92,    47,    56,   138,    35,    89,   118,   121,
     123,   125,    29,     7,    48,     8,     9,    10,    11,    22,
      23,    30,    71,   106,    12,    18,    19,    62,   101,    13,
      58,    59,    78,   141,   142,   143,   144,   201,   145,   146,
      79,    49,    50,    51,   111,    52,    64,    81,    82,    83,
      84,    72
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      28,    53,    34,   119,   120,    63,    39,    65,   147,    96,
      53,    15,   104,    90,    65,    67,   140,    17,    36,    61,
      14,    80,    74,    76,    90,    21,    70,    66,   109,    77,
     113,   184,   185,    57,    73,   137,    54,    63,    94,    53,
      90,   100,    63,   151,    53,    68,   103,    53,   154,    85,
      21,    61,   108,   110,   156,   112,    61,   147,   105,    16,
      70,   107,   159,    70,    31,   140,    24,    95,    38,    25,
     167,   208,   148,   199,   102,   174,    32,    40,   149,   188,
     182,    25,   197,    26,   172,    91,    55,    91,   160,   199,
     126,   199,   161,    60,   211,    80,   213,    80,   139,    80,
      32,    33,    57,    33,    32,    33,    32,   122,   200,   147,
     147,    32,   171,    91,    97,    32,   165,   166,    32,   168,
     170,    90,   147,    25,   200,   147,   200,   147,    63,    53,
     175,   153,   178,   124,   110,   194,   195,   157,    26,    80,
      80,    24,    61,   179,   176,    70,   -99,   139,   206,    68,
     212,   186,   191,   187,    76,   189,   152,    20,   190,   210,
      98,   155,     2,     3,     4,   158,    33,    43,    44,   112,
      75,    24,   196,    37,    25,   198,    26,   177,    69,    80,
      45,   204,   205,   150,   169,   180,    41,    42,    16,   183,
     192,    55,   202,   203,     1,     2,     3,     4,   173,    43,
      44,   114,   115,   116,   117,   209,   127,   181,   202,   162,
     209,   193,    45,     2,     3,     4,   163,   164,    26,     0,
      32,    41,    42,    16,     1,     2,     3,     4,   128,     0,
     129,   130,   131,   132,    43,    44,     0,    86,    87,    88,
       0,     0,     0,     0,     0,     0,     0,    45,     0,    60,
      98,     0,     0,    26,     0,    32,    41,    42,    16,    41,
      42,    16,     0,   128,     0,   129,   130,   131,   132,    43,
      44,     0,    43,    44,     0,     0,     0,     0,     0,     0,
       0,     0,    45,     0,    60,    45,     0,     0,    26,     0,
      32,    26,    55,    41,    42,    16,     0,     0,    41,    42,
      16,    41,    42,    16,     0,     0,    43,    44,     0,     0,
       0,    43,    44,     0,    43,    44,     0,     0,     0,    45,
       0,    60,    98,     0,    45,    26,    60,    45,     0,     0,
      26,     0,     0,    26
};

static const yytype_int16 yycheck[] =
{
      17,    27,    18,    25,    26,    29,    22,    30,    93,    58,
      36,     6,    70,    53,    37,    31,    93,     7,    21,    29,
       0,    47,    38,    46,    64,    15,    36,    30,    77,    46,
      79,   165,   166,    28,    37,    93,    27,    61,    56,    65,
      80,    61,    66,   101,    70,    35,    66,    73,   106,    48,
      40,    61,    76,    77,     1,    78,    66,   142,    70,     5,
      70,    73,   111,    73,     1,   142,    30,    57,     1,    33,
       1,   205,    95,   194,    65,     1,    37,    22,    96,     1,
       1,    33,     1,    35,   142,    34,    36,    34,   112,   210,
      89,   212,   118,    31,   210,   121,   212,   123,    93,   125,
      37,    38,    97,    38,    37,    38,    37,    27,   194,   194,
     195,    37,   136,    34,    59,    37,   133,   134,    37,   135,
     136,   161,   207,    33,   210,   210,   212,   212,   152,   155,
     146,   102,   152,    28,   158,   184,   185,   108,    35,   165,
     166,    30,   152,   155,   147,   155,    11,   142,    11,   139,
     211,   167,   176,   169,   177,   171,   101,     8,   174,   208,
      32,   106,     7,     8,     9,   110,    38,    16,    17,   192,
      40,    30,   188,    21,    33,   191,    35,   148,    35,   205,
      29,   197,   199,    97,     1,   156,     3,     4,     5,   160,
     177,    36,   194,   195,     6,     7,     8,     9,   142,    16,
      17,    21,    22,    23,    24,   207,    90,   158,   210,   121,
     212,   182,    29,     7,     8,     9,   123,   125,    35,    -1,
      37,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      12,    13,    14,    15,    16,    17,    -1,    18,    19,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,
      32,    -1,    -1,    35,    -1,    37,     3,     4,     5,     3,
       4,     5,    -1,    10,    -1,    12,    13,    14,    15,    16,
      17,    -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    -1,    31,    29,    -1,    -1,    35,    -1,
      37,    35,    36,     3,     4,     5,    -1,    -1,     3,     4,
       5,     3,     4,     5,    -1,    -1,    16,    17,    -1,    -1,
      -1,    16,    17,    -1,    16,    17,    -1,    -1,    -1,    29,
      -1,    31,    32,    -1,    29,    35,    31,    29,    -1,    -1,
      35,    -1,    -1,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,     7,     8,     9,    40,    41,    62,    64,    65,
      66,    67,    73,    78,     0,    62,     5,    47,    74,    75,
      65,    47,    68,    69,    30,    33,    35,    50,    52,    61,
      70,     1,    37,    38,    54,    55,    61,    70,     1,    54,
      55,     3,     4,    16,    17,    29,    47,    52,    63,    90,
      91,    92,    94,    95,   100,    36,    53,    62,    79,    80,
      31,    48,    76,    88,    95,    50,    61,    54,    47,    75,
      48,    71,   100,    61,    54,    69,    50,    52,    81,    89,
      95,    96,    97,    98,    99,    92,    18,    19,    20,    56,
      63,    34,    51,    48,    82,    47,    53,    55,    32,    49,
      76,    77,   100,    76,    49,    71,    72,    71,    88,    53,
      88,    93,    50,    53,    21,    22,    23,    24,    57,    25,
      26,    58,    27,    59,    28,    60,    92,    94,    10,    12,
      13,    14,    15,    42,    44,    45,    46,    49,    54,    62,
      66,    82,    83,    84,    85,    87,    88,    90,    50,    82,
      79,    49,    55,    51,    49,    55,     1,    51,    55,    53,
      88,    95,    96,    97,    98,    52,    52,     1,    54,     1,
      54,    88,    49,    84,     1,    54,    61,    51,    76,    71,
      51,    93,     1,    51,    89,    89,    54,    54,     1,    54,
      54,    88,    81,    51,    53,    53,    54,     1,    54,    42,
      85,    86,    87,    87,    54,    52,    11,    43,    89,    87,
      53,    86,    43,    86
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    42,    43,    44,    45,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      56,    56,    57,    57,    57,    57,    58,    58,    59,    60,
      61,    62,    62,    62,    63,    63,    63,    64,    64,    65,
      65,    66,    66,    67,    67,    68,    68,    69,    69,    70,
      70,    71,    71,    71,    72,    72,    73,    73,    74,    74,
      75,    75,    75,    75,    76,    76,    76,    77,    77,    78,
      78,    79,    79,    80,    80,    80,    81,    81,    81,    81,
      82,    82,    83,    83,    84,    84,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    86,
      86,    87,    87,    87,    88,    89,    90,    90,    91,    91,
      91,    91,    92,    92,    92,    92,    93,    93,    94,    94,
      95,    95,    96,    96,    97,    97,    98,    98,    99,    99,
     100
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     4,     5,     3,     1,     4,     3,     4,
       3,     1,     3,     2,     3,     1,     3,     4,     3,     1,
       4,     3,     2,     1,     1,     3,     2,     3,     1,     6,
       5,     3,     1,     5,     4,     2,     4,     3,     5,     4,
       3,     2,     2,     1,     1,     1,     4,     5,     1,     2,
       3,     1,     5,     2,     3,     2,     3,     4,     3,     1,
       7,     1,     7,     5,     1,     1,     2,     1,     3,     1,
       1,     1,     1,     4,     3,     2,     3,     1,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
  YYLTYPE *yylloc;
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Start: CompUnitList  */
#line 107 "sysy_parser.y"
                    { (yyval.treeNode)=(yyvsp[0].treeNode); if(!error_flag){ printTree((yyval.treeNode), 0); } }
#line 1911 "y.tab.c"
    break;

  case 3: /* Node_const: KW_CONST  */
#line 109 "sysy_parser.y"
                     {
        (yyval.treeNode) = createNode("KW_CONST", NULL, yylineno);}
#line 1918 "y.tab.c"
    break;

  case 4: /* Node_if: KW_IF  */
#line 113 "sysy_parser.y"
               {
        (yyval.treeNode) = createNode("KW_IF", NULL, yylineno);}
#line 1925 "y.tab.c"
    break;

  case 5: /* Node_else: KW_ELSE  */
#line 117 "sysy_parser.y"
                   {
        (yyval.treeNode) = createNode("KW_ELSE", NULL, yylineno);}
#line 1932 "y.tab.c"
    break;

  case 6: /* Node_while: KW_WHILE  */
#line 121 "sysy_parser.y"
                     {
        (yyval.treeNode) = createNode("KW_WHILE", NULL, yylineno);}
#line 1939 "y.tab.c"
    break;

  case 7: /* Node_jumpout: KW_BREAK  */
#line 125 "sysy_parser.y"
                       {
        (yyval.treeNode) = createNode("KW_BREAK", NULL, yylineno);}
#line 1946 "y.tab.c"
    break;

  case 8: /* Node_jumpout: KW_CONTINUE  */
#line 127 "sysy_parser.y"
                  {
        (yyval.treeNode) = createNode("KW_CONTINUE", NULL, yylineno);}
#line 1953 "y.tab.c"
    break;

  case 9: /* Node_return: KW_RETURN  */
#line 131 "sysy_parser.y"
                       {
        (yyval.treeNode) = createNode("KW_RETURN", NULL, yylineno);}
#line 1960 "y.tab.c"
    break;

  case 10: /* Node_ID: IDENTIFIER  */
#line 135 "sysy_parser.y"
                    {
        (yyval.treeNode) = createNode("Ident", (yyvsp[0].str_val), yylineno);}
#line 1967 "y.tab.c"
    break;

  case 11: /* Node_open_brace: '{'  */
#line 139 "sysy_parser.y"
                     {
        (yyval.treeNode) = createNode("Seperator", "{", yylineno);}
#line 1974 "y.tab.c"
    break;

  case 12: /* Node_close_brace: '}'  */
#line 143 "sysy_parser.y"
                      {
        (yyval.treeNode) = createNode("Seperator", "}", yylineno);}
#line 1981 "y.tab.c"
    break;

  case 13: /* Node_open_bracket: '['  */
#line 147 "sysy_parser.y"
                       {
        (yyval.treeNode) = createNode("Seperator", "[", yylineno);}
#line 1988 "y.tab.c"
    break;

  case 14: /* Node_close_bracket: ']'  */
#line 151 "sysy_parser.y"
                        {
        (yyval.treeNode) = createNode("Seperator", "]", yylineno);}
#line 1995 "y.tab.c"
    break;

  case 15: /* Node_open_paren: '('  */
#line 155 "sysy_parser.y"
                     {
        (yyval.treeNode) = createNode("Seperator", "(", yylineno);}
#line 2002 "y.tab.c"
    break;

  case 16: /* Node_close_paren: ')'  */
#line 159 "sysy_parser.y"
                      {
        (yyval.treeNode) = createNode("Seperator", ")", yylineno);}
#line 2009 "y.tab.c"
    break;

  case 17: /* Node_semicolon: ';'  */
#line 163 "sysy_parser.y"
                    {
        (yyval.treeNode) = createNode("Seperator", ";", yylineno);}
#line 2016 "y.tab.c"
    break;

  case 18: /* Node_comma: ','  */
#line 167 "sysy_parser.y"
                {
        (yyval.treeNode) = createNode("Seperator", ",", yylineno);}
#line 2023 "y.tab.c"
    break;

  case 19: /* Node_mul_div_mod: '*'  */
#line 171 "sysy_parser.y"
                      {
        (yyval.treeNode) = createNode("Operator", "*", yylineno);}
#line 2030 "y.tab.c"
    break;

  case 20: /* Node_mul_div_mod: '/'  */
#line 173 "sysy_parser.y"
          {
        (yyval.treeNode) = createNode("Operator", "/", yylineno);}
#line 2037 "y.tab.c"
    break;

  case 21: /* Node_mul_div_mod: '%'  */
#line 175 "sysy_parser.y"
          {
        (yyval.treeNode) = createNode("Operator", "%", yylineno);}
#line 2044 "y.tab.c"
    break;

  case 22: /* Node_lgeq: '<'  */
#line 179 "sysy_parser.y"
               {
        (yyval.treeNode) = createNode("Operator", "<", yylineno);}
#line 2051 "y.tab.c"
    break;

  case 23: /* Node_lgeq: '>'  */
#line 181 "sysy_parser.y"
          {
        (yyval.treeNode) = createNode("Operator", ">", yylineno);}
#line 2058 "y.tab.c"
    break;

  case 24: /* Node_lgeq: LEQ  */
#line 183 "sysy_parser.y"
          {
        (yyval.treeNode) = createNode("Operator", "<=", yylineno);}
#line 2065 "y.tab.c"
    break;

  case 25: /* Node_lgeq: GEQ  */
#line 185 "sysy_parser.y"
          {
        (yyval.treeNode) = createNode("Operator", ">=", yylineno);}
#line 2072 "y.tab.c"
    break;

  case 26: /* Node_eqn: EQ  */
#line 189 "sysy_parser.y"
             {
        (yyval.treeNode) = createNode("Operator", "==", yylineno);}
#line 2079 "y.tab.c"
    break;

  case 27: /* Node_eqn: NEQ  */
#line 191 "sysy_parser.y"
          {
        (yyval.treeNode) = createNode("Operator", "!=", yylineno);}
#line 2086 "y.tab.c"
    break;

  case 28: /* Node_and: AND  */
#line 195 "sysy_parser.y"
              {
        (yyval.treeNode) = createNode("Operator", "&&", yylineno);}
#line 2093 "y.tab.c"
    break;

  case 29: /* Node_or: OR  */
#line 199 "sysy_parser.y"
            {
        (yyval.treeNode) = createNode("Operator", "||", yylineno);}
#line 2100 "y.tab.c"
    break;

  case 30: /* Node_assign: '='  */
#line 203 "sysy_parser.y"
                 {
        (yyval.treeNode) = createNode("Operator", "=", yylineno);}
#line 2107 "y.tab.c"
    break;

  case 31: /* BType: KW_VOID  */
#line 207 "sysy_parser.y"
               {
        (yyval.treeNode) = createNode("BType", NULL, yylineno);
        (yyval.treeNode)->child = createNode("Type", "void", yylineno);}
#line 2115 "y.tab.c"
    break;

  case 32: /* BType: KW_INT  */
#line 210 "sysy_parser.y"
            {
        (yyval.treeNode) = createNode("BType", NULL, yylineno);
        (yyval.treeNode)->child = createNode("Type", "int", yylineno);}
#line 2123 "y.tab.c"
    break;

  case 33: /* BType: KW_FLOAT  */
#line 213 "sysy_parser.y"
               {
        (yyval.treeNode) = createNode("BType", NULL, yylineno);
        (yyval.treeNode)->child = createNode("Type", "float", yylineno);}
#line 2131 "y.tab.c"
    break;

  case 34: /* UnaryOp: '+'  */
#line 218 "sysy_parser.y"
             {
        (yyval.treeNode) = createNode("UnaryOp", NULL, yylineno);
        (yyval.treeNode)->child = createNode("Operator", "+", yylineno);}
#line 2139 "y.tab.c"
    break;

  case 35: /* UnaryOp: '-'  */
#line 221 "sysy_parser.y"
          {
        (yyval.treeNode) = createNode("UnaryOp", NULL, yylineno);
        (yyval.treeNode)->child = createNode("Operator", "-", yylineno);}
#line 2147 "y.tab.c"
    break;

  case 36: /* UnaryOp: '!'  */
#line 224 "sysy_parser.y"
          {
        (yyval.treeNode) = createNode("UnaryOp", NULL, yylineno);
        (yyval.treeNode)->child = createNode("Operator", "!", yylineno);}
#line 2155 "y.tab.c"
    break;

  case 37: /* CompUnitList: CompUnitList CompUnit  */
#line 229 "sysy_parser.y"
                                    {
        (yyval.treeNode) = createNode("empty", NULL, (yyvsp[-1].treeNode)->lineno);
        (yyval.treeNode)->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child = (yyval.treeNode)->sibling->child->sibling = (yyvsp[0].treeNode);
        (yyval.treeNode)->sibling->child = NULL;}
#line 2165 "y.tab.c"
    break;

  case 38: /* CompUnitList: CompUnit  */
#line 234 "sysy_parser.y"
               {
        (yyval.treeNode) = createNode("empty", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyval.treeNode)->sibling = (yyvsp[0].treeNode);}
#line 2173 "y.tab.c"
    break;

  case 39: /* CompUnit: Decl  */
#line 239 "sysy_parser.y"
               {
        (yyval.treeNode) = createNode("CompUnit", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode); }
#line 2181 "y.tab.c"
    break;

  case 40: /* CompUnit: FuncDef  */
#line 242 "sysy_parser.y"
              {
        (yyval.treeNode) = createNode("CompUnit", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode); }
#line 2189 "y.tab.c"
    break;

  case 41: /* Decl: ConstDecl  */
#line 247 "sysy_parser.y"
                {
        (yyval.treeNode) = createNode("Decl", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode); }
#line 2197 "y.tab.c"
    break;

  case 42: /* Decl: VarDecl  */
#line 250 "sysy_parser.y"
              {
        (yyval.treeNode) = createNode("Decl", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode); }
#line 2205 "y.tab.c"
    break;

  case 43: /* ConstDecl: Node_const BType ConstDefList Node_semicolon  */
#line 255 "sysy_parser.y"
                                                        {
        (yyval.treeNode) = createNode("ConstDecl", NULL, (yyvsp[-3].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-3].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling->child->sibling = (yyvsp[0].treeNode);
        (yyval.treeNode)->child->sibling->sibling->child = NULL;
        if(strcmp((yyvsp[-2].treeNode)->child->nodeType, "Type")==0&&strcmp((yyvsp[-2].treeNode)->child->attribute, "void")==0){
            yyerror("Incomplete types are not allowed");
        }}
#line 2220 "y.tab.c"
    break;

  case 44: /* ConstDecl: Node_const BType ConstDefList error Node_semicolon  */
#line 265 "sysy_parser.y"
                                                        {
        (yyval.treeNode) = createNode("ConstDecl", NULL, (yyvsp[-4].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-4].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-3].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling->sibling->child->sibling = createNode("Seperator", ";", yylineno);
        (yyval.treeNode)->child->sibling->sibling->child = NULL;
        yyerrok;
        yyclearin;}
#line 2234 "y.tab.c"
    break;

  case 45: /* ConstDefList: ConstDefList Node_comma ConstDef  */
#line 276 "sysy_parser.y"
                                               {
        (yyval.treeNode) = createNode("empty", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->sibling->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child = (yyval.treeNode)->sibling->child->sibling->sibling = (yyvsp[0].treeNode);
        (yyval.treeNode)->sibling->child = NULL;}
#line 2245 "y.tab.c"
    break;

  case 46: /* ConstDefList: ConstDef  */
#line 282 "sysy_parser.y"
               {
        (yyval.treeNode) = createNode("empty", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyval.treeNode)->sibling = (yyvsp[0].treeNode);}
#line 2253 "y.tab.c"
    break;

  case 47: /* ConstDef: Node_ID ConstExpList Node_assign ConstInitVal  */
#line 287 "sysy_parser.y"
                                                        {
        (yyval.treeNode) = createNode("ConstDef", NULL, (yyvsp[-3].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-3].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->child->sibling->sibling = (yyvsp[0].treeNode);
        (yyval.treeNode)->child->sibling->child = NULL;}
#line 2265 "y.tab.c"
    break;

  case 48: /* ConstDef: Node_ID Node_assign ConstInitVal  */
#line 294 "sysy_parser.y"
                                       {
        (yyval.treeNode) = createNode("ConstDef", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[0].treeNode);}
#line 2275 "y.tab.c"
    break;

  case 49: /* ConstExpList: ConstExpList Node_open_bracket ConstExp Node_close_bracket  */
#line 301 "sysy_parser.y"
                                                                         {
        (yyval.treeNode) = createNode("empty", NULL, (yyvsp[-3].treeNode)->lineno);
        (yyval.treeNode)->sibling = (yyvsp[-3].treeNode);
        (yyval.treeNode)->sibling->child->sibling =  (yyvsp[-2].treeNode);
        (yyval.treeNode)->sibling->child->sibling->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child = (yyval.treeNode)->sibling->child->sibling->sibling->sibling = (yyvsp[0].treeNode);
        (yyval.treeNode)->sibling->child = NULL;}
#line 2287 "y.tab.c"
    break;

  case 50: /* ConstExpList: Node_open_bracket ConstExp Node_close_bracket  */
#line 308 "sysy_parser.y"
                                                    {
        (yyval.treeNode) = createNode("empty", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->sibling->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child = (yyval.treeNode)->sibling->sibling->sibling = (yyvsp[0].treeNode);}
#line 2297 "y.tab.c"
    break;

  case 51: /* ConstInitVal: ConstExp  */
#line 321 "sysy_parser.y"
                       {
        (yyval.treeNode) = createNode("ConstInitVal", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode);}
#line 2305 "y.tab.c"
    break;

  case 52: /* ConstInitVal: Node_open_brace ConstInitValList Node_close_brace  */
#line 324 "sysy_parser.y"
                                                        {
        (yyval.treeNode) = createNode("ConstInitVal", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->child->sibling = (yyvsp[0].treeNode);
        (yyval.treeNode)->child->sibling->child = NULL;}
#line 2316 "y.tab.c"
    break;

  case 53: /* ConstInitVal: Node_open_brace Node_close_brace  */
#line 330 "sysy_parser.y"
                                       {
        (yyval.treeNode) = createNode("ConstInitVal", NULL, (yyvsp[-1].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[0].treeNode);}
#line 2325 "y.tab.c"
    break;

  case 54: /* ConstInitValList: ConstInitValList Node_comma ConstInitVal  */
#line 342 "sysy_parser.y"
                                                          {
        (yyval.treeNode) = createNode("empty", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->sibling->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child = (yyval.treeNode)->sibling->child->sibling->sibling = (yyvsp[0].treeNode);
        (yyval.treeNode)->sibling->child = NULL;}
#line 2336 "y.tab.c"
    break;

  case 55: /* ConstInitValList: ConstInitVal  */
#line 348 "sysy_parser.y"
                   {
        (yyval.treeNode) = createNode("empty", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyval.treeNode)->sibling = (yyvsp[0].treeNode);}
#line 2344 "y.tab.c"
    break;

  case 56: /* VarDecl: BType VarDefList Node_semicolon  */
#line 353 "sysy_parser.y"
                                         {
        (yyval.treeNode) = createNode("VarDecl", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->child->sibling = (yyvsp[0].treeNode);
        (yyval.treeNode)->child->sibling->child=NULL;
        if(strcmp((yyvsp[-2].treeNode)->child->nodeType, "Type")==0&&strcmp((yyvsp[-2].treeNode)->child->attribute, "void")==0){
            yyerror("Incomplete types are not allowed");
        }}
#line 2358 "y.tab.c"
    break;

  case 57: /* VarDecl: BType VarDefList error Node_semicolon  */
#line 362 "sysy_parser.y"
                                           {
        (yyval.treeNode) = createNode("VarDecl", NULL, (yyvsp[-3].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-3].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling->child->sibling = createNode("Seperator", ";", yylineno);
        (yyval.treeNode)->child->sibling->child=NULL;
        yyerrok;
        yyclearin;}
#line 2371 "y.tab.c"
    break;

  case 58: /* VarDefList: VarDefList Node_comma VarDef  */
#line 372 "sysy_parser.y"
                                         {
        (yyval.treeNode) = createNode("empty", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->sibling->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child = (yyval.treeNode)->sibling->child->sibling->sibling = (yyvsp[0].treeNode);
        (yyval.treeNode)->sibling->child=NULL;}
#line 2382 "y.tab.c"
    break;

  case 59: /* VarDefList: VarDef  */
#line 378 "sysy_parser.y"
             {
        (yyval.treeNode) = createNode("empty", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyval.treeNode)->sibling = (yyvsp[0].treeNode);}
#line 2390 "y.tab.c"
    break;

  case 60: /* VarDef: Node_ID ConstExpList Node_assign InitVal  */
#line 383 "sysy_parser.y"
                                                 {
        (yyval.treeNode) = createNode("VarDef", NULL, (yyvsp[-3].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-3].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->child->sibling->sibling = (yyvsp[0].treeNode);
        (yyval.treeNode)->child->sibling->child = NULL;}
#line 2402 "y.tab.c"
    break;

  case 61: /* VarDef: Node_ID Node_assign InitVal  */
#line 390 "sysy_parser.y"
                                 {
        (yyval.treeNode) = createNode("VarDef", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[0].treeNode);}
#line 2412 "y.tab.c"
    break;

  case 62: /* VarDef: Node_ID ConstExpList  */
#line 395 "sysy_parser.y"
                           {
        (yyval.treeNode) = createNode("VarDef", NULL, (yyvsp[-1].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[0].treeNode);}
#line 2421 "y.tab.c"
    break;

  case 63: /* VarDef: Node_ID  */
#line 399 "sysy_parser.y"
              {
        (yyval.treeNode) = createNode("VarDef", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode);}
#line 2429 "y.tab.c"
    break;

  case 64: /* InitVal: Exp  */
#line 404 "sysy_parser.y"
             {
        (yyval.treeNode) = createNode("InitVal", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode);}
#line 2437 "y.tab.c"
    break;

  case 65: /* InitVal: Node_open_brace InitValList Node_close_brace  */
#line 407 "sysy_parser.y"
                                                   {
        (yyval.treeNode) = createNode("InitVal", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->child->sibling = (yyvsp[0].treeNode);
        (yyval.treeNode)->child->sibling->child=NULL; }
#line 2448 "y.tab.c"
    break;

  case 66: /* InitVal: Node_open_brace Node_close_brace  */
#line 413 "sysy_parser.y"
                                       {
        (yyval.treeNode) = createNode("InitVal", NULL, (yyvsp[-1].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[0].treeNode);}
#line 2457 "y.tab.c"
    break;

  case 67: /* InitValList: InitValList Node_comma InitVal  */
#line 425 "sysy_parser.y"
                                            {
        (yyval.treeNode) = createNode("empty", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->sibling->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child = (yyval.treeNode)->sibling->child->sibling->sibling = (yyvsp[0].treeNode);
        (yyval.treeNode)->sibling->child=NULL;}
#line 2468 "y.tab.c"
    break;

  case 68: /* InitValList: InitVal  */
#line 431 "sysy_parser.y"
              {
        (yyval.treeNode) = createNode("empty", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyval.treeNode)->sibling = (yyvsp[0].treeNode);}
#line 2476 "y.tab.c"
    break;

  case 69: /* FuncDef: BType Node_ID Node_open_paren FuncFParams Node_close_paren Block  */
#line 436 "sysy_parser.y"
                                                                          {
        (yyval.treeNode) = createNode("FuncDef", NULL, (yyvsp[-5].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-5].treeNode);
        (yyval.treeNode)->child->nodeType = "FuncType";
        (yyval.treeNode)->child->sibling = (yyvsp[-4].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[-3].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling->sibling->sibling = (yyvsp[0].treeNode);}
#line 2490 "y.tab.c"
    break;

  case 70: /* FuncDef: BType Node_ID Node_open_paren Node_close_paren Block  */
#line 445 "sysy_parser.y"
                                                           {
        (yyval.treeNode) = createNode("FuncDef", NULL, (yyvsp[-4].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-4].treeNode);
        (yyval.treeNode)->child->nodeType = "FuncType";
        (yyval.treeNode)->child->sibling = (yyvsp[-3].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling->sibling = (yyvsp[0].treeNode); }
#line 2503 "y.tab.c"
    break;

  case 71: /* FuncFParams: FuncFParam Node_comma FuncFParams  */
#line 455 "sysy_parser.y"
                                               {
        (yyval.treeNode) = createNode("FuncFParams", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[0].treeNode);}
#line 2513 "y.tab.c"
    break;

  case 72: /* FuncFParams: FuncFParam  */
#line 460 "sysy_parser.y"
                 {
        (yyval.treeNode) = createNode("FuncFParams", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode);}
#line 2521 "y.tab.c"
    break;

  case 73: /* FuncFParam: BType Node_ID Node_open_bracket Node_close_bracket ExpList  */
#line 465 "sysy_parser.y"
                                                                       {
        (yyval.treeNode) = createNode("FuncFParam", NULL, (yyvsp[-4].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-4].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-3].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling->sibling = (yyvsp[0].treeNode);
        if(strcmp((yyvsp[-4].treeNode)->child->nodeType, "Type")==0&&strcmp((yyvsp[-4].treeNode)->child->attribute, "void")==0){
            yyerror("The parameter cannot be of the type void");
        }}
#line 2536 "y.tab.c"
    break;

  case 74: /* FuncFParam: BType Node_ID Node_open_bracket Node_close_bracket  */
#line 475 "sysy_parser.y"
                                                           {
        (yyval.treeNode) = createNode("FuncFParam", NULL, (yyvsp[-3].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-3].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling = (yyvsp[0].treeNode);
        if(strcmp((yyvsp[-3].treeNode)->child->nodeType, "Type")==0&&strcmp((yyvsp[-3].treeNode)->child->attribute, "void")==0){
            yyerror("The parameter cannot be of the type void");
        }}
#line 2550 "y.tab.c"
    break;

  case 75: /* FuncFParam: BType Node_ID  */
#line 487 "sysy_parser.y"
                    {
        (yyval.treeNode) = createNode("FuncFParam", NULL, (yyvsp[-1].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[0].treeNode);}
#line 2559 "y.tab.c"
    break;

  case 76: /* ExpList: ExpList Node_open_bracket Exp Node_close_bracket  */
#line 493 "sysy_parser.y"
                                                          {
        (yyval.treeNode) = createNode("empty", NULL, (yyvsp[-3].treeNode)->lineno);
        (yyval.treeNode)->sibling = (yyvsp[-3].treeNode);
        (yyval.treeNode)->sibling->child->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->sibling->child->sibling->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child = (yyval.treeNode)->sibling->child->sibling->sibling->sibling = (yyvsp[0].treeNode);
        (yyval.treeNode)->sibling->child = NULL;}
#line 2571 "y.tab.c"
    break;

  case 77: /* ExpList: Node_open_bracket Exp Node_close_bracket  */
#line 500 "sysy_parser.y"
                                               {
        (yyval.treeNode) = createNode("empty", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->sibling->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child = (yyval.treeNode)->sibling->sibling->sibling = (yyvsp[0].treeNode);}
#line 2581 "y.tab.c"
    break;

  case 78: /* ExpList: ExpList Node_open_bracket Exp error Node_close_bracket  */
#line 505 "sysy_parser.y"
                                                            {
        yyerrok;
        yyclearin;}
#line 2589 "y.tab.c"
    break;

  case 79: /* ExpList: Node_open_bracket Exp error Node_close_bracket  */
#line 508 "sysy_parser.y"
                                                    {
        yyerrok;
        yyclearin;}
#line 2597 "y.tab.c"
    break;

  case 80: /* Block: Node_open_brace BlockItemList Node_close_brace  */
#line 513 "sysy_parser.y"
                                                      {
        (yyval.treeNode) = createNode("Block", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->child->sibling = (yyvsp[0].treeNode);
        (yyval.treeNode)->child->sibling->child=NULL;}
#line 2608 "y.tab.c"
    break;

  case 81: /* Block: Node_open_brace Node_close_brace  */
#line 519 "sysy_parser.y"
                                       {
        (yyval.treeNode) = createNode("Block", NULL, (yyvsp[-1].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[0].treeNode);}
#line 2617 "y.tab.c"
    break;

  case 82: /* BlockItemList: BlockItemList BlockItem  */
#line 531 "sysy_parser.y"
                                       {
        (yyval.treeNode) = createNode("empty", NULL, (yyvsp[-1].treeNode)->lineno);
        (yyval.treeNode)->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child = (yyval.treeNode)->sibling->child->sibling = (yyvsp[0].treeNode);
        (yyval.treeNode)->sibling->child = NULL;}
#line 2627 "y.tab.c"
    break;

  case 83: /* BlockItemList: BlockItem  */
#line 536 "sysy_parser.y"
                {
        (yyval.treeNode) = createNode("empty", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyval.treeNode)->sibling = (yyvsp[0].treeNode);}
#line 2635 "y.tab.c"
    break;

  case 84: /* BlockItem: Decl  */
#line 541 "sysy_parser.y"
                {
        (yyval.treeNode) = createNode("BlockItem", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode);}
#line 2643 "y.tab.c"
    break;

  case 85: /* BlockItem: Stmt  */
#line 544 "sysy_parser.y"
           {
        (yyval.treeNode) = createNode("BlockItem", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode);}
#line 2651 "y.tab.c"
    break;

  case 86: /* StmtOther: LVal Node_assign Exp Node_semicolon  */
#line 549 "sysy_parser.y"
                                               {
        (yyval.treeNode) = createNode("Stmt", NULL, (yyvsp[-3].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-3].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling = (yyvsp[0].treeNode);}
#line 2662 "y.tab.c"
    break;

  case 87: /* StmtOther: LVal Node_assign Exp error Node_semicolon  */
#line 555 "sysy_parser.y"
                                               {
        (yyval.treeNode) = createNode("Stmt", NULL, (yyvsp[-4].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-4].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-3].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling = createNode("Seperator", ";", yylineno);
        yyerrok;
        yyclearin;}
#line 2675 "y.tab.c"
    break;

  case 88: /* StmtOther: Node_semicolon  */
#line 563 "sysy_parser.y"
                     {
        (yyval.treeNode) = createNode("Stmt", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child=(yyvsp[0].treeNode);}
#line 2683 "y.tab.c"
    break;

  case 89: /* StmtOther: Exp Node_semicolon  */
#line 566 "sysy_parser.y"
                         {
        (yyval.treeNode) = createNode("Stmt", NULL, (yyvsp[-1].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[0].treeNode);}
#line 2692 "y.tab.c"
    break;

  case 90: /* StmtOther: Exp error Node_semicolon  */
#line 570 "sysy_parser.y"
                              {
        (yyval.treeNode) = createNode("Stmt", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = createNode("Seperator", ";", yylineno);
        yyerrok;
        yyclearin;}
#line 2703 "y.tab.c"
    break;

  case 91: /* StmtOther: Block  */
#line 576 "sysy_parser.y"
            {
        (yyval.treeNode) = createNode("Stmt", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode); }
#line 2711 "y.tab.c"
    break;

  case 92: /* StmtOther: Node_while Node_open_paren Cond Node_close_paren Stmt  */
#line 579 "sysy_parser.y"
                                                            {
        (yyval.treeNode) = createNode("Stmt", NULL, (yyvsp[-4].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-4].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-3].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling->sibling = (yyvsp[0].treeNode);}
#line 2723 "y.tab.c"
    break;

  case 93: /* StmtOther: Node_jumpout Node_semicolon  */
#line 586 "sysy_parser.y"
                                  {
        (yyval.treeNode) = createNode("Stmt", NULL, (yyvsp[-1].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[0].treeNode);}
#line 2732 "y.tab.c"
    break;

  case 94: /* StmtOther: Node_return Exp Node_semicolon  */
#line 590 "sysy_parser.y"
                                     {
        (yyval.treeNode) = createNode("Stmt", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[0].treeNode);}
#line 2742 "y.tab.c"
    break;

  case 95: /* StmtOther: Node_return Node_semicolon  */
#line 595 "sysy_parser.y"
                                 {
        (yyval.treeNode) = createNode("Stmt", NULL, (yyvsp[-1].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[0].treeNode);}
#line 2751 "y.tab.c"
    break;

  case 96: /* StmtOther: Node_jumpout error Node_semicolon  */
#line 599 "sysy_parser.y"
                                       {
        (yyval.treeNode) = createNode("Stmt", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = createNode("Seperator", ";", yylineno);
        yyerrok;
        yyclearin;}
#line 2762 "y.tab.c"
    break;

  case 97: /* StmtOther: Node_return Exp error Node_semicolon  */
#line 605 "sysy_parser.y"
                                          {
        (yyval.treeNode) = createNode("Stmt", NULL, (yyvsp[-3].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-3].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling->sibling = createNode("Seperator", ";", yylineno);
        yyerrok;
        yyclearin;}
#line 2774 "y.tab.c"
    break;

  case 98: /* StmtOther: Node_return error Node_semicolon  */
#line 612 "sysy_parser.y"
                                      {
        (yyval.treeNode) = createNode("Stmt", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = createNode("Seperator", ";", yylineno);
        yyerrok;
        yyclearin;}
#line 2785 "y.tab.c"
    break;

  case 99: /* StmtMustELSE: StmtOther  */
#line 620 "sysy_parser.y"
                        {
        (yyval.treeNode) = (yyvsp[0].treeNode);}
#line 2792 "y.tab.c"
    break;

  case 100: /* StmtMustELSE: Node_if Node_open_paren Cond Node_close_paren StmtMustELSE Node_else StmtMustELSE  */
#line 622 "sysy_parser.y"
                                                                                        {
        (yyval.treeNode) = createNode("Stmt", NULL, (yyvsp[-6].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-6].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-5].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[-4].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling = (yyvsp[-3].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling->sibling->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling->sibling->sibling->sibling = (yyvsp[0].treeNode); }
#line 2806 "y.tab.c"
    break;

  case 101: /* Stmt: StmtOther  */
#line 633 "sysy_parser.y"
                {
        (yyval.treeNode) = (yyvsp[0].treeNode);}
#line 2813 "y.tab.c"
    break;

  case 102: /* Stmt: Node_if Node_open_paren Cond Node_close_paren StmtMustELSE Node_else Stmt  */
#line 635 "sysy_parser.y"
                                                                                {
        (yyval.treeNode) = createNode("Stmt", NULL, (yyvsp[-6].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-6].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-5].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[-4].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling = (yyvsp[-3].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling->sibling->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling->sibling->sibling->sibling = (yyvsp[0].treeNode); }
#line 2827 "y.tab.c"
    break;

  case 103: /* Stmt: Node_if Node_open_paren Cond Node_close_paren Stmt  */
#line 644 "sysy_parser.y"
                                                         {
        (yyval.treeNode) = createNode("Stmt", NULL, (yyvsp[-4].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-4].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-3].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling->sibling = (yyvsp[0].treeNode);}
#line 2839 "y.tab.c"
    break;

  case 104: /* Exp: AddExp  */
#line 653 "sysy_parser.y"
            {
        (yyval.treeNode) = createNode("Exp", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode);}
#line 2847 "y.tab.c"
    break;

  case 105: /* Cond: LOrExp  */
#line 658 "sysy_parser.y"
             {
        (yyval.treeNode) = createNode("Cond", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode);}
#line 2855 "y.tab.c"
    break;

  case 106: /* LVal: Node_ID ExpList  */
#line 663 "sysy_parser.y"
                      {
        (yyval.treeNode) = createNode("LVal", NULL, (yyvsp[-1].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[0].treeNode); }
#line 2864 "y.tab.c"
    break;

  case 107: /* LVal: Node_ID  */
#line 667 "sysy_parser.y"
              {
        (yyval.treeNode) = createNode("LVal", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode);}
#line 2872 "y.tab.c"
    break;

  case 108: /* PrimaryExp: Node_open_paren Cond Node_close_paren  */
#line 672 "sysy_parser.y"
                                                  {
        (yyval.treeNode) = createNode("PrimaryExp", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[0].treeNode);}
#line 2882 "y.tab.c"
    break;

  case 109: /* PrimaryExp: LVal  */
#line 677 "sysy_parser.y"
           {
        (yyval.treeNode) = createNode("PrimaryExp", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode);}
#line 2890 "y.tab.c"
    break;

  case 110: /* PrimaryExp: INT_CONST  */
#line 680 "sysy_parser.y"
                {
        (yyval.treeNode) = createNode("PrimaryExp", NULL, yylineno);
        char* strValue = (char*)malloc(MAX_STRING_LENGTH);
        if (strValue == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
        snprintf(strValue, MAX_STRING_LENGTH, "%d", yylval.int_val);
        (yyval.treeNode)->child = createNode("Int_const", strValue, yylineno);}
#line 2904 "y.tab.c"
    break;

  case 111: /* PrimaryExp: FLOAT_CONST  */
#line 689 "sysy_parser.y"
                  {
        (yyval.treeNode) = createNode("PrimaryExp", NULL, yylineno);
        char* strValue = (char*)malloc(MAX_STRING_LENGTH);
        if (strValue == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
        snprintf(strValue, MAX_STRING_LENGTH, "%f", yylval.float_val);
        (yyval.treeNode)->child = createNode("Float_const", strValue, yylineno);}
#line 2918 "y.tab.c"
    break;

  case 112: /* UnaryExp: PrimaryExp  */
#line 700 "sysy_parser.y"
                     {
        (yyval.treeNode) = createNode("UnaryExp", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode);}
#line 2926 "y.tab.c"
    break;

  case 113: /* UnaryExp: Node_ID Node_open_paren FuncRParams Node_close_paren  */
#line 703 "sysy_parser.y"
                                                           {
        (yyval.treeNode) = createNode("UnaryExp", NULL, (yyvsp[-3].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-3].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling->sibling = (yyvsp[0].treeNode);}
#line 2937 "y.tab.c"
    break;

  case 114: /* UnaryExp: Node_ID Node_open_paren Node_close_paren  */
#line 709 "sysy_parser.y"
                                               {
        (yyval.treeNode) = createNode("UnaryExp", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[0].treeNode);}
#line 2947 "y.tab.c"
    break;

  case 115: /* UnaryExp: UnaryOp UnaryExp  */
#line 714 "sysy_parser.y"
                       {
        (yyval.treeNode) = createNode("UnaryExp", NULL, (yyvsp[-1].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[0].treeNode); }
#line 2956 "y.tab.c"
    break;

  case 116: /* FuncRParams: Exp Node_comma FuncRParams  */
#line 720 "sysy_parser.y"
                                        {
        (yyval.treeNode) = createNode("FuncRParams", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[0].treeNode);}
#line 2966 "y.tab.c"
    break;

  case 117: /* FuncRParams: Exp  */
#line 725 "sysy_parser.y"
          {
        (yyval.treeNode) = createNode("FuncRParams", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode);}
#line 2974 "y.tab.c"
    break;

  case 118: /* MulExp: UnaryExp  */
#line 730 "sysy_parser.y"
                 {
        (yyval.treeNode) = createNode("MulExp", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode);}
#line 2982 "y.tab.c"
    break;

  case 119: /* MulExp: MulExp Node_mul_div_mod UnaryExp  */
#line 733 "sysy_parser.y"
                                       {
        (yyval.treeNode) = createNode("MulExp", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[0].treeNode);}
#line 2992 "y.tab.c"
    break;

  case 120: /* AddExp: MulExp  */
#line 740 "sysy_parser.y"
               {
        (yyval.treeNode) = createNode("AddExp", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode);}
#line 3000 "y.tab.c"
    break;

  case 121: /* AddExp: AddExp UnaryOp MulExp  */
#line 743 "sysy_parser.y"
                            {
        (yyval.treeNode) = createNode("AddExp", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[0].treeNode);
        if(strcmp((yyvsp[-1].treeNode)->child->attribute, "!")==0){
            yyerror("Unusable operator '!'");
        }}
#line 3013 "y.tab.c"
    break;

  case 122: /* RelExp: AddExp  */
#line 753 "sysy_parser.y"
               {
        (yyval.treeNode) = createNode("RelExp", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode);}
#line 3021 "y.tab.c"
    break;

  case 123: /* RelExp: RelExp Node_lgeq AddExp  */
#line 756 "sysy_parser.y"
                              {
        (yyval.treeNode) = createNode("RelExp", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[0].treeNode); }
#line 3031 "y.tab.c"
    break;

  case 124: /* EqExp: RelExp  */
#line 763 "sysy_parser.y"
              {
        (yyval.treeNode) = createNode("EqExp", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode);}
#line 3039 "y.tab.c"
    break;

  case 125: /* EqExp: EqExp Node_eqn RelExp  */
#line 766 "sysy_parser.y"
                            {
        (yyval.treeNode) = createNode("EqExp", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[0].treeNode); }
#line 3049 "y.tab.c"
    break;

  case 126: /* LAndExp: EqExp  */
#line 773 "sysy_parser.y"
               {
        (yyval.treeNode) = createNode("LAndExp", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode);}
#line 3057 "y.tab.c"
    break;

  case 127: /* LAndExp: LAndExp Node_and EqExp  */
#line 776 "sysy_parser.y"
                             {
        (yyval.treeNode) = createNode("LAndExp", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[0].treeNode); }
#line 3067 "y.tab.c"
    break;

  case 128: /* LOrExp: LAndExp  */
#line 783 "sysy_parser.y"
                {
        (yyval.treeNode) = createNode("LOrExp", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode);}
#line 3075 "y.tab.c"
    break;

  case 129: /* LOrExp: LOrExp Node_or LAndExp  */
#line 786 "sysy_parser.y"
                             {
        (yyval.treeNode) = createNode("LOrExp", NULL, (yyvsp[-2].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[-2].treeNode);
        (yyval.treeNode)->child->sibling = (yyvsp[-1].treeNode);
        (yyval.treeNode)->child->sibling->sibling = (yyvsp[0].treeNode); }
#line 3085 "y.tab.c"
    break;

  case 130: /* ConstExp: AddExp  */
#line 793 "sysy_parser.y"
                 {
        (yyval.treeNode) = createNode("ConstExp", NULL, (yyvsp[0].treeNode)->lineno);
        (yyval.treeNode)->child = (yyvsp[0].treeNode);}
#line 3093 "y.tab.c"
    break;


#line 3097 "y.tab.c"

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
  *++yylsp = yyloc;

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
          = {yyssp, yytoken, &yylloc};
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

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
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

#line 798 "sysy_parser.y"


int main() {
#ifdef YYDEBUG
  yydebug = 0;
#endif
    yyparse();
    return 0;
}
