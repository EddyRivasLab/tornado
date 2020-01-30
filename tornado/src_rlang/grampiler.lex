/* grampiler.lex
 * lex source to produce scanner for stochastic CFGs 
 */

%{
  /* list any needed C libraries here */
  #include <stdio.h>
  #include <string.h>

  #include "util.h"
  #include "y.tab.h"
%}

/* ============= definitions ====================================== */

DIGIT [0-9]

ALPHA [a-zA-Z]

ALPHA_NUM [a-zA-Z0-9]

BASE [ACGU]

BASE_PAIR {BASE}{2}

STACKED_PAIR {BASE_PAIR}"_"{BASE_PAIR}

EMPTY_STR e

SIGMA [abcdfghijklmnopqrstuvwxyz]

V [BDEFHIJKLMNOPQRSTVWXYZ]

COMP_MARKER "'"

SUPERSCRIPT_MARKER "^"

REWRITE_OP "-->"

EMITTER {SIGMA}|{SIGMA}{COMP_MARKER}

BP_STACK_PARAM {SUPERSCRIPT_MARKER}{DIGIT}

NONTERM {V}{BP_STACK_PARAM}?

%% /* ========== rules ============================================ */

"edist" return EDIST_DECL;

" "?":"" "? return SEPARATOR;

" "?"="" "? return GETS;

"remaining_singlets" return BASE_DEFAULT;

"remaining_base_pairs" return BP_DEFAULT;

"remaining_stack_pairs" return SP_DEFAULT;

"|" return CHOICE;

"-"?{DIGIT}+ {
  yylval = (int)strdup(yytext); return INT_VALUE;
}

{ALPHA}{DIGIT}+ {
  yylval = (int)strdup(yytext); return EDIST_KEY;
}

{BASE} {
  yylval = (int)strdup(yytext); return BASE;
}

{BASE_PAIR} {
  yylval = (int)strdup(yytext); return BASE_PAIR;
}

{STACKED_PAIR} {
  yylval = (int)strdup(yytext); return STACKED_PAIR;
}

{NONTERM}" "{REWRITE_OP} {
  yylval = (int)strdup(strtok(yytext," ")); return LHS; /* copy only NONTERM to yylval */
}

{NONTERM} {
  yylval = (int)strdup(yytext); return NONTERM;
}

{EMPTY_STR} {
  yylval = (int)strdup(yytext); return EPSILON;
}

{EMITTER} {
  yylval = (int)strdup(yytext); return EMITTER;
}

[ \t\n]+ /* consume whitespace */

. Die("grampiler lexical error: %s\n", yytext );

%% /* ========== user code ======================================= */
