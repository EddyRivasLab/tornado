/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER = 258,
     REAL = 259,
     PLUS = 260,
     MINUS = 261,
     SQRT = 262,
     LOG = 263,
     EXP = 264,
     MULTIPLY = 265,
     DIVIDE = 266,
     MAX = 267,
     MIN = 268,
     MAXCOND = 269,
     MINCOND = 270,
     SIN = 271,
     COS = 272,
     OR = 273,
     AND = 274,
     GETS = 275,
     ADDS = 276,
     SEP = 277,
     COMMA = 278,
     GREATER = 279,
     LESS = 280,
     OPEN = 281,
     CLOSE = 282,
     XVARIABLE = 283,
     LHS = 284,
     REWRITE = 285,
     NONTERM = 286,
     NONTERMLDISEGMENT = 287,
     NONTERMRDISEGMENT = 288,
     EMISSION = 289,
     EPSILON = 290,
     EMIT = 291,
     DEFAULT_EMIT = 292,
     BPTYPE = 293,
     FORCEWC = 294,
     EDIST_SILENT = 295,
     PARAM_DECL = 296,
     EDIST_DECL = 297,
     LDIST_DECL = 298,
     DEFAULT_LDIST = 299,
     DEFAULT_LDIST_SUM = 300,
     DEFAULT_LDIST_DIF = 301,
     SUM_LDIST = 302,
     DIF_LDIST = 303,
     SYM_LDIST = 304,
     TDIST_DECL = 305,
     DEFAULT_TDIST = 306,
     DIST_NAME = 307,
     TDIST_NAME = 308,
     TTIED = 309,
     ETIED = 310,
     JOINT = 311,
     BAYES = 312,
     MARGINAL = 313,
     CONDITIONAL = 314,
     ROTATE = 315,
     CONDMARG = 316,
     MONOSEGMENT = 317,
     LDISEGMENT = 318,
     RDISEGMENT = 319,
     COORDBASE = 320,
     FIT = 321,
     AFFINE = 322,
     LINEAR = 323,
     PARAM_NAME = 324,
     UMINUS = 325
   };
#endif
/* Tokens.  */
#define INTEGER 258
#define REAL 259
#define PLUS 260
#define MINUS 261
#define SQRT 262
#define LOG 263
#define EXP 264
#define MULTIPLY 265
#define DIVIDE 266
#define MAX 267
#define MIN 268
#define MAXCOND 269
#define MINCOND 270
#define SIN 271
#define COS 272
#define OR 273
#define AND 274
#define GETS 275
#define ADDS 276
#define SEP 277
#define COMMA 278
#define GREATER 279
#define LESS 280
#define OPEN 281
#define CLOSE 282
#define XVARIABLE 283
#define LHS 284
#define REWRITE 285
#define NONTERM 286
#define NONTERMLDISEGMENT 287
#define NONTERMRDISEGMENT 288
#define EMISSION 289
#define EPSILON 290
#define EMIT 291
#define DEFAULT_EMIT 292
#define BPTYPE 293
#define FORCEWC 294
#define EDIST_SILENT 295
#define PARAM_DECL 296
#define EDIST_DECL 297
#define LDIST_DECL 298
#define DEFAULT_LDIST 299
#define DEFAULT_LDIST_SUM 300
#define DEFAULT_LDIST_DIF 301
#define SUM_LDIST 302
#define DIF_LDIST 303
#define SYM_LDIST 304
#define TDIST_DECL 305
#define DEFAULT_TDIST 306
#define DIST_NAME 307
#define TDIST_NAME 308
#define TTIED 309
#define ETIED 310
#define JOINT 311
#define BAYES 312
#define MARGINAL 313
#define CONDITIONAL 314
#define ROTATE 315
#define CONDMARG 316
#define MONOSEGMENT 317
#define LDISEGMENT 318
#define RDISEGMENT 319
#define COORDBASE 320
#define FIT 321
#define AFFINE 322
#define LINEAR 323
#define PARAM_NAME 324
#define UMINUS 325




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 215 "grm_parsegrammar.y"
{ 
  char              *string; 
  double             dval; 
  struct param_s    *param; 
}
/* Line 1529 of yacc.c.  */
#line 195 "grm_parsegrammar.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

