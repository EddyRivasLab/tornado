%{
  /* grampiler.y
   * yacc source file for stochastic context-free grammar compiler (TORNADO)
   * * Ray Lang, 11/1/2005 [St. Louis]
   */
  
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

/* ===== include grammar structure & grammar-io services =============== */

#include "grammar.h"
#include "grammar_io.h"

/* ===== yacc-req'd declarations ======================================== */

#define YYSTYPE char *
#define YYSTYPE_IS_DECLARED

extern int yyparse(void);
extern int yylex(void);

/* ===== compiler declarations ============================================= */

enum score_type_e {SINGLET, BP, SP};

/* for tracking track top level emission distribution records */

struct EDIST_INFO_NODE {
  int index;
  int use_count;
  int num_emitted, num_depends_on;
  char name[MAX_STR_LEN];
  SPEC_STR_LIST spec_list;
  struct EDIST_INFO_NODE* next;
};

typedef struct EDIST_INFO_NODE* EDIST_LIST;

/* for tracking specific emission distribution scores accompanying a grammar */

struct SCORE_NODE {
  enum score_type_e scor_typ;
  int index;
  int value;
  struct SCORE_NODE* next;
};

typedef struct SCORE_NODE* SCORE_LIST;

/* ===== global variables ============================================= */
/* static qualifier limits scope to this file in
 * the event the name is used anywhere else
 */

/* for emission scores explicitly specified in the source grammar */
static CYKVAL pair_scores[NUM_BASE_PAIRS];
static CYKVAL singlet_scores[NUM_BASES];
static CYKVAL stack_scores[NUM_STACKED_PAIRS];

static EDIST_LIST edist_info_list; /* linked list of emission distribtion specs */

static SCORE_LIST scores; /* linked list of specific edist scores */

static SPEC_STR_LIST rule_specs; /* linked list of rewrite rule specifications */

static char curr_lhs[MAX_STR_LEN]; /* left hand side rewrite operator of current rule */
static char nonterm_str[MAXNT+1]; /* nonterminals in the grammar */
static char rule_str[MAX_STR_LEN]; /* used by yacc rules to insert source rule into object file */

/* arrays assigned values by yacc rules;
 * the array values are used to generate the rewrite specs in the object file */
static enum atom_e atom_type[MAXATOMS];
static int context[MAXATOMS][MAXCOORD];
 static int coord_base[MAXATOMS][MAXCOORD];
static int coord_ofst[MAXATOMS][MAXCOORD];
static int coords[MAXATOMS];
static int edist[MAXATOMS];
static int ldist[MAXATOMS];
static int nterm[MAXATOMS];

static int rhs_count[MAXNT]; /* used to generate the nrules array in the object file */
static int num_controlling_pairs[MAXNT]; /* number of pairs a stack-annotated nonterm depends on */

static int nt_ndx; /* index of nonterm being rewritten by current right-hand-side */
static int num_atoms; /* count of atoms found in the right-hand-side of a rule */
static int num_nonterms; /* count of nonterms found in source grammar */
static int rule_count; /* number of rules, presently used only for diagnostic output */

/* used as booleans to track whether source grammar specifies emission scores */
static int has_pairs, has_stacks, edist_scores_specified;
static int singlet_score_given, default_singlet_score_given;
static int pair_score_given, default_pair_score_given;
static int stack_score_given, default_stack_score_given;

/* ===== function prototypes ============================================= */

/* initialization functions */
void clear_rule_arrays();
void initialize_globals();

/* functions to analyze & compose the grammar */
CYKVAL* create_escore_array(int, int);

EDIST_LIST append_default_edist(char*, int);
EDIST_LIST push_edist_info(int, int, char*, CYKVAL[], EDIST_LIST);

SCORE_LIST push_score_node(enum score_type_e, int, int, SCORE_LIST);

SPEC_STR_LIST build_top_level_fields();
SPEC_STR_LIST push_edist(char*, int, int, int, CYKVAL[], SPEC_STR_LIST);
SPEC_STR_LIST push_str_node(char *, SPEC_STR_LIST);

int check_for_scores();
int collect_edists(EDIST_LIST, SPEC_STR_LIST*);
int find_default_edist(char*, int);
int find_named_edist(char*, int, int);
int is_all_zeroes(CYKVAL*, int);
int is_base_pair(char *, char *);
int is_stacking_nt(char *);
int nonterm_index_of(char *);

void add_declared_edist(char*, int, int); 
void add_rule_specs(int, int, enum iterstate_e, enum iterstate_e);
void adjust_edist_indices(EDIST_LIST);
void count_rhs();
void ensure_nonstacking_nt(char *); 
void ensure_nonterms_have_rules();
void process_specified_scores();

/* function(s) to output the compiled grammar */
void write_spec_str_list(FILE*, SPEC_STR_LIST);

/* function(s) to deallocate linked lists */
int destroy_info_list(EDIST_LIST);
int destroy_spec_list(SPEC_STR_LIST);

/* diagnostic functions */
void show_singlet_and_pair_scores();
void show_stack_scores();

/* ===== yacc-req'd functions ============================================= */

void yyerror(const char *str)
{
  Die("grampiler %s\n", str);
}

int yywrap()
{
  return 1;
}

/* ===== main ============================================================ */

int main()
{
  char s[MAX_STR_LEN];
  SPEC_STR_LIST top_level_specs, edist_specs = NULL;
  int num_edist = 0;

  initialize_globals();

  /* parse the file, construct rule spec list by side effect */
  yyparse();

  /* push spec for top level prod rule field onto rule list */
  sprintf(s, ":PR_K:RULE:2:%d:%d\n", MAXNT, MAXRULES);
  rule_specs = push_str_node(s, rule_specs);

  /* construct the top level fields */
  top_level_specs = build_top_level_fields();

  /* output the top level fields */
  write_spec_str_list(stdout, top_level_specs);

  /* compute top level emission distribution fields & output the edists */
  num_edist = collect_edists(edist_info_list, &edist_specs);
  
  sprintf(s, ":EDIST_K:EDIST:1:%d\n", num_edist);
  edist_specs = push_str_node(s, edist_specs);

  sprintf(s, ":NED_K:int:0:%d\n", num_edist);
  edist_specs = push_str_node(s, edist_specs);

  write_spec_str_list(stdout, edist_specs );

  /* output the production rules */
  write_spec_str_list(stdout, rule_specs);

  /* diagnostic output */
  {
    int i, num_rules = 0;
    for(i = 0; i < MAXNT; i++) num_rules += rhs_count[i];

    fprintf(stderr, "found %d rules with %d right hand sides\n", 
	    rule_count, num_rules);
    fprintf(stderr, "the nonterminals are: %s\n",nonterm_str);
  }

  {
    int n;
    /* deallocate linked lists of spec strings */
    n = destroy_spec_list(top_level_specs);
    /* fprintf(stderr, "deallocated %d nodes from top_level_specs\n",n); */
    
    n = destroy_spec_list(edist_specs);
    /* fprintf(stderr, "deallocated %d nodes from edist_list\n",n); */
    
    n = destroy_spec_list(rule_specs);
    /* fprintf(stderr, "deallocated %d nodes from rule_specs\n",n); */

    /* deallocate linked list of edist info nodes */
    n = destroy_info_list(edist_info_list);
    /* fprintf(stderr, "deallocated %d nodes from the edist_info_list\n",n); */
  }

  ensure_nonterms_have_rules(); /* Dies if any nonterms not re-written */
  
  fprintf(stderr, "grammar compilation complete\n\n");
  return 0;
}

/* ======================================================================
 * Function: initialize_globals()
 * Incept: Ray Lang, 11/10/2005 [St. Louis] 
 *
 * Purpose: initialize the global static variables and arrays
 */
void initialize_globals()
{
  int i;

  rule_count = num_atoms = num_nonterms = 0;
  nonterm_str[num_nonterms] = '\0';

  for(i = 0; i < MAXNT; i++)
    rhs_count[i] = num_controlling_pairs[i] = 0;

  scores = NULL;
  rule_specs = NULL;
  edist_info_list = NULL;

  for(i = 0; i < NUM_BASES; i++)
    singlet_scores[i] = 0;
  for(i = 0; i < NUM_BASE_PAIRS; i++)
    pair_scores[i] = 0;
  for(i = 0; i < NUM_STACKED_PAIRS; i++)
    stack_scores[i] = 0;

  singlet_score_given = default_singlet_score_given = FALSE;
  pair_score_given = default_pair_score_given = FALSE;
  stack_score_given = default_stack_score_given = FALSE;
  has_pairs = has_stacks = FALSE;
}

/* ======================================================================
 * Function: clear_rule_arrays()
 * Incept: Ray Lang, 11/4/2005 [St. Louis] 
 *
 * Purpose: zero-out rule info in preparation for a new rule
 */
void clear_rule_arrays()
{
  int i,j;
  for(i = 0; i < MAXATOMS; i++) {
    atom_type[i] = (enum atom_e)0;
    edist[i] = ldist[i] = nterm[i] = coords[i] = 0;
    for(j = 0; j < MAXCOORD; j++) {
      coord_base[i][j] = coord_ofst[i][j] = context[i][j] = 0;
    }
  }
}

/* ======================================================================
 * Function: is_base_pair()
 * Incept: Ray Lang, 11/1/2005 [St. Louis] 
 *
 * Purpose: determine whether two emission atoms are paired
 */
int is_base_pair(char *s1, char *s2)
{
  return s1[0] == s2[0];
}

/* ======================================================================
 * used by is_stacking_nt() and nonterm_index_of() to access
 * the number of pairs a stacking nonterminal depends on 
 */
#define STACK_DEP_NDX 2

/* ======================================================================
 * Function: is_stacking_nt()
 * Incept: Ray Lang, 11/29/2005 [St. Louis] 
 *
 * Purpose: determine a non-terminal carries a stacking annotation
 */
int is_stacking_nt(char *nt)
{
  return isalpha(nt[0]) && nt[1] == '^' && isdigit(nt[STACK_DEP_NDX]);
}

/* ======================================================================
 * Function: is_all_zeroes()
 * Incept: Ray Lang, 12/2/2005 [St. Louis] 
 *
 * Purpose: returns TRUE iff array contains nothing but zeroes
 */
int is_all_zeroes(CYKVAL a[], int n)
{
  int all_zeroes = TRUE;
  int i = 0;
  
  while(all_zeroes && i < n) {
    all_zeroes = all_zeroes && (a[i++] == 0);
  }

  return all_zeroes;
}

/* ======================================================================
 * Function: ensure_nonstacking_nt()
 * Incept: Ray Lang, 11/29/2005 [St. Louis] 
 *
 * Purpose: guarantee that a nonterminal is NOT carrying a stack parameter
 *          annotation, grampiler dies otherwise
 */
void ensure_nonstacking_nt(char * nt)
{
  if ( is_stacking_nt(nt) )
    Die("grampiler error in ensure_nonstacking_nt(), nonterminal %c "
	"has stacking annotation in incorrect context\n", nt[0]);
}

/* ======================================================================
 * Function: ensure_nonterms_have_rules()
 * Incept: Ray Lang, 11/29/2005 [St. Louis] 
 *
 * Purpose: display the number of right-hand-sides for each nonterminal
 */
void ensure_nonterms_have_rules()
{
  int i, count;

  if(num_nonterms != strlen(nonterm_str))
    Die("grampiler error in ensure_nonterms_have_rules(), num_nonterms is %d, "
	"but nonterm_str is %s\n", num_nonterms, nonterm_str);
  for(i = 0; i < num_nonterms; i++) {
    count = rhs_count[i];
    if(count == 0)
      Die("grampiler error in ensure_nonterms_have_rules(), "
	  "%c not used as a left-hand-side\n",nonterm_str[i]);
    else
      fprintf(stderr, "%c is rewritten %d times\n", nonterm_str[i], rhs_count[i]);
  }
  fprintf(stderr, "\n");
}

/* ======================================================================
 * Function: count_rhs()
 * Incept: Ray Lang, 12/5/2005 [St. Louis] 
 *
 * Purpose: track count fo right-hand-sides per nonterminal,
 *          Die if count exceeds MAXRULES (defined in grammar.h)
 */
void count_rhs()
{
  rhs_count[nt_ndx]++; /* update number of re-writes for current non-terminal */
  if(rhs_count[nt_ndx] > MAXRULES)
    Die("grampiler error parsing rules: max number of production rules exceeded for %s\n", 
	curr_lhs);
}

/* ======================================================================
 * Function: nonterm_index_of()
 * Incept: Ray Lang, 11/1/2005 [St. Louis] 
 *
 * Purpose: lookup the index of a nonterminal in the grammar
 *          if the nonterminal is not found, it is added;
 *
 *          also performs consistency check for stack annotations
 *          grampiler dies if inconsistency is detected
 *
 *          grampiler dies if num_noterms exceeds MAXNT (defined on grammar.h)
 */
int nonterm_index_of(char* nt)
{
  int ndx;

  if(!strchr(nonterm_str,nt[0])) {
    ndx = num_nonterms; /* new nonterminal being added to end of nonterm_str */
    nonterm_str[num_nonterms++] = nt[0];
    nonterm_str[num_nonterms] = '\0';
    if ( is_stacking_nt(nt) ) {
      num_controlling_pairs[ndx] = nt[STACK_DEP_NDX] - '0';
      fprintf(stderr, "%s carries a stacking annotation\n", nt);
    }
    if ( num_nonterms > MAXNT ) {
      Die("grampiler error in nonterm_index_of(), max number of nonterms exceeded\n");
    }
  } else {
    ndx = 0; /* search for existing nonterminal */
    while(nonterm_str[ndx] != nt[0]) {
      ndx++;
    }
    if ( (is_stacking_nt(nt) && !num_controlling_pairs[ndx]) ||
	 (!is_stacking_nt(nt) && num_controlling_pairs[ndx]) )
      Die("grampiler error in nonterm_index_of(), nonterminal %c "
	  "used both with and without a stacking annotation\n", nt[0]);
    if ( is_stacking_nt(nt) && num_controlling_pairs[ndx] != (nt[STACK_DEP_NDX] - '0') )
      Die("grampiler error in nonterm_index_of(), nonterminal %c "
	  "used with conflicting stack annotations\n", nt[0]);
  }
  return ndx;
}

/* ======================================================================
 * Function: create_escore_array()
 * Incept: Ray Lang, 12/2/2005 [St. Louis] 
 *
 * Purpose: dynamically allocate an escores array
 *          and initialize all values to zero
 */
CYKVAL* create_escore_array(int n_emits, int n_depends)
{
  int scor_arr_siz = (int)pow(NUM_BASES,n_emits) * (int)pow(NUM_BASES,n_depends);
  CYKVAL* scor_arr = malloc(sizeof(CYKVAL) * scor_arr_siz); /* deallocated by caller */
  int i;

  for(i = 0; i < scor_arr_siz; i++)
    scor_arr[i] = 0;

  return scor_arr;
}

/* ======================================================================
 * Function: add_declared_edist()
 * Incept: Ray Lang, 11/18/2005 [St. Louis] 
 *
 * Purpose: process info in a edist declaration and
 *          save it in the global edist_info_list
 */
void add_declared_edist(char* nm, int n_emits, int n_depends)
{
  CYKVAL* scor_arr;

  /* check to make sure name is not already in use */
  EDIST_LIST current = edist_info_list;
  while(current && strcmp(current->name,nm) != 0) {
    current = current->next;
  }
  if(current)
    Die("grampiler error in add_declared_edist(), edist name %s previously declared\n", nm);
  
  /* name not found, so okay to add */
  fprintf(stderr, "adding named edist \'%s\' emitting %d depending on %d\n", 
	  nm, n_emits, n_depends);

  scor_arr = create_escore_array(n_emits,n_depends);
  edist_info_list = push_edist_info(n_emits, n_depends, nm, scor_arr, edist_info_list);
  free(scor_arr); /* allocated in create_escore_array() */
}

/* ======================================================================
 * Function: collect_edists()
 * Incept: Ray Lang, 11/18/2005 [St. Louis] 
 *
 * Purpose: links together all the spec_str_lists from the edist
 *          info nodes and attaches a SHALLOW COPY of the entire list
 *          to the second argument
 *
 *          return value is the number of emission distributions
 *
 *          function cross checks the index value in the info_nodes
 *          grampiler Dies if an index value is incorrect
 */
int collect_edists(EDIST_LIST edist_info_list, SPEC_STR_LIST* specs)
{
  SPEC_STR_LIST curr_spec = NULL;
  EDIST_LIST curr_info = edist_info_list;
  int edist_count = 0;

  *specs = NULL;
  
  /* grab the list from the first info node */
  if(curr_info) {
    if(curr_info->index != edist_count++)
      Die("grampiler error in collect_edists(), edist \'%s\'->index is %d, edist_count is %d\n",
	  curr_info->name, curr_info->index, edist_count);
    if(curr_info->use_count < 1) {
      fprintf(stderr, "Grampiler warning: no rewrite rules use edist \'%s\'\n",
	      curr_info->name);
    }
    /* initialize 2nd argument from 1st node's spec list */
    curr_spec = *specs = curr_info->spec_list;
    /* find last spec str node */
    while(curr_spec->next)
      curr_spec = curr_spec->next;
    /* advance to next info node */
    curr_info = curr_info->next;
  }
  
  /* attach lists from remaining info nodes */
  while(curr_info) {
    if(curr_info->index != edist_count++)
      Die("grampiler error in collect_edists(), edist \'%s\'->index is %d, edist_count is %d\n",
	  curr_info->name, curr_info->index, edist_count);
    if(curr_info->use_count < 1) {
      fprintf(stderr, "Grampiler warning: no rewrite rules use edist \'%s\'\n",
	      curr_info->name);
    }
    /* attach list to end of previous list */
    curr_spec->next = curr_info->spec_list;
    /* find last spec str node */
    while(curr_spec->next)
      curr_spec = curr_spec->next;
    /* advance to next info node */
    curr_info = curr_info->next;
  }  
  return edist_count++; /* zero-based indexing requires increment to calculate actual count */
}

/* ======================================================================
 * Function: append_default_edist()
 * Incept: Ray Lang, 11/22/2005 [St. Louis] 
 *
 * Purpose: create a default emission distribution and
 *          append it to the end of the edist_info_list
 *          return value is pointer to newly appended edist_info node
 */
EDIST_LIST append_default_edist(char* nm, int n_depends)
{
  EDIST_LIST new_edist = NULL, prev, curr;
  CYKVAL* scor_arr;

  /* create the node to append */
  if(strcmp(nm, "SINGLET") == 0) {
    assert(n_depends == 0);
    scor_arr = create_escore_array(1,n_depends);
    new_edist = push_edist_info(1, n_depends, "SINGLET", scor_arr, NULL);
  } else if(strcmp(nm, "PAIR") == 0) {
    assert(n_depends == 0);
    scor_arr = create_escore_array(2,n_depends);
    new_edist = push_edist_info(2, n_depends, "PAIR", scor_arr, NULL);
  } else if(strcmp(nm, "STACK") == 0) {
    assert(n_depends >= 2);
    scor_arr = create_escore_array(2,n_depends);
    new_edist = push_edist_info(2, n_depends, "STACK", scor_arr, NULL);
  } else
    Die("grampiler error in append_default_edist(), unknown edist type %s\n", nm);
  
  free(scor_arr); /* allocated in create_escore_array(), unneeded once new_edist node is set up */
  
  /* find end of edist_info_list */
  prev = NULL;
  curr = edist_info_list;
  if(!curr) { /* list is empty */
    edist_info_list = new_edist;
  } else {
    while(curr->next) { /* find end of list */
      prev = curr;
      curr = curr->next;
    }
    /* set index and attach new node */
    new_edist->index = curr->index + 1;
    curr->next = new_edist;
  }
  return new_edist;
}

/* ======================================================================
 * Function: find_default_edist()
 * Incept: Ray Lang, 11/10/2005 [St. Louis] 
 *
 * Purpose: find the index of the emission distribution of a given type
 *          and increment the use_count for the corresponding edist record
 *          this function creates the a default distribution if necessary
 */
int find_default_edist(char* nm, int n_depends)
{
  EDIST_LIST current = edist_info_list;

  if( (strcmp(nm,"SINGLET") != 0) && 
      (strcmp(nm,"PAIR") != 0) && 
      (strcmp(nm,"STACK") != 0) )
    {
      Die("grampiler error in find_default_edist(), unknown edist type \'%s\'\n", nm);
    }
  
  while(current && (strcmp(current->name,nm) != 0 || current->num_depends_on != n_depends)) {
    current = current->next;
  }

  if(!current) /* EITHER edist_info_list is empty OR edist not found */
    current = append_default_edist(nm, n_depends);
  
  current->use_count++;
  return current->index;
}

/* ======================================================================
 * Function: find_named_edist()
 * Incept: Ray Lang, 11/21/2005 [St. Louis] 
 *
 * Purpose: find the index of the emission distribution by name
 *          and increment the use_count for the corresponding edist record 
 *          grampiler Dies if named edist is not found
 */
int find_named_edist(char* nm, int n_emits, int n_depends)
{
  EDIST_LIST current = edist_info_list;
  
  if(!current)
    Die("grampiler error in find_named_edist(), edist_info_list is empty\n");

  while(current && strcmp(current->name,nm) != 0) {
    current = current->next;
  }

  if(!current)
    Die("grampiler error in find_named_edist(), edist \'%s\' not found\n", nm);

  assert( strcmp(current->name,nm) == 0 );

  if( (current->num_emitted != n_emits) ||
      (current->num_depends_on < n_depends) )
    Die("grampiler error in find_named_edist(), edist \'%s\' emits %d depending on %d, "
	"but atom emits %d depending on at least %d\n",
	nm, current->num_emitted, current->num_depends_on, n_emits, n_depends);
  
  current->use_count++;
  return current->index;
}

/* ======================================================================
 * Function: process_specified_scores();
 * Incept: Ray Lang, 11/8/2005 [St. Louis] 
 *
 * Purpose: assign any specified emission distribution scores to arrays,
 *          deallocate linked list of scores, construct linked list
 *          of field specifications for emission distrubutions
 */
void process_specified_scores()
{
  SCORE_LIST current, temp;

  current = scores;
  while(current) {
    switch(current->scor_typ) {
    case SINGLET:
      singlet_scores[current->index] = current->value;
      break;
    case BP:
      pair_scores[current->index] = current->value;
      break;
    case SP:
      stack_scores[current->index] = current->value;
      break;
    default:
      Die("Unknown score type encountered while processing specified emission scores");
      break;
    }
    temp = current;
    current = current->next;
    free(temp); /* allocated in push_score_node */
  }
  if(has_stacks) { /* assigned by check_for_scores() */
    edist_info_list = 
      push_edist_info(2, 2, "STACK", stack_scores, edist_info_list);
  }
  if(has_pairs) { /* assigned by check_for_scores() */
    edist_info_list = 
      push_edist_info(2, 0, "PAIR", pair_scores, edist_info_list);
  }
  edist_info_list = /* always set up a distribution for singlets */
    push_edist_info(1, 0, "SINGLET", singlet_scores, edist_info_list);
}

/* ======================================================================
 * Function: check_for_scores()
 * Incept: Ray Lang, 11/8/2005 [St. Louis] 
 *
 * Purpose: verify that if any individual emission distribution scores
 *          have been provided, then a default value for that type has
 *          also been provided -- if not, the grammar compiler Dies
 */
int check_for_scores()
{
  int inconsistent_singlet = singlet_score_given && !default_singlet_score_given;
  int inconsistent_bp = pair_score_given && !default_pair_score_given;
  int inconsistent_sp = stack_score_given && !default_stack_score_given;
  
  int scores_given = singlet_score_given || pair_score_given || stack_score_given;

  if(inconsistent_singlet)
    Die("Singlet score specified without an accompanying default");
    
  if(inconsistent_bp)
    Die("Base pair score specified without an accompanying default");

  if(inconsistent_sp)
    Die("Stack pair score specified without an accompanying default");

  has_stacks = default_stack_score_given;
  has_pairs = default_pair_score_given; 

  return scores_given;
}

/* ======================================================================
 * Function: push_score_node()
 * Incept: Ray Lang, 11/8/2005 [St. Louis] 
 *
 * Purpose: add a single score node to the front of a linked list
 */
SCORE_LIST push_score_node(enum score_type_e typ, 
			   int ndx, int val, SCORE_LIST scores)
{
  SCORE_LIST temp;
  
  temp = malloc(sizeof(struct SCORE_NODE)); /* deallocated on list traversal */
  temp->scor_typ = typ;
  temp->index    = ndx;
  temp->value    = val;
  temp->next     = scores;
  
  return temp;
}

/* ======================================================================
 * Function: push_str_node()
 * Incept: Ray Lang, 11/3/2005 [St. Louis] 
 *
 * Purpose: add a single spec string node to the front of a linked list
 */
SPEC_STR_LIST push_str_node(char *s, SPEC_STR_LIST lst)
{
  SPEC_STR_LIST temp;

  temp = malloc(sizeof(struct SPEC_STR_NODE)); /* deallocated on output */
  temp->next = lst;
  strcpy(temp->str,s);
  
  return temp;
}

/* ======================================================================
 * Function: push_edist_info() 
 * Incept: Ray Lang, 11/10/2005 [St. Louis] 
 *
 * Purpose: push tracking info for emission distributions to linked list
 */
EDIST_LIST push_edist_info(int n_emits, int n_depends, char* nm, 
			   CYKVAL* scor_arr, EDIST_LIST lst)
{
  EDIST_LIST temp = malloc(sizeof(struct EDIST_INFO_NODE)); /* freed in destroy_info_list() */

  /* temp->index          = 0; */ /* assigned in adjust_edist_indices() */
  temp->use_count      = 0;
  temp->num_emitted    = n_emits;
  temp->num_depends_on = n_depends;
  strcpy(temp->name,     nm);
  temp->spec_list      = push_edist(nm, n_emits, n_depends, (n_emits % 2 == 0), scor_arr, NULL);
  temp->next           = lst;
  return temp;
}

/* ======================================================================
 * Function: push_edist()
 * Incept: Ray Lang, 11/9/2005 [St. Louis] 
 *
 * Purpose: add emission distribution field specifications to linked list
 */
SPEC_STR_LIST push_edist(char *nm, int num_emitted, int num_depends_on, int is_base_pair, 
			 CYKVAL scores[], SPEC_STR_LIST lst)
{
  char s[MAX_STR_LEN];
  char temp_str[MAX_STR_LEN];
  int i, arr_siz;
  const int MAX_VALS_PER_LINE = 4;
  SPEC_STR_LIST temp_node, scors_lst = NULL;
  
  /* matrix size is 4^emitted * 4^num_depends_on */
  arr_siz = (int)pow(NUM_BASES,num_emitted) * (int)pow(NUM_BASES,num_depends_on);
  
  /* builds the *specs backwards, "pushing" them onto list */
  sprintf(s, ";%s\n",SPEC_ENDS);
  lst = push_str_node(s, lst);
  
  sprintf(s, ";EP_K;double;1;%d", arr_siz);
  lst = push_str_node(s, lst);
  
  /* scores array built "in-order" then flipped around backwards */
  sprintf(s, ";ESC_K;CYKVAL;1;%d", arr_siz);


  /* array values only need to be stored if there are non-zero values on the array */
  if( !is_all_zeroes(scores,arr_siz) ) {
    for(i = 0; i < arr_siz; i++) {
      sprintf(temp_str, ";%d", scores[i]);
      strcat(s,temp_str);
      
      if((i+1) < arr_siz && (i+1) % MAX_VALS_PER_LINE == 0) {
	sprintf(temp_str, ";%s", SPEC_CONTINUES);
	strcat(s,temp_str);
	scors_lst = push_str_node(s, scors_lst);
	strcpy(s,"");
      }
    }
  }

  if(strlen(s) > 0)
    scors_lst = push_str_node(s, scors_lst);
  /* flip scores list onto final list in reverse order */
  while(scors_lst) {
    temp_node = scors_lst;
    scors_lst = scors_lst->next;
    temp_node->next = lst;
    lst = temp_node;
  }
  
  sprintf(s, ";IS_BASEPAIR_K;int;0;%d", is_base_pair);
  lst = push_str_node(s, lst);
  
  sprintf(s, ";N_K;int;0;%d", num_emitted);
  lst = push_str_node(s, lst);

  /* for debugging the compiled grammar file */
  sprintf(s, "edist \'%s\', emitting %d, depending on %d", nm, num_emitted, num_depends_on);
  lst = push_str_node(s, lst);
  
  return lst;
}

/* ======================================================================
 * Function: build_top_level_fields()
 * Incept: Ray Lang, 11/7/2005 [St. Louis] 
 *
 * Purpose: construct linked list of spec strings for top level grammar fields
 */
SPEC_STR_LIST build_top_level_fields()
{
  SPEC_STR_LIST spec_str_lst = NULL;
  char s[MAX_STR_LEN];
  char temp[MAX_STR_LEN];
  int num_rules = 0;
  int i;

  for(i = 0; i < MAXNT; i++)
    num_rules += rhs_count[i];

  sprintf(s, ":LDIST_K:LDIST:1:0\n");
  spec_str_lst = push_str_node(s, spec_str_lst);

  sprintf(s, ":NLD_K:int:0:0\n");
  spec_str_lst = push_str_node(s, spec_str_lst);

  sprintf(s, ":RULE_MIN_K:int:2:%d:%d\n", MAXNT, MAXRULES);
  spec_str_lst = push_str_node(s, spec_str_lst);

  sprintf(s, ":NONTERM_MIN_K:int:1:%d\n", MAXNT);
  spec_str_lst = push_str_node(s, spec_str_lst);

  sprintf(s, ":TSC_K:CYKVAL:2:%d:%d\n", MAXNT, MAXRULES);
  spec_str_lst = push_str_node(s, spec_str_lst);

  sprintf(s, ":TP_K:double:2:%d:%d\n", MAXNT, MAXRULES);
  spec_str_lst = push_str_node(s, spec_str_lst);

  sprintf(s, ":TN_K:int:1:%d:%d\n", MAXNT, num_rules);
  spec_str_lst = push_str_node(s, spec_str_lst);

  sprintf(s, ":TDIST_IDX_K:int:1:%d\n", MAXNT);
  spec_str_lst = push_str_node(s, spec_str_lst);

  sprintf(s, ":NTD_K:int:0:1\n");
  spec_str_lst = push_str_node(s, spec_str_lst);

  sprintf(s, ":NRULES_K:int:1:%d", MAXNT);
  for(i = 0; i < num_nonterms; i++) {
    sprintf(temp, ":%d", rhs_count[i]);
    strcat(s,temp);
  }
  strcat(s,"\n");  
  spec_str_lst = push_str_node(s, spec_str_lst);

  sprintf(s, ":M_K:int:0:%d\n", num_nonterms);
  spec_str_lst = push_str_node(s, spec_str_lst);

  return spec_str_lst;
}

/* ======================================================================
 * Function: adjust_edist_indices()
 * Incept: Ray Lang, 11/18/2005 [St. Louis] 
 *
 * Purpose: compute and store the position each edist record
 *          will have in the compiled grammar's edist array
 *
 *          the edist's index number is required to link emission atoms 
 *          in the rewrite rules to the correct distribution table
 */
void adjust_edist_indices(EDIST_LIST info_list)
{
  EDIST_LIST current = info_list;
  int n = 0;

  while(current) {
    current->index = n++;
    current = current->next;
  }
}

/* ======================================================================
 * Function: set_rule_indices() 
 * Incept: Ray Lang, 12/5/2005 [St. Louis] 
 *
 * Purpose: add a rule's row & column indices to the spec list
 */
void set_rule_indices(int row, int col)
{ 
  char s[MAX_STR_LEN];

  sprintf(s, ";RULE_COL_NDX;int;0;%d",col);
  rule_specs = push_str_node(s, rule_specs);
  sprintf(s, ";RULE_ROW_NDX;int;0;%d",row);
  rule_specs = push_str_node(s, rule_specs);
}

/* ======================================================================
 * Function: add_rule_specs()
 * Incept: Ray Lang, 11/2/2005 [St. Louis] 
 *
 * Purpose: add field specs for a grammar production rule
 *          to the global linked list 'rule_specs'
 */
void add_rule_specs(int num_atoms, int is_allterms,
			  enum iterstate_e d1_state, 
			  enum iterstate_e d2_state)
{
  char s[MAX_STR_LEN];
  char temp[MAX_STR_LEN];
  int i,j; /* loop indices */

  /* builds the specs backwards, "pushing" them onto rule_specs */
  sprintf(s, ";%s\n",SPEC_ENDS);
  rule_specs = push_str_node(s, rule_specs);

  sprintf(s, ";ATOM_MIND_K;int;1;%d", MAXATOMS);
  rule_specs = push_str_node(s, rule_specs);

  sprintf(s, ";CONTEXT_K;int;2;%d;%d", MAXATOMS, MAXCOORD);
  for(i = 0; i < num_atoms; i++) {
    for(j = 0; j < MAXCOORD; j++) {
      sprintf(temp, ";%d", context[i][j]);
      strcat(s,temp);
    }
  }
  rule_specs = push_str_node(s, rule_specs);

  sprintf(s, ";OFFSET_K;int;2;%d;%d", MAXATOMS, MAXCOORD);
  for(i = 0; i < num_atoms; i++) {
    for(j = 0; j < MAXCOORD; j++) {
      sprintf(temp, ";%d", coord_ofst[i][j]);
      strcat(s,temp);
    }
  }
  rule_specs = push_str_node(s, rule_specs);

  sprintf(s, ";COORDBASE_K;int;2;%d;%d", MAXATOMS, MAXCOORD);
  for(i = 0; i < num_atoms; i++) {
    for(j = 0; j < MAXCOORD; j++) {
      sprintf(temp, ";%d", coord_base[i][j]);
      strcat(s,temp);
    }
  }
  rule_specs = push_str_node(s, rule_specs);

  sprintf(s, ";NCOORDS_K;int;1;%d", MAXATOMS);
  for(i = 0; i < num_atoms; i++) {
    sprintf(temp, ";%d", coords[i]);
    strcat(s,temp);
  }
  rule_specs = push_str_node(s, rule_specs);  

  sprintf(s, ";NTERM_IDX_K;int;1;%d", MAXATOMS);
  for(i = 0; i < num_atoms; i++) {
    sprintf(temp, ";%d", nterm[i]);
    strcat(s,temp);
  }
  rule_specs = push_str_node(s, rule_specs);  

  sprintf(s, ";LDIST_IDX_K;int;1;%d", MAXATOMS);
  for(i = 0; i < num_atoms; i++) {
    sprintf(temp, ";%d", ldist[i]);
    strcat(s,temp);
  }
  rule_specs = push_str_node(s, rule_specs);  

  sprintf(s, ";EDIST_IDX_K;int;1;%d", MAXATOMS);
  for(i = 0; i < num_atoms; i++) {
    sprintf(temp, ";%d", edist[i]);
    strcat(s,temp);
  }
  rule_specs = push_str_node(s, rule_specs);  

  sprintf(s, ";ATOMTYPE_K;int;1;%d", MAXATOMS);
  for(i = 0; i < num_atoms; i++) {
    sprintf(temp, ";%d", atom_type[i]);
    strcat(s,temp);
  }
  rule_specs = push_str_node(s, rule_specs);

  if(d2_state == ITERATOR_ON) {
    sprintf(s, ";D2_ITERATOR_MAX_K;int;0;%d", INT_MAX);
    rule_specs = push_str_node(s, rule_specs);
    sprintf(s, ";D2_ITERATOR_MIN_K;int;0;%d", 0);
    rule_specs = push_str_node(s, rule_specs);    
  }
  sprintf(s, ";D2_ITERATOR_STATE_K;int;0;%d", d2_state);
  rule_specs = push_str_node(s, rule_specs);

  if(d1_state == ITERATOR_ON) {
    sprintf(s, ";D1_ITERATOR_MAX_K;int;0;%d", INT_MAX);
    rule_specs = push_str_node(s, rule_specs);
    sprintf(s, ";D1_ITERATOR_MIN_K;int;0;%d", 0);
    rule_specs = push_str_node(s, rule_specs);    
  }
  sprintf(s, ";D1_ITERATOR_STATE_K;int;0;%d", d1_state);
  rule_specs = push_str_node(s, rule_specs);

  sprintf(s, ";IS_ALLTERMINALS_K;int;0;%d", is_allterms);
  rule_specs = push_str_node(s, rule_specs);

  sprintf(s, ";NATOMS_K;int;0;%d", num_atoms);
  rule_specs = push_str_node(s, rule_specs);

  return;
}

/* ======================================================================
 * Function: write_spec_str_list()
 * Incept: Ray Lang, 11/4/2005 [St. Louis] 
 *
 * Purpose: output linked list of field specification strings
 */
void write_spec_str_list(FILE* ofp, SPEC_STR_LIST lst)
{
  SPEC_STR_LIST current;

  current = lst;
  while(current) {
    fprintf(ofp, "%s\n", current->str);
    current = current->next;
  }
}

/* ======================================================================
 * Function: destroy_spec_list()
 * Incept: Ray Lang, 11/15/2005 [St. Louis] 
 *
 * Purpose: deallocate linked list of field specification strings
 *          returns number of nodes deallocated
 */
int destroy_spec_list(SPEC_STR_LIST lst)
{
  SPEC_STR_LIST current, temp;
  int num_freed = 0;

  current = lst;
  while(current) {
    temp = current;
    current = current->next;
    free(temp); /* allocated in push_str_node */
    num_freed++;
  }
  return num_freed;
}

/* ======================================================================
 * Function: destroy_info_list()
 * Incept: Ray Lang, 11/18/2005 [St. Louis] 
 *
 * Purpose: deallocate linked list of edist info nodes
 *          returns number of nodes deallocated
 */
int destroy_info_list(EDIST_LIST lst)
{
  EDIST_LIST current, temp;
  int num_freed = 0;
  
  current = lst;
  while(current) {
    temp = current;
    current = current->next;
    free(temp); /* allocated in push_edist_info */
    num_freed++;
  }
  return num_freed;
}
/* ======================================================================
 * Function: show_singlet_and_pair_scores() 
 * Incept: Ray Lang, 11/1/2005 [St. Louis] 
 *
 * Purpose: display the global static arrays used 
 *          for singlet & base pair emission scores  
 */
void show_singlet_and_pair_scores()
{
  int i;

  fprintf(stderr, "singlet_scores: ");
  for(i = 0; i < NUM_BASES; i++)
    fprintf(stderr, "[%d]: %d  ", i, singlet_scores[i]);
  fprintf(stderr, "\n");
  
  fprintf(stderr, "pair_scores: ");  
  for(i = 0; i < NUM_BASE_PAIRS; i++) {
    fprintf(stderr, "[%d]: %d  ", i, pair_scores[i]);
    if((i+1) % 4 == 0)
      fprintf(stderr, "\n");
  }
  fprintf(stderr, "\n");
}

/* ======================================================================
 * Function: show_stack_scores() 
 * Incept: Ray Lang, 11/1/2005 [St. Louis] 
 *
 * Purpose: display the global static array used for stacked pair emission scores 
 */
void show_stack_scores()
{
  int i;

  fprintf(stderr, "stack_scores: ");
  for(i = 0; i < NUM_STACKED_PAIRS; i++) {
    fprintf(stderr, "[%d]: %d  ", i, stack_scores[i]);
    if((i+1) % 4 == 0)
      fprintf(stderr, "\n");
  }
  fprintf(stderr, "\n");
}

/* ===== end of user-written code ======================================== */

%}

%token LHS NONTERM EPSILON EMITTER CHOICE GETS INT_VALUE
%token BASE BASE_DEFAULT BASE_PAIR BP_DEFAULT STACKED_PAIR SP_DEFAULT
%token EDIST_DECL EDIST_KEY SEPARATOR

%% /* ===== yacc grammar rules ======================================== */

rna_grammar :
     edists
     {
       /* N.B. scores must be processed PRIOR to parsing the rules
        *      so that emission distributions can be correctly
	*      indexed to rules during compilation
        */
       if(check_for_scores()) {
	 fprintf(stderr, "processing specified emission scores\n");
	 process_specified_scores();
	 edist_scores_specified = TRUE;
	 /* for diagnostic purposes only */
	 /* show_singlet_and_pair_scores();
	    show_stack_scores(); */
       } else {
	 edist_scores_specified = FALSE;
	 /* for diagnostic purposes only */
	 fprintf(stderr, "no emission scores were specified\n");
       }
       adjust_edist_indices(edist_info_list);
     }
     rules
     ;

edists:
     edist_decls scores;

edist_decls: /* empty */
     | edist_decls edist_decl
     ;

edist_decl:
     EDIST_DECL SEPARATOR INT_VALUE SEPARATOR INT_VALUE SEPARATOR EDIST_KEY
     {
       add_declared_edist($7, atoi($3), atoi($5));
     };

scores: /* empty */
     | scores score
     ;

score:
     singlet_edist_score
     |
     default_singlet_edist_score
     |
     bp_edist_score
     |
     default_bp_edist_score
     |
     sp_edist_score
     |
     default_sp_edist_score
     ;

singlet_edist_score:
     BASE GETS INT_VALUE
     {
       scores = push_score_node(SINGLET, base_from_string($1), atoi($3), scores);
       singlet_score_given = TRUE;
       fprintf(stderr, "base score detected: %s = %d\n", $1, atoi($3));
     };

default_singlet_edist_score:
     BASE_DEFAULT GETS INT_VALUE
     {
       int i;
       for(i = 0; i < NUM_BASES; i++)
	 singlet_scores[i] = atoi($3);
       default_singlet_score_given = TRUE;
       fprintf(stderr, "default singlet score is: %d\n", atoi($3));
     };
	 
bp_edist_score:
     BASE_PAIR GETS INT_VALUE
     {
       scores = push_score_node(BP, bp_from_string($1), atoi($3), scores);
       pair_score_given = TRUE;
       fprintf(stderr, "base pair score detected: %s = %d\n", $1, atoi($3));
     };

default_bp_edist_score:
     BP_DEFAULT GETS INT_VALUE
     {
       int i;
       for(i = 0; i < NUM_BASE_PAIRS; i++)
	 pair_scores[i] = atoi($3);
       default_pair_score_given = TRUE;
       fprintf(stderr, "default pair score is: %d\n", atoi($3));
     };

sp_edist_score:
     STACKED_PAIR GETS INT_VALUE
     {
       scores = push_score_node(SP, sp_from_string($1), atoi($3), scores);
       stack_score_given = TRUE;
       fprintf(stderr, "stacked pair score detected: %s = %d\n", $1, atoi($3));
     };

default_sp_edist_score:
     SP_DEFAULT GETS INT_VALUE
     {
       int i;
       for(i = 0; i < NUM_STACKED_PAIRS; i++)
	 stack_scores[i] = atoi($3);
       default_stack_score_given = TRUE;
       fprintf(stderr, "default stack score is: %d\n", atoi($3));
     };

rules: /* empty */
     | rules rule
     ; 

rule:
     LHS
     {
       /* N.B. call to nonterm_index_of() sets global nt_ndx, which must
        *      have the correct value PRIOR to parsing the rhs_list
        */
       rule_count++;
       strcpy(curr_lhs,$1); /* copy left-hand side to global string variable */
       nt_ndx = nonterm_index_of($1);
       fprintf(stderr, "\nnew left hand side is: %s\n", curr_lhs); /* diagnostic */
     }
     rhs_list
     ;

rhs_list: 
     right_hand_side
{
  count_rhs();
}
|
     right_hand_side
{
  count_rhs();
}
CHOICE rhs_list
;

right_hand_side:
     EPSILON
     {
       clear_rule_arrays();
       num_atoms = 1;
       atom_type[0] = EPSILON_ATOM;
       add_rule_specs(num_atoms,FALSE,ITERATOR_OFF,ITERATOR_OFF);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s", curr_lhs, $1);
       rule_specs = push_str_node(rule_str, rule_specs);
       /* diagnostic */
       fprintf(stderr, "RHS #1: %d atoms, empty string < %s >\n", num_atoms, $1);
     }
     |
     EMITTER
     {
       clear_rule_arrays();
       num_atoms = 1;
       atom_type[0] = EMISSION_ATOM; edist[0] = find_default_edist("SINGLET",0);
       add_rule_specs(num_atoms,TRUE,ITERATOR_OFF,ITERATOR_OFF);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s", curr_lhs, $1);
       rule_specs = push_str_node(rule_str, rule_specs);
       /* diagnostic */
       fprintf(stderr, "RHS #2: %d atoms, singlet < %s >\n", num_atoms, $1);
     }
     |
     EMITTER EDIST_KEY
     {
       clear_rule_arrays();
       num_atoms = 1;
       atom_type[0] = EMISSION_ATOM; edist[0] = find_named_edist($2,1,0); /* singlet emission */
       add_rule_specs(num_atoms,TRUE,ITERATOR_OFF,ITERATOR_OFF);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s %s", curr_lhs, $1, $2);
       rule_specs = push_str_node(rule_str, rule_specs);
       /* diagnostic */
       fprintf(stderr, "RHS #3: %d atoms, singlet with edist < %s %s >\n", num_atoms, $1, $2);
     }
     |
     NONTERM
     {
       ensure_nonstacking_nt($1);
       clear_rule_arrays();
       num_atoms = 1;
       atom_type[0] = NONTERMINAL_ATOM; nterm[0] = nonterm_index_of($1);
       add_rule_specs(num_atoms,FALSE,ITERATOR_OFF,ITERATOR_OFF);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s", curr_lhs, $1);
       rule_specs = push_str_node(rule_str, rule_specs);
       /* diagnostic */
       fprintf(stderr, "RHS #4: %d atoms, nonterm < %s >\n", num_atoms, $1);
     }
     |
     EMITTER NONTERM
     {
       ensure_nonstacking_nt($2);
       clear_rule_arrays(); 
       num_atoms = 2;
       atom_type[0] = EMISSION_ATOM; edist[0] = find_default_edist("SINGLET",0);
       atom_type[1] = NONTERMINAL_ATOM; nterm[1] = nonterm_index_of($2);
       coords[0] = 1; coords[1] = 2;
       /* I, I+1...J */
       coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
       coord_base[1][0] = COORD_I; coord_ofst[1][0] = 1;
       coord_base[1][1] = COORD_J; coord_ofst[1][1] = 0;
       add_rule_specs(num_atoms,FALSE,ITERATOR_OFF,ITERATOR_OFF);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s %s", curr_lhs, $1, $2);
       rule_specs = push_str_node(rule_str, rule_specs);
       /* diagnostic */
       fprintf(stderr, "RHS #5: %d atoms, singlet + nonterm < %s %s >\n", num_atoms, $1, $2);
     }
     |
     EMITTER NONTERM EDIST_KEY
     {
       ensure_nonstacking_nt($2);
       clear_rule_arrays();
       num_atoms = 2;
       atom_type[0] = EMISSION_ATOM; edist[0] = find_named_edist($3,1,0); /* singlet emission */
       atom_type[1] = NONTERMINAL_ATOM; nterm[1] = nonterm_index_of($2);
       coords[0] = 1; coords[1] = 2;
       /* I, I+1...J */
       coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
       coord_base[1][0] = COORD_I; coord_ofst[1][0] = 1;
       coord_base[1][1] = COORD_J; coord_ofst[1][1] = 0;
       add_rule_specs(num_atoms,FALSE,ITERATOR_OFF,ITERATOR_OFF);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s %s %s", curr_lhs, $1, $2, $3);
       rule_specs = push_str_node(rule_str, rule_specs);
       /* diagnostic */
       fprintf(stderr, "RHS #6: %d atoms, singlet + nonterm + edist < %s %s %s >\n", num_atoms, $1, $2, $3);
     }
     |
     NONTERM EMITTER
     { 
       ensure_nonstacking_nt($1);
       clear_rule_arrays();
       num_atoms = 2;
       atom_type[0] = NONTERMINAL_ATOM; nterm[0] = nonterm_index_of($1);
       atom_type[1] = EMISSION_ATOM; edist[1] = find_default_edist("SINGLET",0);
       coords[0] = 2; coords[1] = 1;
       /* I...J-1, J */
       coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
       coord_base[0][1] = COORD_J; coord_ofst[0][1] = -1;
       coord_base[1][0] = COORD_J; coord_ofst[1][0] = 0;
       add_rule_specs(num_atoms,FALSE,ITERATOR_OFF,ITERATOR_OFF);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s %s", curr_lhs, $1, $2);
       rule_specs = push_str_node(rule_str, rule_specs);
       /* diagnostic */
       fprintf(stderr, "RHS #7: %d atoms, nonterm + singlet < %s %s >\n", num_atoms, $1, $2);
     }
     |
     NONTERM EMITTER EDIST_KEY
     { 
       ensure_nonstacking_nt($1);
       clear_rule_arrays();
       num_atoms = 2;
       atom_type[0] = NONTERMINAL_ATOM; nterm[0] = nonterm_index_of($1);
       atom_type[1] = EMISSION_ATOM; edist[1] = find_named_edist($3,1,0); /* singlet emission */
       coords[0] = 2; coords[1] = 1;
       /* I...J-1, J */
       coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
       coord_base[0][1] = COORD_J; coord_ofst[0][1] = -1;
       coord_base[1][0] = COORD_J; coord_ofst[1][0] = 0;
       add_rule_specs(num_atoms,FALSE,ITERATOR_OFF,ITERATOR_OFF);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s %s %s", curr_lhs, $1, $2, $3);
       rule_specs = push_str_node(rule_str, rule_specs);
       /* diagnostic */
       fprintf(stderr, "RHS #8: %d atoms, nonterm + singlet + edist < %s %s %s >\n", num_atoms, $1, $2, $3);
     }
     |
     NONTERM NONTERM
     {
       ensure_nonstacking_nt($1);
       ensure_nonstacking_nt($2);
       clear_rule_arrays();
       num_atoms = 2;
       atom_type[0] = NONTERMINAL_ATOM; nterm[0] = nonterm_index_of($1);
       atom_type[1] = NONTERMINAL_ATOM; nterm[1] = nonterm_index_of($2);
       coords[0] = 2; coords[1] = 2;
       /* I, K...K+1, J */
       coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
       coord_base[0][1] = COORD_K; coord_ofst[0][1] = 0;
       coord_base[1][0] = COORD_K; coord_ofst[1][0] = 1;
       coord_base[1][1] = COORD_J; coord_ofst[1][1] = 0;
       add_rule_specs(num_atoms,FALSE,ITERATOR_ON,ITERATOR_OFF);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s %s", curr_lhs, $1, $2);
       rule_specs = push_str_node(rule_str, rule_specs);
       /* diagnostic */
       fprintf(stderr, "RHS #9: %d atoms, nonterm + nonterm < %s %s >\n", num_atoms, $1, $2);
     }
     |
     EMITTER NONTERM EMITTER
     { 
       clear_rule_arrays();
       if(is_base_pair($1, $3)) {
	 num_atoms = 2;
	 if(is_stacking_nt($2)) {
	   int depending_on = 2 * num_controlling_pairs[ nonterm_index_of($2) ];
	   atom_type[0] = EMISSION_ATOM; edist[0] = find_default_edist("STACK",depending_on);
	   /* diagnostic */
	   fprintf(stderr, "RHS #10: %d atoms, pair + stacking_nt < %s %s %s >\n", num_atoms, $1, $2, $3);
	 } else {
	   atom_type[0] = EMISSION_ATOM; edist[0] = find_default_edist("PAIR",0);
	   /* diagnostic */
	   fprintf(stderr, "RHS #11: %d atoms, pair + nonterm < %s %s %s >\n", num_atoms, $1, $2, $3);
	 }
	 atom_type[1] = NONTERMINAL_ATOM; nterm[1] = nonterm_index_of($2);
	 coords[0] = 2; coords[1] = 2;
	 /* I, I+1...J-1, J */
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[0][1] = COORD_J; coord_ofst[0][1] = 0;
	 coord_base[1][0] = COORD_I; coord_ofst[1][0] = 1;
	 coord_base[1][1] = COORD_J; coord_ofst[1][1] = -1;
       } else {
	 ensure_nonstacking_nt($2);
	 num_atoms = 3;
	 atom_type[0] = EMISSION_ATOM; edist[0] = find_default_edist("SINGLET",0);
	 atom_type[1] = NONTERMINAL_ATOM; nterm[1] = nonterm_index_of($2);
	 atom_type[2] = EMISSION_ATOM; edist[2] = find_default_edist("SINGLET",0);
	 coords[0] = 1; coords[1] = 2; coords[2] = 1;
	 /* I, I+1...J-1, J */
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[1][0] = COORD_I; coord_ofst[1][0] = 1;
	 coord_base[1][1] = COORD_J; coord_ofst[1][1] = -1;
	 coord_base[2][0] = COORD_J; coord_ofst[0][0] = 0;
	 /* diagnostic */
	 fprintf(stderr, "RHS #12: %d atoms, singlet + nonterm + singlet < %s %s %s >\n",
		 num_atoms, $1, $2, $3);
       }
       add_rule_specs(num_atoms,FALSE,ITERATOR_OFF,ITERATOR_OFF);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s %s %s", curr_lhs, $1, $2, $3);
       rule_specs = push_str_node(rule_str, rule_specs);
     }
     |
     EMITTER NONTERM EMITTER EDIST_KEY
     { 
       clear_rule_arrays();
       if(is_base_pair($1, $3)) {
	 num_atoms = 2;
	 if(is_stacking_nt($2)) {
	   int depending_on = 2 * num_controlling_pairs[ nonterm_index_of($2) ];
	   atom_type[0] = EMISSION_ATOM; edist[0] = find_named_edist($4,2,depending_on); /* stack emission */
	   /* diagnostic */
	   fprintf(stderr, "RHS #13: %d atoms, pair + stacking_nt + edist < %s %s %s %s >\n",
		   num_atoms, $1, $2, $3, $4);
	 } else {
	   atom_type[0] = EMISSION_ATOM; edist[0] = find_named_edist($4,2,0); /* pair emission */
	   /* diagnostic */
	   fprintf(stderr, "RHS #14: %d atoms, pair + nonterm + edist < %s %s %s %s >\n",
		   num_atoms, $1, $2, $3, $4);
	 }
	 atom_type[1] = NONTERMINAL_ATOM; nterm[1] = nonterm_index_of($2);
	 coords[0] = 2; coords[1] = 2;
	 /* I, I+1...J-1, J */
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[0][1] = COORD_J; coord_ofst[0][1] = 0;
	 coord_base[1][0] = COORD_I; coord_ofst[1][0] = 1;
	 coord_base[1][1] = COORD_J; coord_ofst[1][1] = -1;
       } else {
	 ensure_nonstacking_nt($2);
	 num_atoms = 3;
	 atom_type[0] = EMISSION_ATOM; edist[0] = find_named_edist($4,1,0); /* singlet emission */
	 atom_type[1] = NONTERMINAL_ATOM; nterm[1] = nonterm_index_of($2);
	 atom_type[2] = EMISSION_ATOM; edist[2] = find_named_edist($4,1,0); /* singlet emission */
	 coords[0] = 1; coords[1] = 2; coords[2] = 1;
	 /* I, I+1...J-1, J */
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[1][0] = COORD_I; coord_ofst[1][0] = 1;
	 coord_base[1][1] = COORD_J; coord_ofst[1][1] = -1;
	 coord_base[2][0] = COORD_J; coord_ofst[0][0] = 0;
	 /* diagnostic */
	 fprintf(stderr, "RHS #15: %d atoms, singlet + nonterm + singlet + edist < %s %s %s %s >\n",
		 num_atoms, $1, $2, $3, $4);
       }
       add_rule_specs(num_atoms,FALSE,ITERATOR_OFF,ITERATOR_OFF);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s %s %s %s", curr_lhs, $1, $2, $3, $4);
       rule_specs = push_str_node(rule_str, rule_specs);
     }
     |
     EMITTER NONTERM EMITTER EDIST_KEY EDIST_KEY
     { 
       if(is_base_pair($1, $3)) {
	 Die("grampiler error, rule for base pair emission has too many edist keys:\n"
	     "\t\t%s %s %s %s %s %s", curr_lhs, $1, $2, $3, $4, $5);
       } else {
	 ensure_nonstacking_nt($2);
	 clear_rule_arrays();
	 num_atoms = 3;
	 atom_type[0] = EMISSION_ATOM; edist[0] = find_named_edist($4,1,0); /* singlet emission */
	 atom_type[1] = NONTERMINAL_ATOM; nterm[1] = nonterm_index_of($2);
	 atom_type[2] = EMISSION_ATOM; edist[2] = find_named_edist($5,1,0); /* singlet emission */
	 coords[0] = 1; coords[1] = 2; coords[2] = 1;
	 /* I, I+1...J-1, J */
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[1][0] = COORD_I; coord_ofst[1][0] = 1;
	 coord_base[1][1] = COORD_J; coord_ofst[1][1] = -1;
	 coord_base[2][0] = COORD_J; coord_ofst[0][0] = 0;
       }
       add_rule_specs(num_atoms,FALSE,ITERATOR_OFF,ITERATOR_OFF);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s %s %s %s %s", curr_lhs, $1, $2, $3, $4, $5);
       rule_specs = push_str_node(rule_str, rule_specs);
       /* diagnostic */
       fprintf(stderr, "RHS #16: %d atoms, singlet + nonterm + singlet + 2 edists < %s %s %s %s %s >\n",
	       num_atoms, $1, $2, $3, $4, $5);
     }
     |
     EMITTER NONTERM EMITTER NONTERM
      {
       ensure_nonstacking_nt($4);
       clear_rule_arrays();
       if(is_base_pair($1, $3)) {
	 num_atoms = 3;
	 if(is_stacking_nt($2)) {
	   int depending_on = 2 * num_controlling_pairs[ nonterm_index_of($2) ];
	   atom_type[0] = EMISSION_ATOM; edist[0] = find_default_edist("STACK",depending_on);
	   /* diagnostic */
	   fprintf(stderr, "RHS #17: %d atoms, pair + stacking_nt + nonterm < %s %s %s %s >\n",
		   num_atoms, $1, $2, $3, $4);
	 } else {
	   atom_type[0] = EMISSION_ATOM; edist[0] = find_default_edist("PAIR",0);
	   /* diagnostic */
	   fprintf(stderr, "RHS #18: %d atoms, pair + nonterm + nonterm < %s %s %s %s >\n",
		   num_atoms, $1, $2, $3, $4);
	 }
	 atom_type[1] = NONTERMINAL_ATOM; nterm[1] = nonterm_index_of($2);
	 atom_type[2] = NONTERMINAL_ATOM; nterm[2] = nonterm_index_of($4);
	 coords[0] = 2; coords[1] = 2; coords[2] = 2;
	 /* I, I+1...K-1, K, K+1...J*/
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[0][1] = COORD_K; coord_ofst[0][1] = 0;
	 coord_base[1][0] = COORD_I; coord_ofst[1][0] = 1;
	 coord_base[1][1] = COORD_K; coord_ofst[1][1] = -1;
	 coord_base[2][0] = COORD_K; coord_ofst[2][0] = 1;
	 coord_base[2][1] = COORD_J; coord_ofst[2][1] = 0;
       } else {
	 ensure_nonstacking_nt($2);
	 num_atoms = 4;
	 atom_type[0] = EMISSION_ATOM; edist[0] = find_default_edist("SINGLET",0);
	 atom_type[1] = NONTERMINAL_ATOM; nterm[1] = nonterm_index_of($2);
	 atom_type[2] = EMISSION_ATOM; edist[2] = find_default_edist("SINGLET",0);
	 atom_type[3] = NONTERMINAL_ATOM; nterm[3] = nonterm_index_of($4);
	 coords[0] = 1; coords[1] = 2; coords[2] = 1; coords[3] = 2;
	 /* I, I+1...K-1, K, K+1...J*/
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[1][0] = COORD_I; coord_ofst[1][0] = 1;
	 coord_base[1][1] = COORD_K; coord_ofst[1][1] = -1;
	 coord_base[2][0] = COORD_K; coord_ofst[2][0] = 0;
	 coord_base[3][0] = COORD_K; coord_ofst[3][0] = 1;
	 coord_base[3][1] = COORD_J; coord_ofst[3][1] = 0;
	 /* diagnostic */
	 fprintf(stderr, "RHS #19: %d atoms, singlet + nonterm + singlet + nonterm < %s %s %s %s >\n",
		 num_atoms, $1, $2, $3, $4);
       }
       add_rule_specs(num_atoms,FALSE,ITERATOR_ON,ITERATOR_OFF);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s %s %s %s", curr_lhs, $1, $2, $3, $4);
       rule_specs = push_str_node(rule_str, rule_specs);
     }
     |
     EMITTER NONTERM EMITTER NONTERM EDIST_KEY
     {
       ensure_nonstacking_nt($4);
       clear_rule_arrays();
       if(is_base_pair($1, $3)) {
	 num_atoms = 3;
	 if(is_stacking_nt($2)) {
	   int depending_on = 2 * num_controlling_pairs[ nonterm_index_of($2) ];
	   atom_type[0] = EMISSION_ATOM; edist[0] = find_named_edist($5,2,depending_on); /* stack emission */
	   /* diagnostic */
	   fprintf(stderr, "RHS #20: %d atoms, pair + stacking_nt + nonterm + edist < %s %s %s %s %s >\n",
		   num_atoms, $1, $2, $3, $4, $5);
	 } else {
	   atom_type[0] = EMISSION_ATOM; edist[0] = find_named_edist($5,2,0); /* pair emission */
	   /* diagnostic */
	   fprintf(stderr, "RHS #21: %d atoms, pair + nonterm + nonterm + edist < %s %s %s %s %s >\n",
		   num_atoms, $1, $2, $3, $4, $5);
	 }
	 atom_type[1] = NONTERMINAL_ATOM; nterm[1] = nonterm_index_of($2);
	 atom_type[2] = NONTERMINAL_ATOM; nterm[2] = nonterm_index_of($4);
	 coords[0] = 2; coords[1] = 2; coords[2] = 2;
	 /* I, I+1...K-1, K, K+1...J*/
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[0][1] = COORD_K; coord_ofst[0][1] = 0;
	 coord_base[1][0] = COORD_I; coord_ofst[1][0] = 1;
	 coord_base[1][1] = COORD_K; coord_ofst[1][1] = -1;
	 coord_base[2][0] = COORD_K; coord_ofst[2][0] = 1;
	 coord_base[2][1] = COORD_J; coord_ofst[2][1] = 0;
       } else {
	 ensure_nonstacking_nt($2);
	 num_atoms = 4;
	 atom_type[0] = EMISSION_ATOM; edist[0] = find_named_edist($5,1,0); /* singlet emission */
	 atom_type[1] = NONTERMINAL_ATOM; nterm[1] = nonterm_index_of($2);
	 atom_type[2] = EMISSION_ATOM; edist[2] = find_named_edist($5,1,0); /* singlet emission */
	 atom_type[3] = NONTERMINAL_ATOM; nterm[3] = nonterm_index_of($4);
	 coords[0] = 1; coords[1] = 2; coords[2] = 1; coords[3] = 2;
	 /* I, I+1...K-1, K, K+1...J*/
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[1][0] = COORD_I; coord_ofst[1][0] = 1;
	 coord_base[1][1] = COORD_K; coord_ofst[1][1] = -1;
	 coord_base[2][0] = COORD_K; coord_ofst[2][0] = 0;
	 coord_base[3][0] = COORD_K; coord_ofst[3][0] = 1;
	 coord_base[3][1] = COORD_J; coord_ofst[3][1] = 0;
	 /* diagnostic */
	 fprintf(stderr, "RHS #22: %d atoms, singlet + nonterm + singlet + nonterm + edist < %s %s %s %s %s >\n",
		 num_atoms, $1, $2, $3, $4, $5);
       }
       add_rule_specs(num_atoms,FALSE,ITERATOR_ON,ITERATOR_OFF);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s %s %s %s", curr_lhs, $1, $2, $3, $4);
       rule_specs = push_str_node(rule_str, rule_specs);
     }
     |
     EMITTER NONTERM EMITTER NONTERM EDIST_KEY EDIST_KEY
     {
       if(is_base_pair($1, $3)) {
	 Die("grampiler error, rule for base pair emission has too many edist keys:\n"
	     "\t\t%s %s %s %s %s %s %s", curr_lhs, $1, $2, $3, $4, $5, $6);
       } else {
	 ensure_nonstacking_nt($2);
	 ensure_nonstacking_nt($4);
	 clear_rule_arrays();
	 num_atoms = 4;
	 atom_type[0] = EMISSION_ATOM; edist[0] = find_named_edist($5,1,0); /* singlet emission */
	 atom_type[1] = NONTERMINAL_ATOM; nterm[1] = nonterm_index_of($2);
	 atom_type[2] = EMISSION_ATOM; edist[2] = find_named_edist($6,1,0); /* singlet emission */
	 atom_type[3] = NONTERMINAL_ATOM; nterm[3] = nonterm_index_of($4);
	 coords[0] = 1; coords[1] = 2; coords[2] = 1; coords[3] = 2;
	 /* I, I+1...K-1, K, K+1...J*/
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[1][0] = COORD_I; coord_ofst[1][0] = 1;
	 coord_base[1][1] = COORD_K; coord_ofst[1][1] = -1;
	 coord_base[2][0] = COORD_K; coord_ofst[2][0] = 0;
	 coord_base[3][0] = COORD_K; coord_ofst[3][0] = 1;
	 coord_base[3][1] = COORD_J; coord_ofst[3][1] = 0;
	 /* diagnostic */
	 fprintf(stderr, "RHS #23: %d atoms, singlet + nonterm + singlet + nonterm + 2 edists "
		 "< %s %s %s %s %s %s >\n", num_atoms, $1, $2, $3, $4, $5, $6);
       }
       add_rule_specs(num_atoms,FALSE,ITERATOR_ON,ITERATOR_OFF);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s %s %s %s %s %s", curr_lhs, $1, $2, $3, $4, $5, $6);
       rule_specs = push_str_node(rule_str, rule_specs);
     }
     |
     NONTERM EMITTER NONTERM EMITTER
     {
       ensure_nonstacking_nt($1);
       clear_rule_arrays();
       if(is_base_pair($2, $4)) {
	 num_atoms = 3;
	 if(is_stacking_nt($3)) {
	   int depending_on = 2 * num_controlling_pairs[ nonterm_index_of($3) ];
	   atom_type[1] = EMISSION_ATOM; edist[1] = find_default_edist("STACK",depending_on);
	   /* diagnostic */
	   fprintf(stderr, "RHS #24: %d atoms, nonterm + pair + stacking_nt < %s %s %s %s >\n",
		   num_atoms, $1, $2, $3, $4);
	 } else {
	   atom_type[1] = EMISSION_ATOM; edist[1] = find_default_edist("PAIR",0);
	   /* diagnostic */
	   fprintf(stderr, "RHS #25: %d atoms, nonterm + pair + nonterm < %s %s %s %s >\n",
		   num_atoms, $1, $2, $3, $4);
	 }
	 atom_type[0] = NONTERMINAL_ATOM; nterm[0] = nonterm_index_of($1);
	 atom_type[2] = NONTERMINAL_ATOM; nterm[2] = nonterm_index_of($3);
	 coords[0] = 2; coords[1] = 2; coords[2] = 2;
	 /* I...K-1, K, K+1...J-1, J */
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[0][1] = COORD_K; coord_ofst[0][1] = -1;
	 coord_base[1][0] = COORD_K; coord_ofst[1][0] = 0;
	 coord_base[1][1] = COORD_J; coord_ofst[1][1] = 0;
	 coord_base[2][0] = COORD_K; coord_ofst[2][0] = 1;
	 coord_base[2][1] = COORD_J; coord_ofst[2][1] = -1;
       } else {
	 ensure_nonstacking_nt($3);
	 num_atoms = 4;
	 atom_type[0] = NONTERMINAL_ATOM; nterm[0] = nonterm_index_of($1);
	 atom_type[1] = EMISSION_ATOM; edist[1] = find_default_edist("SINGLET",0);
	 atom_type[2] = NONTERMINAL_ATOM; nterm[2] = nonterm_index_of($3);
	 atom_type[3] = EMISSION_ATOM; edist[3] = find_default_edist("SINGLET",0);
	 coords[0] = 2; coords[1] = 1; coords[2] = 2; coords[3] = 1;
	 /* I...K-1, K, K+1...J-1, J */
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[0][1] = COORD_K; coord_ofst[0][1] = -1;
	 coord_base[1][0] = COORD_K; coord_ofst[1][0] = 0;
	 coord_base[2][0] = COORD_K; coord_ofst[2][0] = 1;
	 coord_base[2][1] = COORD_J; coord_ofst[2][1] = -1;
	 coord_base[3][0] = COORD_J; coord_ofst[3][0] = 0;
	 /* diagnostic */
	 fprintf(stderr, "RHS #26: %d atoms, nonterm + singlet + nonterm + singlet < %s %s %s %s >\n",
		 num_atoms, $1, $2, $3, $4);	 
       }
       add_rule_specs(num_atoms,FALSE,ITERATOR_ON,ITERATOR_OFF);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s %s %s %s", curr_lhs, $1, $2, $3, $4);
       rule_specs = push_str_node(rule_str, rule_specs);
     }
     |
     NONTERM EMITTER NONTERM EMITTER EDIST_KEY
     {
       ensure_nonstacking_nt($1);
       clear_rule_arrays();
       if(is_base_pair($2, $4)) {
	 num_atoms = 3;
	 if(is_stacking_nt($3)) {
	   int depending_on = 2 * num_controlling_pairs[ nonterm_index_of($3) ];
	   atom_type[1] = EMISSION_ATOM; edist[1] = find_named_edist($5,2,depending_on); /* stack emission */
	   /* diagnostic */
	   fprintf(stderr, "RHS #27: %d atoms, nonterm + pair + stacking_nt + edist < %s %s %s %s %s >\n",
		   num_atoms, $1, $2, $3, $4, $5);
	 } else {
	   atom_type[1] = EMISSION_ATOM; edist[1] = find_named_edist($5,2,0); /* pair emission */
	   /* diagnostic */
	   fprintf(stderr, "RHS #28: %d atoms, nonterm + pair + nonterm + edist < %s %s %s %s %s >\n",
		   num_atoms, $1, $2, $3, $4, $5);
	 }
	 atom_type[0] = NONTERMINAL_ATOM; nterm[0] = nonterm_index_of($1);
	 atom_type[2] = NONTERMINAL_ATOM; nterm[2] = nonterm_index_of($3);
	 coords[0] = 2; coords[1] = 2; coords[2] = 2;
	 /* I...K-1, K, K+1...J-1, J */
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[0][1] = COORD_K; coord_ofst[0][1] = -1;
	 coord_base[1][0] = COORD_K; coord_ofst[1][0] = 0;
	 coord_base[1][1] = COORD_J; coord_ofst[1][1] = 0;
	 coord_base[2][0] = COORD_K; coord_ofst[2][0] = 1;
	 coord_base[2][1] = COORD_J; coord_ofst[2][1] = -1;
       } else {
	 ensure_nonstacking_nt($3);
	 num_atoms = 4;
	 atom_type[0] = NONTERMINAL_ATOM; nterm[0] = nonterm_index_of($1);
	 atom_type[1] = EMISSION_ATOM; edist[1] = find_named_edist($5,1,0); /* singlet emission */
	 atom_type[2] = NONTERMINAL_ATOM; nterm[2] = nonterm_index_of($3);
	 atom_type[3] = EMISSION_ATOM; edist[3] = find_named_edist($5,1,0); /* singlet emission */
	 coords[0] = 2; coords[1] = 1; coords[2] = 2; coords[3] = 1;
	 /* I...K-1, K, K+1...J-1, J */
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[0][1] = COORD_K; coord_ofst[0][1] = -1;
	 coord_base[1][0] = COORD_K; coord_ofst[1][0] = 0;
	 coord_base[2][0] = COORD_K; coord_ofst[2][0] = 1;
	 coord_base[2][1] = COORD_J; coord_ofst[2][1] = -1;
	 coord_base[3][0] = COORD_J; coord_ofst[3][0] = 0;
	 /* diagnostic */
	 fprintf(stderr, "RHS #29: %d atoms, nonterm + singlet + nonterm + singlet + edist "
		 "< %s %s %s %s %s >\n", num_atoms, $1, $2, $3, $4, $5);
       }
       add_rule_specs(num_atoms,FALSE,ITERATOR_ON,ITERATOR_OFF);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s %s %s %s %s", curr_lhs, $1, $2, $3, $4, $5);
       rule_specs = push_str_node(rule_str, rule_specs);
     }
     |
     NONTERM EMITTER NONTERM EMITTER EDIST_KEY EDIST_KEY
     {
       if(is_base_pair($2, $4)) {
	 Die("grampiler error, rule for base pair emission has too many edist keys:\n"
	     "\t\t%s %s %s %s %s %s %s", curr_lhs, $1, $2, $3, $4, $5, $6);
       } else {
	 ensure_nonstacking_nt($1);
	 ensure_nonstacking_nt($3);
	 clear_rule_arrays();
	 num_atoms = 4;
	 atom_type[0] = NONTERMINAL_ATOM; nterm[0] = nonterm_index_of($1);
	 atom_type[1] = EMISSION_ATOM; edist[1] = find_named_edist($5,1,0); /* singlet emission */
	 atom_type[2] = NONTERMINAL_ATOM; nterm[2] = nonterm_index_of($3);
	 atom_type[3] = EMISSION_ATOM; edist[3] = find_named_edist($6,1,0); /* singlet emission */
	 coords[0] = 2; coords[1] = 1; coords[2] = 2; coords[3] = 1;
	 /* I...K-1, K, K+1...J-1, J */
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[0][1] = COORD_K; coord_ofst[0][1] = -1;
	 coord_base[1][0] = COORD_K; coord_ofst[1][0] = 0;
	 coord_base[2][0] = COORD_K; coord_ofst[2][0] = 1;
	 coord_base[2][1] = COORD_J; coord_ofst[2][1] = -1;
	 coord_base[3][0] = COORD_J; coord_ofst[3][0] = 0;
	 /* diagnostic */
	 fprintf(stderr, "RHS #30: %d atoms, nonterm + singlet + nonterm + singlet + 2 edists "
		 "< %s %s %s %s %s %s >\n", num_atoms, $1, $2, $3, $4, $5, $6);
       }
       add_rule_specs(num_atoms,FALSE,ITERATOR_ON,ITERATOR_OFF);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s %s %s %s %s", curr_lhs, $1, $2, $3, $4, $5);
       rule_specs = push_str_node(rule_str, rule_specs);
     }
     |
     NONTERM EMITTER NONTERM EMITTER NONTERM
     {
       ensure_nonstacking_nt($1);
       ensure_nonstacking_nt($5);
       clear_rule_arrays();
       if(is_base_pair($2, $4)) {
	 num_atoms = 4;
	 if(is_stacking_nt($3)) {
	   int depending_on = 2 * num_controlling_pairs[ nonterm_index_of($3) ];
	   atom_type[1] = EMISSION_ATOM; edist[1] = find_default_edist("STACK",depending_on);
	   /* diagnostic */
	   fprintf(stderr, "RHS #31: %d atoms, nonterm + pair + stacking_nt + nonterm "
		   "< %s %s %s %s %s >\n", num_atoms, $1, $2, $3, $4, $5);
	 } else {
	   atom_type[1] = EMISSION_ATOM; edist[1] = find_default_edist("PAIR",0);
	   /* diagnostic */
	   fprintf(stderr, "RHS #32: %d atoms, nonterm + pair + nonterm + nonterm "
		   "< %s %s %s %s %s >\n", num_atoms, $1, $2, $3, $4, $5);
	 }
	 atom_type[0] = NONTERMINAL_ATOM; nterm[0] = nonterm_index_of($1);
	 atom_type[2] = NONTERMINAL_ATOM; nterm[2] = nonterm_index_of($3);
	 atom_type[3] = NONTERMINAL_ATOM; nterm[3] = nonterm_index_of($5);
	 coords[0] = 2; coords[1] = 2; coords[2] = 2; coords[3] = 2;
	 /* I...K-1, K, K+1...L-1, L, L+1...J */
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[0][1] = COORD_K; coord_ofst[0][1] = -1;
	 coord_base[1][0] = COORD_K; coord_ofst[1][0] = 0;
	 coord_base[1][1] = COORD_L; coord_ofst[1][1] = 0;
	 coord_base[2][0] = COORD_K; coord_ofst[2][0] = 1;
	 coord_base[2][1] = COORD_L; coord_ofst[2][1] = -1;
	 coord_base[3][0] = COORD_L; coord_ofst[3][0] = 1;
	 coord_base[3][1] = COORD_J; coord_ofst[3][1] = 0;
       } else {
	 ensure_nonstacking_nt($3);
	 num_atoms = 5;
	 atom_type[0] = NONTERMINAL_ATOM; nterm[0] = nonterm_index_of($1);
	 atom_type[1] = EMISSION_ATOM; edist[1] = find_default_edist("SINGLET",0);
	 atom_type[2] = NONTERMINAL_ATOM; nterm[2] = nonterm_index_of($3);
	 atom_type[3] = EMISSION_ATOM; edist[3] = find_default_edist("SINGLET",0);
	 atom_type[4] = NONTERMINAL_ATOM; nterm[4] = nonterm_index_of($5);
	 coords[0] = 2; coords[1] = 1; coords[2] = 2; coords[3] = 1; coords[3] = 2;
	 /* I...K-1, K, K+1...L-1, L, L+1...J */
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[0][1] = COORD_K; coord_ofst[0][1] = -1;
	 coord_base[1][0] = COORD_K; coord_ofst[1][0] = 0;
	 coord_base[2][0] = COORD_K; coord_ofst[2][0] = 1;
	 coord_base[2][1] = COORD_L; coord_ofst[2][1] = -1;
	 coord_base[3][0] = COORD_L; coord_ofst[3][0] = 0;
	 coord_base[4][0] = COORD_L; coord_ofst[4][0] = 1;
	 coord_base[4][1] = COORD_J; coord_ofst[4][1] = 0;
	 /* diagnostic */
	 fprintf(stderr, "RHS #33: %d atoms, nonterm + singlet + nonterm + singlet + nonterm "
		 "< %s %s %s %s %s >\n", num_atoms, $1, $2, $3, $4, $5);
       }
       add_rule_specs(num_atoms,FALSE,ITERATOR_ON,ITERATOR_ON);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s %s %s %s %s", curr_lhs, $1, $2, $3, $4, $5);
       rule_specs = push_str_node(rule_str, rule_specs);
     }
     |
     NONTERM EMITTER NONTERM EMITTER NONTERM EDIST_KEY
     {
       ensure_nonstacking_nt($1);
       ensure_nonstacking_nt($5);
       clear_rule_arrays();
       if(is_base_pair($2, $4)) {
	 num_atoms = 4;
	 if(is_stacking_nt($3)) {
	   int depending_on = 2 * num_controlling_pairs[ nonterm_index_of($3) ];
	   atom_type[1] = EMISSION_ATOM; edist[1] = find_named_edist($6,2,depending_on); /* stack emission */
	   /* diagnostic */
	   fprintf(stderr, "RHS #34: %d atoms, nonterm + pair + stacking_nt + nonterm + edist "
		   "< %s %s %s %s %s %s >\n", num_atoms, $1, $2, $3, $4, $5, $6);
	 } else {
	   atom_type[1] = EMISSION_ATOM; edist[1] = find_named_edist($6,2,0); /* pair emission */
	   /* diagnostic */
	   fprintf(stderr, "RHS #35: %d atoms, nonterm + pair + nonterm + nonterm + edist "
		   "< %s %s %s %s %s %s >\n", num_atoms, $1, $2, $3, $4, $5, $6);
	 }
	 atom_type[0] = NONTERMINAL_ATOM; nterm[0] = nonterm_index_of($1);
	 atom_type[2] = NONTERMINAL_ATOM; nterm[2] = nonterm_index_of($3);
	 atom_type[3] = NONTERMINAL_ATOM; nterm[3] = nonterm_index_of($5);
	 coords[0] = 2; coords[1] = 2; coords[2] = 2; coords[3] = 2;
	 /* I...K-1, K, K+1...L-1, L, L+1...J */
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[0][1] = COORD_K; coord_ofst[0][1] = -1;
	 coord_base[1][0] = COORD_K; coord_ofst[1][0] = 0;
	 coord_base[1][1] = COORD_L; coord_ofst[1][1] = 0;
	 coord_base[2][0] = COORD_K; coord_ofst[2][0] = 1;
	 coord_base[2][1] = COORD_L; coord_ofst[2][1] = -1;
	 coord_base[3][0] = COORD_L; coord_ofst[3][0] = 1;
	 coord_base[3][1] = COORD_J; coord_ofst[3][1] = 0;
       } else {
	 ensure_nonstacking_nt($3);
	 num_atoms = 5;
	 atom_type[0] = NONTERMINAL_ATOM; nterm[0] = nonterm_index_of($1);
	 atom_type[1] = EMISSION_ATOM; edist[1] = find_named_edist($6,1,0); /* singlet emission */
	 atom_type[2] = NONTERMINAL_ATOM; nterm[2] = nonterm_index_of($3);
	 atom_type[3] = EMISSION_ATOM; edist[3] = find_named_edist($6,1,0); /* singlet emission */
	 atom_type[4] = NONTERMINAL_ATOM; nterm[4] = nonterm_index_of($5);
	 coords[0] = 2; coords[1] = 1; coords[2] = 2; coords[3] = 1; coords[3] = 2;
	 /* I...K-1, K, K+1...L-1, L, L+1...J */
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[0][1] = COORD_K; coord_ofst[0][1] = -1;
	 coord_base[1][0] = COORD_K; coord_ofst[1][0] = 0;
	 coord_base[2][0] = COORD_K; coord_ofst[2][0] = 1;
	 coord_base[2][1] = COORD_L; coord_ofst[2][1] = -1;
	 coord_base[3][0] = COORD_L; coord_ofst[3][0] = 0;
	 coord_base[4][0] = COORD_L; coord_ofst[4][0] = 1;
	 coord_base[4][1] = COORD_J; coord_ofst[4][1] = 0;
	 /* diagnostic */
	 fprintf(stderr, "RHS #36: %d atoms, nonterm + singlet + nonterm + singlet + nonterm + edist "
		 "< %s %s %s %s %s %s >\n", num_atoms, $1, $2, $3, $4, $5, $6);
       }
       add_rule_specs(num_atoms,FALSE,ITERATOR_ON,ITERATOR_ON);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s %s %s %s %s %s", curr_lhs, $1, $2, $3, $4, $5, $6);
       rule_specs = push_str_node(rule_str, rule_specs);
     }
     |
     NONTERM EMITTER NONTERM EMITTER NONTERM EDIST_KEY EDIST_KEY
     {
       if(is_base_pair($2, $4)) {
	 Die("grampiler error, rule for base pair emission has too many edist keys:\n"
	     "\t\t%s %s %s %s %s %s %s %s", curr_lhs, $1, $2, $3, $4, $5, $6, $7);
       } else {
	 ensure_nonstacking_nt($1);
	 ensure_nonstacking_nt($3);
	 ensure_nonstacking_nt($5);
	 clear_rule_arrays();
	 num_atoms = 5;
	 atom_type[0] = NONTERMINAL_ATOM; nterm[0] = nonterm_index_of($1);
	 atom_type[1] = EMISSION_ATOM; edist[1] = find_named_edist($6,1,0); /* singlet emission */
	 atom_type[2] = NONTERMINAL_ATOM; nterm[2] = nonterm_index_of($3);
	 atom_type[3] = EMISSION_ATOM; edist[3] = find_named_edist($7,1,0); /* singlet emission */
	 atom_type[4] = NONTERMINAL_ATOM; nterm[4] = nonterm_index_of($5);
	 coords[0] = 2; coords[1] = 1; coords[2] = 2; coords[3] = 1; coords[3] = 2;
	 /* I...K-1, K, K+1...L-1, L, L+1...J */
	 coord_base[0][0] = COORD_I; coord_ofst[0][0] = 0;
	 coord_base[0][1] = COORD_K; coord_ofst[0][1] = -1;
	 coord_base[1][0] = COORD_K; coord_ofst[1][0] = 0;
	 coord_base[2][0] = COORD_K; coord_ofst[2][0] = 1;
	 coord_base[2][1] = COORD_L; coord_ofst[2][1] = -1;
	 coord_base[3][0] = COORD_L; coord_ofst[3][0] = 0;
	 coord_base[4][0] = COORD_L; coord_ofst[4][0] = 1;
	 coord_base[4][1] = COORD_J; coord_ofst[4][1] = 0;
       }
       add_rule_specs(num_atoms,FALSE,ITERATOR_ON,ITERATOR_ON);
       set_rule_indices(nt_ndx,rhs_count[nt_ndx]);
       /* copy rule to object file for reference */
       sprintf(rule_str, "%s --> %s %s %s %s %s %s %s", curr_lhs, $1, $2, $3, $4, $5, $6, $7);
       rule_specs = push_str_node(rule_str, rule_specs);
       /* diagnostic */
       fprintf(stderr, "RHS #37: %d atoms, nonterm + singlet + nonterm + singlet + nonterm + 2 edists "
	       "< %s %s %s %s %s %s %s >\n", num_atoms, $1, $2, $3, $4, $5, $6, $7);       
     }
     ;
