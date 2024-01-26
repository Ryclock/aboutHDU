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

#line 116 "y.tab.h"

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
