/* grammar_io.h
 * header file for SCFG compiler support functions for the TORNADO project
 *
 * Ray Lang, 10/11/2005 [St. Louis]
 */

#ifndef GRAMMAR_IO_INCLUDED
#define GRAMMAR_IO_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "util.h"
#include "grammar.h"

#define MAX_STR_LEN 120
#define MAX_TYPE_STR_LEN 10

/* these nucleotide enumerations are used as symbolic indices 
 * into the emission distribution arrays */

enum BASE_E {A, C, G, U, NUM_BASES};

enum BASE_PAIR_E {AA, AC, AG, AU, CA, CC, CG, CU, 
		  GA, GC, GG, GU, UA, UC, UG, UU, NUM_BASE_PAIRS};

enum STACKED_PAIR_E {AA_AA, AA_AC, AA_AG, AA_AU, AA_CA, AA_CC, AA_CG, AA_CU, 
		     AA_GA, AA_GC, AA_GG, AA_GU, AA_UA, AA_UC, AA_UG, AA_UU, 
		     AC_AA, AC_AC, AC_AG, AC_AU, AC_CA, AC_CC, AC_CG, AC_CU, 
		     AC_GA, AC_GC, AC_GG, AC_GU, AC_UA, AC_UC, AC_UG, AC_UU, 
		     AG_AA, AG_AC, AG_AG, AG_AU, AG_CA, AG_CC, AG_CG, AG_CU, 
		     AG_GA, AG_GC, AG_GG, AG_GU, AG_UA, AG_UC, AG_UG, AG_UU, 
		     AU_AA, AU_AC, AU_AG, AU_AU, AU_CA, AU_CC, AU_CG, AU_CU, 
		     AU_GA, AU_GC, AU_GG, AU_GU, AU_UA, AU_UC, AU_UG, AU_UU, 
		     CA_AA, CA_AC, CA_AG, CA_AU, CA_CA, CA_CC, CA_CG, CA_CU, 
		     CA_GA, CA_GC, CA_GG, CA_GU, CA_UA, CA_UC, CA_UG, CA_UU, 
		     CC_AA, CC_AC, CC_AG, CC_AU, CC_CA, CC_CC, CC_CG, CC_CU, 
		     CC_GA, CC_GC, CC_GG, CC_GU, CC_UA, CC_UC, CC_UG, CC_UU, 
		     CG_AA, CG_AC, CG_AG, CG_AU, CG_CA, CG_CC, CG_CG, CG_CU, 
		     CG_GA, CG_GC, CG_GG, CG_GU, CG_UA, CG_UC, CG_UG, CG_UU, 
		     CU_AA, CU_AC, CU_AG, CU_AU, CU_CA, CU_CC, CU_CG, CU_CU, 
		     CU_GA, CU_GC, CU_GG, CU_GU, CU_UA, CU_UC, CU_UG, CU_UU, 
		     GA_AA, GA_AC, GA_AG, GA_AU, GA_CA, GA_CC, GA_CG, GA_CU, 
		     GA_GA, GA_GC, GA_GG, GA_GU, GA_UA, GA_UC, GA_UG, GA_UU, 
		     GC_AA, GC_AC, GC_AG, GC_AU, GC_CA, GC_CC, GC_CG, GC_CU, 
		     GC_GA, GC_GC, GC_GG, GC_GU, GC_UA, GC_UC, GC_UG, GC_UU, 
		     GG_AA, GG_AC, GG_AG, GG_AU, GG_CA, GG_CC, GG_CG, GG_CU, 
		     GG_GA, GG_GC, GG_GG, GG_GU, GG_UA, GG_UC, GG_UG, GG_UU, 
		     GU_AA, GU_AC, GU_AG, GU_AU, GU_CA, GU_CC, GU_CG, GU_CU, 
		     GU_GA, GU_GC, GU_GG, GU_GU, GU_UA, GU_UC, GU_UG, GU_UU, 
		     UA_AA, UA_AC, UA_AG, UA_AU, UA_CA, UA_CC, UA_CG, UA_CU, 
		     UA_GA, UA_GC, UA_GG, UA_GU, UA_UA, UA_UC, UA_UG, UA_UU, 
		     UC_AA, UC_AC, UC_AG, UC_AU, UC_CA, UC_CC, UC_CG, UC_CU, 
		     UC_GA, UC_GC, UC_GG, UC_GU, UC_UA, UC_UC, UC_UG, UC_UU, 
		     UG_AA, UG_AC, UG_AG, UG_AU, UG_CA, UG_CC, UG_CG, UG_CU, 
		     UG_GA, UG_GC, UG_GG, UG_GU, UG_UA, UG_UC, UG_UG, UG_UU, 
		     UU_AA, UU_AC, UU_AG, UU_AU, UU_CA, UU_CC, UU_CG, UU_CU, 
		     UU_GA, UU_GC, UU_GG, UU_GU, UU_UA, UU_UC, UU_UG, UU_UU,
                     NUM_STACKED_PAIRS};

/* very long specs are broken across multiple lines */
#define SPEC_CONTINUES "CONTINUED"

/* marks end of specs for nested structures */
#define SPEC_ENDS "END_SPEC"

enum GRAMMAR_KEY { 

  ZERO_KEY ,       /* default value */

  /* fields in struct RULE */
  RULE_ROW_NDX , RULE_COL_NDX , /* not fields, but req'd by grammpiler to properly index rules  */
  NATOMS_K ,            /* int natoms;  (number of atoms in the rule)                           */
  ATOMTYPE_K ,          /* enum atom_e atomtype[MAXATOMS];  (type (NONTERMINAL_ATOM,  etc.))    */
  EDIST_IDX_K ,         /* int edist_idx[MAXATOMS];  (index of emission dist)                   */
  LDIST_IDX_K ,         /* int ldist_idx[MAXATOMS];  (index of length dist (SEGMENTs only))     */
  NTERM_IDX_K ,         /* int nterm_idx[MAXATOMS];  (index of nonterminal (NONTEMINAL only))   */
  NCOORDS_K ,           /* int ncoords[MAXATOMS];  (number of sequence coords used)             */
  COORDBASE_K ,         /* int coordbase[MAXATOMS][MAXCOORD];  (COORD_I, COORD_J, ..., COORD_L) */
  OFFSET_K ,            /* int offset[MAXATOMS][MAXCOORD];  (offset of each base coord)         */
  CONTEXT_K ,           /* int context[MAXATOMS][MAXCOORD];  ( context to use for each residue) */
  D1_ITERATOR_STATE_K , /* enum iterstate_e d1_iterator_state;  (ITERATOR_ON | _OFF)            */
  D1_ITERATOR_MIN_K ,   /* int d1_iterator_min;  (-1 | minlength of a SEGMENT)                  */
  D1_ITERATOR_MAX_K ,   /* int d1_iterator_max;  (MAXINT | maxlength of a SEGMENT)              */
  D2_ITERATOR_STATE_K , /* enum iterstate_e d2_iterator_state;  (ITERATOR_ON | _OFF | _TIED)    */
  D2_ITERATOR_MIN_K ,   /* int d2_iterator_min;  (-1 | minlength of a SEGMENT)                  */
  D2_ITERATOR_MAX_K ,   /* int d2_iterator_max;  (MAXINT | maxlength of a SEGMENT)              */
  ATOM_MIND_K ,         /* int atom_mind[MAXATOMS];  (minimum subseq lengths for each atom)     */
  IS_ALLTERMINALS_K ,   /* int is_allterminals;  (TRUE if rule contains no nonterminals)        */

  /* fields in struct EDIST */
  N_K ,           /* int n;  (number of residues emitted, usually 1 or 2)          */
  EP_K ,          /* double *ep;  (prob distribution [0...NUM_BASES^N_K - 1])      */
  ESC_K ,         /* CYKVAL *esc;  (scores, [0...NUM_BASES^N_K - 1])               */
  IS_BASEPAIR_K , /* int is_basepair;  (TRUE if n=2 and x,x' are annotated as a bp */

  /* fields in struct LDIST */
  MIN_K , /* int min;  (minimum length w/ prob > 0)                       */
  MAX_K , /* int max;  (maximum length w/ prob > 0)                       */
  LP_K ,  /* double *lp;  (probability dist [0...max]; 0...min-1 are 0.0) */
  LSC_K , /* CYKVAL *lsc;  (scores, [0...max]; 0...min-1 are -\infty)     */

  /* fields in struct GRAMMAR */
  M_K ,          /* int M;  (# of nonterminals in the grammar)                     */
  PR_K,          /* RULE pr[MAXNT][MAXRULES];  (production rules for each nonterm) */
  NRULES_K,      /* int nrules[MAXNT]; (NOT COMMENTED IN GRAMMAR.H)                */
  TDIST_IDX_K ,  /* int tdist_idx[MAXNT];  (idx of trans dist to use for each NT)  */
  NTD_K ,        /* int ntd;  (number of transition distributions)                 */
  TN_K,          /* int tn[MAXNT];  (number of rules for each trans dist)          */
  TP_K ,         /* double tp[MAXNT][MAXRULES];  (transition prob distributions)   */
  TSC_K ,        /* CYKVAL tsc[MAXNT][MAXRULES];  (transition scores (log t[][]))  */
  NED_K ,        /* int ned;  (number of emission distribtions of the grammar)     */
  EDIST_K ,      /* EDIST *edist;  (emission distribtions of the grammar)          */
  NLD_K ,        /* int nld;  (number of length distribtions of the grammar)       */
  LDIST_K ,      /* LDIST *ldist;  (length distribtions of thd grammar)            */
  NONTERM_MIN_K, /* int nt_mind[MAXNT];  (min subseq length for nonterminals)      */
  RULE_MIN_K ,   /* int rule_mind[MAXNT][MAXRULES];  (min subseq length for rules) */
  
  NUM_GRAMMAR_KEYS }; /* must be last in the enumeration to capture number of keys defined */

typedef struct {
  enum GRAMMAR_KEY fld_key; /* key to corresponding grammar struct field */
  char type_str[MAX_TYPE_STR_LEN]; /* field's data type */
  int num_dim; /* number of dimensions of the string (zero for scalars) */
  int* dim_sizes; /* sizes of dimensions (NULL for scalars) */
  void* vals; /* values of the fields */
} FIELD_SPEC;

/* declarations for linked list of FIELD_SPEC */
struct SPEC_NODE {
  FIELD_SPEC spec;
  struct SPEC_NODE* next;
};

typedef struct SPEC_NODE* SPEC_LIST;

/* declarations for linked list of specification strings */
struct SPEC_STR_NODE {
  char str[MAX_STR_LEN];
  struct SPEC_STR_NODE* next;
};

typedef struct SPEC_STR_NODE* SPEC_STR_LIST;
  
/* map a grammar key to its corresponding string for output purposes */
char* str_from_key(char*, enum GRAMMAR_KEY);

/* map an iterator state to its corresponding string for output purposes */
char* str_from_iterstate(char*, enum iterstate_e);

/* map an atom type to its corresponding string for output purposes */
char* str_from_atom(char*, enum atom_e);

/* map a coordinate base to its corresponding string for output purposes */
char* str_from_coordbase(char*, int);

/* map a string to its corresponding base enum constant for input purposes (or Die) */
enum BASE_E base_from_string(char*);

/* map a string to its corresponding base pair enum constant for input purposes (or Die) */
enum BASE_PAIR_E bp_from_string(char*);

/* map a string to its corresponding base pair enum constant for input purposes (or Die) */
enum STACKED_PAIR_E sp_from_string(char*);

/* map a string to its corresponding grammar key for input purposes (or Die) */
enum GRAMMAR_KEY key_from_string(char*);

/* open the file provided as an argument, return pointer to grammar structure (or Die) */
GRAMMAR* read_compiled_grammar(char*);

/* read an opened input stream, return pointer to a grammar structure (or Die) */
GRAMMAR* read_compiled_grammar_file(FILE*);

/* write contents of all fields in a grammar structure to an opened output stream */
void raw_grammar_dump(FILE*, GRAMMAR*);

/* write contents of all fields in a grammar structure to an opened output stream */
void raw_grammar_dump1(FILE*, GRAMMAR*, int);

#endif /* GRAMMAR_IO_INCLUDED */
