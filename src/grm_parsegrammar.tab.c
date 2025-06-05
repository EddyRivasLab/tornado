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
#line 1 "grm_parsegrammar.y"

  /* grm_parsegrammar.y
   * yacc source file for SCFG compiler (TORNADO) 
   *
   * er, Thu Aug  2 09:20:58 EDT 2007
   *    starting from Ray Lang's grampiler.y
   */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <math.h>
  

 /* argument to pass yyparse() */
#define YYPARSE_PARAM yyparse_param     /* the RNA grammar */

#include <esl_config.h>
#include <easel.h>
#include <esl_alphabet.h>
#include <esl_regexp.h>
#include <esl_vectorops.h>

#include "grammar.h"
#include "grm_config.h"
#include "grm_io.h"
#include "grm_gmx.h"
#include "grm_parsegrammar.h" 
#include "grm_util.h"
   
 /* static variables */
  static char              errbuf[eslERRBUFSIZE]; 
  static struct lexeme_s   lexeme;      /* lexeme at hand */
  static ATOM              iatom;       /* incomplete atom */
  static int               rnr = 0;     /* total number of rules in the rna_grammar */
  static int               ynr = 0;     /* total number of rules in the yacc_grammar */
  static int               nt_idx;      /* index of NT at work */
  static int               is_new_rule; /* TRUE if starting a new rule */
  static int               ntied = 0;
  static int               nparam = 0;
  static int               p;
  static int               tied[MAXRULES];

  /* static functions */
  static int             add_coord(ATOM *iatom, char *coord, int offset, int verbose);
  static int             add_context(ATOM *iatom, char *context, int offset, int verbose);
  static enum basepair_e get_basepairtype(char *bptype);
  static int             is_base_pair(char *s1, char *s2); 
  static int             is_default_score (int L, ESL_DSQ *dsq); 
  static int             rna_atom_add_to_rule(int r, int w, ATOM *iatom, GRAMMAR *G, struct lexeme_s lexeme, int verbose); 
  static int             rna_atom_add_to_rule_emission(int r, int w, ATOM iatom, GRAMMAR *G, struct lexeme_s lexeme); 
  static int             rna_atom_add_to_rule_nonterminal(int r, int w, ATOM iatom, GRAMMAR *G, struct lexeme_s lexeme); 
  static int             rna_atom_add_to_rule_nonterminal_di(int r, int w, ATOM iatom, GRAMMAR *G, struct lexeme_s lexeme); 
  static int             rna_atom_add_to_rule_monosegment(int r, int w, ATOM iatom, GRAMMAR *G, struct lexeme_s lexeme); 
  static int             rna_atom_add_to_rule_disegment(int r, int w, ATOM iatom, GRAMMAR *G, struct lexeme_s lexeme); 
  static int             rna_atom_add_to_rule_disegment_tied(NT *nt, RULE *r, ATOM *A, GRAMMAR *G, struct lexeme_s lexeme); 
  static int             rna_atom_add_to_rule_disegment_untied(NT *nt, RULE *r, ATOM *A, GRAMMAR *G, struct lexeme_s lexeme); 
  static enum basepair_e rna_atom_basepairtype(ATOM *A, char *ntname); 
  static void            rna_atom_clear(ATOM *A); 
  static void            atom_qsort(int *v, int *coord, int *offset, int left, int right);  
  static int             rna_atom_write(ATOM *A, RULE *R, GRAMMAR *G, int add_ntcontext, int verbose); 
  static int             rna_atom_write_disegment(ATOM *A, RULE *R, GRAMMAR *G, int verbose); 
  static int             rna_atom_write_edist_emission(ATOM *A, RULE *R, GRAMMAR *G, int verbose); 
  static int             rna_atom_write_edist_tieddisegment(ATOM *A, RULE *R, GRAMMAR *G, int verbose); 
  static int             rna_atom_write_emission(ATOM *A, RULE *R, GRAMMAR *G, int add_ntcontext, int verbose); 
  static int             rna_atom_write_emission_context(ATOM *A, GRAMMAR *G, int add_ntcontext); 
  static int             rna_atom_write_epsilon(ATOM *A, GRAMMAR *G); 
  static int             rna_atom_write_monosegment(ATOM *A, GRAMMAR *G, int verbose); 
  static int             rna_atom_write_nonterminal(ATOM *A, GRAMMAR *G); 
  static int             rna_atom_write_segment_ldist(ATOM *A, GRAMMAR *G, int verbose); 
  static int             rna_edist_add_edist(GRAMMAR *G, char *atom, char *edistname, int c1, int c2, int add); 
  static int             rna_edist_add_score(GRAMMAR *G, char *lexeme, SCVAL sc, int add); 
  static int             rna_edist_assign (EDIST *edist, ATOM *A, GRAMMAR *G); 
  static int             rna_edist_assign_tieddisegment(int idx, EDIST *edist, ATOM *A, GRAMMAR *G); 
  static int             rna_edist_check_name(EDIST *edist); 
  static void            rna_edist_declare(GRAMMAR *G, char *ename, int nemist,  
					   int ncontexts, int nbasepairs, 
					   char *basepairtype1, int basepair1_coordl_idx, int basepair1_coordr_idx, int force_wccomp1,  
					   char *basepairtype2, int basepair2_coordl_idx, int basepair2_coordr_idx, int force_wccomp2, int verbose); 
  static void            rna_edist_declare_one(GRAMMAR *G, char *ename, int nemist, int ncontexts, int nbasepairs, int silent,  
					       char *basepairtype1, int basepair1_coordl_idx, int basepair1_coordr_idx, int force_wccomp1,   
					       char *basepairtype2, int basepair2_coordl_idx, int basepair2_coordr_idx, int force_wccomp2,   
					       int edist_idx, int verbose); 
  static void            rna_edist_declare_tied_joint(GRAMMAR *G, char *tename1, int nbp1, char *tename2, int nbp2, char *tiedtype, int verbose); 
  static void            rna_edist_declare_tied_bayes(GRAMMAR *G, char *tename1, int nbp1, char *tename2, int nbp2, char *tiedtype, int verbose); 
  static void            rna_edist_declare_tied_marginal(GRAMMAR *G, char *tename, int nbp, int coord, char *tiedtype, int verbose); 
  static void            rna_edist_declare_tied_conditional(GRAMMAR *G, char *tename1, int nbp1, int coord, char *tename2, int nbp2, char *tiedtype, int verbose); 
  static void            rna_edist_declare_tied_condmarg(GRAMMAR *G, char *tename1, int nbp1, char *tename2, int nbp2, char *tiedtype, int verbose); 
  static void            rna_edist_declare_tied_rotate_simple(GRAMMAR *G, char *tename, int nbp, char *tiedtype, int rc, int verbose); 
  static void            rna_edist_declare_tied_rotate_context(GRAMMAR *G, char *tename1, int nbp1, char *tename2, int nbp2, char *tename3, int nbp3,  
							       char *tiedtype, int rc1, int rc2, int verbose); 
  static int             rna_edist_write(EDIST *edist, GRAMMAR *G, int edist_idx, int verbose); 
  static int             rna_ldist_add_score_mono(GRAMMAR *G, char *l, SCVAL sc, int add, int verbose); 
  static int             rna_ldist_add_score_di(GRAMMAR *G, char *l, char *m, SCVAL sc, int add, int verbose); 
  static int             rna_ldist_add_score_di_sum(GRAMMAR *G, char *l, SCVAL sc, int add, int verbose); 
  static int             rna_ldist_add_score_di_dif(GRAMMAR *G, char *l, SCVAL sc, int add, int verbose); 
  static int             rna_ldist_add_score_di_sym(GRAMMAR *G, char *l, SCVAL sc, int add, int verbose); 
  static int             rna_ldist_add_affine_score(GRAMMAR *G, double a, double b, double c, double d, int verbose); 
  static int             rna_ldist_add_linear_score(GRAMMAR *G, double a, double b, int verbose); 
  static int             rna_ldist_assign (ATOM *A, GRAMMAR *G); 
  static void            rna_ldist_declare(GRAMMAR *G, char *ldecl, char *lname, int min, int fit, int max, int minL, int minR, int verbose); 
  static int             rna_ldist_write(GRAMMAR *G, char *ldecl, char *lname, int min, int fit, int max, int minL, int minR, int verbose); 
  static int             rna_lhs_write(GRAMMAR *G, struct lexeme_s lexeme, char *errbuf, int *ret_nt_idx, int verbose); 
  static int             rna_nonterminal_context(NT *nt); 
  static int             rna_nonterminal_get_context(int *ret_nct, int *ct_tag, char *ntname); 
  static int             rna_rule_atomlist_write(int rnr, int w, GRAMMAR *G); 
  static int             rna_rule_enum_write(int rnr, int ynr, int w, GRAMMAR *G, struct lexeme_s lexeme, int verbose);  
  static void            rna_rule_print(int w, GRAMMAR *G); 
  static void            rna_rule_syntax(RULE *R, struct lexeme_s lexeme); 
  static void            rna_rule_syntax_add(RULE *R, char *atomsyntax); 
  static int             rna_tdist_add_score(GRAMMAR *G, int t, SCVAL sc, int add); 
  static int             rna_tdist_add_score_default(GRAMMAR *G, SCVAL sc); 
  static int             rna_tdist_assign(NT *nt, GRAMMAR *G, char *tdist_name); 
  static void            rna_tdist_declare(GRAMMAR *G, char *ntname, int nrules, int verbose); 
  static int             rna_tdist_tie(int ntied, int *tied, GRAMMAR *G, int verbose); 
  static int             rna_tdist_write(GRAMMAR *G, char *tdist_name, int nrules, int verbose); 
  static int   yacc_rule1        (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule2        (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule3        (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule4        (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule5        (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule6        (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule7        (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule8        (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule9        (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule10       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule11       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule12       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule12_2at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule12_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule13       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule13_2at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule13_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule14       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule14_2at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule14_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule15       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule16       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule16_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule16_4at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule17       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule17_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule17_4at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule18       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule18_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule18_4at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule19       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule19_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule20       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule20_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule21       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule21_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule22       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule22_4at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule22_5at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule23       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule23_2at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule24       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule24_2at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule25       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule25_2at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule26       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule26_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule27       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule27_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule28       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule29       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule30       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose); 
  static int   yacc_rule31       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule31_tied  (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule31_tied_context  (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule31_tied_nocontext (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule31_untied(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule32       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule33       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule34       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule35       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule35_2at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule35_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule36       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule36_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule36_4at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule37       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule37_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule37_4at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule38       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule38_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule38_4at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule39       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule39_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule39_4at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule40       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule40_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule40_4at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule41       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule41_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule42       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule42_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule43       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule43_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule44       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule44_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule45       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule45_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule46       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule46_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule47       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule47_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule48       (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  static int   yacc_rule48_3at   (RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose);  
  

#line 285 "grm_parsegrammar.tab.c"

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

#include "grm_parsegrammar.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INTEGER = 3,                    /* INTEGER  */
  YYSYMBOL_REAL = 4,                       /* REAL  */
  YYSYMBOL_PLUS = 5,                       /* PLUS  */
  YYSYMBOL_MINUS = 6,                      /* MINUS  */
  YYSYMBOL_SQRT = 7,                       /* SQRT  */
  YYSYMBOL_LOG = 8,                        /* LOG  */
  YYSYMBOL_EXP = 9,                        /* EXP  */
  YYSYMBOL_MULTIPLY = 10,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 11,                    /* DIVIDE  */
  YYSYMBOL_MAX = 12,                       /* MAX  */
  YYSYMBOL_MIN = 13,                       /* MIN  */
  YYSYMBOL_MAXCOND = 14,                   /* MAXCOND  */
  YYSYMBOL_MINCOND = 15,                   /* MINCOND  */
  YYSYMBOL_SIN = 16,                       /* SIN  */
  YYSYMBOL_COS = 17,                       /* COS  */
  YYSYMBOL_OR = 18,                        /* OR  */
  YYSYMBOL_AND = 19,                       /* AND  */
  YYSYMBOL_GETS = 20,                      /* GETS  */
  YYSYMBOL_ADDS = 21,                      /* ADDS  */
  YYSYMBOL_SEP = 22,                       /* SEP  */
  YYSYMBOL_COMMA = 23,                     /* COMMA  */
  YYSYMBOL_GREATER = 24,                   /* GREATER  */
  YYSYMBOL_LESS = 25,                      /* LESS  */
  YYSYMBOL_OPEN = 26,                      /* OPEN  */
  YYSYMBOL_CLOSE = 27,                     /* CLOSE  */
  YYSYMBOL_XVARIABLE = 28,                 /* XVARIABLE  */
  YYSYMBOL_LHS = 29,                       /* LHS  */
  YYSYMBOL_REWRITE = 30,                   /* REWRITE  */
  YYSYMBOL_NONTERM = 31,                   /* NONTERM  */
  YYSYMBOL_NONTERMLDISEGMENT = 32,         /* NONTERMLDISEGMENT  */
  YYSYMBOL_NONTERMRDISEGMENT = 33,         /* NONTERMRDISEGMENT  */
  YYSYMBOL_EMISSION = 34,                  /* EMISSION  */
  YYSYMBOL_EPSILON = 35,                   /* EPSILON  */
  YYSYMBOL_EMIT = 36,                      /* EMIT  */
  YYSYMBOL_DEFAULT_EMIT = 37,              /* DEFAULT_EMIT  */
  YYSYMBOL_BPTYPE = 38,                    /* BPTYPE  */
  YYSYMBOL_FORCEWC = 39,                   /* FORCEWC  */
  YYSYMBOL_EDIST_SILENT = 40,              /* EDIST_SILENT  */
  YYSYMBOL_PARAM_DECL = 41,                /* PARAM_DECL  */
  YYSYMBOL_EDIST_DECL = 42,                /* EDIST_DECL  */
  YYSYMBOL_LDIST_DECL = 43,                /* LDIST_DECL  */
  YYSYMBOL_DEFAULT_LDIST = 44,             /* DEFAULT_LDIST  */
  YYSYMBOL_DEFAULT_LDIST_SUM = 45,         /* DEFAULT_LDIST_SUM  */
  YYSYMBOL_DEFAULT_LDIST_DIF = 46,         /* DEFAULT_LDIST_DIF  */
  YYSYMBOL_SUM_LDIST = 47,                 /* SUM_LDIST  */
  YYSYMBOL_DIF_LDIST = 48,                 /* DIF_LDIST  */
  YYSYMBOL_SYM_LDIST = 49,                 /* SYM_LDIST  */
  YYSYMBOL_TDIST_DECL = 50,                /* TDIST_DECL  */
  YYSYMBOL_DEFAULT_TDIST = 51,             /* DEFAULT_TDIST  */
  YYSYMBOL_DIST_NAME = 52,                 /* DIST_NAME  */
  YYSYMBOL_TDIST_NAME = 53,                /* TDIST_NAME  */
  YYSYMBOL_TTIED = 54,                     /* TTIED  */
  YYSYMBOL_ETIED = 55,                     /* ETIED  */
  YYSYMBOL_JOINT = 56,                     /* JOINT  */
  YYSYMBOL_BAYES = 57,                     /* BAYES  */
  YYSYMBOL_MARGINAL = 58,                  /* MARGINAL  */
  YYSYMBOL_CONDITIONAL = 59,               /* CONDITIONAL  */
  YYSYMBOL_ROTATE = 60,                    /* ROTATE  */
  YYSYMBOL_CONDMARG = 61,                  /* CONDMARG  */
  YYSYMBOL_MONOSEGMENT = 62,               /* MONOSEGMENT  */
  YYSYMBOL_LDISEGMENT = 63,                /* LDISEGMENT  */
  YYSYMBOL_RDISEGMENT = 64,                /* RDISEGMENT  */
  YYSYMBOL_COORDBASE = 65,                 /* COORDBASE  */
  YYSYMBOL_FIT = 66,                       /* FIT  */
  YYSYMBOL_AFFINE = 67,                    /* AFFINE  */
  YYSYMBOL_LINEAR = 68,                    /* LINEAR  */
  YYSYMBOL_PARAM_NAME = 69,                /* PARAM_NAME  */
  YYSYMBOL_UMINUS = 70,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 71,                  /* $accept  */
  YYSYMBOL_start = 72,                     /* start  */
  YYSYMBOL_73_1 = 73,                      /* $@1  */
  YYSYMBOL_rna_grammar = 74,               /* rna_grammar  */
  YYSYMBOL_decls = 75,                     /* decls  */
  YYSYMBOL_param_decls = 76,               /* param_decls  */
  YYSYMBOL_param_decl = 77,                /* param_decl  */
  YYSYMBOL_expression = 78,                /* expression  */
  YYSYMBOL_dist_decls = 79,                /* dist_decls  */
  YYSYMBOL_edist_decls = 80,               /* edist_decls  */
  YYSYMBOL_ldist_decls = 81,               /* ldist_decls  */
  YYSYMBOL_tdist_decls = 82,               /* tdist_decls  */
  YYSYMBOL_edist_decl = 83,                /* edist_decl  */
  YYSYMBOL_ldist_decl = 84,                /* ldist_decl  */
  YYSYMBOL_tdist_decl = 85,                /* tdist_decl  */
  YYSYMBOL_edist_decl_only = 86,           /* edist_decl_only  */
  YYSYMBOL_edist_decl_tied = 87,           /* edist_decl_tied  */
  YYSYMBOL_88_2 = 88,                      /* $@2  */
  YYSYMBOL_89_3 = 89,                      /* $@3  */
  YYSYMBOL_90_4 = 90,                      /* $@4  */
  YYSYMBOL_91_5 = 91,                      /* $@5  */
  YYSYMBOL_92_6 = 92,                      /* $@6  */
  YYSYMBOL_93_7 = 93,                      /* $@7  */
  YYSYMBOL_94_8 = 94,                      /* $@8  */
  YYSYMBOL_edist_tied = 95,                /* edist_tied  */
  YYSYMBOL_ldist_decl_only = 96,           /* ldist_decl_only  */
  YYSYMBOL_tdist_decl_only = 97,           /* tdist_decl_only  */
  YYSYMBOL_edist_decl_with_scores = 98,    /* edist_decl_with_scores  */
  YYSYMBOL_99_9 = 99,                      /* $@9  */
  YYSYMBOL_100_10 = 100,                   /* $@10  */
  YYSYMBOL_101_11 = 101,                   /* $@11  */
  YYSYMBOL_102_12 = 102,                   /* $@12  */
  YYSYMBOL_103_13 = 103,                   /* $@13  */
  YYSYMBOL_104_14 = 104,                   /* $@14  */
  YYSYMBOL_105_15 = 105,                   /* $@15  */
  YYSYMBOL_106_16 = 106,                   /* $@16  */
  YYSYMBOL_107_17 = 107,                   /* $@17  */
  YYSYMBOL_108_18 = 108,                   /* $@18  */
  YYSYMBOL_109_19 = 109,                   /* $@19  */
  YYSYMBOL_110_20 = 110,                   /* $@20  */
  YYSYMBOL_111_21 = 111,                   /* $@21  */
  YYSYMBOL_112_22 = 112,                   /* $@22  */
  YYSYMBOL_ldist_decl_with_scores = 113,   /* ldist_decl_with_scores  */
  YYSYMBOL_tdist_decl_with_scores = 114,   /* tdist_decl_with_scores  */
  YYSYMBOL_115_23 = 115,                   /* $@23  */
  YYSYMBOL_tdefine = 116,                  /* tdefine  */
  YYSYMBOL_ttied = 117,                    /* ttied  */
  YYSYMBOL_ttied_one = 118,                /* ttied_one  */
  YYSYMBOL_ttied_one_rhs = 119,            /* ttied_one_rhs  */
  YYSYMBOL_ttied_idx = 120,                /* ttied_idx  */
  YYSYMBOL_escores = 121,                  /* escores  */
  YYSYMBOL_lscores = 122,                  /* lscores  */
  YYSYMBOL_tscores = 123,                  /* tscores  */
  YYSYMBOL_other_escores = 124,            /* other_escores  */
  YYSYMBOL_other_lscores = 125,            /* other_lscores  */
  YYSYMBOL_other_tscores = 126,            /* other_tscores  */
  YYSYMBOL_default_escore = 127,           /* default_escore  */
  YYSYMBOL_default_lscore = 128,           /* default_lscore  */
  YYSYMBOL_default_lscore_sum = 129,       /* default_lscore_sum  */
  YYSYMBOL_default_lscore_dif = 130,       /* default_lscore_dif  */
  YYSYMBOL_default_tscore = 131,           /* default_tscore  */
  YYSYMBOL_one_escore = 132,               /* one_escore  */
  YYSYMBOL_one_lscore = 133,               /* one_lscore  */
  YYSYMBOL_function = 134,                 /* function  */
  YYSYMBOL_one_tscore = 135,               /* one_tscore  */
  YYSYMBOL_rewrites = 136,                 /* rewrites  */
  YYSYMBOL_rewrite = 137,                  /* rewrite  */
  YYSYMBOL_138_24 = 138,                   /* $@24  */
  YYSYMBOL_139_25 = 139,                   /* $@25  */
  YYSYMBOL_rhs_list = 140,                 /* rhs_list  */
  YYSYMBOL_rule = 141,                     /* rule  */
  YYSYMBOL_rule_atomlist = 142,            /* rule_atomlist  */
  YYSYMBOL_atom = 143,                     /* atom  */
  YYSYMBOL_emission_atom = 144,            /* emission_atom  */
  YYSYMBOL_nonterm_atom = 145,             /* nonterm_atom  */
  YYSYMBOL_monoseg_atom = 146,             /* monoseg_atom  */
  YYSYMBOL_diseg_atom = 147,               /* diseg_atom  */
  YYSYMBOL_list = 148,                     /* list  */
  YYSYMBOL_coordlist = 149,                /* coordlist  */
  YYSYMBOL_coordrange = 150,               /* coordrange  */
  YYSYMBOL_contextlist = 151,              /* contextlist  */
  YYSYMBOL_paircoord = 152,                /* paircoord  */
  YYSYMBOL_paircontext = 153,              /* paircontext  */
  YYSYMBOL_coord = 154,                    /* coord  */
  YYSYMBOL_context = 155,                  /* context  */
  YYSYMBOL_rule_enum = 156                 /* rule_enum  */
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
typedef yytype_int16 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   757

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  86
/* YYNRULES -- Number of rules.  */
#define YYNRULES  335
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  611

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   325


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   276,   276,   276,   295,   296,   301,   302,   303,   304,
     309,   310,   313,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   350,   351,   352,   353,   354,   355,   356,   359,   360,
     362,   363,   365,   366,   369,   370,   371,   373,   374,   376,
     377,   382,   388,   394,   400,   406,   412,   418,   428,   427,
     435,   434,   442,   441,   449,   448,   456,   455,   463,   462,
     470,   469,   482,   491,   506,   514,   520,   526,   532,   538,
     544,   552,   557,   562,   567,   573,   582,   581,   589,   588,
     596,   595,   603,   602,   610,   609,   617,   616,   624,   623,
     631,   630,   638,   637,   645,   644,   652,   651,   659,   658,
     666,   665,   673,   672,   680,   684,   683,   690,   691,   692,
     695,   695,   697,   703,   703,   705,   709,   711,   713,   716,
     716,   718,   718,   720,   720,   724,   730,   736,   742,   750,
     756,   764,   770,   778,   783,   788,   789,   790,   791,   794,
     800,   806,   813,   823,   829,   837,   842,   847,   852,   857,
     862,   867,   872,   877,   882,   887,   891,   897,   904,   912,
     919,   927,   937,   938,   943,   942,   952,   951,   963,   968,
     976,   980,   984,   988,   995,   996,   997,   998,  1001,  1011,
    1025,  1037,  1046,  1059,  1070,  1082,  1095,  1111,  1111,  1114,
    1115,  1116,  1117,  1121,  1122,  1126,  1127,  1128,  1129,  1132,
    1141,  1150,  1154,  1158,  1162,  1169,  1173,  1177,  1181,  1189,
    1197,  1205,  1214,  1222,  1231,  1241,  1250,  1260,  1269,  1279,
    1288,  1298,  1309,  1319,  1330,  1340,  1351,  1361,  1372,  1381,
    1392,  1404,  1414,  1425,  1437,  1447,  1459,  1471,  1482,  1494,
    1505,  1517,  1530,  1541,  1553,  1566,  1577,  1589,  1602,  1614,
    1627,  1639,  1652,  1664,  1677,  1689,  1702,  1716,  1727,  1739,
    1750,  1762,  1774,  1787,  1800,  1814,  1828,  1843,  1851,  1860,
    1869,  1879,  1888,  1898,  1908,  1919,  1931,  1944,  1955,  1967,
    1980,  1991,  2003,  2016,  2028,  2041,  2055,  2065,  2076,  2088,
    2101,  2112,  2124,  2137,  2151,  2162,  2174,  2187,  2201,  2212,
    2224,  2237,  2251,  2262,  2274,  2287,  2301,  2313,  2326,  2340,
    2355,  2367,  2380,  2392,  2405,  2418,  2432,  2445,  2459,  2472,
    2486,  2499,  2513,  2527,  2542,  2556
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INTEGER", "REAL",
  "PLUS", "MINUS", "SQRT", "LOG", "EXP", "MULTIPLY", "DIVIDE", "MAX",
  "MIN", "MAXCOND", "MINCOND", "SIN", "COS", "OR", "AND", "GETS", "ADDS",
  "SEP", "COMMA", "GREATER", "LESS", "OPEN", "CLOSE", "XVARIABLE", "LHS",
  "REWRITE", "NONTERM", "NONTERMLDISEGMENT", "NONTERMRDISEGMENT",
  "EMISSION", "EPSILON", "EMIT", "DEFAULT_EMIT", "BPTYPE", "FORCEWC",
  "EDIST_SILENT", "PARAM_DECL", "EDIST_DECL", "LDIST_DECL",
  "DEFAULT_LDIST", "DEFAULT_LDIST_SUM", "DEFAULT_LDIST_DIF", "SUM_LDIST",
  "DIF_LDIST", "SYM_LDIST", "TDIST_DECL", "DEFAULT_TDIST", "DIST_NAME",
  "TDIST_NAME", "TTIED", "ETIED", "JOINT", "BAYES", "MARGINAL",
  "CONDITIONAL", "ROTATE", "CONDMARG", "MONOSEGMENT", "LDISEGMENT",
  "RDISEGMENT", "COORDBASE", "FIT", "AFFINE", "LINEAR", "PARAM_NAME",
  "UMINUS", "$accept", "start", "$@1", "rna_grammar", "decls",
  "param_decls", "param_decl", "expression", "dist_decls", "edist_decls",
  "ldist_decls", "tdist_decls", "edist_decl", "ldist_decl", "tdist_decl",
  "edist_decl_only", "edist_decl_tied", "$@2", "$@3", "$@4", "$@5", "$@6",
  "$@7", "$@8", "edist_tied", "ldist_decl_only", "tdist_decl_only",
  "edist_decl_with_scores", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14",
  "$@15", "$@16", "$@17", "$@18", "$@19", "$@20", "$@21", "$@22",
  "ldist_decl_with_scores", "tdist_decl_with_scores", "$@23", "tdefine",
  "ttied", "ttied_one", "ttied_one_rhs", "ttied_idx", "escores", "lscores",
  "tscores", "other_escores", "other_lscores", "other_tscores",
  "default_escore", "default_lscore", "default_lscore_sum",
  "default_lscore_dif", "default_tscore", "one_escore", "one_lscore",
  "function", "one_tscore", "rewrites", "rewrite", "$@24", "$@25",
  "rhs_list", "rule", "rule_atomlist", "atom", "emission_atom",
  "nonterm_atom", "monoseg_atom", "diseg_atom", "list", "coordlist",
  "coordrange", "contextlist", "paircoord", "paircontext", "coord",
  "context", "rule_enum", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-467)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-116)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -467,    32,   289,  -467,    20,    48,    70,   135,  -467,   148,
     472,  -467,  -467,   302,   143,   477,  -467,  -467,  -467,  -467,
    -467,   185,  -467,  -467,  -467,  -467,   121,   206,   199,   199,
     209,   148,  -467,  -467,  -467,   143,  -467,  -467,   302,   143,
    -467,   108,   221,   234,  -467,  -467,   231,   222,   275,   279,
    -467,  -467,   199,   290,   314,   338,   362,   377,   387,   413,
     417,   427,   199,  -467,   426,   446,  -467,   160,  -467,   143,
     199,   291,   199,   199,    66,  -467,  -467,   199,   366,  -467,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   100,
     199,   199,   199,   199,   199,   354,   160,   -13,   165,  -467,
     265,   436,   458,  -467,   259,  -467,  -467,  -467,  -467,  -467,
    -467,   519,   462,   519,   519,   130,   465,   475,   485,   487,
    -467,   519,   499,   115,   228,   300,   370,   372,   379,   381,
     309,   323,  -467,     9,     9,  -467,  -467,   453,   134,   458,
     461,   489,   110,   491,   461,   158,    67,  -467,   399,   514,
     461,   492,   516,  -467,   461,   482,   518,   160,   522,   528,
     525,   526,  -467,   199,   199,   199,   550,   551,   552,   553,
     331,   554,  -467,  -467,  -467,   199,   199,   199,   199,  -467,
    -467,    71,   147,   391,   531,   536,   508,   -27,   -23,  -467,
     527,  -467,   510,   412,  -467,   544,   111,   261,  -467,   530,
     190,   248,  -467,   532,    50,   501,   540,  -467,   534,   542,
     520,   537,  -467,   519,   519,   519,   429,   460,   483,   511,
     548,   555,  -467,   556,   332,   341,   395,   404,  -467,   455,
       4,   557,  -467,   147,  -467,  -467,  -467,  -467,   570,   571,
    -467,   461,  -467,   166,  -467,   541,   524,   529,  -467,   521,
     461,   461,   533,  -467,   260,   201,   535,   538,   539,   273,
     543,   545,  -467,   546,   547,   549,   558,   559,   560,   561,
     562,   563,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,    52,  -467,  -467,   199,   199,   152,   199,   565,
     577,  -467,  -467,   579,  -467,  -467,   566,   564,   567,   568,
     321,  -467,   569,   466,   573,  -467,   575,  -467,   544,  -467,
     572,   322,   574,   388,   576,  -467,  -467,   578,   580,   389,
      87,  -467,  -467,  -467,   581,   582,   583,   584,  -467,   585,
     587,   586,   588,   519,   519,   519,   519,   519,   519,   519,
     519,   468,   478,   593,   -18,   406,   415,  -467,   486,   519,
     590,  -467,   596,   600,   282,  -467,   521,   589,  -467,  -467,
     591,  -467,   592,  -467,   597,   599,   521,   521,  -467,   594,
    -467,  -467,   390,  -467,   595,  -467,   598,   601,  -467,   394,
    -467,   602,   603,  -467,   604,  -467,   461,  -467,   605,   199,
     199,    37,   606,   607,   199,   199,   167,   608,   577,   577,
     199,   199,   611,   573,  -467,  -467,  -467,  -467,  -467,  -467,
     575,  -467,  -467,   609,  -467,   612,  -467,  -467,   613,  -467,
    -467,  -467,   614,   615,  -467,   488,   519,   623,   625,   -16,
     626,   627,  -467,   343,   352,  -467,   496,   199,  -467,  -467,
     519,   519,   624,  -467,  -467,  -467,  -467,   616,   199,   620,
     617,   628,   607,   618,   622,   619,  -467,  -467,   621,   519,
     513,   629,   506,   630,    -8,   638,  -467,  -467,   515,  -467,
    -467,   641,  -467,   199,   199,   631,   199,    78,   664,   607,
     632,   622,   622,   257,   272,   634,   671,   519,   519,  -467,
     519,   653,   654,    -5,   655,  -467,  -467,  -467,  -467,   656,
     519,   657,   519,   517,  -467,   658,   679,   188,   681,   607,
     645,   622,   622,   683,   684,   199,   199,     8,   666,   667,
      12,   668,  -467,  -467,  -467,  -467,   669,   670,   519,   519,
     672,   673,   674,   690,   694,   695,   607,   659,   622,   622,
     697,   698,    42,   699,   700,   682,   685,   686,  -467,  -467,
    -467,  -467,  -467,  -467,   687,  -467,   688,  -467,   660,   702,
     675,   622,   622,   703,   -30,    16,   689,  -467,  -467,  -467,
     691,   692,  -467,  -467,  -467,   713,   607,   678,   622,   661,
     715,   701,  -467,   704,  -467,  -467,   705,   693,   622,   676,
     523,  -467,  -467,    69,   707,   622,   716,   607,   718,  -467,
     708,  -467,   709,   696,   622,   719,  -467,  -467,  -467,   622,
    -467
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,     0,     4,     1,     0,     0,     0,     0,     3,     0,
       7,    10,     8,    32,    33,    31,    38,    40,    42,    46,
      45,    48,    50,    44,    47,    49,     0,     0,     0,     0,
     174,     5,   172,    11,     9,    36,    39,    41,    34,    35,
      43,     0,     0,     0,   114,   131,   145,   146,     0,     0,
      24,    25,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    30,     0,     0,   176,     0,   173,    37,
       0,     0,     0,     0,   127,   147,   148,     0,     0,    17,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   222,   220,   219,
     277,     0,   175,   178,   180,   182,   184,   185,   186,   187,
     181,   143,     0,   149,   150,     0,     0,     0,     0,     0,
     132,    12,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    18,    13,    14,    15,    16,     0,    85,   177,
       0,   229,   227,   281,     0,   225,   223,   221,     0,     0,
       0,   279,     0,   278,     0,     0,     0,     0,     0,     0,
       0,     0,   183,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    19,    20,    21,     0,     0,     0,     0,    22,
      23,     0,     0,   211,     0,     0,   232,   236,   241,   228,
       0,   282,   188,   197,   200,   199,   234,   238,   226,     0,
     244,   230,   224,     0,   296,     0,     0,   280,     0,     0,
     283,     0,   179,   144,   155,   156,     0,     0,     0,     0,
       0,     0,   165,     0,     0,     0,     0,     0,    81,     0,
       0,     0,   116,   117,   120,   118,   133,   212,     0,     0,
     190,     0,   233,   255,   237,     0,   242,   312,   189,     0,
       0,     0,   249,   235,   252,   267,   239,   290,   304,   269,
     245,   247,   231,   300,   308,   297,     0,   191,   287,     0,
     284,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    26,    27,     0,     0,     0,     0,     0,
       0,   121,   119,   128,   213,   214,   203,   264,   322,   256,
     262,   243,   313,   215,   198,   206,   205,   202,   201,   209,
     250,   258,   253,   260,     0,   268,   240,   291,   305,   320,
     271,   270,   246,   248,   301,   309,   298,   316,   192,   288,
       0,   285,   293,   157,   158,   159,   160,   161,   162,   163,
     164,     0,     0,     0,    51,     0,     0,    82,     0,   151,
       0,   125,   122,     0,     0,   134,     0,   265,   323,   257,
     330,   263,   314,   216,     0,     0,     0,     0,   251,   326,
     259,   254,   273,   261,     0,   292,   306,   324,   321,   328,
     272,   302,   310,   299,   317,   289,     0,   286,   294,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   204,   266,   331,   315,   217,   218,   208,
     207,   210,   327,   334,   274,   275,   307,   325,   332,   329,
     303,   311,   318,     0,   295,     0,   167,     0,     0,    52,
      86,     0,    59,     0,     0,    83,     0,     0,   124,   123,
     168,   169,     0,   335,   276,   333,   319,   193,     0,     0,
       0,     0,     0,     0,     0,     0,    28,    29,     0,   152,
       0,   194,     0,     0,    53,    90,    61,    88,     0,    87,
     129,     0,    84,     0,     0,   195,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   126,     0,   170,   171,   196,
     166,     0,     0,    54,    92,    63,    94,    91,    89,   137,
     135,   138,   136,     0,   130,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      55,    98,    65,    96,    93,    95,   139,   140,   153,   154,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   100,    67,   102,
      99,    97,   141,   142,     0,    74,     0,    77,     0,     0,
       0,     0,     0,     0,     0,    56,     0,   104,   101,   103,
       0,     0,    72,    73,    76,     0,     0,     0,     0,     0,
       0,   106,    69,     0,   105,    75,     0,     0,     0,     0,
       0,   110,   107,    57,    78,     0,     0,     0,     0,   111,
     108,    71,    79,     0,     0,     0,   112,   109,    80,     0,
     113
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -467,  -467,  -467,  -467,  -467,  -467,   714,   -29,   722,   710,
      -3,  -467,   -10,    68,   720,  -467,  -467,  -467,  -467,  -467,
    -467,  -467,  -467,  -467,  -443,  -467,  -467,  -467,  -467,  -467,
    -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,
    -467,  -467,  -467,  -467,  -467,  -467,  -467,   351,  -467,   141,
    -466,  -467,   356,  -467,  -467,  -467,  -467,  -467,   706,   711,
    -467,  -467,  -467,  -467,  -467,  -467,   712,  -467,  -467,   507,
     447,  -467,   502,  -467,  -467,  -467,  -467,  -467,  -467,  -149,
     249,   358,   244,  -142,   175,  -467
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,     8,     9,    10,    11,    64,    12,    13,
      14,    15,    16,    17,    18,    19,    20,   393,   452,   479,
     509,   536,   576,   597,   432,    21,    22,    23,   454,   482,
     481,   511,   512,   539,   538,   561,   562,   578,   588,   604,
     595,   609,    24,    25,   182,   232,   233,   234,   352,   353,
     469,    44,   235,   485,    74,   293,   470,    45,    46,    47,
     236,   504,   120,   222,   355,    31,    32,    67,    96,   102,
     103,   104,   105,   106,   107,   108,   109,   192,   193,   184,
     304,   194,   305,   185,   306,   110
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      65,   206,   195,    36,   392,   209,   451,   243,   245,   466,
      35,   530,    39,   140,   478,   497,   498,   508,   141,    92,
      93,   142,   571,    79,   288,   244,   572,   573,    36,   246,
     289,   574,     3,    89,   535,    69,   495,   -58,   575,   -60,
     427,   111,    26,   113,   114,   524,   525,   -62,   121,   143,
     -64,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     531,   133,   134,   135,   136,   137,   522,   -66,   532,   115,
      27,   -68,   550,   551,    50,    51,   428,    52,    53,    54,
      55,   264,    37,    56,    57,    58,    59,    60,    61,   429,
     343,   596,    28,   548,   554,   568,   569,    62,   200,   296,
     555,   201,   265,    37,   344,    90,    91,    37,   308,   309,
      92,    93,   584,   116,   117,   118,   491,   492,   379,   202,
      90,    91,   592,   228,   -70,    92,    93,   132,    70,   599,
     493,    71,   119,   582,   213,   214,   215,    37,   607,   380,
      63,   187,   172,   610,   188,   252,   224,   225,   226,   227,
     164,   165,   229,   166,   601,    50,    51,    29,    52,    53,
      54,    55,   189,   253,    56,    57,    58,    59,    60,    61,
      50,    51,   190,    52,    53,    54,    55,    30,    62,    56,
      57,    58,    59,    60,    61,  -115,     6,   144,  -115,   196,
      48,    97,   197,    62,    98,    99,   145,   297,   230,   146,
     298,   231,    50,    51,   347,    52,    53,    54,    55,    49,
     198,    56,    57,    58,    59,    60,    61,   147,   299,   435,
     199,    63,   100,   101,   259,    62,   519,   148,   149,    41,
      42,    43,   313,    90,    91,   314,    63,   423,    92,    93,
     520,    72,   260,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   315,    73,   173,   345,   346,   348,   349,
      50,    51,    66,    52,    53,    54,    55,    42,    63,    56,
      57,    58,    59,    60,    61,    50,    51,    43,    52,    53,
      54,    55,   261,    62,    56,    57,    58,    59,    60,    61,
     158,   150,   254,   159,   311,   255,   151,    77,    62,   152,
     262,    78,   400,   401,   319,    90,    91,   320,   402,   499,
      92,    93,   312,   256,    90,    91,    80,   153,    -6,    92,
      93,   160,   161,   257,   501,   321,    63,   174,    90,    91,
       4,     5,     6,    92,    93,   112,   179,    90,    91,     7,
      81,    63,    92,    93,     5,     6,    90,    91,    90,    91,
     180,    92,    93,    92,    93,   360,   369,    90,    91,   283,
     425,   426,    92,    93,    82,   433,   434,   436,   284,   122,
     456,   440,   441,   361,   370,    90,    91,    90,    91,   457,
      92,    93,    92,    93,    90,    91,    90,    91,    83,    92,
      93,    92,    93,   175,   237,   176,   238,   239,   220,   221,
      90,    91,   177,    84,   178,    92,    93,   138,   459,    90,
      91,    90,    91,    85,    92,    93,    92,    93,   285,   462,
      90,    91,   372,   377,   413,    92,    93,   286,   418,   394,
     203,    90,    91,   204,   249,   250,    92,    93,   395,    86,
     373,   378,   414,    87,   487,   488,   419,   490,    94,   272,
     273,    90,    91,    88,   500,   502,    92,    93,    90,    91,
      90,    91,   154,    92,    93,    92,    93,   155,    95,   363,
     156,   364,   365,    90,    91,   181,   157,   287,    92,    93,
     274,   275,   163,    90,    91,   167,   528,   529,    92,    93,
     389,    90,    91,    90,    91,   168,    92,    93,    92,    93,
     390,    90,    91,   276,   277,   169,    92,    93,   396,   170,
     448,    90,    91,     4,     5,     6,    92,    93,   458,     5,
       6,   171,     7,   186,    90,    91,   183,     7,   476,    92,
      93,   278,   279,   473,   474,   483,   484,   515,   516,   438,
     439,   410,   411,   191,   207,   205,   210,   208,   140,   211,
     144,   150,   154,   216,   217,   218,   219,   223,   240,   241,
     242,   247,   248,   251,   258,   266,   263,   267,   268,   269,
     280,   271,   270,   294,   295,   300,   301,   281,   282,   290,
     351,   302,   354,   594,   291,   310,   303,   316,   356,   292,
     317,   318,   327,   350,   367,   322,   366,   323,   324,   325,
     407,   326,   408,   139,   212,   403,   162,   374,   307,   430,
     409,   328,   329,   386,   331,   391,   357,   397,   398,   358,
     359,   362,   399,   463,   368,   330,   371,   332,   437,   415,
     375,   465,   376,   381,   382,   383,   384,   385,   387,   442,
     388,   404,   447,   405,   406,   449,   412,   450,   453,   455,
     416,   460,   477,   417,   420,   421,   422,   424,   467,   468,
     480,   443,   431,   486,   444,   445,   446,   494,   461,   464,
     503,   471,   496,   472,   505,   506,   507,   510,   513,   514,
     517,   475,   518,   489,   521,   523,   526,   527,   533,   534,
     537,   540,   541,   545,   542,   543,   544,   546,   547,   549,
     552,   553,   556,   557,   558,   566,   570,   559,   560,   563,
     564,   577,   565,   579,   580,   567,   581,   583,   586,   600,
     585,   602,   608,   587,    33,    38,   589,   590,   593,   598,
     603,   605,    34,   591,     0,    40,   606,     0,     0,     0,
       0,     0,     0,    68,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    76,     0,     0,     0,    75
};

static const yytype_int16 yycheck[] =
{
      29,   150,   144,    13,    22,   154,    22,    34,    31,   452,
      13,     3,    15,    26,    22,   481,   482,    22,    31,    10,
      11,    34,    52,    52,    20,    52,    56,    57,    38,    52,
      26,    61,     0,    62,    22,    38,   479,    55,    22,    55,
       3,    70,    22,    72,    73,   511,   512,    55,    77,    62,
      55,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      52,    90,    91,    92,    93,    94,   509,    55,    60,     3,
      22,    55,   538,   539,     3,     4,    39,     6,     7,     8,
       9,    31,    14,    12,    13,    14,    15,    16,    17,    52,
      38,    22,    22,   536,    52,   561,   562,    26,    31,   241,
      58,    34,    52,    35,    52,     5,     6,    39,   250,   251,
      10,    11,   578,    47,    48,    49,    38,    39,    31,    52,
       5,     6,   588,    52,    55,    10,    11,    27,    20,   595,
      52,    23,    66,   576,   163,   164,   165,    69,   604,    52,
      69,    31,    27,   609,    34,    34,   175,   176,   177,   178,
      20,    21,   181,    23,   597,     3,     4,    22,     6,     7,
       8,     9,    52,    52,    12,    13,    14,    15,    16,    17,
       3,     4,    62,     6,     7,     8,     9,    29,    26,    12,
      13,    14,    15,    16,    17,    51,    43,    22,    54,    31,
      69,    31,    34,    26,    34,    35,    31,    31,    51,    34,
      34,    54,     3,     4,    52,     6,     7,     8,     9,     3,
      52,    12,    13,    14,    15,    16,    17,    52,    52,    52,
      62,    69,    62,    63,    34,    26,    38,    62,    63,    44,
      45,    46,    31,     5,     6,    34,    69,   386,    10,    11,
      52,    20,    52,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,    52,    20,    27,   285,   286,   287,   288,
       3,     4,    53,     6,     7,     8,     9,    45,    69,    12,
      13,    14,    15,    16,    17,     3,     4,    46,     6,     7,
       8,     9,    34,    26,    12,    13,    14,    15,    16,    17,
      31,    26,    31,    34,    34,    34,    31,    22,    26,    34,
      52,    22,    20,    21,    31,     5,     6,    34,    26,    52,
      10,    11,    52,    52,     5,     6,    26,    52,    29,    10,
      11,    62,    63,    62,    52,    52,    69,    27,     5,     6,
      41,    42,    43,    10,    11,    44,    27,     5,     6,    50,
      26,    69,    10,    11,    42,    43,     5,     6,     5,     6,
      27,    10,    11,    10,    11,    34,    34,     5,     6,    27,
     389,   390,    10,    11,    26,   394,   395,   396,    27,     3,
      27,   400,   401,    52,    52,     5,     6,     5,     6,    27,
      10,    11,    10,    11,     5,     6,     5,     6,    26,    10,
      11,    10,    11,    23,     3,    23,     5,     6,    67,    68,
       5,     6,    23,    26,    23,    10,    11,    53,   437,     5,
       6,     5,     6,    26,    10,    11,    10,    11,    23,   448,
       5,     6,    34,    34,    34,    10,    11,    23,    34,    23,
      31,     5,     6,    34,    22,    23,    10,    11,    23,    26,
      52,    52,    52,    26,   473,   474,    52,   476,    22,    20,
      21,     5,     6,    26,   483,   484,    10,    11,     5,     6,
       5,     6,    26,    10,    11,    10,    11,    31,    22,     3,
      34,     5,     6,     5,     6,    22,    18,    22,    10,    11,
      20,    21,    20,     5,     6,    20,   515,   516,    10,    11,
      22,     5,     6,     5,     6,    20,    10,    11,    10,    11,
      22,     5,     6,    20,    21,    20,    10,    11,    22,    22,
      22,     5,     6,    41,    42,    43,    10,    11,    22,    42,
      43,    22,    50,    34,     5,     6,    65,    50,    22,    10,
      11,    20,    21,    20,    21,    20,    21,    20,    21,   398,
     399,   366,   367,    52,    52,    31,    64,    31,    26,    31,
      22,    26,    26,     3,     3,     3,     3,     3,    27,    23,
      52,    34,    52,    19,    34,    64,    34,    27,    34,    27,
      22,    34,    52,     3,     3,    34,    52,    22,    22,    22,
       3,    52,     3,    60,   233,    52,    65,    52,    22,   233,
      52,    52,    34,    28,    19,    52,    23,    52,    52,    52,
       3,    52,     3,    96,   157,   356,   104,    31,   250,     3,
     366,    52,    52,    26,    52,    22,    52,    27,    22,    52,
      52,    52,    22,     3,    52,    64,    52,    64,    20,    34,
      52,     3,    52,    52,    52,    52,    52,    52,    52,    28,
      52,    52,    27,    52,    52,    22,    52,    22,    22,    22,
      52,    27,    22,    52,    52,    52,    52,    52,    40,    37,
      22,    52,    55,    22,    52,    52,    52,     3,    52,    52,
      36,    52,    40,    52,     3,    22,    22,    22,    22,    22,
      22,    52,     3,    52,     3,    40,     3,     3,    22,    22,
      22,    22,    22,     3,    22,    22,    22,     3,     3,    40,
       3,     3,     3,     3,    22,     3,     3,    22,    22,    22,
      22,    22,    52,    22,    22,    40,     3,    39,     3,     3,
      59,     3,     3,    22,    10,    15,    22,    22,    52,    22,
      22,    22,    10,    40,    -1,    15,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    46
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    72,    73,     0,    41,    42,    43,    50,    74,    75,
      76,    77,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    96,    97,    98,   113,   114,    22,    22,    22,    22,
      29,   136,   137,    77,    79,    81,    83,    84,    80,    81,
      85,    44,    45,    46,   122,   128,   129,   130,    69,     3,
       3,     4,     6,     7,     8,     9,    12,    13,    14,    15,
      16,    17,    26,    69,    78,    78,    53,   138,   137,    81,
      20,    23,    20,    20,   125,   130,   129,    22,    22,    78,
      26,    26,    26,    26,    26,    26,    26,    26,    26,    78,
       5,     6,    10,    11,    22,    22,   139,    31,    34,    35,
      62,    63,   140,   141,   142,   143,   144,   145,   146,   147,
     156,    78,    44,    78,    78,     3,    47,    48,    49,    66,
     133,    78,     3,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    27,    78,    78,    78,    78,    78,    53,   140,
      26,    31,    34,    62,    22,    31,    34,    52,    62,    63,
      26,    31,    34,    52,    26,    31,    34,    18,    31,    34,
      62,    63,   143,    20,    20,    21,    23,    20,    20,    20,
      22,    22,    27,    27,    27,    23,    23,    23,    23,    27,
      27,    22,   115,    65,   150,   154,    34,    31,    34,    52,
      62,    52,   148,   149,   152,   154,    31,    34,    52,    62,
      31,    34,    52,    31,    34,    31,   150,    52,    31,   150,
      64,    31,   141,    78,    78,    78,     3,     3,     3,     3,
      67,    68,   134,     3,    78,    78,    78,    78,    52,    78,
      51,    54,   116,   117,   118,   123,   131,     3,     5,     6,
      27,    23,    52,    34,    52,    31,    52,    34,    52,    22,
      23,    19,    34,    52,    31,    34,    52,    62,    34,    34,
      52,    34,    52,    34,    31,    52,    64,    27,    34,    27,
      52,    34,    20,    21,    20,    21,    20,    21,    20,    21,
      22,    22,    22,    27,    27,    23,    23,    22,    20,    26,
      22,   118,   123,   126,     3,     3,   154,    31,    34,    52,
      34,    52,    52,    65,   151,   153,   155,   152,   154,   154,
      52,    34,    52,    31,    34,    52,    52,    52,    52,    31,
      34,    52,    52,    52,    52,    52,    52,    34,    52,    52,
      64,    52,    64,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    38,    52,    78,    78,    52,    78,    78,
      28,     3,   119,   120,     3,   135,    22,    52,    52,    52,
      34,    52,    52,     3,     5,     6,    23,    19,    52,    34,
      52,    52,    34,    52,    31,    52,    52,    34,    52,    31,
      52,    52,    52,    52,    52,    52,    26,    52,    52,    22,
      22,    22,    22,    88,    23,    23,    22,    27,    22,    22,
      20,    21,    26,   151,    52,    52,    52,     3,     3,   153,
     155,   155,    52,    34,    52,    34,    52,    52,    34,    52,
      52,    52,    52,   150,    52,    78,    78,     3,    39,    52,
       3,    55,    95,    78,    78,    52,    78,    20,   120,   120,
      78,    78,    28,    52,    52,    52,    52,    27,    22,    22,
      22,    22,    89,    22,    99,    22,    27,    27,    22,    78,
      27,    52,    78,     3,    52,     3,    95,    40,    37,   121,
     127,    52,    52,    20,    21,    52,    22,    22,    22,    90,
      22,   101,   100,    20,    21,   124,    22,    78,    78,    52,
      78,    38,    39,    52,     3,    95,    40,   121,   121,    52,
      78,    52,    78,    36,   132,     3,    22,    22,    22,    91,
      22,   102,   103,    22,    22,    20,    21,    22,     3,    38,
      52,     3,    95,    40,   121,   121,     3,     3,    78,    78,
       3,    52,    60,    22,    22,    22,    92,    22,   105,   104,
      22,    22,    22,    22,    22,     3,     3,     3,    95,    40,
     121,   121,     3,     3,    52,    58,     3,     3,    22,    22,
      22,   106,   107,    22,    22,    52,     3,    40,   121,   121,
       3,    52,    56,    57,    61,    22,    93,    22,   108,    22,
      22,     3,    95,    39,   121,    59,     3,    22,   109,    22,
      22,    40,   121,    52,    60,   111,    22,    94,    22,   121,
       3,    95,     3,    22,   110,    22,    40,   121,     3,   112,
     121
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    71,    73,    72,    74,    74,    75,    75,    75,    75,
      76,    76,    77,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    79,    79,    79,    79,    79,    79,    79,    80,    80,
      81,    81,    82,    82,    83,    83,    83,    84,    84,    85,
      85,    86,    86,    86,    86,    86,    86,    86,    88,    87,
      89,    87,    90,    87,    91,    87,    92,    87,    93,    87,
      94,    87,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    96,    96,    96,    96,    97,    99,    98,   100,    98,
     101,    98,   102,    98,   103,    98,   104,    98,   105,    98,
     106,    98,   107,    98,   108,    98,   109,    98,   110,    98,
     111,    98,   112,    98,   113,   115,   114,   116,   116,   116,
     117,   117,   118,   119,   119,   120,   121,   122,   123,   124,
     124,   125,   125,   126,   126,   127,   127,   127,   127,   127,
     127,   127,   127,   128,   128,   128,   128,   128,   128,   129,
     130,   131,   131,   132,   132,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   134,   134,   135,   135,
     135,   135,   136,   136,   138,   137,   139,   137,   140,   140,
     141,   141,   142,   142,   143,   143,   143,   143,   144,   144,
     145,   146,   146,   147,   147,   147,   147,   148,   148,   149,
     149,   149,   149,   150,   150,   151,   151,   151,   151,   152,
     153,   154,   154,   154,   154,   155,   155,   155,   155,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     0,     2,     0,     1,     1,     2,
       1,     2,     5,     3,     3,     3,     3,     2,     3,     4,
       4,     4,     4,     4,     1,     1,     6,     6,    10,    10,
       1,     1,     1,     1,     2,     2,     2,     3,     1,     2,
       1,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     9,    11,    13,    15,    17,    21,    25,     0,    11,
       0,    13,     0,    15,     0,    17,     0,    19,     0,    23,
       0,    27,    11,    11,     9,    13,    11,     9,    15,    17,
      19,     7,     9,    11,    13,     5,     0,    13,     0,    15,
       0,    15,     0,    17,     0,    17,     0,    19,     0,    19,
       0,    21,     0,    21,     0,    23,     0,    25,     0,    29,
       0,    27,     0,    31,     2,     0,     7,     1,     1,     2,
       1,     2,     3,     3,     3,     1,     2,     2,     2,     0,
       2,     0,     2,     0,     2,     3,     3,     3,     3,     5,
       5,     7,     7,     3,     5,     1,     1,     2,     2,     3,
       3,     3,     6,     3,     3,     3,     3,     5,     5,     5,
       5,     5,     5,     5,     5,     3,     9,     5,     3,     3,
       6,     6,     1,     2,     0,     3,     0,     4,     1,     3,
       1,     1,     1,     2,     1,     1,     1,     1,     3,     4,
       4,     4,     5,     8,     9,    10,    11,     1,     3,     1,
       1,     3,     3,     3,     5,     1,     1,     3,     3,     3,
       3,     1,     2,     3,     3,     1,     2,     3,     3,     1,
       1,     2,     1,     2,     3,     2,     3,     2,     3,     2,
       3,     4,     3,     4,     3,     4,     3,     4,     3,     4,
       5,     3,     4,     5,     3,     4,     5,     4,     5,     4,
       5,     6,     4,     5,     6,     4,     5,     6,     5,     6,
       5,     6,     5,     6,     5,     6,     7,     4,     5,     4,
       5,     5,     6,     6,     7,     7,     8,     1,     2,     2,
       3,     2,     3,     3,     4,     5,     6,     4,     5,     6,
       4,     5,     6,     5,     6,     7,     3,     4,     5,     6,
       4,     5,     6,     7,     4,     5,     6,     7,     4,     5,
       6,     7,     4,     5,     6,     7,     5,     6,     7,     8,
       5,     6,     5,     6,     6,     7,     6,     7,     6,     7,
       6,     7,     7,     8,     7,     8
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
        yyerror (yyparse_param, YY_("syntax error: cannot back up")); \
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
                  Kind, Value, yyparse_param); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *yyparse_param)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yyparse_param);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *yyparse_param)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, yyparse_param);
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
                 int yyrule, void *yyparse_param)
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
                       &yyvsp[(yyi + 1) - (yynrhs)], yyparse_param);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, yyparse_param); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *yyparse_param)
{
  YY_USE (yyvaluep);
  YY_USE (yyparse_param);
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
yyparse (void *yyparse_param)
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
  case 2: /* $@1: %empty  */
#line 276 "grm_parsegrammar.y"
{  
if (((struct yyparse_s *)yyparse_param)->verbose) printf("\nCREATE GRAMMAR\n");  
}
#line 1900 "grm_parsegrammar.tab.c"
    break;

  case 3: /* start: $@1 rna_grammar  */
#line 280 "grm_parsegrammar.y"
{  
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("END_GRAMMAR\n\n"); 
  if (((struct yyparse_s *)yyparse_param)->verbose) printf ("#n-parameters: %d \n", nparam); 
  if (((struct yyparse_s *)yyparse_param)->verbose) { 
    for (p =0; p < nparam; p++) 
      if (param[p].used == FALSE) printf ("#parameter[%d]: %s=%f NOT USED\n", p, param[p].name, param[p].value); 
  } 
}
#line 1913 "grm_parsegrammar.tab.c"
    break;

  case 12: /* param_decl: PARAM_DECL SEP PARAM_NAME SEP expression  */
#line 314 "grm_parsegrammar.y"
{ 
  (yyvsp[-2].param)->value = (yyvsp[0].dval); 
  (yyvsp[-2].param)->used  = FALSE; 
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("param[%d] %s=%f\n", nparam, (yyvsp[-2].param)->name, (yyvsp[-2].param)->value); 
  nparam ++; 
}
#line 1924 "grm_parsegrammar.tab.c"
    break;

  case 13: /* expression: expression PLUS expression  */
#line 327 "grm_parsegrammar.y"
                                               { (yyval.dval) = (yyvsp[-2].dval) + (yyvsp[0].dval);  }
#line 1930 "grm_parsegrammar.tab.c"
    break;

  case 14: /* expression: expression MINUS expression  */
#line 328 "grm_parsegrammar.y"
                                               { (yyval.dval) = (yyvsp[-2].dval) - (yyvsp[0].dval);  }
#line 1936 "grm_parsegrammar.tab.c"
    break;

  case 15: /* expression: expression MULTIPLY expression  */
#line 329 "grm_parsegrammar.y"
                                               { (yyval.dval) = (yyvsp[-2].dval) * (yyvsp[0].dval);  }
#line 1942 "grm_parsegrammar.tab.c"
    break;

  case 16: /* expression: expression DIVIDE expression  */
#line 330 "grm_parsegrammar.y"
                                               { if ((yyvsp[0].dval) == 0.0) { grammar_fatal("divide by zero"); } else { (yyval.dval) = (yyvsp[-2].dval) / (yyvsp[0].dval); } }
#line 1948 "grm_parsegrammar.tab.c"
    break;

  case 17: /* expression: MINUS expression  */
#line 331 "grm_parsegrammar.y"
                                               { (yyval.dval) = -(yyvsp[0].dval);      }
#line 1954 "grm_parsegrammar.tab.c"
    break;

  case 18: /* expression: OPEN expression CLOSE  */
#line 332 "grm_parsegrammar.y"
                                               { (yyval.dval) = (yyvsp[-1].dval);       }
#line 1960 "grm_parsegrammar.tab.c"
    break;

  case 19: /* expression: SQRT OPEN expression CLOSE  */
#line 333 "grm_parsegrammar.y"
                                               { (yyval.dval) = sqrt((yyvsp[-1].dval)); }
#line 1966 "grm_parsegrammar.tab.c"
    break;

  case 20: /* expression: LOG OPEN expression CLOSE  */
#line 334 "grm_parsegrammar.y"
                                               { (yyval.dval) = log((yyvsp[-1].dval));  }
#line 1972 "grm_parsegrammar.tab.c"
    break;

  case 21: /* expression: EXP OPEN expression CLOSE  */
#line 335 "grm_parsegrammar.y"
                                               { (yyval.dval) = exp((yyvsp[-1].dval));  }
#line 1978 "grm_parsegrammar.tab.c"
    break;

  case 22: /* expression: SIN OPEN expression CLOSE  */
#line 336 "grm_parsegrammar.y"
                                               { (yyval.dval) = sin((yyvsp[-1].dval));  }
#line 1984 "grm_parsegrammar.tab.c"
    break;

  case 23: /* expression: COS OPEN expression CLOSE  */
#line 337 "grm_parsegrammar.y"
                                               { (yyval.dval) = cos((yyvsp[-1].dval));  }
#line 1990 "grm_parsegrammar.tab.c"
    break;

  case 24: /* expression: INTEGER  */
#line 338 "grm_parsegrammar.y"
                                               { (yyval.dval) = atof((yyvsp[0].string)); }
#line 1996 "grm_parsegrammar.tab.c"
    break;

  case 25: /* expression: REAL  */
#line 339 "grm_parsegrammar.y"
                                               { (yyval.dval) = atof((yyvsp[0].string)); }
#line 2002 "grm_parsegrammar.tab.c"
    break;

  case 26: /* expression: MAX OPEN expression COMMA expression CLOSE  */
#line 340 "grm_parsegrammar.y"
                                                                                       { (yyval.dval) = ((yyvsp[-3].dval) > (yyvsp[-1].dval))? (yyvsp[-3].dval) : (yyvsp[-1].dval); }
#line 2008 "grm_parsegrammar.tab.c"
    break;

  case 27: /* expression: MIN OPEN expression COMMA expression CLOSE  */
#line 341 "grm_parsegrammar.y"
                                                                                       { (yyval.dval) = ((yyvsp[-3].dval) > (yyvsp[-1].dval))? (yyvsp[-1].dval) : (yyvsp[-3].dval); }
#line 2014 "grm_parsegrammar.tab.c"
    break;

  case 28: /* expression: MAXCOND OPEN expression COMMA expression COMMA expression COMMA expression CLOSE  */
#line 342 "grm_parsegrammar.y"
                                                                                       { (yyval.dval) = ((yyvsp[-7].dval) > (yyvsp[-5].dval))? (yyvsp[-3].dval) : (yyvsp[-1].dval); }
#line 2020 "grm_parsegrammar.tab.c"
    break;

  case 29: /* expression: MINCOND OPEN expression COMMA expression COMMA expression COMMA expression CLOSE  */
#line 343 "grm_parsegrammar.y"
                                                                                       { (yyval.dval) = ((yyvsp[-7].dval) < (yyvsp[-5].dval))? (yyvsp[-3].dval) : (yyvsp[-1].dval); }
#line 2026 "grm_parsegrammar.tab.c"
    break;

  case 30: /* expression: PARAM_NAME  */
#line 344 "grm_parsegrammar.y"
                                               { if (isnan((yyvsp[0].param)->value)) grammar_fatal("param %s value is nan", (yyvsp[0].param)->name); else { (yyval.dval) = (yyvsp[0].param)->value; (yyvsp[0].param)->used = TRUE; } }
#line 2032 "grm_parsegrammar.tab.c"
    break;

  case 51: /* edist_decl_only: EDIST_DECL SEP INTEGER SEP INTEGER SEP INTEGER SEP DIST_NAME  */
#line 383 "grm_parsegrammar.y"
{ 
  rna_edist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[0].string), atoi((yyvsp[-6].string)), atoi((yyvsp[-4].string)), atoi((yyvsp[-2].string)), "", 0, 1, FALSE, "", -1, -1, FALSE, ((struct yyparse_s *)yyparse_param)->verbose);  
}
#line 2040 "grm_parsegrammar.tab.c"
    break;

  case 52: /* edist_decl_only: EDIST_DECL SEP INTEGER SEP INTEGER SEP INTEGER SEP BPTYPE SEP DIST_NAME  */
#line 389 "grm_parsegrammar.y"
{ 
  rna_edist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[0].string), atoi((yyvsp[-8].string)), atoi((yyvsp[-6].string)), atoi((yyvsp[-4].string)), (yyvsp[-2].string), 0, 1, FALSE, "", -1, -1, FALSE, ((struct yyparse_s *)yyparse_param)->verbose);  
}
#line 2048 "grm_parsegrammar.tab.c"
    break;

  case 53: /* edist_decl_only: EDIST_DECL SEP INTEGER SEP INTEGER SEP INTEGER SEP BPTYPE SEP FORCEWC SEP DIST_NAME  */
#line 395 "grm_parsegrammar.y"
{ 
  rna_edist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[0].string), atoi((yyvsp[-10].string)), atoi((yyvsp[-8].string)), atoi((yyvsp[-6].string)), (yyvsp[-4].string), 0, 1, TRUE, "", -1, -1, FALSE, ((struct yyparse_s *)yyparse_param)->verbose);  
}
#line 2056 "grm_parsegrammar.tab.c"
    break;

  case 54: /* edist_decl_only: EDIST_DECL SEP INTEGER SEP INTEGER SEP INTEGER SEP BPTYPE SEP INTEGER SEP INTEGER SEP DIST_NAME  */
#line 401 "grm_parsegrammar.y"
{ 
  rna_edist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[0].string), atoi((yyvsp[-12].string)), atoi((yyvsp[-10].string)), atoi((yyvsp[-8].string)), (yyvsp[-6].string), atoi((yyvsp[-4].string)), atoi((yyvsp[-2].string)), FALSE, "", -1, -1, FALSE, ((struct yyparse_s *)yyparse_param)->verbose);  
}
#line 2064 "grm_parsegrammar.tab.c"
    break;

  case 55: /* edist_decl_only: EDIST_DECL SEP INTEGER SEP INTEGER SEP INTEGER SEP BPTYPE SEP INTEGER SEP INTEGER SEP FORCEWC SEP DIST_NAME  */
#line 407 "grm_parsegrammar.y"
{ 
  rna_edist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[0].string), atoi((yyvsp[-14].string)), atoi((yyvsp[-12].string)), atoi((yyvsp[-10].string)), (yyvsp[-8].string), atoi((yyvsp[-6].string)), atoi((yyvsp[-4].string)), TRUE, "", -1, -1, FALSE, ((struct yyparse_s *)yyparse_param)->verbose);  
}
#line 2072 "grm_parsegrammar.tab.c"
    break;

  case 56: /* edist_decl_only: EDIST_DECL SEP INTEGER SEP INTEGER SEP INTEGER SEP BPTYPE SEP INTEGER SEP INTEGER SEP BPTYPE SEP INTEGER SEP INTEGER SEP DIST_NAME  */
#line 413 "grm_parsegrammar.y"
{ 
  rna_edist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[0].string), atoi((yyvsp[-18].string)), atoi((yyvsp[-16].string)), atoi((yyvsp[-14].string)), (yyvsp[-12].string), atoi((yyvsp[-10].string)), atoi((yyvsp[-8].string)), FALSE, (yyvsp[-6].string), atoi((yyvsp[-4].string)), atoi((yyvsp[-2].string)), FALSE, ((struct yyparse_s *)yyparse_param)->verbose);  
}
#line 2080 "grm_parsegrammar.tab.c"
    break;

  case 57: /* edist_decl_only: EDIST_DECL SEP INTEGER SEP INTEGER SEP INTEGER SEP BPTYPE SEP INTEGER SEP INTEGER SEP FORCEWC SEP BPTYPE SEP INTEGER SEP INTEGER SEP FORCEWC SEP DIST_NAME  */
#line 419 "grm_parsegrammar.y"
{ 
  rna_edist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[0].string), atoi((yyvsp[-22].string)), atoi((yyvsp[-20].string)), atoi((yyvsp[-18].string)), (yyvsp[-16].string), atoi((yyvsp[-14].string)), atoi((yyvsp[-12].string)), TRUE, (yyvsp[-8].string), atoi((yyvsp[-6].string)), atoi((yyvsp[-4].string)), TRUE, ((struct yyparse_s *)yyparse_param)->verbose);  
}
#line 2088 "grm_parsegrammar.tab.c"
    break;

  case 58: /* $@2: %empty  */
#line 428 "grm_parsegrammar.y"
{ 
  rna_edist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[0].string), atoi((yyvsp[-6].string)), atoi((yyvsp[-4].string)), atoi((yyvsp[-2].string)), "", 0, 1, FALSE, "", -1, -1, FALSE, ((struct yyparse_s *)yyparse_param)->verbose);  
}
#line 2096 "grm_parsegrammar.tab.c"
    break;

  case 60: /* $@3: %empty  */
#line 435 "grm_parsegrammar.y"
{ 
  rna_edist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[0].string), atoi((yyvsp[-8].string)), atoi((yyvsp[-6].string)), atoi((yyvsp[-4].string)), (yyvsp[-2].string), 0, 1, FALSE, "", -1, -1, FALSE, ((struct yyparse_s *)yyparse_param)->verbose);  
}
#line 2104 "grm_parsegrammar.tab.c"
    break;

  case 62: /* $@4: %empty  */
#line 442 "grm_parsegrammar.y"
{ 
  rna_edist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[0].string), atoi((yyvsp[-10].string)), atoi((yyvsp[-8].string)), atoi((yyvsp[-6].string)), (yyvsp[-4].string), 0, 1, TRUE, "", -1, -1, FALSE, ((struct yyparse_s *)yyparse_param)->verbose);  
}
#line 2112 "grm_parsegrammar.tab.c"
    break;

  case 64: /* $@5: %empty  */
#line 449 "grm_parsegrammar.y"
{ 
  rna_edist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[0].string), atoi((yyvsp[-12].string)), atoi((yyvsp[-10].string)), atoi((yyvsp[-8].string)), (yyvsp[-6].string), atoi((yyvsp[-4].string)), atoi((yyvsp[-2].string)), FALSE, "", -1, -1, FALSE, ((struct yyparse_s *)yyparse_param)->verbose);  
}
#line 2120 "grm_parsegrammar.tab.c"
    break;

  case 66: /* $@6: %empty  */
#line 456 "grm_parsegrammar.y"
{ 
  rna_edist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[0].string), atoi((yyvsp[-14].string)), atoi((yyvsp[-12].string)), atoi((yyvsp[-10].string)), (yyvsp[-8].string), atoi((yyvsp[-6].string)), atoi((yyvsp[-4].string)), TRUE, "", -1, -1, FALSE, ((struct yyparse_s *)yyparse_param)->verbose);  
}
#line 2128 "grm_parsegrammar.tab.c"
    break;

  case 68: /* $@7: %empty  */
#line 463 "grm_parsegrammar.y"
{ 
  rna_edist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[0].string), atoi((yyvsp[-18].string)), atoi((yyvsp[-16].string)), atoi((yyvsp[-14].string)), (yyvsp[-12].string), atoi((yyvsp[-10].string)), atoi((yyvsp[-8].string)), FALSE, (yyvsp[-6].string), atoi((yyvsp[-4].string)), atoi((yyvsp[-2].string)), FALSE, ((struct yyparse_s *)yyparse_param)->verbose);  
}
#line 2136 "grm_parsegrammar.tab.c"
    break;

  case 70: /* $@8: %empty  */
#line 470 "grm_parsegrammar.y"
{ 
  rna_edist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[0].string), atoi((yyvsp[-22].string)), atoi((yyvsp[-20].string)), atoi((yyvsp[-18].string)), (yyvsp[-16].string), atoi((yyvsp[-14].string)), atoi((yyvsp[-12].string)), TRUE, (yyvsp[-10].string), atoi((yyvsp[-6].string)), atoi((yyvsp[-4].string)), TRUE, ((struct yyparse_s *)yyparse_param)->verbose);  
}
#line 2144 "grm_parsegrammar.tab.c"
    break;

  case 72: /* edist_tied: ETIED SEP DIST_NAME SEP INTEGER SEP DIST_NAME SEP INTEGER SEP JOINT  */
#line 483 "grm_parsegrammar.y"
{  
  rna_edist_declare_tied_joint(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-8].string), atoi((yyvsp[-6].string)), (yyvsp[-4].string), atoi((yyvsp[-2].string)), (yyvsp[0].string), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2152 "grm_parsegrammar.tab.c"
    break;

  case 73: /* edist_tied: ETIED SEP DIST_NAME SEP INTEGER SEP DIST_NAME SEP INTEGER SEP BAYES  */
#line 492 "grm_parsegrammar.y"
{  
  rna_edist_declare_tied_bayes(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-8].string), atoi((yyvsp[-6].string)), (yyvsp[-4].string), atoi((yyvsp[-2].string)), (yyvsp[0].string), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2160 "grm_parsegrammar.tab.c"
    break;

  case 74: /* edist_tied: ETIED SEP DIST_NAME SEP INTEGER SEP INTEGER SEP MARGINAL  */
#line 507 "grm_parsegrammar.y"
{  
  rna_edist_declare_tied_marginal(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-6].string), atoi((yyvsp[-4].string)), atoi((yyvsp[-2].string)), (yyvsp[0].string), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2168 "grm_parsegrammar.tab.c"
    break;

  case 75: /* edist_tied: ETIED SEP DIST_NAME SEP INTEGER SEP INTEGER SEP DIST_NAME SEP INTEGER SEP CONDITIONAL  */
#line 515 "grm_parsegrammar.y"
{  
  rna_edist_declare_tied_conditional(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-10].string), atoi((yyvsp[-8].string)), atoi((yyvsp[-6].string)), (yyvsp[-4].string), atoi((yyvsp[-2].string)), (yyvsp[0].string), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2176 "grm_parsegrammar.tab.c"
    break;

  case 76: /* edist_tied: ETIED SEP DIST_NAME SEP INTEGER SEP DIST_NAME SEP INTEGER SEP CONDMARG  */
#line 521 "grm_parsegrammar.y"
{  
  rna_edist_declare_tied_condmarg(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-8].string), atoi((yyvsp[-6].string)), (yyvsp[-4].string), atoi((yyvsp[-2].string)), (yyvsp[0].string), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2184 "grm_parsegrammar.tab.c"
    break;

  case 77: /* edist_tied: ETIED SEP DIST_NAME SEP INTEGER SEP ROTATE SEP INTEGER  */
#line 527 "grm_parsegrammar.y"
{  
  rna_edist_declare_tied_rotate_simple(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-6].string), atoi((yyvsp[-4].string)), (yyvsp[-2].string), atoi((yyvsp[0].string)), ((struct yyparse_s *)yyparse_param)->verbose);
}
#line 2192 "grm_parsegrammar.tab.c"
    break;

  case 78: /* edist_tied: ETIED SEP DIST_NAME SEP INTEGER SEP DIST_NAME SEP INTEGER SEP DIST_NAME SEP INTEGER SEP ROTATE  */
#line 533 "grm_parsegrammar.y"
{ 
  rna_edist_declare_tied_rotate_context(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-12].string), atoi((yyvsp[-10].string)), (yyvsp[-8].string), atoi((yyvsp[-6].string)), (yyvsp[-4].string), atoi((yyvsp[-2].string)), (yyvsp[0].string), -1, -1, ((struct yyparse_s *)yyparse_param)->verbose);
}
#line 2200 "grm_parsegrammar.tab.c"
    break;

  case 79: /* edist_tied: ETIED SEP DIST_NAME SEP INTEGER SEP DIST_NAME SEP INTEGER SEP DIST_NAME SEP INTEGER SEP ROTATE SEP INTEGER  */
#line 539 "grm_parsegrammar.y"
{ 
  rna_edist_declare_tied_rotate_context(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-14].string), atoi((yyvsp[-12].string)), (yyvsp[-10].string), atoi((yyvsp[-8].string)), (yyvsp[-6].string), atoi((yyvsp[-4].string)), (yyvsp[-2].string), atoi((yyvsp[0].string)), -1, ((struct yyparse_s *)yyparse_param)->verbose);
}
#line 2208 "grm_parsegrammar.tab.c"
    break;

  case 80: /* edist_tied: ETIED SEP DIST_NAME SEP INTEGER SEP DIST_NAME SEP INTEGER SEP DIST_NAME SEP INTEGER SEP ROTATE SEP INTEGER SEP INTEGER  */
#line 545 "grm_parsegrammar.y"
{ 
  rna_edist_declare_tied_rotate_context(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-16].string), atoi((yyvsp[-14].string)), (yyvsp[-12].string), atoi((yyvsp[-10].string)), (yyvsp[-8].string), atoi((yyvsp[-6].string)), (yyvsp[-4].string), atoi((yyvsp[-2].string)), atoi((yyvsp[0].string)), ((struct yyparse_s *)yyparse_param)->verbose);
}
#line 2216 "grm_parsegrammar.tab.c"
    break;

  case 81: /* ldist_decl_only: LDIST_DECL SEP expression SEP expression SEP DIST_NAME  */
#line 553 "grm_parsegrammar.y"
{
  rna_ldist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-6].string), (yyvsp[0].string), (int)((yyvsp[-4].dval)), (int)((yyvsp[-2].dval)), (int)((yyvsp[-2].dval)), 0, 0, ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2224 "grm_parsegrammar.tab.c"
    break;

  case 82: /* ldist_decl_only: LDIST_DECL SEP expression SEP expression SEP expression SEP DIST_NAME  */
#line 558 "grm_parsegrammar.y"
{
  rna_ldist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-8].string), (yyvsp[0].string), (int)((yyvsp[-6].dval)), (int)((yyvsp[-4].dval)), (int)((yyvsp[-2].dval)), 0, 0, ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2232 "grm_parsegrammar.tab.c"
    break;

  case 83: /* ldist_decl_only: LDIST_DECL SEP expression SEP expression SEP expression SEP expression SEP DIST_NAME  */
#line 563 "grm_parsegrammar.y"
{
  rna_ldist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-10].string), (yyvsp[0].string), (int)((yyvsp[-4].dval)), (int)((yyvsp[-2].dval)), (int)((yyvsp[-2].dval)), (int)((yyvsp[-8].dval)), (int)((yyvsp[-6].dval)), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2240 "grm_parsegrammar.tab.c"
    break;

  case 84: /* ldist_decl_only: LDIST_DECL SEP expression SEP expression SEP expression SEP expression SEP expression SEP DIST_NAME  */
#line 568 "grm_parsegrammar.y"
{
  rna_ldist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-12].string), (yyvsp[0].string), (int)((yyvsp[-6].dval)), (int)((yyvsp[-4].dval)), (int)((yyvsp[-2].dval)), (int)((yyvsp[-10].dval)), (int)((yyvsp[-8].dval)), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2248 "grm_parsegrammar.tab.c"
    break;

  case 85: /* tdist_decl_only: TDIST_DECL SEP expression SEP TDIST_NAME  */
#line 574 "grm_parsegrammar.y"
{
  rna_tdist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[0].string), (int)((yyvsp[-2].dval)), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2256 "grm_parsegrammar.tab.c"
    break;

  case 86: /* $@9: %empty  */
#line 582 "grm_parsegrammar.y"
{
  rna_edist_declare_one(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), atoi((yyvsp[-8].string)), atoi((yyvsp[-6].string)), atoi((yyvsp[-4].string)), FALSE, "", 0, 1, FALSE, "", -1, -1, FALSE, atoi((yyvsp[0].string)), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2264 "grm_parsegrammar.tab.c"
    break;

  case 88: /* $@10: %empty  */
#line 589 "grm_parsegrammar.y"
{
  rna_edist_declare_one(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-4].string), atoi((yyvsp[-10].string)), atoi((yyvsp[-8].string)), atoi((yyvsp[-6].string)), TRUE, "", 0, 1, FALSE, "", -1, -1, FALSE, atoi((yyvsp[-2].string)), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2272 "grm_parsegrammar.tab.c"
    break;

  case 90: /* $@11: %empty  */
#line 596 "grm_parsegrammar.y"
{
  rna_edist_declare_one(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), atoi((yyvsp[-10].string)), atoi((yyvsp[-8].string)), atoi((yyvsp[-6].string)), FALSE, (yyvsp[-4].string), 0, 1, FALSE, "", -1, -1, FALSE, atoi((yyvsp[0].string)), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2280 "grm_parsegrammar.tab.c"
    break;

  case 92: /* $@12: %empty  */
#line 603 "grm_parsegrammar.y"
{
  rna_edist_declare_one(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), atoi((yyvsp[-12].string)), atoi((yyvsp[-10].string)), atoi((yyvsp[-8].string)), FALSE, (yyvsp[-6].string), 0, 1, TRUE, "", -1, -1, FALSE, atoi((yyvsp[0].string)), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2288 "grm_parsegrammar.tab.c"
    break;

  case 94: /* $@13: %empty  */
#line 610 "grm_parsegrammar.y"
{
  rna_edist_declare_one(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-4].string), atoi((yyvsp[-12].string)), atoi((yyvsp[-10].string)), atoi((yyvsp[-8].string)), TRUE, (yyvsp[-6].string), 0, 1, FALSE, "", -1, -1, FALSE, atoi((yyvsp[-2].string)), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2296 "grm_parsegrammar.tab.c"
    break;

  case 96: /* $@14: %empty  */
#line 617 "grm_parsegrammar.y"
{
  rna_edist_declare_one(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-4].string), atoi((yyvsp[-14].string)), atoi((yyvsp[-12].string)), atoi((yyvsp[-10].string)), TRUE, (yyvsp[-8].string), 0, 1, TRUE, "", -1, -1, FALSE, atoi((yyvsp[-2].string)), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2304 "grm_parsegrammar.tab.c"
    break;

  case 98: /* $@15: %empty  */
#line 624 "grm_parsegrammar.y"
{
  rna_edist_declare_one(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), atoi((yyvsp[-14].string)), atoi((yyvsp[-12].string)), atoi((yyvsp[-10].string)), FALSE, (yyvsp[-8].string), atoi((yyvsp[-6].string)), atoi((yyvsp[-4].string)), FALSE, "", -1, -1, FALSE, atoi((yyvsp[0].string)), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2312 "grm_parsegrammar.tab.c"
    break;

  case 100: /* $@16: %empty  */
#line 631 "grm_parsegrammar.y"
{
  rna_edist_declare_one(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), atoi((yyvsp[-16].string)), atoi((yyvsp[-14].string)), atoi((yyvsp[-12].string)), FALSE, (yyvsp[-10].string), atoi((yyvsp[-8].string)), atoi((yyvsp[-6].string)), TRUE, "", -1, -1, FALSE, atoi((yyvsp[0].string)), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2320 "grm_parsegrammar.tab.c"
    break;

  case 102: /* $@17: %empty  */
#line 638 "grm_parsegrammar.y"
{
  rna_edist_declare_one(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-4].string), atoi((yyvsp[-16].string)), atoi((yyvsp[-14].string)), atoi((yyvsp[-12].string)), TRUE, (yyvsp[-10].string), atoi((yyvsp[-8].string)), atoi((yyvsp[-6].string)), FALSE, "", -1, -1, FALSE, atoi((yyvsp[-2].string)), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2328 "grm_parsegrammar.tab.c"
    break;

  case 104: /* $@18: %empty  */
#line 645 "grm_parsegrammar.y"
{
  rna_edist_declare_one(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-4].string), atoi((yyvsp[-18].string)), atoi((yyvsp[-16].string)), atoi((yyvsp[-14].string)), TRUE, (yyvsp[-12].string), atoi((yyvsp[-10].string)), atoi((yyvsp[-8].string)), TRUE, "", -1, -1, FALSE, atoi((yyvsp[-2].string)), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2336 "grm_parsegrammar.tab.c"
    break;

  case 106: /* $@19: %empty  */
#line 652 "grm_parsegrammar.y"
{
  rna_edist_declare_one(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), atoi((yyvsp[-20].string)), atoi((yyvsp[-18].string)), atoi((yyvsp[-16].string)), FALSE, (yyvsp[-14].string), atoi((yyvsp[-12].string)), atoi((yyvsp[-10].string)), FALSE, (yyvsp[-8].string), atoi((yyvsp[-6].string)), atoi((yyvsp[-4].string)), FALSE, atoi((yyvsp[0].string)), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2344 "grm_parsegrammar.tab.c"
    break;

  case 108: /* $@20: %empty  */
#line 659 "grm_parsegrammar.y"
{
  rna_edist_declare_one(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), atoi((yyvsp[-24].string)), atoi((yyvsp[-22].string)), atoi((yyvsp[-20].string)), FALSE, (yyvsp[-18].string), atoi((yyvsp[-16].string)), atoi((yyvsp[-14].string)), TRUE, (yyvsp[-10].string), atoi((yyvsp[-8].string)), atoi((yyvsp[-6].string)), TRUE, atoi((yyvsp[0].string)), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2352 "grm_parsegrammar.tab.c"
    break;

  case 110: /* $@21: %empty  */
#line 666 "grm_parsegrammar.y"
{
  rna_edist_declare_one(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-4].string), atoi((yyvsp[-22].string)), atoi((yyvsp[-20].string)), atoi((yyvsp[-18].string)), TRUE, (yyvsp[-16].string), atoi((yyvsp[-14].string)), atoi((yyvsp[-12].string)), FALSE, (yyvsp[-10].string), atoi((yyvsp[-8].string)), atoi((yyvsp[-6].string)), FALSE, atoi((yyvsp[-2].string)), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2360 "grm_parsegrammar.tab.c"
    break;

  case 112: /* $@22: %empty  */
#line 673 "grm_parsegrammar.y"
{
  rna_edist_declare_one(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-4].string), atoi((yyvsp[-26].string)), atoi((yyvsp[-24].string)), atoi((yyvsp[-22].string)), TRUE, (yyvsp[-20].string), atoi((yyvsp[-18].string)), atoi((yyvsp[-16].string)), TRUE, (yyvsp[-12].string), atoi((yyvsp[-10].string)), atoi((yyvsp[-8].string)), TRUE, atoi((yyvsp[-2].string)), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2368 "grm_parsegrammar.tab.c"
    break;

  case 115: /* $@23: %empty  */
#line 684 "grm_parsegrammar.y"
{
  rna_tdist_declare(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[0].string), (int)((yyvsp[-2].dval)), ((struct yyparse_s *)yyparse_param)->verbose); 
}
#line 2376 "grm_parsegrammar.tab.c"
    break;

  case 122: /* ttied_one: TTIED SEP ttied_one_rhs  */
#line 698 "grm_parsegrammar.y"
{ if (rna_tdist_tie(ntied, tied, ((struct yyparse_s *)yyparse_param)->Gr, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK)
    grammar_fatal("coud't tie parameters for tdist");
    ntied = 0; 
}
#line 2385 "grm_parsegrammar.tab.c"
    break;

  case 125: /* ttied_idx: INTEGER  */
#line 706 "grm_parsegrammar.y"
{ tied[ntied++] = atoi((yyvsp[0].string)); }
#line 2391 "grm_parsegrammar.tab.c"
    break;

  case 135: /* default_escore: DEFAULT_EMIT GETS expression  */
#line 725 "grm_parsegrammar.y"
{  
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("default e-score [%f]\n", (SCVAL)((yyvsp[0].dval)));
  if (rna_edist_add_score(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), (SCVAL)((yyvsp[0].dval)), FALSE) != eslOK) 
    grammar_fatal("couldn't set specified emission default score %d for default %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-2].string)); 
}
#line 2401 "grm_parsegrammar.tab.c"
    break;

  case 136: /* default_escore: DEFAULT_EMIT ADDS expression  */
#line 731 "grm_parsegrammar.y"
{  
  if (rna_edist_add_score(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), (SCVAL)((yyvsp[0].dval)), TRUE) != eslOK) 
    grammar_fatal("couldn't add specified emission default score %d for default %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-2].string)); 
}
#line 2410 "grm_parsegrammar.tab.c"
    break;

  case 137: /* default_escore: DEFAULT_EMIT GETS DIST_NAME  */
#line 737 "grm_parsegrammar.y"
{  
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("default e-score [%s]\n", (yyvsp[0].string));
  if (rna_edist_add_edist(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), (yyvsp[0].string), -1, -1, FALSE) != eslOK) 
    grammar_fatal("couldn't set pre-specified emission default edist %s for default %s", (yyvsp[0].string), (yyvsp[-2].string)); 
}
#line 2420 "grm_parsegrammar.tab.c"
    break;

  case 138: /* default_escore: DEFAULT_EMIT ADDS DIST_NAME  */
#line 743 "grm_parsegrammar.y"
{  
  if (rna_edist_add_edist(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), (yyvsp[0].string), -1, -1, TRUE) != eslOK) 
    grammar_fatal("couldn't add pre-specified emission default edist %s for default %s", (yyvsp[0].string), (yyvsp[-2].string)); 
}
#line 2429 "grm_parsegrammar.tab.c"
    break;

  case 139: /* default_escore: DEFAULT_EMIT GETS DIST_NAME SEP INTEGER  */
#line 751 "grm_parsegrammar.y"
{  
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("default e-score [%s] : %d \n", (yyvsp[-2].string), atoi((yyvsp[0].string)));
  if (rna_edist_add_edist(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-4].string), (yyvsp[-2].string), atoi((yyvsp[0].string)), -1, FALSE) != eslOK) 
    grammar_fatal("couldn't set pre-specified emission default edist %s for default %s", (yyvsp[-2].string), (yyvsp[-4].string)); 
}
#line 2439 "grm_parsegrammar.tab.c"
    break;

  case 140: /* default_escore: DEFAULT_EMIT ADDS DIST_NAME SEP INTEGER  */
#line 757 "grm_parsegrammar.y"
{  
  if (rna_edist_add_edist(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-4].string), (yyvsp[-2].string), atoi((yyvsp[0].string)), -1, TRUE) != eslOK) 
    grammar_fatal("couldn't add pre-specified emission default edist %s for default %s", (yyvsp[-2].string), (yyvsp[-4].string)); 
}
#line 2448 "grm_parsegrammar.tab.c"
    break;

  case 141: /* default_escore: DEFAULT_EMIT GETS DIST_NAME SEP INTEGER SEP INTEGER  */
#line 765 "grm_parsegrammar.y"
{  
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("default e-score [%s] : %d : %d\n", (yyvsp[-4].string), atoi((yyvsp[-2].string)), atoi((yyvsp[0].string)));
  if (rna_edist_add_edist(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-6].string), (yyvsp[-4].string), atoi((yyvsp[-2].string)), atoi((yyvsp[0].string)), FALSE) != eslOK) 
    grammar_fatal("couldn't set pre-specified emission default edist %s for default %s", (yyvsp[-4].string), (yyvsp[-6].string)); 
}
#line 2458 "grm_parsegrammar.tab.c"
    break;

  case 142: /* default_escore: DEFAULT_EMIT ADDS DIST_NAME SEP INTEGER SEP INTEGER  */
#line 771 "grm_parsegrammar.y"
{  
  if (rna_edist_add_edist(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-6].string), (yyvsp[-4].string), atoi((yyvsp[-2].string)), atoi((yyvsp[0].string)), TRUE) != eslOK) 
    grammar_fatal("couldn't add pre-specified emission default edist %s for default %s", (yyvsp[-4].string), (yyvsp[-6].string)); 
}
#line 2467 "grm_parsegrammar.tab.c"
    break;

  case 143: /* default_lscore: DEFAULT_LDIST GETS expression  */
#line 779 "grm_parsegrammar.y"
{
  if (rna_ldist_add_score_mono(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), (SCVAL)((yyvsp[0].dval)), FALSE, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("couldn't add ldist default score %d for default length %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-2].string)); 
}
#line 2476 "grm_parsegrammar.tab.c"
    break;

  case 144: /* default_lscore: DEFAULT_LDIST COMMA DEFAULT_LDIST GETS expression  */
#line 784 "grm_parsegrammar.y"
{
  if (rna_ldist_add_score_di(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-4].string), (yyvsp[-2].string), (SCVAL)((yyvsp[0].dval)), FALSE, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("couldn't add ldist default score %f for default length %s,%s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-4].string), (yyvsp[-2].string)); 
}
#line 2485 "grm_parsegrammar.tab.c"
    break;

  case 149: /* default_lscore_sum: DEFAULT_LDIST_SUM GETS expression  */
#line 795 "grm_parsegrammar.y"
{
  if (rna_ldist_add_score_di_sum(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), (SCVAL)((yyvsp[0].dval)), FALSE, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("couldn't add ldist default score %f for default sum length %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-2].string)); 
}
#line 2494 "grm_parsegrammar.tab.c"
    break;

  case 150: /* default_lscore_dif: DEFAULT_LDIST_DIF GETS expression  */
#line 801 "grm_parsegrammar.y"
{
  if (rna_ldist_add_score_di_dif(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), (SCVAL)((yyvsp[0].dval)), FALSE, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("couldn't add ldist default score %f for default sum length %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-2].string)); 
}
#line 2503 "grm_parsegrammar.tab.c"
    break;

  case 151: /* default_tscore: DEFAULT_TDIST GETS expression  */
#line 807 "grm_parsegrammar.y"
{
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("default t-score [%f]\n", (SCVAL)((yyvsp[0].dval)));

  if (rna_tdist_add_score_default(((struct yyparse_s *)yyparse_param)->Gr, (SCVAL)((yyvsp[0].dval))) != eslOK) 
    grammar_fatal("couldn't add tdist score %f for default transition %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-2].string)); 
}
#line 2514 "grm_parsegrammar.tab.c"
    break;

  case 152: /* default_tscore: DEFAULT_TDIST OPEN XVARIABLE CLOSE GETS expression  */
#line 814 "grm_parsegrammar.y"
{
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("default t-score [%f]\n", (SCVAL)((yyvsp[0].dval)));

  if (rna_tdist_add_score_default(((struct yyparse_s *)yyparse_param)->Gr, (SCVAL)((yyvsp[0].dval))) != eslOK) 
    grammar_fatal("couldn't add tdist score %f for default transition %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-5].string)); 
}
#line 2525 "grm_parsegrammar.tab.c"
    break;

  case 153: /* one_escore: EMIT GETS expression  */
#line 824 "grm_parsegrammar.y"
{
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("get e-score [%f]\n",(SCVAL)((yyvsp[0].dval)));
  if (rna_edist_add_score(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), (SCVAL)((yyvsp[0].dval)), FALSE) != eslOK) 
     grammar_fatal("couldn't set specified single-base score %f for singlet %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-2].string));  
}
#line 2535 "grm_parsegrammar.tab.c"
    break;

  case 154: /* one_escore: EMIT ADDS expression  */
#line 830 "grm_parsegrammar.y"
{
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("add e-score [%f]\n",(SCVAL)((yyvsp[0].dval)));
  if (rna_edist_add_score(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), (SCVAL)((yyvsp[0].dval)), TRUE) != eslOK) 
     grammar_fatal("couldn't add specified single-base score %f for singlet %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-2].string));  
}
#line 2545 "grm_parsegrammar.tab.c"
    break;

  case 155: /* one_lscore: INTEGER GETS expression  */
#line 838 "grm_parsegrammar.y"
{
  if (rna_ldist_add_score_mono(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), (SCVAL)((yyvsp[0].dval)), FALSE, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("couldn't add specified ldist score %f for length %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-2].string)); 
}
#line 2554 "grm_parsegrammar.tab.c"
    break;

  case 156: /* one_lscore: INTEGER ADDS expression  */
#line 843 "grm_parsegrammar.y"
{
  if (rna_ldist_add_score_mono(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), (SCVAL)((yyvsp[0].dval)), TRUE, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("couldn't add specified ldist score %f for length %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-2].string)); 
}
#line 2563 "grm_parsegrammar.tab.c"
    break;

  case 157: /* one_lscore: INTEGER COMMA INTEGER GETS expression  */
#line 848 "grm_parsegrammar.y"
{
  if (rna_ldist_add_score_di(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-4].string), (yyvsp[-2].string), (SCVAL)((yyvsp[0].dval)), FALSE, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("couldn't add specified ldist score %f for length %s %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-4].string), (yyvsp[-2].string)); 
}
#line 2572 "grm_parsegrammar.tab.c"
    break;

  case 158: /* one_lscore: INTEGER COMMA INTEGER ADDS expression  */
#line 853 "grm_parsegrammar.y"
{
  if (rna_ldist_add_score_di(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-4].string), (yyvsp[-2].string), (SCVAL)((yyvsp[0].dval)), TRUE, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("couldn't add specified ldist score %f for length %s %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-4].string), (yyvsp[-2].string)); 
}
#line 2581 "grm_parsegrammar.tab.c"
    break;

  case 159: /* one_lscore: SUM_LDIST GETS INTEGER GETS expression  */
#line 858 "grm_parsegrammar.y"
{
  if (rna_ldist_add_score_di_sum(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), (SCVAL)((yyvsp[0].dval)), FALSE, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("couldn't add specified ldist sum_score %f for length %s %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-4].string), (yyvsp[-2].string)); 
}
#line 2590 "grm_parsegrammar.tab.c"
    break;

  case 160: /* one_lscore: SUM_LDIST GETS INTEGER ADDS expression  */
#line 863 "grm_parsegrammar.y"
{
  if (rna_ldist_add_score_di_sum(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), (SCVAL)((yyvsp[0].dval)), TRUE, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("couldn't add specified ldist sum_score %f for length %s %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-4].string), (yyvsp[-2].string)); 
}
#line 2599 "grm_parsegrammar.tab.c"
    break;

  case 161: /* one_lscore: DIF_LDIST GETS INTEGER GETS expression  */
#line 868 "grm_parsegrammar.y"
{
  if (rna_ldist_add_score_di_dif(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), (SCVAL)((yyvsp[0].dval)), FALSE, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("couldn't add specified ldist dif_score %f for length %s %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-4].string), (yyvsp[-2].string)); 
}
#line 2608 "grm_parsegrammar.tab.c"
    break;

  case 162: /* one_lscore: DIF_LDIST GETS INTEGER ADDS expression  */
#line 873 "grm_parsegrammar.y"
{
  if (rna_ldist_add_score_di_dif(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), (SCVAL)((yyvsp[0].dval)), TRUE, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("couldn't add specified ldist dif_score %f for length %s %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-4].string), (yyvsp[-2].string)); 
}
#line 2617 "grm_parsegrammar.tab.c"
    break;

  case 163: /* one_lscore: SYM_LDIST GETS INTEGER GETS expression  */
#line 878 "grm_parsegrammar.y"
{
  if (rna_ldist_add_score_di_sym(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), (SCVAL)((yyvsp[0].dval)), FALSE, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("couldn't add specified ldist sym_score %f for length %s %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-4].string), (yyvsp[-2].string)); 
}
#line 2626 "grm_parsegrammar.tab.c"
    break;

  case 164: /* one_lscore: SYM_LDIST GETS INTEGER ADDS expression  */
#line 883 "grm_parsegrammar.y"
{
  if (rna_ldist_add_score_di_sym(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].string), (SCVAL)((yyvsp[0].dval)), TRUE, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("couldn't add specified ldist sym_score %f for length %s %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-4].string), (yyvsp[-2].string)); 
}
#line 2635 "grm_parsegrammar.tab.c"
    break;

  case 166: /* function: AFFINE SEP expression SEP expression SEP expression SEP expression  */
#line 892 "grm_parsegrammar.y"
{ 
  if (rna_ldist_add_affine_score(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-6].dval), (yyvsp[-4].dval), (yyvsp[-2].dval), (yyvsp[0].dval), ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("couldn't add ldist affine function for scores > %d", (yyvsp[-7].string)); 

}
#line 2645 "grm_parsegrammar.tab.c"
    break;

  case 167: /* function: LINEAR SEP expression SEP expression  */
#line 898 "grm_parsegrammar.y"
{
  if (rna_ldist_add_linear_score(((struct yyparse_s *)yyparse_param)->Gr, (yyvsp[-2].dval), (yyvsp[0].dval), ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("couldn't add ldist linear function for scores > %d", (yyvsp[-3].string)); 
}
#line 2654 "grm_parsegrammar.tab.c"
    break;

  case 168: /* one_tscore: INTEGER GETS expression  */
#line 905 "grm_parsegrammar.y"
{
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("t=%d [%f]\n", atoi((yyvsp[-2].string)), (SCVAL)((yyvsp[0].dval)));

  if (rna_tdist_add_score(((struct yyparse_s *)yyparse_param)->Gr, atoi((yyvsp[-2].string)), (SCVAL)((yyvsp[0].dval)), FALSE) != eslOK) 
    grammar_fatal("couldn't add tdist score %d for transition %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-2].string)); 
}
#line 2665 "grm_parsegrammar.tab.c"
    break;

  case 169: /* one_tscore: INTEGER ADDS expression  */
#line 913 "grm_parsegrammar.y"
{
  if (rna_tdist_add_score(((struct yyparse_s *)yyparse_param)->Gr, atoi((yyvsp[-2].string)), (SCVAL)((yyvsp[0].dval)), TRUE) != eslOK) 
    grammar_fatal("couldn't add tdist score %d for transition %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-2].string)); 
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("t=%d +=[%f]\n", atoi((yyvsp[-2].string)), (SCVAL)((yyvsp[0].dval)));
}
#line 2675 "grm_parsegrammar.tab.c"
    break;

  case 170: /* one_tscore: INTEGER OPEN XVARIABLE CLOSE GETS expression  */
#line 920 "grm_parsegrammar.y"
{
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("t=%d [%f]\n", atoi((yyvsp[-5].string)), (SCVAL)((yyvsp[0].dval)));

  if (rna_tdist_add_score(((struct yyparse_s *)yyparse_param)->Gr, atoi((yyvsp[-5].string)), (SCVAL)((yyvsp[0].dval)), FALSE) != eslOK) 
    grammar_fatal("couldn't add tdist score %d for transition %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-5].string)); 
}
#line 2686 "grm_parsegrammar.tab.c"
    break;

  case 171: /* one_tscore: INTEGER OPEN XVARIABLE CLOSE ADDS expression  */
#line 928 "grm_parsegrammar.y"
{
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("t=%d [%f]\n", atoi((yyvsp[-5].string)), (SCVAL)((yyvsp[0].dval)));

  if (rna_tdist_add_score(((struct yyparse_s *)yyparse_param)->Gr, atoi((yyvsp[-5].string)), (SCVAL)((yyvsp[0].dval)), TRUE) != eslOK) 
    grammar_fatal("couldn't add tdist score %d for transition %s", (SCVAL)((yyvsp[0].dval)), (yyvsp[-5].string)); 
}
#line 2697 "grm_parsegrammar.tab.c"
    break;

  case 174: /* $@24: %empty  */
#line 943 "grm_parsegrammar.y"
{
  is_new_rule = TRUE;
  lexeme.l = 1;
  strcpy(lexeme.lex[0], (yyvsp[0].string));
  if (rna_lhs_write(((struct yyparse_s *)yyparse_param)->Gr, lexeme, errbuf, &nt_idx, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("cannot rewrite LHS %s.\n%s\n", lexeme.lex[0], errbuf);
}
#line 2709 "grm_parsegrammar.tab.c"
    break;

  case 176: /* $@25: %empty  */
#line 952 "grm_parsegrammar.y"
{
  is_new_rule = TRUE;
  lexeme.l = 2;
  strcpy(lexeme.lex[0], (yyvsp[-1].string));
  strcpy(lexeme.lex[1], (yyvsp[0].string));
  if (rna_lhs_write(((struct yyparse_s *)yyparse_param)->Gr, lexeme, errbuf, &nt_idx, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("cannot rewrite LHS %s.\n%s\n", lexeme.lex[0], errbuf);
}
#line 2722 "grm_parsegrammar.tab.c"
    break;

  case 178: /* rhs_list: rule  */
#line 964 "grm_parsegrammar.y"
{ 
  is_new_rule = TRUE;
  rnr ++;
}
#line 2731 "grm_parsegrammar.tab.c"
    break;

  case 179: /* rhs_list: rhs_list OR rule  */
#line 969 "grm_parsegrammar.y"
{ 
  is_new_rule = TRUE; 
  rnr ++;
}
#line 2740 "grm_parsegrammar.tab.c"
    break;

  case 180: /* rule: rule_atomlist  */
#line 977 "grm_parsegrammar.y"
{  
  if (((struct yyparse_s *)yyparse_param)->verbose) rna_rule_print(nt_idx, ((struct yyparse_s *)yyparse_param)->Gr);
}
#line 2748 "grm_parsegrammar.tab.c"
    break;

  case 182: /* rule_atomlist: atom  */
#line 985 "grm_parsegrammar.y"
{
  is_new_rule = FALSE; 
}
#line 2756 "grm_parsegrammar.tab.c"
    break;

  case 183: /* rule_atomlist: rule_atomlist atom  */
#line 989 "grm_parsegrammar.y"
{
  is_new_rule = FALSE; 
}
#line 2764 "grm_parsegrammar.tab.c"
    break;

  case 188: /* emission_atom: EMISSION SEP list  */
#line 1002 "grm_parsegrammar.y"
{
  lexeme.l = 2;
  strcpy(lexeme.lex[0], (yyvsp[-2].string));
  strcpy(lexeme.lex[1], (yyvsp[0].string));
  iatom.atomtype = EMISSION_ATOM;
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("  emission atom %s:%s\n", lexeme.lex[0], lexeme.lex[1]);
  if (rna_atom_add_to_rule(rnr, nt_idx, &iatom, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("error in rna_rule %d emision_atom\n", rnr);
}
#line 2778 "grm_parsegrammar.tab.c"
    break;

  case 189: /* emission_atom: EMISSION SEP list DIST_NAME  */
#line 1012 "grm_parsegrammar.y"
{
  lexeme.l = 3;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-1].string));
  strcpy(lexeme.lex[2], (yyvsp[0].string));
  iatom.atomtype = EMISSION_ATOM;
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("  emission atom %s:%s dist %s\n", lexeme.lex[0], lexeme.lex[1], lexeme.lex[2]);
  if (rna_atom_add_to_rule(rnr, nt_idx, &iatom, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("error in rna_rule %d emision_atom\n", rnr);
}
#line 2793 "grm_parsegrammar.tab.c"
    break;

  case 190: /* nonterm_atom: NONTERM OPEN coordrange CLOSE  */
#line 1026 "grm_parsegrammar.y"
{
  lexeme.l = 1;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  iatom.atomtype = NONTERMINAL_ATOM;
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("  nonterminal atom %s\n", lexeme.lex[0]);
  if (rna_atom_add_to_rule(rnr, nt_idx, &iatom, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("error in rna_rule %d nonterminal_atom\n", rnr);
}
#line 2806 "grm_parsegrammar.tab.c"
    break;

  case 191: /* monoseg_atom: MONOSEGMENT OPEN coordrange CLOSE  */
#line 1038 "grm_parsegrammar.y"
{
  lexeme.l = 1;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  iatom.atomtype = MONOSEGMENT_ATOM;
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("monosegment atom %s\n", lexeme.lex[0]);
  if (rna_atom_add_to_rule(rnr, nt_idx, &iatom, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("error in rna_rule %d monosegment_atom\n", rnr);
}
#line 2819 "grm_parsegrammar.tab.c"
    break;

  case 192: /* monoseg_atom: MONOSEGMENT OPEN coordrange CLOSE DIST_NAME  */
#line 1047 "grm_parsegrammar.y"
{
  lexeme.l = 2;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[0].string));
  iatom.atomtype = MONOSEGMENT_ATOM;
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("monosegment atom %s ldist %s\n", lexeme.lex[0], lexeme.lex[1]);
  if (rna_atom_add_to_rule(rnr, nt_idx, &iatom, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("error in rna_rule %d monosegment_atom\n", rnr);
}
#line 2833 "grm_parsegrammar.tab.c"
    break;

  case 193: /* diseg_atom: LDISEGMENT OPEN coordrange CLOSE RDISEGMENT OPEN coordrange CLOSE  */
#line 1060 "grm_parsegrammar.y"
{
  lexeme.l = 1;
  strcpy(lexeme.lex[0], (yyvsp[-7].string));
  strcat(lexeme.lex[0], "^");          
  strcat(lexeme.lex[0], (yyvsp[-3].string));
  iatom.atomtype = DISEGMENT_ATOM;
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("  disegment atom %s\n", lexeme.lex[0]);
  if (rna_atom_add_to_rule(rnr, nt_idx, &iatom, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("error in rna_rule %d disegment_atom\n", rnr);
}
#line 2848 "grm_parsegrammar.tab.c"
    break;

  case 194: /* diseg_atom: LDISEGMENT OPEN coordrange CLOSE RDISEGMENT OPEN coordrange CLOSE DIST_NAME  */
#line 1071 "grm_parsegrammar.y"
{
  lexeme.l = 2;
  strcpy(lexeme.lex[0], (yyvsp[-8].string));
  strcat(lexeme.lex[0], "^");          
  strcat(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[0].string));
  iatom.atomtype = DISEGMENT_ATOM;
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("  disegment atom %s dist %s\n", lexeme.lex[0], lexeme.lex[1]);
  if (rna_atom_add_to_rule(rnr, nt_idx, &iatom, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("error in rna_rule %d disegment_atom\n", rnr);
}
#line 2864 "grm_parsegrammar.tab.c"
    break;

  case 195: /* diseg_atom: LDISEGMENT OPEN coordrange CLOSE RDISEGMENT OPEN coordrange CLOSE DIST_NAME DIST_NAME  */
#line 1083 "grm_parsegrammar.y"
{
  lexeme.l = 3;
  strcpy(lexeme.lex[0], (yyvsp[-9].string));
  strcat(lexeme.lex[0], "^");          
  strcat(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-1].string));
  strcpy(lexeme.lex[2], (yyvsp[0].string));
  iatom.atomtype = DISEGMENT_ATOM;
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("  disegment atom %s dist %s dist %s\n", lexeme.lex[0], lexeme.lex[1], lexeme.lex[2]);
  if (rna_atom_add_to_rule(rnr, nt_idx, &iatom, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("error in rna_rule %d disegment_atom\n", rnr);
}
#line 2881 "grm_parsegrammar.tab.c"
    break;

  case 196: /* diseg_atom: LDISEGMENT OPEN coordrange CLOSE RDISEGMENT OPEN coordrange CLOSE DIST_NAME DIST_NAME DIST_NAME  */
#line 1096 "grm_parsegrammar.y"
{
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-10].string));
  strcat(lexeme.lex[0], "^");          
  strcat(lexeme.lex[0], (yyvsp[-6].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  iatom.atomtype = DISEGMENT_ATOM;
  if (((struct yyparse_s *)yyparse_param)->verbose) printf("  disegment atom %s dist %s dist %s dist %s\n", lexeme.lex[0], lexeme.lex[1], lexeme.lex[2], lexeme.lex[3]);
  if (rna_atom_add_to_rule(rnr, nt_idx, &iatom, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) 
    grammar_fatal("error in rna_rule %d disegment_atom\n", rnr);
}
#line 2899 "grm_parsegrammar.tab.c"
    break;

  case 209: /* paircoord: coord AND coord  */
#line 1133 "grm_parsegrammar.y"
{
  iatom.has_basepair = TRUE;
  iatom.bp[iatom.nbasepairs].basepair_coordl_idx = iatom.ncoords-2;
  iatom.bp[iatom.nbasepairs].basepair_coordr_idx = iatom.ncoords-1;
  iatom.nbasepairs ++;
}
#line 2910 "grm_parsegrammar.tab.c"
    break;

  case 210: /* paircontext: context AND context  */
#line 1142 "grm_parsegrammar.y"
{
  iatom.cbp[iatom.ncbasepairs].basepair_coordl_idx = iatom.ncontexts-2;
  iatom.cbp[iatom.ncbasepairs].basepair_coordr_idx = iatom.ncontexts-1;
  iatom.ncbasepairs ++;
}
#line 2920 "grm_parsegrammar.tab.c"
    break;

  case 211: /* coord: COORDBASE  */
#line 1151 "grm_parsegrammar.y"
{
  add_coord(&iatom, (yyvsp[0].string), 0, ((struct yyparse_s *)yyparse_param)->verbose);
}
#line 2928 "grm_parsegrammar.tab.c"
    break;

  case 212: /* coord: COORDBASE INTEGER  */
#line 1155 "grm_parsegrammar.y"
{
  add_coord(&iatom, (yyvsp[-1].string), atoi((yyvsp[0].string)), ((struct yyparse_s *)yyparse_param)->verbose);
}
#line 2936 "grm_parsegrammar.tab.c"
    break;

  case 213: /* coord: COORDBASE PLUS INTEGER  */
#line 1159 "grm_parsegrammar.y"
{
  add_coord(&iatom, (yyvsp[-2].string), atoi((yyvsp[0].string)), ((struct yyparse_s *)yyparse_param)->verbose);
}
#line 2944 "grm_parsegrammar.tab.c"
    break;

  case 214: /* coord: COORDBASE MINUS INTEGER  */
#line 1163 "grm_parsegrammar.y"
{
  add_coord(&iatom, (yyvsp[-2].string), -atoi((yyvsp[0].string)), ((struct yyparse_s *)yyparse_param)->verbose);
}
#line 2952 "grm_parsegrammar.tab.c"
    break;

  case 215: /* context: COORDBASE  */
#line 1170 "grm_parsegrammar.y"
{
  add_context(&iatom, (yyvsp[0].string), 0, ((struct yyparse_s *)yyparse_param)->verbose);
}
#line 2960 "grm_parsegrammar.tab.c"
    break;

  case 216: /* context: COORDBASE INTEGER  */
#line 1174 "grm_parsegrammar.y"
{
  add_context(&iatom, (yyvsp[-1].string), atoi((yyvsp[0].string)), ((struct yyparse_s *)yyparse_param)->verbose);
}
#line 2968 "grm_parsegrammar.tab.c"
    break;

  case 217: /* context: COORDBASE PLUS INTEGER  */
#line 1178 "grm_parsegrammar.y"
{
  add_context(&iatom, (yyvsp[-2].string), atoi((yyvsp[0].string)), ((struct yyparse_s *)yyparse_param)->verbose);
}
#line 2976 "grm_parsegrammar.tab.c"
    break;

  case 218: /* context: COORDBASE MINUS INTEGER  */
#line 1182 "grm_parsegrammar.y"
{
  add_context(&iatom, (yyvsp[-2].string), -atoi((yyvsp[0].string)), ((struct yyparse_s *)yyparse_param)->verbose);
}
#line 2984 "grm_parsegrammar.tab.c"
    break;

  case 219: /* rule_enum: EPSILON  */
#line 1190 "grm_parsegrammar.y"
{
  ynr = 1;
  lexeme.l = 1;
  strcpy(lexeme.lex[0], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 2995 "grm_parsegrammar.tab.c"
    break;

  case 220: /* rule_enum: EMISSION  */
#line 1198 "grm_parsegrammar.y"
{
  ynr = 2;
  lexeme.l = 1;
  strcpy(lexeme.lex[0], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3006 "grm_parsegrammar.tab.c"
    break;

  case 221: /* rule_enum: EMISSION DIST_NAME  */
#line 1206 "grm_parsegrammar.y"
{
  ynr = 2;
  lexeme.l = 2;
  strcpy(lexeme.lex[0], (yyvsp[-1].string));
  strcpy(lexeme.lex[1], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3018 "grm_parsegrammar.tab.c"
    break;

  case 222: /* rule_enum: NONTERM  */
#line 1215 "grm_parsegrammar.y"
{     
  ynr = 3;
  lexeme.l = 1;
  strcpy(lexeme.lex[0], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3029 "grm_parsegrammar.tab.c"
    break;

  case 223: /* rule_enum: EMISSION EMISSION  */
#line 1223 "grm_parsegrammar.y"
{     
  ynr = 4;
  lexeme.l = 2;
  strcpy(lexeme.lex[0], (yyvsp[-1].string));
  strcpy(lexeme.lex[1], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3041 "grm_parsegrammar.tab.c"
    break;

  case 224: /* rule_enum: EMISSION EMISSION DIST_NAME  */
#line 1232 "grm_parsegrammar.y"
{     
  ynr = 4;
  lexeme.l = 3;
  strcpy(lexeme.lex[0], (yyvsp[-2].string));
  strcpy(lexeme.lex[1], (yyvsp[-1].string));
  strcpy(lexeme.lex[2], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3054 "grm_parsegrammar.tab.c"
    break;

  case 225: /* rule_enum: EMISSION NONTERM  */
#line 1242 "grm_parsegrammar.y"
{
  ynr = 5;
  lexeme.l = 2;
  strcpy(lexeme.lex[0], (yyvsp[-1].string));
  strcpy(lexeme.lex[1], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3066 "grm_parsegrammar.tab.c"
    break;

  case 226: /* rule_enum: EMISSION NONTERM DIST_NAME  */
#line 1251 "grm_parsegrammar.y"
{
  ynr = 5;
  lexeme.l = 3;
  strcpy(lexeme.lex[0], (yyvsp[-2].string));
  strcpy(lexeme.lex[1], (yyvsp[-1].string));
  strcpy(lexeme.lex[2], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3079 "grm_parsegrammar.tab.c"
    break;

  case 227: /* rule_enum: NONTERM EMISSION  */
#line 1261 "grm_parsegrammar.y"
{
  ynr = 6;
  lexeme.l = 2;
  strcpy(lexeme.lex[0], (yyvsp[-1].string));
  strcpy(lexeme.lex[1], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3091 "grm_parsegrammar.tab.c"
    break;

  case 228: /* rule_enum: NONTERM EMISSION DIST_NAME  */
#line 1270 "grm_parsegrammar.y"
{
  ynr = 6;
  lexeme.l = 3;
  strcpy(lexeme.lex[0], (yyvsp[-2].string));
  strcpy(lexeme.lex[1], (yyvsp[-1].string));
  strcpy(lexeme.lex[2], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3104 "grm_parsegrammar.tab.c"
    break;

  case 229: /* rule_enum: NONTERM NONTERM  */
#line 1280 "grm_parsegrammar.y"
{
  ynr = 7;
  lexeme.l = 2;
  strcpy(lexeme.lex[0], (yyvsp[-1].string));
  strcpy(lexeme.lex[1], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3116 "grm_parsegrammar.tab.c"
    break;

  case 230: /* rule_enum: EMISSION EMISSION EMISSION  */
#line 1289 "grm_parsegrammar.y"
{
  ynr = 8;
  lexeme.l = 3;
  strcpy(lexeme.lex[0], (yyvsp[-2].string));
  strcpy(lexeme.lex[1], (yyvsp[-1].string));
  strcpy(lexeme.lex[2], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3129 "grm_parsegrammar.tab.c"
    break;

  case 231: /* rule_enum: EMISSION EMISSION EMISSION DIST_NAME  */
#line 1299 "grm_parsegrammar.y"
{
  ynr = 8;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3143 "grm_parsegrammar.tab.c"
    break;

  case 232: /* rule_enum: NONTERM NONTERM EMISSION  */
#line 1310 "grm_parsegrammar.y"
{
  ynr = 9;
  lexeme.l = 3;
  strcpy(lexeme.lex[0], (yyvsp[-2].string));
  strcpy(lexeme.lex[1], (yyvsp[-1].string));
  strcpy(lexeme.lex[2], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3156 "grm_parsegrammar.tab.c"
    break;

  case 233: /* rule_enum: NONTERM NONTERM EMISSION DIST_NAME  */
#line 1320 "grm_parsegrammar.y"
{
  ynr = 9;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3170 "grm_parsegrammar.tab.c"
    break;

  case 234: /* rule_enum: EMISSION NONTERM NONTERM  */
#line 1331 "grm_parsegrammar.y"
{
  ynr = 10;
  lexeme.l = 3;
  strcpy(lexeme.lex[0], (yyvsp[-2].string));
  strcpy(lexeme.lex[1], (yyvsp[-1].string));
  strcpy(lexeme.lex[2], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3183 "grm_parsegrammar.tab.c"
    break;

  case 235: /* rule_enum: EMISSION NONTERM NONTERM DIST_NAME  */
#line 1341 "grm_parsegrammar.y"
{
  ynr = 10;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3197 "grm_parsegrammar.tab.c"
    break;

  case 236: /* rule_enum: NONTERM EMISSION NONTERM  */
#line 1352 "grm_parsegrammar.y"
{
  ynr = 11;
  lexeme.l = 3;
  strcpy(lexeme.lex[0], (yyvsp[-2].string));
  strcpy(lexeme.lex[1], (yyvsp[-1].string));
  strcpy(lexeme.lex[2], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3210 "grm_parsegrammar.tab.c"
    break;

  case 237: /* rule_enum: NONTERM EMISSION NONTERM DIST_NAME  */
#line 1362 "grm_parsegrammar.y"
{
  ynr = 11;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3224 "grm_parsegrammar.tab.c"
    break;

  case 238: /* rule_enum: EMISSION NONTERM EMISSION  */
#line 1373 "grm_parsegrammar.y"
{
  ynr = 12;
  lexeme.l = 3;
  strcpy(lexeme.lex[0], (yyvsp[-2].string));
  strcpy(lexeme.lex[1], (yyvsp[-1].string));
  strcpy(lexeme.lex[2], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3237 "grm_parsegrammar.tab.c"
    break;

  case 239: /* rule_enum: EMISSION NONTERM EMISSION DIST_NAME  */
#line 1382 "grm_parsegrammar.y"
{
  ynr = 12;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3251 "grm_parsegrammar.tab.c"
    break;

  case 240: /* rule_enum: EMISSION NONTERM EMISSION DIST_NAME DIST_NAME  */
#line 1393 "grm_parsegrammar.y"
{
  ynr = 12;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3266 "grm_parsegrammar.tab.c"
    break;

  case 241: /* rule_enum: NONTERM EMISSION EMISSION  */
#line 1405 "grm_parsegrammar.y"
{
  ynr = 13;
  lexeme.l = 3;
  strcpy(lexeme.lex[0], (yyvsp[-2].string));
  strcpy(lexeme.lex[1], (yyvsp[-1].string));
  strcpy(lexeme.lex[2], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3279 "grm_parsegrammar.tab.c"
    break;

  case 242: /* rule_enum: NONTERM EMISSION EMISSION DIST_NAME  */
#line 1415 "grm_parsegrammar.y"
{
  ynr = 13;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3293 "grm_parsegrammar.tab.c"
    break;

  case 243: /* rule_enum: NONTERM EMISSION EMISSION DIST_NAME DIST_NAME  */
#line 1426 "grm_parsegrammar.y"
{
  ynr = 13;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3308 "grm_parsegrammar.tab.c"
    break;

  case 244: /* rule_enum: EMISSION EMISSION NONTERM  */
#line 1438 "grm_parsegrammar.y"
{
  ynr = 14;
  lexeme.l = 3;
  strcpy(lexeme.lex[0], (yyvsp[-2].string));
  strcpy(lexeme.lex[1], (yyvsp[-1].string));
  strcpy(lexeme.lex[2], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3321 "grm_parsegrammar.tab.c"
    break;

  case 245: /* rule_enum: EMISSION EMISSION NONTERM DIST_NAME  */
#line 1448 "grm_parsegrammar.y"
{
  ynr = 14;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3335 "grm_parsegrammar.tab.c"
    break;

  case 246: /* rule_enum: EMISSION EMISSION NONTERM DIST_NAME DIST_NAME  */
#line 1460 "grm_parsegrammar.y"
{
  ynr = 14;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3350 "grm_parsegrammar.tab.c"
    break;

  case 247: /* rule_enum: EMISSION EMISSION EMISSION EMISSION  */
#line 1472 "grm_parsegrammar.y"
{
  ynr = 15;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3364 "grm_parsegrammar.tab.c"
    break;

  case 248: /* rule_enum: EMISSION EMISSION EMISSION EMISSION DIST_NAME  */
#line 1483 "grm_parsegrammar.y"
{
  ynr = 15;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3379 "grm_parsegrammar.tab.c"
    break;

  case 249: /* rule_enum: EMISSION NONTERM NONTERM EMISSION  */
#line 1495 "grm_parsegrammar.y"
{
  ynr = 16;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3393 "grm_parsegrammar.tab.c"
    break;

  case 250: /* rule_enum: EMISSION NONTERM NONTERM EMISSION DIST_NAME  */
#line 1506 "grm_parsegrammar.y"
{
  ynr = 16;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3408 "grm_parsegrammar.tab.c"
    break;

  case 251: /* rule_enum: EMISSION NONTERM NONTERM EMISSION DIST_NAME DIST_NAME  */
#line 1518 "grm_parsegrammar.y"
{
  ynr = 16;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3424 "grm_parsegrammar.tab.c"
    break;

  case 252: /* rule_enum: EMISSION NONTERM EMISSION NONTERM  */
#line 1531 "grm_parsegrammar.y"
{     
  ynr = 17;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3438 "grm_parsegrammar.tab.c"
    break;

  case 253: /* rule_enum: EMISSION NONTERM EMISSION NONTERM DIST_NAME  */
#line 1542 "grm_parsegrammar.y"
{
  ynr = 17;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3453 "grm_parsegrammar.tab.c"
    break;

  case 254: /* rule_enum: EMISSION NONTERM EMISSION NONTERM DIST_NAME DIST_NAME  */
#line 1554 "grm_parsegrammar.y"
{
  ynr = 17;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3469 "grm_parsegrammar.tab.c"
    break;

  case 255: /* rule_enum: NONTERM EMISSION NONTERM EMISSION  */
#line 1567 "grm_parsegrammar.y"
{
  ynr = 18;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3483 "grm_parsegrammar.tab.c"
    break;

  case 256: /* rule_enum: NONTERM EMISSION NONTERM EMISSION DIST_NAME  */
#line 1578 "grm_parsegrammar.y"
{
  ynr = 18;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3498 "grm_parsegrammar.tab.c"
    break;

  case 257: /* rule_enum: NONTERM EMISSION NONTERM EMISSION DIST_NAME DIST_NAME  */
#line 1590 "grm_parsegrammar.y"
{        
  ynr = 18;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3514 "grm_parsegrammar.tab.c"
    break;

  case 258: /* rule_enum: EMISSION NONTERM EMISSION NONTERM EMISSION  */
#line 1603 "grm_parsegrammar.y"
{
  ynr = 19;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3529 "grm_parsegrammar.tab.c"
    break;

  case 259: /* rule_enum: EMISSION NONTERM EMISSION NONTERM EMISSION DIST_NAME  */
#line 1615 "grm_parsegrammar.y"
{
  ynr = 19;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3545 "grm_parsegrammar.tab.c"
    break;

  case 260: /* rule_enum: EMISSION NONTERM EMISSION EMISSION NONTERM  */
#line 1628 "grm_parsegrammar.y"
{
  ynr = 20;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3560 "grm_parsegrammar.tab.c"
    break;

  case 261: /* rule_enum: EMISSION NONTERM EMISSION EMISSION NONTERM DIST_NAME  */
#line 1640 "grm_parsegrammar.y"
{
  ynr = 20;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3576 "grm_parsegrammar.tab.c"
    break;

  case 262: /* rule_enum: NONTERM EMISSION EMISSION NONTERM EMISSION  */
#line 1653 "grm_parsegrammar.y"
{
  ynr = 21;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3591 "grm_parsegrammar.tab.c"
    break;

  case 263: /* rule_enum: NONTERM EMISSION EMISSION NONTERM EMISSION DIST_NAME  */
#line 1665 "grm_parsegrammar.y"
{
  ynr = 21;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3607 "grm_parsegrammar.tab.c"
    break;

  case 264: /* rule_enum: NONTERM EMISSION NONTERM EMISSION NONTERM  */
#line 1678 "grm_parsegrammar.y"
{
  ynr = 22;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3622 "grm_parsegrammar.tab.c"
    break;

  case 265: /* rule_enum: NONTERM EMISSION NONTERM EMISSION NONTERM DIST_NAME  */
#line 1690 "grm_parsegrammar.y"
{
  ynr = 22;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3638 "grm_parsegrammar.tab.c"
    break;

  case 266: /* rule_enum: NONTERM EMISSION NONTERM EMISSION NONTERM DIST_NAME DIST_NAME  */
#line 1703 "grm_parsegrammar.y"
{
  ynr = 22;
  lexeme.l = 7;
  strcpy(lexeme.lex[0], (yyvsp[-6].string));
  strcpy(lexeme.lex[1], (yyvsp[-5].string));
  strcpy(lexeme.lex[2], (yyvsp[-4].string));
  strcpy(lexeme.lex[3], (yyvsp[-3].string));
  strcpy(lexeme.lex[4], (yyvsp[-2].string));
  strcpy(lexeme.lex[5], (yyvsp[-1].string));
  strcpy(lexeme.lex[6], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3655 "grm_parsegrammar.tab.c"
    break;

  case 267: /* rule_enum: EMISSION NONTERM EMISSION EMISSION  */
#line 1717 "grm_parsegrammar.y"
{
  ynr = 23;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3669 "grm_parsegrammar.tab.c"
    break;

  case 268: /* rule_enum: EMISSION NONTERM EMISSION EMISSION DIST_NAME  */
#line 1728 "grm_parsegrammar.y"
{
  ynr = 23;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3684 "grm_parsegrammar.tab.c"
    break;

  case 269: /* rule_enum: EMISSION EMISSION NONTERM EMISSION  */
#line 1740 "grm_parsegrammar.y"
{
  ynr = 24;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3698 "grm_parsegrammar.tab.c"
    break;

  case 270: /* rule_enum: EMISSION EMISSION NONTERM EMISSION DIST_NAME  */
#line 1751 "grm_parsegrammar.y"
{
  ynr = 24;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3713 "grm_parsegrammar.tab.c"
    break;

  case 271: /* rule_enum: EMISSION EMISSION NONTERM EMISSION EMISSION  */
#line 1763 "grm_parsegrammar.y"
{
  ynr = 25;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3728 "grm_parsegrammar.tab.c"
    break;

  case 272: /* rule_enum: EMISSION EMISSION NONTERM EMISSION EMISSION DIST_NAME  */
#line 1775 "grm_parsegrammar.y"
{
  ynr = 25;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3744 "grm_parsegrammar.tab.c"
    break;

  case 273: /* rule_enum: EMISSION NONTERM EMISSION EMISSION NONTERM EMISSION  */
#line 1788 "grm_parsegrammar.y"
{
  ynr = 26;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3760 "grm_parsegrammar.tab.c"
    break;

  case 274: /* rule_enum: EMISSION NONTERM EMISSION EMISSION NONTERM EMISSION DIST_NAME  */
#line 1801 "grm_parsegrammar.y"
{
  ynr = 26;
  lexeme.l = 7;
  strcpy(lexeme.lex[0], (yyvsp[-6].string));
  strcpy(lexeme.lex[1], (yyvsp[-5].string));
  strcpy(lexeme.lex[2], (yyvsp[-4].string));
  strcpy(lexeme.lex[3], (yyvsp[-3].string));
  strcpy(lexeme.lex[4], (yyvsp[-2].string));
  strcpy(lexeme.lex[5], (yyvsp[-1].string));
  strcpy(lexeme.lex[6], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3777 "grm_parsegrammar.tab.c"
    break;

  case 275: /* rule_enum: EMISSION NONTERM EMISSION EMISSION EMISSION NONTERM EMISSION  */
#line 1815 "grm_parsegrammar.y"
{
  ynr = 27;
  lexeme.l = 7;
  strcpy(lexeme.lex[0], (yyvsp[-6].string));
  strcpy(lexeme.lex[1], (yyvsp[-5].string));
  strcpy(lexeme.lex[2], (yyvsp[-4].string));
  strcpy(lexeme.lex[3], (yyvsp[-3].string));
  strcpy(lexeme.lex[4], (yyvsp[-2].string));
  strcpy(lexeme.lex[5], (yyvsp[-1].string));
  strcpy(lexeme.lex[6], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3794 "grm_parsegrammar.tab.c"
    break;

  case 276: /* rule_enum: EMISSION NONTERM EMISSION EMISSION EMISSION NONTERM EMISSION DIST_NAME  */
#line 1829 "grm_parsegrammar.y"
{
  ynr = 27;
  lexeme.l = 8;
  strcpy(lexeme.lex[0], (yyvsp[-7].string));
  strcpy(lexeme.lex[1], (yyvsp[-6].string));
  strcpy(lexeme.lex[2], (yyvsp[-5].string));
  strcpy(lexeme.lex[3], (yyvsp[-4].string));
  strcpy(lexeme.lex[4], (yyvsp[-3].string));
  strcpy(lexeme.lex[5], (yyvsp[-2].string));
  strcpy(lexeme.lex[6], (yyvsp[-1].string));
  strcpy(lexeme.lex[7], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3812 "grm_parsegrammar.tab.c"
    break;

  case 277: /* rule_enum: MONOSEGMENT  */
#line 1844 "grm_parsegrammar.y"
{
  ynr = 28;
  lexeme.l = 1;
  strcpy(lexeme.lex[0], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3823 "grm_parsegrammar.tab.c"
    break;

  case 278: /* rule_enum: MONOSEGMENT DIST_NAME  */
#line 1852 "grm_parsegrammar.y"
{
  ynr = 28;
  lexeme.l = 2;
  strcpy(lexeme.lex[0], (yyvsp[-1].string));
  strcpy(lexeme.lex[1], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3835 "grm_parsegrammar.tab.c"
    break;

  case 279: /* rule_enum: MONOSEGMENT NONTERM  */
#line 1861 "grm_parsegrammar.y"
{   
  ynr = 29;
  lexeme.l = 2;
  strcpy(lexeme.lex[0], (yyvsp[-1].string));
  strcpy(lexeme.lex[1], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3847 "grm_parsegrammar.tab.c"
    break;

  case 280: /* rule_enum: MONOSEGMENT NONTERM DIST_NAME  */
#line 1870 "grm_parsegrammar.y"
{   
  ynr = 29;
  lexeme.l = 3;
  strcpy(lexeme.lex[0], (yyvsp[-2].string));
  strcpy(lexeme.lex[1], (yyvsp[-1].string));
  strcpy(lexeme.lex[2], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3860 "grm_parsegrammar.tab.c"
    break;

  case 281: /* rule_enum: NONTERM MONOSEGMENT  */
#line 1880 "grm_parsegrammar.y"
{   
  ynr = 30;
  lexeme.l = 2;
  strcpy(lexeme.lex[0], (yyvsp[-1].string));
  strcpy(lexeme.lex[1], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3872 "grm_parsegrammar.tab.c"
    break;

  case 282: /* rule_enum: NONTERM MONOSEGMENT DIST_NAME  */
#line 1889 "grm_parsegrammar.y"
{   
  ynr = 30;
  lexeme.l = 3;
  strcpy(lexeme.lex[0], (yyvsp[-2].string));
  strcpy(lexeme.lex[1], (yyvsp[-1].string));
  strcpy(lexeme.lex[2], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3885 "grm_parsegrammar.tab.c"
    break;

  case 283: /* rule_enum: LDISEGMENT NONTERM RDISEGMENT  */
#line 1899 "grm_parsegrammar.y"
{           
  ynr = 31;
  lexeme.l = 3;
  strcpy(lexeme.lex[0], (yyvsp[-2].string));
  strcpy(lexeme.lex[1], (yyvsp[-1].string));
  strcpy(lexeme.lex[2], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3898 "grm_parsegrammar.tab.c"
    break;

  case 284: /* rule_enum: LDISEGMENT NONTERM RDISEGMENT DIST_NAME  */
#line 1909 "grm_parsegrammar.y"
{           
  ynr = 31;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3912 "grm_parsegrammar.tab.c"
    break;

  case 285: /* rule_enum: LDISEGMENT NONTERM RDISEGMENT DIST_NAME DIST_NAME  */
#line 1920 "grm_parsegrammar.y"
{           
  ynr = 31;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3927 "grm_parsegrammar.tab.c"
    break;

  case 286: /* rule_enum: LDISEGMENT NONTERM RDISEGMENT DIST_NAME DIST_NAME DIST_NAME  */
#line 1932 "grm_parsegrammar.y"
{           
  ynr = 31;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3943 "grm_parsegrammar.tab.c"
    break;

  case 287: /* rule_enum: MONOSEGMENT EMISSION NONTERM EMISSION  */
#line 1945 "grm_parsegrammar.y"
{   
  ynr = 32;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3957 "grm_parsegrammar.tab.c"
    break;

  case 288: /* rule_enum: MONOSEGMENT EMISSION NONTERM EMISSION DIST_NAME  */
#line 1956 "grm_parsegrammar.y"
{   
  ynr = 32;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3972 "grm_parsegrammar.tab.c"
    break;

  case 289: /* rule_enum: MONOSEGMENT EMISSION NONTERM EMISSION DIST_NAME DIST_NAME  */
#line 1968 "grm_parsegrammar.y"
{   
  ynr = 32;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 3988 "grm_parsegrammar.tab.c"
    break;

  case 290: /* rule_enum: EMISSION NONTERM EMISSION MONOSEGMENT  */
#line 1981 "grm_parsegrammar.y"
{   
  ynr = 33;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4002 "grm_parsegrammar.tab.c"
    break;

  case 291: /* rule_enum: EMISSION NONTERM EMISSION MONOSEGMENT DIST_NAME  */
#line 1992 "grm_parsegrammar.y"
{   
  ynr = 33;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4017 "grm_parsegrammar.tab.c"
    break;

  case 292: /* rule_enum: EMISSION NONTERM EMISSION MONOSEGMENT DIST_NAME DIST_NAME  */
#line 2004 "grm_parsegrammar.y"
{   
  ynr = 33;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4033 "grm_parsegrammar.tab.c"
    break;

  case 293: /* rule_enum: LDISEGMENT EMISSION NONTERM EMISSION RDISEGMENT  */
#line 2017 "grm_parsegrammar.y"
{           
  ynr = 34;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4048 "grm_parsegrammar.tab.c"
    break;

  case 294: /* rule_enum: LDISEGMENT EMISSION NONTERM EMISSION RDISEGMENT DIST_NAME  */
#line 2029 "grm_parsegrammar.y"
{           
  ynr = 34;   
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4064 "grm_parsegrammar.tab.c"
    break;

  case 295: /* rule_enum: LDISEGMENT EMISSION NONTERM EMISSION RDISEGMENT DIST_NAME DIST_NAME  */
#line 2042 "grm_parsegrammar.y"
{           
  ynr = 34;
  lexeme.l = 7;
  strcpy(lexeme.lex[0], (yyvsp[-6].string));
  strcpy(lexeme.lex[1], (yyvsp[-5].string));
  strcpy(lexeme.lex[2], (yyvsp[-4].string));
  strcpy(lexeme.lex[3], (yyvsp[-3].string));
  strcpy(lexeme.lex[4], (yyvsp[-2].string));
  strcpy(lexeme.lex[5], (yyvsp[-1].string));
  strcpy(lexeme.lex[6], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4081 "grm_parsegrammar.tab.c"
    break;

  case 296: /* rule_enum: EMISSION MONOSEGMENT EMISSION  */
#line 2056 "grm_parsegrammar.y"
{
  ynr = 35;
  lexeme.l = 3;
  strcpy(lexeme.lex[0], (yyvsp[-2].string));
  strcpy(lexeme.lex[1], (yyvsp[-1].string));
  strcpy(lexeme.lex[2], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4094 "grm_parsegrammar.tab.c"
    break;

  case 297: /* rule_enum: EMISSION MONOSEGMENT EMISSION DIST_NAME  */
#line 2066 "grm_parsegrammar.y"
{
  ynr = 35;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4108 "grm_parsegrammar.tab.c"
    break;

  case 298: /* rule_enum: EMISSION MONOSEGMENT EMISSION DIST_NAME DIST_NAME  */
#line 2077 "grm_parsegrammar.y"
{
  ynr = 35;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4123 "grm_parsegrammar.tab.c"
    break;

  case 299: /* rule_enum: EMISSION MONOSEGMENT EMISSION DIST_NAME DIST_NAME DIST_NAME  */
#line 2089 "grm_parsegrammar.y"
{
  ynr = 35;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4139 "grm_parsegrammar.tab.c"
    break;

  case 300: /* rule_enum: EMISSION MONOSEGMENT NONTERM EMISSION  */
#line 2102 "grm_parsegrammar.y"
{
  ynr = 36;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4153 "grm_parsegrammar.tab.c"
    break;

  case 301: /* rule_enum: EMISSION MONOSEGMENT NONTERM EMISSION DIST_NAME  */
#line 2113 "grm_parsegrammar.y"
{
  ynr = 36;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4168 "grm_parsegrammar.tab.c"
    break;

  case 302: /* rule_enum: EMISSION MONOSEGMENT NONTERM EMISSION DIST_NAME DIST_NAME  */
#line 2125 "grm_parsegrammar.y"
{
  ynr = 36;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4184 "grm_parsegrammar.tab.c"
    break;

  case 303: /* rule_enum: EMISSION MONOSEGMENT NONTERM EMISSION DIST_NAME DIST_NAME DIST_NAME  */
#line 2138 "grm_parsegrammar.y"
{
  ynr = 36;
  lexeme.l = 7;
  strcpy(lexeme.lex[0], (yyvsp[-6].string));
  strcpy(lexeme.lex[1], (yyvsp[-5].string));
  strcpy(lexeme.lex[2], (yyvsp[-4].string));
  strcpy(lexeme.lex[3], (yyvsp[-3].string));
  strcpy(lexeme.lex[4], (yyvsp[-2].string));
  strcpy(lexeme.lex[5], (yyvsp[-1].string));
  strcpy(lexeme.lex[6], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4201 "grm_parsegrammar.tab.c"
    break;

  case 304: /* rule_enum: EMISSION NONTERM MONOSEGMENT EMISSION  */
#line 2152 "grm_parsegrammar.y"
{
  ynr = 37;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4215 "grm_parsegrammar.tab.c"
    break;

  case 305: /* rule_enum: EMISSION NONTERM MONOSEGMENT EMISSION DIST_NAME  */
#line 2163 "grm_parsegrammar.y"
{
  ynr = 37;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4230 "grm_parsegrammar.tab.c"
    break;

  case 306: /* rule_enum: EMISSION NONTERM MONOSEGMENT EMISSION DIST_NAME DIST_NAME  */
#line 2175 "grm_parsegrammar.y"
{
  ynr = 37;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4246 "grm_parsegrammar.tab.c"
    break;

  case 307: /* rule_enum: EMISSION NONTERM MONOSEGMENT EMISSION DIST_NAME DIST_NAME DIST_NAME  */
#line 2188 "grm_parsegrammar.y"
{
  ynr = 37;
  lexeme.l = 7;
  strcpy(lexeme.lex[0], (yyvsp[-6].string));
  strcpy(lexeme.lex[1], (yyvsp[-5].string));
  strcpy(lexeme.lex[2], (yyvsp[-4].string));
  strcpy(lexeme.lex[3], (yyvsp[-3].string));
  strcpy(lexeme.lex[4], (yyvsp[-2].string));
  strcpy(lexeme.lex[5], (yyvsp[-1].string));
  strcpy(lexeme.lex[6], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4263 "grm_parsegrammar.tab.c"
    break;

  case 308: /* rule_enum: EMISSION MONOSEGMENT EMISSION NONTERM  */
#line 2202 "grm_parsegrammar.y"
{           
  ynr = 38;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4277 "grm_parsegrammar.tab.c"
    break;

  case 309: /* rule_enum: EMISSION MONOSEGMENT EMISSION NONTERM DIST_NAME  */
#line 2213 "grm_parsegrammar.y"
{           
  ynr = 38;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4292 "grm_parsegrammar.tab.c"
    break;

  case 310: /* rule_enum: EMISSION MONOSEGMENT EMISSION NONTERM DIST_NAME DIST_NAME  */
#line 2225 "grm_parsegrammar.y"
{           
  ynr = 38;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4308 "grm_parsegrammar.tab.c"
    break;

  case 311: /* rule_enum: EMISSION MONOSEGMENT EMISSION NONTERM DIST_NAME DIST_NAME DIST_NAME  */
#line 2238 "grm_parsegrammar.y"
{           
  ynr = 38;
  lexeme.l = 7;
  strcpy(lexeme.lex[0], (yyvsp[-6].string));
  strcpy(lexeme.lex[1], (yyvsp[-5].string));
  strcpy(lexeme.lex[2], (yyvsp[-4].string));
  strcpy(lexeme.lex[3], (yyvsp[-3].string));
  strcpy(lexeme.lex[4], (yyvsp[-2].string));
  strcpy(lexeme.lex[5], (yyvsp[-1].string));
  strcpy(lexeme.lex[6], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4325 "grm_parsegrammar.tab.c"
    break;

  case 312: /* rule_enum: NONTERM EMISSION MONOSEGMENT EMISSION  */
#line 2252 "grm_parsegrammar.y"
{           
  ynr = 39;
  lexeme.l = 4;
  strcpy(lexeme.lex[0], (yyvsp[-3].string));
  strcpy(lexeme.lex[1], (yyvsp[-2].string));
  strcpy(lexeme.lex[2], (yyvsp[-1].string));
  strcpy(lexeme.lex[3], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4339 "grm_parsegrammar.tab.c"
    break;

  case 313: /* rule_enum: NONTERM EMISSION MONOSEGMENT EMISSION DIST_NAME  */
#line 2263 "grm_parsegrammar.y"
{           
  ynr = 39;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4354 "grm_parsegrammar.tab.c"
    break;

  case 314: /* rule_enum: NONTERM EMISSION MONOSEGMENT EMISSION DIST_NAME DIST_NAME  */
#line 2275 "grm_parsegrammar.y"
{           
  ynr = 39;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4370 "grm_parsegrammar.tab.c"
    break;

  case 315: /* rule_enum: NONTERM EMISSION MONOSEGMENT EMISSION DIST_NAME DIST_NAME DIST_NAME  */
#line 2288 "grm_parsegrammar.y"
{           
  ynr = 39;
  lexeme.l = 7;
  strcpy(lexeme.lex[0], (yyvsp[-6].string));
  strcpy(lexeme.lex[1], (yyvsp[-5].string));
  strcpy(lexeme.lex[2], (yyvsp[-4].string));
  strcpy(lexeme.lex[3], (yyvsp[-3].string));
  strcpy(lexeme.lex[4], (yyvsp[-2].string));
  strcpy(lexeme.lex[5], (yyvsp[-1].string));
  strcpy(lexeme.lex[6], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4387 "grm_parsegrammar.tab.c"
    break;

  case 316: /* rule_enum: EMISSION LDISEGMENT NONTERM RDISEGMENT EMISSION  */
#line 2302 "grm_parsegrammar.y"
{           
  ynr = 40;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4402 "grm_parsegrammar.tab.c"
    break;

  case 317: /* rule_enum: EMISSION LDISEGMENT NONTERM RDISEGMENT EMISSION DIST_NAME  */
#line 2314 "grm_parsegrammar.y"
{           
  ynr = 40;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4418 "grm_parsegrammar.tab.c"
    break;

  case 318: /* rule_enum: EMISSION LDISEGMENT NONTERM RDISEGMENT EMISSION DIST_NAME DIST_NAME  */
#line 2327 "grm_parsegrammar.y"
{           
  ynr = 40;
  lexeme.l = 7;
  strcpy(lexeme.lex[0], (yyvsp[-6].string));
  strcpy(lexeme.lex[1], (yyvsp[-5].string));
  strcpy(lexeme.lex[2], (yyvsp[-4].string));
  strcpy(lexeme.lex[3], (yyvsp[-3].string));
  strcpy(lexeme.lex[4], (yyvsp[-2].string));
  strcpy(lexeme.lex[5], (yyvsp[-1].string));
  strcpy(lexeme.lex[6], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4435 "grm_parsegrammar.tab.c"
    break;

  case 319: /* rule_enum: EMISSION LDISEGMENT NONTERM RDISEGMENT EMISSION DIST_NAME DIST_NAME DIST_NAME  */
#line 2341 "grm_parsegrammar.y"
{           
  ynr = 40;
  lexeme.l = 8;
  strcpy(lexeme.lex[0], (yyvsp[-7].string));
  strcpy(lexeme.lex[1], (yyvsp[-6].string));
  strcpy(lexeme.lex[2], (yyvsp[-5].string));
  strcpy(lexeme.lex[3], (yyvsp[-4].string));
  strcpy(lexeme.lex[4], (yyvsp[-3].string));
  strcpy(lexeme.lex[5], (yyvsp[-2].string));
  strcpy(lexeme.lex[6], (yyvsp[-1].string));
  strcpy(lexeme.lex[7], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4453 "grm_parsegrammar.tab.c"
    break;

  case 320: /* rule_enum: EMISSION EMISSION NONTERM EMISSION NONTERM  */
#line 2356 "grm_parsegrammar.y"
{
  ynr = 41;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4468 "grm_parsegrammar.tab.c"
    break;

  case 321: /* rule_enum: EMISSION EMISSION NONTERM EMISSION NONTERM DIST_NAME  */
#line 2368 "grm_parsegrammar.y"
{
  ynr = 41;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4484 "grm_parsegrammar.tab.c"
    break;

  case 322: /* rule_enum: NONTERM EMISSION NONTERM EMISSION EMISSION  */
#line 2381 "grm_parsegrammar.y"
{
  ynr = 42;
  lexeme.l = 5;
  strcpy(lexeme.lex[0], (yyvsp[-4].string));
  strcpy(lexeme.lex[1], (yyvsp[-3].string));
  strcpy(lexeme.lex[2], (yyvsp[-2].string));
  strcpy(lexeme.lex[3], (yyvsp[-1].string));
  strcpy(lexeme.lex[4], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4499 "grm_parsegrammar.tab.c"
    break;

  case 323: /* rule_enum: NONTERM EMISSION NONTERM EMISSION EMISSION DIST_NAME  */
#line 2393 "grm_parsegrammar.y"
{
  ynr = 42;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4515 "grm_parsegrammar.tab.c"
    break;

  case 324: /* rule_enum: EMISSION EMISSION NONTERM EMISSION NONTERM EMISSION  */
#line 2406 "grm_parsegrammar.y"
{
  ynr = 43;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4531 "grm_parsegrammar.tab.c"
    break;

  case 325: /* rule_enum: EMISSION EMISSION NONTERM EMISSION NONTERM EMISSION DIST_NAME  */
#line 2419 "grm_parsegrammar.y"
{
  ynr = 43;
  lexeme.l = 7;
  strcpy(lexeme.lex[0], (yyvsp[-6].string));
  strcpy(lexeme.lex[1], (yyvsp[-5].string));
  strcpy(lexeme.lex[2], (yyvsp[-4].string));
  strcpy(lexeme.lex[3], (yyvsp[-3].string));
  strcpy(lexeme.lex[4], (yyvsp[-2].string));
  strcpy(lexeme.lex[5], (yyvsp[-1].string));
  strcpy(lexeme.lex[6], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4548 "grm_parsegrammar.tab.c"
    break;

  case 326: /* rule_enum: EMISSION NONTERM EMISSION NONTERM EMISSION EMISSION  */
#line 2433 "grm_parsegrammar.y"
{
  ynr = 44;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4564 "grm_parsegrammar.tab.c"
    break;

  case 327: /* rule_enum: EMISSION NONTERM EMISSION NONTERM EMISSION EMISSION DIST_NAME  */
#line 2446 "grm_parsegrammar.y"
{
  ynr = 44;
  lexeme.l = 7;
  strcpy(lexeme.lex[0], (yyvsp[-6].string));
  strcpy(lexeme.lex[1], (yyvsp[-5].string));
  strcpy(lexeme.lex[2], (yyvsp[-4].string));
  strcpy(lexeme.lex[3], (yyvsp[-3].string));
  strcpy(lexeme.lex[4], (yyvsp[-2].string));
  strcpy(lexeme.lex[5], (yyvsp[-1].string));
  strcpy(lexeme.lex[6], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4581 "grm_parsegrammar.tab.c"
    break;

  case 328: /* rule_enum: EMISSION EMISSION NONTERM EMISSION EMISSION NONTERM  */
#line 2460 "grm_parsegrammar.y"
{
  ynr = 45;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4597 "grm_parsegrammar.tab.c"
    break;

  case 329: /* rule_enum: EMISSION EMISSION NONTERM EMISSION EMISSION NONTERM DIST_NAME  */
#line 2473 "grm_parsegrammar.y"
{
  ynr = 45;
  lexeme.l = 7;
  strcpy(lexeme.lex[0], (yyvsp[-6].string));
  strcpy(lexeme.lex[1], (yyvsp[-5].string));
  strcpy(lexeme.lex[2], (yyvsp[-4].string));
  strcpy(lexeme.lex[3], (yyvsp[-3].string));
  strcpy(lexeme.lex[4], (yyvsp[-2].string));
  strcpy(lexeme.lex[5], (yyvsp[-1].string));
  strcpy(lexeme.lex[6], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4614 "grm_parsegrammar.tab.c"
    break;

  case 330: /* rule_enum: NONTERM EMISSION EMISSION NONTERM EMISSION EMISSION  */
#line 2487 "grm_parsegrammar.y"
{
  ynr = 46;
  lexeme.l = 6;
  strcpy(lexeme.lex[0], (yyvsp[-5].string));
  strcpy(lexeme.lex[1], (yyvsp[-4].string));
  strcpy(lexeme.lex[2], (yyvsp[-3].string));
  strcpy(lexeme.lex[3], (yyvsp[-2].string));
  strcpy(lexeme.lex[4], (yyvsp[-1].string));
  strcpy(lexeme.lex[5], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4630 "grm_parsegrammar.tab.c"
    break;

  case 331: /* rule_enum: NONTERM EMISSION EMISSION NONTERM EMISSION EMISSION DIST_NAME  */
#line 2500 "grm_parsegrammar.y"
{
  ynr = 46;
  lexeme.l = 7;
  strcpy(lexeme.lex[0], (yyvsp[-6].string));
  strcpy(lexeme.lex[1], (yyvsp[-5].string));
  strcpy(lexeme.lex[2], (yyvsp[-4].string));
  strcpy(lexeme.lex[3], (yyvsp[-3].string));
  strcpy(lexeme.lex[4], (yyvsp[-2].string));
  strcpy(lexeme.lex[5], (yyvsp[-1].string));
  strcpy(lexeme.lex[6], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4647 "grm_parsegrammar.tab.c"
    break;

  case 332: /* rule_enum: EMISSION EMISSION NONTERM EMISSION EMISSION NONTERM EMISSION  */
#line 2514 "grm_parsegrammar.y"
{
  ynr = 47;
  lexeme.l = 7;
  strcpy(lexeme.lex[0], (yyvsp[-6].string));
  strcpy(lexeme.lex[1], (yyvsp[-5].string));
  strcpy(lexeme.lex[2], (yyvsp[-4].string));
  strcpy(lexeme.lex[3], (yyvsp[-3].string));
  strcpy(lexeme.lex[4], (yyvsp[-2].string));
  strcpy(lexeme.lex[5], (yyvsp[-1].string));
  strcpy(lexeme.lex[6], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4664 "grm_parsegrammar.tab.c"
    break;

  case 333: /* rule_enum: EMISSION EMISSION NONTERM EMISSION EMISSION NONTERM EMISSION DIST_NAME  */
#line 2528 "grm_parsegrammar.y"
{
  ynr = 47;
  lexeme.l = 8;
  strcpy(lexeme.lex[0], (yyvsp[-7].string));
  strcpy(lexeme.lex[1], (yyvsp[-6].string));
  strcpy(lexeme.lex[2], (yyvsp[-5].string));
  strcpy(lexeme.lex[3], (yyvsp[-4].string));
  strcpy(lexeme.lex[4], (yyvsp[-3].string));
  strcpy(lexeme.lex[5], (yyvsp[-2].string));
  strcpy(lexeme.lex[6], (yyvsp[-1].string));
  strcpy(lexeme.lex[7], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4682 "grm_parsegrammar.tab.c"
    break;

  case 334: /* rule_enum: EMISSION NONTERM EMISSION EMISSION NONTERM EMISSION EMISSION  */
#line 2543 "grm_parsegrammar.y"
{
  ynr = 48;
  lexeme.l = 7;
  strcpy(lexeme.lex[0], (yyvsp[-6].string));
  strcpy(lexeme.lex[1], (yyvsp[-5].string));
  strcpy(lexeme.lex[2], (yyvsp[-4].string));
  strcpy(lexeme.lex[3], (yyvsp[-3].string));
  strcpy(lexeme.lex[4], (yyvsp[-2].string));
  strcpy(lexeme.lex[5], (yyvsp[-1].string));
  strcpy(lexeme.lex[6], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4699 "grm_parsegrammar.tab.c"
    break;

  case 335: /* rule_enum: EMISSION NONTERM EMISSION EMISSION NONTERM EMISSION EMISSION DIST_NAME  */
#line 2557 "grm_parsegrammar.y"
{ 
  ynr = 48;
  lexeme.l = 8;
  strcpy(lexeme.lex[0], (yyvsp[-7].string));
  strcpy(lexeme.lex[1], (yyvsp[-6].string));
  strcpy(lexeme.lex[2], (yyvsp[-5].string));
  strcpy(lexeme.lex[3], (yyvsp[-4].string));
  strcpy(lexeme.lex[4], (yyvsp[-3].string));
  strcpy(lexeme.lex[5], (yyvsp[-2].string));
  strcpy(lexeme.lex[6], (yyvsp[-1].string));
  strcpy(lexeme.lex[7], (yyvsp[0].string));
  if (rna_rule_enum_write(rnr, ynr, nt_idx, ((struct yyparse_s *)yyparse_param)->Gr, lexeme, ((struct yyparse_s *)yyparse_param)->verbose) != eslOK) grammar_fatal("error in rule %d\n", ynr);
}
#line 4717 "grm_parsegrammar.tab.c"
    break;


#line 4721 "grm_parsegrammar.tab.c"

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
      yyerror (yyparse_param, YY_("syntax error"));
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
                      yytoken, &yylval, yyparse_param);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yyparse_param);
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
  yyerror (yyparse_param, YY_("memory exhausted"));
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
                  yytoken, &yylval, yyparse_param);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yyparse_param);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 2573 "grm_parsegrammar.y"
 /* user generated code */


/*****************************************************************
 * 0. yacc-req'd functions
 *****************************************************************/
void yyerror(void *yyparse_param, char const *s)
{
#if 1
  grammar_fatal("yyerror: %s\n", s);
#else
  fprintf(stderr, "yyerror: %s\n", s);
#endif
}

int yywrap()
{
  return 1;
}
/*----------------- end, yacc-req'd functions  ----------------*/

/*****************************************************************
 * 1. External function
 *****************************************************************/

/* Function:  Grammar_Parse()
 * Incept:    ER, Tue Aug 28 10:17:17 EDT 2007 [janelia]
 *
 * Purpose:   Given a file with a grammar syntax, 
 *            parse the file to fill a grammar structure.
 *            Grammar is allocated here and freed by caller.
 *
 * Args:      FILE  - 
 *
 * Returns:   G - the grammar structure.
 *
 */
GRAMMAR *
Grammar_Parse(FILE *fp, char *gfilename, 
	      enum param_e paramtype, int nparamfile, char **paramfile, double *cweight,
	      int backrules, int force_min_loop, int force_min_stem,
	      int force_wccomp, char *errbuf, int verbose)
{
  struct yyparse_s *yyparse_param = NULL;
  GRAMMAR          *G = NULL;
  FILE             *file;
  double            wgt;
  int               cf;     /* number of countfiles */
  int               status;
  
  if ((G = Grammar_Create(gfilename, errbuf)) == NULL) goto ERROR; 

  ESL_ALLOC(yyparse_param, sizeof(struct yyparse_s));
  yyparse_param->Gr      = G;
  yyparse_param->verbose = verbose;
  
  do {
    /* store data in the GRAMMAR structure */
    yyparse((void *)yyparse_param);
 }
  while (!feof(fp));
  if (yyparse_param != NULL) free(yyparse_param);

  /* Read in parameters from file, if given separatedly from grmfile. */
  if (paramfile != NULL) {
    switch(paramtype) {
    case COUNT:
     if ((status = Grammar_ZeroCounts(G, errbuf)) != eslOK) goto ERROR;
     break;
    case LPROB:
      break;
    case SCORE:
      break;
    default: ESL_XFAIL(eslFAIL, errbuf, "unknown type of grammar parameters");
    }

    for (cf = 0; cf < nparamfile; cf ++) {
      if ((file = fopen(paramfile[cf], "r")) == NULL)
	ESL_XFAIL(eslFAIL, errbuf, "Failed to open count file %s", paramfile[cf]);
      if (verbose) printf("reading param file: %s\n", paramfile[cf]);
      if (cweight != NULL) wgt = cweight[cf]; else wgt = 1.0;
      if ((status = Grammar_Read(file, G, paramtype, wgt, errbuf, FALSE)) != eslOK) goto ERROR;
      fclose(file);
    }
  }

  /* After parsing finish setting up the grammar */
  if ((status = Grammar_Set(G, backrules, errbuf, verbose)) != eslOK) goto ERROR;

  /* Set optional parameters. Ignore constrain if it cannot be imposed.
   */
  G->force_wccomp = force_wccomp;
  if (force_min_loop > G->min_loop) G->force_min_loop = force_min_loop;
  if (force_min_stem > G->min_stem) {
    if (G->S > 0) G->force_min_stem = force_min_stem;
    else printf("Ignoring force_min_stem option. min_stem is %d\n", G->min_stem);
  }


  
  /* Validate data structure in G */
  if (nparamfile > 0) {
    if ((status = GMX_GrammarFitNormalize(G, FALSE, 0.0, NULL, NULL, NULL, NULL, NULL, errbuf, FALSE)) != eslOK) goto ERROR;
  }
  else {
    if ((status = Grammar_Validate(G, errbuf)) != eslOK) goto ERROR;
   }


  return G;

 ERROR: 
  if (G != NULL) Grammar_Destroy(G);
  if (yyparse_param != NULL) free(yyparse_param);
  return NULL;
}

/*----------------- end, external functions  ----------------*/

/*****************************************************************
 * 2. Local functions
 *****************************************************************/
int 
add_coord(ATOM *iatom, char *coord, int offset, int verbose)
{
  int idx;

  idx = iatom->ncoords++;

  if      (!strcmp(coord, "i")) iatom->coordbase[idx] = COORD_I;
  else if (!strcmp(coord, "j")) iatom->coordbase[idx] = COORD_J;
  else if (!strcmp(coord, "k")) iatom->coordbase[idx] = COORD_K;
  else if (!strcmp(coord, "l")) iatom->coordbase[idx] = COORD_L;
  else grammar_fatal("add_coord() do not recognize this coord %s", coord);

  iatom->offset[idx] = offset;

  if (verbose) printf("  coord %s (%d) offset %d\n", coord, idx, offset);

  return eslOK;
}

int 
add_context(ATOM *iatom, char *context, int offset, int verbose)
{
  int idx;

  idx = iatom->ncontexts++;

  if      (!strcmp(context, "i")) iatom->contextbase[idx] = COORD_I;
  else if (!strcmp(context, "j")) iatom->contextbase[idx] = COORD_J;
  else if (!strcmp(context, "k")) iatom->contextbase[idx] = COORD_K;
  else if (!strcmp(context, "l")) iatom->contextbase[idx] = COORD_L;
  else grammar_fatal("add_coord() do not recognize this coord %s", context);

  iatom->contextoffset[idx] = offset;

  if (verbose) printf("  context %s (%d) offset %d atom_ncontexts %d\n", context, idx, offset, iatom->ncontexts);

  return eslOK;
}

enum basepair_e
get_basepairtype(char *bptype)
{
  enum basepair_e basepairtype = BPTYPE_UNKNOWN;
  
  if      (strstr(bptype, "WW")) basepairtype = WW_C; 
  else if (strstr(bptype, "ww")) basepairtype = WW_T; 
  else if (strstr(bptype, "WH")) basepairtype = WH_C; 
  else if (strstr(bptype, "wh")) basepairtype = WH_T; 
  else if (strstr(bptype, "WS")) basepairtype = WS_C; 
  else if (strstr(bptype, "ws")) basepairtype = WS_T; 
  else if (strstr(bptype, "HW")) basepairtype = HW_C; 
  else if (strstr(bptype, "hw")) basepairtype = HW_T; 
  else if (strstr(bptype, "HH")) basepairtype = HH_C; 
  else if (strstr(bptype, "hh")) basepairtype = HH_T; 
  else if (strstr(bptype, "HS")) basepairtype = HS_C; 
  else if (strstr(bptype, "hs")) basepairtype = HS_T; 
  else if (strstr(bptype, "SW")) basepairtype = SW_C; 
  else if (strstr(bptype, "sw")) basepairtype = SW_T; 
  else if (strstr(bptype, "SH")) basepairtype = SH_C; 
  else if (strstr(bptype, "sh")) basepairtype = SH_T; 
  else if (strstr(bptype, "SS")) basepairtype = SS_C; 
  else if (strstr(bptype, "ss")) basepairtype = SS_T; 
  else  grammar_fatal("could not identify basepairtype %s\n", bptype);
  
  return basepairtype;
}

int 
is_base_pair(char *s1, char *s2)
{
  return s1[0] == s2[0] && s2[1] == '\'';
}

int
is_default_score (int L, ESL_DSQ *dsq)
{
  int is_default = 0;
  int l;

  /* in the RNA alphabet 15 is the Digit for the
   * the "any" character (N or X)
   */
  for (l = 1; l <= L; l ++) 
    if (dsq[l] != 15) break;
  
  if (l == L+1) is_default = 1;

  return is_default;
}

/* Function: rna_atom_add_to_rule()
 * Incept:    ER,Wed Apr 16 09:17:50 EDT 2008   [janelia]
 *
 * Purpose: Adds a new atom in a production rule
 *
 * Returns: <eslOK> on success; 
 */
int
rna_atom_add_to_rule(int rnr, int w, ATOM *iatom, GRAMMAR *G, struct lexeme_s lexeme, int verbose) 
{
  NT    *nt;            /* pointer to nonterminal */
  RULE  *R;             /* the rule at hand */
  ATOM  *A;             /* pointer to atom */
  int    r;
  int    add_ntcontext; /* not in this mode */
 
   if (is_new_rule == TRUE)
    {
      if (rna_rule_atomlist_write(rnr, w, G) != eslOK) 
	grammar_fatal("error in rna_rule %d\n", rnr); 
     }
  
  nt = &(G->nt[w]);  /* nt pointer */
  r  = nt->nrules-1; /* rule index */
  R  = &(nt->pr[r]);
  A  = &(R->atom[R->natoms]);

  R->natoms ++;

  if (r < 0) 
    grammar_fatal("error in rna_atom_add_to_rule() rule %d has negative index %d\n", rnr, r);

  switch(iatom->atomtype) {
  case EMISSION_ATOM:
    if (rna_atom_add_to_rule_emission(r, w, *iatom, G, lexeme) != eslOK) 
      grammar_fatal("error in rna_atom_add_to_rule() rule %d emission atom\n", rnr);
    break;
  case NONTERMINAL_ATOM:
    if (rna_atom_add_to_rule_nonterminal(r, w, *iatom, G, lexeme) != eslOK) 
      grammar_fatal("error in rna_atom_add_to_rule() rule %d nonterminal atom\n", rnr); 
    break;
  case MONOSEGMENT_ATOM:
    if (rna_atom_add_to_rule_monosegment(r, w, *iatom, G, lexeme) != eslOK) 
      grammar_fatal("error in rna_atom_add_to_rule() rule %d monosegment atom\n", rnr); 
    break;
  case DISEGMENT_ATOM:
    if (rna_atom_add_to_rule_disegment(r, w, *iatom, G, lexeme) != eslOK) 
      grammar_fatal("error in rna_atom_add_to_rule() rule %d disegment atom\n", rnr); 
    break;
  default: 
    grammar_fatal("no such atomtype");
  }

  add_ntcontext = FALSE; /* not in this mode. context is given by the emissions */
  if (rna_atom_write(A, R, G, add_ntcontext, verbose) != eslOK) 
    grammar_fatal("rna_atom_add_to_rule() failed at atom %s rule %s nt %s.", 
		  A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname); 

  rna_rule_syntax_add(R, A->atom_syntax);
  
  rna_atom_clear(iatom);

  if (verbose)  
    printf("rule %d nt_idx %d atom #%d %s \n", r, R->nt_idx, R->natoms, A->atom_syntax);

  return eslOK;
}


/* Function: rna_atom_add_to_rule_emission()
 * Incept:    ER,Wed Apr 16 09:17:50 EDT 2008   [janelia]
 *
 * Purpose: Adds a new emission atom in a production rule
 *
 * Returns: <eslOK> on success; 
 */
int
rna_atom_add_to_rule_emission(int r, int w, ATOM iatom, GRAMMAR *G, struct lexeme_s lexeme) 
{
  NT    *nt;         /* pointer to nonterminal */
  TDIST *tdist;      /* pointer to transition distribution */
  RULE  *R;          /* the rule at hand */
  ATOM  *A;          /* pointer to atom */
  int    a;          /* atom index */
  int    tofw;       /* index for transition distribution (td) */
  int    c;          /* index for coordinates */
  int    t;          /* index for max_nctxts */
  int    x;          /* index for contexts */
  int    bp;         /* index for basepairs */
  int    cbp;        /* index for context basepairs */
 
  nt    = &(G->nt[w]);       /* nt pointer */
  tofw  = nt->tdist_idx;     /* tdist index */
  tdist = &(G->tdist[tofw]); /* tdist pointer */
  R     = &(nt->pr[r]);
  a     = R->natoms-1;
  A     = &(R->atom[a]);

  A->atomtype                  = iatom.atomtype;
  A->ncoords                   = iatom.ncoords;           /* number of emissions */
  for (c = 0; c < A->ncoords; c++) {
    A->coordbase[c]            = iatom.coordbase[c];
    A->offset[c]               = iatom.offset[c];           
  }
  A->has_basepair              = iatom.has_basepair;      /* number of basepairs */
  A->nbasepairs                = iatom.nbasepairs;
  for (bp = 0; bp < A->nbasepairs; bp++) {
    A->bp[bp].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[0]);
    A->bp[bp].basepair_coordl_idx = iatom.bp[bp].basepair_coordl_idx;
    A->bp[bp].basepair_coordr_idx = iatom.bp[bp].basepair_coordr_idx;
    A->bp[bp].force_wccomp        = iatom.bp[bp].force_wccomp;
  } 
  A->max_nctxts                = iatom.max_nctxts;        /* max_nctxts */
  for (t = 0; t < A->max_nctxts; t++) 
    A->maxctxt_basetag[t]      = iatom.maxctxt_basetag[t];    
  A->ncontexts = iatom.ncontexts;                         /* context */
  for (x = 0; x < A->ncontexts; x ++) {
    A->contextbase[x]   = iatom.contextbase[x];
    A->contextoffset[x] = iatom.contextoffset[x];
  }
  A->ncbasepairs               = iatom.ncbasepairs;
  for (cbp = 0; cbp < A->ncbasepairs; cbp++) {
    A->cbp[cbp].basepair_coordl_idx = iatom.cbp[bp].basepair_coordl_idx;
    A->cbp[cbp].basepair_coordr_idx = iatom.cbp[bp].basepair_coordr_idx;
    A->cbp[cbp].force_wccomp        = iatom.cbp[bp].force_wccomp;
  } 
  strcpy(A->atom_syntax, lexeme.lex[0]);                  /* atom name  */
  A->nedists                   = 1;              
  strcpy(A->edist_name[0], (lexeme.l > 2)? lexeme.lex[2] : "e0"); /* edist name */
  A->nldists                   = 0;              

  return eslOK;
}

/* Function: rna_atom_add_to_rule_nonterminal()
 * Incept:    ER,Wed Apr 16 09:17:50 EDT 2008   [janelia]
 *
 * Purpose: Adds a new nonterminal atom in a production rule
 *
 * Returns: <eslOK> on success; 
 */
int
rna_atom_add_to_rule_nonterminal(int r, int w, ATOM iatom, GRAMMAR *G, struct lexeme_s lexeme) 
{
  NT    *nt;         /* pointer to nonterminal */
  TDIST *tdist;      /* pointer to transition distribution */
  RULE  *R;          /* the rule at hand */
  ATOM  *A;          /* pointer to atom */
  int    a;          /* atom index */
  int    tofw;       /* index for transition distribution (td) */
  int    c;          /* index for coordinates */
  int    t;          /* index for contexts */
  int    x;          /* index for contexts */
  
  nt    = &(G->nt[w]);       /* nt pointer */
  tofw  = nt->tdist_idx;     /* tdist index */
  tdist = &(G->tdist[tofw]); /* tdist pointer */
  R     = &(nt->pr[r]);
  a     = R->natoms-1;
  A     = &(R->atom[a]);

  A->atomtype                  = iatom.atomtype;
  A->ncoords                   = iatom.ncoords;           /* number of emissions */
  for (c = 0; c < A->ncoords; c++) {
    A->coordbase[c]            = iatom.coordbase[c];
    A->offset[c]               = iatom.offset[c];           
  }
  A->max_nctxts                = iatom.max_nctxts;        /* context */
  for (t = 0; t < A->max_nctxts; t++) 
    A->maxctxt_basetag[t]      = iatom.maxctxt_basetag[t];             
   strcpy(A->atom_syntax, lexeme.lex[0]);   /* atom name  */
  A->ncontexts = iatom.ncontexts;                         /* context */
  for (x = 0; x < A->ncontexts; x ++) {
    A->contextbase[x]   = iatom.contextbase[x];
    A->contextoffset[x] = iatom.contextoffset[x];
  }
  A->nedists                   = 0;              
  A->nldists                   = 0;              
  A->has_basepair              = FALSE;
  A->nbasepairs                = 0;
  A->ncbasepairs               = 0;
 
  return eslOK;
}

/* Function: rna_atom_add_to_rule_nonterminal_di()
 * Incept:    ER, Fri Aug 10 08:45:03 EDT 2012, [janelia]
 *
 * Purpose: Adds a new nonterminal_di atom in a production rule
 *
 * Returns: <eslOK> on success; 
 */
int
rna_atom_add_to_rule_nonterminal_di(int r, int w, ATOM iatom, GRAMMAR *G, struct lexeme_s lexeme) 
{
  NT    *nt;         /* pointer to nonterminal */
  TDIST *tdist;      /* pointer to transition distribution */
  RULE  *R;          /* the rule at hand */
  ATOM  *A;          /* pointer to atom */
  int    a;          /* atom index */
  int    tofw;       /* index for transition distribution (td) */
  int    c;          /* index for coordinates */
  int    t;          /* index for contexts */
  int    x;          /* index for contexts */
  
  nt    = &(G->nt[w]);       /* nt pointer */
  tofw  = nt->tdist_idx;     /* tdist index */
  tdist = &(G->tdist[tofw]); /* tdist pointer */
  R     = &(nt->pr[r]);
  a     = R->natoms-1;
  A     = &(R->atom[a]);

  A->atomtype                  = iatom.atomtype;
  A->ncoords                   = iatom.ncoords;           /* number of emissions */
  for (c = 0; c < A->ncoords; c++) {
    A->coordbase[c]            = iatom.coordbase[c];
    A->offset[c]               = iatom.offset[c];           
  }
  A->max_nctxts                = iatom.max_nctxts;        /* context */
  for (t = 0; t < A->max_nctxts; t++) 
    A->maxctxt_basetag[t]      = iatom.maxctxt_basetag[t];             
   strcpy(A->atom_syntax, lexeme.lex[0]);   /* atom name  */
  A->ncontexts = iatom.ncontexts;                         /* context */
  for (x = 0; x < A->ncontexts; x ++) {
    A->contextbase[x]   = iatom.contextbase[x];
    A->contextoffset[x] = iatom.contextoffset[x];
  }
  A->nedists                   = 0;              
  A->nldists                   = 0;              
  A->has_basepair              = FALSE;
  A->nbasepairs                = 0;
  A->ncbasepairs               = 0;
 
  return eslOK;
}

/* Function: rna_atom_add_to_rule_monosegment()
 * Incept:    ER,Wed Apr 16 09:17:50 EDT 2008   [janelia]
 *
 * Purpose: Adds a new monosegment atom in a production rule
 *
 * Returns: <eslOK> on success; 
 */
int
rna_atom_add_to_rule_monosegment(int r, int w, ATOM iatom, GRAMMAR *G, struct lexeme_s lexeme) 
{
  NT    *nt;         /* pointer to nonterminal */
  TDIST *tdist;      /* pointer to transition distribution */
  RULE  *R;          /* the rule at hand */
  ATOM  *A;          /* pointer to atom */
  int    a;          /* atom index */
  int    tofw;       /* index for transition distribution (td) */
  int    c;          /* index for coordinates */
  int    x;          /* index for contexts */
 
  nt    = &(G->nt[w]);       /* nt pointer */
  tofw  = nt->tdist_idx;     /* tdist index */
  tdist = &(G->tdist[tofw]); /* tdist pointer */
  R     = &(nt->pr[r]);
  a     = R->natoms-1;
  A     = &(R->atom[a]);

  A->atomtype                  = iatom.atomtype;
  A->has_basepair              = FALSE;
  A->nbasepairs                = 0;
  A->ncbasepairs               = 0;
  A->ncoords                   = iatom.ncoords;              
  for (c = 0; c < A->ncoords; c++) {
    A->coordbase[c]            = iatom.coordbase[c];
    A->offset[c]               = iatom.offset[c];           
  }
  A->ncontexts = iatom.ncontexts;                         /* context */
  for (x = 0; x < A->ncontexts; x ++) {
    A->contextbase[x]   = iatom.contextbase[x];
    A->contextoffset[x] = iatom.contextoffset[x];
  }
  A->nedists                   = 0;              
  strcpy(A->atom_syntax, lexeme.lex[0]); /* atom name  */
  A->nldists                   = 1;              
  strcpy(A->ldist_name[0], (lexeme.l > 1)? lexeme.lex[1] : "l0"); /* ldist name */

  return eslOK;
}

/* Function: rna_atom_add_to_rule_disegment()
 * Incept:    ER,Wed Apr 16 09:17:50 EDT 2008   [janelia]
 *
 * Purpose: Adds a new disegment atom in a production rule
 *
 * Returns: <eslOK> on success; 
 */
int
rna_atom_add_to_rule_disegment(int r, int w, ATOM iatom, GRAMMAR *G, struct lexeme_s lexeme) 
{
  NT    *nt;         /* pointer to nonterminal */
  TDIST *tdist;      /* pointer to transition distribution */
  RULE  *R;          /* the rule at hand */
  ATOM  *A;          /* pointer to atom */
  int    a;          /* atom index */
  int    tofw;       /* index for transition distribution (td) */
  int    c;          /* index for coordinates */
  int    x;          /* index for contexts */
 
  nt    = &(G->nt[w]);       /* nt pointer */
  tofw  = nt->tdist_idx;     /* tdist index */
  tdist = &(G->tdist[tofw]); /* tdist pointer */
  R     = &(nt->pr[r]);
  a     = R->natoms-1;
  A     = &(R->atom[a]);

  A->atomtype                  = iatom.atomtype;
  A->ncoords                   = iatom.ncoords;              /* monosegment */
  for (c = 0; c < A->ncoords; c++) {
    A->coordbase[c]            = iatom.coordbase[c];
    A->offset[c]               = iatom.offset[c]; 
  }
  A->ncontexts = iatom.ncontexts;                         /* context */
  for (x = 0; x < A->ncontexts; x ++) {
    A->contextbase[x]   = iatom.contextbase[x];
    A->contextoffset[x] = iatom.contextoffset[x];
  }
  strcpy(A->atom_syntax, lexeme.lex[0]); /* atom name  */

  if      (!strcmp(A->atom_syntax, "d...^...d'")) /* tied disegment */ 
    {  
      if (rna_atom_add_to_rule_disegment_tied(nt, R, A, G, lexeme) != eslOK)
	grammar_fatal("rna_atom_add_to_rule_disegment_tied() failed. %s", A->atom_syntax);
    }
  else if (!strcmp(A->atom_syntax, "d...^...d")) /* untied_disegment */
    {
      if (rna_atom_add_to_rule_disegment_untied(nt, R, A, G, lexeme) != eslOK)
	grammar_fatal("rna_atom_add_to_rule_disegment_untied() failed. %s", A->atom_syntax);
    }
  else 
    grammar_fatal("rna_atom_add_to_rule_disegment() failed. %s", A->atom_syntax);

     
  return eslOK;
}

int
rna_atom_add_to_rule_disegment_tied(NT *nt, RULE *R, ATOM *A, GRAMMAR *G, struct lexeme_s lexeme)
{
  char ename[eslERRBUFSIZE];
  int  nedistf;             /* number of edists used for the final basepair */
  int  nedisti;             /* number of edists used for the internal basepairs */
  int  n, ns;               /* edist n */
  int  c, cs;               /* edist context */
  int  e;                   /* index for edists */

  A->has_basepair              = TRUE;
  A->nbasepairs                = 1;
  A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[0]);
  A->bp[0].basepair_coordl_idx = 0;
  A->bp[0].basepair_coordr_idx = 1;
  A->nldists                = 1;    
    
  nedisti = Integer_Power(4, 2);
  
  /* ldist + 2 edists name 
   *
   * default:              d...()...d'()
   *                       ldist:         l0
   *                       edist_idx = 0: e0_2_c
   *                       edist_idx = 1: e0_2_2
   *
   * specify ldist:        d...()...d'() ln
   *                       ldist:         ln
   *                       edist_idx = 0: e0_2_c
   *                       edist_idx = 1: e0_2_2
   *
   * specify the 2 edists: d...()...d'() en_2_c em_2_2
   *                       ldist:         l0
   *                       edist_idx = 0: en_2_c
   *                       edist_idx = 1: em_2_2
   *
   * specify the 3 dists:  d...()...d'() lk en_2_c em_2_2
   *                       ldist:         lk
   *                       edist_idx = 0: en_2_c
   *                       edist_idx = 1: em_2_2
   *
   */
  if      (lexeme.l == 1) {
    strcpy(A->ldist_name[0],    "l0");    
    sprintf(ename, "e0_2_%d", A->ncontexts);    
    nedistf = Integer_Power(4, A->ncontexts);
    for (e = 0; e < nedistf; e ++) strcpy(A->edist_name[e],         ename);
    for (e = 0; e < nedisti; e ++) strcpy(A->edist_name[nedistf+e], "e0_2_2");
  } 
  else if (lexeme.l == 2) {
    if      (strstr(lexeme.lex[1], "l")) 
      {
	strcpy(A->ldist_name[0], lexeme.lex[1]);
	sprintf(ename, "e0_2_%d", A->ncontexts);
	nedistf = Integer_Power(4, A->ncontexts);
	for (e = 0; e < nedistf; e ++) strcpy(A->edist_name[e],         ename);
	for (e = 0; e < nedisti; e ++) strcpy(A->edist_name[nedistf+e], "e0_2_2");
      }
    else return eslFAIL;
  }
  else if (lexeme.l == 3) {
    if      (strstr(lexeme.lex[1], "e") && strstr(lexeme.lex[2], "e")) 
      {

	strcpy(A->ldist_name[0], "l0"); 

	EnameNemitNcontext(lexeme.lex[1], NULL, &n, &c, NULL);
	/* a stacked pair */
	if (n != 2) return eslFAIL;
	if (c != 2) return eslFAIL;
	A->contextbase[0]   = COORD_I;
	A->contextbase[1]   = COORD_J;
	A->contextoffset[0] = -1;
 	A->contextoffset[1] = +1;
	nedistf = Integer_Power(4, A->ncontexts);
	sprintf(ename, "_2_%d", A->ncontexts);

	if (strstr(lexeme.lex[1], ename))  {
	  for (e = 0; e < nedistf; e ++) strcpy(A->edist_name[e],         lexeme.lex[1]); 
	}
	else return eslFAIL;
	if  (strstr(lexeme.lex[2], "_2_2")) {
	  for (e = 0; e < nedisti; e ++) strcpy(A->edist_name[nedistf+e], lexeme.lex[2]);
	} 
	else return eslFAIL;
      }
   else return eslFAIL;
  } 
  else if (lexeme.l == 4) {
    if      (strstr(lexeme.lex[1], "l") && strstr(lexeme.lex[2], "e") && strstr(lexeme.lex[3], "e")) 
      {
 	strcpy(A->ldist_name[0], lexeme.lex[1]);

	EnameNemitNcontext(lexeme.lex[2], NULL, &n,  &c,  NULL);
	EnameNemitNcontext(lexeme.lex[3], NULL, &ns, &cs, NULL);

	/* a stacked pair */
	if (n  != 2 || ns != 2) return eslFAIL;
	if (c  != 2 && c  != 0) return eslFAIL;
	if (cs != 2 && cs != 0) return eslFAIL;
	A->ncontexts = c; 
	if (c == 2) {
	  A->contextbase[0]   = COORD_I;
	  A->contextbase[1]   = COORD_J;
	  A->contextoffset[0] = -1;
	  A->contextoffset[1] = +1;
	}
	
	nedistf = Integer_Power(4, A->ncontexts);
	sprintf(ename, "_%d_%d", n, c);
	if (strstr(lexeme.lex[2], ename))  {
	  for (e = 0; e < nedistf; e ++) strcpy(A->edist_name[e],         lexeme.lex[2]); 
	}
	else return eslFAIL;
	sprintf(ename, "_%d_%d", ns, cs);
	if (strstr(lexeme.lex[3], ename)) {
	  for (e = 0; e < nedisti; e ++) strcpy(A->edist_name[nedistf+e], lexeme.lex[3]);
	}
	else return eslFAIL;
      }
    else return eslFAIL;
  } 
  else return eslFAIL;
  
  A->nedists = nedistf + nedisti; 
  if (A->nedists > MAXEDISTS) return eslFAIL;

  return eslOK;

}
int
rna_atom_add_to_rule_disegment_untied(NT *nt, RULE *r, ATOM *A, GRAMMAR *G, struct lexeme_s lexeme)
{
  A->nedists      = 0;
  A->ncontexts    = 0;
  A->has_basepair = FALSE;
  A->nbasepairs   = 0;
  A->ncbasepairs  = 0;
  A->is_bck       = FALSE;

 /* ldist name */
  if (lexeme.l == 1) {
    A->nldists = 1;
    strcpy(A->ldist_name[0], "l0");
  }
  else if (lexeme.l == 2) {
    A->nldists = 1;

    if (strstr(lexeme.lex[1], "l")) strcpy(A->ldist_name[0], lexeme.lex[1]);
    else                            return eslFAIL;					   
  }
  else if (lexeme.l == 3) {
   A->nldists = 2;
   if (strstr(lexeme.lex[1], "l")) strcpy(A->ldist_name[0], lexeme.lex[1]);
   else                            return eslFAIL;					   
   if (strstr(lexeme.lex[2], "l")) strcpy(A->ldist_name[1], lexeme.lex[2]);
   else                            return eslFAIL;					   
  }
  else 
    return eslFAIL;
  
  return eslOK;
}


/* Function: rna_atom_basepairtype()
 * Incept:   ER, Mon Oct 29 11:03:34 EDT 2007 [janelia]
 *
 * Purpose:  
 *
 * Returns:  atom basepairtype
 *
 */
enum basepair_e
rna_atom_basepairtype(ATOM *A, char *ntname)
{
  enum basepair_e atom_basepairtype = BPTYPE_UNKNOWN;

  /* defined only for emission atoms (and a special type of disegment atoms) that have a basepair */
  if ( A->has_basepair == TRUE          &&
       (A->atomtype == EMISSION_ATOM ||  
        A->atomtype == DISEGMENT_ATOM  )  )
    {
      if (isalpha(ntname[0]) && ntname[1] == '_') {
	atom_basepairtype = get_basepairtype(ntname+2);
      }
      else if (isalpha(ntname[0]) && ntname[1] == '^' && isdigit(ntname[2])) {
	/* context is only allowed to canonical bps (WW_C) */
	atom_basepairtype = WW_C;
      }
      else if (isalpha(ntname[0])) {
	/* cWW by default */
	atom_basepairtype = WW_C;
      }
      else grammar_fatal("could not identify basepairtype for this atom %s and this nt %s\n", A->atom_syntax, ntname);
    }

  return atom_basepairtype;
}

void
rna_atom_clear(ATOM *A)
{
  A->nedists      = 0;
  A->nldists      = 0;
  A->ncoords      = 0;
  A->ncontexts    = 0;
  A->nbasepairs   = 0;
  A->ncbasepairs  = 0;
  A->max_nctxts   = -1;

  A->has_basepair = FALSE;
  A->is_bck       = FALSE;
}


/* adapted from C's qsort() */
void
atom_qsort(int *v, int *coord, int *offset, int left, int right) 
{
  int i;
  int last;

  if (left >= right) return;

  ESL_SWAP(v[left], v[(left+right)/2], int); 

  last = left;
  for (i = left+1; i <= right; i++) {

    if ((coord[v[i]] <  coord[v[left]])                                     || 
	(coord[v[i]] == coord[v[left]] && offset[v[i]] <  offset[v[left]])    )
      {
	last ++;
	ESL_SWAP(v[last], v[i], int); 
      } 
  }
  ESL_SWAP(v[left], v[last], int); 

  atom_qsort(v, coord, offset, left, last-1);
  atom_qsort(v, coord, offset, last+1, right);
}

/* Function: rna_atom_write()
 * Incept:    ER, Thu Oct 25 13:55:25 EDT 2007 [janelia]
 *
 * Purpose: write an rna grammar atom
 *
 * Returns: <eslOK> on success;
 *
 */
int 
rna_atom_write(ATOM *A, RULE *R, GRAMMAR *G, int add_ntcontext, int verbose)
{
  int c; 

  A->nt_idx = R->nt_idx;
  A->is_bck = FALSE;

  switch (A->atomtype) {
  case EPSILON_ATOM:
    if (rna_atom_write_epsilon(A, G) != eslOK)
      return eslFAIL;
    break;
     
  case NONTERMINAL_ATOM:
    if (rna_atom_write_nonterminal(A, G) != eslOK)
      return eslFAIL;
    break;

  case EMISSION_ATOM:
    if (rna_atom_write_emission(A, R, G, add_ntcontext, verbose) != eslOK)
      return eslFAIL;
    break;
    
  case MONOSEGMENT_ATOM:
    if (rna_atom_write_monosegment(A, G, verbose) != eslOK)
      return eslFAIL;
    break;
    
  case DISEGMENT_ATOM:
    if (rna_atom_write_disegment(A, R, G, verbose) != eslOK)
      return eslFAIL;
    break;
    
  default:
    return eslFAIL;
  }/* end of switch over atom types */
 

  /* determine whether rule has iterators */
  for (c = 0; c < A->ncoords; c++)
    {
      switch (A->coordbase[c]) {
      case COORD_I: break;
      case COORD_J: break;
      case COORD_K: 
	if (R->d1_iterator_state == ITERATOR_OFF) 
	  R->d1_iterator_state = ITERATOR_ON; 
	break;
      case COORD_L:
	if (A->nldists > 0) {

	  switch(G->ldist[A->ldist_idx[0]].type) {
	  case LDIST_SEMI: 
	    if (R->d1_iterator_state == ITERATOR_ON)
	      {
		if (R->d2_iterator_state != ITERATOR_TIED) 
		  R->d2_iterator_state = ITERATOR_SEMIJOINT; 
	      }
	    else if (R->d2_iterator_state == ITERATOR_OFF) 
	      {
		R->d2_iterator_state = ITERATOR_ON; 
	      }
	    break;
	  case LDIST_MONO: 
	    if (R->d1_iterator_state == ITERATOR_ON)
	      {
		if (R->d2_iterator_state != ITERATOR_TIED) 
		  R->d2_iterator_state = ITERATOR_JOINT; 
	      }
	    else if (R->d2_iterator_state == ITERATOR_OFF) 
	      {
		R->d2_iterator_state = ITERATOR_ON; 
	      }
	    break;
	  case LDIST_DI: 
	    /* D1/D2 independent loops */
	    R->d1_iterator_state = ITERATOR_ON;
	    R->d2_iterator_state = ITERATOR_ON;
	    break;
	  default: grammar_fatal("unrecognized type for rule %s", R->rule_syntax);
	  }


	}
   	break;
      default: grammar_fatal("unrecognized coord. Atom %s, coord %d,%d", A->atom_syntax, c, A->coordbase[c]);
	break;
      }     
    }

  return eslOK;
}

/* Function: rna_atom_write_disegment()
 * Incept:    ER, Thu Oct 25 13:55:25 EDT 2007 [janelia]
 *
 * Purpose: write an rna grammar emission disegment atom
 *
 * Returns: <eslOK> on success;
 *
 */
int 
rna_atom_write_disegment(ATOM *A, RULE *R, GRAMMAR *G, int verbose)
{
  A->nterm_idx = -1;

  /* tie iterators if so required */
  if (!strcmp(A->atom_syntax, "d...^...d'")) {
    A->has_basepair   = TRUE;
    A->nbasepairs     = 1;   /* This is not true, but irrelevant later on */

    /* write the stemrule structure */
    G->stemr[G->S].nt_idx   = R->nt_idx;
    G->stemr[G->S].rule_idx = G->nt[R->nt_idx].nrules-1;
    R->d2_iterator_state    = ITERATOR_TIED;
    R->is_stemr   = TRUE;
    R->stemr_idx  = G->S;
    G->S ++;

   /* set edists if this is a stem-length atom */
    if (rna_atom_write_edist_tieddisegment(A, R, G, verbose) != eslOK) 
      grammar_fatal("could not find edists for atom %s\n", A->atom_syntax);
  }
  else { /* joint disegment */
    A->has_basepair   = FALSE;
    A->nbasepairs     = 0;

    /* write the jdrule structure */
    G->jdr[G->K].nt_idx   = R->nt_idx;
    G->jdr[G->K].rule_idx = G->nt[R->nt_idx].nrules-1;
    R->d2_iterator_state  = ITERATOR_JOINT;
    R->is_jdr  = TRUE;
    R->jdr_idx = G->K;
    G->K ++;
  }
  
  if (rna_atom_write_segment_ldist(A, G, verbose) != eslOK) 
    grammar_fatal("could not find ldist %s for atom %s\n", A->ldist_name, A->atom_syntax);
  
  return eslOK;
}

/* Function: rna_atom_write_edist_tieddisegment()
 * Incept:    ER, Fri Nov 16 18:14:21 EST 2007 [janelia]
 *
 * Purpose: write the edist(s) for a rna grammar tied_disegment atom
 *
 * Returns: <eslOK> on success;
 *
 */
int 
rna_atom_write_edist_tieddisegment(ATOM *A, RULE *R, GRAMMAR *G, int verbose)
{
  EDIST edist;
  char  ename[MAXSTR];
  char  s[MAXSTR];
  int   edist_idx;  /* index for edists */
  int   idx, tidx;  /* index for edists */
  int   b;          /* index for basepairs */
  int   is_default;

  /* For a tied disegment, the are 2 edists */
  edist.n            = 2;
  edist.nbasepairs   = 1;
  edist.has_basepair = TRUE;  
  strcpy(ename, "");

  for (edist_idx = 0; edist_idx < A->nedists; edist_idx ++, tidx ++) 
    {
      strcpy(edist.ename, A->edist_name[edist_idx]);
      if (strcmp(ename, edist.ename)) tidx = 0; /* reset after moving from one to the other distribution */
      
      strcpy(ename, edist.ename);
      if      (strstr(edist.ename, "_2_0")) edist.c = 0;
      else if (strstr(edist.ename, "_2_1")) edist.c = 1;
      else if (strstr(edist.ename, "_2_2")) edist.c = 2;
      else return eslFAIL;
      
      for (b = 0; b < edist.nbasepairs; b ++) {
	edist.bp[b].basepairtype        = A->bp[b].basepairtype;   
	edist.bp[b].basepair_coordl_idx = A->bp[b].basepair_coordl_idx;
	edist.bp[b].basepair_coordr_idx = A->bp[b].basepair_coordr_idx;
	edist.bp[b].force_wccomp        = A->bp[b].force_wccomp;
      }
      
      idx = tidx % Integer_Power(4, edist.c);
      sprintf(s, "_%d", idx);
      strcat(edist.ename, s);
      if (rna_edist_check_name(&edist) != eslOK) return eslFAIL;
      
      /* the convention is that any default edist will start
       *  its name as e0_...
       */
      is_default = FALSE;
      if (strstr(edist.ename, "e0")) is_default = TRUE;
      if (is_default) rna_edist_write(&edist, G, idx, verbose);
      
      if (rna_edist_assign_tieddisegment(edist_idx, &edist, A, G) != eslOK) 
	grammar_fatal("could not find edist %s for this atom %s\n", 
		      edist.ename, A->atom_syntax); 
    }
  
  return eslOK;
}

/* Function: rna_atom_write_edist_emission()
 * Incept:    ER, Fri Nov 16 18:14:21 EST 2007 [janelia]
 *
 * Purpose: write the edist(s) for a rna grammar emission atom
 *
 * Returns: <eslOK> on success;
 *
 */
int 
rna_atom_write_edist_emission(ATOM *A, RULE *R, GRAMMAR *G, int verbose)
{
  EDIST edist;
  int   edist_idx;  /* index for edists */
  int   b;          /* index for basepairs */
  int   is_default;

  /* For an emission atom, the number of edist emissions 
     is the number of coords of the atom. */
  edist.n                   = A->ncoords;
  edist.c                   = A->ncontexts;
  edist.has_basepair        = A->has_basepair;
  edist.nbasepairs          = A->nbasepairs;
  edist.tiedtype            = TIED_OFF;
  edist.silent              = FALSE;
  edist.rc1                 = -1;
  edist.rc2                 = -1;
  edist.nted                = 0;
  edist.nued                = 0;
  for (b = 0; b < edist.nbasepairs; b ++) {
    edist.bp[b].basepairtype        = A->bp[b].basepairtype;   
    edist.bp[b].basepair_coordl_idx = A->bp[b].basepair_coordl_idx;
    edist.bp[b].basepair_coordr_idx = A->bp[b].basepair_coordr_idx;
    edist.bp[b].force_wccomp        = A->bp[b].force_wccomp;
  }
  
  for (edist_idx = 0; edist_idx < A->nedists; edist_idx ++) {
    
    strcpy(edist.ename, A->edist_name[edist_idx]);
    
    if (rna_edist_check_name(&edist) != eslOK) return eslFAIL;
    
    /* the convention is that any default edist will start
     *  its name as e0_...
     */
    is_default = FALSE;
    if (strstr(edist.ename, "e0")) is_default = TRUE;
    
    /* add default edist(s) if not there already */
    if (is_default) 
      rna_edist_write(&edist, G, edist_idx, verbose);
    
    /* find the edist(s) */
    if (rna_edist_assign(&edist, A, G) != eslOK) 
      grammar_fatal("could not find edist %s for this atom %s\n", 
	   edist.ename, A->atom_syntax);      
  }
  
  return eslOK;
}

/* Function: rna_atom_write_emission()
 * Incept:    ER, Thu Oct 25 13:55:25 EDT 2007 [janelia]
 *
 * Purpose: write an rna grammar emission atom
 *
 * Returns: <eslOK> on success;
 *
 */
int 
rna_atom_write_emission(ATOM *A, RULE *R, GRAMMAR *G, int add_ntcontext, int verbose)
{
  A->nldists = 0;
  A->nterm_idx = -1;

  if (A->has_basepair == FALSE) A->nbasepairs = 0;

  if (rna_atom_write_emission_context(A, G, add_ntcontext) != eslOK) 
    grammar_fatal("could not find context for atom %s\n", A->atom_syntax);
  
  if (rna_atom_write_edist_emission(A, R, G, verbose) != eslOK) 
    grammar_fatal("could not find edists for atom %s\n", A->atom_syntax);
  
  return eslOK;
}

/* Function: rna_atom_write_emission_context()
 * Incept:    ER, Thu Oct 25 13:27:25 EDT 2007 [janelia]
 *
 * Purpose: Assigns the context of atom as that of the NT that
 *          generated the rule.
 *
 * Returns: The context for the atom
 *
 */
int
rna_atom_write_emission_context(ATOM *A, GRAMMAR *G, int add_ntcontext)
{
  int  nt_idx;    /* nonterminal that generates this atoms */
  int  edist_idx; /* edists index */
  int  c;         /* context index */

  nt_idx = A->nt_idx;

  /* If we are using the compact notation, 
   * by default the context of an emission atom 
   * is that of the NT that produces it 
   * (add_ntcontext = TRUE).
   *
   * if we are given the atomlist, the context of an emission
   * is given directly by the emission atom 
   *(add_ntcontext = FALSE). 
   */
  if (add_ntcontext == TRUE) {
    A->ncontexts = G->nt[nt_idx].ncontexts;

    for (c = 0; c < A->ncontexts; c ++) {
      A->contextbase[c]   = G->nt[nt_idx].contextbase[c];
      A->contextoffset[c] = G->nt[nt_idx].contextoffset[c];
    }
  }

  /* now we should have the context of the atom 
   * completely determined. Add the number of edists accordingly.
   */
  A->nedists = Integer_Power(4, A->ncontexts);
  if (A->nedists > MAXEDISTS) grammar_fatal("Too many edists for atom %s\n", A->atom_syntax);

  for (edist_idx = 1; edist_idx < A->nedists; edist_idx ++)
    strcpy(A->edist_name[edist_idx], A->edist_name[0]);  
  
  return eslOK;
}

/* Function: rna_atom_write_epsilon()
 * Incept:    ER, Thu Oct 25 13:55:25 EDT 2007 [janelia]
 *
 * Purpose: write an rna grammar epsilon atom
 *
 * Returns: <eslOK> on success;
 *
 */
int 
rna_atom_write_epsilon(ATOM *A, GRAMMAR *G)
{
  A->edist_idx[0]   = 0;
  A->ncoords        = 0;
  A->ncontexts      = 0;
  A->nedists        = 0; 
  A->nldists        = 0;
  A->has_basepair   = FALSE;
  A->nbasepairs     = 0;
  A->ncbasepairs    = 0;
  A->nterm_idx      = -1;

  return eslOK;
}

/* Function: rna_atomwrite__monosegment()
 * Incept:    ER, Thu Oct 25 13:55:25 EDT 2007 [janelia]
 *
 * Purpose: write an rna grammar emission monosegment atom
 *
 * Returns: <eslOK> on success;
 *
 */
int 
rna_atom_write_monosegment(ATOM *A, GRAMMAR *G, int verbose)
{
  A->ncontexts      = 0;
  A->nedists        = 0; 
  A->nldists        = 1; 
  A->has_basepair   = FALSE;
  A->nbasepairs     = 0;
  A->ncbasepairs    = 0;
  A->nterm_idx      = -1;

  if (rna_atom_write_segment_ldist(A, G, verbose) != eslOK) 
    grammar_fatal("could not find ldist %s for atom %s\n",
		  A->ldist_name, A->atom_syntax);

  return eslOK;
}

/* Function: rna_atom_write_nonterminal()
 * Incept:    ER, Thu Oct 25 13:55:25 EDT 2007 [janelia]
 *
 * Purpose: write an rna grammar nonterminal atom
 *
 * Returns: <eslOK> on success;
 *
 */
int 
rna_atom_write_nonterminal(ATOM *A, GRAMMAR *G)
{
  int nt_ncontexts;
  int ct_tag[MAXCTXT];
  int ct;              /* context index */
  int c;               /* max context index */

  A->ncontexts      = 0;
  A->nedists        = 0; 
  A->nldists        = 0; 
  A->has_basepair   = FALSE;
  A->nbasepairs     = 0;
  A->ncbasepairs    = 0;
  A->nterm_idx      = -1;       /* will be determined at the end */

  /* check that the NT is compatible with the maximum contexts
   * allowed */
  if (rna_nonterminal_get_context(&nt_ncontexts, ct_tag, A->atom_syntax) != eslOK)
    return eslFAIL;

  if (A->max_nctxts >= 0 && nt_ncontexts > A->max_nctxts) return eslFAIL;

  for (ct = 0; ct < nt_ncontexts; ct ++) {
    for (c = 0; c < A->max_nctxts; c ++) {
      if (ct_tag[ct] == A->maxctxt_basetag[c]) break;
    }
    if (ct == nt_ncontexts) return eslFAIL;
  }
  
  return eslOK;
}

/* Function:  rna_atom_write_segment_ldist()
 * Incept:    ER, Thu Oct 25 13:55:25 EDT 2007 [janelia]
 *
 * Purpose:   write an ldist for a rna grammar emission segment atom
 *
 * Returns:   <eslOK> on success;
 *
 */
int 
rna_atom_write_segment_ldist(ATOM *A, GRAMMAR *G, int verbose)
{
  int is_default = FALSE;
  int l;
 
  for (l = 0; l < A->nldists; l ++) {
    /* the convention is that any default ldist will start
     *  its name as l0_...
     */
    if (!strcmp(A->ldist_name[l], "l"))  return eslFAIL;
    if (!strcmp(A->ldist_name[l], "l0")) is_default = TRUE;
    
    /* add default ldist if not there already */
    if (is_default) 
      if (rna_ldist_write(G, A->ldist_name[l], "ldist_mono", 0, 0, MAXSEGMENT-1, 0, 0, verbose) != eslOK) return eslFAIL;
  }
  
  /* find the ldist */
  if (rna_ldist_assign(A, G) != eslOK) return eslFAIL;
  
  
  return eslOK;
}

/* Function: rna_edist_add_edist()
 * Incept:   ER, May  6 17:07:51 EDT 2008 [janelia]
 *
 * Purpose:  Adds one specified score for an edist under construction
 *
 *
 * Returns:  <eslOK> on success;
 *
 */
int
rna_edist_add_edist(GRAMMAR *G, char *atom, char *edistname, int c1, int c2, int add)
{
  char         *msg = "rna_edist_add_edist(): alphabet failed";
  ESL_ALPHABET *a;           /* the RNA alphabet */
  ESL_DSQ      *dsq = NULL;  /* Digitize version of the atom */
  ESL_DSQ      *pdsq = NULL; /* Digitize version of the atom */
  EDIST         edist;       /* the edist at hand */
  EDIST         pedist;      /* a previously defined edist we are using here */
  int           edist_idx;   /* edist index */
  int           nemits;      /* total number of emissions (4^n) */
  int           nn;
  int           idx, pidx;   /* score index */
  int           i;           /* index for existing edists */
  int           found;

  /* adding scores to the last edist written */
  edist_idx = G->ned - 1;
  edist     = G->edist[edist_idx];
  nemits    = Integer_Power(4, edist.n);

  /* some restiction apply. Allowed options:
   * NN  = e1_2_c           # e(NN)  = e1_2_c(NN)
   * NN  = e1_1_c : 0       # e(aN)  = e1_1_c(a)
   * NNN = e1_2_c : 0 : 2   # e(aNb) = e1_2_c(ab)
   *
   */
  if      (c1 == -1 && c2 == -1) nn = edist.n;
  else if (c1 >=  0 && c2 == -1) nn = 1;
  else if (c1 >=  0 && c2 >=  0) nn = 2;
  else    grammar_fatal("rna_edist_add_edist(): bad definition for %s\n", edistname);

  /* Create an RNA alphabet.
   * Digitize the atom string.
   */
  if ((a = esl_alphabet_Create(eslRNA)) == NULL) grammar_fatal(msg);
  if ((dsq = malloc(sizeof(ESL_DSQ) * (edist.n+2))) == NULL) grammar_fatal(msg);
  if (esl_abc_Digitize(a, atom, dsq) != eslOK) grammar_fatal(msg);
  if (esl_abc_dsqlen(dsq) != edist.n) grammar_fatal(msg);

  /* Find the previously defined edist we are going to use */
  found = FALSE;
  for (i = 0; i < G->ned-1; i++) {
    if (strstr(G->edist[i].ename, edistname)       &&
	edist.nbasepairs == G->edist[i].nbasepairs   ) 
      { 
	pedist = G->edist[i];
	found = TRUE;

	if (pedist.n  !=  nn) 
	  grammar_fatal("rna_edist_add_edist(): cannot add a score to atom (%s) in distribution %s. Edist %s has the wrong number of emissions, should have %d\n", 
			atom, edist.ename, pedist.ename, nn);
	if (pedist.n  >  edist.n ) 
	  grammar_fatal("rna_edist_add_edist(): cannot add a score to atom (%s) in distribution %s\n", atom, edist.ename);
	
	break;
      }
  }
  if (found == FALSE) grammar_fatal("rna_edist_add_edist(): cannot find edist %s\n", edistname);
  if ((pdsq = malloc(sizeof(ESL_DSQ) * (pedist.n))) == NULL) grammar_fatal(msg);
 
  /* if the distribution is tied, you need to make it explicit now! */
  if (pedist.tiedtype != TIED_OFF) 
    if (Grammar_CalculateTiedEdist(&pedist, G, SCORE, NULL) != eslOK) grammar_fatal("rna_edist_add_edist(): couldn't tie edist %s\n", edistname);
  
  /* We are using a previously defined edist to fill the defaults
   */
  if (is_default_score(edist.n, dsq)) 
    {
      /* The default score always appears first,
       * so it is safe to set all edist scores by it
       */
      for (idx = 0; idx < nemits; idx ++) {

	if (edist.n == pedist.n) pidx = idx;
	else {
	  Index2Res(idx, dsq, edist.n, NULL);
	  if (pedist.n == 2) { pdsq[0] = dsq[c1]; pdsq[1] = dsq[c2]; }
	  if (pedist.n == 1) { pdsq[0] = dsq[c1]; }
	  pidx = Res2Index(pdsq, pedist.n);
#if 0
	  printf("%s[%d] [", edist.ename, idx);
	  for (i = 0; i < edist.n; i ++)
	    printf("%d ", dsq[i]);
	  printf("] ---> ");
	  printf("%s[%d] [", pedist.ename, pidx);
	  for (i = 0; i < pedist.n; i ++)
	    printf("%d ", pdsq[i]);
	  printf("] | %f %f\n", edist.esc[idx], pedist.esc[pidx]);
#endif
	}
	
 	if (add == TRUE) edist.esc[idx] += pedist.esc[pidx]; 
	else             edist.esc[idx]  = pedist.esc[pidx];
      }
    }
  else 
    return eslFAIL;
   
  /* clean up.
   */
  esl_alphabet_Destroy(a);
  if (dsq  != NULL) free(dsq);
  if (pdsq != NULL) free(pdsq);

  return eslOK;  
}

/* Function: rna_edist_add_score()
 * Incept:   ER, Thu Aug 30 09:40:34 EDT 2007 [janelia]
 *
 * Purpose:  Adds one specified score for an edist under construction
 *
 *
 * Returns:  <eslOK> on success;
 *
 */
int
rna_edist_add_score(GRAMMAR *G, char *atom, SCVAL sc, int add)
{
  char         *msg = "rna_edist_add_score(): alphabet failed";
  ESL_ALPHABET *a;         /* the RNA alphabet */
  ESL_DSQ      *dsq;       /* Digitize version of the atom */
  EDIST         edist;     /* the edist at hand */
  int           edist_idx; /* edist index */
  int           nemits;    /* total number of emissions (4^n) */
  int           idx;       /* score index */
  int           i;
  
  G->sctype = SCORE; /* set the type */

  /* adding scores to the last edist written */
  edist_idx = G->ned - 1;
  edist     = G->edist[edist_idx];

  if (edist.n != strlen(atom)) 
    grammar_fatal("cannot add a score to this atom (%s) in this distribution %s\n", atom, edist.ename);
  nemits = Integer_Power(4, edist.n);

  /* Create an RNA alphabet.
   * Digitize the atom string.
   */
  if ((a = esl_alphabet_Create(eslRNA)) == NULL) grammar_fatal(msg);
  if ((dsq = malloc(sizeof(ESL_DSQ) * (edist.n+2))) == NULL) grammar_fatal(msg);
  if (esl_abc_Digitize(a, atom, dsq) != eslOK) grammar_fatal(msg);
  if (esl_abc_dsqlen(dsq) != edist.n) grammar_fatal(msg);

  /* Add the score to the edist.
   */
  if (is_default_score(edist.n, dsq)) 
    {
      /* The default score always appears first,
       * so it is safe to set all edist scores by it
       */
      for (idx = 0; idx < nemits; idx ++) 
	if (add == TRUE) edist.esc[idx] += sc; else edist.esc[idx] = sc;
    }
  else 
    {
      /* add one specific score */
      idx = 0;
      for (i = 1; i <= edist.n; i ++) {
	if (dsq[i] < 4) idx = idx*4 + dsq[i]; 
	else grammar_fatal(msg);
      }
      if (add == TRUE) edist.esc[idx] += sc; else edist.esc[idx] = sc; 
#if 0
      printf("atom %s\n", atom);
      printf("\nadd %s[%d]=%f (%f)\n", edist.ename, idx, edist.esc[idx], sc);
#endif
    }
  
  /* clean up.
   */
  esl_alphabet_Destroy(a);
  free(dsq);

  return eslOK;  
} 

/* Function: rna_edist_assign()
 * Incept:   ER, Thu Aug 30 09:40:34 EDT 2007 [janelia]
 *
 * Purpose:  For an emission rule that uses a pre-specified edist,
 *           identifies the edist, and returns the edist index.
 *           If edist is not found dies.
 *
 * Returns:  <eslOK> on success;
 *
 */
int
rna_edist_assign(EDIST *edist, ATOM *A, GRAMMAR *G) 
{
  int edist_idx;
  int i, idx;       /* index for existing edists */
  int b;            /* index for nbasepairs */
  int is_same;

  if (!strstr(edist->ename, "e")) 
    grammar_fatal("rna_edist_assign(): edist_name has to start with e");
  
  /* Check if this edist exists */
  for (i = 0; i < G->ned; i++) {
    is_same = FALSE;

   if (G->edist[i].n == edist->n                    && 
	G->edist[i].nbasepairs == edist->nbasepairs && 
	strstr(G->edist[i].ename, edist->ename)       ) 
      { 
	is_same = TRUE;

	for (b = 0; b < G->edist[i].nbasepairs; b ++) {
	  if (edist->bp[b].basepairtype != BPTYPE_UNKNOWN && edist->bp[b].basepairtype != WW_C && G->edist[i].bp[b].basepairtype != edist->bp[b].basepairtype )
	    { 
	      is_same = FALSE; 
	      grammar_fatal("rna_edist_assign(): check bptypes %s  %s bptype %d %d", G->edist[i].ename, edist->ename, G->edist[i].bp[b].basepairtype,edist->bp[b].basepairtype);
	      break; 
	    }
	  if (G->edist[i].bp[b].basepair_coordl_idx != edist->bp[b].basepair_coordl_idx || 
	      G->edist[i].bp[b].basepair_coordr_idx != edist->bp[b].basepair_coordr_idx   )
	    { 
	      is_same = FALSE; 
	      grammar_fatal("rna_edist_assign(): check coords! %s  %s bptype %d %d", G->edist[i].ename, edist->ename);
	      break; 
	    
	    }
	      if (is_same && (edist->bp[b].basepairtype == BPTYPE_UNKNOWN || edist->bp[b].basepairtype == WW_C) ) { 
	    edist->bp[b].basepairtype = G->edist[i].bp[b].basepairtype;
	    A->bp[b].basepairtype     = G->edist[i].bp[b].basepairtype;
	  }
	}

	if (is_same) {
	  /* if the edist has the name completely specified 
	   * (e1_2_0_0 as suposed to just e1, for instance),
	   * and the atom has context but the edist has not,
	   * this is a "flag" for reducing the context of this atom
	   * to that specified by the given edist, as supposed to the one
	   * given by the nonterminal that originated the atom
	   */
	  if (!strcmp(G->edist[i].ename, edist->ename) &&
	      A->ncontexts >   0                       && 
	      G->edist[i].c == 0                         ) 
	    {
	      A->ncontexts = G->edist[i].c; /* change the atom context according to the edist */
	      A->nedists   = Integer_Power(4, A->ncontexts);
	    }
	  
	  if (G->edist[i].c == A->ncontexts) {
	    idx = i;
	    for (edist_idx = 0; edist_idx < A->nedists; edist_idx++) {
	      A->edist_idx[edist_idx] = idx; if (A->nedists > 0) idx++;
	    }
	    
	    break; 
	  } 
	} 

 	
      }
  }
  
  /* if edist not found die */
  if (i == G->ned) {
    grammar_fatal("rna_edist_assign(): edist %s n=%d c=%d nbasepairs=%d not found", 
	 edist->ename, edist->n, edist->c, edist->nbasepairs);
  }
  
  return eslOK;
}

/* Function: rna_edist_assign_tieddisegment()
 * Incept:   ER, Tue Dec  4 19:51:59 EST 2007 [janelia]
 *
 * Purpose:  For an disegment emission rule that uses pre-specified edists,
 *           identifies the edist, and returns the edist index.
 *           If edist is not found dies.
 *
 * Returns:  <eslOK> on success;
 *
 */
int
rna_edist_assign_tieddisegment(int idx, EDIST *edist, ATOM *A, GRAMMAR *G) 
{
  int i;       /* index for existing edists */
  int b;       /* index for nbasepairs */
  int is_same;
  
  if (!strstr(edist->ename, "e")) 
    grammar_fatal("rna_edist_assign_tieddisegment() edist_name has to start with e, instead of %s", edist->ename);
  
  /* Check if this edist exists */
  for (i = 0; i < G->ned; i++) {
    is_same = FALSE;

    if (G->edist[i].n == edist->n                   && 
	G->edist[i].c == edist->c                   && 
	G->edist[i].nbasepairs == edist->nbasepairs && 
	strstr(G->edist[i].ename, edist->ename)       ) 
      { 

	is_same = TRUE;

	for (b = 0; b < G->edist[i].nbasepairs; b ++) {
	  if (G->edist[i].bp[b].basepairtype != edist->bp[b].basepairtype               || 
	      G->edist[i].bp[b].basepair_coordl_idx != edist->bp[b].basepair_coordl_idx || 
	      G->edist[i].bp[b].basepair_coordr_idx != edist->bp[b].basepair_coordr_idx   )
	    { 
	      is_same = FALSE; 
	      break; 
	    }
	}

	if (is_same) { 
	  A->edist_idx[idx] = i;
	  strcpy(A->edist_name[idx], edist->ename);
	  if (0) printf("idx %d A_edist_idx %d ename %s\n", idx, A->edist_idx[idx], A->edist_name[idx]); 
	  break; 
	}
      }
  }

  /* if edist not found die */
  if (i == G->ned) {
    grammar_fatal("rna_edist_assign_tieddisegment(): edist %s n=%d c=%d nbasepairs=%d not found", 
	 edist->ename, edist->n, edist->c, edist->nbasepairs);
  }
  
  return eslOK;
}

/* Function: rna_edist_check_name()
 * Incept:   ER, Mon Nov 19 10:42:18 EST 2007 [janelia]
 *
 * Purpose:  Given an edist, check that the name matches
 *           the number of emissions and contexts of the edist.
 *
 *
 * Returns:  <eslOK> on success;
 *
 */
int 
rna_edist_check_name(EDIST *edist) 
{
  ESL_REGEXP *m; 
  ESL_REGEXP *ms; 
  char       *pattern;
  char       *num;
  char       *string;
  char       *s;
  int         status;
  int         nemits = -1;
  int         ncontexts = -1;
  int         n;

  m = esl_regexp_Create();

  /* if the edist name is of the form ex_n_c,
   * check that n = edist->n and c = edist->c
   */
  pattern = "^e[0-9]+_[0-9]+_[0-9]+$";
  if (esl_regexp_Match(m, pattern, edist->ename) == eslOK) {
    ms = esl_regexp_Create();
    num = "[0-9]+";
    esl_regexp_Compile(ms, num);
    
    string = edist->ename; 
    
    n = 0;
    while ((status = esl_regexp_MultipleMatches(ms, &string)) == eslOK)
      {
 	n ++;
	s = esl_regexp_SubmatchDup(ms, 0);
	if (n == 2) nemits    = atoi(s);
	if (n == 3) ncontexts = atoi(s);
	if (n < 1 || n > 3) return eslFAIL;
	free(s);
      }

    if (nemits != edist->n || ncontexts != edist->c) return eslFAIL;
    
    esl_regexp_Destroy(ms);
  }
  
  esl_regexp_Destroy(m);

  return eslOK;
}

/* Function: rna_edist_declare()
 * Incept:   ER, Mon Nov 19 10:42:18 EST 2007 [janelia]
 *
 * Purpose:  declares edist(s).
 *
 * Returns:  void.
 *
 */
void
rna_edist_declare(GRAMMAR *G, char *ename, 
		  int nemits, int ncontexts, 
		  int nbasepairs, 
		  char *basepairtype1, int basepair1_coordl_idx, int basepair1_coordr_idx, int force_wccomp1, 
		  char *basepairtype2, int basepair2_coordl_idx, int basepair2_coordr_idx, int force_wccomp2, 
		  int verbose)
{
  int nedist;       /* actual number of edists (4^c) */
  int edist_idx;    /* index for edists */

  if (!strstr(ename, "e")) grammar_fatal("rna_edist_declare() edist_name has to start with e");

  nedist = Integer_Power(4, ncontexts); /* total number of edists to be declared */

  for (edist_idx = 0; edist_idx < nedist; edist_idx++)
    rna_edist_declare_one(G, ename, nemits, ncontexts, nbasepairs, FALSE,
			  basepairtype1, basepair1_coordl_idx, basepair1_coordr_idx, force_wccomp1,
			  basepairtype2, basepair2_coordl_idx, basepair2_coordr_idx, force_wccomp2,
			  edist_idx, verbose);
}

/* Function: edist_declare_one()
 * Incept:   ER, Mon Nov 19 10:42:18 EST 2007 [janelia]
 *
 * Purpose:  Declares one edist.
 *
 *
 * Returns:  void;
 *
 */
void
rna_edist_declare_one(GRAMMAR *G, char *ename, int nemits, int ncontexts, int nbasepairs, int silent,
		      char *basepairtype1, int basepair1_coordl_idx, int basepair1_coordr_idx, int force_wccomp1, 
		      char *basepairtype2, int basepair2_coordl_idx, int basepair2_coordr_idx, int force_wccomp2, 
		      int edist_idx, int verbose)
{
  EDIST edist;
  int   nedists;

  if (!strstr(ename, "e")) grammar_fatal("rna_edist_declare_one() edist_name has to start with e");
  strcpy(edist.ename, ename);

  nedists            = Integer_Power(4, ncontexts);
  edist.n            = nemits;
  edist.c            = ncontexts;
  edist.has_basepair = (nbasepairs > 0)? TRUE : FALSE;
  edist.nbasepairs   = nbasepairs;
  edist.silent       = silent;
  edist.tiedtype     = TIED_OFF;
  edist.rc1          = -1;
  edist.rc2          = -1;
  edist.nted         = 0;
  edist.nued         = 0;

  if (edist.has_basepair == TRUE) {
    
    if ( nemits == 2 && 
	 (basepair1_coordl_idx != 0 || basepair1_coordr_idx != 1) ) 
      grammar_fatal("rna_edist_declare() edist_name has to start with e");
    
    if (nbasepairs > 2 ) 
      grammar_fatal("rna_edist_declare() more than two basepairs not implemented.");
    
    if (basepair1_coordl_idx < basepair1_coordr_idx &&
	basepair1_coordl_idx < nemits               && 
	basepair1_coordr_idx < nemits                 ) 
      {
	edist.bp[0].basepairtype        = get_basepairtype(basepairtype1+1);
	edist.bp[0].basepair_coordl_idx = basepair1_coordl_idx;
	edist.bp[0].basepair_coordr_idx = basepair1_coordr_idx;
 	edist.bp[0].force_wccomp        = force_wccomp1;
      }

    if (basepair2_coordl_idx < basepair2_coordr_idx &&
	basepair2_coordl_idx < nemits               && 
	basepair2_coordr_idx < nemits                 ) 
      {
	edist.bp[1].basepairtype        = get_basepairtype(basepairtype2+1);
	edist.bp[1].basepair_coordl_idx = basepair2_coordl_idx;
	edist.bp[1].basepair_coordr_idx = basepair2_coordr_idx;
 	edist.bp[1].force_wccomp        = force_wccomp2;
      }
  }

  if (rna_edist_write(&edist, G, edist_idx, verbose) != eslOK) 
    grammar_fatal("rna_edist_declare(): edist %s n=%d c=%d nbasepairs=%d edist_idx=%d, not found", 
	 ename, nemits, ncontexts, nbasepairs, edist_idx);
}

void
rna_edist_declare_tied_joint(GRAMMAR *G, char *tename1, int nbp1, char *tename2, int nbp2, char *tiedtype, int verbose)
{  
 
  EDIST        *edist;     /* the edist at hand */
  int           edist_idx; /* edist index */
  int           nedist;    /* actual number of edists (4^c) */
  int           i,n;       /* index for edists */
  int           idx;       /* index for edists */

  /* tying the last edist(s) written */
  edist_idx = G->ned-1;
  edist     = &(G->edist[edist_idx]);
  nedist    = Integer_Power(4, edist->c); /* total number of edists to be declared */

  /* limited span of this operation */
  if (edist->n != 2) grammar_fatal("rna_edist_declare_tied_joint(): edist need to have 2 coords");

  /* check for the right nomenclature  */
  if (!strstr(tename1, "e") || !strstr(tename2, "e")) 
    grammar_fatal("rna_edist_declare_tied_joint(): edit to tie don't have permitted names %s %s", tename1, tename2);

  /* find the edist(s) we are tying it to */
  for (n = 0, idx = edist_idx; n < nedist; n ++, idx--) {
    
    edist = &(G->edist[idx]);
    
    for (i = 0; i < G->ned-1; i++) {
      if (strstr(G->edist[i].ename, tename1) &&
	  G->edist[i].nbasepairs == nbp1     &&   
	  G->edist[i].n          == 1        && 
	  G->edist[i].c          == edist->c   ) { edist->tedist_idx[edist->nted++] = i; break; }
    }
    if (i == edist_idx) grammar_fatal("rna_edist_declare_tied_joint(): couldn't find edit %s to tie to", tename1);

    for (i = 0; i < G->ned-1; i++) {
      if (strstr(G->edist[i].ename, tename2) && 
	  G->edist[i].nbasepairs == nbp2     && 
	  G->edist[i].n          == 1        && 
	  G->edist[i].c          == edist->c    ) { edist->tedist_idx[edist->nted++] = i; break; }
    }
    if (i == edist_idx) grammar_fatal("rna_edist_declare_tied_joint(): couldn't find edit %s to tie to", tename2);
    
    edist->tiedtype = TIED_JOINT;
    edist->rc1      = -1;
    edist->rc2      = -1;

    if (Grammar_CalculateTiedEdist(edist, G, SCORE, NULL) != eslOK) 
      grammar_fatal("rna_edist_declare_tied_joint(): coudn't tie edist %s", edist->ename);

    if (verbose) {
      printf(" TYING-JOINT edist [#%d] %s to edist [#%d] %s and edist [#%d] %s\n", 
	     idx, edist->ename, 
	     edist->tedist_idx[0], G->edist[edist->tedist_idx[0]].ename, 
	     edist->tedist_idx[1], G->edist[edist->tedist_idx[1]].ename);
    }   
  } 
}

void
rna_edist_declare_tied_bayes(GRAMMAR *G, char *tename1, int nbp1, char *tename2, int nbp2, char *tiedtype, int verbose)
{  
 
  EDIST        *edist;     /* the edist at hand */
  int           edist_idx; /* edist index */
  int           nedist;    /* actual number of edists (4^c) */
  int           i,n;       /* index for edists */
  int           idx;       /* index for edists */
  int           n1, c1;
  int           n2, c2;

  /* tying the last edist(s) written */
  edist_idx = G->ned-1;
  edist     = &(G->edist[edist_idx]);
  nedist    = Integer_Power(4, edist->c); /* total number of edists to be declared */

  /* limited span of this operation */
  if (edist->nbasepairs > 1) grammar_fatal("rna_edist_declare_tied_bayes(): 1 basepair at most");

  /* check for the right nomenclature  */
  if (!strstr(tename1, "e") || !strstr(tename2, "e")) 
    grammar_fatal("rna_edist_declare_tied_bayes(): edit to tie don't have permitted names %s %s", tename1, tename2);

  /* find the edist(s) we are tying it to */
  EnameNemitNcontext(tename1, NULL, &n1, &c1, NULL);
  EnameNemitNcontext(tename2, NULL, &n2, &c2, NULL);

  /* apply restictions */
  if (n2 != 1)           grammar_fatal("rna_edist_declare_tied_bayes(): wrong number of coordinates for %s", tename2);
  if (n1+n2 != edist->n) grammar_fatal("rna_edist_declare_tied_bayes(): wrong number of coordinates for  %s %s", tename1, tename2);
  if (c1-n2 != edist->c) grammar_fatal("rna_edist_declare_tied_bayes(): wrong number of contexts for  %s %s", tename1, tename2);

  for (n = 0, idx = edist_idx; n < nedist; n ++, idx--) {
    
    edist = &(G->edist[idx]);
    
    for (i = 0; i < G->ned-1; i++) {
      if (strstr(G->edist[i].ename, tename1) &&
	  G->edist[i].nbasepairs == nbp1     &&   
	  G->edist[i].n          == n1       && 
	  G->edist[i].c          == c1          ) { edist->tedist_idx[edist->nted++] = i; break; }
    }
    if (i == edist_idx) grammar_fatal("rna_edist_declare_tied_bayes(): couldn't find edit %s to tie to", tename1);

    for (i = 0; i < G->ned-1; i++) {
      if (strstr(G->edist[i].ename, tename2) && 
	  G->edist[i].nbasepairs == nbp2     && 
	  G->edist[i].n          == n2       && 
	  G->edist[i].c          == c2         ) { edist->tedist_idx[edist->nted++] = i; break; }
    }
    if (i == edist_idx) grammar_fatal("rna_edist_declare_tied_bayes(): couldn't find edit %s to tie to", tename2);
    
    /* apply more restictions */
    if (edist->nbasepairs != G->edist[edist->tedist_idx[0]].nbasepairs)  
      grammar_fatal("rna_edist_declare_tied_bayes(): wrong number of basepairs for %s", tename1);

    edist->tiedtype = TIED_BAYES;
    edist->rc1      = -1;
    edist->rc2      = -1;

    if (Grammar_CalculateTiedEdist(edist, G, SCORE, NULL) != eslOK) 
      grammar_fatal("rna_edist_declare_tied_bayes(): coudn't tie edist %s", edist->ename);

    if (verbose) {
      printf(" TYING-BAYES edist [#%d] %s to edist [#%d] %s and edist [#%d] %s\n", 
	     idx, edist->ename, 
	     edist->tedist_idx[0], G->edist[edist->tedist_idx[0]].ename, 
	     edist->tedist_idx[1], G->edist[edist->tedist_idx[1]].ename);
    }   
  } 
}

void
rna_edist_declare_tied_marginal(GRAMMAR *G, char *tename, int nbp, int coord, char *tiedtype, int verbose)
{  
  EDIST        *edist;     /* the edist at hand */
  int           edist_idx; /* edist index */
  int           nedist;    /* actual number of edists (4^c) */
  int           i,n;       /* index for edists */
  int           idx;       /* index for edists */

  /* tying the last edist(s) written */
  edist_idx = G->ned-1;
  edist     = &(G->edist[edist_idx]);
  nedist    = Integer_Power(4, edist->c); /* total number of edists to be declared */

  /* limited span of this operation */
  if (edist->n != 2) grammar_fatal("rna_edist_declare_tied_marginal(): edist need to have 2 coords");

  /* check for the right nomenclature  */
  if (!strstr(tename, "e")) 
    grammar_fatal("rna_edist_declare_tied_marginal(): edit to tie don't have permitted name %s", tename);

  /* find the edist(s) we are tying it to */
  for (n = 0, idx = edist_idx; n < nedist; n ++, idx--) {
    
    edist = &(G->edist[idx]);
    
    for (i = 0; i < G->ned-1; i++) {
      if (strstr(G->edist[i].ename, tename) && 
	  G->edist[i].nbasepairs == nbp     && 
	  G->edist[i].n          == 2       && 
	  G->edist[i].c          == edist->c   ) { edist->tedist_idx[edist->nted++] = i; break; }
    }
    if (i == edist_idx) grammar_fatal("rna_edist_declare_tied_marginal(): couldn't find edit %s to tie to", tename);

    if      (coord == 0) edist->tiedtype = TIED_LMARGINAL;
    else if (coord == 1) edist->tiedtype = TIED_RMARGINAL;
    else grammar_fatal("rna_edist_declare_tied_marginal(): wrong coordinate\n");
    edist->rc1 = -1;
    edist->rc2 = -1;

    if (Grammar_CalculateTiedEdist(edist, G, SCORE, NULL) != eslOK) 
      grammar_fatal("rna_edist_declare_tied_marginal(): coudn't tie edist %s", edist->ename);

    if (verbose) {
      printf("TYING-MARGINAL edist [#%d] %s to edist [#%d] %s\n", 
	     idx, edist->ename, 
	     edist->tedist_idx[0], G->edist[edist->tedist_idx[0]].ename);
    }   
  }  
}

void
rna_edist_declare_tied_conditional(GRAMMAR *G, char *tename1, int nbp1, int coord, char *tename2, int nbp2, char *tiedtype, int verbose)
{  
  EDIST        *edist;     /* the edist at hand */
  int           edist_idx; /* edist index */
  int           nedist;    /* actual number of edists (4^c) */
  int           i,n;       /* index for edists */
  int           idx;       /* index for edists */

  /* tying the last edist(s) written */
  edist_idx = G->ned-1;
  edist     = &(G->edist[edist_idx]);
  nedist    = Integer_Power(4, edist->c); /* total number of edists to be declared */

  /* limited span of this operation */
  if (edist->n != 1) grammar_fatal("rna_edist_declare_tied_conditional(): edist need to have 1 coords");

  /* check for the right nomenclature  */
  if (!strstr(tename1, "e") || !strstr(tename2, "e")) 
    grammar_fatal("rna_edist_declare_tied_conditional(): edit to tie don't have permitted names %s %s %s", tename1, tename2);

  /* find the edist(s) we are tying it to */
  for (n = 0, idx = edist_idx; n < nedist; n ++, idx--) {
    
    edist = &(G->edist[idx]);
    
    for (i = 0; i < G->ned-1; i++) {
      if (strstr(G->edist[i].ename, tename1)   &&
	  G->edist[i].nbasepairs == nbp1       && 
	  G->edist[i].n          == edist->n+1 && 
	  G->edist[i].c          == edist->c-1    ) { edist->tedist_idx[edist->nted++] = i; break; }      
    }
    if (i == edist_idx) grammar_fatal("rna_edist_declare_tied_conditional(): couldn't find edit %s [nbp=%d] to tie to", tename1, nbp1);

    for (i = 0; i < G->ned-1; i++) {
      if (strstr(G->edist[i].ename, tename2)  &&
	  G->edist[i].nbasepairs == nbp2      && 
	  G->edist[i].n          == 1         && 
	  G->edist[i].c          == 0            ) { edist->uedist_idx[edist->nued++] = i; break; }
    }
    if (i == edist_idx) grammar_fatal("rna_edist_declare_tied_conditional(): couldn't find edit %s to untie to", tename2);
        
    if      (coord == 0) edist->tiedtype = TIED_LCONDITIONAL;
    else if (coord == 1) edist->tiedtype = TIED_RCONDITIONAL;
    else grammar_fatal("rna_edist_declare_tied_conditional(): wrong coordinate\n");
    edist->rc1  = -1;
    edist->rc2  = -1;

    if (Grammar_CalculateTiedEdist(edist, G, SCORE, NULL) != eslOK) 
      grammar_fatal("rna_edist_declare_tied_conditional(): coudn't tie edist %s", edist->ename);

    if (verbose) {
       printf("TYING-CONDITIONAL edist [#%d] %s to edist [#%d] %s and untied to edist [#%d] %s\n", 
	     idx, edist->ename, 
	     edist->tedist_idx[0], G->edist[edist->tedist_idx[0]].ename, 
	     edist->uedist_idx[0], G->edist[edist->uedist_idx[0]].ename);
    }   
  }   
}

void
rna_edist_declare_tied_condmarg(GRAMMAR *G, char *tename1, int nbp1, char *tename2, int nbp2, char *tiedtype, int verbose)
{  
  EDIST        *edist;     /* the edist at hand */
  int           edist_idx; /* edist index */
  int           nedist;    /* actual number of edists (4^c) */
  int           i,n;       /* index for edists */
  int           ctxt;
  int           idx;       /* index for edists */

  /* tying the last edist(s) written */
  edist_idx = G->ned-1;
  edist     = &(G->edist[edist_idx]);
  nedist    = Integer_Power(4, edist->c); /* total number of edists to be declared */

 /* limited span of this operation */
  if (edist->c != 0) grammar_fatal("rna_edist_declare_tied_condmarg(): edist need to have no context");

  /* check for the right nomenclature  */
  if (!strstr(tename1, "e") || !strstr(tename2, "e")) 
    grammar_fatal("rna_edist_declare_tied_condmarg(): edit to tie don't have permitted names %s %s %s", tename1, tename2);

  /* find the edist(s) we are tying it to */
  for (n = 0, idx = edist_idx; n < nedist; n ++, idx--) {
    
    edist = &(G->edist[idx]);
    
    for (i = 0; i < G->ned-1; i++) {
      if (strstr(G->edist[i].ename, tename1)   &&
	  G->edist[i].nbasepairs == nbp1       && 
	  G->edist[i].n          == edist->n      ) { ctxt = G->edist[i].c; edist->tedist_idx[edist->nted++] = i; break; }      
    }
    if (i == edist_idx) grammar_fatal("rna_edist_declare_tied_condmarg(): couldn't find edit %s [nbp=%d] to tie to", tename1, nbp1);

    for (i = 0; i < G->ned-1; i++) {
      if (strstr(G->edist[i].ename, tename2)  &&
	  G->edist[i].nbasepairs == nbp2      && 
	  G->edist[i].n          == ctxt      && 
	  G->edist[i].c          == edist->c     ) { edist->tedist_idx[edist->nted++] = i; break; }
    }
    if (i == edist_idx) grammar_fatal("rna_edist_declare_tied_condmarg(): couldn't find edit %s to tie to", tename2);
    
    edist->tiedtype = TIED_CONDMARG;
    edist->rc1      = -1;
    edist->rc2      = -1;
    
    if (Grammar_CalculateTiedEdist(edist, G, SCORE, NULL) != eslOK) 
      grammar_fatal("rna_edist_declare_tied_condmarg(): coudn't tie edist %s", edist->ename);
    
    if (verbose) {
       printf("TYING-CONDMARG edist [#%d] %s to edist [#%d] %s and to edist [#%d] %s\n", 
	      idx, edist->ename, 
	      edist->tedist_idx[0], G->edist[edist->tedist_idx[0]].ename, 
	      edist->tedist_idx[1], G->edist[edist->tedist_idx[1]].ename);
    }   
  }   
}

void
rna_edist_declare_tied_rotate_simple(GRAMMAR *G, char *tename, int nbp, char *tiedtype, int rc, int verbose)
{  
  EDIST        *edist;     /* the edist at hand */
  int           edist_idx; /* edist index */
  int           nedist;    /* actual number of edists (4^c) */
  int           i,n;       /* index for edists */
  int           tn, tc;
  int           idx;       /* index for edists */
 
  /* tying the last edist(s) written */
  edist_idx = G->ned-1;
  edist     = &(G->edist[edist_idx]);
  nedist    = Integer_Power(4, edist->c); /* total number of edists to be declared */

 /* limited span of this operation */
  if (edist->c != 0) grammar_fatal("rna_edist_declare_tied_rotate_simple(): edist cannot have context");

  if (rc < 0) grammar_fatal("rna_edist_declare_tied_rotate_simple(): negative number of extra coordinates");
  edist->rc1 = rc;
  
  /* check for the right nomenclature  */
  if (!strstr(tename, "e")) 
    grammar_fatal("rna_edist_declare_tied_rotate_simple(): edit to tie does have permitted names %s", tename);
  
  EnameNemitNcontext(tename, NULL, &tn, &tc, NULL);
  if (tn != edist->n) grammar_fatal("rna_edist_declare_tied_rotate_simple(): tedit %s wrong number of emits", tename);
  if (tc != edist->c) grammar_fatal("rna_edist_declare_tied_rotate_simple(): tedit %s wrong context", tename);
  
  /* find the edist(s) we are tying it to */
  for (n = 0, idx = edist_idx; n < nedist; n ++, idx--) {
    
    edist = &(G->edist[idx]);
    
    for (i = 0; i < G->ned-1; i++) { 
      if (strstr(G->edist[i].ename, tename)  && 
	  G->edist[i].nbasepairs == nbp      && 
	  G->edist[i].n          == edist->n && 
	  G->edist[i].c          == edist->c    ) { edist->tedist_idx[edist->nted++] = i; break; }
    }
    if (i == edist_idx) grammar_fatal("rna_edist_declare_tied_rotate_simple(): couldn't find edist %s [n=%d c=%d nbp=%d] to tie to", tename, edist->n, edist->c, nbp);
    
    edist->tiedtype = TIED_ROTATE_SIMPLE;
    
    if (Grammar_CalculateTiedEdist(edist, G, SCORE, NULL) != eslOK) 
      grammar_fatal("rna_edist_declare_tied_rotate(): coudn't tie edist %s", edist->ename);
    
    if (verbose) {
      printf("TYING-ROTATE_SIMPLE edist [#%d] %s to edist [#%d] %s\n", 
	     idx, edist->ename, 
	     edist->tedist_idx[0], G->edist[edist->tedist_idx[0]].ename);
    }   
  } 
}

void
rna_edist_declare_tied_rotate_context(GRAMMAR *G, char *tename1, int nbp1, char *tename2, int nbp2, char *tename3, int nbp3, char *tiedtype, int rc1, int rc2, int verbose)
{  
  EDIST        *edist;     /* the edist at hand */
  int           edist_idx; /* edist index */
  int           nedist;    /* actual number of edists (4^c) */
  int           i,n;       /* index for edists */
  int           newnctx;
  int           m;
  int           idx;       /* index for edists */
 
  /* tying the last edist(s) written */
  edist_idx = G->ned-1;
  edist     = &(G->edist[edist_idx]);
  nedist    = Integer_Power(4, edist->c); /* total number of edists to be declared */

 /* limited span of this operation */
  if (edist->c == 0) grammar_fatal("rna_edist_declare_tied_rotate(): edist need to have contexts");

  if      (rc1 == -1 && rc2 == -1) { newnctx = edist->n; }
  else if (rc1 == -1 || rc2 == -1) { newnctx = 1;        }
  else                             { newnctx = 2; 
    if (rc1+1 != rc2) grammar_fatal("rna_edist_declare_tied_rotate(): rotated coords have to be consecutive"); }  
  m = edist->n - newnctx; 
  if (m < 0) grammar_fatal("rna_edist_declare_tied_rotate(): negative number of extra coordinates");
  edist->rc1 = rc1;
  edist->rc2 = rc2;

  /* check for the right nomenclature  */
  if (!strstr(tename1, "e") || !strstr(tename2, "e") || !strstr(tename3, "e")) 
    grammar_fatal("rna_edist_declare_tied_joint(): edit to tie don't have permitted names %s %s", tename1, tename2);

  /* find the edist(s) we are tying it to */
  for (n = 0, idx = edist_idx; n < nedist; n ++, idx--) {
    
    edist = &(G->edist[idx]);
    
    for (i = 0; i < G->ned-1; i++) { 
      if (strstr(G->edist[i].ename, tename1)     && 
	  G->edist[i].nbasepairs == nbp1         && 
	  G->edist[i].n          == m + edist->c && 
	  G->edist[i].c          == newnctx         ) { edist->tedist_idx[edist->nted++] = i; break; }
    }
    if (i == edist_idx) grammar_fatal("rna_edist_declare_tied_rotate(): couldn't find edist1 %s [n=%d c=%d nbp=%d] to tie to", tename1, edist->n, edist->c, nbp1);

    for (i = 0; i < G->ned-1; i++) {
      if (strstr(G->edist[i].ename, tename2) && 
	  G->edist[i].nbasepairs == nbp2     && 
	  G->edist[i].n          == newnctx  && 
	  G->edist[i].c          == 0          ) { edist->tedist_idx[edist->nted++] = i; break; }
    }
     if (i == edist_idx) grammar_fatal("rna_edist_declare_tied_rotate(): couldn't find edist2 %s [n=%d c=%d nbp=%d] to tie to", tename2, edist->n, 0, nbp2);
    
     for (i = 0; i < G->ned-1; i++) {
      if (strstr(G->edist[i].ename, tename3) && 
	  G->edist[i].nbasepairs == nbp3     && 
	  G->edist[i].n          == edist->c && 
	  G->edist[i].c          == 0          ) { edist->uedist_idx[edist->nued++] = i; break; }
     }
    if (i == edist_idx) grammar_fatal("rna_edist_declare_tied_rotate(): couldn't find edist3 %s [n=%d c=%d nbp=%d] to untie to", tename3, edist->c, 0, nbp3);
    
    edist->tiedtype = TIED_ROTATE_CONTEXT;
    edist->rc1      = rc1;
    edist->rc2      = rc2;

    if (Grammar_CalculateTiedEdist(edist, G, SCORE, NULL) != eslOK) 
      grammar_fatal("rna_edist_declare_tied_rotate(): coudn't tie edist %s", edist->ename);

    if (verbose) {
      printf("TYING-ROTATE edist [#%d] %s to edist [#%d] %s and edist [#%d] %s and untied to edist [#%d] %s\n", 
	     idx, edist->ename, 
	     edist->tedist_idx[0], G->edist[edist->tedist_idx[0]].ename, 
	     edist->tedist_idx[1], G->edist[edist->tedist_idx[1]].ename, 
	     edist->uedist_idx[0], G->edist[edist->uedist_idx[0]].ename);
    }   
  } 
}

/* Function: rna_edist_write()
 * Incept:   ER, Mon Oct 29 17:03:56 EDT 2007 [janelia]
 *
 * Purpose: Writes a new edist in the grammar structure.
 *
 * Returns: <eslOK> on success;
 *
 */
int
rna_edist_write(EDIST *edist, GRAMMAR *G, int edist_idx, int verbose) 
{
  int i; /* index for existing edists */  
  int b; /* index for nbasepairs */ 
  int is_same;

  /* consistency check */
  if (!strstr(edist->ename, "e")) 
    grammar_fatal("rna_edist_write() edist_name has to start with e");
  if (edist->has_basepair && edist->n < 2) 
    grammar_fatal("rna_edist conflict: %s has_basepair but allows only %d emissions", 
		  edist->ename, edist->n);

  if (edist->has_basepair == FALSE) edist->nbasepairs = 0;

  /* Check if this is an existing edist */
  for (i = 0; i < G->ned; i++) {
    is_same = FALSE;

    if (G->edist[i].n == edist->n                   && 
	G->edist[i].c == edist->c                   && 
	G->edist[i].nbasepairs == edist->nbasepairs && 
	strstr(G->edist[i].ename, edist->ename)       ) 
      {
	is_same = TRUE;
	
	for (b = 0; b < edist->nbasepairs; b ++) 
	  if (G->edist[i].bp[b].basepairtype        != edist->bp[b].basepairtype        || 
	      G->edist[i].bp[b].basepair_coordl_idx != edist->bp[b].basepair_coordl_idx || 
	      G->edist[i].bp[b].basepair_coordr_idx != edist->bp[b].basepair_coordr_idx || 
	      G->edist[i].bp[b].force_wccomp        != edist->bp[b].force_wccomp          )
	    {
	      is_same = FALSE; break;
	    }
	
	if (is_same) break; 
      }
  }
  
  /* a trully new edist */
  if (i + edist_idx == G->ned) { 
    if (Grammar_Add_Edist(edist, G, edist_idx) != eslOK) return eslFAIL;
    if (verbose) {
      printf("EDIST #%d %s silent? %d tied? %d nbasepairs %d ", 
	     i+edist_idx, G->edist[i+edist_idx].ename, edist->silent, edist->tiedtype, edist->nbasepairs);
      if (edist->has_basepair) 
	for (b = 0; b < edist->nbasepairs; b ++) {
	  if (edist->bp[b].force_wccomp) 
	    printf("bp_wccomp(%d %d) ", edist->bp[b].basepair_coordl_idx, edist->bp[b].basepair_coordr_idx);
	  else 
	    printf("bp(%d %d) ", edist->bp[b].basepair_coordl_idx, edist->bp[b].basepair_coordr_idx);
	}
      printf("\n");
    }
  }

  return eslOK;
}

/* Function: rna_ldist_add_score_mono()
 * Incept:   ER, Mon Dec 10 17:16:43 EST 2007 [janelia]
 *
 * Purpose:  Adds one specified score for a ldist under construction
 *
 *
 * Returns:  <eslOK> on success;
 *
 */
int
rna_ldist_add_score_mono(GRAMMAR *G, char *l, SCVAL sc, int add, int verbose)
{
  LDIST  *ldist;     /* the ldist at hand */
  int     ldist_idx; /* ldist index */
  int     len;
  
  G->sctype = SCORE; /* set the type */

  /* adding scores to the last ldist written */
  ldist_idx = G->nld - 1;
  ldist     = &(G->ldist[ldist_idx]);

  if (!strcmp(l, "ld")) { /* default, set all values to sc */
    for (len = 0; len <= ldist->max-ldist->min; len++) 
      {  
	if (add) ldist->lsc[len] += sc;
	else     ldist->lsc[len]  = sc;
      }
    if (verbose) printf("ldist %s: default score %f\n", ldist->lname, ldist->lsc[0]);
  }
  else { 
    len = atoi(l)-ldist->min;
    if (len < 0 || len > ldist->max-ldist->min+1) return eslFAIL;
    if (add) ldist->lsc[len] += sc;
    else     ldist->lsc[len]  = sc;
    if (verbose) printf("ldist %s: adding score %d %f\n", ldist->lname, len+ldist->min, ldist->lsc[len]);
  }

  return eslOK;  
} 

/* Function: rna_ldist_add_score_di()
 * Incept:   ER, Tue Jun  1 14:27:09 EDT 2010 [janelia]
 *
 * Purpose:  Adds one specified score for a ldist under construction
 *           with two arguments (for free disegment atoms)
 *
 *
 * Returns:  <eslOK> on success;
 *
 */
int
rna_ldist_add_score_di(GRAMMAR *G, char *l, char *n, SCVAL sc, int add, int verbose)
{
  LDIST  *ldist;     /* the ldist at hand */
  int     ldist_idx; /* ldist index */
  int     l1, l2;
  int     dim, len;
  
  G->sctype = SCORE; /* set the type */

  /* adding scores to the last ldist written */
  ldist_idx = G->nld - 1;
  ldist     = &(G->ldist[ldist_idx]);

  dim = ldist->max + 1;

  if (!strcmp(l, "ld") && !strcmp(n, "ld")) { /* default, set all values to sc */
    for (len = 0; len < dim*dim; len++) 
      {  
	if (add) ldist->lsc[len] += sc;
	else     ldist->lsc[len]  = sc;
      }
    if (verbose) printf("ldist %s: default score %f\n", ldist->lname, ldist->lsc[0]);
  }
  else { 
    l1 = atoi(l);
    l2 = atoi(n);
    len = l2 * dim + l1;

    if (len < 0 || (l1+l2) > ldist->max) return eslFAIL;    
    if (add) ldist->lsc[len] += sc;
    else     ldist->lsc[len]  = sc;
    if (verbose) printf("ldist %s: adding score [%d,%d] add %f %f\n", ldist->lname, l1, l2, sc, ldist->lsc[len]);
  }

  return eslOK;  
} 

int
rna_ldist_add_score_di_sum(GRAMMAR *G, char *l, SCVAL sc, int add, int verbose)
{
  LDIST  *ldist;     /* the ldist at hand */
  int     ldist_idx; /* ldist index */
  int     l1, l2, lsum;
  int     dim, len;
  int     x;
  
  G->sctype = SCORE; /* set the type */

  /* adding scores to the last ldist written */
  ldist_idx = G->nld - 1;
  ldist     = &(G->ldist[ldist_idx]);

  dim = ldist->max + 1;

  lsum = atoi(l);
  for (x = 0; x <= lsum; x++) {
    l1 = x;
    l2 = lsum - l1;
    if ((l1+l2) <= ldist->max && (l1+l2) >= ldist->min) 
      { 
	len = l2 * dim + l1;
	if (add) ldist->lsc[len] += sc;
	else     ldist->lsc[len]  = sc;
	if (verbose) printf("ldist %s: adding sum_score [%d,%d] lsum=%d %f %f\n", ldist->lname, l1, l2, lsum, sc, ldist->lsc[len]);
      }
  }
  
  return eslOK;  
} 

int
rna_ldist_add_score_di_dif(GRAMMAR *G, char *l, SCVAL sc, int add, int verbose)
{
  LDIST  *ldist;     /* the ldist at hand */
  int     ldist_idx; /* ldist index */
  int     l1, l2, ldif;
  int     dim, len;
  int     x;
  
  G->sctype = SCORE; /* set the type */
   
  /* adding scores to the last ldist written */
  ldist_idx = G->nld - 1;
  ldist     = &(G->ldist[ldist_idx]);

 dim = ldist->max + 1;

  ldif = atoi(l);
  for (x = 0; x <= ldist->max; x++) {
    l1 = x;
    
    l2 = l1 - ldif;
    if (l2 >= 0) {
      if (l1+l2 <= ldist->max && l1+l2 >= ldist->min) {
	len = l2 * dim + l1; 
	if (add) ldist->lsc[len] += sc;
	else     ldist->lsc[len]  = sc;
	if (verbose) printf("ldist %s: adding diff_score [%d,%d] ldif=%d %f %f\n", ldist->lname, l1, l2, ldif, sc, ldist->lsc[len]);
      }  
    }
    
    l2 = l1 + ldif;
    if (l2 <= ldist->max) {
      if (l1+l2 <= ldist->max && l1+l2 >= ldist->min) {
	len = l2 * dim + l1; 
	if (add) ldist->lsc[len] += sc;
	else     ldist->lsc[len]  = sc;
	if (verbose) printf("ldist %s: adding diff_score [%d,%d] ldif=%d %f %f\n", ldist->lname, l1, l2, ldif, sc, ldist->lsc[len]);
      }
    }
  }
  
  return eslOK;  
} 

int
rna_ldist_add_score_di_sym(GRAMMAR *G, char *l, SCVAL sc, int add, int verbose)
{
  LDIST  *ldist;     /* the ldist at hand */
  int     ldist_idx; /* ldist index */
  int     l1, l2, lsym;
  int     dim, len;
  
  G->sctype = SCORE; /* set the type */

  /* adding scores to the last ldist written */
  ldist_idx = G->nld - 1;
  ldist     = &(G->ldist[ldist_idx]);

  dim = ldist->max + 1;

  lsym = atoi(l);
  l1 = l2 = lsym;
  len = l2 * dim + l1;
  if ((l1+l2) <= ldist->max && (l1+l2) >= ldist->min) 
    {    
      if (add) ldist->lsc[len] += sc;
      else     ldist->lsc[len]  = sc;
      if (verbose) printf("ldist %s: adding sym_score [%d,%d] %f %f\n", ldist->lname, l1, l2, sc, ldist->lsc[len]);
    }
  return eslOK;  
} 

int
rna_ldist_add_affine_score(GRAMMAR *G, double a, double b, double c, double d, int verbose)
{  
  int     ldist_idx; /* ldist index */
  LDIST  *ldist;     /* the ldist at hand */
  int     len;

  /* adding scores to the last ldist written */
  ldist_idx = G->nld - 1;
  ldist     = &(G->ldist[ldist_idx]);

  if (ldist->type != LDIST_MONO) grammar_fatal("affine scores only implemented for mono ldist\n");
  if (verbose) printf("affine function (l> %d): a=%f b=%f c=%f d=%f\n", ldist->fit, a, b, c, d);

  for (len = ldist->fit-ldist->min; len <= ldist->max-ldist->min; len++)  {
    ldist->lsc[len] = (SCVAL)(a + b*log((double)(len+ldist->min)*c+d));
    if (verbose) printf("ldist %s: adding affine score %d %f \n", ldist->lname, len+ldist->min, ldist->lsc[len]);
  }

  return eslOK;  
}

int
rna_ldist_add_linear_score(GRAMMAR *G, double a, double b, int verbose)
{  
  int     ldist_idx; /* ldist index */
  LDIST  *ldist;     /* the ldist at hand */
  int     len;

  /* adding scores to the last ldist written */
  ldist_idx = G->nld - 1;
  ldist     = &(G->ldist[ldist_idx]);

  if (ldist->type != LDIST_MONO) grammar_fatal("linear scores only implemented for mono ldist\n");
  if (verbose) printf("linear function (l> %d): a=%f b=%f\n", ldist->fit, a, b);

  for (len = ldist->fit-ldist->min; len <= ldist->max-ldist->min; len++)  {
    ldist->lsc[len] = (SCVAL)(a + b * (double)(len+ldist->min));
    if (verbose) printf("ldist %s: adding linear score %d %f \n", ldist->lname, len+ldist->min, ldist->lsc[len]);
  }

  return eslOK;  
}

/* Function:  rna_ldist_assign()
 * Incept:    ER, Wed Oct 31 09:45:34 EDT 2007 [janelia]
 *
 * Purpose: For an segment rule that uses a pre-specified ldist,
 *          identifies the ldist, and returns the ldist index.
 *          If ldist is not found dies.
 *
 * Returns: <eslOK> on success;
 *
 */
int
rna_ldist_assign(ATOM *A, GRAMMAR *G) 
{
  int   l;       /* index for atom ldists */
  int   i;       /* index for existing ldists */
  
  for (l = 0; l < A->nldists; l ++) {
    if (!strstr(A->ldist_name[l], "l")) 
      grammar_fatal("rna_ldist_assign() ldist_name has to start with l (ldist=%s atom=%s)", A->ldist_name[0], A->atom_syntax);
    
    /* Check if ldist already exists */
    for (i = 0; i < G->nld; i++) 
      if (strstr(G->ldist[i].lname, A->ldist_name[l])) 
	{ 
	  A->ldist_idx[l] = i; 
	  break; 
	}
    
    
    /* if ldist not found die */
    if (i == G->nld) 
      grammar_fatal("ldist %s  not found", A->ldist_name[l]);
  }
  
  return eslOK;
}

/* Function:  rna_ldist_declare()
 * Incept:    ER, Mon Oct 29 15:36:45 EDT 2007 [janelia]
 *
 * Purpose: Writes a new ldist in the grammar structure.
 *
 * Returns: void;
 *
 */
void
rna_ldist_declare(GRAMMAR *G, char *ldecl, char *lname, int min, int fit, int max, int minL, int minR, int verbose) 
{
  if (!strstr(lname, "l")) 
    grammar_fatal("rna_ldist_declare() ldist_name has to start with l %s", lname);

  if (rna_ldist_write(G, ldecl, lname, min, fit, max, minL, minR, verbose) != eslOK) 
    grammar_fatal("rna_ldist_declare(): something went wrong declaring ldist: %s min %d max %d", 
	 lname, min, max);
}

/* Function: rna_ldist_write()
 * Incept:   ER, Thu Aug 30 09:40:34 EDT 2007 [janelia]
 *
 * Purpose:  Writes a new ldist in the grammar structure.
 *
 * Returns: <eslOK> on success;
 *
 */
int
rna_ldist_write(GRAMMAR *G, char *ldecl, char *lname, int min, int fit, int max, int minL, int minR, int verbose) 
{
  enum ldist_e type;
  int           i;            /* index for existing ldists */

  if      (!strcmp(ldecl, "ldist-di"))   type = LDIST_DI;
  else if (!strcmp(ldecl, "ldist-semi")) type = LDIST_SEMI;
  else if (!strcmp(ldecl, "ldist"))      type = LDIST_MONO;
  else     grammar_fatal("rna_ldist_write() unknown type(%s) for ldist %s", type, lname);

  if (!strstr(lname, "l")) 
    grammar_fatal("rna_ldist_write() ldist_name has to start with l %s", lname);

  if (min > max) return eslFAIL;

  /* Check if this is an existing ldist */
  for (i = 0; i < G->nld; i++)
    if (G->ldist[i].min  == min         && 
	G->ldist[i].max  == max         && 
	G->ldist[i].fit  == fit         && 
	G->ldist[i].minL == minL        && 
	G->ldist[i].minR == minR        && 
	G->ldist[i].type == type        && 
	strstr(G->ldist[i].lname, lname)   ) 
      {
	break; 
      }
  
  /* a trully new ldist */
  if (i == G->nld) {
    if (Grammar_Add_Ldist(G, lname, type, min, fit, max, minL, minR) != eslOK) return eslFAIL;
    if (verbose) printf("LDIST #%d %s type %d\n", i, G->ldist[i].lname, G->ldist[i].type);
  }

  return eslOK;
}

/* Function: rna_lhs_write()
 * Incept:   ER, Tue Dec  4 15:22:11 EST 2007 [janelia]
 *
 * Purpose:  Adds a new nonterminal and transition distribution to the rna_grammar
 *
 * Returns:  <eslOK> on success;
 *
 */
int
rna_lhs_write(GRAMMAR *G, struct lexeme_s lexeme, char *errbuf, int *ret_nt_idx, int verbose) 
{
  NT    *nt;     /* pointer to nonterminal */
  int    w;      /* nonterminal added */
  int    tn_idx; /* index of tdist added */
  char   td_name[MAXDISSTR];
  int    status;
  
  /* Check if this is an existing NT.
   * (The rules of a given NT might come in more than one line.)
   */
  for (w = 0; w < G->M; w ++) 
    if (!strcmp(G->nt[w].ntname, lexeme.lex[0])) break; 

  /* A new nonterminal */
  if (w == G->M) {
    if (Grammar_Add_Nonterminal(G, lexeme.lex[0]) != eslOK)
      ESL_XFAIL(eslEINVAL, errbuf, "rna_lhs_write(): couldn't add nonterminal %s", 
		nt->ntname);

    nt = &(G->nt[w]);

    if (rna_nonterminal_context(nt) != eslOK) 
      ESL_XFAIL(eslEINVAL, errbuf, "rna_lhs_write(): couldn't add context to nonterminal %s", 
		nt->ntname);

    /* add a new transition distribution */
    if (lexeme.l == 1) { 
      tn_idx = G->ntd;
      sprintf(td_name, "t%d", tn_idx);
       if (Grammar_Add_Tdist(G, td_name, 0) != eslOK)
	ESL_XFAIL(eslEINVAL, errbuf, "rna_lhs_write(): nonterminal %s -- cannot add default tdist", 
		  nt->ntname);
      if (verbose) printf("TDIST #%d %s\n", tn_idx, G->tdist[tn_idx].tname);
      
      nt->td_predef   = FALSE;
      nt->tdist_idx = G->ntd-1; /* assign new tdist to the nt */
    }

    /* assign an already defined tdist to the nt */
    else if (lexeme.l == 2) {
 
      nt->td_predef = TRUE;
      if (rna_tdist_assign(nt, G, lexeme.lex[1]) != eslOK)
	ESL_XFAIL(eslEINVAL, errbuf, "rna_lhs_write(): couldn't assign tdist to nonterminal %s", 
		  nt->ntname);
    }
    else return eslFAIL;

    if (verbose) printf("NT #%d %s td_predef? %d\n", w, G->nt[w].ntname, G->nt[w].td_predef);
  }

  /* An existing nonterminal.
   * Check we are not trying to impossed a different tdist on it/ 
   */
  else {
    nt = &(G->nt[w]);

    if (lexeme.l == 1) { 
       if (nt->td_predef == TRUE) 
	ESL_XFAIL(eslEINVAL, errbuf, "rna_lhs_write(): nonterminal %s as already been defined as tdist-TIED.", 
		  nt->ntname);
    }
    else if (lexeme.l == 2) { 
      if (nt->td_predef == FALSE) 
	ESL_XFAIL(eslEINVAL, errbuf, "rna_lhs_write(): nonterminal %s as already been defined as tdist-UNTIED.", 
		  nt->ntname);
    }
    else return eslFAIL;
  }
  
  /* return idx for NT at work */
  *ret_nt_idx = w;                   
  
  return eslOK;
  
 ERROR:
  return status;
}

/* Function: rna_nonterminal_context()
 * Incept:    ER, Wed Aug 22 15:44:23 EDT 2007 [janelia]
 *
 * Purpose: Identifies the context of a nonterminal
 *
 * Returns: <eslOK> on success;
 *
 */
int
rna_nonterminal_context(NT *nt) 
{
  int  ct_idx;  /* index over contexts */

  /* undetermined */
  for (ct_idx = 0; ct_idx < nt->ncontexts; ct_idx ++) {
    nt->contextbase[ct_idx]   = -1;
    nt->contextoffset[ct_idx] = 0;
  }
  
  if (rna_nonterminal_get_context(&nt->ncontexts, nt->contextoffset, nt->ntname) != eslOK)
    return eslFAIL;

  for (ct_idx = 0; ct_idx < nt->ncontexts; ct_idx ++) {
    if      (nt->contextoffset[ct_idx] < 0) nt->contextbase[ct_idx] = COORD_I;
    else if (nt->contextoffset[ct_idx] > 0) nt->contextbase[ct_idx] = COORD_J;
  }

  if (0) {
    printf("\n NT %s ncontexts %d\n", nt->ntname, nt->ncontexts);
    for (ct_idx = 0; ct_idx < nt->ncontexts; ct_idx ++) 
      printf("coor %d off %d\n", nt->contextbase[ct_idx], nt->contextoffset[ct_idx]);
  }

  return eslOK;
}

/* Function:  rna_nonterminal_get_context()
 * Incept:    ER, Wed Nov 21 14:11:52 EST 2007 [janelia]
 *
 * Purpose: Identifies the context of a nonterminal from the name tags
 *
 * Returns: <eslOK> on success;
 *
 */
int
rna_nonterminal_get_context(int *ret_nct, int *ct_tag, char *ntname)
{
  char *name = NULL;
  char *pattern = NULL;
  int   nct = -1;
  int   c;             /* index over characters */
  int   ct_idx;        /* index over contexts */
  int   is_negative = FALSE;
  
  esl_strdup(ntname, -1, &name);
  esl_sprintf(&pattern, "^");

  if (name[0] == '{' ) 
    {
      if (isalpha(name[1])) 
	nct = 0; 
      else 
	{
	  c      = 1;
	  nct    = 0;
	  ct_idx = 0;
	  
	  while (name[c]) {
	    if      (name[c] == ',')   { c ++; }
	    else if (name[c] == '+')   { c ++; is_negative = FALSE; }
	    else if (name[c] == '-')   { c ++; is_negative = TRUE; }
	    else if (isdigit(name[c])) { ct_tag[ct_idx] = (is_negative)? -atoi(name+c):atoi(name+c); 
	      ct_idx ++; nct ++; c ++; is_negative = FALSE; }
	    else if (name[c] == '}' )  { c ++; }
	    else grammar_fatal("could not find context for this NT %s\n", ntname);
	  }
	}
    }
  else nct = 0;

  /* check context has been defined */
  if (nct < 0) return eslFAIL;

  /* check the context tags are in incremental order */
  for (ct_idx = 0; ct_idx < nct-1; ct_idx++) 
    if (ct_tag[ct_idx] > ct_tag[ct_idx+1]) 
      return eslFAIL;
    
  *ret_nct = nct;

  if (name    != NULL) free(name);
  if (pattern != NULL) free(pattern);
  return eslOK;
}

/* Function: rna_rule_atomlist_write()
 * Incept:    ER, Wed Apr 16 09:17:50 EDT 2008 [janelia]
 *
 * Purpose: Adds a new production rule
 *
 * Returns: <eslOK> on success; 
 */
int
rna_rule_atomlist_write(int rnr, int w, GRAMMAR *G)
{
  NT    *nt;       /* pointer to nonterminal */
  TDIST *tdist;    /* pointer to transition distribution */
  RULE  *R;        /* the rule at hand */
  int    tofw;     /* index for transition distribution (td) */
  int    r;        /* index for rules of a td */

  nt    = &(G->nt[w]);       /* nt pointer */
  r     = nt->nrules++;      /* rule index, add rule*/
  tofw  = nt->tdist_idx;     /* tdist index */
  tdist = &(G->tdist[tofw]); /* tdist pointer */

  /* if not a tied distribution add rule to tdist */
  if (!nt->td_predef) {
    tdist->tn ++;   
    /* probabilities and scores unused */
    tdist->tc[r]  = 0.0;
    tdist->tp[r]  = 0.0;
    tdist->tsc[r] = 0;
  }
  if (nt->nrules > MAXRULES) grammar_fatal("RULE #%d #tn = %d\n", rnr, nt->nrules);
  if (tdist->tn  > MAXRULES) grammar_fatal("RULE #%d #td = %d\n", rnr, tdist->tn);  

  R = &(nt->pr[r]);
  R->nt_idx    = w;
  R->tdist_idx = tofw;
  R->rule_idx  = r;
  R->natoms    = 0;

  /* defaults, no iterators */
  R->d1_iterator_state = ITERATOR_OFF;
  R->d2_iterator_state = ITERATOR_OFF;

  /* some more defaults */
  strcpy(R->rule_syntax, "");
  R->is_jdr   = FALSE;
  R->is_stemr = FALSE;

  return eslOK;
}


/* Function: rna_rule_enum_write()
 * Incept:    ER, Tue Aug 21 09:58:29 EDT 2007 [janelia]
 *
 * Purpose: Adds a new rule to the rna_grammar structure
 *
 * Returns: <eslOK> on success; 
 */
int
rna_rule_enum_write(int rnr, int ynr, int w, GRAMMAR *G, struct lexeme_s lexeme, int verbose) 
{
  NT    *nt;       /* pointer to nonterminal */
  TDIST *tdist;    /* pointer to transition distribution */
  RULE  *R;        /* the rule at hand */
  int    tofw;     /* index for transition distribution (td) */
  int    r;        /* index for rules of a td */
  int    natoms;

  nt    = &(G->nt[w]);       /* nt pointer */
  r     = nt->nrules++;      /* add rule */
  tofw  = nt->tdist_idx;     /* tdist index */
  tdist = &(G->tdist[tofw]); /* tdist pointer */

  /* if not a tied distribution add rule to tdist */
  if (!nt->td_predef) {
    tdist->tn ++;   
    /* probabilities and scores unused */
    tdist->tc[r]  = 0.0;
    tdist->tp[r]  = 0.0;
    tdist->tsc[r] = 0;
  }
  if (nt->nrules > MAXRULES) grammar_fatal("RULE #%d #tn = %d\n", rnr, nt->nrules);
  if (tdist->tn  > MAXRULES) grammar_fatal("RULE #%d #td = %d\n", rnr, tdist->tn);  

  R = &(nt->pr[r]);
  R->nt_idx    = w;
  R->tdist_idx = tofw;
  R->rule_idx  = r;
  R->natoms    = 0;
  R->is_jdr    = FALSE;
  R->is_stemr  = FALSE;
  rna_rule_syntax(R, lexeme);

  /* defaults, no iterators */
  R->d1_iterator_state = ITERATOR_OFF;
  R->d2_iterator_state = ITERATOR_OFF;

  if (verbose)  
    printf("RULE #%d [NT #%d] RULE_IDX %d TD_IDX %d TN_IDX %d: %s --> %s\n", 
	   rnr, R->nt_idx, r, tofw, tdist->tn-1, nt->ntname, R->rule_syntax);

  switch(ynr) {
  case 1:  natoms = yacc_rule1(R, lexeme, G, verbose);  break; /* EPSILON */

  case 2:  natoms = yacc_rule2(R, lexeme, G, verbose);  break; /* EMISSION or
								  EMISSION DIST_NAME */
    
  case 3:  natoms = yacc_rule3(R, lexeme, G, verbose);  break; /* NONTERM */
    
  case 4:  natoms = yacc_rule4(R, lexeme, G, verbose);  break; /* EMISSION EMISSION or
								  EMISSION EMISSION DIST_NAME */
    
  case 5:  natoms = yacc_rule5(R, lexeme, G, verbose);  break; /* EMISSION NONTERM or
								  EMISSION NONTERM DIST_NAME */
    
  case 6:  natoms = yacc_rule6(R, lexeme, G, verbose);  break; /* NONTERM EMISSION or 
								  NONTERM EMISSION DIST_NAME */
    
  case 7:  natoms = yacc_rule7(R, lexeme, G, verbose);  break; /* NONTERM NONTERM */

  case 8:  natoms = yacc_rule8(R, lexeme, G, verbose);  break; /* EMISSION EMISSION EMISSION */

  case 9:  natoms = yacc_rule9(R, lexeme, G, verbose);  break; /* NONTERM NONTERM EMISSION */
    
  case 10: natoms = yacc_rule10(R, lexeme, G, verbose); break; /* EMISSION NONTERM NONTERM */
    
  case 11: natoms = yacc_rule11(R, lexeme, G, verbose); break; /* NONTERM EMISSION NONTERM */
    
  case 12: natoms = yacc_rule12(R, lexeme, G, verbose); break; /* EMISSION NONTERM EMISSION or 
								  EMISSION NONTERM EMISSION DIST_NAME or
								  EMISSION NONTERM EMISSION DIST_NAME DIST_NAME */
    
  case 13: natoms = yacc_rule13(R, lexeme, G, verbose); break; /* NONTERM EMISSION EMISSION or 
								  NONTERM EMISSION EMISSION DIST_NAME or
								  NONTERM EMISSION EMISSION DIST_NAME DIST_NAME */
    
  case 14: natoms = yacc_rule14(R, lexeme, G, verbose); break; /* EMISSION EMISSION NONTERM or 
								  EMISSION EMISSION NONTERM DIST_NAME or 
								  EMISSION EMISSION NONTERM DIST_NAME DIST_NAME */
    
  case 15: natoms = yacc_rule15(R, lexeme, G, verbose); break; /* EMISSION EMISSION EMISSION EMISSION or 
								  EMISSION EMISSION  EMISSION EMISSION DIST_NAME */
    
  case 16: natoms = yacc_rule16(R, lexeme, G, verbose); break; /* EMISSION NONTERM NONTERM EMISSION or 
								  EMISSION NONTERM NONTERM EMISSION DIST_NAME or 
								  EMISSION NONTERM NONTERM EMISSION DIST_NAME DIST_NAME */
    
  case 17: natoms = yacc_rule17(R, lexeme, G, verbose); break; /* EMISSION NONTERM EMISSION NONTERM or 
								  EMISSION NONTERM EMISSION NONTERM DIST_NAME or 
								  EMISSION NONTERM EMISSION NONTERM DIST_NAME DIST_NAME */
    
  case 18: natoms = yacc_rule18(R, lexeme, G, verbose); break; /* NONTERM EMISSION NONTERM EMISSION or 
								  NONTERM EMISSION NONTERM EMISSION DIST_NAME or 
								  NONTERM EMISSION NONTERM EMISSION DIST_NAME DIST_NAME */
    
  case 19: natoms = yacc_rule19(R, lexeme, G, verbose); break; /* EMISSION NONTERM EMISSION NONTERM EMISSION or
								  EMISSION NONTERM EMISSION NONTERM EMISSION DIST_NAME */
    
  case 20: natoms = yacc_rule20(R, lexeme, G, verbose); break; /* EMISSION NONTERM EMISSION EMISSION NONTERM or
								  EMISSION NONTERM EMISSION EMISSION NONTERM DIST_NAME */
    
  case 21: natoms = yacc_rule21(R, lexeme, G, verbose); break; /* NONTERM EMISSION EMISSION NONTERM EMISSION or 
								  NONTERM EMISSION EMISSION NONTERM EMISSION DIST_NAME */
    
  case 22: natoms = yacc_rule22(R, lexeme, G, verbose); break; /* NONTERM EMISSION NONTERM EMISSION NONTERM or  
								  NONTERM EMISSION NONTERM EMISSION NONTERM DIST_NAME or 
								  NONTERM EMISSION NONTERM EMISSION NONTERM DIST_NAME DIST_NAME */
    
  case 23: natoms = yacc_rule23(R, lexeme, G, verbose); break; /* EMISSION NONTERM EMISSION EMISSION (bulges or dangles) or 
								  EMISSION NONTERM EMISSION EMISSION DIST_NAME */
    
  case 24: natoms = yacc_rule24(R, lexeme, G, verbose); break; /* EMISSION EMISSION NONTERM EMISSION (bulges or dangles) or 
								  EMISSION EMISSION NONTERM EMISSION DIST_NAME */
    
  case 25: natoms = yacc_rule25(R, lexeme, G, verbose); break; /* EMISSION EMISSION NONTERM EMISSION EMISSION (2x2 internal loops) or
								  EMISSION EMISSION NONTERM EMISSION EMISSION DIST_NAME */
    
  case 26: natoms = yacc_rule26(R, lexeme, G, verbose); break; /* EMISSION NONTERM EMISSION EMISSION NONTERM EMISSION (coaxials) or
								  EMISSION NONTERM EMISSION EMISSION NONTERM EMISSION  DIST_NAME */
    
  case 27: natoms = yacc_rule27(R, lexeme, G, verbose); break; /* EMISSION NONTERM EMISSION EMISSION EMISSION NONTERM EMISSION (coaxials with one residue in between) or 
								  EMISSION NONTERM EMISSION EMISSION EMISSION NONTERM EMISSION  DIST_NAME */
    
  case 28: natoms = yacc_rule28(R, lexeme, G, verbose); break; /* MONOSEGMENT or 
								  MONOSEGMENT DIST_NAME */
    
  case 29: natoms = yacc_rule29(R, lexeme, G, verbose); break; /* MONOSEGMENT NONTERM or 
								  MONOSEGMENT NONTERM DIST_NAME */
    
  case 30: natoms = yacc_rule30(R, lexeme, G, verbose); break; /* NONTERM MONOSEGMENT or 
								  NONTERM MONOSEGMENT DIST_NAME */
    
  case 31: natoms = yacc_rule31(R, lexeme, G, verbose); break; /* LDISEGMENT NONTERM RDISEGMENT or 
								  LDISEGMENT NONTERM RDISEGMENT DIST_NAME or
								  LDISEGMENT NONTERM RDISEGMENT DIST_NAME DIST_NAME or
								  LDISEGMENT NONTERM RDISEGMENT DIST_NAME DIST_NAME  DIST_NAME */
    
  case 32: natoms = yacc_rule32(R, lexeme, G, verbose); break; /* MONOSEGMENT EMISSION NONTERM EMISSION or 
								  MONOSEGMENT EMISSION NONTERM EMISSION DIST_NAME or 
								  MONOSEGMENT EMISSION NONTERM EMISSION DIST_NAME DIST_NAME */
    
  case 33: natoms = yacc_rule33(R, lexeme, G, verbose); break; /* EMISSION NONTERM EMISSION MONOSEGMENT or  
								  EMISSION NONTERM EMISSION MONOSEGMENT DIST_NAME or  
								  EMISSION NONTERM EMISSION MONOSEGMENT DIST_NAME DIST_NAME */
    
  case 34: natoms = yacc_rule34(R, lexeme, G, verbose); break; /* LDISEGMENT EMISSION NONTERM EMISSION RDISEGMENT or 
								  LDISEGMENT EMISSION NONTERM EMISSION RDISEGMENT DIST_NAME or 
								  LDISEGMENT EMISSION NONTERM EMISSION RDISEGMENT DIST_NAME DIST_NAME */
    
  case 35: natoms = yacc_rule35(R, lexeme, G, verbose); break; /* EMISSION MONOSEGMENT EMISSION or 
								  EMISSION MONOSEGMENT EMISSION DIST_NAME or
								  EMISSION MONOSEGMENT EMISSION DIST_NAME DIST_NAME */
    
  case 36: natoms = yacc_rule36(R, lexeme, G, verbose); break; /* EMISSION MONOSEGMENT NONTERM EMISSION or 
								  EMISSION MONOSEGMENT NONTERM EMISSION DIST_NAME or
								  EMISSION MONOSEGMENT NONTERM EMISSION DIST_NAME DIST_NAME or 
								  EMISSION MONOSEGMENT NONTERM EMISSION DIST_NAME DIST_NAME DIST_NAME */
    
  case 37: natoms = yacc_rule37(R, lexeme, G, verbose); break; /* EMISSION NONTERM MONOSEGMENT EMISSION or 
								  EMISSION NONTERM MONOSEGMENT EMISSION DIST_NAME or
								  EMISSION NONTERM MONOSEGMENT EMISSION DIST_NAME DIST_NAME or
								  EMISSION NONTERM MONOSEGMENT EMISSION DIST_NAME DIST_NAME DIST_NAME */
    
  case 38: natoms = yacc_rule38(R, lexeme, G, verbose); break; /* EMISSION MONOSEGMENT EMISSION NONTERM or 		
								  EMISSION MONOSEGMENT EMISSION NONTERM DIST_NAME or
								  EMISSION MONOSEGMENT EMISSION NONTERM DIST_NAME DIST_NAME or
								  EMISSION MONOSEGMENT EMISSION NONTERM DIST_NAME DIST_NAME DIST_NAME */
    
  case 39: natoms = yacc_rule39(R, lexeme, G, verbose); break; /* NONTERM EMISSION MONOSEGMENT EMISSION or 
								  NONTERM EMISSION MONOSEGMENT EMISSION DIST_NAME or
								  NONTERM EMISSION MONOSEGMENT EMISSION DIST_NAME DIST_NAME or
								  NONTERM EMISSION MONOSEGMENT EMISSION DIST_NAME DIST_NAME DIST_NAME */
    
  case 40: natoms = yacc_rule40(R, lexeme, G, verbose); break; /* EMISSION LDISEGMENT NONTERM RDISEGMENT EMISSION or 
								  EMISSION LDISEGMENT NONTERM RDISEGMENT EMISSION DIST_NAME or
								  EMISSION LDISEGMENT NONTERM RDISEGMENT EMISSION DIST_NAME DIST_NAME or
								  EMISSION LDISEGMENT NONTERM RDISEGMENT EMISSION DIST_NAME DIST_NAME DIST_NAME */
    
  case 41: natoms = yacc_rule41(R, lexeme, G, verbose); break; /* EMISSION EMISSION NONTERM EMISSION NONTERM or
								  EMISSION EMISSION NONTERM EMISSION NONTERM DIST_NAME */
    
  case 42: natoms = yacc_rule42(R, lexeme, G, verbose); break; /* NONTERM EMISSION NONTERM EMISSION EMISSION or
								  NONTERM EMISSION NONTERM EMISSION EMISSION DIST_NAME */
    
  case 43: natoms = yacc_rule43(R, lexeme, G, verbose); break; /* EMISSION EMISSION NONTERM EMISSION NONTERM EMISSION (coaxials) or
								  EMISSION EMISSION NONTERM EMISSION NONTERM EMISSION  DIST_NAME */
    
  case 44: natoms = yacc_rule44(R, lexeme, G, verbose); break; /* EMISSION NONTERM EMISSION NONTERM EMISSION EMISSION (coaxials) or
								  EMISSION NONTERM EMISSION NONTERM EMISSION EMISSION DIST_NAME */
    
  case 45: natoms = yacc_rule45(R, lexeme, G, verbose); break; /* EMISSION EMISSION NONTERM EMISSION EMISSION NONTERM (coaxials) or
								  EMISSION EMISSION NONTERM EMISSION EMISSION NONTERM DIST_NAME */
    
  case 46: natoms = yacc_rule46(R, lexeme, G, verbose); break; /* NONTERM EMISSION EMISSION NONTERM EMISSION EMISSION (coaxials) or
								  NONTERM EMISSION EMISSION NONTERM EMISSION EMISSION DIST_NAME */
    
  case 47: natoms = yacc_rule47(R, lexeme, G, verbose); break; /* EMISSION EMISSION NONTERM EMISSION EMISSION NONTERM EMISSION (coaxials with dangles) or 
								  EMISSION EMISSION NONTERM EMISSION EMISSION NONTERM EMISSION  DIST_NAME */
    
  case 48: natoms = yacc_rule48(R, lexeme, G, verbose); break; /* EMISSION NONTERM EMISSION EMISSION NONTERM EMISSION EMISSION (coaxials with dangles) or 
								  EMISSION NONTERM EMISSION EMISSION NONTERM EMISSION EMISSION  DIST_NAME */
    
  default: 
    grammar_fatal("no such yacc rule %d", ynr);
  }
  
  if (R->natoms != natoms) 
    grammar_fatal("died in yacc rule %d - rna rule %s. Rule has %d atoms, should have %d", 
	 ynr, R->rule_syntax, natoms, R->natoms);

  return eslOK;
}

/* Function:  rna_rule_print()
 * Incept:    ER,   Thu Apr 17 11:04:55 EDT 2008 [janelia]
 *
 * Purpose:   print a rule so far (for debugging purposes)
 *
 * Returns:   void; 
 */
void
rna_rule_print(int w, GRAMMAR *G)
{
  NT    *nt;         /* pointer to nonterminal */
  TDIST *tdist;      /* pointer to transition distribution */
  RULE  *R;          /* the rule at hand */
  int    tofw;       /* index for transition distribution (td) */
  int    r;          /* rule index */

  nt    = &(G->nt[w]);       /* nt pointer */
  tofw  = nt->tdist_idx;     /* tdist index */
  tdist = &(G->tdist[tofw]); /* tdist pointer */
  r     = nt->nrules-1;
  R     = &(nt->pr[r]);
  
  printf("RULE #%d [NT #%d] RULE_IDX %d TD_IDX %d TN_IDX %d: %s --> %s d1_min=%d d1_max=%d\n", 
	 rnr, R->nt_idx, r, tofw, tdist->tn-1, nt->ntname, R->rule_syntax, R->d1_iterator_min, R->d1_iterator_max);
}

/* Function: rna_rule_syntax()
 * Incept:    ER, Tue Aug 21 09:58:29 EDT 2007 [janelia]
 *
 * Purpose: Identifies the whole syntax of the rule.
 */
void
rna_rule_syntax(RULE *R, struct lexeme_s lexeme)
{
  char s[MAXSTR];
  int  l;

  if (lexeme.l == 0) strcpy(R->rule_syntax, "");

  for (l = 0; l < lexeme.l; l++) {
    (l == lexeme.l-1)? sprintf(s, "%s", lexeme.lex[l]) : sprintf(s, "%s ", lexeme.lex[l]);
    (l == 0)? strcpy(R->rule_syntax, s) : strcat(R->rule_syntax, s);
  }
}

void
rna_rule_syntax_add(RULE *R, char *atomsyntax)
{
  char s[MAXSTR];
  
  if (atomsyntax) {
    (!strcmp(R->rule_syntax, ""))? sprintf(s, "%s", atomsyntax) : sprintf(s, " %s", atomsyntax);
    if (R->rule_syntax[0] == '\0') strcat(R->rule_syntax, s);
    else                           strcpy(R->rule_syntax, s);
  }
}

/* Function: rna_tdist_add_score()
 * Incept:   ER, Mon Dec 10 17:17:36 EST 2007 [janelia]
 *
 * Purpose:  Adds one specified score for a tdist under construction
 *
 *
 * Returns:  <eslOK> on success;
 *
 */
int
rna_tdist_add_score(GRAMMAR *G, int t, SCVAL sc, int add)
{
  TDIST *tdist;     /* the tdist at hand */
  int    tdist_idx; /* tdist index */
 
  G->sctype = SCORE; /* set the type */

  /* adding scores to the last tdist written */
  tdist_idx = G->ntd - 1;
  tdist     = &(G->tdist[tdist_idx]);

  if (t < 0 || t >= tdist->tn) return eslFAIL;

  if (add) tdist->tsc[t] += sc; 
  else     tdist->tsc[t]  = sc;
 
  return eslOK;  
} 

/* Function: rna_tdist_add_score_default()
 * Incept:   ER, Sun Aug 15 21:32:05 EDT 2010 [janelia]
 *
 * Purpose:  Adds specified score to all transitons of  tdist under construction
 *           this has been a bug for 3 years. I was adding default score only to 
 *           the zero element.
 *
 * Returns:  <eslOK> on success;
 *
 */
int
rna_tdist_add_score_default(GRAMMAR *G, SCVAL sc)
{
  TDIST *tdist;     /* the tdist at hand */
  int    tdist_idx; /* tdist index */
  int    t;         /* index for transitions */
 
  G->sctype = SCORE; /* set the type */

  /* adding scores to the last tdist written */
  tdist_idx = G->ntd - 1;
  tdist     = &(G->tdist[tdist_idx]);

  for (t = 0; t < tdist->tn; t ++)
    tdist->tsc[t] = sc;

  return eslOK;  
} 

/* Function: rna_tdist_assign()
 * Incept:   ER, Tue Dec  4 15:34:03 EST 2007 [janelia]
 *
 * Purpose:  assign a predefined tdist to a NT
 *
 * Returns:  <eslOK> on success;
 *
 */
int
rna_tdist_assign(NT *nt, GRAMMAR *G, char *tdist_name)
{
  int t; /* index for existing tdists */

  if (!strstr(tdist_name, "t")) 
    grammar_fatal("rna_tdist_assign() tdist_name has to start with t");

  /* Check if this tdist exists */
  for (t = 0; t < G->ntd; t++) {
    if (!strcmp(G->tdist[t].tname, tdist_name)) 
      { 
	nt->tdist_idx = t; 
	break; 
      }
  }

  /* if tdist not found die */
  if (t == G->ntd) 
    grammar_fatal("tdist %s not found", tdist_name);

  return eslOK;
}

/* Function: rna_tdist_declare()
 * Incept:   ER, Wed Nov 21 15:47:45 EST 2007 [janelia]
 *
 * Purpose:  declares a transition distribution.
 *
 * Returns:  void.
 *
 */
void
rna_tdist_declare(GRAMMAR *G, char *tdname, int nrules, int verbose)
{
  if (!strstr(tdname, "t-")) 
    grammar_fatal("rna_tdist_declare() tdist_name has to start with 't-'");

  if (rna_tdist_write(G, tdname, nrules, verbose) != eslOK) 
    grammar_fatal("rna_tdist_declare(): tdist %s nrules %d", 
	 tdname, nrules);
}

/* Function: rna_tdist_tie()
 * Incept:   ER, Mon Jan 21 20:02:04 EST 2008 [janelia]
 *
 * Purpose;  To tie the transition parameter of a tdist
 *           under construction.
 *
 * Returns:  <eslOK> on success;
 *
 */
int
rna_tdist_tie(int ntied, int *tied, GRAMMAR *G, int verbose)
{
  TDIST *tdist; /* pointer to transition distribution */
  int    t,tt;  /* index for clustered transitions */
  int    t_idx; /* index for transitions */
  int    td;    /* index for transitions */

  /* tdist under construction */
  tdist = &(G->tdist[G->ntd-1]);

  /* make sure that none of the transitions is already tied */
  for (t = 0; t < ntied; t++) {
    t_idx = tied[t];

    for (td = 0; td < tdist->tn; td++) 
      if (td != t_idx &&
	  tdist->ttied[td] == tdist->ttied[t_idx]) return eslFAIL;
  }

  /* order the tied transitions */
  esl_vec_ISortIncreasing(tied, ntied);

  /* remove duplicates */
  for (t = 1; t < ntied; t++) {
    if (tied[t] == tied[t-1]) {
      for (tt = t; tt < ntied-1; tt++)
	tied[tt] = tied[tt+1];
      t--;
      ntied--;
    }
  }

  if (verbose) {
    printf("   TDIST %s tied:",  tdist->tname); 
    for (t = 0; t < ntied; t++) 
      printf(" %d ", tied[t]); 
    printf("\n"); 
  }
  
  /* assign to lower idx; 
   * adjust number of free transitions
   */
  for (t = 1; t < ntied; t++) {
    tdist->ttied[tied[t]] =  tdist->ttied[tied[0]];

    tdist->ttn --;
    for (td = tied[t]+1; td < tdist->tn; td++) 
      tdist->ttied[td] --;
  }
  
  /* paranoia */
  if (tdist->ttn < 1 || tdist->ttn > tdist->tn) return eslFAIL;

  return eslOK;
}

/* Function: rna_tdist_write()
 * Incept:    ER, Tue Dec  4 15:34:03 EST 2007 [janelia]
 *
 * Purpose: Adds a new tdist to the rna_grammar
 *
 * Returns: <eslOK> on success;
 *
 */
int
rna_tdist_write (GRAMMAR *G, char *tdist_name, int nrules, int verbose)
{
  char full_tdname[MAXDISSTR];
  int  t;            /* index for existing tdists */

  if (!strstr(tdist_name, "t")) grammar_fatal("rna_tdist_write() tdist_name has to start with t");

  /* Check if this is an existing ldist */
  for (t = 0; t < G->ntd; t++)
    if (G->tdist[t].tn == nrules             && 
	strcmp(G->tdist[t].tname, tdist_name) == 0) 
      {
	break; 
      }
  
  /* a trully new ldist */
  if (t == G->ntd) {
    /* name of tdist */
    sprintf(full_tdname, "%s", tdist_name);
    
    if (Grammar_Add_Tdist(G, full_tdname, nrules) != eslOK) return eslFAIL;
    if (verbose) printf("TDIST #%d %s nrules=%d\n", t, G->tdist[t].tname, nrules);
  }

  return eslOK;
}

/* YACC RULE #1 EPSILON
 * 1 atom: \epsilon */
int
yacc_rule1(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  
  strcpy(yr_name, "yacc_rule1");
  R->natoms = 1;

  /* atom 0: epsilon */
  A = &(R->atom[++a]);
  A->atomtype            = EPSILON_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 0;            
  A->max_nctxts          = 0;            /* context */
  strcpy(A->atom_syntax, lexeme.lex[0]); /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #2 EMITTER
 * 1 atom, a singlet emitter i.
 */
int
yacc_rule2(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule2");
  R->natoms = 1;

  /* atom 0: singlet emitter i */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->nbasepairs          = 0;
  A->ncbasepairs         = 0;
  A->ncoords             = 1;            /* singlet emitter */
  A->coordbase[0]        = COORD_I;      /* of residue i */
  A->offset[0]           = 0;            /* (i+0) */
  strcpy(A->atom_syntax, lexeme.lex[0]); /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 1)? lexeme.lex[1] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #3 NONTERM
 * 1 atom, a nonterminal (i,j)
 */
int
yacc_rule3(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule3");
  R->natoms = 1;

  /* atom 0: nonterminal (i,j) */
  A = &(R->atom[++a]);
  A->atomtype           = NONTERMINAL_ATOM;
  A->ncoords            = 2;               /* nonterminal */
  A->coordbase[0]       = COORD_I;         /* i     */
  A->offset[0]          = 0;               /* (i+0) */
  A->coordbase[1]       = COORD_J;         /* j     */
  A->offset[1]          = 0;               /* (j-0) */
  A->max_nctxts         = 0;               /* context */
  strcpy(A->atom_syntax, lexeme.lex[0]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return a+1;
}

/* YACC RULE #4 EMISSION EMISSION 
 * 1 atom, a double emitter i,i+1
 */
int
yacc_rule4(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   notallowed = FALSE;
  
  if (is_base_pair(lexeme.lex[0], lexeme.lex[1])) notallowed = TRUE;

  strcpy(yr_name, "yacc_rule4");
  R->natoms = 1;

  /* atom 0: double emitter i,i+1 */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 2;              /* doublet emitter */
  A->coordbase[0]        = COORD_I;        /* i */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_I;        /* i+1 */
  A->offset[1]           = +1;        
  strcpy(A->atom_syntax, lexeme.lex[0]);  /* atom name  */
  strcpy(A->atom_syntax, lexeme.lex[1]);  /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 2)? lexeme.lex[2] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #5 EMISSION NONTERM
 * 2 atoms, a singlet emitter i and nonterminal (i+1,j)
 */
int
yacc_rule5(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule5");
  R->natoms = 2;

  /* atom 0: sigle emitter i */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 1;              /* singlet emitter */
  A->coordbase[0]        = COORD_I;        /* i */
  A->offset[0]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[0]);   /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 2)? lexeme.lex[2] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+1,j) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_I;        /* i+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_J;        /* j   */
  A->offset[1]           = 0;        
  A->max_nctxts          = 1;              /* context */
  A->maxctxt_basetag[0]  = -1;             /* -1 tag */
  strcpy(A->atom_syntax, lexeme.lex[1]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return a+1;
}

/* YACC RULE #6 NONTERM EMISSION
 * 2 atoms, a singlet emitter i and nonterminal (i+1,j)
 */
int
yacc_rule6(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule6");
  R->natoms = 2;

  /* atom 0: nonterminal (i,j-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_I;        /* i */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_J;        /* j-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 1;              /* context */
  A->maxctxt_basetag[0]  = +1;             /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[0]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: siglet emitter j */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 1;              /* singlet emitter */
  A->coordbase[0]        = COORD_J;        /* j */
  A->offset[0]           = 0;  
  strcpy(A->atom_syntax, lexeme.lex[1]);   /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 2)? lexeme.lex[2] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return a+1;
}

/* YACC RULE #7 NONTERM NONTERM
 * 2 atoms, nonterminal (i,k) and nonterminal (k+1,j)
 */
int
yacc_rule7(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule7");
  R->natoms = 2;

  /* atom 0: nonterminal (i,k) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_I;        /* i */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_K;        /* k */
  A->offset[1]           = 0;        
  A->max_nctxts          = 0;              /* context */
  strcpy(A->atom_syntax, lexeme.lex[0]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (k+1,j) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_K;        /* k+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_J;        /* j */
  A->offset[1]           = 0;        
  A->max_nctxts          = 0;              /* context */
  strcpy(A->atom_syntax, lexeme.lex[1]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return a+1;
}

/* YACC RULE #8 EMISSION EMISSION EMISSION 
 * 1 atom, a triple emitter i,i+1,i+2
 */
int
yacc_rule8(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   notallowed = FALSE;
  
  if (is_base_pair(lexeme.lex[0], lexeme.lex[1])) notallowed = TRUE;
  if (is_base_pair(lexeme.lex[0], lexeme.lex[2])) notallowed = TRUE;
  if (is_base_pair(lexeme.lex[1], lexeme.lex[2])) notallowed = TRUE;

  strcpy(yr_name, "yacc_rule8");
  R->natoms = 1;

  /* atom 0: triple emitter i,i+1, i+2 */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 3;              /* triplet emitter */
  A->coordbase[0]        = COORD_I;        /* i */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_I;        /* i+1 */
  A->offset[1]           = +1;        
  A->coordbase[2]        = COORD_I;        /* i+2 */
  A->offset[2]           = +2;        
  strcpy(A->atom_syntax, lexeme.lex[0]); /* atom name  */
  strcpy(A->atom_syntax, lexeme.lex[1]); /* atom name  */
  strcpy(A->atom_syntax, lexeme.lex[2]); /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 3)? lexeme.lex[3] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #9 NONTERM NONTERM EMISSION 
 * 3 atoms, nonterminal (i,k), nonterminal (k+1,j-1) and singlet emitter j
 */
int
yacc_rule9(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  
  strcpy(yr_name, "yacc_rule9");
  R->natoms = 3;

  /* atom 0: nonterminal (i,k) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_I;        /* i */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_K;        /* k */
  A->offset[1]           = 0;        
  A->max_nctxts          = 0;              /* context */
  strcpy(A->atom_syntax, lexeme.lex[0]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
     grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (k+1,j) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_K;        /* k+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_J;        /* j-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 1;              /* context */
  A->maxctxt_basetag[0]  = +1;             /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[1]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: siglet emitter j */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 1;              /* singlet emitter */
  A->coordbase[0]        = COORD_J;        /* j */
  A->offset[0]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[2]); /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 3)? lexeme.lex[3] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #10 EMISSION NONTERM NONTERM 
 * 3 atoms, singlet emitter i, nonterminal (i+1,k), nonterminal (k+1,j) 
 */
int
yacc_rule10(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule10");
  R->natoms = 3;

  /* atom 0: siglet emitter i */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 1;              /* singlet emitter */
  A->coordbase[0]        = COORD_I;        /* i */
  A->offset[0]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[0]); /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 3)? lexeme.lex[3] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 1: nonterminal (i+1,k) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_I;        /* i+1 */
  A->offset[0]           = +1;        
  A->coordbase[1]        = COORD_K;        /* k */
  A->offset[1]           = 0;        
  A->max_nctxts          = 1;              /* context */
  A->maxctxt_basetag[0]  = -1;             /* -1 tag */
  strcpy(A->atom_syntax, lexeme.lex[1]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (k+1,j) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_K;        /* k+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_J;        /* j */
  A->offset[1]           = 0;        
  A->max_nctxts          = 0;              /* context */
  strcpy(A->atom_syntax, lexeme.lex[2]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname); 

  return a+1;
}

/* YACC RULE #11 NONTERM EMISSION NONTERM 
 * 3 atoms, nonterminal (i,k-1), single emitter k, nonterminal (k+1,j) 
 */
int
yacc_rule11(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule9");
  R->natoms = 3;

  /* atom 0: nonterminal (i,k-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->max_nctxts          = 1;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_I;        /* i */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_K;        /* k-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 1;              /* context */
  A->maxctxt_basetag[0]  = +1;             /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[0]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: sigle emitter k */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 1;              /* single emitter */
  A->coordbase[0]        = COORD_K;        /* k */
  A->offset[0]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[1]);   /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 3)? lexeme.lex[3] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 1: nonterminal (k+1,j) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_K;        /* k+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_J;        /* j */
  A->offset[1]           = 0;        
  A->max_nctxts          = 1;              /* context */
  A->maxctxt_basetag[0]  = -1;             /* -1 tag */
  strcpy(A->atom_syntax, lexeme.lex[2]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname); 

  return a+1;
}

/* YACC RULE #12 EMISSION NONTERM EMISSION 
 *
 * 2 atoms, double emission i,j and nonterminal (i+1,j-1)
 *
 * 3 atoms, a single emitter i, nonterminal (i+1,j-1), and a single emitter j
 */
int
yacc_rule12(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char  yr_name[MAXSTR];
  int   natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule12");
  
  if (lexeme.l < 5)       /* joint emission */
    natoms = yacc_rule12_2at(R, lexeme, G, verbose);
  else if (lexeme.l == 5) /* independent emissions */
    natoms = yacc_rule12_3at(R, lexeme, G, verbose);
  else 
    grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return natoms;
}
int
yacc_rule12_2at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  
  strcpy(yr_name, "yacc_rule12_2at");
  R->natoms = 2;
  
  /* atom 0: double emitter i,j */
  A = &(R->atom[++a]);
  A->atomtype                  = EMISSION_ATOM;
  A->nbasepairs                = (is_base_pair(lexeme.lex[0], lexeme.lex[2]))? 1 : 0;
  A->has_basepair              = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncbasepairs               = 0;
  A->ncoords                   = 2;              /* double emitter */
  A->coordbase[0]              = COORD_I;        /* i */
  A->offset[0]                 = 0;        
  A->coordbase[1]              = COORD_J;        /* j */
  A->offset[1]                 = 0;
  A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[1]);
  A->bp[0].basepair_coordl_idx = (A->has_basepair)? 0 : -1;
  A->bp[0].basepair_coordr_idx = (A->has_basepair)? 1 : -1;
  A->bp[0].force_wccomp        = FALSE;
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[2]);    /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 3)? lexeme.lex[3] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+1,j-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;              /* nonterminal */
  A->coordbase[0]           = COORD_I;        /* i+1 */
  A->offset[0]              = 1;        
  A->coordbase[1]           = COORD_J;        /* j-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 2;              /* context */
  A->maxctxt_basetag[0]     = -1;             /* -1 tag */
  A->maxctxt_basetag[1]     = +1;             /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[1]);      /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return a+1;
}
int
yacc_rule12_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule12_3at");
  R->natoms = 3;

  /* atom 0: siglet emitter i */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncbasepairs         = 0;
  A->ncoords             = 1;              /* singlet emitter */
  A->coordbase[0]        = COORD_I;        /* i */
  A->offset[0]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[0]); /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 3)? lexeme.lex[3] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+1,j-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_I;        /* i+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_J;        /* j-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 2;              /* context */
  A->maxctxt_basetag[0]  = -1;             /* -1 tag */
  A->maxctxt_basetag[1]  = +1;             /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[1]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: siglet emitter j */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncbasepairs         = 0;
  A->ncoords             = 1;              /* singlet emitter */
  A->coordbase[0]        = COORD_J;        /* j */
  A->offset[0]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[2]); /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 4)? lexeme.lex[4] : ((lexeme.l > 3)? lexeme.lex[3] : "e0")); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return a+1;
}

/* YACC RULE #13 NONTERM EMISSION EMISSION 
 *
 * 2 atoms, nonterminal (i,j-2), and  double emission j-1,j 
 *
 * 3 atoms, nonterminal (i,j-2), a single emitter j-1, and a single emitter j
 */
int
yacc_rule13(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char  yr_name[MAXSTR];
  int   natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule13");
  
  if (lexeme.l < 5)       /* joint emission */
    natoms = yacc_rule13_2at(R, lexeme, G, verbose);
  else if (lexeme.l == 5) /* independent emissions */
    natoms = yacc_rule13_3at(R, lexeme, G, verbose);
  else 
    grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return natoms;
}
int
yacc_rule13_2at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   notallowed = FALSE;
  
  if (is_base_pair(lexeme.lex[1], lexeme.lex[2])) notallowed = TRUE;

  strcpy(yr_name, "yacc_rule13_2at");
  R->natoms = 2;
  
  /* atom 0: nonterminal (i,j-2) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_I;        /* i */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_J;        /* j-2 */
  A->offset[1]           = -2;        
  A->max_nctxts          = 2;              /* context */
  A->maxctxt_basetag[0]  = +1;             /* +1 tag */
  A->maxctxt_basetag[1]  = +2;             /* +2 tag */
  strcpy(A->atom_syntax, lexeme.lex[0]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: double emitter j-1,j */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 2;              /* double emitter */
  A->coordbase[0]        = COORD_J;        /* j-1 */
  A->offset[0]           = -1;        
  A->coordbase[1]        = COORD_J;        /* j */
  A->offset[1]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[1]); /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[2]); /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 3)? lexeme.lex[3] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}
int
yacc_rule13_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule13_3at");
  R->natoms = 3;

  /* atom 0: nonterminal (i,j-2) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->max_nctxts          = 2;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_I;        /* i */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_J;        /* j-2 */
  A->offset[1]           = -2;        
  A->max_nctxts          = 2;              /* context */
  A->maxctxt_basetag[0]  = +1;             /* +1 tag */
  A->maxctxt_basetag[1]  = +2;             /* +2 tag */
  strcpy(A->atom_syntax, lexeme.lex[0]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: siglet emitter j-1 */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 1;              /* singlet emitter */
  A->coordbase[0]        = COORD_J;        /* j-1 */
  A->offset[0]           = -1;        
  strcpy(A->atom_syntax, lexeme.lex[1]);   /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 3)? lexeme.lex[3] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: siglet emitter j */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 1;              /* singlet emitter */
  A->coordbase[0]        = COORD_J;        /* j */
  A->offset[0]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[2]);   /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 4)? lexeme.lex[4] : ((lexeme.l > 3)? lexeme.lex[3] : "e0")); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return a+1;
}

/* YACC RULE #14 EMISSION EMISSION NONTERM 
 *
 * 2 atoms, double emission i,i+1, and nonterminal (i+2,j). 
 *
 * 3 atoms, a single emitter i, a single emitter i+1, and nonterminal (i+2,j).
 */
int
yacc_rule14(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char  yr_name[MAXSTR];
  int   natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule14");
  
  if (lexeme.l < 5)       /* joint emission */
    natoms = yacc_rule14_2at(R, lexeme, G, verbose);
  else if (lexeme.l == 5) /* independent emissions */
    natoms = yacc_rule14_3at(R, lexeme, G, verbose);
  else 
    grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return natoms;
}
int
yacc_rule14_2at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   notallowed = FALSE;
  
  if (is_base_pair(lexeme.lex[0], lexeme.lex[1])) notallowed = TRUE;

  strcpy(yr_name, "yacc_rule14_2at");
  R->natoms = 2;
  
  /* atom 0: double emitter i,i+1 */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 2;              /* double emitter */
  A->coordbase[0]        = COORD_I;        /* i */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_I;        /* i+1 */
  A->offset[1]           = +1;        
  strcpy(A->atom_syntax, lexeme.lex[0]); /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[1]); /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 3)? lexeme.lex[3] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+2,j) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->max_nctxts          = 2;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_I;        /* i+2 */
  A->offset[0]           = +2;        
  A->coordbase[1]        = COORD_J;        /* j */
  A->offset[1]           = 0;        
  A->max_nctxts          = 2;              /* context */
  A->maxctxt_basetag[0]  = -2;             /* -2 tag */
  A->maxctxt_basetag[1]  = -1;             /* -1 tag */
  strcpy(A->atom_syntax, lexeme.lex[2]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}
int
yacc_rule14_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule14_3at");
  R->natoms = 3;

  /* atom 1: siglet emitter i */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 1;              /* singlet emitter */
  A->coordbase[0]        = COORD_I;        /* i */
  A->offset[0]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[0]);   /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 3)? lexeme.lex[3] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: siglet emitter i+1 */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 1;              /* singlet emitter */
  A->coordbase[0]        = COORD_I;        /* i+1 */
  A->offset[0]           = +1;        
  strcpy(A->atom_syntax, lexeme.lex[1]);   /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 4)? lexeme.lex[4] : ((lexeme.l > 3)? lexeme.lex[3] : "e0")); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 1: nonterminal (i+2,j) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_I;        /* i+2 */
  A->offset[0]           = +2;        
  A->coordbase[1]        = COORD_J;        /* j */
  A->offset[1]           = 0;        
  A->max_nctxts          = 2;              /* context */
  A->maxctxt_basetag[0]  = -2;             /* -2 tag */
  A->maxctxt_basetag[1]  = -1;             /* -1 tag */
  strcpy(A->atom_syntax, lexeme.lex[2]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return a+1;
}

/* YACC RULE #15 EMISSION EMISSION EMISSION  EMISSION 
 * 1 atom, a quadruple emitter i,i+1,i+2,i+3
 */
int
yacc_rule15(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   notallowed = FALSE;
  
  if (is_base_pair(lexeme.lex[0], lexeme.lex[1])) notallowed = TRUE;
  if (is_base_pair(lexeme.lex[0], lexeme.lex[2])) notallowed = TRUE;
  if (is_base_pair(lexeme.lex[0], lexeme.lex[3])) notallowed = TRUE;
  if (is_base_pair(lexeme.lex[1], lexeme.lex[2])) notallowed = TRUE;
  if (is_base_pair(lexeme.lex[1], lexeme.lex[3])) notallowed = TRUE;
  if (is_base_pair(lexeme.lex[2], lexeme.lex[3])) notallowed = TRUE;

  strcpy(yr_name, "yacc_rule15");
  R->natoms = 1;

  /* atom 0: triple emitter i,i+1,i+2,i+3 */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 4;              /* triplet emitter */
  A->coordbase[0]        = COORD_I;        /* i */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_I;        /* i+1 */
  A->offset[1]           = +1;        
  A->coordbase[2]        = COORD_I;        /* i+2 */
  A->offset[2]           = +2;        
  A->coordbase[3]        = COORD_I;        /* i+3 */
  A->offset[3]           = +3;        
  strcpy(A->atom_syntax, lexeme.lex[0]); /* atom name  */
  strcpy(A->atom_syntax, lexeme.lex[1]); /* atom name  */
  strcpy(A->atom_syntax, lexeme.lex[2]); /* atom name  */
  strcpy(A->atom_syntax, lexeme.lex[3]); /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 4)? lexeme.lex[4] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #16 EMISSION NONTERM NONTERM EMISSION 
 *
 * 3 atoms, doublet emission i,j, nonterminal (i+1,k), and nonterminal (k,j-1)
 *
 * 4 atoms, a singlet emitter i, nonterminal (i+1,k), nonterminal (k+1,j-1), and a singlet emitter j
 */
int
yacc_rule16(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule16");
  
  if (lexeme.l < 6)       /* joint emission */
    natoms = yacc_rule16_3at(R, lexeme, G, verbose);
  else if (lexeme.l == 6) /* independent emissions */
    natoms = yacc_rule16_4at(R, lexeme, G, verbose);
  else 
    grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return natoms;
}
int
yacc_rule16_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule16_3at");
  R->natoms = 3;

  /* atom 0: pair emitter i,j */
  A = &(R->atom[++a]);
  A->atomtype                   = EMISSION_ATOM;
  A->nbasepairs                 = (is_base_pair(lexeme.lex[0], lexeme.lex[3]))? 1 : 0;
  A->has_basepair               = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                    = 2;              /* doublet emitter */
  A->coordbase[0]               = COORD_I;        /* i */
  A->offset[0]                  = 0;        
  A->coordbase[1]               = COORD_J;        /* j */
  A->offset[1]                  = 0;        
  A->bp[0].basepairtype        = rna_atom_basepairtype(A, G->nt[R->nt_idx].ntname);
  A->bp[0].basepair_coordl_idx = (A->has_basepair)? 0 : -1;
  A->bp[0].basepair_coordr_idx = (A->has_basepair)? 1 : -1;
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 4)? lexeme.lex[4] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+1,k) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;               /* nonterminal */
  A->coordbase[0]           = COORD_I;         /* i+1 */
  A->offset[0]              = 1;        
  A->coordbase[1]           = COORD_K;         /* k */
  A->offset[1]              = 0;        
  A->max_nctxts             = 1;              /* context */
  A->maxctxt_basetag[0]     = -1;             /* -1 tag */
  strcpy( A->atom_syntax, lexeme.lex[1]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+1,j-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_K;       /* k+1 */
  A->offset[0]              = 1;        
  A->coordbase[1]           = COORD_J;       /* j-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 1;             /* context */
  A->maxctxt_basetag[0]     = +1;            /* +1 tag */
  strcpy( A->atom_syntax, lexeme.lex[2]);    /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return a+1;
}
int
yacc_rule16_4at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule16_4at");
  R->natoms = 4;

  /* atom 0: singlet emitter i*/
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 1;             /* singlet emitter */
  A->coordbase[0]        = COORD_I;       /* i */
  A->offset[0]           = 0;        
  strcpy( A->atom_syntax, lexeme.lex[0]); /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 4)? lexeme.lex[4] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+1,k) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;             /* nonterminal */
  A->coordbase[0]        = COORD_I;       /* i+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_K;       /* k */
  A->offset[1]           = 0;        
  A->max_nctxts          = 1;             /* context */
  A->maxctxt_basetag[0]  = -1;            /* -1 tag */
  strcpy( A->atom_syntax, lexeme.lex[1]); /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+1,j-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;             /* nonterminal */
  A->coordbase[0]        = COORD_K;       /* k+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_J;       /* j-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 1;             /* context */
  A->maxctxt_basetag[0]  = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[2]);  /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("yacc_rule10_4at() failed at atom %s rule %s nt %s.", A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 3: singlet emitter j */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 1;               /* singlet emitter */
  A->coordbase[0]        = COORD_K;         /* k */
  A->offset[0]           = 0;        
  strcpy( A->atom_syntax, lexeme.lex[3]); /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 5)? lexeme.lex[5] : ((lexeme.l > 4)? lexeme.lex[4] : "e0")); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return a+1;
}

/* YACC RULE #17 EMISSION NONTERM EMISSION NONTERM 
 *
 * 3 atoms, doublet emission i,k, nonterminal (i+1,k-1), and nonterminal (k+1,j)
 *
 * 4 atoms, a singlet emitter i, nonterminal (i+1,k-1), a singlet emitter k, and nonterminal (k+1,j)
 */
int
yacc_rule17(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule17");
  
  if (lexeme.l < 6)       /* joint emission */
    natoms = yacc_rule17_3at(R, lexeme, G, verbose);
  else if (lexeme.l == 6) /* independent emissions */
    natoms = yacc_rule17_4at(R, lexeme, G, verbose);
  else 
    grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return natoms;
}
int
yacc_rule17_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule17_3at");
  R->natoms = 3;

  /* atom 0: doublet emitter i,k */
  A = &(R->atom[++a]);
  A->atomtype                  = EMISSION_ATOM;
  A->nbasepairs                = (is_base_pair(lexeme.lex[0], lexeme.lex[2]))? 1 : 0;
  A->has_basepair              = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                   = 2;              /* doublet emitter */
  A->coordbase[0]              = COORD_I;        /* i */
  A->offset[0]                 = 0;        
  A->coordbase[1]              = COORD_K;        /* k */
  A->offset[1]                 = 0;        
  A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[1]);
  A->bp[0].basepair_coordl_idx = (A->has_basepair)? 0 : -1;
  A->bp[0].basepair_coordr_idx = (A->has_basepair)? 1 : -1;
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[2]);    /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 4)? lexeme.lex[4] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+1,k-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_I;       /* i+1 */
  A->offset[0]              = 1;        
  A->coordbase[1]           = COORD_K;       /* k-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 2;             /* context */
  A->maxctxt_basetag[0]     = -1;            /* -1 tag */
  A->maxctxt_basetag[1]     = +1;            /* +1 tag */
  strcpy( A->atom_syntax, lexeme.lex[1]);    /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+1,j) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_K;       /* k+1 */
  A->offset[0]              = 1;        
  A->coordbase[1]           = COORD_J;       /* j */
  A->offset[1]              = 0;        
  A->max_nctxts             = 1;             /* context */
  A->maxctxt_basetag[0]     = -1;            /* -1 tag */
  strcpy( A->atom_syntax, lexeme.lex[3]);    /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return a+1;
}
int
yacc_rule17_4at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule17_4at");
  R->natoms = 4;

  /* atom 0: singlet emitter i*/
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 1;             /* singlet emitter */
  A->coordbase[0]        = COORD_I;       /* i */
  A->offset[0]           = 0;        
  strcpy( A->atom_syntax, lexeme.lex[0]); /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 4)? lexeme.lex[4] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+1,k-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;             /* nonterminal */
  A->coordbase[0]        = COORD_I;       /* i+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_K;       /* k-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 2;             /* context */
  A->maxctxt_basetag[0]  = -1;            /* -1 tag */
  A->maxctxt_basetag[1]  = +1;            /* +1 tag */
  strcpy( A->atom_syntax, lexeme.lex[1]); /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: singlet emitter k */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 1;               /* singlet emitter */
  A->coordbase[0]        = COORD_K;         /* k */
  A->offset[0]           = 0;        
  strcpy( A->atom_syntax, lexeme.lex[2]);   /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 5)? lexeme.lex[5] : ((lexeme.l > 4)? lexeme.lex[4] : "e0")); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 3: nonterminal (k+1,j) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_K;        /* k+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_J;        /* j */
  A->offset[1]           = 0;        
  A->max_nctxts          = 1;             /* context */
  A->maxctxt_basetag[0]  = -1;            /* -1 tag */
  strcpy(A->atom_syntax, lexeme.lex[3]);  /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return a+1;
}

/* YACC RULE #18 NONTERM EMISSION NONTERM EMISSION 
 *
 * 3 atoms, nonterminal (i,k-1), doublet emission k,j, and nonterminal (k+1,j-1)
 *
 * 4 atoms, nonterminal (i,k-1), a singlet emitter k, nonterminal (k+1,j-1), and a singlet emitter j 
 */
int
yacc_rule18(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule18");
  
  if (lexeme.l < 6)       /* joint emission */
    natoms = yacc_rule18_3at(R, lexeme, G, verbose);
  else if (lexeme.l == 6) /* independent emissions */
    natoms = yacc_rule18_4at(R, lexeme, G, verbose);
  else 
    grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return natoms;
}
int
yacc_rule18_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule18_3at");
  R->natoms = 3;

  /* atom 0: nonterminal (i,k-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;              /* nonterminal */
  A->coordbase[0]           = COORD_I;        /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_K;        /* k-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 1;             /* context */
  A->maxctxt_basetag[0]     = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[0]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: double emitter k,j */
  A = &(R->atom[++a]);
  A->atomtype                  = EMISSION_ATOM;
  A->nbasepairs                = (is_base_pair(lexeme.lex[1], lexeme.lex[3]))? 1 : 0;
  A->has_basepair              = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                   = 2;             /* double emitter */
  A->coordbase[0]              = COORD_K;       /* k */
  A->offset[0]                 = 0;        
  A->coordbase[1]              = COORD_J;       /* j */
  A->offset[1]                 = 0;        
  A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
  A->bp[0].basepair_coordl_idx = (A->has_basepair)? 0 : -1;
  A->bp[0].basepair_coordr_idx = (A->has_basepair)? 1 : -1;
  strcpy(A->atom_syntax, lexeme.lex[1]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 4)? lexeme.lex[4] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+1,j-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;              /* nonterminal */
  A->coordbase[0]           = COORD_K;        /* k+1 */
  A->offset[0]              = 1;        
  A->coordbase[1]           = COORD_J;        /* j-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 2;             /* context */
  A->maxctxt_basetag[0]     = -1;            /* -1 tag */
  A->maxctxt_basetag[1]     = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[2]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return a+1;
}
int
yacc_rule18_4at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  
  strcpy(yr_name, "yacc_rule18_4at");
  R->natoms = 4;

  /* atom 0: nonterminal (i,k-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_I;        /* i */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_K;        /* k-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 1;             /* context */
  A->maxctxt_basetag[0]  = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[0]);  /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: singlet emitter k */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 1;              /* singlet  emitter */
  A->coordbase[0]        = COORD_K;        /* k */
  A->offset[0]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[1]);   /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 4)? lexeme.lex[4] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+1,j-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;             /* nonterminal */
  A->coordbase[0]        = COORD_K;       /* k+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_J;       /* j-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 2;             /* context */
  A->maxctxt_basetag[0]  = -1;            /* -1 tag */
  A->maxctxt_basetag[1]  = +1;            /* +1 tag */
  strcpy( A->atom_syntax, lexeme.lex[2]); /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 3: singlet emitter j */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 1;              /* singlet  emitter */
  A->coordbase[0]        = COORD_J;        /* k */
  A->offset[0]           = 0;           
  strcpy(A->atom_syntax, lexeme.lex[3]);   /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 5)? lexeme.lex[5] : ((lexeme.l > 4)? lexeme.lex[4] : "e0")); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return a+1;
}

/* YACC RULE #19 EMISSION NONTERM EMISSION NONTERM EMISSION 
 *
 * 3 atoms, triplet emission i,k,j, nonterminal (i+1,k-1), nonterminal (k+1,j-1)
 *
 */
int
yacc_rule19(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule19");
  
  if (lexeme.l < 7)       /* joint emission */
    natoms = yacc_rule19_3at(R, lexeme, G, verbose);
  else 
    grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);
    
  return natoms;
}
int
yacc_rule19_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;

  if (is_base_pair(lexeme.lex[0], lexeme.lex[2]) ||
      is_base_pair(lexeme.lex[2], lexeme.lex[4]) || 
      is_base_pair(lexeme.lex[0], lexeme.lex[4])   ) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;

  strcpy(yr_name, "yacc_rule19_3at");
  R->natoms = 3;

  /* atom 0: three-way emitter i,k,j */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 3;             /* three-way emitter */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_K;       /* k */
  A->offset[1]              = 0;        
  A->coordbase[2]           = COORD_J;       /* j */
  A->offset[2]              = 0; 
  if      (is_base_pair(lexeme.lex[0], lexeme.lex[2])) {
    A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[1]);
    A->bp[0].basepair_coordl_idx = 0;
    A->bp[0].basepair_coordr_idx = 1;
  }
  else if (is_base_pair(lexeme.lex[2], lexeme.lex[4])) {
    A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[3]);
    A->bp[0].basepair_coordl_idx = 1;
    A->bp[0].basepair_coordr_idx = 2;
  }
  else if (is_base_pair(lexeme.lex[0], lexeme.lex[4])) {
    A->bp[0].basepairtype        = rna_atom_basepairtype(A, G->nt[R->nt_idx].ntname);
    A->bp[0].basepair_coordl_idx = 0;
    A->bp[0].basepair_coordr_idx = 2;
  }
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[2]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[4]);    /* atom name  */

 /* edist name */
  if      (lexeme.l == 5) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 6) { 
    if (strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]);
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+1,k-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;             /* nonterminal */
  A->coordbase[0]        = COORD_I;       /* i+1 */
  A->offset[0]           = +1;        
  A->coordbase[1]        = COORD_K;       /* k-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 2;             /* context */
  A->maxctxt_basetag[0]  = -1;            /* -1 tag */
  A->maxctxt_basetag[1]  = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[1]);  /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+1,j-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;             /* nonterminal */
  A->coordbase[0]        = COORD_K;       /* k+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_J;       /* j-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 2;             /* context */
  A->maxctxt_basetag[0]  = -1;            /* -1 tag */
  A->maxctxt_basetag[1]  = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[3]);  /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return a+1;
}

/* YACC RULE #20 EMISSION NONTERM EMISSION EMISSION NONTERM 
 *
 * 3 atoms, three-way emission i,k,K+1, nonterminal (i+1,k-1), nonterminal (k+2,j)
 *
 */
int
yacc_rule20(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule20");
  
  if (lexeme.l < 7)       /* joint emission */
     natoms = yacc_rule20_3at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return natoms;
}
int
yacc_rule20_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;
  int   notallowed = FALSE;

  if (is_base_pair(lexeme.lex[2], lexeme.lex[3])) notallowed = TRUE;

  if (is_base_pair(lexeme.lex[0], lexeme.lex[2]) ||
      is_base_pair(lexeme.lex[0], lexeme.lex[3]) ) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;

  strcpy(yr_name, "yacc_rule20_3at");
  R->natoms = 3;

  /* atom 0: three-way emitter i,k,k+1 */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 3;             /* three-way emitter */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_K;       /* k */
  A->offset[1]              = 0;        
  A->coordbase[2]           = COORD_K;       /* k+1 */
  A->offset[2]              = +1; 
  A->bp[0].basepairtype     = rna_atom_basepairtype(A, lexeme.lex[1]);
  if      (is_base_pair(lexeme.lex[0], lexeme.lex[2])) {
    A->bp[0].basepair_coordl_idx = 0;
    A->bp[0].basepair_coordr_idx = 1;
  }
  else if (is_base_pair(lexeme.lex[2], lexeme.lex[3])) {
    A->bp[0].basepair_coordl_idx = 0;
    A->bp[0].basepair_coordr_idx = 2;
  }
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[2]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */

 /* edist name */
  if      (lexeme.l == 5) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 6) { 
    if (strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]);
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+1,k-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_I;       /* i+1 */
  A->offset[0]              = +1;        
  A->coordbase[1]           = COORD_K;       /* k-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 3;             /* context */
  A->maxctxt_basetag[0]     = -1;            /* -1 tag */
  A->maxctxt_basetag[1]     = +1;            /* +1 tag */
  A->maxctxt_basetag[2]     = +2;            /* +2 tag */
  strcpy(A->atom_syntax, lexeme.lex[1]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+2,j) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_K;       /* k+2 */
  A->offset[0]              = 2;        
  A->coordbase[1]           = COORD_J;       /* j */
  A->offset[1]              = 0;        
  A->max_nctxts             = 2;             /* context */
  A->maxctxt_basetag[0]     = -2;            /* -2 tag */
  A->maxctxt_basetag[1]     = -1;            /* -1 tag */
  strcpy(A->atom_syntax, lexeme.lex[4]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #21 NONTERM EMISSION EMISSION NONTERM EMISSION 
 *
 * 3 atoms, nonterminal (i,k-1), three-way emission k,k+1,j, nonterminal (k+2,j-1)
 *
 */
int
yacc_rule21(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule21");
  
  if (lexeme.l < 7)       /* joint emission */
    natoms = yacc_rule21_3at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return natoms;
}
int
yacc_rule21_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;
  int   notallowed = FALSE;

  if (is_base_pair(lexeme.lex[1], lexeme.lex[2])) notallowed = TRUE;

  if (is_base_pair(lexeme.lex[1], lexeme.lex[4]) ||
      is_base_pair(lexeme.lex[2], lexeme.lex[4]) ) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;

  strcpy(yr_name, "yacc_rule21_3at");
  R->natoms = 3;

  /* atom 0: nonterminal (i,k-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_K;       /* k-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 2;             /* context */
  A->maxctxt_basetag[0]     = +1;            /* +1 tag */
  A->maxctxt_basetag[1]     = +2;            /* +2 tag */
  strcpy(A->atom_syntax, lexeme.lex[0]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: three-way emitter k,k+1,j */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 3;             /* three-way emitter */
  A->coordbase[0]           = COORD_K;       /* k */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_K;       /* k+1 */
  A->offset[1]              = 1;        
  A->coordbase[2]           = COORD_J;       /* j */
  A->offset[2]              = 0; 
  A->bp[0].basepairtype     = rna_atom_basepairtype(A, lexeme.lex[3]);
  if      (is_base_pair(lexeme.lex[1], lexeme.lex[4])) {
    A->bp[0].basepair_coordl_idx = 0;
    A->bp[0].basepair_coordr_idx = 2;
  }
  else if (is_base_pair(lexeme.lex[2], lexeme.lex[4])) {
    A->bp[0].basepair_coordl_idx = 1;
    A->bp[0].basepair_coordr_idx = 2;
  }
  strcpy(A->atom_syntax, lexeme.lex[1]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[2]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[4]);    /* atom name  */

 /* edist name */
  if      (lexeme.l == 5) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 6) { 
    if (strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]);
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+2,j-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_K;       /* k+2 */
  A->offset[0]              = 2;        
  A->coordbase[1]           = COORD_J;       /* j-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 3;             /* context */
  A->maxctxt_basetag[0]     = -2;            /* -2 tag */
  A->maxctxt_basetag[1]     = -1;            /* -1 tag */
  A->maxctxt_basetag[2]     = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[3]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #22 NONTERM EMISSION NONTERM EMISSION NONTERM 
 *
 * 4 atoms, nonterminal (i,k-1), doublet emission k,l, nonterminal (k+1,l-1), and nonterminal (l+1,j)
 *
 * 5 atoms, nonterminal (i,k-1), a singlet emitter k, nonterminal (k+1,l-1), a singlet emitter l, and nonterminal (l+1,j)
 */
int
yacc_rule22(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule22");
  
  if (lexeme.l < 7)       /* joint emission */
    natoms = yacc_rule22_4at(R, lexeme, G, verbose);
  else if (lexeme.l == 7) /* independent emissions */
    natoms = yacc_rule22_5at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return natoms;
}
int
yacc_rule22_4at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule22_4at");
  R->natoms = 4;

  /* atom 0: nonterminal (i,k-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_K;       /* k-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 1;             /* context */
  A->maxctxt_basetag[0]     = +1;            /* +1 tag */
  strcpy( A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: doublet  emitter k,l */
  A = &(R->atom[++a]);
  A->atomtype                  = EMISSION_ATOM;
  A->nbasepairs                = (is_base_pair(lexeme.lex[1], lexeme.lex[3]))? 1 : 0;
  A->has_basepair              = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                   = 2;             /* doublet  emitter */
  A->coordbase[0]              = COORD_K;       /* k */
  A->offset[0]                 = 0;        
  A->coordbase[1]              = COORD_L;       /* l */
  A->offset[1]                 = 0;        
  A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
  A->bp[0].basepair_coordl_idx = (A->has_basepair)? 0 : -1;
  A->bp[0].basepair_coordr_idx = (A->has_basepair)? 1 : -1;
  strcpy(A->atom_syntax, lexeme.lex[1]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 5)? lexeme.lex[5] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+1,l-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;              /* nonterminal */
  A->coordbase[0]           = COORD_K;        /* k+1 */
  A->offset[0]              = 1;        
  A->coordbase[1]           = COORD_L;        /* l-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 2;             /* context */
  A->maxctxt_basetag[0]     = -1;            /* -1 tag */
  A->maxctxt_basetag[1]     = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[2]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 3: nonterminal (l+1,j) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;              /* nonterminal */
  A->coordbase[0]           = COORD_L;        /* l+1 */
  A->offset[0]              = 1;        
  A->coordbase[1]           = COORD_J;        /* j */
  A->offset[1]              = 0;        
  A->max_nctxts             = 1;             /* context */
  A->maxctxt_basetag[0]     = -1;            /* -1 tag */
  strcpy(A->atom_syntax, lexeme.lex[4]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}
int
yacc_rule22_5at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule22_5at");
  R->natoms = 5;

  /* atom 0: nonterminal (i,k-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;             /* nonterminal */
  A->coordbase[0]        = COORD_I;       /* i */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_K;       /* k-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 1;             /* context */
  A->maxctxt_basetag[0]  = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[0]);  /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: singlet emitter k */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 2;               /* singlet  emitter */
  A->coordbase[0]        = COORD_K;         /* k */
  A->offset[0]           = 0;        
  strcpy( A->atom_syntax, lexeme.lex[1]);   /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 5)? lexeme.lex[5] : "e0"); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+1,l-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;             /* nonterminal */
  A->coordbase[0]        = COORD_K;       /* k+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_L;       /* l-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 2;             /* context */
  A->maxctxt_basetag[0]  = -1;            /* -1 tag */
  A->maxctxt_basetag[1]  = +1;            /* +1 tag */
  strcpy( A->atom_syntax, lexeme.lex[2]); /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 3: singlet emitter l */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 2;               /* singlet  emitter */
  A->coordbase[0]        = COORD_L;         /* l */
  A->offset[0]           = 0;        
  strcpy( A->atom_syntax, lexeme.lex[3]);   /* atom name  */
  strcpy(A->edist_name[0], (lexeme.l > 6)? lexeme.lex[6] : ((lexeme.l > 5)? lexeme.lex[5] : "e0")); /* edist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 4: nonterminal (l+1,j) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;             /* nonterminal */
  A->coordbase[0]        = COORD_L;       /* l+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_J;       /* j */
  A->offset[1]           = 0;        
  A->max_nctxts          = 1;             /* context */
  A->maxctxt_basetag[0]  = -1;            /* -1 tag */
  strcpy( A->atom_syntax, lexeme.lex[4]); /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #23 EMISSION NONTERM EMISSION EMISSION 
 *
 * 2 atoms, three-way emission i,j-1,j, and nonterminal (i+1,j-2)
 *
 */
int
yacc_rule23(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule23");
  
  if (lexeme.l < 6)       /* joint emission */
    natoms = yacc_rule23_2at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return natoms;
}
int
yacc_rule23_2at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;
  int   notallowed = FALSE;

  if (is_base_pair(lexeme.lex[2], lexeme.lex[3])) notallowed = TRUE;

  if (is_base_pair(lexeme.lex[0], lexeme.lex[2]) ||
      is_base_pair(lexeme.lex[0], lexeme.lex[3]) ) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;

  strcpy(yr_name, "yacc_rule23_2at");
  R->natoms = 2;

  /* atom 0: three-way emitter i,j-1,j */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 3;             /* three-way emitter */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_J;       /* j-1 */
  A->offset[1]              = -1;        
  A->coordbase[2]           = COORD_J;       /* j */
  A->offset[2]              = 0; 
  A->bp[0].basepairtype     = rna_atom_basepairtype(A, lexeme.lex[1]);
  if      (is_base_pair(lexeme.lex[0], lexeme.lex[2])) {
    A->bp[0].basepair_coordl_idx = 0;
    A->bp[0].basepair_coordr_idx = 1;
  }
  else if (is_base_pair(lexeme.lex[0], lexeme.lex[3])) {
    A->bp[0].basepair_coordl_idx = 0;
    A->bp[0].basepair_coordr_idx = 2;
  }
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[2]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */

 /* edist name */
  if      (lexeme.l == 4) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 5) { 
    if (strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]);
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+1,j-2) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;            /* nonterminal */
  A->coordbase[0]           = COORD_I;      /* i+1 */
  A->offset[0]              = +1;        
  A->coordbase[1]           = COORD_J;      /* j-2 */
  A->offset[1]              = -2;        
  A->max_nctxts             = 3;             /* context */
  A->maxctxt_basetag[0]     = -1;            /* -1 tag */
  A->maxctxt_basetag[1]     = +1;            /* +1 tag */
  A->maxctxt_basetag[2]     = +2;            /* +2 tag */
  strcpy(A->atom_syntax, lexeme.lex[1]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #24 EMISSION EMISSION NONTERM EMISSION
 *
 * 2 atoms, three-way emission i,i+1,j, and nonterminal (i+2,j-1)
 *
 */
int
yacc_rule24(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule24");
  
  if (lexeme.l < 6)       /* joint emission */
    natoms = yacc_rule24_2at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return natoms;
}
int
yacc_rule24_2at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;
  int   notallowed = FALSE;

  if (is_base_pair(lexeme.lex[0], lexeme.lex[1])) notallowed = TRUE;

  if (is_base_pair(lexeme.lex[0], lexeme.lex[3]) ||
      is_base_pair(lexeme.lex[1], lexeme.lex[3]) ) 
    nbasepairs = TRUE;
  else 
    nbasepairs = FALSE;

  strcpy(yr_name, "yacc_rule24_2at");
  R->natoms = 2;

  /* atom 0: three-way emitter i,i+1,j */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 3;             /* three-way emitter */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_I;       /* i+1 */
  A->offset[1]              = +1;        
  A->coordbase[2]           = COORD_K;       /* j */
  A->offset[2]              = 0; 
  A->bp[0].basepairtype     = rna_atom_basepairtype(A, lexeme.lex[2]);
  if      (is_base_pair(lexeme.lex[0], lexeme.lex[3])) {
    A->bp[0].basepair_coordl_idx = 0;
    A->bp[0].basepair_coordr_idx = 2;
  }
  else if (is_base_pair(lexeme.lex[1], lexeme.lex[3])) {
    A->bp[0].basepair_coordl_idx = 1;
    A->bp[0].basepair_coordr_idx = 2;
  }
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[1]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */

 /* edist name */
  if      (lexeme.l == 4) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 5) { 
    if (strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]);
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+2,j-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_I;       /* i+2 */
  A->offset[0]              = +2;        
  A->coordbase[1]           = COORD_J;       /* j-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 3;             /* context */
  A->maxctxt_basetag[0]     = -2;            /* -2 tag */
  A->maxctxt_basetag[1]     = -1;            /* -1 tag */
  A->maxctxt_basetag[2]     = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[2]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #25 EMISSION EMISSION NONTERM EMISSION EMISSION
 *
 * 2 atoms, four-way emission i,i+1,j-1,j, and nonterminal (i+2,j-2)
 *
 */
int
yacc_rule25(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule25");
  
  if (lexeme.l < 7)       /* joint emission */
    natoms = yacc_rule25_2at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return natoms;
}
int
yacc_rule25_2at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;
  int   notallowed = FALSE;

  if (is_base_pair(lexeme.lex[0], lexeme.lex[1])) notallowed = TRUE; /* a a' T b c  */
  if (is_base_pair(lexeme.lex[3], lexeme.lex[4])) notallowed = TRUE; /* b c  T a a' */

  if ( (is_base_pair(lexeme.lex[0], lexeme.lex[4]) && is_base_pair(lexeme.lex[1], lexeme.lex[3])) || /* a b T b' a' */
       (is_base_pair(lexeme.lex[0], lexeme.lex[3]) && is_base_pair(lexeme.lex[1], lexeme.lex[4]))    /* a b T a' b' (pknot) */
     ) 
    nbasepairs = 2;
  else if (is_base_pair(lexeme.lex[0], lexeme.lex[3]) || /* a b T a' c  */
	   is_base_pair(lexeme.lex[0], lexeme.lex[4]) || /* a b T c  a' */
	   is_base_pair(lexeme.lex[1], lexeme.lex[3]) || /* b a T a' c  */
	   is_base_pair(lexeme.lex[1], lexeme.lex[4])    /* b a T c  a' */
	   ) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;

  strcpy(yr_name, "yacc_rule25_2at");
  R->natoms = 2;

  /* atom 0: four-way emitter i,i+1,j-1, j */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 4;             /* four-way emitter */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_I;       /* i+1 */
  A->offset[1]              = +1;        
  A->coordbase[2]           = COORD_J;       /* j-1 */
  A->offset[2]              = -1; 
  A->coordbase[3]           = COORD_J;       /* j */
  A->offset[3]              = 0; 
  if      (nbasepairs == 2) {
    A->bp[0].basepairtype   = rna_atom_basepairtype(A, lexeme.lex[2]);
    A->bp[1].basepairtype   = rna_atom_basepairtype(A, lexeme.lex[2]);

    /* a b T b' a' */
    if      (is_base_pair(lexeme.lex[0], lexeme.lex[4]) && is_base_pair(lexeme.lex[1], lexeme.lex[3])) {
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 3;
      A->bp[1].basepair_coordl_idx = 1;
      A->bp[1].basepair_coordr_idx = 2;
    }
    
    /* a b T a' b' (pknot) */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[3]) && is_base_pair(lexeme.lex[1], lexeme.lex[4])) {
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 2;
      A->bp[1].basepair_coordl_idx = 1;
      A->bp[1].basepair_coordr_idx = 3;
    }
    
    else 
      grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (nbasepairs == 1) {
    A->bp[0].basepairtype          = rna_atom_basepairtype(A, lexeme.lex[2]);

    /* a b T a' c  */
    if      (is_base_pair(lexeme.lex[0], lexeme.lex[3])) {
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 2;
    }

    /* a b T c  a' */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[4])) {
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 3;
    }

    /* b a T a' c  */
    else if (is_base_pair(lexeme.lex[1], lexeme.lex[3])) {
      A->bp[0].basepair_coordl_idx = 1;
      A->bp[0].basepair_coordr_idx = 2;
    }

    /* b a T c  a' */    
    else if (is_base_pair(lexeme.lex[1], lexeme.lex[4])) {
      A->bp[0].basepair_coordl_idx = 1;
      A->bp[0].basepair_coordr_idx = 3;
    }

    else 
      grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }

  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[1]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[4]);    /* atom name  */

 /* edist name */
  if      (lexeme.l == 5) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 6) { 
    if (strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]);
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+2,j-2) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_I;       /* i+2 */
  A->offset[0]              = +2;        
  A->coordbase[1]           = COORD_J;       /* j-2 */
  A->offset[1]              = -2;        
  A->max_nctxts             = 4;             /* context */
  A->maxctxt_basetag[0]     = -2;            /* -2 tag */
  A->maxctxt_basetag[1]     = -1;            /* -1 tag */
  A->maxctxt_basetag[2]     = +1;            /* +1 tag */
  A->maxctxt_basetag[3]     = +2;            /* +2 tag */
  strcpy(A->atom_syntax, lexeme.lex[2]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #26 EMISSION NONTERM EMISSION EMISSION NONTERM EMISSION
 *
 * 3 atoms, four-way emission i,k,k+1,j, nonterminal (i+1,k-1), and nonterminal (k+2,j-1)
 *
 */
int
yacc_rule26(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule26");
  
  if (lexeme.l < 8)       /* joint emission */
    natoms = yacc_rule26_3at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return natoms;
}
int
yacc_rule26_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;
  int   notallowed = FALSE;

  if (is_base_pair(lexeme.lex[2], lexeme.lex[3])) notallowed = TRUE; /* a T b b' Q c */

  if ( (is_base_pair(lexeme.lex[0], lexeme.lex[2]) && is_base_pair(lexeme.lex[3], lexeme.lex[5])) || /* a T a' b  Q b' */
       (is_base_pair(lexeme.lex[0], lexeme.lex[3]) && is_base_pair(lexeme.lex[2], lexeme.lex[5]))    /* a T b  a' Q b' (pknot) */
       ) 
    nbasepairs = 2;
  else if (is_base_pair(lexeme.lex[0], lexeme.lex[2]) || /* a T a' b  Q c */
	   is_base_pair(lexeme.lex[0], lexeme.lex[3]) || /* a T b  a' Q c */
	   is_base_pair(lexeme.lex[2], lexeme.lex[5]) || /* b T c  a  Q a' */
	   is_base_pair(lexeme.lex[3], lexeme.lex[5]) || /* b T a  c  Q a' */
	   is_base_pair(lexeme.lex[0], lexeme.lex[5])    /* a T b  c  Q a' */
	   ) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;
  
  strcpy(yr_name, "yacc_rule26_3at");
  R->natoms = 3;

  /* atom 0: four-way emitter i,k,k+1,j */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 4;             /* four-way emitter */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_K;       /* k */
  A->offset[1]              = 0;        
  A->coordbase[2]           = COORD_K;       /* k+1 */
  A->offset[2]              = +1; 
  A->offset[3]              = 0; 
  if      (nbasepairs == 2) {
    A->bp[0].basepairtype   = rna_atom_basepairtype(A, lexeme.lex[1]);
    A->bp[1].basepairtype   = rna_atom_basepairtype(A, lexeme.lex[4]);
    
    /* a T a' b  Q b' */
    if       (is_base_pair(lexeme.lex[0], lexeme.lex[2]) && is_base_pair(lexeme.lex[3], lexeme.lex[5])) {
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 1;     
      A->bp[1].basepair_coordl_idx = 2;
      A->bp[1].basepair_coordr_idx = 3;     
    }

    /* a T b  a' Q b' (pknot) */
    else if  (is_base_pair(lexeme.lex[0], lexeme.lex[3]) && is_base_pair(lexeme.lex[2], lexeme.lex[5])) {
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 2;     
      A->bp[1].basepair_coordl_idx = 1;
      A->bp[1].basepair_coordr_idx = 3;     
    }

    else 
      grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (nbasepairs == 1) {

    /* a T a' b  Q c */
    if      (is_base_pair(lexeme.lex[0], lexeme.lex[2])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[1]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 1;     
    }

    /* a T b  a' Q c */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[3])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[1]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 2;     
    }

    /* b T c  a  Q a' */
    else if (is_base_pair(lexeme.lex[2], lexeme.lex[5])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[4]);
      A->bp[0].basepair_coordl_idx = 1;
      A->bp[0].basepair_coordr_idx = 3;     
    }

    /* b T a  c  Q a' */
    else if (is_base_pair(lexeme.lex[3], lexeme.lex[5])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[4]);
      A->bp[0].basepair_coordl_idx = 2;
      A->bp[0].basepair_coordr_idx = 3;     
    }

    /* a T b  c  Q a' */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[5])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, G->nt[R->nt_idx].ntname);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 3;     
    }

    else 
      grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[2]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[5]);    /* atom name  */

 /* edist name */
  if      (lexeme.l == 6) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 7) { 
    if (strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[6]);
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+1,k-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_I;       /* i+1 */
  A->offset[0]              = +1;        
  A->coordbase[1]           = COORD_K;       /* k-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 3;             /* context */
  A->maxctxt_basetag[0]     = -1;            /* -1 tag */
  A->maxctxt_basetag[1]     = +1;            /* +1 tag */
  A->maxctxt_basetag[2]     = +2;            /* +2 tag */
  strcpy(A->atom_syntax, lexeme.lex[1]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+2,j-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_K;       /* k+2 */
  A->offset[0]              = +2;        
  A->coordbase[1]           = COORD_J;       /* j-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 3;             /* context */
  A->maxctxt_basetag[0]     = -2;            /* -2 tag */
  A->maxctxt_basetag[1]     = -1;            /* -1 tag */
  A->maxctxt_basetag[2]     = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[4]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #27 EMISSION NONTERM EMISSION EMISSION EMISSION NONTERM EMISSION
 *
 * 3 atoms, five-way emission i,k,k+1,k+2,j, nonterminal (i+1,k-1), and nonterminal (k+3,j-1)
 *
 */
int
yacc_rule27(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule27");
  
  if (lexeme.l < 9)       /* joint emission */
    natoms = yacc_rule27_3at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return natoms;
}
int
yacc_rule27_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;
  int   notallowed = FALSE;

  if (is_base_pair(lexeme.lex[2], lexeme.lex[3])) notallowed = TRUE; /* a T b b' c  Q g */
  if (is_base_pair(lexeme.lex[2], lexeme.lex[4])) notallowed = TRUE; /* a T b c  b' Q g */
  if (is_base_pair(lexeme.lex[3], lexeme.lex[4])) notallowed = TRUE; /* a T c b  b' Q g */

  if ( (is_base_pair(lexeme.lex[0], lexeme.lex[2]) && is_base_pair(lexeme.lex[4], lexeme.lex[6])) || /* a T a' c  b  Q b'  */
       (is_base_pair(lexeme.lex[0], lexeme.lex[3]) && is_base_pair(lexeme.lex[4], lexeme.lex[6])) || /* a T c  a' b  Q b'  */
       (is_base_pair(lexeme.lex[0], lexeme.lex[2]) && is_base_pair(lexeme.lex[3], lexeme.lex[6])) || /* a T a' b  c  Q b'  */
       (is_base_pair(lexeme.lex[0], lexeme.lex[4]) && is_base_pair(lexeme.lex[2], lexeme.lex[6])) || /* a T b  c  a' Q b'  (pknot) */
       (is_base_pair(lexeme.lex[0], lexeme.lex[3]) && is_base_pair(lexeme.lex[2], lexeme.lex[6])) || /* a T b  a' c  Q b'  (pknot) */
       (is_base_pair(lexeme.lex[0], lexeme.lex[4]) && is_base_pair(lexeme.lex[3], lexeme.lex[6]))    /* a T c  b  a' Q b'  (pknot) */
       ) 
    nbasepairs = 2;
  else if (is_base_pair(lexeme.lex[0], lexeme.lex[2]) || /* a T a' b  c  Q f  */
	   is_base_pair(lexeme.lex[0], lexeme.lex[3]) || /* a T b  a' c  Q f  */
	   is_base_pair(lexeme.lex[0], lexeme.lex[4]) || /* a T b  c  a' Q f  */
	   is_base_pair(lexeme.lex[4], lexeme.lex[6]) || /* a T b  c  f  Q f' */
	   is_base_pair(lexeme.lex[3], lexeme.lex[6]) || /* a T b  f  c  Q f' */
	   is_base_pair(lexeme.lex[2], lexeme.lex[6]) || /* a T f  b  c  Q f' */
	   is_base_pair(lexeme.lex[0], lexeme.lex[6])    /* a T b  c  f  Q a' */
	   ) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;
  
  strcpy(yr_name, "yacc_rule27_3at");
  R->natoms = 3;

  /* atom 0: five-way emitter i,k,k+1,k+2,j */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 5;             /* five-way emitter */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_K;       /* k */
  A->offset[1]              = 0;        
  A->coordbase[2]           = COORD_K;       /* k+1 */
  A->offset[2]              = +1; 
  A->coordbase[3]           = COORD_K;       /* k+2 */
  A->offset[3]              = +2; 
  A->coordbase[4]           = COORD_J;       /* j */
  A->offset[4]              = 0; 
  if      (nbasepairs == 2) {
    A->bp[0].basepairtype   = rna_atom_basepairtype(A, lexeme.lex[1]);
    A->bp[1].basepairtype   = rna_atom_basepairtype(A, lexeme.lex[5]);
    
    /* a T a' c  b  Q b'  */
    if       (is_base_pair(lexeme.lex[0], lexeme.lex[2]) && is_base_pair(lexeme.lex[4], lexeme.lex[6])) {
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 1;     
      A->bp[1].basepair_coordl_idx = 3;
      A->bp[1].basepair_coordr_idx = 4;     
    }

    /* a T c  a' b  Q b'  */
    else if  (is_base_pair(lexeme.lex[0], lexeme.lex[3]) && is_base_pair(lexeme.lex[4], lexeme.lex[6])) {
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 2;     
      A->bp[1].basepair_coordl_idx = 3;
      A->bp[1].basepair_coordr_idx = 4;     
    }

    /* a T a' b  c  Q b'  */
    else if  (is_base_pair(lexeme.lex[0], lexeme.lex[2]) && is_base_pair(lexeme.lex[3], lexeme.lex[6])) {
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 1;     
      A->bp[1].basepair_coordl_idx = 2;
      A->bp[1].basepair_coordr_idx = 4;     
    }

    /* a T b  c  a' Q b'  (pknot) */
    else if  (is_base_pair(lexeme.lex[0], lexeme.lex[4]) && is_base_pair(lexeme.lex[2], lexeme.lex[6])) {
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 3;     
      A->bp[1].basepair_coordl_idx = 1;
      A->bp[1].basepair_coordr_idx = 4;     
    }

    /* a T b  a' c  Q b'  (pknot) */
    else if  (is_base_pair(lexeme.lex[0], lexeme.lex[3]) && is_base_pair(lexeme.lex[2], lexeme.lex[6])) {
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 2;     
      A->bp[1].basepair_coordl_idx = 1;
      A->bp[1].basepair_coordr_idx = 4;     
    }
    
    /* a T c  b  a' Q b'  (pknot) */
    else if  (is_base_pair(lexeme.lex[0], lexeme.lex[4]) && is_base_pair(lexeme.lex[3], lexeme.lex[6])) {
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 3;     
      A->bp[1].basepair_coordl_idx = 2;
      A->bp[1].basepair_coordr_idx = 4;     
    }

    else 
      grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (nbasepairs == 1) {

    /* a T a' b  c  Q f  */
    if      (is_base_pair(lexeme.lex[0], lexeme.lex[2])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[1]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 1;     
    }

    /* a T b  a' c  Q f  */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[3])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[1]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 2;     
    }

    /* a T b  c  a' Q f  */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[4])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[1]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 3;     
    }

    /* a T b  c  f  Q f' */
    else if (is_base_pair(lexeme.lex[4], lexeme.lex[6])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[5]);
      A->bp[0].basepair_coordl_idx = 3;
      A->bp[0].basepair_coordr_idx = 4;     
    }

    /* a T b  f  c  Q f' */
    else if (is_base_pair(lexeme.lex[3], lexeme.lex[6])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[5]);
      A->bp[0].basepair_coordl_idx = 2;
      A->bp[0].basepair_coordr_idx = 4;     
    }

    /* a T f  b  c  Q f' */    
    else if (is_base_pair(lexeme.lex[2], lexeme.lex[6])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[5]);
      A->bp[0].basepair_coordl_idx = 1;
      A->bp[0].basepair_coordr_idx = 4;     
    }

    /* a T b  c  f  Q a' */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[6])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, G->nt[R->nt_idx].ntname);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 4;     
    }

    else 
      grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }

  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[2]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[4]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[6]);    /* atom name  */

 /* edist name */
  if      (lexeme.l == 7) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 8) { 
    if (strstr(lexeme.lex[7], "e")) strcpy(A->edist_name[0], lexeme.lex[7]);
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+1,k-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_I;       /* i+1 */
  A->offset[0]              = +1;        
  A->coordbase[1]           = COORD_K;       /* k-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 4;             /* context */
  A->maxctxt_basetag[0]     = -1;            /* -1 tag */
  A->maxctxt_basetag[1]     = +1;            /* +1 tag */
  A->maxctxt_basetag[2]     = +2;            /* +2 tag */
  A->maxctxt_basetag[3]     = +3;            /* +3 tag */
  strcpy(A->atom_syntax, lexeme.lex[1]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+3,j-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_K;       /* k+3 */
  A->offset[0]              = +3;        
  A->coordbase[1]           = COORD_J;       /* j-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 4;             /* context */
  A->maxctxt_basetag[0]     = -3;            /* -3 tag */
  A->maxctxt_basetag[1]     = -2;            /* -2 tag */
  A->maxctxt_basetag[2]     = -1;            /* -1 tag */
  A->maxctxt_basetag[3]     = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[5]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #28 MONOSEGMENT
 *
 * 1 atom: monosegment (i to j)
 */
int
yacc_rule28(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule28");
  R->natoms = 1;

  /* atom 0: monosegment (i to j) */
  A = &(R->atom[++a]);
  A->atomtype            = MONOSEGMENT_ATOM;
  A->nldists             = 1; 
  A->has_basepair        = FALSE;
  A->nldists             = 1; 
  A->ncoords             = 2;              /* monosegment */
  A->coordbase[0]        = COORD_I;        /* i */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_J;        /* j */
  A->offset[1]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[0]);   /* atom name  */
  strcpy(A->ldist_name[0], (lexeme.l > 1)? lexeme.lex[1] : "l0"); /* ldist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #29 MONOSEGMENT NONTERM
 *
 * 2 atoms: monosegment (i to k) and nonterminal (k+1,j)
 */
int
yacc_rule29(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule29");
  R->natoms = 2;

  /* atom 0: monosegment (i to k) */
  A = &(R->atom[++a]);
  A->atomtype            = MONOSEGMENT_ATOM;
  A->nldists             = 1; 
  A->has_basepair        = FALSE;
  A->ncoords             = 2;              /* monosegment */
  A->coordbase[0]        = COORD_I;        /* i */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_K;        /* k */
  A->offset[1]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[0]);   /* atom name  */
  strcpy(A->ldist_name[0], (lexeme.l > 2)? lexeme.lex[2] : "l0"); /* ldist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 1: nonterminal (k+1,j) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;             /* nonterminal */
  A->coordbase[0]        = COORD_K;       /* k+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_J;       /* j */
  A->offset[1]           = 0;        
  A->max_nctxts          = 0;             /* context */
  strcpy(A->atom_syntax, lexeme.lex[1]);  /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #30 NONTERM MONOSEGMENT 
 *
 * 2 atoms: nonterminal (i,l-1) and  monosegment (l to j)
 */
int
yacc_rule30(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule30");
  R->natoms = 2;

  /* atom 0: nonterminal (i,l-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;             /* nonterminal */
  A->coordbase[0]        = COORD_I;       /* i */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_L;       /* l-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 0;             /* context */
  strcpy(A->atom_syntax, lexeme.lex[0]);  /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 1: monosegment (k+1 to j) */
  A = &(R->atom[++a]);
  A->atomtype            = MONOSEGMENT_ATOM;
  A->nldists             = 1; 
  A->has_basepair        = FALSE;
  A->ncoords             = 2;              /* monosegment */
  A->coordbase[0]        = COORD_L;        /* l */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_J;        /* j */
  A->offset[1]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[1]);   /* atom name  */
  strcpy(A->ldist_name[0], (lexeme.l > 2)? lexeme.lex[2] : "l0"); /* ldist name */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #31 LDISEGMENT NONTERM RDISEGMENT
 *
 * 2 atoms: disegment (i to k) + (l to j) and nonterminal (k+1,l-1) 
 */
int
yacc_rule31(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule31");
  
  if      (!strcmp(lexeme.lex[2], "...d"))  /* disegment */
    natoms = yacc_rule31_untied(R, lexeme, G, verbose);
  else if (!strcmp(lexeme.lex[2], "...d'")) /* tied_disegment */
    natoms = yacc_rule31_tied(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return natoms;
}
int
yacc_rule31_untied(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule31_untied");
  R->natoms = 2;

  /* atom 0: disegment (i to k)+(l to j) */
  A = &(R->atom[++a]);
  A->atomtype            = DISEGMENT_ATOM;
  A->has_basepair        = FALSE;
  A->nedists             = 0; 
  A->nldists             = 1; 
  A->ncoords             = 4;              /* disegment */
  A->coordbase[0]        = COORD_I;        /* i */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_K;        /* k */
  A->offset[1]           = 0;        
  A->coordbase[2]        = COORD_L;        /* l */
  A->offset[2]           = 0;        
  A->coordbase[3]        = COORD_J;        /* j */
  A->offset[3]           = 0;        
  A->max_nctxts          = 0;             /* context */
  A->ncontexts           = 0;             /* context */
  strcpy(A->atom_syntax, lexeme.lex[0]);   /* atom name  */
  strcat(A->atom_syntax, "^");             /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[2]);   /* atom name  */

  /* ldist name */
  if      (lexeme.l == 3) {
    A->nldists           = 1; 
    strcpy(A->ldist_name[0], "l0"); 
  }
  else if (lexeme.l == 4) {
    A->nldists           = 1; 
    if (strstr(lexeme.lex[3], "l")) strcpy(A->ldist_name[0], lexeme.lex[3]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 5) {
    A->nldists           = 2; 
    if (strstr(lexeme.lex[3], "l")) strcpy(A->ldist_name[0], lexeme.lex[3]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
    if (strstr(lexeme.lex[4], "l")) strcpy(A->ldist_name[1], lexeme.lex[4]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 1: nonterminal (k+1,l-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;             /* nonterminal */
  A->coordbase[0]        = COORD_K;       /* k+1 */
  A->offset[0]           = +1;        
  A->coordbase[1]        = COORD_L;       /* l-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 0;             /* context */
  strcpy(A->atom_syntax, lexeme.lex[1]);  /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

int
yacc_rule31_tied(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{ 
  NT  *nt;
  int  natoms = 0; /* natoms */
  
  nt = &(G->nt[R->nt_idx]);
  
  if (nt->ncontexts == 2)
    natoms = yacc_rule31_tied_context(R, lexeme, G, verbose);
  else if (nt->ncontexts == 0)
    natoms = yacc_rule31_tied_nocontext(R, lexeme, G, verbose);
  else
   grammar_fatal("rule %s nt %s, not IMPLEMENTED.", R->rule_syntax, G->nt[R->nt_idx].ntname);

  return natoms;
}

int
yacc_rule31_tied_context(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1;         /* atom index */
  int   e;              /* edist index */

  strcpy(yr_name, "yacc_rule31_tied_context");
  R->natoms = 2;

  /* atom 0: disegment (i to k)+(l to j) */
  A = &(R->atom[++a]);
  A->atomtype               = DISEGMENT_ATOM;
  A->nldists                = 1; 
  A->nbasepairs             = 1;
  A->has_basepair           = TRUE;
  A->nedists                = 16;             /* 16 (all are stacked pairs) */
  A->ncoords                = 4;              /* disegment */
  A->coordbase[0]           = COORD_I;        /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_K;        /* k */
  A->offset[1]              = 0;        
  A->coordbase[2]           = COORD_L;        /* l */
  A->offset[2]              = 0;        
  A->coordbase[3]           = COORD_J;        /* j */
  A->offset[3]              = 0;        
  A->bp[0].basepairtype     = rna_atom_basepairtype(A, lexeme.lex[1]);
  A->bp[0].basepair_coordl_idx = 0;
  A->bp[0].basepair_coordr_idx = 1;
  A->max_nctxts             = 0;             /* context */
  A->ncontexts              = 0;             /* context */
  strcpy(A->atom_syntax, lexeme.lex[0]);   /* atom name  */
  strcat(A->atom_syntax, "^");             /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[2]);   /* atom name  */

  /* ldist + edists name 
   *
   * default:              d... T ...d'
   *                       ldist:             l0
   *                       edist_idx = 0..31: e0_2_2
   *
   * specify ldist:        d... T ...d' ln
   *                       ldist:             ln
   *                       edist_idx = 0..31: e0_2_2
   *
   * specify the edists:   d... T ...d' em_2_2
   *                       ldist:             l0
   *                       edist_idx = 0..31: em_2_2
   *
   * specify the 2 dists:  d... T ...d' lk em_2_2
   *                       ldist:             lk
   *                       edist_idx = 0..31: em_2_2
   *
   */
  if      (lexeme.l == 3) {
    strcpy(A->ldist_name[0],    "l0");
    for (e = 0; e < 32; e ++) strcpy(A->edist_name[e], "e0_2_2");
  } 
  else if (lexeme.l == 4) {
    if      (strstr(lexeme.lex[3], "l")) 
      {
	strcpy(A->ldist_name[0], lexeme.lex[3]); 
	for (e = 0; e < 32; e ++) strcpy(A->edist_name[e], "e0_2_2");
      }
    else if (strstr(lexeme.lex[3], "e"))
      {
	strcpy(A->ldist_name[0],    "l0");
	for (e = 0; e < 32; e ++) strcpy(A->edist_name[e], lexeme.lex[3]); 
      }
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[3], "l") && strstr(lexeme.lex[4], "e")) 
      {
	strcpy(A->ldist_name[0], lexeme.lex[3]);
	if      (strstr(lexeme.lex[4], "_2_2")) for (e = 0; e < 32; e ++) strcpy(A->edist_name[e], lexeme.lex[4]); 
	else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
      }
    else if (strstr(lexeme.lex[3], "e") && strstr(lexeme.lex[4], "l"))
      {
	strcpy(A->ldist_name[0], lexeme.lex[4]);
	if      (strstr(lexeme.lex[3], "_2_2")) for (e = 0; e < 32; e ++) strcpy(A->edist_name[e], lexeme.lex[3]); 
	else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
      }
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  } 
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 1: nonterminal (k+1,l-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;             /* nonterminal */
  A->coordbase[0]        = COORD_K;       /* k+1 */
  A->offset[0]           = +1;        
  A->coordbase[1]        = COORD_L;       /* l-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 2;             /* context */
   strcpy(A->atom_syntax, lexeme.lex[1]); /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

int
yacc_rule31_tied_nocontext(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1;         /* atom index */
  int   e;              /* edist index */

  strcpy(yr_name, "yacc_rule31_tied_nocontext");
  R->natoms = 2;

  /* atom 0: disegment (i to k)+(l to j) */
  A = &(R->atom[++a]);
  A->atomtype               = DISEGMENT_ATOM;
  A->nldists                = 1; 
  A->nbasepairs             = 1;
  A->has_basepair           = TRUE;
  A->nedists                = 17;             /* 1 (terminal bp) + 16 (stacked pairs) */
  A->ncoords                = 4;              /* disegment */
  A->coordbase[0]           = COORD_I;        /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_K;        /* k */
  A->offset[1]              = 0;        
  A->coordbase[2]           = COORD_L;        /* l */
  A->offset[2]              = 0;        
  A->coordbase[3]           = COORD_J;        /* j */
  A->offset[3]              = 0;        
  A->bp[0].basepairtype     = rna_atom_basepairtype(A, lexeme.lex[1]);
  A->bp[0].basepair_coordl_idx = 0;
  A->bp[0].basepair_coordr_idx = 1;
  A->max_nctxts             = 0;             /* context */
  A->ncontexts              = 0;             /* context */
  strcpy(A->atom_syntax, lexeme.lex[0]);     /* atom name  */
  strcat(A->atom_syntax, "^");               /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[2]);     /* atom name  */

  /* ldist + 2 edists name 
   *
   * default:              d... T ...d'
   *                       ldist:             l0
   *                       edist_idx = 0:     e0_2_0
   *                       edist_idx = 1..16: e0_2_2
   *
   * specify ldist:        d... T ...d' ln
   *                       ldist:              ln
   *                       edist_idx = 0:     e0_2_0
   *                       edist_idx = 1..16: e0_2_2
   *
   * specify the 2 edists: d... T ...d' en_2_0 em_2_2
   *                       ldist:             l0
   *                       edist_idx = 0:     en_2_0
   *                       edist_idx = 1..16: em_2_2
   *
   * specify the 3 dists:  d... T ...d' lk en_2_0 em_2_2
   *                       ldist:             lk
   *                       edist_idx = 0:     en_2_0
   *                       edist_idx = 1..16: em_2_2
   *
   */
  if      (lexeme.l == 3) {
    strcpy(A->ldist_name[0],    "l0");
    strcpy(A->edist_name[0], "e0_2_0");
    for (e = 1; e <= 16; e ++) strcpy(A->edist_name[e], "e0_2_2");
  } 
  else if (lexeme.l == 4) {
    if      (strstr(lexeme.lex[3], "l")) 
      {
	strcpy(A->ldist_name[0], lexeme.lex[3]); 
	strcpy(A->edist_name[0], "e0_2_0");
	for (e = 1; e <= 16; e ++) strcpy(A->edist_name[e], "e0_2_2");
      }
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[3], "e") && strstr(lexeme.lex[4], "e")) 
      {
	strcpy(A->ldist_name[0], "l0"); 
	if      (strstr(lexeme.lex[3], "_2_0"))    strcpy(A->edist_name[0], lexeme.lex[3]); 
	else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

	if      (strstr(lexeme.lex[4], "_2_2")) for (e = 1; e <= 16; e ++) strcpy(A->edist_name[e], lexeme.lex[4]); 
	else if (strstr(lexeme.lex[4], "_2_0")) A->nedists = 1; /* no stacking */
	else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
      }
    else if (strstr(lexeme.lex[3], "l") && strstr(lexeme.lex[4], "e")) 
      {
	strcpy(A->ldist_name[0], lexeme.lex[3]); 
	if      (strstr(lexeme.lex[4], "_2_0")) {
	  strcpy(A->edist_name[0], lexeme.lex[4]);
	  for (e = 1; e <= 16; e ++) strcpy(A->edist_name[e], "e0_2_2");
	} 
	else if (strstr(lexeme.lex[4], "_2_2")) {
	  strcpy(A->edist_name[0], "e0_2_0");
	  for (e = 1; e <= 16; e ++) strcpy(A->edist_name[e], lexeme.lex[4]); 
	}
	else return eslFAIL;
      }
    else if (strstr(lexeme.lex[3], "e") && strstr(lexeme.lex[4], "l")) 
      {
	strcpy(A->ldist_name[0], lexeme.lex[4]); 
	if      (strstr(lexeme.lex[3], "_2_0")) {
	  strcpy(A->edist_name[0], lexeme.lex[3]);
	  for (e = 1; e <= 16; e ++) strcpy(A->edist_name[e], "e0_2_2");
	} 
	else if (strstr(lexeme.lex[3], "_2_2")) {
	  strcpy(A->edist_name[0], "e0_2_0");
	  for (e = 1; e <= 16; e ++) strcpy(A->edist_name[e], lexeme.lex[3]); 
	}
	else return eslFAIL;
 
      }
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  } 
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[3], "l") && strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e")) 
      {
	strcpy(A->ldist_name[0], lexeme.lex[3]);
	if      (strstr(lexeme.lex[4], "_2_0"))    strcpy(A->edist_name[0], lexeme.lex[4]); 
	else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

	if      (strstr(lexeme.lex[5], "_2_2")) for (e = 1; e <= 16; e ++) strcpy(A->edist_name[e], lexeme.lex[5]); 
	else if (strstr(lexeme.lex[5], "_2_0")) A->nedists = 1; /* no stacking */
	else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
      }
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  } 
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 1: nonterminal (k+1,l-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;             /* nonterminal */
  A->coordbase[0]        = COORD_K;       /* k+1 */
  A->offset[0]           = +1;        
  A->coordbase[1]        = COORD_L;       /* l-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 2;             /* context */
   strcpy(A->atom_syntax, lexeme.lex[1]); /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #32 MONOSEGMENT EMISSION NONTERM EMISSION 
 *
 * 3 atoms: monosegment (i to k), double emission k+1,j and nonterminal (k+2,j-1)
 */
int
yacc_rule32(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;

  strcpy(yr_name, "yacc_rule32");
  R->natoms = 3;

  if (is_base_pair(lexeme.lex[1], lexeme.lex[3])) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;

  /* atom 0: monosegment (i to k) */
  A = &(R->atom[++a]);
  A->atomtype               = MONOSEGMENT_ATOM;
  A->nldists                = 1; 
  A->has_basepair           = FALSE;
  A->ncoords                = 2;              /* monosegment */
  A->coordbase[0]           = COORD_I;        /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_K;        /* k */
  A->offset[1]              = 0;        
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */

  /* ldist name */
  if      (lexeme.l == 4) 
    strcpy(A->ldist_name[0], "l0"); 
  else if (lexeme.l == 5) {
    if (strstr(lexeme.lex[4], "l")) strcpy(A->ldist_name[0], lexeme.lex[4]);
    else                            strcpy(A->ldist_name[0], "l0"); 
  }
  else if (lexeme.l == 6) { 
    if      (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->ldist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->ldist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 1: doublet emitter (k+1,j) */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 2;             /* doublet  emitter */
  A->coordbase[0]           = COORD_K;       /* k + 1 */
  A->offset[0]              = 1;        
  A->coordbase[1]           = COORD_J;       /* j */
  A->offset[1]              = 0;        
  A->bp[0].basepairtype     = rna_atom_basepairtype(A, lexeme.lex[2]);
  A->bp[0].basepair_coordl_idx = (A->has_basepair)? 0 : -1;
  A->bp[0].basepair_coordr_idx = (A->has_basepair)? 1 : -1;
  strcpy(A->atom_syntax, lexeme.lex[1]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */

  /* edist name */
  if      (lexeme.l == 4) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 5) {
    if (strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else                            strcpy(A->edist_name[0], "e0"); 
  }
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 2: nonterminal (k+2,j-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;              /* nonterminal */
  A->coordbase[0]           = COORD_K;        /* k+1 */
  A->offset[0]              = 2;        
  A->coordbase[1]           = COORD_J;        /* j-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 2;             /* context */
  A->maxctxt_basetag[0]     = -1;            /* -1 tag */
  A->maxctxt_basetag[1]     = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[2]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #33 EMISSION NONTERM EMISSION MONOSEGMENT
 *
 * 3 atoms: double emission i,l-1,  nonterminal (i+1,l-2) and monosegment (l to j), 
 */
int
yacc_rule33(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;

  strcpy(yr_name, "yacc_rule33");
  R->natoms = 3;

  if (is_base_pair(lexeme.lex[0], lexeme.lex[2])) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;

  /* atom 0: doublet emitter (i,l-1) */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 2;             /* doublet emitter */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_L;       /* l-1 */
  A->offset[1]              = -1;        
  A->bp[0].basepairtype     = rna_atom_basepairtype(A, lexeme.lex[2]);
  A->bp[0].basepair_coordl_idx = (A->has_basepair)? 0 : -1;
  A->bp[0].basepair_coordr_idx = (A->has_basepair)? 1 : -1;
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[2]);    /* atom name  */

  /* edist name */
  if      (lexeme.l == 4) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 5) { 
    if (strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]);
    else                            strcpy(A->edist_name[0], "e0"); 
  }
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 1: nonterminal (i+1,l-2) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_I;       /* i+1 */
  A->offset[0]              = 1;        
  A->coordbase[1]           = COORD_L;       /* l-2 */
  A->offset[1]              = -2;        
  A->max_nctxts             = 2;             /* context */
  A->maxctxt_basetag[0]     = -1;            /* -1 tag */
  A->maxctxt_basetag[1]     = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[1]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 2: monosegment (l to j) */
  A = &(R->atom[++a]);
  A->atomtype               = MONOSEGMENT_ATOM;
  A->nldists                = 1; 
  A->has_basepair           = FALSE;
  A->ncoords                = 2;             /* monosegment */
  A->coordbase[0]           = COORD_L;       /* l */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_J;       /* j */
  A->offset[1]              = 0;        
  strcpy(A->atom_syntax, lexeme.lex[3]);     /* atom name  */

  /* ldist name */
  if       (lexeme.l == 4) 
    strcpy(A->ldist_name[0], "l0"); 
  else if (lexeme.l == 5) {
    if (strstr(lexeme.lex[4], "l")) strcpy(A->ldist_name[0], lexeme.lex[4]);
    else                            strcpy(A->ldist_name[0], "l0"); 
  }
  else if (lexeme.l == 6) { 
    if      (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->ldist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->ldist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else  grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #34 LDISEGMENT EMISSION NONTERM EMISSION RDISEGMENT
 *
 * 3 atoms: disegment (i to k) + (l to j) double emission k+1,l-1,  and nonterminal (k+2,l-2) 
 */
int
yacc_rule34(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;

  strcpy(yr_name, "yacc_rule34");
  R->natoms = 3;

  if (is_base_pair(lexeme.lex[1], lexeme.lex[3])) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;

  /* atom 0: disegment (i to k)+(l to j) */
  A = &(R->atom[++a]);
  A->atomtype               = DISEGMENT_ATOM;
  A->nldists                = 1; 
  A->has_basepair           = FALSE;
  A->ncoords                = 4;              /* disegment */
  A->coordbase[0]           = COORD_I;        /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_K;        /* k */
  A->offset[1]              = 0;        
  A->coordbase[2]           = COORD_L;        /* l */
  A->offset[2]              = 0;        
  A->coordbase[3]           = COORD_J;        /* j */
  A->offset[3]              = 0;        
  A->nedists                = 0;
  A->ncontexts              = 0;
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[4]);    /* atom name  */

  /* ldist name */
  if      (lexeme.l == 5) 
    strcpy(A->ldist_name[0], "l0"); 
  else if (lexeme.l == 6) {
    if (strstr(lexeme.lex[5], "l")) strcpy(A->ldist_name[0], lexeme.lex[5]);
    else                            strcpy(A->ldist_name[0], "l0"); 
  }
  else if (lexeme.l == 7) {
    if      (strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e")) strcpy(A->ldist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l")) strcpy(A->ldist_name[0], lexeme.lex[6]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: doublet emitter (k+1,l-1) */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 2;             /* doublet emitter */
  A->coordbase[0]           = COORD_K;       /* k+1 */
  A->offset[0]              = +1;        
  A->coordbase[1]           = COORD_L;       /* l-1 */
  A->offset[1]              = -1;        
  A->bp[0].basepairtype     = rna_atom_basepairtype(A, lexeme.lex[2]);
  A->bp[0].basepair_coordl_idx = (A->has_basepair)? 0 : -1;
  A->bp[0].basepair_coordr_idx = (A->has_basepair)? 1 : -1;
  strcpy(A->atom_syntax, lexeme.lex[1]); /* atom name  */
  strcat(A->atom_syntax, "^");           /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]); /* atom name  */

  /* edist name */
  if      (lexeme.l == 5) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 6) {
    if (strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]);
    else                            strcpy(A->edist_name[0], "e0"); 
  }
  else if (lexeme.l == 7) {
    if      (strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[6]); 
    else grammar_fatal("yacc_rule25() failed at atom %s rule %s nt %s.", A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 2: nonterminal (k+2,l-2) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;              /* nonterminal */
  A->coordbase[0]           = COORD_K;        /* k + 2 */
  A->offset[0]              = +2;        
  A->coordbase[1]           = COORD_L;        /* l - 2 */
  A->offset[1]              = -2;        
  A->max_nctxts             = 2;             /* context */
  A->maxctxt_basetag[0]     = -1;            /* -1 tag */
  A->maxctxt_basetag[1]     = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[2]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #35 EMISSION MONOSEGMENT EMISSION  
 *
 * 2 atoms: double emission i,j, and monosegment (i+1 to j-1)
 *
 * 3 atoms: singlet emission i, monosegment (i+1 to j-1), and singlet emission j 
 *
 */
int
yacc_rule35(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule35");
  
  if (lexeme.l < 6)       /* joint emission */
    natoms = yacc_rule35_2at(R, lexeme, G, verbose);
  else if (lexeme.l == 6) /* independent emissions */
    natoms = yacc_rule35_3at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return natoms;
}
int
yacc_rule35_2at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;

  strcpy(yr_name, "yacc_rule35_2at");
  R->natoms = 2;

  if (is_base_pair(lexeme.lex[0], lexeme.lex[2])) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;

  /* atom 0: doublet emitter (i,j) */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 2;             /* doublet emitter */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_J;       /* j */
  A->offset[1]              = 0;        
  A->bp[0].basepairtype     = rna_atom_basepairtype(A, G->nt[R->nt_idx].ntname);
  A->bp[0].basepair_coordl_idx = (A->has_basepair)? 0 : -1;
  A->bp[0].basepair_coordr_idx = (A->has_basepair)? 1 : -1;
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[2]);    /* atom name  */

  /* edist name */
  if      (lexeme.l == 3) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 4) { 
    if      (strstr(lexeme.lex[3], "e")) strcpy(A->edist_name[0], lexeme.lex[3]);
    else if (strstr(lexeme.lex[3], "l")) strcpy(A->edist_name[0], "e0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[3], "e") && strstr(lexeme.lex[4], "l")) strcpy(A->edist_name[0], lexeme.lex[3]); 
    else if (strstr(lexeme.lex[3], "l") && strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

   /* atom 1: monosegment (i+1 to j-1) */
  A = &(R->atom[++a]);
  A->atomtype               = MONOSEGMENT_ATOM;
  A->nldists                = 1; 
  A->has_basepair           = FALSE;
  A->ncoords                = 2;              /* monosegment */
  A->coordbase[0]           = COORD_I;        /* i+1 */
  A->offset[0]              = +1;        
  A->coordbase[1]           = COORD_J;        /* j-1 */
  A->offset[1]              = -1;        
  strcpy(A->atom_syntax, lexeme.lex[1]);    /* atom name  */

  /* ldist name */
  if      (lexeme.l == 3) 
    strcpy(A->ldist_name[0], "l0"); 
  else if (lexeme.l == 4) { 
    if      (strstr(lexeme.lex[3], "l")) strcpy(A->ldist_name[0], lexeme.lex[3]);
    else if (strstr(lexeme.lex[3], "e")) strcpy(A->ldist_name[0], "l0"); 
  }
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[3], "l") && strstr(lexeme.lex[4], "e")) strcpy(A->ldist_name[0], lexeme.lex[3]); 
    else if (strstr(lexeme.lex[3], "e") && strstr(lexeme.lex[4], "l")) strcpy(A->ldist_name[0], lexeme.lex[4]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}
int
yacc_rule35_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule35_3at");
  R->natoms = 3;

  /* atom 0: singlet emitter i */
  A = &(R->atom[++a]);
  A->atomtype          = EMISSION_ATOM;
  A->has_basepair      = FALSE;
  A->ncoords           = 1;             /* singlet emitter */
  A->coordbase[0]      = COORD_I;       /* i */
  A->offset[0]         = 0;        
  strcpy(A->atom_syntax, lexeme.lex[0]); /* atom name  */

  /* edist name */
  if      (lexeme.l == 3) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 4) { 
    if      (strstr(lexeme.lex[3], "e")) strcpy(A->edist_name[0], lexeme.lex[3]);
    else if (strstr(lexeme.lex[3], "l")) strcpy(A->edist_name[0], "e0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[3], "e") && strstr(lexeme.lex[4], "l")) strcpy(A->edist_name[0], lexeme.lex[3]); 
    else if (strstr(lexeme.lex[3], "e") && strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[3]); 
    else if (strstr(lexeme.lex[3], "l") && strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[3], "e") && strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->edist_name[0], lexeme.lex[3]); 
    else if (strstr(lexeme.lex[3], "e") && strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[3]); 
    else if (strstr(lexeme.lex[3], "l") && strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

   /* atom 1: monosegment (i+1 to j-1) */
  A = &(R->atom[++a]);
  A->atomtype          = MONOSEGMENT_ATOM;
  A->nldists           = 1; 
  A->has_basepair      = FALSE;
  A->ncoords           = 2;              /* monosegment */
  A->coordbase[0]      = COORD_I;        /* i+1 */
  A->offset[0]         = +1;        
  A->coordbase[1]      = COORD_J;        /* j-1 */
  A->offset[1]         = -1;        
  strcpy(A->atom_syntax, lexeme.lex[1]); /* atom name  */

  /* ldist name */
  if      (lexeme.l == 3) 
    strcpy(A->edist_name[0], "l0"); 
  else if (lexeme.l == 4) { 
    if      (strstr(lexeme.lex[3], "l")) strcpy(A->ldist_name[0], lexeme.lex[3]);
    else if (strstr(lexeme.lex[3], "e")) strcpy(A->ldist_name[0], "l0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[3], "e") && strstr(lexeme.lex[4], "l")) strcpy(A->ldist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[3], "e") && strstr(lexeme.lex[4], "e")) strcpy(A->ldist_name[0], "l0"); 
    else if (strstr(lexeme.lex[3], "l") && strstr(lexeme.lex[4], "e")) strcpy(A->ldist_name[0], lexeme.lex[3]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[3], "e") && strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->ldist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[3], "e") && strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->ldist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[3], "l") && strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e")) strcpy(A->ldist_name[0], lexeme.lex[3]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 2: singlet emitter j */
  A = &(R->atom[++a]);
  A->atomtype          = EMISSION_ATOM;
  A->has_basepair      = FALSE;
  A->ncoords           = 1;             /* singlet emitter */
  A->coordbase[0]      = COORD_J;       /* j */
  A->offset[0]         = 0;        
  strcpy(A->atom_syntax, lexeme.lex[2]); /* atom name  */

  /* edist name */
  if      (lexeme.l == 3) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 4) { 
    if      (strstr(lexeme.lex[3], "e")) strcpy(A->edist_name[0], lexeme.lex[3]);
    else if (strstr(lexeme.lex[3], "l")) strcpy(A->edist_name[0], "e0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[3], "e") && strstr(lexeme.lex[4], "l")) strcpy(A->edist_name[0], lexeme.lex[3]); 
    else if (strstr(lexeme.lex[3], "e") && strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[3], "l") && strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[3], "e") && strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[3], "e") && strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[3], "l") && strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #36 EMISSION MONOSEGMENT NONTERM EMISSION 
 *
 * 3 atoms: double emission i,j, monosegment (i+1 to k), and nonterminal (k+1,j-1)
 *
 * 4 atoms: singlet emission i, monosegment (i+1 to k), nonterminal (k+1,j-1), and singlet emission j.
 */
int
yacc_rule36(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule36");
  
  if (lexeme.l < 7)       /* joint emission */
    natoms = yacc_rule36_3at(R, lexeme, G, verbose);
  else if (lexeme.l == 7) /* independent emissions */
    natoms = yacc_rule36_4at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return natoms;
}
int
yacc_rule36_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;

  strcpy(yr_name, "yacc_rule36_3at");
  R->natoms = 3;

  if (is_base_pair(lexeme.lex[0], lexeme.lex[3])) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;

 /* atom 0: doublet emitter (i,j) */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 2;             /* doublet emitter */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_J;       /* j */
  A->offset[1]              = 0;        
  A->bp[0].basepairtype     = rna_atom_basepairtype(A, G->nt[R->nt_idx].ntname);
  A->bp[0].basepair_coordl_idx = (A->has_basepair)? 0 : -1;
  A->bp[0].basepair_coordr_idx = (A->has_basepair)? 1 : -1;
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */

  /* edist name */
  if      (lexeme.l == 4) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l")) strcpy(A->edist_name[0], "e0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 1: monosegment (i+1 to k) */
  A = &(R->atom[++a]);
  A->atomtype               = MONOSEGMENT_ATOM;
  A->nldists                = 1; 
  A->has_basepair           = FALSE;
  A->ncoords                = 2;            /* monosegment */
  A->coordbase[0]           = COORD_I;      /* i+1 */
  A->offset[0]              = +1;        
  A->coordbase[1]           = COORD_K;      /* k */
  A->offset[1]              = 0;        
  strcpy(A->atom_syntax, lexeme.lex[1]);    /* atom name  */

  /* ldist name */
  if      (lexeme.l == 4) 
    strcpy(A->ldist_name[0], "l0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "l")) strcpy(A->ldist_name[0], lexeme.lex[4]);
    else if (strstr(lexeme.lex[4], "l")) strcpy(A->ldist_name[0], "l0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) { 
    if      (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->ldist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->ldist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

   /* atom 2: nonterminal (k+1,j-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;              /* nonterminal */
  A->coordbase[0]           = COORD_K;        /* k+1 */
  A->offset[0]              = 1;        
  A->coordbase[1]          = COORD_J;        /* j-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 1;             /* context */
  A->maxctxt_basetag[0]     = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[2]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}
int
yacc_rule36_4at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule36_4at");
  R->natoms = 4;

 /* atom 0: singlet emitter i */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 2;             /* pair emitter */
  A->coordbase[0]        = COORD_I;       /* i */
  A->offset[0]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[0]);   /* atom name  */

  /* edist name */
  if      (lexeme.l == 4) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l")) strcpy(A->edist_name[0], "e0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 7) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 1: monosegment (i+1 to k) */
  A = &(R->atom[++a]);
  A->atomtype            = MONOSEGMENT_ATOM;
  A->nldists             = 1; 
  A->has_basepair        = FALSE;
  A->ncoords             = 2;              /* monosegment */
  A->coordbase[0]        = COORD_I;        /* i+1 */
  A->offset[0]           = +1;        
  A->coordbase[1]        = COORD_K;        /* k */
  A->offset[1]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[1]);   /* atom name  */

  /* ldist name */
  if      (lexeme.l == 4) 
    strcpy(A->ldist_name[0], "l0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "l")) strcpy(A->ldist_name[0], lexeme.lex[4]);
    else if (strstr(lexeme.lex[4], "e")) strcpy(A->ldist_name[0], "l0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) { 
    if      (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->ldist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->ldist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 7) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l")) strcpy(A->ldist_name[0], lexeme.lex[6]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e")) strcpy(A->ldist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "e")) strcpy(A->ldist_name[0], lexeme.lex[4]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

   /* atom 2: nonterminal (k+1,j-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;             /* nonterminal */
  A->coordbase[0]        = COORD_K;       /* k+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_J;       /* j-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 1;             /* context */
  A->maxctxt_basetag[0]  = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[2]);  /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

 /* atom 3: singlet emitter j */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 2;             /* pair emitter */
  A->coordbase[0]        = COORD_J;       /* j */
  A->offset[0]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[3]);   /* atom name  */

  /* edist name */
  if      (lexeme.l == 4) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l")) strcpy(A->edist_name[0], "e0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 7) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[6]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[6]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #37 EMISSION NONTERM MONOSEGMENT EMISSION 
 *
 * 3 atoms: double emission i,j, nonterminal (i+1,l-1) and monosegment (l to j-1)
 *
 * 4 atoms: singlet emission i, nonterminal (i+1,l-1), monosegment (l to j-1), and singlet emission j.
 */
int
yacc_rule37(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule37");
  
  if (lexeme.l < 7)       /* joint emission */
    natoms = yacc_rule37_3at(R, lexeme, G, verbose);
  else if (lexeme.l == 7) /* independent emissions */
    natoms = yacc_rule37_4at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return natoms;
}
int
yacc_rule37_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;

  strcpy(yr_name, "yacc_rule37_3at");
  R->natoms = 3;

  if (is_base_pair(lexeme.lex[0], lexeme.lex[3])) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;

 /* atom 0: double emitter (i,j) */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 2;             /* double emitter */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_J;       /* j */
  A->offset[1]              = 0;        
  A->bp[0].basepairtype     = rna_atom_basepairtype(A, G->nt[R->nt_idx].ntname);
  A->bp[0].basepair_coordl_idx = (A->has_basepair)? 0 : -1;
  A->bp[0].basepair_coordr_idx = (A->has_basepair)? 1 : -1;
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */

  /* edist name */
  if      (lexeme.l == 4) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l")) strcpy(A->edist_name[0], "e0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 1: nonterminal (i+1,l-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;              /* nonterminal */
  A->coordbase[0]           = COORD_I;        /* i+1 */
  A->offset[0]              = 1;        
  A->coordbase[1]           = COORD_L;        /* l-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 1;              /* context */
  A->maxctxt_basetag[0]     = -1;             /* -1 tag */
 strcpy(A->atom_syntax, lexeme.lex[1]);       /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 2: monosegment (l to j-1) */
  A = &(R->atom[++a]);
  A->atomtype               = MONOSEGMENT_ATOM;
  A->nldists                = 1; 
  A->has_basepair           = FALSE;
  A->ncoords                = 2;              /* monosegment */
  A->coordbase[0]           = COORD_L;        /* l */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_J;        /* j-1 */
  A->offset[1]              = -1;        
  strcpy(A->atom_syntax, lexeme.lex[2]);    /* atom name  */

  /* ldist name */
  if      (lexeme.l == 4) 
    strcpy(A->ldist_name[0], "l0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "l")) strcpy(A->ldist_name[0], lexeme.lex[4]);
    else if (strstr(lexeme.lex[4], "e")) strcpy(A->ldist_name[0], "l0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) { 
    if      (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->ldist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->ldist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}
int
yacc_rule37_4at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule37_4at");
  R->natoms = 4;

 /* atom 0: singlet emitter i */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 2;             /* singlet  emitter */
  A->coordbase[0]        = COORD_I;       /* i */
  A->offset[0]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[0]);   /* atom name  */

  /* edist name */
  if      (lexeme.l == 4) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l")) strcpy(A->edist_name[0], "e0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 7) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 1: nonterminal (i+1,l-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_I;        /* i+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_L;        /* l-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 1;              /* context */
  A->maxctxt_basetag[0]  = -1;             /* -1 tag */
  strcpy(A->atom_syntax, lexeme.lex[1]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 2: monosegment (l to j-1) */
  A = &(R->atom[++a]);
  A->atomtype            = MONOSEGMENT_ATOM;
  A->nldists             = 1; 
  A->has_basepair        = FALSE;
  A->ncoords             = 2;              /* monosegment */
  A->coordbase[0]        = COORD_L;        /* l */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_J;        /* j-1 */
  A->offset[1]           = -1;        
  strcpy(A->atom_syntax, lexeme.lex[2]); /* atom name  */

  /* ldist name */
  if      (lexeme.l == 4) 
    strcpy(A->ldist_name[0], "l0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "l")) strcpy(A->ldist_name[0], lexeme.lex[4]);
    else if (strstr(lexeme.lex[4], "e")) strcpy(A->ldist_name[0], "l0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) { 
    if      (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->ldist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->ldist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 7) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l")) strcpy(A->ldist_name[0], lexeme.lex[6]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e")) strcpy(A->ldist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "e")) strcpy(A->ldist_name[0], lexeme.lex[4]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

 /* atom 3: singlet emitter j */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 2;             /* singlet  emitter */
  A->coordbase[0]        = COORD_J;       /* j */
  A->offset[0]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[3]);   /* atom name  */

  /* edist name */
  if      (lexeme.l == 4) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l")) strcpy(A->edist_name[0], "e0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 7) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[6]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[6]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #38 EMISSION MONOSEGMENT EMISSION NONTERM 
 *
 * 3 atoms: double emission i,k, monosegment (i+1 to k-1), and nonterminal (k+1,j)
 *
 * 4 atoms: singlet emission i, monosegment (i+1 to k-1), singlet emission k, and nonterminal (k+1,j).
 */
int
yacc_rule38(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule38");
  
  if (lexeme.l < 7)       /* joint emission */
    natoms = yacc_rule38_3at(R, lexeme, G, verbose);
  else if (lexeme.l == 7) /* independent emissions */
    natoms = yacc_rule38_4at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return natoms;
}
int
yacc_rule38_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;

  strcpy(yr_name, "yacc_rule38_3at");
  R->natoms = 3;

  if (is_base_pair(lexeme.lex[0], lexeme.lex[2])) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;

 /* atom 0: doublet emitter (i,k) */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 2;             /* doublet emitter */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_K;       /* k */
  A->offset[1]              = 0;        
  A->bp[0].basepairtype     = rna_atom_basepairtype(A, G->nt[R->nt_idx].ntname);
  A->bp[0].basepair_coordl_idx = (A->has_basepair)? 0 : -1;
  A->bp[0].basepair_coordr_idx = (A->has_basepair)? 1 : -1;
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[2]);    /* atom name  */

  /* edist name */
  if      (lexeme.l == 4) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l")) strcpy(A->edist_name[0], "e0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 1: monosegment (i+1 to k-1) */
  A = &(R->atom[++a]);
  A->atomtype               = MONOSEGMENT_ATOM;
  A->nldists                = 1; 
  A->has_basepair           = FALSE;
  A->ncoords                = 2;              /* monosegment */
  A->coordbase[0]           = COORD_I;        /* i+1 */
  A->offset[0]              = +1;        
  A->coordbase[1]           = COORD_K;        /* k-1 */
  A->offset[1]              = -1;        
  strcpy(A->atom_syntax, lexeme.lex[1]);      /* atom name  */

  /* ldist name */
  if      (lexeme.l == 4) 
    strcpy(A->ldist_name[0], "l0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "l")) strcpy(A->ldist_name[0], lexeme.lex[4]);
    else if (strstr(lexeme.lex[4], "l")) strcpy(A->ldist_name[0], "l0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) { 
    if      (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->ldist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->ldist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

   /* atom 2: nonterminal (k+1,j) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;              /* nonterminal */
  A->coordbase[0]           = COORD_K;        /* k+1 */
  A->offset[0]              = 1;        
  A->coordbase[1]           = COORD_J;        /* j */
  A->offset[1]              = 0;        
  A->max_nctxts             = 1;              /* context */
  A->maxctxt_basetag[0]     = -1;             /* -1 tag */
  strcpy(A->atom_syntax, lexeme.lex[3]);      /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}
int
yacc_rule38_4at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule38_4at");
  R->natoms = 4;

 /* atom 0: singlet emitter i */
  A = &(R->atom[++a]);
  A->atomtype          = EMISSION_ATOM;
  A->has_basepair      = FALSE;
  A->ncoords           = 2;             /* singlet  emitter */
  A->coordbase[0]      = COORD_I;       /* i */
  A->offset[0]         = 0;        
  strcpy(A->atom_syntax, lexeme.lex[0]); /* atom name  */

  /* edist name */
  if      (lexeme.l == 4) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l")) strcpy(A->edist_name[0], "e0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 7) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 1: monosegment (i+1 to k-1) */
  A = &(R->atom[++a]);
  A->atomtype            = MONOSEGMENT_ATOM;
  A->nldists             = 1; 
  A->has_basepair        = FALSE;
  A->ncoords             = 2;              /* monosegment */
  A->coordbase[0]        = COORD_I;        /* i+1 */
  A->offset[0]           = +1;        
  A->coordbase[1]        = COORD_K;        /* k-1 */
  A->offset[1]           = -1;        
  strcpy(A->atom_syntax, lexeme.lex[1]);   /* atom name  */

  /* ldist name */
  if      (lexeme.l == 4) 
    strcpy(A->ldist_name[0], "l0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "l")) strcpy(A->ldist_name[0], lexeme.lex[4]);
    else if (strstr(lexeme.lex[4], "e")) strcpy(A->ldist_name[0], "l0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) { 
    if      (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->ldist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->ldist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 7) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l")) strcpy(A->ldist_name[0], lexeme.lex[6]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e")) strcpy(A->ldist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "e")) strcpy(A->ldist_name[0], lexeme.lex[4]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

 /* atom 2: singlet emitter k */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 2;             /* singlet  emitter */
  A->coordbase[0]        = COORD_K;       /* k */
  A->offset[0]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[2]);   /* atom name  */

  /* edist name */
  if      (lexeme.l == 4) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l")) strcpy(A->edist_name[0], "e0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 7) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[6]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[6]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

   /* atom 3: nonterminal (k+1,j) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->max_nctxts          = 0;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_K;        /* k+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_J;        /* j */
  A->offset[1]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[3]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);


  return a+1;
}

/* YACC RULE #39 NONTERM EMISSION MONOSEGMENT EMISSION 
 *
 * 3 atoms: nonterminal (i,l-1), doublet emission l,j, and monosegment (l+1 to j-1)
 *
 * 4 atoms: nonterminal (i,l-1), singlet emission l, monosegment (l+1 to j-1), and singlet emission j.
 */
int
yacc_rule39(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule39");
  
  if (lexeme.l < 7)       /* joint emission */
    natoms = yacc_rule39_3at(R, lexeme, G, verbose); 
  else if (lexeme.l == 7) /* independent emissions */
    natoms = yacc_rule39_4at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return natoms;
}
int
yacc_rule39_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;

  strcpy(yr_name, "yacc_rule39_3at");
  R->natoms = 3;

  if (is_base_pair(lexeme.lex[1], lexeme.lex[3])) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;

   /* atom 0: nonterminal (i,l-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;              /* nonterminal */
  A->coordbase[0]           = COORD_I;        /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_L;        /* l-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 1;              /* context */
  A->maxctxt_basetag[0]     = +1;             /* +1 tag */
 strcpy(A->atom_syntax, lexeme.lex[0]);       /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

 /* atom 1: doublet emitter (l,j) */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 2;             /* doublet emitter */
  A->coordbase[0]           = COORD_L;       /* l */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_J;       /* j */
  A->offset[1]              = 0;        
  A->bp[0].basepairtype     = rna_atom_basepairtype(A, G->nt[R->nt_idx].ntname);
  A->bp[0].basepair_coordl_idx = (A->has_basepair)? 0 : -1;
  A->bp[0].basepair_coordr_idx = (A->has_basepair)? 1 : -1;
  strcpy(A->atom_syntax, lexeme.lex[1]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */

  /* edist name */
  if      (lexeme.l == 4) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l")) strcpy(A->edist_name[0], "e0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 2: monosegment (l+1 to j-1) */
  A = &(R->atom[++a]);
  A->atomtype               = MONOSEGMENT_ATOM;
  A->nldists                = 1; 
  A->has_basepair           = FALSE;
  A->ncoords                = 2;              /* monosegment */
  A->coordbase[0]           = COORD_L;        /* l+1 */
  A->offset[0]              = +1;        
  A->coordbase[1]           = COORD_J;        /* j-1 */
  A->offset[1]              = -1;        
  strcpy(A->atom_syntax, lexeme.lex[2]);      /* atom name  */

  /* ldist name */
  if      (lexeme.l == 4) 
    strcpy(A->ldist_name[0], "l0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "l")) strcpy(A->ldist_name[0], lexeme.lex[4]);
    else if (strstr(lexeme.lex[4], "e")) strcpy(A->ldist_name[0], "l0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) { 
    if      (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->ldist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->ldist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}
int
yacc_rule39_4at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule39_4at");
  R->natoms = 4;

  /* atom 0: nonterminal (i,l-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_I;        /* i */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_L;        /* l-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 1;              /* context */
  A->maxctxt_basetag[0]  = +1;             /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[0]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

 /* atom 1: singlet emitter l */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 2;             /* singlet emitter */
  A->coordbase[0]        = COORD_L;       /* l */
  A->offset[0]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[1]);   /* atom name  */

  /* edist name */
  if      (lexeme.l == 4) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l")) strcpy(A->edist_name[0], "e0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 7) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 2: monosegment (l+1 to j-1) */
  A = &(R->atom[++a]);
  A->atomtype            = MONOSEGMENT_ATOM;
  A->nldists             = 1; 
  A->has_basepair        = FALSE;
  A->ncoords             = 2;              /* monosegment */
  A->coordbase[0]        = COORD_L;        /* l+1 */
  A->offset[0]           = +1;        
  A->coordbase[1]        = COORD_J;        /* j-1 */
  A->offset[1]           = -1;        
  strcpy(A->atom_syntax, lexeme.lex[2]);   /* atom name  */

  /* ldist name */
  if      (lexeme.l == 4) 
    strcpy(A->ldist_name[0], "l0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "l")) strcpy(A->ldist_name[0], lexeme.lex[4]);
    else if (strstr(lexeme.lex[4], "e")) strcpy(A->ldist_name[0], "l0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) { 
    if      (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->ldist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->ldist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 7) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l")) strcpy(A->ldist_name[0], lexeme.lex[6]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e")) strcpy(A->ldist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "e")) strcpy(A->ldist_name[0], lexeme.lex[4]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

 /* atom 3: singlet emitter j */
  A = &(R->atom[++a]);
  A->atomtype          = EMISSION_ATOM;
  A->has_basepair      = FALSE;
  A->ncoords           = 2;             /* singlet emitter */
  A->coordbase[0]      = COORD_J;       /* j */
  A->offset[0]         = 0;        
  strcpy(A->atom_syntax, lexeme.lex[3]); /* atom name  */

  /* edist name */
  if      (lexeme.l == 4) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 5) {
    if      (strstr(lexeme.lex[4], "e")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l")) strcpy(A->edist_name[0], "e0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l")) strcpy(A->edist_name[0], lexeme.lex[4]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 7) {
    if      (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[4], "e") && strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[6]); 
    else if (strstr(lexeme.lex[4], "l") && strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[6]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #40 EMISSION LDISEGMENT NONTERM RDISEGMENT EMISSION 
 *
 * 3 atoms:  double emission i,j, disegment (i+1 to k) + (l to j-1),  and nonterminal (k+1,l-1) 
 *
 * 4 atoms:  singlet emission i, disegment (i+1 to k) + (l to j-1), nonterminal (k+1,l-1), and singlet emission j
 */
int
yacc_rule40(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule40");
  
  if (lexeme.l < 8)       /* joint emission */
    natoms = yacc_rule40_3at(R, lexeme, G, verbose);
  else if (lexeme.l == 8) /* independent emissions */
    natoms = yacc_rule40_4at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return natoms;
}
int
yacc_rule40_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;

  strcpy(yr_name, "yacc_rule40_3at");
  R->natoms = 3;

  if (is_base_pair(lexeme.lex[0], lexeme.lex[4])) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;

   /* atom 0: doublet emitter (i,j) */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 2;             /* doublet emitter */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_J;       /* j */
  A->offset[1]              = 0;        
  A->bp[0].basepairtype     = rna_atom_basepairtype(A, G->nt[R->nt_idx].ntname);
  A->bp[0].basepair_coordl_idx = (A->has_basepair)? 0 : -1;
  A->bp[0].basepair_coordr_idx = (A->has_basepair)? 1 : -1;
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[4]);    /* atom name  */

  /* edist name */
  if      (lexeme.l == 5) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]);
    else if (strstr(lexeme.lex[5], "l")) strcpy(A->edist_name[0], "e0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 7) {
    if      (strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[6]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 1: disegment (i+1 to k)+(l to j-1) */
  A = &(R->atom[++a]);
  A->atomtype               = DISEGMENT_ATOM;
  A->nldists                = 1; 
  A->has_basepair           = FALSE;
  A->ncoords                = 4;              /* disegment */
  A->coordbase[0]           = COORD_I;        /* i+1 */
  A->offset[0]              = +1;        
  A->coordbase[1]           = COORD_K;        /* k */
  A->offset[1]              = 0;        
  A->coordbase[2]           = COORD_L;        /* l */
  A->offset[2]              = 0;        
  A->coordbase[3]           = COORD_J;        /* j-1 */
  A->offset[3]              = -1;        
  A->nedists                = 0;
  A->ncontexts              = 0;
  strcpy(A->atom_syntax, lexeme.lex[1]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */

  /* ldist name */
  if      (lexeme.l == 5) 
    strcpy(A->ldist_name[0], "l0"); 
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[5], "l")) strcpy(A->ldist_name[0], lexeme.lex[5]);
    else if (strstr(lexeme.lex[5], "e")) strcpy(A->ldist_name[0], "l0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 7) {
    if      (strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l")) strcpy(A->ldist_name[0], lexeme.lex[6]); 
    else if (strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e")) strcpy(A->ldist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+1,l-1) */
  A = &(R->atom[++a]);   
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;              /* nonterminal */
  A->coordbase[0]           = COORD_K;        /* k + 1 */
  A->offset[0]              = +1;        
  A->coordbase[1]           = COORD_L;        /* l - 1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 0;              /* context */
  strcpy(A->atom_syntax, lexeme.lex[2]);      /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}
int
yacc_rule40_4at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */

  strcpy(yr_name, "yacc_rule40_4at");
  R->natoms = 4;

  /* atom 0: singlet emitter i */
  A = &(R->atom[++a]);
  A->atomtype          = EMISSION_ATOM;
  A->has_basepair      = FALSE;
  A->ncoords           = 1;             /* singlet emitter */
  A->coordbase[0]      = COORD_I;       /* i */
  A->offset[0]         = 0;        
  strcpy(A->atom_syntax, lexeme.lex[0]); /* atom name  */

  /* edist name */
  if      (lexeme.l == 5) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]);
    else if (strstr(lexeme.lex[5], "l")) strcpy(A->edist_name[0], "e0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 7) {
    if      (strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[6]); 
    else if (strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 8) {
    if      (strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "e") && strstr(lexeme.lex[7], "l")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l") && strstr(lexeme.lex[7], "e")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e") && strstr(lexeme.lex[7], "e")) strcpy(A->edist_name[0], lexeme.lex[6]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 1: disegment (i+1 to k)+(l to j-1) */
  A = &(R->atom[++a]);
  A->atomtype            = DISEGMENT_ATOM;
  A->nldists             = 1; 
  A->has_basepair        = FALSE;
  A->ncoords             = 4;            /* disegment */
  A->coordbase[0]        = COORD_I;      /* i+1 */
  A->offset[0]           = +1;        
  A->coordbase[1]        = COORD_K;      /* k */
  A->offset[1]           = 0;        
  A->coordbase[2]        = COORD_L;      /* l */
  A->offset[2]           = 0;        
  A->coordbase[3]        = COORD_J;      /* j-1 */
  A->offset[3]           = -1;        
  A->nedists             = 0;
  A->ncontexts           = 0;
  strcpy(A->atom_syntax, lexeme.lex[1]); /* atom name  */
  strcat(A->atom_syntax, "^");           /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]); /* atom name  */

  /* ldist name */
  if      (lexeme.l == 5) 
    strcpy(A->ldist_name[0], "l0"); 
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[5], "l")) strcpy(A->ldist_name[0], lexeme.lex[5]);
    else if (strstr(lexeme.lex[5], "e")) strcpy(A->ldist_name[0], "l0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 7) {
    if      (strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l")) strcpy(A->ldist_name[0], lexeme.lex[6]); 
    else if (strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e")) strcpy(A->ldist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "e")) strcpy(A->ldist_name[0], "l0");
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 8) {
    if      (strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "e") && strstr(lexeme.lex[7], "l")) strcpy(A->ldist_name[0], lexeme.lex[7]); 
    else if (strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l") && strstr(lexeme.lex[7], "e")) strcpy(A->ldist_name[0], lexeme.lex[6]); 
    else if (strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e") && strstr(lexeme.lex[7], "e")) strcpy(A->ldist_name[0], lexeme.lex[5]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+1,l-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;              /* nonterminal */
  A->coordbase[0]        = COORD_K;        /* k + 1 */
  A->offset[0]           = +1;        
  A->coordbase[1]        = COORD_L;        /* l - 1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 0;              /* context */
  strcpy(A->atom_syntax, lexeme.lex[2]);   /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  /* atom 3: singlet emitter j */
  A = &(R->atom[++a]);
  A->atomtype            = EMISSION_ATOM;
  A->has_basepair        = FALSE;
  A->ncoords             = 1;             /* singlet emitter */
  A->coordbase[0]        = COORD_J;       /* j */
  A->offset[0]           = 0;        
  strcpy(A->atom_syntax, lexeme.lex[4]);  /* atom name  */

  /* edist name */
  if      (lexeme.l == 5) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 6) {
    if      (strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]);
    else if (strstr(lexeme.lex[5], "l")) strcpy(A->edist_name[0], "e0"); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 7) {
    if      (strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l")) strcpy(A->edist_name[0], lexeme.lex[5]); 
    else if (strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[6]); 
    else if (strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[6]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (lexeme.l == 8) {
    if      (strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "e") && strstr(lexeme.lex[7], "l")) strcpy(A->edist_name[0], lexeme.lex[6]); 
    else if (strstr(lexeme.lex[5], "e") && strstr(lexeme.lex[6], "l") && strstr(lexeme.lex[7], "e")) strcpy(A->edist_name[0], lexeme.lex[7]); 
    else if (strstr(lexeme.lex[5], "l") && strstr(lexeme.lex[6], "e") && strstr(lexeme.lex[7], "e")) strcpy(A->edist_name[0], lexeme.lex[7]); 
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);


  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #41 EMISSION EMISSION NONTERM EMISSION NONTERM 
 *
 * 3 atoms, triplet emission i,i+1,k, nonterminal (i+2,k-1), nonterminal (k+1,j)
 *
 */
int
yacc_rule41(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule41");
  
  if (lexeme.l < 7)       /* joint emission */
    natoms = yacc_rule41_3at(R, lexeme, G, verbose);
  else 
    grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);
    
  return natoms;
}
int
yacc_rule41_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;
  int   notallowed = FALSE;

  if (is_base_pair(lexeme.lex[0], lexeme.lex[1])) notallowed = TRUE; /* a  a' S c  P  */

  if (is_base_pair(lexeme.lex[0], lexeme.lex[3]) || /* a  b  S a' P  */
      is_base_pair(lexeme.lex[1], lexeme.lex[3]))   /* b  a  S a' P  */
    nbasepairs = 1;
  else 
    nbasepairs = 0;

  strcpy(yr_name, "yacc_rule41_3at");
  R->natoms = 3;

  /* atom 0: three-way emitter i,i+1,k */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 3;             /* three-way emitter */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_I;       /* i+1 */
  A->offset[1]              = +1;        
  A->coordbase[2]           = COORD_K;       /* k */
  A->offset[2]              = 0; 
  if      (is_base_pair(lexeme.lex[0], lexeme.lex[3])) { /* a  b  S a' P  */
    A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
    A->bp[0].basepair_coordl_idx = 0;
    A->bp[0].basepair_coordr_idx = 2;
  }
  else if (is_base_pair(lexeme.lex[1], lexeme.lex[3])) { /* b  a  S a' P  */
    A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
    A->bp[0].basepair_coordl_idx = 1;
    A->bp[0].basepair_coordr_idx = 2;
  }
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[1]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */

 /* edist name */
  if      (lexeme.l == 5) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 6) { 
    if (strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]);
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+2,k-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;             /* nonterminal */
  A->coordbase[0]        = COORD_I;       /* i+2 */
  A->offset[0]           = +2;        
  A->coordbase[1]        = COORD_K;       /* k-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 3;             /* context */
  A->maxctxt_basetag[0]  = -2;            /* -2 tag */
  A->maxctxt_basetag[1]  = -1;            /* -1 tag */
  A->maxctxt_basetag[2]  = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[2]);  /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+1,j) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;             /* nonterminal */
  A->coordbase[0]        = COORD_K;       /* k+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_J;       /* j */
  A->offset[1]           = 0;        
  A->max_nctxts          = 1;             /* context */
  A->maxctxt_basetag[0]  = -1;            /* -1 tag */
  strcpy(A->atom_syntax, lexeme.lex[4]);  /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return a+1;
}

/* YACC RULE #42 NONTERM EMISSION NONTERM EMISSION EMISSION
 *
 * 3 atoms, nonterminal (i,k-1), triplet emission k,j-1,j, and nonterminal (k+1,j-2)
 *
 */
int
yacc_rule42(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule42");
  
  if (lexeme.l < 7)       /* joint emission */
    natoms = yacc_rule42_3at(R, lexeme, G, verbose);
  else 
    grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);
    
  return natoms;
}
int
yacc_rule42_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;
  int   notallowed = FALSE;

  if (is_base_pair(lexeme.lex[3], lexeme.lex[4])) notallowed = TRUE; /* S a  P b b' */

  if (is_base_pair(lexeme.lex[1], lexeme.lex[3]) || /* S a  P a' b */
      is_base_pair(lexeme.lex[1], lexeme.lex[4]) )  /* S a  P b  a' */
    nbasepairs = 1;
  else 
    nbasepairs = 0;

  strcpy(yr_name, "yacc_rule42_3at");
  R->natoms = 3;

  /* atom 0: nonterminal (i,k-1) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;             /* nonterminal */
  A->coordbase[0]        = COORD_I;       /* i */
  A->offset[0]           = 0;        
  A->coordbase[1]        = COORD_K;       /* k-1 */
  A->offset[1]           = -1;        
  A->max_nctxts          = 1;             /* context */
  A->maxctxt_basetag[0]  = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[0]);  /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: three-way emitter k,j-1,j */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 3;             /* three-way emitter */
  A->coordbase[0]           = COORD_K;       /* k */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_J;       /* j-1 */
  A->offset[1]              = -1;        
  A->coordbase[2]           = COORD_J;       /* j */
  A->offset[2]              = 0; 
  if      (is_base_pair(lexeme.lex[1], lexeme.lex[3])) { /* S a  P a' b */
    A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
    A->bp[0].basepair_coordl_idx = 0;
    A->bp[0].basepair_coordr_idx = 1;
  }
  else if (is_base_pair(lexeme.lex[1], lexeme.lex[4])) { /* S a  P b  a' */
    A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
    A->bp[0].basepair_coordl_idx = 0;
    A->bp[0].basepair_coordr_idx = 2;
  }
  strcpy(A->atom_syntax, lexeme.lex[1]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[4]);    /* atom name  */

 /* edist name */
  if      (lexeme.l == 5) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 6) { 
    if (strstr(lexeme.lex[5], "e")) strcpy(A->edist_name[0], lexeme.lex[5]);
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+1,j-2) */
  A = &(R->atom[++a]);
  A->atomtype            = NONTERMINAL_ATOM;
  A->ncoords             = 2;             /* nonterminal */
  A->coordbase[0]        = COORD_K;       /* k+1 */
  A->offset[0]           = 1;        
  A->coordbase[1]        = COORD_J;       /* j-2 */
  A->offset[1]           = -2;        
  A->max_nctxts          = 3;             /* context */
  A->maxctxt_basetag[0]  = -1;            /* -1 tag */
  A->maxctxt_basetag[1]  = +1;            /* +1 tag */
  A->maxctxt_basetag[2]  = +2;            /* +2 tag */
  strcpy(A->atom_syntax, lexeme.lex[2]);  /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return a+1;
}

/* YACC RULE #43 EMISSION EMISSION NONTERM EMISSION NONTERM EMISSION
 *
 * 3 atoms, four-way emission i,i+1,k,j, nonterminal (i+2,k-1), and nonterminal (k+1,j-1)
 *
 */
int
yacc_rule43(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule43");
  
  if (lexeme.l < 8)       /* joint emission */
    natoms = yacc_rule43_3at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return natoms;
}
int
yacc_rule43_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;
  int   notallowed = FALSE;

  if (is_base_pair(lexeme.lex[0], lexeme.lex[1])) notallowed = TRUE; /* a a' S c P f */

  if (is_base_pair(lexeme.lex[0], lexeme.lex[3]) || /* a  b  S a' P f  */ 
      is_base_pair(lexeme.lex[1], lexeme.lex[3]) || /* b  a  S a' P f  */ 
      is_base_pair(lexeme.lex[3], lexeme.lex[5]) || /* a  b  S c  P c' */ 
      is_base_pair(lexeme.lex[0], lexeme.lex[5])    /* a  b  S c  P a' */
      ) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;
  
  strcpy(yr_name, "yacc_rule43_3at");
  R->natoms = 3;

  /* atom 0: four-way emitter i,i+1,k,j */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 4;             /* four-way emitter */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_I;       /* i+1 */
  A->offset[1]              = +1;        
  A->coordbase[2]           = COORD_K;       /* k */
  A->offset[2]              = 0; 
  A->coordbase[3]           = COORD_J;       /* j */
  A->offset[3]              = 0; 

  if (nbasepairs == 1) {
    
    /* a  b  S a' P f  */ 
    if      (is_base_pair(lexeme.lex[0], lexeme.lex[3])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 2;     
    }
    
    /* b  a  S a' P f  */ 
    else if (is_base_pair(lexeme.lex[1], lexeme.lex[3])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 1;
      A->bp[0].basepair_coordr_idx = 2;     
    }
    
    /* a  b  S c  P c' */
    else if (is_base_pair(lexeme.lex[3], lexeme.lex[5])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[4]);
      A->bp[0].basepair_coordl_idx = 2;
      A->bp[0].basepair_coordr_idx = 3;     
    }
    
    /* a  b  S c  P a' */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[5])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, G->nt[R->nt_idx].ntname);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 3;     
    }

    else 
      grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[1]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[5]);    /* atom name  */

 /* edist name */
  if      (lexeme.l == 6) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 7) { 
    if (strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[6]);
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+2,k-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_I;       /* i+2 */
  A->offset[0]              = +2;        
  A->coordbase[1]           = COORD_K;       /* k-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 3;             /* context */
  A->maxctxt_basetag[0]     = -2;            /* -2 tag */
  A->maxctxt_basetag[1]     = -1;            /* -1 tag */
  A->maxctxt_basetag[2]     = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[2]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+1,j-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_K;       /* k+1 */
  A->offset[0]              = +1;        
  A->coordbase[1]           = COORD_J;       /* j-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 2;             /* context */
  A->maxctxt_basetag[0]     = -1;            /* -1 tag */
  A->maxctxt_basetag[1]     = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[4]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #44 EMISSION NONTERM EMISSION NONTERM EMISSION EMISSION 
 *
 * 3 atoms, four-way emission i,k,j-1,j, nonterminal (i+1,k-1), and nonterminal (k+1,j-2)
 *
 */
int
yacc_rule44(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule44");
  
  if (lexeme.l < 8)       /* joint emission */
    natoms = yacc_rule44_3at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return natoms;
}
int
yacc_rule44_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;
  int   notallowed = FALSE;

  if (is_base_pair(lexeme.lex[4], lexeme.lex[5])) notallowed = TRUE; /* a S b P c c' */
  
  if (is_base_pair(lexeme.lex[0], lexeme.lex[2]) || /* a S a' P b  c  */
      is_base_pair(lexeme.lex[2], lexeme.lex[4]) || /* a S b  P b' c  */
      is_base_pair(lexeme.lex[2], lexeme.lex[5]) || /* a S b  P c  b' */
      is_base_pair(lexeme.lex[0], lexeme.lex[5])    /* a S b  P c  a' */
      ) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;
  
  strcpy(yr_name, "yacc_rule44_3at");
  R->natoms = 3;

  /* atom 0: four-way emitter i,k,j-1,j */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 4;             /* four-way emitter */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_K;       /* k */
  A->offset[1]              = 0;        
  A->coordbase[2]           = COORD_J;       /* j-1 */
  A->offset[2]              = -1; 
  A->coordbase[3]           = COORD_J;       /* j */
  A->offset[3]              = 0; 

  if (nbasepairs == 1) {
    
    /* a S a' P b  c  */
    if      (is_base_pair(lexeme.lex[0], lexeme.lex[2])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[1]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 1;     
    }

    /* a S b  P b' c  */
    else if (is_base_pair(lexeme.lex[2], lexeme.lex[4])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[3]);
      A->bp[0].basepair_coordl_idx = 1;
      A->bp[0].basepair_coordr_idx = 2;     
    }

    /* a S b  P c  b' */
    else if (is_base_pair(lexeme.lex[2], lexeme.lex[5])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[3]);
      A->bp[0].basepair_coordl_idx = 1;
      A->bp[0].basepair_coordr_idx = 3;     
    }

    /* a S b  P c  a' */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[5])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, G->nt[R->nt_idx].ntname);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 3;     
    }

    else 
      grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[2]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[4]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[5]);    /* atom name  */

 /* edist name */
  if      (lexeme.l == 6) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 7) { 
    if (strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[6]);
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+1,k-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_I;       /* i+1 */
  A->offset[0]              = +1;        
  A->coordbase[1]           = COORD_K;       /* k-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 2;             /* context */
  A->maxctxt_basetag[0]     = -1;            /* -1 tag */
  A->maxctxt_basetag[1]     = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[1]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+1,j-2) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_K;       /* k+1 */
  A->offset[0]              = +1;        
  A->coordbase[1]           = COORD_J;       /* j-2 */
  A->offset[1]              = -2;        
  A->max_nctxts             = 3;             /* context */
  A->maxctxt_basetag[0]     = -1;            /* -1 tag */
  A->maxctxt_basetag[1]     = +1;            /* +1 tag */
  A->maxctxt_basetag[2]     = +2;            /* +2 tag */
  strcpy(A->atom_syntax, lexeme.lex[3]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #45 EMISSION EMISSION NONTERM EMISSION EMISSION NONTERM 
 *
 * 3 atoms, four-way emission i,i+1,k,k+1, nonterminal (i+2,k-1), and nonterminal (k+2,j)
 *
 */
int
yacc_rule45(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule45");
  
  if (lexeme.l < 8)       /* joint emission */
    natoms = yacc_rule45_3at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return natoms;
}
int
yacc_rule45_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;
  int   notallowed = FALSE;

  if (is_base_pair(lexeme.lex[0], lexeme.lex[1])) notallowed = TRUE; /* a a' S b c  P */
  if (is_base_pair(lexeme.lex[3], lexeme.lex[4])) notallowed = TRUE; /* a b  S c c' P */
  
  if      ((is_base_pair(lexeme.lex[0], lexeme.lex[4]) && is_base_pair(lexeme.lex[1], lexeme.lex[3])) || /* a b S b' a' P */
	   (is_base_pair(lexeme.lex[0], lexeme.lex[3]) && is_base_pair(lexeme.lex[1], lexeme.lex[4]))    /* a b S a' b' P (pknot) */
	   ) 
    nbasepairs = 2;
  else if (is_base_pair(lexeme.lex[0], lexeme.lex[3]) || /* a b S a' c  P */
	   is_base_pair(lexeme.lex[0], lexeme.lex[4]) || /* a b S c  a' P */
 	   is_base_pair(lexeme.lex[1], lexeme.lex[3]) || /* a b S b' c  P */
	   is_base_pair(lexeme.lex[1], lexeme.lex[4])    /* a b S c  b' P */
	   ) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;
  
  strcpy(yr_name, "yacc_rule45_3at");
  R->natoms = 3;

  /* atom 0: four-way emitter i,i+1,k,k+1 */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 4;             /* four-way emitter */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_I;       /* i+1 */
  A->offset[1]              = +1;        
  A->coordbase[2]           = COORD_K;       /* k */
  A->offset[2]              = 0; 
  A->coordbase[3]           = COORD_K;       /* k+1 */
  A->offset[3]              = +1; 

  if (nbasepairs == 2) {
    
    /* a b S b' a' P */
    if      (is_base_pair(lexeme.lex[0], lexeme.lex[4]) && is_base_pair(lexeme.lex[1], lexeme.lex[3])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 3;     
      A->bp[1].basepair_coordl_idx = 1;
      A->bp[1].basepair_coordr_idx = 2;     
    }
    
    /* a b S a' b' P (pknot) */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[3]) && is_base_pair(lexeme.lex[1], lexeme.lex[4])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 2;     
      A->bp[1].basepair_coordl_idx = 1;
      A->bp[1].basepair_coordr_idx = 3;     
    }
    
    else 
      grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (nbasepairs == 1) {
    
    /* a b S a' c  P */ 
    if      (is_base_pair(lexeme.lex[0], lexeme.lex[3])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 2;     
    }
    
    /* a b S c  a' P */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[4])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 3;     
    }
    
    /* a b S b' c  P */
    else if (is_base_pair(lexeme.lex[1], lexeme.lex[3])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 1;
      A->bp[0].basepair_coordr_idx = 2;     
    }

    /* a b S c  b' P */
    else if (is_base_pair(lexeme.lex[1], lexeme.lex[4])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 1;
      A->bp[0].basepair_coordr_idx = 3;     
    }  
    
    else 
      grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[1]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[4]);    /* atom name  */

 /* edist name */
  if      (lexeme.l == 6) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 7) { 
    if (strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[6]);
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+2,k-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_I;       /* i+2 */
  A->offset[0]              = +2;        
  A->coordbase[1]           = COORD_K;       /* k-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 4;             /* context */
  A->maxctxt_basetag[0]     = -2;            /* -2 tag */
  A->maxctxt_basetag[1]     = -1;            /* -1 tag */
  A->maxctxt_basetag[2]     = +1;            /* +1 tag */
  A->maxctxt_basetag[3]     = +2;            /* +2 tag */
  strcpy(A->atom_syntax, lexeme.lex[2]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+2,j) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_K;       /* k+2 */
  A->offset[0]              = +2;        
  A->coordbase[1]           = COORD_J;       /* j */
  A->offset[1]              = 0;        
  A->max_nctxts             = 2;             /* context */
  A->maxctxt_basetag[0]     = -2;            /* -2 tag */
  A->maxctxt_basetag[1]     = -1;            /* -1 tag */
  strcpy(A->atom_syntax, lexeme.lex[5]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #46 NONTERM EMISSION EMISSION NONTERM EMISSION EMISSION 
 *
 * 3 atoms, nonterminal (i,k-1), four-way emission k,k+1,j-1,j, and nonterminal (k+2,j-2)
 *
 */
int
yacc_rule46(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule46");
  
  if (lexeme.l < 8)       /* joint emission */
    natoms = yacc_rule46_3at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return natoms;
}
int
yacc_rule46_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;
  int   notallowed = FALSE;

  if (is_base_pair(lexeme.lex[1], lexeme.lex[2])) notallowed = TRUE; /* S a a' P b c  */
  if (is_base_pair(lexeme.lex[4], lexeme.lex[5])) notallowed = TRUE; /* S a b  P c c' */
  
  if      ((is_base_pair(lexeme.lex[1], lexeme.lex[5]) && is_base_pair(lexeme.lex[2], lexeme.lex[4])) || /* S a b P b' a' */
	   (is_base_pair(lexeme.lex[1], lexeme.lex[4]) && is_base_pair(lexeme.lex[2], lexeme.lex[5]))    /* S a b P a' b' (pknot) */
	   ) 
    nbasepairs = 2;
  else if (is_base_pair(lexeme.lex[1], lexeme.lex[4]) || /* S a b P a' c  */
	   is_base_pair(lexeme.lex[1], lexeme.lex[5]) || /* S a b P c  a' */
 	   is_base_pair(lexeme.lex[2], lexeme.lex[4]) || /* S a b P b' c  */
	   is_base_pair(lexeme.lex[2], lexeme.lex[5])    /* S a b P c  b' */
	   ) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;
  
  strcpy(yr_name, "yacc_rule46_3at");
  R->natoms = 3;

  /* atom 0: nonterminal (i,k-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_K;       /* k-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 2;             /* context */
  A->maxctxt_basetag[0]     = +1;            /* +1 tag */
  A->maxctxt_basetag[1]     = +2;            /* +2 tag */
  strcpy(A->atom_syntax, lexeme.lex[0]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: four-way emitter k,k+1,j-1,j */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 4;             /* four-way emitter */
  A->coordbase[0]           = COORD_K;       /* k */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_K;       /* k+1 */
  A->offset[1]              = +1;        
  A->coordbase[2]           = COORD_J;       /* j-1 */
  A->offset[2]              = -1; 
  A->coordbase[3]           = COORD_J;       /* j */
  A->offset[3]              = 0; 

  if (nbasepairs == 2) {
    
    /* S a b P b' a' */
    if      (is_base_pair(lexeme.lex[1], lexeme.lex[5]) && is_base_pair(lexeme.lex[2], lexeme.lex[4])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[3]);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[3]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 3;     
      A->bp[1].basepair_coordl_idx = 1;
      A->bp[1].basepair_coordr_idx = 2;     
    }
    
    /* S a b P a' b' (pknot) */
    else if (is_base_pair(lexeme.lex[1], lexeme.lex[4]) && is_base_pair(lexeme.lex[2], lexeme.lex[5])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[3]);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[3]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 2;     
      A->bp[1].basepair_coordl_idx = 1;
      A->bp[1].basepair_coordr_idx = 3;     
    }
    
    else 
      grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (nbasepairs == 1) {
    
    /* S a b P a' c  */ 
    if      (is_base_pair(lexeme.lex[1], lexeme.lex[4])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 2;     
    }
    
    /* S a b P c  a' */
    else if (is_base_pair(lexeme.lex[1], lexeme.lex[5])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 3;     
    }
    
    /* S a b P b' c  */
    else if (is_base_pair(lexeme.lex[2], lexeme.lex[4])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 1;
      A->bp[0].basepair_coordr_idx = 2;     
    }

    /* S a b P c  b' */
    else if (is_base_pair(lexeme.lex[2], lexeme.lex[5])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 1;
      A->bp[0].basepair_coordr_idx = 3;     
    }  
    
    else 
      grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  
  strcpy(A->atom_syntax, lexeme.lex[1]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[2]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[4]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[5]);    /* atom name  */

 /* edist name */
  if      (lexeme.l == 6) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 7) { 
    if (strstr(lexeme.lex[6], "e")) strcpy(A->edist_name[0], lexeme.lex[6]);
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+2,j-2) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_K;       /* k+2 */
  A->offset[0]              = +2;        
  A->coordbase[1]           = COORD_J;       /* j-2 */
  A->offset[1]              = -2;        
  A->max_nctxts             = 4;             /* context */
  A->maxctxt_basetag[0]     = -2;            /* -2 tag */
  A->maxctxt_basetag[1]     = -1;            /* -1 tag */
  A->maxctxt_basetag[2]     = +1;            /* +1 tag */
  A->maxctxt_basetag[3]     = +2;            /* +2 tag */
  strcpy(A->atom_syntax, lexeme.lex[3]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #47 EMISSION EMISSION NONTERM EMISSION EMISSION NONTERM EMISSION
 *
 * 3 atoms, five-way emission i,i+1,k,k+1,j, nonterminal (i+2,k-1), and nonterminal (k+2,j-1)
 *
 */
int
yacc_rule47(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule47");
  
  if (lexeme.l < 9)       /* joint emission */
    natoms = yacc_rule47_3at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return natoms;
}
int
yacc_rule47_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;
  int   notallowed = FALSE;

  if (is_base_pair(lexeme.lex[0], lexeme.lex[1])) notallowed = TRUE; /* a a' S c f  P e */
  if (is_base_pair(lexeme.lex[3], lexeme.lex[4])) notallowed = TRUE; /* a b  S c c' P e */

  if ( (is_base_pair(lexeme.lex[0], lexeme.lex[4]) && is_base_pair(lexeme.lex[1], lexeme.lex[3])) || /* a b S b' a' P c  */
       (is_base_pair(lexeme.lex[0], lexeme.lex[3]) && is_base_pair(lexeme.lex[1], lexeme.lex[4])) || /* a b S a' b' P c  (pknot) */
       (is_base_pair(lexeme.lex[0], lexeme.lex[3]) && is_base_pair(lexeme.lex[4], lexeme.lex[6])) || /* a b S a' c  P c'  */
       (is_base_pair(lexeme.lex[0], lexeme.lex[4]) && is_base_pair(lexeme.lex[3], lexeme.lex[6])) || /* a b S c  a' P c'  (pknot) */
       (is_base_pair(lexeme.lex[1], lexeme.lex[3]) && is_base_pair(lexeme.lex[4], lexeme.lex[6])) || /* b a S a' c  P c' */
       (is_base_pair(lexeme.lex[1], lexeme.lex[4]) && is_base_pair(lexeme.lex[3], lexeme.lex[6])) || /* b a S c  a' P c' (pknot) */
       (is_base_pair(lexeme.lex[0], lexeme.lex[6]) && is_base_pair(lexeme.lex[1], lexeme.lex[3])) || /* a b S b' c  P a' */
       (is_base_pair(lexeme.lex[0], lexeme.lex[6]) && is_base_pair(lexeme.lex[1], lexeme.lex[4]))    /* a b S c  b' P a' */
       ) 
    nbasepairs = 2;
  else if (is_base_pair(lexeme.lex[0], lexeme.lex[4]) || /* a b S c  a' P f  */ 
	   is_base_pair(lexeme.lex[0], lexeme.lex[3]) || /* a b S a' c  P f  */ 
	   is_base_pair(lexeme.lex[1], lexeme.lex[3]) || /* a b S b' c  P f  */ 
	   is_base_pair(lexeme.lex[1], lexeme.lex[4]) || /* a b S c  b' P f  */ 
 	   is_base_pair(lexeme.lex[4], lexeme.lex[6]) || /* a b S c  f  P f' */ 
	   is_base_pair(lexeme.lex[3], lexeme.lex[6]) || /* a b S f  c  P f' */
	   is_base_pair(lexeme.lex[0], lexeme.lex[6])    /* a b S c  f  P a' */
	   ) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;
  
  strcpy(yr_name, "yacc_rule47_3at");
  R->natoms = 3;

  /* atom 0: five-way emitter i,i+1,k,k+1,j */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 5;             /* five-way emitter */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_I;       /* i+1 */
  A->offset[1]              = +1;        
  A->coordbase[2]           = COORD_K;       /* k */
  A->offset[2]              = 0; 
  A->coordbase[3]           = COORD_K;       /* k+1 */
  A->offset[3]              = +1; 
  A->coordbase[4]           = COORD_J;       /* j */
  A->offset[4]              = 0; 

  if      (nbasepairs == 2) {
    
    /* a b S b' a' P c  */
    if       (is_base_pair(lexeme.lex[0], lexeme.lex[4]) && is_base_pair(lexeme.lex[1], lexeme.lex[3])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 3;     
      A->bp[1].basepair_coordl_idx = 1;
      A->bp[1].basepair_coordr_idx = 2;     
    }
    
    /* a b S a' b' P c  (pknot) */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[3]) && is_base_pair(lexeme.lex[1], lexeme.lex[4])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 2;     
      A->bp[1].basepair_coordl_idx = 1;
      A->bp[1].basepair_coordr_idx = 3;     
    }
    
    /* a b S a' c  P c'  */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[3]) && is_base_pair(lexeme.lex[4], lexeme.lex[6])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[5]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 2;     
      A->bp[1].basepair_coordl_idx = 3;
      A->bp[1].basepair_coordr_idx = 4;     
    } 

    /* a b S c  a' P c'  (pknot) */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[4]) && is_base_pair(lexeme.lex[3], lexeme.lex[6])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[5]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 3;     
      A->bp[1].basepair_coordl_idx = 2;
      A->bp[1].basepair_coordr_idx = 4;     
    }

    /* b a S a' c  P c' */
    else if (is_base_pair(lexeme.lex[1], lexeme.lex[3]) && is_base_pair(lexeme.lex[4], lexeme.lex[6])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[5]);
      A->bp[0].basepair_coordl_idx = 1;
      A->bp[0].basepair_coordr_idx = 2;     
      A->bp[1].basepair_coordl_idx = 3;
      A->bp[1].basepair_coordr_idx = 4;     
    }
    
    /* b a S c  a' P c' (pknot) */
    else if (is_base_pair(lexeme.lex[1], lexeme.lex[4]) && is_base_pair(lexeme.lex[3], lexeme.lex[6])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[5]);
      A->bp[0].basepair_coordl_idx = 1;
      A->bp[0].basepair_coordr_idx = 3;     
      A->bp[1].basepair_coordl_idx = 2;
      A->bp[1].basepair_coordr_idx = 4;     
    }

    /* a b S b' c  P a' */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[6]) && is_base_pair(lexeme.lex[1], lexeme.lex[3])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, G->nt[R->nt_idx].ntname);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 4;     
      A->bp[1].basepair_coordl_idx = 1;
      A->bp[1].basepair_coordr_idx = 2;     
    }
    
    /* a b S c  b' P a' */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[6]) && is_base_pair(lexeme.lex[1], lexeme.lex[4])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, G->nt[R->nt_idx].ntname);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 4;     
      A->bp[1].basepair_coordl_idx = 1;
      A->bp[1].basepair_coordr_idx = 3;     
    }  
    
    else 
      grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (nbasepairs == 1) {

    /* a b S c  a' P f  */ 
    if      (is_base_pair(lexeme.lex[0], lexeme.lex[4])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 3;     
    }
    /* a b S a' c  P f  */ 
    else if(is_base_pair(lexeme.lex[0], lexeme.lex[3])){
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 2;     
    } 

    /* a b S b' c  P f  */
    else if(is_base_pair(lexeme.lex[1], lexeme.lex[3])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 1;
      A->bp[0].basepair_coordr_idx = 2;     
    }  

    /* a b S c  b' P f  */
    else if(is_base_pair(lexeme.lex[1], lexeme.lex[4])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[2]);
      A->bp[0].basepair_coordl_idx = 1;
      A->bp[0].basepair_coordr_idx = 3;     
    }  

    /* a b S c  f  P f' */ 
    else if(is_base_pair(lexeme.lex[4], lexeme.lex[6])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[5]);
      A->bp[0].basepair_coordl_idx = 3;
      A->bp[0].basepair_coordr_idx = 4;     
    }
    
    /* a b S f  c  P f' */
    else if(is_base_pair(lexeme.lex[3], lexeme.lex[6])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[5]);
      A->bp[0].basepair_coordl_idx = 2;
      A->bp[0].basepair_coordr_idx = 4;     
    }
    
    /* a b S c  f  P a' */
    else if(is_base_pair(lexeme.lex[0], lexeme.lex[6])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, G->nt[R->nt_idx].ntname);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 4;     
    }
    
    else 
      grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[1]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[4]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[6]);    /* atom name  */

 /* edist name */
  if      (lexeme.l == 7) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 8) { 
    if (strstr(lexeme.lex[7], "e")) strcpy(A->edist_name[0], lexeme.lex[7]);
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+2,k-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_I;       /* i+2 */
  A->offset[0]              = +2;        
  A->coordbase[1]           = COORD_K;       /* k-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 4;             /* context */
  A->maxctxt_basetag[0]     = -2;            /* -2 tag */
  A->maxctxt_basetag[1]     = -1;            /* -1 tag */
  A->maxctxt_basetag[2]     = +1;            /* +1 tag */
  A->maxctxt_basetag[3]     = +2;            /* +2 tag */
  strcpy(A->atom_syntax, lexeme.lex[2]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+2,j-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_K;       /* k+2 */
  A->offset[0]              = +2;        
  A->coordbase[1]           = COORD_J;       /* j-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 3;             /* context */
  A->maxctxt_basetag[0]     = -2;            /* -2 tag */
  A->maxctxt_basetag[1]     = -1;            /* -1 tag */
  A->maxctxt_basetag[2]     = +1;            /* +1 tag */
  strcpy(A->atom_syntax, lexeme.lex[5]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/* YACC RULE #48 EMISSION NONTERM EMISSION EMISSION NONTERM EMISSION EMISSION 
 *
 * 3 atoms, five-way emission i,k,k+1,j-1,j, nonterminal (i+1,k-1), and nonterminal (k+2,j-2)
 *
 */
int
yacc_rule48(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  char yr_name[MAXSTR];
  int  natoms = 0; /* natoms */

  strcpy(yr_name, "yacc_rule48");
  
  if (lexeme.l < 9)       /* joint emission */
    natoms = yacc_rule48_3at(R, lexeme, G, verbose);
  else 
   grammar_fatal("%s() failed at rna_rule %s nt %s.", yr_name, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  return natoms;
}
int
yacc_rule48_3at(RULE *R, struct lexeme_s lexeme, GRAMMAR *G, int verbose) 
{
  ATOM *A;
  char  yr_name[MAXSTR];
  int   a = -1; /* atom index */
  int   nbasepairs;
  int   notallowed = FALSE;

  if (is_base_pair(lexeme.lex[2], lexeme.lex[3])) notallowed = TRUE; /* a S b  b' P e  f  */
  if (is_base_pair(lexeme.lex[5], lexeme.lex[6])) notallowed = TRUE; /* a S b  c  P e  e' */

  if ( (is_base_pair(lexeme.lex[0], lexeme.lex[2]) && is_base_pair(lexeme.lex[3], lexeme.lex[5])) || /* a S a' b  P b' c  */
       (is_base_pair(lexeme.lex[0], lexeme.lex[3]) && is_base_pair(lexeme.lex[2], lexeme.lex[5])) || /* a S b  a' P b' c  (pknot) */
       (is_base_pair(lexeme.lex[0], lexeme.lex[2]) && is_base_pair(lexeme.lex[3], lexeme.lex[6])) || /* a S a' b  P c  b' */
       (is_base_pair(lexeme.lex[0], lexeme.lex[3]) && is_base_pair(lexeme.lex[2], lexeme.lex[6])) || /* a S b  a' P c  b' (pknot) */
       (is_base_pair(lexeme.lex[2], lexeme.lex[6]) && is_base_pair(lexeme.lex[3], lexeme.lex[5])) || /* a S b  c  P c' b' */
       (is_base_pair(lexeme.lex[2], lexeme.lex[5]) && is_base_pair(lexeme.lex[3], lexeme.lex[6])) || /* a S b  c  P b' c' (pknot) */
       (is_base_pair(lexeme.lex[0], lexeme.lex[6]) && is_base_pair(lexeme.lex[2], lexeme.lex[5])) || /* a S b  c  P b' a' */
       (is_base_pair(lexeme.lex[0], lexeme.lex[6]) && is_base_pair(lexeme.lex[3], lexeme.lex[5]))    /* a S c  b  P b' a' */
       ) 
    nbasepairs = 2;
  else if (is_base_pair(lexeme.lex[0], lexeme.lex[2]) || /* a S a' b  P c  f  */
	   is_base_pair(lexeme.lex[0], lexeme.lex[3]) || /* a S b  a' P c  f  */
	   is_base_pair(lexeme.lex[3], lexeme.lex[5]) || /* a S b  c  P c' f  */
	   is_base_pair(lexeme.lex[2], lexeme.lex[5]) || /* a S c  b  P c' f  */
	   is_base_pair(lexeme.lex[3], lexeme.lex[6]) || /* a S b  c  P f  c' */
	   is_base_pair(lexeme.lex[2], lexeme.lex[6]) || /* a S c  b  P f  c' */
	   is_base_pair(lexeme.lex[0], lexeme.lex[6])    /* a S b  c  P f  a' */
	   ) 
    nbasepairs = 1;
  else 
    nbasepairs = 0;
  
  strcpy(yr_name, "yacc_rule48_3at");
  R->natoms = 3;

  /* atom 0: five-way emitter i,k,k+1,j-1,j */
  A = &(R->atom[++a]);
  A->atomtype               = EMISSION_ATOM;
  A->nbasepairs             = nbasepairs;
  A->has_basepair           = (A->nbasepairs > 0)? TRUE : FALSE;
  A->ncoords                = 5;             /* five-way emitter */
  A->coordbase[0]           = COORD_I;       /* i */
  A->offset[0]              = 0;        
  A->coordbase[1]           = COORD_K;       /* k */
  A->offset[1]              = 0;        
  A->coordbase[2]           = COORD_K;       /* k+1 */
  A->offset[2]              = +1; 
  A->coordbase[3]           = COORD_J;       /* j-1 */
  A->offset[3]              = -1; 
  A->coordbase[4]           = COORD_J;       /* j */
  A->offset[4]              = 0; 
  if      (nbasepairs == 2) {
    
    /* a S a' b  P b' c  */
    if      (is_base_pair(lexeme.lex[0], lexeme.lex[2]) && is_base_pair(lexeme.lex[3], lexeme.lex[5])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[1]);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[4]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 1;     
      A->bp[1].basepair_coordl_idx = 2;
      A->bp[1].basepair_coordr_idx = 3;     
    }
    
    /* a S b  a' P b' c  (pknot) */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[3]) && is_base_pair(lexeme.lex[2], lexeme.lex[5])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[1]);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[4]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 2;     
      A->bp[1].basepair_coordl_idx = 1;
      A->bp[1].basepair_coordr_idx = 3;     
    }
    
    /* a S a' b  P c  b' */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[2]) && is_base_pair(lexeme.lex[3], lexeme.lex[6])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[1]);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[4]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 1;     
      A->bp[1].basepair_coordl_idx = 2;
      A->bp[1].basepair_coordr_idx = 4;     
    }
    
    /* a S b  a' P c  b' (pknot) */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[3]) && is_base_pair(lexeme.lex[2], lexeme.lex[6])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[1]);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[4]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 2;     
      A->bp[1].basepair_coordl_idx = 1;
      A->bp[1].basepair_coordr_idx = 4;     
    }
    
    /* a S b  c  P c' b' */
    else if (is_base_pair(lexeme.lex[2], lexeme.lex[6]) && is_base_pair(lexeme.lex[3], lexeme.lex[5])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[4]);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[4]);
      A->bp[0].basepair_coordl_idx = 1;
      A->bp[0].basepair_coordr_idx = 4;     
      A->bp[1].basepair_coordl_idx = 2;
      A->bp[1].basepair_coordr_idx = 3;     
    }
    
    /* a S b  c  P b' c' (pknot) */
    else if (is_base_pair(lexeme.lex[2], lexeme.lex[5]) && is_base_pair(lexeme.lex[3], lexeme.lex[6])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[4]);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[4]);
      A->bp[0].basepair_coordl_idx = 1;
      A->bp[0].basepair_coordr_idx = 3;     
      A->bp[1].basepair_coordl_idx = 2;
      A->bp[1].basepair_coordr_idx = 4;     
    }
    
    /* a S b  c  P b' a' */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[6]) && is_base_pair(lexeme.lex[2], lexeme.lex[5])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, G->nt[R->nt_idx].ntname);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[4]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 4;     
      A->bp[1].basepair_coordl_idx = 1;
      A->bp[1].basepair_coordr_idx = 3;     
    }
    
    /* a S c  b  P b' a' */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[6]) && is_base_pair(lexeme.lex[3], lexeme.lex[5])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, G->nt[R->nt_idx].ntname);
      A->bp[1].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[4]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 4;     
      A->bp[1].basepair_coordl_idx = 2;
      A->bp[1].basepair_coordr_idx = 3;     
    }   

    else 
      grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else if (nbasepairs == 1) {

    /* a S a' b  P c  f  */
    if      (is_base_pair(lexeme.lex[0], lexeme.lex[2])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[1]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 1;     
    } 

    /* a S b  a' P c  f  */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[3])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[1]);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 2;     
    }
    
    /* a S b  c  P c' f  */
    else if (is_base_pair(lexeme.lex[3], lexeme.lex[5])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[4]);
      A->bp[0].basepair_coordl_idx = 2;
      A->bp[0].basepair_coordr_idx = 3;     
    }
    
    /* a S c  b  P c' f  */
    else if (is_base_pair(lexeme.lex[2], lexeme.lex[5])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[4]);
      A->bp[0].basepair_coordl_idx = 1;
      A->bp[0].basepair_coordr_idx = 3;     
    }
    
    /* a S b  c  P f  c' */
    else if (is_base_pair(lexeme.lex[3], lexeme.lex[6])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[4]);
      A->bp[0].basepair_coordl_idx = 2;
      A->bp[0].basepair_coordr_idx = 4;     
    }
    
    /* a S c  b  P f  c' */
    else if (is_base_pair(lexeme.lex[2], lexeme.lex[6])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, lexeme.lex[4]);
      A->bp[0].basepair_coordl_idx = 1;
      A->bp[0].basepair_coordr_idx = 4;     
    }
    
    /* a S b  c  P f  a' */
    else if (is_base_pair(lexeme.lex[0], lexeme.lex[6])) {
      A->bp[0].basepairtype        = rna_atom_basepairtype(A, G->nt[R->nt_idx].ntname);
      A->bp[0].basepair_coordl_idx = 0;
      A->bp[0].basepair_coordr_idx = 4;     
    }   
    
    else 
      grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }

  strcpy(A->atom_syntax, lexeme.lex[0]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[2]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[3]);    /* atom name  */
  strcat(A->atom_syntax, "^");              /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[5]);    /* atom name  */
  strcat(A->atom_syntax, lexeme.lex[6]);    /* atom name  */

 /* edist name */
  if      (lexeme.l == 7) 
    strcpy(A->edist_name[0], "e0"); 
  else if (lexeme.l == 8) { 
    if (strstr(lexeme.lex[7], "e")) strcpy(A->edist_name[0], lexeme.lex[7]);
    else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  }
  else grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 1: nonterminal (i+1,k-1) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_I;       /* i+1 */
  A->offset[0]              = +1;        
  A->coordbase[1]           = COORD_K;       /* k-1 */
  A->offset[1]              = -1;        
  A->max_nctxts             = 3;             /* context */
  A->maxctxt_basetag[0]     = -1;            /* -1 tag */
  A->maxctxt_basetag[1]     = +1;            /* +1 tag */
  A->maxctxt_basetag[2]     = +2;            /* +2 tag */
  strcpy(A->atom_syntax, lexeme.lex[1]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);
  
  /* atom 2: nonterminal (k+2,j-2) */
  A = &(R->atom[++a]);
  A->atomtype               = NONTERMINAL_ATOM;
  A->ncoords                = 2;             /* nonterminal */
  A->coordbase[0]           = COORD_K;       /* k+2 */
  A->offset[0]              = +2;        
  A->coordbase[1]           = COORD_J;       /* j-2 */
  A->offset[1]              = -2;        
  A->max_nctxts             = 4;             /* context */
  A->maxctxt_basetag[0]     = -2;            /* -2 tag */
  A->maxctxt_basetag[1]     = -1;            /* -1 tag */
  A->maxctxt_basetag[2]     = +1;            /* +1 tag */
  A->maxctxt_basetag[3]     = +2;            /* +2 tag */
  strcpy(A->atom_syntax, lexeme.lex[4]);     /* atom name  */
  if (rna_atom_write(A, R, G, TRUE, verbose) != eslOK) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  if (notallowed) 
    grammar_fatal("%s() failed at atom %s rule %s nt %s.", yr_name, A->atom_syntax, R->rule_syntax, G->nt[R->nt_idx].ntname);

  return a+1;
}

/*----------------- end, local functions  ----------------*/


/*****************************************************************
 * 3. main
 *****************************************************************/
#ifdef grmPARSE_TESTDRIVE
/* 
   flex -I grm_parsegrammar.lex
   byacc -d grm_parsegrammar.y
   gcc -I /groups/eddy/home/rivase/src/easel -I ~/src/easel -g -Wall -c grammar.c
   gcc -I /groups/eddy/home/rivase/src/easel -I ~/src/easel -g -Wall -c grm_util.c
   gcc -I ~/src/easel -L ~/src/easel -g -Wall -DgrmPARSE_TESTDRIVE lex.yy.c y.tab.c -o test_grammarparser grammar.o grm_util.o -lm -ll -ly -leasel
   
*/
int
main (int argc, char **argv)
{
  extern FILE *yyin;
  GRAMMAR     *G;
  int          be_verbose = TRUE;

  if ((yyin = fopen(argv[1], "r")) == NULL)
    grammar_fatal("Coudn't open file %s\n", argv[1]);

  G = Grammar_Parse(yyin);
  Grammar_Dump(stdout, G, FALSE, be_verbose);

  Grammar_Destroy(G);
  fclose(yyin);

  return 0;
}
#endif /* grmPARSE_TESTDRIVE */
/*----------------- end, main  ----------------*/
