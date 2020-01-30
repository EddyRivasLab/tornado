/* grammar_io.c
 * implementation of SCFG compiler support functions for the TORNADO project
 *
 * Ray Lang, 10/11/2005 [St. Louis]
 */

#include "grammar_io.h"

/* copy/paste/uncomment the line below for a stop point */
/* { char junk; printf("\npaused, pressed <ENTER> to continue"); scanf("%c",&junk); } */

/* auxiliary functions not exported by this module */
char* next_data_spec(FILE*);
void raw_rule_dump(FILE*, RULE, int);
void raw_edist_dump(FILE*, EDIST);
void raw_ldist_dump(FILE*, LDIST);
FIELD_SPEC find_spec(SPEC_LIST, enum GRAMMAR_KEY);
void show_spec(FIELD_SPEC); /* for diagnostics only */

/* global constants, not exported */
int DEFAULT_INT = 0;
double DEFAULT_DOUBLE = 0.0;

/* ======================================================================
 * Function: read_compiled_grammar()
 * Incept: Ray Lang, 12/2/2005 [St. Louis] 
 *
 * Purpose: accept file name of compiled grammar
 *          return pointer to grammar structure
 */
GRAMMAR*
read_compiled_grammar(char* filnam)
{
  FILE *ifp;
  GRAMMAR* gp = NULL;

  if( (ifp = fopen(filnam, "r")) != NULL ) {
    /* fprintf(stderr, "%s now open for input\n", filnam); */
    gp = read_compiled_grammar_file(ifp);
    fclose(ifp);
    /* fprintf(stderr, "%s closed\n", filnam); */
  } else {
    Die("could not open %s for input", filnam);
  }
  return gp;
}

/* ======================================================================
 * Function: read_compiled_grammar_file()
 * Incept: Ray Lang, 10/17/2005 [St. Louis] 
 *
 * Purpose: build a grammar structure from an open input file stream
 */

GRAMMAR*
read_compiled_grammar_file(FILE* fp)
{
  /* prototypes of functions called only by this function */
  FIELD_SPEC parse_spec(FILE*, char*);
  GRAMMAR* grammar_struct_from_field_specs(FIELD_SPEC[]);
  void show_spec_array(FIELD_SPEC[]); /* for diagnostics only */
  
  /* local declarations */
  char* spec_str;
  FIELD_SPEC grammar_vals[NUM_GRAMMAR_KEYS] = {{0}};
  FIELD_SPEC spec;

  /* --------------- executable statements begin --------------- */
  while( (spec_str = next_data_spec(fp)) ) {
    spec = parse_spec(fp, spec_str);
    /* fprintf(stderr, "spec_str %s parsed\n", spec_str); */ /* diagnostic */
    grammar_vals[spec.fld_key] = spec;
    free(spec_str); /* allocated in next_data_spec() */
  }
  /* diagnostic
     show_spec_array(grammar_vals);
  */
  return grammar_struct_from_field_specs(grammar_vals);
}

/* ======================================================================
 * Function: grammar_struct_from_field_specs()
 * Incept: Ray Lang, 10/27/2005 [St. Louis] 
 *
 * Purpose: build a grammar structure from an open input file stream
 */
GRAMMAR*
grammar_struct_from_field_specs(FIELD_SPEC specs[])
{
  /* prototypes of functions called only by this function */
  EDIST edist_from_spec(SPEC_LIST);
  LDIST ldist_from_spec(SPEC_LIST);
  RULE rule_from_spec(SPEC_LIST);

  /* local declarations */
  GRAMMAR* g = Grammar_Create();
  int rows,cols; /* matrix dimensions */
  int i,j; /* loop indices */
  int offset; /* resolution of 2 dimensions to one */

  /* --------------- executable statements begin --------------- */
  /* scalar values */
  g->M = *(int *)(specs[M_K].vals);
  g->ntd = *(int *)(specs[NTD_K].vals);
  g->ned = *(int *)(specs[NED_K].vals);
  g->nld = *(int *)(specs[NLD_K].vals);
  
  /* arrays */
  rows = specs[NRULES_K].dim_sizes[0];
  for(i = 0; i < rows; i++) {
    g->nrules[i] = ((int *)specs[NRULES_K].vals)[i];
  }
  rows = specs[TDIST_IDX_K].dim_sizes[0];
  for(i = 0; i < rows; i++) {
    g->tdist_idx[i] = ((int *)specs[TDIST_IDX_K].vals)[i];
  }
  rows = specs[TN_K].dim_sizes[0];
  for(i = 0; i < rows; i++) {
    g->tn[i] = ((int *)specs[TN_K].vals)[i];
  }
  rows = specs[NONTERM_MIN_K].dim_sizes[0];
  for(i = 0; i < rows; i++) {
    g->nt_mind[i] = ((int *)specs[NONTERM_MIN_K].vals)[i];
  }

  /* matrices */
  rows = specs[TP_K].dim_sizes[0];
  cols = specs[TP_K].dim_sizes[1];
  for(i = 0; i < rows; i++) {
    for(j = 0; j < cols; j++) {
      offset = i * cols + j;
      g->tp[i][j] =  ((double *)specs[TP_K].vals)[offset];
    }
  }
  rows = specs[TSC_K].dim_sizes[0];
  cols = specs[TSC_K].dim_sizes[1];
  for(i = 0; i < rows; i++) {
    for(j = 0; j < cols; j++) {
      offset = i * cols + j;
      g->tsc[i][j] = ((CYKVAL *)specs[TSC_K].vals)[offset];
    }
  }
  rows = specs[RULE_MIN_K].dim_sizes[0];
  cols = specs[RULE_MIN_K].dim_sizes[1];
  for(i = 0; i < rows; i++) {
    for(j = 0; j < cols; j++) {
      offset = i * cols + j;
      g->rule_mind[i][j] = ((int *)specs[RULE_MIN_K].vals)[offset];
    }
  }

  /* structured fields: emission distribution list */
  rows = specs[EDIST_K].dim_sizes[0];
  g->edist = malloc(sizeof(EDIST) * rows);
  for(i = 0; i < rows; i++) {
    g->edist[i] = edist_from_spec(((SPEC_LIST *)specs[EDIST_K].vals)[i]);
  }

  /* structured fields: length distribution list */
  rows = specs[LDIST_K].dim_sizes[0];
  g->ldist = malloc(sizeof(LDIST) * rows);
  for(i = 0; i < rows; i++) {
    g->ldist[i] = ldist_from_spec(((SPEC_LIST *)specs[LDIST_K].vals)[i]);
    /* diagnostic
    printf("\nthe following ldist was assigned:\n");
    raw_ldist_dump(stdout,g->ldist[i]);
    */
  }

  /* production rules are handled differently from other matrices, since a rule's
   * the row and column coordinates are determined at compile time and stored
   * in each rule's spec list -- the row number corresponds to the index of the
   * nonterminal on the left hand side of the rule.
   */
  {
    SPEC_LIST rule_specs;
    FIELD_SPEC spec;
    int row, col, rule_count = 0;

    /* how many rules are there in the grammar? */
    for(i = 0; i < g->M; i++)
      rule_count += g->nrules[i];
    /* for that many rules, (1) get the spec, (2) find out the coordinates,
     * (3) place the rule at that position in the pr[][] matrix
     */
    for(i = 0; i < rule_count; i++) {
      rule_specs = ((SPEC_LIST *)specs[PR_K].vals)[i];
      spec = find_spec(rule_specs,RULE_ROW_NDX);
      row = *(int *)(spec.vals);
      spec = find_spec(rule_specs,RULE_COL_NDX);
      col = *(int *)(spec.vals);
      g->pr[row][col] = rule_from_spec(rule_specs);
    }
  }
  return g;
}

/* ======================================================================
 * Function: rule_from_spec()
 * Incept: Ray Lang, 10/27/2005 [St. Louis] 
 *
 * Purpose: construct a production rule from a spec list
 */
RULE
rule_from_spec(SPEC_LIST spc_lst)
{
  /* local declarations */
  RULE result = {0}; /* return value */
  int rows,cols; /* matrix dimensions */
  int i,j; /* loop indices */
  int offset; /* resolution of 2 dimensions to one */
  FIELD_SPEC spec; /* specification of field data */
  
  /* --------------- executable statements begin --------------- */
  
  /* N.B. must check after searching for each key because some
   *      of the fields in a rule structure might not be used
   */
  
  /* scalars */
  spec = find_spec(spc_lst,NATOMS_K);
  if(spec.fld_key == NATOMS_K) {
    result.natoms = *(int *)(spec.vals);
  }

  spec = find_spec(spc_lst,D1_ITERATOR_STATE_K);
  if(spec.fld_key == D1_ITERATOR_STATE_K) {
    result.d1_iterator_state = *(enum iterstate_e *)(spec.vals);
  }

  spec = find_spec(spc_lst,D1_ITERATOR_MIN_K);
  if(spec.fld_key == D1_ITERATOR_MIN_K) {
    result.d1_iterator_min = *(int *)(spec.vals);
  }

  spec = find_spec(spc_lst,D1_ITERATOR_MAX_K);
  if(spec.fld_key == D1_ITERATOR_MAX_K) {
    result.d1_iterator_max = *(int *)(spec.vals);
  }

  spec = find_spec(spc_lst,D2_ITERATOR_STATE_K);
  if(spec.fld_key == D2_ITERATOR_STATE_K) {
    result.d2_iterator_state = *(enum iterstate_e *)(spec.vals);
  }

  spec = find_spec(spc_lst,D2_ITERATOR_MIN_K);
  if(spec.fld_key == D2_ITERATOR_MIN_K) {
    result.d2_iterator_min = *(int *)(spec.vals);
  }

  spec = find_spec(spc_lst,D2_ITERATOR_MAX_K);
  if(spec.fld_key == D2_ITERATOR_MAX_K) {
    result.d2_iterator_max = *(int *)(spec.vals);
  }

  spec = find_spec(spc_lst,IS_ALLTERMINALS_K);
  if(spec.fld_key == IS_ALLTERMINALS_K) {
    result.is_allterminals = *(int *)(spec.vals);
  }

  /* vectors */
  spec = find_spec(spc_lst,ATOMTYPE_K);
  if(spec.fld_key == ATOMTYPE_K) {
    rows = spec.dim_sizes[0];
    for(i = 0; i < rows; i++)
      result.atomtype[i] = ((enum atom_e *)spec.vals)[i];
  }

  spec = find_spec(spc_lst,EDIST_IDX_K);
  if(spec.fld_key == EDIST_IDX_K) {
    rows = spec.dim_sizes[0];
    for(i = 0; i < rows; i++)
      result.edist_idx[i] = ((int *)spec.vals)[i];
  }
  
  spec = find_spec(spc_lst,LDIST_IDX_K);
  if(spec.fld_key == LDIST_IDX_K) {
    rows = spec.dim_sizes[0];
    for(i = 0; i < rows; i++)
      result.ldist_idx[i] = ((int *)spec.vals)[i];
  }
  
  spec = find_spec(spc_lst,NTERM_IDX_K);
  if(spec.fld_key == NTERM_IDX_K) {
    rows = spec.dim_sizes[0];
    for(i = 0; i < rows; i++)
      result.nterm_idx[i] = ((int *)spec.vals)[i];
  }
  
  spec = find_spec(spc_lst,NCOORDS_K);
  if(spec.fld_key == NCOORDS_K) {
    rows = spec.dim_sizes[0];
    for(i = 0; i < rows; i++)
      result.ncoords[i] = ((int *)spec.vals)[i];
  }
  
  spec = find_spec(spc_lst,ATOM_MIND_K);
  if(spec.fld_key == ATOM_MIND_K) {
    rows = spec.dim_sizes[0];
    for(i = 0; i < rows; i++)
      result.atom_mind[i] = ((int *)spec.vals)[i];
  }

  /* matrices */
  spec = find_spec(spc_lst,COORDBASE_K);
  if(spec.fld_key == COORDBASE_K) {
    rows = spec.dim_sizes[0];
    cols = spec.dim_sizes[1];
    for(i = 0; i < rows; i++) {
      for(j = 0; j < cols; j++) {
	offset = i * cols + j;
	result.coordbase[i][j] = ((int *)spec.vals)[offset]; 
      }
    }
  }

  spec = find_spec(spc_lst,OFFSET_K);
  if(spec.fld_key == OFFSET_K) {
    rows = spec.dim_sizes[0];
    cols = spec.dim_sizes[1];
    for(i = 0; i < rows; i++) {
      for(j = 0; j < cols; j++) {
	offset = i * cols + j;
	result.offset[i][j] = ((int *)spec.vals)[offset];
      }
    }
  }
  
  spec = find_spec(spc_lst,CONTEXT_K);
  if(spec.fld_key == CONTEXT_K) {
    rows = spec.dim_sizes[0];
    cols = spec.dim_sizes[1];
    for(i = 0; i < rows; i++) {
      for(j = 0; j < cols; j++) {
	offset = i * cols + j;
	result.context[i][j] = ((int *)spec.vals)[offset];
      }
    }
  }

  return result;
}

/* ======================================================================
 * Function: edist_from_spec()
 * Incept: Ray Lang, 10/27/2005 [St. Louis] 
 *
 * Purpose: construct an emission distribution from a spec list
 */
EDIST
edist_from_spec(SPEC_LIST spc_lst)
{
  /* local declarations */
  EDIST result; /* return value */
  int i; /* loop counter */
  int vec_len; /* vector length */
  FIELD_SPEC spec; /* specification of field data */

  /* --------------- executable statements begin --------------- */
  /* scalar: number of residues emitted */
  spec = find_spec(spc_lst,N_K);
  result.n = *(int *)(spec.vals);
  
  /* scalar: TRUE if n == 2 and x,x' are annotated as base pair */
  spec = find_spec(spc_lst,IS_BASEPAIR_K); 
  result.is_basepair = *(int *)(spec.vals);

  /* vector: probability distributions */
  spec = find_spec(spc_lst,EP_K);
  vec_len = spec.dim_sizes[0];
  result.ep = malloc(sizeof(double) * vec_len);
  for(i = 0; i < vec_len; i++)
    result.ep[i] = ((double *)spec.vals)[i];
  
  /* vector: CYK scores */
  spec = find_spec(spc_lst,ESC_K);
  vec_len = spec.dim_sizes[0];
  result.esc = malloc(sizeof(CYKVAL) * vec_len);
  for(i = 0; i < vec_len; i++)
    result.esc[i] = ((CYKVAL *)spec.vals)[i];

  return result;
}

/* ======================================================================
 * Function: ldist_from_spec()
 * Incept: Ray Lang, 10/27/2005 [St. Louis] 
 *
 * Purpose: construct a length distribution from a spec list
 *
 * N.B. SINCE LENGTH DISTRIBUTIONS ARE NOT USUALLY SPECIFIED WITH
 *      THE GRAMMAR, THIS FUNCTION HAS NOT BEEN TESTED
 */
LDIST
ldist_from_spec(SPEC_LIST spc_lst)
{
  /* local declarations */
  LDIST result; /* return value */
  int i; /* loop counter */
  int vec_len; /* vector length */
  FIELD_SPEC spec; /* specification of field data */

  /* --------------- executable statements begin --------------- */
  /* scalar: min length w/ prob > 0 */
  spec = find_spec(spc_lst,MIN_K);
  result.min = *(int *)(spec.vals);
  
  /* scalar: max length w/ prob > 0 */
  spec = find_spec(spc_lst,MAX_K); 
  result.max = *(int *)(spec.vals);

  /* vector: probability distributions */
  spec = find_spec(spc_lst,LP_K);
  vec_len = spec.dim_sizes[0];
  result.lp = malloc(sizeof(double) * vec_len);
  for(i = 0; i < vec_len; i++)
    result.lp[i] = ((double *)spec.vals)[i];
  
  /* vector: CYK scores */
  spec = find_spec(spc_lst,LSC_K);
  vec_len = spec.dim_sizes[0];
  result.lsc = malloc(sizeof(CYKVAL) * vec_len);
  for(i = 0; i < vec_len; i++)
    result.lsc[i] = ((CYKVAL *)spec.vals)[i];

  return result;
}

/* ======================================================================
 * Function: find_spec()
 * Incept: Ray Lang, 10/27/2005 [St. Louis] 
 *
 * Purpose: retrieve a spec by key from a spec list
 */
FIELD_SPEC
find_spec(SPEC_LIST spc_lst, enum GRAMMAR_KEY key)
{
  /* local declarations */
  FIELD_SPEC unused_key; /* return value when key is not found */
  SPEC_LIST current; /* list pointer */

  /* --------------- executable statements begin --------------- */
  unused_key.fld_key = ZERO_KEY;
  
  for(current = spc_lst;
      current && current->spec.fld_key != key;
      current = current->next);

  if(current)
    return current->spec;
  else
    return unused_key;
}

/* ======================================================================
 * Function: parse_spec()
 * Incept: Ray Lang, 10/25/2005 [St. Louis] 
 *
 * Purpose: construct field spec for a grammar struct from a string
 *
 * N.B. mututally recursive with construct_nested_spec()
 */
FIELD_SPEC 
parse_spec(FILE* fp, char* spec)
{
  /* prototype of function called only by this function */
  SPEC_LIST construct_nested_spec(FILE*);

  /* local declarations */
  FIELD_SPEC result;
  int num_datums; /* number of pieces of data in the spec */
  int arr_siz = 1; /* max array size for this spec */
  int spec_len = strlen(spec);
  int i; /* loop counter */

  /* --------------- executable statements begin --------------- */
  /* count number of pieces of data in the string */
  num_datums = 0;
  for(i = 0; i < spec_len; i++)
    if(spec[i] == ':' || spec[i] == ';')
      num_datums++;

  /* get field key */
  result.fld_key = key_from_string(strtok(spec,":;"));
  num_datums--; /* count down number of datums remaining */

  /* get type string */
  strcpy(result.type_str,strtok(NULL,":;"));
  num_datums--;

  /* get number of dimensions */
  result.num_dim = atoi( strtok(NULL,":;") );
  num_datums--;

  /* allocate dimensions array */
  if(result.num_dim > 0)
    result.dim_sizes = malloc(sizeof(int) * result.num_dim);
  else
    result.dim_sizes = NULL;

  /* get dimension sizes */
  for(i = 0; i < result.num_dim; i++) {
    result.dim_sizes[i] = atoi( strtok(NULL,":;") );   /* dimension size */
    arr_siz *= result.dim_sizes[i];
    num_datums--;
  }

  /* allocate values array */
  if(strcmp(result.type_str,"int") == 0 || strcmp(result.type_str,"CYKVAL") == 0)
    result.vals = malloc(sizeof(int) * arr_siz);
  else if(strcmp(result.type_str,"double") == 0)
    result.vals = malloc(sizeof(double) * arr_siz);
  else if(strcmp(result.type_str,"EDIST") == 0)
    result.vals = malloc(sizeof(EDIST) * arr_siz);
  else if(strcmp(result.type_str,"LDIST") == 0)
    result.vals = malloc(sizeof(LDIST) * arr_siz);
  else if(strcmp(result.type_str,"RULE") == 0)
    result.vals = malloc(sizeof(RULE) * arr_siz);

  /* get scalar values, N.B. for nested structures, num_datums is zero 
   * (nested structures are on separate lines) so loop below doesn't execute
   */
  for(i = 0; i < num_datums; i++) {
    if(strcmp(result.type_str,"int") == 0 || strcmp(result.type_str,"CYKVAL") == 0) {
      ((int *)result.vals)[i] = atoi(strtok(NULL,":;"));
    } else if(strcmp(result.type_str,"double") == 0) {
      ((double *)result.vals)[i] = atof(strtok(NULL,":;"));
    }
  }

  /* fill remainder of array with default values or get structured values */
  if(strcmp(result.type_str,"int") == 0 || strcmp(result.type_str,"CYKVAL") == 0)
    for(; i < arr_siz; i++) ((int *)result.vals)[i] = DEFAULT_INT;

  else if(strcmp(result.type_str,"double") == 0)
    for(; i < arr_siz; i++) ((double *)result.vals)[i] = DEFAULT_DOUBLE;

  else  /* nested structure (RULE, EDIST, or LDIST) */
    for(i = 0; i < arr_siz; i++) ((SPEC_LIST *)result.vals)[i] = construct_nested_spec(fp);

  return result;
}

/* ======================================================================
 * Function: construct_nested_spec()
 * Incept: Ray Lang, 10/25/2005 [St. Louis] 
 *
 * Purpose: construct field spec for a nested field in the grammar struct
 *
 * N.B. mututally recursive with parse_spec()
 */
SPEC_LIST construct_nested_spec(FILE* fp)
{
  /* local declarations */
  SPEC_LIST top = NULL, temp;
  FIELD_SPEC nested_spec;
  char* spec_str;

  /* --------------- executable statements begin --------------- */
  while( (spec_str = next_data_spec(fp)) && !strstr(spec_str,SPEC_ENDS)) {
    nested_spec = parse_spec(fp, spec_str);
    temp = malloc(sizeof(struct SPEC_NODE));
    temp->spec = nested_spec;
    temp->next = top;
    top = temp;
    free(spec_str); /* allocated in next_data_spec() */
  }
  free(spec_str); /* free 'SPEC_ENDS' allocated in next_data_spec() */
  return top;
}

/* ======================================================================
 * Function: show_spec_array()
 * Incept: Ray Lang, 10/26/2005 [St. Louis] 
 *
 * Purpose: display the array of grammar structure field specifications
 */
void
show_spec_array(FIELD_SPEC a[])
{
  /* local declaration */
  int i;
  
  /* --------------- executable statements begin --------------- */
  for(i = 0; i < NUM_GRAMMAR_KEYS; i++) {
    if(a[i].fld_key != ZERO_KEY)
      show_spec(a[i]);
  }
  return;
}

/* ======================================================================
 * Function: show_spec()
 * Incept: Ray Lang, 10/17/2005 [St. Louis] 
 *
 * Purpose: display a specification for a grammar structure field
 * function calls itself recursively if there are nested specs
 */
void
show_spec(FIELD_SPEC s)
{
  /* local declarations */
  char buffer[MAX_STR_LEN];
  int i; /* loop counter */
  int val_count = 1; /* total number of values in the field */

  /* --------------- executable statements begin --------------- */
  printf("show_spec, field key is: %s\n",str_from_key(buffer,s.fld_key));
  printf("         type string is: %s\n",s.type_str);
  printf("            num dims is: %d\n",s.num_dim);
  if(s.num_dim > 0) { /* field is non-scalar */
    printf("      dimension size(s): ");
    for(i = 0; i < s.num_dim; i++) {
      val_count *= s.dim_sizes[i]; /* compute number of values in the array */
      printf("%d     ",s.dim_sizes[i]);
    }
    printf("\n");
  }
  printf("       the value(s) are: ");
  if(strcmp(s.type_str,"int") == 0 || strcmp(s.type_str,"CYKVAL") == 0)
    for(i = 0; i < val_count; i++) {
      printf("%d   ",((int *)s.vals)[i]);
    }
  else if(strcmp(s.type_str,"double") == 0)
    for(i = 0; i < val_count; i++) {
      printf("%.2f   ",((double *)s.vals)[i]);
    }
  else /* nested structure (RULE, EDIST, or LDIST) */
    for(i = 0; i < val_count; i++) {
      printf("nested structure below\n");
      SPEC_LIST top = ((SPEC_LIST *)s.vals)[i];
      while( top ) {
	show_spec(top->spec);
	top = top->next;
      }
    }
  printf("\n\n");
}

/* ======================================================================
 * Function: next_data_spec()
 * Incept: Ray Lang, 10/12/2005 [St. Louis] 
 *
 * Purpose: read from a compiled SCFG object file, 
 * compose a specification string for a grammar structure field.
 *
 * N.B. info in the object file pertaining to a single grammar field may be
 * broken across multiple lines
 *
 */
char* 
next_data_spec(FILE* fp)
{
  /* prototypes of functions called only by this function */
  int is_spec(char* s);

  /* local declarations */
  char buffer[MAX_STR_LEN] = {0};
  int ttl_len = 0, node_count = 0, end_of_spec = FALSE;
  char *result;
  SPEC_STR_LIST head = NULL, current, temp;

  /* --------------- executable statements begin --------------- */
  while (!end_of_spec) {
    fgets(buffer, MAX_STR_LEN, fp);
    /* build linked list of spec strings */
    if( is_spec(buffer) ) {
      if(!head) {/* first node */
	head = malloc(sizeof(struct SPEC_STR_NODE)); /* deallocated below */
	strcpy(head->str,buffer);
	head->next = NULL;
	current = head;
	node_count = 1;
      } else { /* subsequent nodes */
	temp = malloc(sizeof(struct SPEC_STR_NODE)); /* deallocated below */
	strcpy(temp->str,buffer);
	temp->next = NULL;
	current->next = temp;
	current = temp;
	node_count++;
      } 
      ttl_len += strlen(buffer); /* accumulate total length for composed string */
    }
    end_of_spec = feof(fp) || (is_spec(buffer) && !strstr(buffer,SPEC_CONTINUES));
  }
  
  /* compose all the separate lines into a single spec string */
  if( node_count >= 1) {
    result = malloc(sizeof(char) * ttl_len + 1); /* deallocated by caller */
    result[0] = '\0'; /* prepare for calls to strcat() below */
  } else {
    result = NULL;
  }

  if( node_count == 1 ) { /* spec did not continue across multiple lines */
    strcpy(result,head->str);
    free(head);
  } else if( node_count > 1 ) { /* spec continued across multiple lines */
    char *end_ptr;
    current = head;
    while(current) {
      temp = current;
      strcat(result,current->str);
      end_ptr = strstr(result,SPEC_CONTINUES);
      if(end_ptr) *(end_ptr-1) = '\0'; /* truncate semicolcon and continuation marker */
      current = current->next;
      free(temp);
    }
  }
  return result;
}

/* ======================================================================
 * Function: is_spec()
 * Incept: Ray Lang, 10/12/2005 [St. Louis] 
 *
 * Purpose: determine whether a c-string is a grammar struct field specification
 */
int is_spec(char* s)
{
  return s[0] == ':' || s[0] == ';';
}

/* ======================================================================
 * Function: raw_grammar_dump()
 * Incept: Ray Lang, 10/24/2005 [St. Louis] 
 *
 * Purpose: write to a file condensed "raw" grammar values
 * labeled according to struct field names
 *
 * cf. raw_grammar_dump1 for explanation of "condensed"
 */
void 
raw_grammar_dump(FILE *fp, GRAMMAR *G)
{
  raw_grammar_dump1(fp, G, TRUE);
}

/* ======================================================================
 * Function: raw_grammar_dump1()
 * Incept: Ray Lang, 10/12/2005 [St. Louis] 
 *
 * Purpose: write to a file "raw" grammar values
 * labeled according to struct field names
 *
 * 3rd argument controls whether to condense the output to only those
 * fields used by the grammar or to show values of all fields
 * TRUE: show only struct members in use
 * FALSE: show all struct members
 */
void 
raw_grammar_dump1(FILE *fp, GRAMMAR *G, int condense)
{
  /* local declarations */
  int r,c;

  /* --------------- executable statements begin --------------- */
  fprintf(fp, "G->M: %d\n", G->M);
  fprintf(fp, "\n");

  fprintf(fp, "G->pr matrix ----------------------------------------\n");
  for(r = 0; r < (condense ? G->M : MAXNT); r++)
    for(c = 0; c < (condense ? G->nrules[r] : MAXRULES); c++) {
      fprintf(fp, "G->pr[%d][%d]:\t", r, c);
      raw_rule_dump(fp, G->pr[r][c],condense);
      fprintf(fp, "- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    }

  fprintf(fp, "G->nrules array ----------------------------------------\n");
  for(r = 0; r < (condense ? G->M : MAXNT); r++)
    fprintf(fp, "[%d]: %d\t", r, G->nrules[r]);
  fprintf(fp, "\n\n");

  fprintf(fp, "G->tdist_idx array ----------------------------------------\n");
  for(r = 0; r < (condense ? G->M : MAXNT); r++)
    fprintf(fp, "[%d]: %d\t", r, G->tdist_idx[r]);  
  fprintf(fp, "\n\n");

  fprintf(fp, "G->ntd: %d\n", G->ntd);
  fprintf(fp, "\n");

  fprintf(fp, "G->tn array ----------------------------------------\n");
  for(r = 0; r < (condense ? G->M : MAXNT); r++)
    fprintf(fp, "[%d]: %d\t", r, G->tn[r]);  
  fprintf(fp, "\n\n");

  fprintf(fp, "G->tp matrix ----------------------------------------\n     ");
  for(c = 0; c < MAXRULES; c++)
    fprintf(fp, "   [%d]   ", c); /* column labels */
  fprintf(fp, "\n");
  for(r = 0; r < (condense ? G->M : MAXNT); r++) {
    fprintf(fp, "[%d]", r); /* row labels */
    for(c = 0; c < (condense ? G->nrules[r] : MAXRULES); c++)
      fprintf(fp, "%9.4f", G->tp[r][c]);
    fprintf(fp, "\n");
  }
  fprintf(fp, "\n");

  fprintf(fp, "G->tsc matrix ----------------------------------------\n     ");
  for(c = 0; c < MAXRULES; c++)
    fprintf(fp, "  [%d] ", c); /* column labels */
  fprintf(fp, "\n");
  for(r = 0; r < (condense ? G->M : MAXNT); r++) {
    fprintf(fp, "[%d]", r); /* row labels */
    for(c = 0; c < (condense ? G->nrules[r] : MAXRULES); c++)
      fprintf(fp, "%6d", G->tsc[r][c]);
    fprintf(fp, "\n");
  }
  fprintf(fp, "\n");

  fprintf(fp, "G->ned: %d ----------------------------------------\n", G->ned);
  for(r = 0; r < G->ned; r++) {
    fprintf(fp, "G->edist[%d]\t", r);
    raw_edist_dump(fp, G->edist[r]);
  }

  fprintf(fp, "G->nld: %d ----------------------------------------\n", G->nld);
  for(r = 0; r < G->nld; r++) {
    fprintf(fp, "LDIST #%d\t", r);
    raw_ldist_dump(fp, G->ldist[r]);
  }
  fprintf(fp, "\n");
  fprintf(fp, "G->nt_mind array ----------------------------------------\n");
  for(r = 0; r < (condense ? G->M : MAXNT); r++)
    fprintf(fp, "[%d]: %d\t", r, G->nt_mind[r]);  
  fprintf(fp, "\n\n");

  fprintf(fp, "G->rule_mind matrix ----------------------------------------\n     ");
  for(c = 0; c < MAXRULES; c++)
    fprintf(fp, "  [%d] ", c); /* column labels */
  fprintf(fp, "\n");
  for(r = 0; r < (condense ? G->M : MAXNT); r++) {
    fprintf(fp, "[%d]", r); /* row labels */
    for(c = 0; c < (condense ? G->nrules[r] : MAXRULES); c++)
      fprintf(fp, "%6d", G->rule_mind[r][c]);
    fprintf(fp, "\n");
  }
  fprintf(fp, "\nEND OF GRAMMAR\n");

  return;
}

/* ======================================================================
 * Function: raw_rule_dump()
 * Incept: Ray Lang, 10/12/2005 [St. Louis] 
 *
 * Purpose: raw dump of a rule structure (auxiliary to raw_grammar_dump)
 */
void 
raw_rule_dump(FILE *fp, RULE rl, int condense)
{
  /* local declarations */
  int r, c;
  char s[15];

  /* --------------- executable statements begin --------------- */
  fprintf(fp, "natoms: %d\t", rl.natoms);
  fprintf(fp, "is_allterminals: %s\n", (rl.is_allterminals ? "TRUE" : "FALSE") );

  fprintf(fp, "d1_iterator_state: %s", str_from_iterstate(s, rl.d1_iterator_state) );
  if(!condense || rl.d1_iterator_state != ITERATOR_OFF) { /* either _ON or _TIED */
    fprintf(fp, "\td1_iterator_min: %d\t", rl.d1_iterator_min);
    fprintf(fp, "d1_iterator_max: %d\n", rl.d1_iterator_max);
  } else {
    fprintf(fp, "\n");
  }

  fprintf(fp, "d2_iterator_state: %s", str_from_iterstate(s, rl.d2_iterator_state) );
  if(!condense || rl.d2_iterator_state != ITERATOR_OFF) { /* either _ON or _TIED */
    fprintf(fp, "\td2_iterator_min: %d\t", rl.d2_iterator_min);
    fprintf(fp, "d2_iterator_max: %d\n", rl.d2_iterator_max);
  } else {
    fprintf(fp, "\n");
  }
  fprintf(fp, "\n");

  for(r = 0; r < (condense ? rl.natoms : MAXATOMS); r++) {
    fprintf(fp, "atomtype[%d]: %s\n", r, str_from_atom(s, rl.atomtype[r]) );
  }
  fprintf(fp, "\n");

  fprintf(fp, "edist_idx");
  for(r = 0; r < (condense ? rl.natoms : MAXATOMS); r++) {
    fprintf(fp, "[%d]: %d \t", r, rl.edist_idx[r] );
  }
  fprintf(fp, "\n");

  fprintf(fp, "ldist_idx");
  for(r = 0; r < (condense ? rl.natoms : MAXATOMS); r++) {
    fprintf(fp, "[%d]: %d \t", r, rl.ldist_idx[r] );
  }
  fprintf(fp, "\n");

  fprintf(fp, "nterm_idx");
  for(r = 0; r < (condense ? rl.natoms : MAXATOMS); r++) {
    fprintf(fp, "[%d]: %d \t", r, rl.nterm_idx[r] );
  }
  fprintf(fp, "\n");

  fprintf(fp, "  ncoords");
  for(r = 0; r < (condense ? rl.natoms : MAXATOMS); r++) {
    fprintf(fp, "[%d]: %d \t", r, rl.ncoords[r] );
  }
  fprintf(fp, "\n\n");

  fprintf(fp, "coordbase matrix:\n      ");
  for(c = 0; c < MAXCOORD; c++)
    fprintf(fp, "  [%d]     ", c); /* column labels */
  fprintf(fp, "\n");
  for(r = 0; r < (condense ? rl.natoms : MAXATOMS); r++) {
    fprintf(fp, "[%d]   ", r); /* row labels */
    for(c = 0; c < MAXCOORD; c++)
      fprintf(fp, "%s   ", str_from_coordbase(s, rl.coordbase[r][c]) );
    fprintf(fp, "\n");
  }
  fprintf(fp, "\n");

  fprintf(fp, "offset matrix:\n      ");
  for(c = 0; c < MAXCOORD; c++)
    fprintf(fp, "[%d]  ", c); /* column labels */
  fprintf(fp, "\n");
  for(r = 0; r < (condense ? rl.natoms : MAXATOMS); r++) {
    fprintf(fp, "[%d]", r); /* row labels */
    for(c = 0; c < MAXCOORD; c++)
      fprintf(fp, "%5d", rl.offset[r][c]);
    fprintf(fp, "\n");
  }
  fprintf(fp, "\n");

  fprintf(fp, "context matrix:\n      ");
  for(c = 0; c < MAXCOORD; c++)
    fprintf(fp, "[%d]  ", c); /* column labels */
  fprintf(fp, "\n");
  for(r = 0; r < (condense ? rl.natoms : MAXATOMS); r++) {
    fprintf(fp, "[%d]", r); /* row labels */
    for(c = 0; c < MAXCOORD; c++)
      fprintf(fp, "%5d", rl.context[r][c]);
    fprintf(fp, "\n");
  }
  fprintf(fp, "\n");

  fprintf(fp, "atom_mind");
  for(r = 0; r < (condense ? rl.natoms : MAXATOMS); r++) {
    fprintf(fp, "[%d]: %d \t", r, rl.atom_mind[r] );
  }
  fprintf(fp, "\n");

  return;
}

/* ======================================================================
 * Function: raw_edist_dump()
 * Incept: Ray Lang, 10/12/2005 [St. Louis] 
 *
 * Purpose: raw dump of an edist structure (auxiliary to raw_grammar_dump)
 */
void 
raw_edist_dump(FILE *fp, EDIST e)
{
  /* local declarations */
  int i, vec_len = pow(NUM_BASES,e.n);

  /* diagnostic output
  printf("e.n is: %d, vec_len is: %d\n", e.n, vec_len);
  */

  /* --------------- executable statements begin --------------- */
  fprintf(fp, "n: %d\t", e.n);
  fprintf(fp, "is_basepair: %s\n", (e.is_basepair ? "TRUE" : "FALSE") );
  for(i = 0; i < vec_len; i++) {
    fprintf(fp, "ep[%2d]: %.4f\t", i, e.ep[i]);
    if(i % 4 == 3) /* line break after every fourth value */
      fprintf(fp, "\n");
  }
  fprintf(fp, "\n");
  for(i = 0; i < vec_len; i++) {
    fprintf(fp, "esc[%2d]: %-9d  ", i, e.esc[i]);
    if(i % 4 == 3) /* line break after every fourth value */
      fprintf(fp, "\n");
  }
  fprintf(fp, "- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
  return;
}

/* ======================================================================
 * Function: raw_ldist_dump()
 * Incept: Ray Lang, 10/12/2005 [St. Louis] 
 *
 * Purpose: raw dump of an ldist structure (auxiliary to raw_grammar_dump)
 */
void 
raw_ldist_dump(FILE *fp, LDIST l)
{
  fprintf(fp, "min: %d\t", l.min);
  fprintf(fp, "max: %d\n", l.max);
  fprintf(fp, "- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
  return;
}

/* ======================================================================
 * Function: str_from_coordbase()
 * Incept: Ray Lang, 10/12/2005 [St. Louis] 
 *
 * Purpose: map a coordbase to a string for output purposes
 */

char* 
str_from_coordbase(char* s, int c)
{
  switch (c) {
  case COORD_I: strcpy(s,"COORD_I"); break;
    
  case COORD_J: strcpy(s,"COORD_J"); break;
    
  case COORD_K: strcpy(s,"COORD_K"); break;
    
  case COORD_L: strcpy(s,"COORD_L"); break;
    
  default: strcpy(s,"Undefined coordbase"); break;
  }
  return s;
}

/* ======================================================================
 * Function: str_from_iterstate()
 * Incept: Ray Lang, 10/12/2005 [St. Louis] 
 *
 * Purpose: map an iterator_state to a string for output purposes
 */
char* 
str_from_iterstate(char* s, enum iterstate_e i)
{
  switch (i) {
  case ITERATOR_ON: strcpy(s,"ITERATOR_ON"); break;
    
  case ITERATOR_OFF: strcpy(s,"ITERATOR_OFF"); break;
    
  case ITERATOR_TIED: strcpy(s,"ITERATOR_TIED"); break;
    
  default: strcpy(s,"Undefined iterator state"); break;
  }
  return s;
}

/* ======================================================================
 * Function: str_from_atom()
 * Incept: Ray Lang, 10/12/2005 [St. Louis] 
 *
 * Purpose: map an atomtype to a string for output purposes
 */
char* 
str_from_atom(char* s, enum atom_e a)
{
  switch (a) {
  case EPSILON_ATOM: strcpy(s,"EPSILON_ATOM"); break;

  case NONTERMINAL_ATOM: strcpy(s,"NONTERMINAL_ATOM"); break;

  case EMISSION_ATOM: strcpy(s,"EMISSION_ATOM"); break;

  case MONOSEGMENT_ATOM: strcpy(s,"MONOSEGMENT_ATOM"); break;

  case DISEGMENT_ATOM: strcpy(s,"DISEGMENT_ATOM"); break;
    
  default: strcpy(s,"Undefined atom type"); break;
  }
  return s;
}

/* ======================================================================
 * Function: str_from_key()
 * Incept: Ray Lang, 10/11/2005 [St. Louis] 
 *
 * Purpose: maps a grammar key to a string
 */
char *
str_from_key(char* s, enum GRAMMAR_KEY k)
{
  switch(k) {
  case RULE_ROW_NDX:
    strcpy(s,"RULE_ROW_NDX"); break;
  case RULE_COL_NDX:
    strcpy(s,"RULE_COL_NDX"); break;
  case NATOMS_K:
    strcpy(s,"NATOMS_K"); break;
  case ATOMTYPE_K:
    strcpy(s,"ATOMTYPE_K"); break;
  case EDIST_IDX_K:
    strcpy(s,"EDIST_IDX_K"); break;
  case LDIST_IDX_K:
    strcpy(s,"LDIST_IDX_K"); break;
  case NTERM_IDX_K:
    strcpy(s,"NTERM_IDX_K"); break;
  case NCOORDS_K:
    strcpy(s,"NCOORDS_K"); break;
  case COORDBASE_K:
    strcpy(s,"COORDBASE_K"); break;
  case OFFSET_K:
    strcpy(s,"OFFSET_K"); break;
  case CONTEXT_K:
    strcpy(s,"CONTEXT_K"); break;
  case D1_ITERATOR_STATE_K:
    strcpy(s,"D1_ITERATOR_STATE_K"); break;
  case D1_ITERATOR_MIN_K:
    strcpy(s,"D1_ITERATOR_MIN_K"); break;
  case D1_ITERATOR_MAX_K:
    strcpy(s,"D1_ITERATOR_MAX_K"); break;
  case D2_ITERATOR_STATE_K:
    strcpy(s,"D2_ITERATOR_STATE_K"); break;
  case D2_ITERATOR_MIN_K:
    strcpy(s,"D2_ITERATOR_MIN_K"); break;
  case D2_ITERATOR_MAX_K:
    strcpy(s,"D2_ITERATOR_MAX_K"); break;
  case ATOM_MIND_K:
    strcpy(s,"ATOM_MIND_K"); break;
  case IS_ALLTERMINALS_K:
    strcpy(s,"IS_ALLTERMINALS_K"); break;
  case N_K:
    strcpy(s,"N_K"); break;
  case EP_K:
    strcpy(s,"EP_K"); break;
  case ESC_K:
    strcpy(s,"ESC_K"); break;
  case IS_BASEPAIR_K:
    strcpy(s,"IS_BASEPAIR_K"); break;
  case MIN_K:
    strcpy(s,"MIN_K"); break;
  case MAX_K:
    strcpy(s,"MAX_K"); break;
  case LP_K:
    strcpy(s,"LP_K"); break;
  case LSC_K:
    strcpy(s,"LSC_K"); break;
  case M_K:
    strcpy(s,"M_K"); break;
  case PR_K:
    strcpy(s,"PR_K"); break;
  case NRULES_K:
    strcpy(s,"NRULES_K"); break;
  case TDIST_IDX_K:
    strcpy(s,"TDIST_IDX_K"); break;
  case NTD_K:
    strcpy(s,"NTD_K"); break;
  case TN_K:
    strcpy(s,"TN_K"); break;
  case TP_K:
    strcpy(s,"TP_K"); break;
  case TSC_K:
    strcpy(s,"TSC_K"); break;
  case NED_K:
    strcpy(s,"NED_K"); break;
  case EDIST_K:
    strcpy(s,"EDIST_K"); break;
  case NLD_K:
    strcpy(s,"NLD_K"); break;
  case LDIST_K:
    strcpy(s,"LDIST_K"); break;
  case NONTERM_MIN_K:
    strcpy(s,"NONTERM_MIN_K"); break;
  case RULE_MIN_K:
    strcpy(s,"RULE_MIN_K"); break;
  case NUM_GRAMMAR_KEYS:
    strcpy(s,"NUM_GRAMMAR_KEYS"); break;
  default:
    strcpy(s,"Undefined grammar key"); break;
  }
  return s;
}

/* ======================================================================
 * Function: base_from_string()
 * Incept: Ray Lang, 11/07/2005 [St. Louis]
 *
 * Purpose: map a string to its corresponding base enum constant
 */
enum BASE_E base_from_string(char* s)
{
  /* local declaration */
  enum BASE_E b;

  if (strcmp(s, "A")==0)
    b = A;
  else if (strcmp(s, "C")==0)
    b = C;
  else if (strcmp(s, "G")==0)
    b = G;
  else if (strcmp(s, "U")==0)
    b = U;
  else
    Die("Cannot map string to BASE_E constant\n");
  
  return b;
}

/* ======================================================================
 * Function: bp_from_string()
 * Incept: Ray Lang, 11/07/2005 [St. Louis]
 *
 * Purpose: map a string to its corresponding base pair enum constant
 */ 
enum BASE_PAIR_E bp_from_string(char* s)
{
  /* local declaration */
  enum BASE_PAIR_E bp;

  if (strcmp(s, "AA")==0)
    bp = AA;
  else if (strcmp(s, "AC")==0)
    bp = AC;
  else if (strcmp(s, "AG")==0)
    bp = AG;
  else if (strcmp(s, "AU")==0)
    bp = AU;
  else if (strcmp(s, "CA")==0)
    bp = CA;
  else if (strcmp(s, "CC")==0)
    bp = CC;
  else if (strcmp(s, "CG")==0)
    bp = CG;
  else if (strcmp(s, "CU")==0)
    bp = CU;
  else if (strcmp(s, "GA")==0)
    bp = GA;
  else if (strcmp(s, "GC")==0)
    bp = GC;
  else if (strcmp(s, "GG")==0)
    bp = GG;
  else if (strcmp(s, "GU")==0)
    bp = GU;
  else if (strcmp(s, "UA")==0)
    bp = UA;
  else if (strcmp(s, "UC")==0)
    bp = UC;
  else if (strcmp(s, "UG")==0)
    bp = UG;
  else if (strcmp(s, "UU")==0)
    bp = UU;
  else
    Die("Cannot map string to BASE_PAIR_E constant\n");
  
  return bp;
}

/* ======================================================================
 * Function: sp_from_string()
 * Incept: Ray Lang, 11/07/2005 [St. Louis] 
 *
 * Purpose: map a string to its corresponding base pair enum constant
 */

enum STACKED_PAIR_E sp_from_string(char* s)
{
  /* local declaration */
  enum STACKED_PAIR_E sp;

  if (strcmp(s, "AA_AA")==0)
    sp = AA_AA;
  else if (strcmp(s, "AA_AC")==0)
    sp = AA_AC;
  else if (strcmp(s, "AA_AG")==0)
    sp = AA_AG;
  else if (strcmp(s, "AA_AU")==0)
    sp = AA_AU;
  else if (strcmp(s, "AA_CA")==0)
    sp = AA_CA;
  else if (strcmp(s, "AA_CC")==0)
    sp = AA_CC;
  else if (strcmp(s, "AA_CG")==0)
    sp = AA_CG;
  else if (strcmp(s, "AA_CU")==0)
    sp = AA_CU;
  else if (strcmp(s, "AA_GA")==0)
    sp = AA_GA;
  else if (strcmp(s, "AA_GC")==0)
    sp = AA_GC;
  else if (strcmp(s, "AA_GG")==0)
    sp = AA_GG;
  else if (strcmp(s, "AA_GU")==0)
    sp = AA_GU;
  else if (strcmp(s, "AA_UA")==0)
    sp = AA_UA;
  else if (strcmp(s, "AA_UC")==0)
    sp = AA_UC;
  else if (strcmp(s, "AA_UG")==0)
    sp = AA_UG;
  else if (strcmp(s, "AA_UU")==0)
    sp = AA_UU;
  else if (strcmp(s, "AC_AA")==0)
    sp = AC_AA;
  else if (strcmp(s, "AC_AC")==0)
    sp = AC_AC;
  else if (strcmp(s, "AC_AG")==0)
    sp = AC_AG;
  else if (strcmp(s, "AC_AU")==0)
    sp = AC_AU;
  else if (strcmp(s, "AC_CA")==0)
    sp = AC_CA;
  else if (strcmp(s, "AC_CC")==0)
    sp = AC_CC;
  else if (strcmp(s, "AC_CG")==0)
    sp = AC_CG;
  else if (strcmp(s, "AC_CU")==0)
    sp = AC_CU;
  else if (strcmp(s, "AC_GA")==0)
    sp = AC_GA;
  else if (strcmp(s, "AC_GC")==0)
    sp = AC_GC;
  else if (strcmp(s, "AC_GG")==0)
    sp = AC_GG;
  else if (strcmp(s, "AC_GU")==0)
    sp = AC_GU;
  else if (strcmp(s, "AC_UA")==0)
    sp = AC_UA;
  else if (strcmp(s, "AC_UC")==0)
    sp = AC_UC;
  else if (strcmp(s, "AC_UG")==0)
    sp = AC_UG;
  else if (strcmp(s, "AC_UU")==0)
    sp = AC_UU;
  else if (strcmp(s, "AG_AA")==0)
    sp = AG_AA;
  else if (strcmp(s, "AG_AC")==0)
    sp = AG_AC;
  else if (strcmp(s, "AG_AG")==0)
    sp = AG_AG;
  else if (strcmp(s, "AG_AU")==0)
    sp = AG_AU;
  else if (strcmp(s, "AG_CA")==0)
    sp = AG_CA;
  else if (strcmp(s, "AG_CC")==0)
    sp = AG_CC;
  else if (strcmp(s, "AG_CG")==0)
    sp = AG_CG;
  else if (strcmp(s, "AG_CU")==0)
    sp = AG_CU;
  else if (strcmp(s, "AG_GA")==0)
    sp = AG_GA;
  else if (strcmp(s, "AG_GC")==0)
    sp = AG_GC;
  else if (strcmp(s, "AG_GG")==0)
    sp = AG_GG;
  else if (strcmp(s, "AG_GU")==0)
    sp = AG_GU;
  else if (strcmp(s, "AG_UA")==0)
    sp = AG_UA;
  else if (strcmp(s, "AG_UC")==0)
    sp = AG_UC;
  else if (strcmp(s, "AG_UG")==0)
    sp = AG_UG;
  else if (strcmp(s, "AG_UU")==0)
    sp = AG_UU;
  else if (strcmp(s, "AU_AA")==0)
    sp = AU_AA;
  else if (strcmp(s, "AU_AC")==0)
    sp = AU_AC;
  else if (strcmp(s, "AU_AG")==0)
    sp = AU_AG;
  else if (strcmp(s, "AU_AU")==0)
    sp = AU_AU;
  else if (strcmp(s, "AU_CA")==0)
    sp = AU_CA;
  else if (strcmp(s, "AU_CC")==0)
    sp = AU_CC;
  else if (strcmp(s, "AU_CG")==0)
    sp = AU_CG;
  else if (strcmp(s, "AU_CU")==0)
    sp = AU_CU;
  else if (strcmp(s, "AU_GA")==0)
    sp = AU_GA;
  else if (strcmp(s, "AU_GC")==0)
    sp = AU_GC;
  else if (strcmp(s, "AU_GG")==0)
    sp = AU_GG;
  else if (strcmp(s, "AU_GU")==0)
    sp = AU_GU;
  else if (strcmp(s, "AU_UA")==0)
    sp = AU_UA;
  else if (strcmp(s, "AU_UC")==0)
    sp = AU_UC;
  else if (strcmp(s, "AU_UG")==0)
    sp = AU_UG;
  else if (strcmp(s, "AU_UU")==0)
    sp = AU_UU;
  else if (strcmp(s, "CA_AA")==0)
    sp = CA_AA;
  else if (strcmp(s, "CA_AC")==0)
    sp = CA_AC;
  else if (strcmp(s, "CA_AG")==0)
    sp = CA_AG;
  else if (strcmp(s, "CA_AU")==0)
    sp = CA_AU;
  else if (strcmp(s, "CA_CA")==0)
    sp = CA_CA;
  else if (strcmp(s, "CA_CC")==0)
    sp = CA_CC;
  else if (strcmp(s, "CA_CG")==0)
    sp = CA_CG;
  else if (strcmp(s, "CA_CU")==0)
    sp = CA_CU;
  else if (strcmp(s, "CA_GA")==0)
    sp = CA_GA;
  else if (strcmp(s, "CA_GC")==0)
    sp = CA_GC;
  else if (strcmp(s, "CA_GG")==0)
    sp = CA_GG;
  else if (strcmp(s, "CA_GU")==0)
    sp = CA_GU;
  else if (strcmp(s, "CA_UA")==0)
    sp = CA_UA;
  else if (strcmp(s, "CA_UC")==0)
    sp = CA_UC;
  else if (strcmp(s, "CA_UG")==0)
    sp = CA_UG;
  else if (strcmp(s, "CA_UU")==0)
    sp = CA_UU;
  else if (strcmp(s, "CC_AA")==0)
    sp = CC_AA;
  else if (strcmp(s, "CC_AC")==0)
    sp = CC_AC;
  else if (strcmp(s, "CC_AG")==0)
    sp = CC_AG;
  else if (strcmp(s, "CC_AU")==0)
    sp = CC_AU;
  else if (strcmp(s, "CC_CA")==0)
    sp = CC_CA;
  else if (strcmp(s, "CC_CC")==0)
    sp = CC_CC;
  else if (strcmp(s, "CC_CG")==0)
    sp = CC_CG;
  else if (strcmp(s, "CC_CU")==0)
    sp = CC_CU;
  else if (strcmp(s, "CC_GA")==0)
    sp = CC_GA;
  else if (strcmp(s, "CC_GC")==0)
    sp = CC_GC;
  else if (strcmp(s, "CC_GG")==0)
    sp = CC_GG;
  else if (strcmp(s, "CC_GU")==0)
    sp = CC_GU;
  else if (strcmp(s, "CC_UA")==0)
    sp = CC_UA;
  else if (strcmp(s, "CC_UC")==0)
    sp = CC_UC;
  else if (strcmp(s, "CC_UG")==0)
    sp = CC_UG;
  else if (strcmp(s, "CC_UU")==0)
    sp = CC_UU;
  else if (strcmp(s, "CG_AA")==0)
    sp = CG_AA;
  else if (strcmp(s, "CG_AC")==0)
    sp = CG_AC;
  else if (strcmp(s, "CG_AG")==0)
    sp = CG_AG;
  else if (strcmp(s, "CG_AU")==0)
    sp = CG_AU;
  else if (strcmp(s, "CG_CA")==0)
    sp = CG_CA;
  else if (strcmp(s, "CG_CC")==0)
    sp = CG_CC;
  else if (strcmp(s, "CG_CG")==0)
    sp = CG_CG;
  else if (strcmp(s, "CG_CU")==0)
    sp = CG_CU;
  else if (strcmp(s, "CG_GA")==0)
    sp = CG_GA;
  else if (strcmp(s, "CG_GC")==0)
    sp = CG_GC;
  else if (strcmp(s, "CG_GG")==0)
    sp = CG_GG;
  else if (strcmp(s, "CG_GU")==0)
    sp = CG_GU;
  else if (strcmp(s, "CG_UA")==0)
    sp = CG_UA;
  else if (strcmp(s, "CG_UC")==0)
    sp = CG_UC;
  else if (strcmp(s, "CG_UG")==0)
    sp = CG_UG;
  else if (strcmp(s, "CG_UU")==0)
    sp = CG_UU;
  else if (strcmp(s, "CU_AA")==0)
    sp = CU_AA;
  else if (strcmp(s, "CU_AC")==0)
    sp = CU_AC;
  else if (strcmp(s, "CU_AG")==0)
    sp = CU_AG;
  else if (strcmp(s, "CU_AU")==0)
    sp = CU_AU;
  else if (strcmp(s, "CU_CA")==0)
    sp = CU_CA;
  else if (strcmp(s, "CU_CC")==0)
    sp = CU_CC;
  else if (strcmp(s, "CU_CG")==0)
    sp = CU_CG;
  else if (strcmp(s, "CU_CU")==0)
    sp = CU_CU;
  else if (strcmp(s, "CU_GA")==0)
    sp = CU_GA;
  else if (strcmp(s, "CU_GC")==0)
    sp = CU_GC;
  else if (strcmp(s, "CU_GG")==0)
    sp = CU_GG;
  else if (strcmp(s, "CU_GU")==0)
    sp = CU_GU;
  else if (strcmp(s, "CU_UA")==0)
    sp = CU_UA;
  else if (strcmp(s, "CU_UC")==0)
    sp = CU_UC;
  else if (strcmp(s, "CU_UG")==0)
    sp = CU_UG;
  else if (strcmp(s, "CU_UU")==0)
    sp = CU_UU;
  else if (strcmp(s, "GA_AA")==0)
    sp = GA_AA;
  else if (strcmp(s, "GA_AC")==0)
    sp = GA_AC;
  else if (strcmp(s, "GA_AG")==0)
    sp = GA_AG;
  else if (strcmp(s, "GA_AU")==0)
    sp = GA_AU;
  else if (strcmp(s, "GA_CA")==0)
    sp = GA_CA;
  else if (strcmp(s, "GA_CC")==0)
    sp = GA_CC;
  else if (strcmp(s, "GA_CG")==0)
    sp = GA_CG;
  else if (strcmp(s, "GA_CU")==0)
    sp = GA_CU;
  else if (strcmp(s, "GA_GA")==0)
    sp = GA_GA;
  else if (strcmp(s, "GA_GC")==0)
    sp = GA_GC;
  else if (strcmp(s, "GA_GG")==0)
    sp = GA_GG;
  else if (strcmp(s, "GA_GU")==0)
    sp = GA_GU;
  else if (strcmp(s, "GA_UA")==0)
    sp = GA_UA;
  else if (strcmp(s, "GA_UC")==0)
    sp = GA_UC;
  else if (strcmp(s, "GA_UG")==0)
    sp = GA_UG;
  else if (strcmp(s, "GA_UU")==0)
    sp = GA_UU;
  else if (strcmp(s, "GC_AA")==0)
    sp = GC_AA;
  else if (strcmp(s, "GC_AC")==0)
    sp = GC_AC;
  else if (strcmp(s, "GC_AG")==0)
    sp = GC_AG;
  else if (strcmp(s, "GC_AU")==0)
    sp = GC_AU;
  else if (strcmp(s, "GC_CA")==0)
    sp = GC_CA;
  else if (strcmp(s, "GC_CC")==0)
    sp = GC_CC;
  else if (strcmp(s, "GC_CG")==0)
    sp = GC_CG;
  else if (strcmp(s, "GC_CU")==0)
    sp = GC_CU;
  else if (strcmp(s, "GC_GA")==0)
    sp = GC_GA;
  else if (strcmp(s, "GC_GC")==0)
    sp = GC_GC;
  else if (strcmp(s, "GC_GG")==0)
    sp = GC_GG;
  else if (strcmp(s, "GC_GU")==0)
    sp = GC_GU;
  else if (strcmp(s, "GC_UA")==0)
    sp = GC_UA;
  else if (strcmp(s, "GC_UC")==0)
    sp = GC_UC;
  else if (strcmp(s, "GC_UG")==0)
    sp = GC_UG;
  else if (strcmp(s, "GC_UU")==0)
    sp = GC_UU;
  else if (strcmp(s, "GG_AA")==0)
    sp = GG_AA;
  else if (strcmp(s, "GG_AC")==0)
    sp = GG_AC;
  else if (strcmp(s, "GG_AG")==0)
    sp = GG_AG;
  else if (strcmp(s, "GG_AU")==0)
    sp = GG_AU;
  else if (strcmp(s, "GG_CA")==0)
    sp = GG_CA;
  else if (strcmp(s, "GG_CC")==0)
    sp = GG_CC;
  else if (strcmp(s, "GG_CG")==0)
    sp = GG_CG;
  else if (strcmp(s, "GG_CU")==0)
    sp = GG_CU;
  else if (strcmp(s, "GG_GA")==0)
    sp = GG_GA;
  else if (strcmp(s, "GG_GC")==0)
    sp = GG_GC;
  else if (strcmp(s, "GG_GG")==0)
    sp = GG_GG;
  else if (strcmp(s, "GG_GU")==0)
    sp = GG_GU;
  else if (strcmp(s, "GG_UA")==0)
    sp = GG_UA;
  else if (strcmp(s, "GG_UC")==0)
    sp = GG_UC;
  else if (strcmp(s, "GG_UG")==0)
    sp = GG_UG;
  else if (strcmp(s, "GG_UU")==0)
    sp = GG_UU;
  else if (strcmp(s, "GU_AA")==0)
    sp = GU_AA;
  else if (strcmp(s, "GU_AC")==0)
    sp = GU_AC;
  else if (strcmp(s, "GU_AG")==0)
    sp = GU_AG;
  else if (strcmp(s, "GU_AU")==0)
    sp = GU_AU;
  else if (strcmp(s, "GU_CA")==0)
    sp = GU_CA;
  else if (strcmp(s, "GU_CC")==0)
    sp = GU_CC;
  else if (strcmp(s, "GU_CG")==0)
    sp = GU_CG;
  else if (strcmp(s, "GU_CU")==0)
    sp = GU_CU;
  else if (strcmp(s, "GU_GA")==0)
    sp = GU_GA;
  else if (strcmp(s, "GU_GC")==0)
    sp = GU_GC;
  else if (strcmp(s, "GU_GG")==0)
    sp = GU_GG;
  else if (strcmp(s, "GU_GU")==0)
    sp = GU_GU;
  else if (strcmp(s, "GU_UA")==0)
    sp = GU_UA;
  else if (strcmp(s, "GU_UC")==0)
    sp = GU_UC;
  else if (strcmp(s, "GU_UG")==0)
    sp = GU_UG;
  else if (strcmp(s, "GU_UU")==0)
    sp = GU_UU;
  else if (strcmp(s, "UA_AA")==0)
    sp = UA_AA;
  else if (strcmp(s, "UA_AC")==0)
    sp = UA_AC;
  else if (strcmp(s, "UA_AG")==0)
    sp = UA_AG;
  else if (strcmp(s, "UA_AU")==0)
    sp = UA_AU;
  else if (strcmp(s, "UA_CA")==0)
    sp = UA_CA;
  else if (strcmp(s, "UA_CC")==0)
    sp = UA_CC;
  else if (strcmp(s, "UA_CG")==0)
    sp = UA_CG;
  else if (strcmp(s, "UA_CU")==0)
    sp = UA_CU;
  else if (strcmp(s, "UA_GA")==0)
    sp = UA_GA;
  else if (strcmp(s, "UA_GC")==0)
    sp = UA_GC;
  else if (strcmp(s, "UA_GG")==0)
    sp = UA_GG;
  else if (strcmp(s, "UA_GU")==0)
    sp = UA_GU;
  else if (strcmp(s, "UA_UA")==0)
    sp = UA_UA;
  else if (strcmp(s, "UA_UC")==0)
    sp = UA_UC;
  else if (strcmp(s, "UA_UG")==0)
    sp = UA_UG;
  else if (strcmp(s, "UA_UU")==0)
    sp = UA_UU;
  else if (strcmp(s, "UC_AA")==0)
    sp = UC_AA;
  else if (strcmp(s, "UC_AC")==0)
    sp = UC_AC;
  else if (strcmp(s, "UC_AG")==0)
    sp = UC_AG;
  else if (strcmp(s, "UC_AU")==0)
    sp = UC_AU;
  else if (strcmp(s, "UC_CA")==0)
    sp = UC_CA;
  else if (strcmp(s, "UC_CC")==0)
    sp = UC_CC;
  else if (strcmp(s, "UC_CG")==0)
    sp = UC_CG;
  else if (strcmp(s, "UC_CU")==0)
    sp = UC_CU;
  else if (strcmp(s, "UC_GA")==0)
    sp = UC_GA;
  else if (strcmp(s, "UC_GC")==0)
    sp = UC_GC;
  else if (strcmp(s, "UC_GG")==0)
    sp = UC_GG;
  else if (strcmp(s, "UC_GU")==0)
    sp = UC_GU;
  else if (strcmp(s, "UC_UA")==0)
    sp = UC_UA;
  else if (strcmp(s, "UC_UC")==0)
    sp = UC_UC;
  else if (strcmp(s, "UC_UG")==0)
    sp = UC_UG;
  else if (strcmp(s, "UC_UU")==0)
    sp = UC_UU;
  else if (strcmp(s, "UG_AA")==0)
    sp = UG_AA;
  else if (strcmp(s, "UG_AC")==0)
    sp = UG_AC;
  else if (strcmp(s, "UG_AG")==0)
    sp = UG_AG;
  else if (strcmp(s, "UG_AU")==0)
    sp = UG_AU;
  else if (strcmp(s, "UG_CA")==0)
    sp = UG_CA;
  else if (strcmp(s, "UG_CC")==0)
    sp = UG_CC;
  else if (strcmp(s, "UG_CG")==0)
    sp = UG_CG;
  else if (strcmp(s, "UG_CU")==0)
    sp = UG_CU;
  else if (strcmp(s, "UG_GA")==0)
    sp = UG_GA;
  else if (strcmp(s, "UG_GC")==0)
    sp = UG_GC;
  else if (strcmp(s, "UG_GG")==0)
    sp = UG_GG;
  else if (strcmp(s, "UG_GU")==0)
    sp = UG_GU;
  else if (strcmp(s, "UG_UA")==0)
    sp = UG_UA;
  else if (strcmp(s, "UG_UC")==0)
    sp = UG_UC;
  else if (strcmp(s, "UG_UG")==0)
    sp = UG_UG;
  else if (strcmp(s, "UG_UU")==0)
    sp = UG_UU;
  else if (strcmp(s, "UU_AA")==0)
    sp = UU_AA;
  else if (strcmp(s, "UU_AC")==0)
    sp = UU_AC;
  else if (strcmp(s, "UU_AG")==0)
    sp = UU_AG;
  else if (strcmp(s, "UU_AU")==0)
    sp = UU_AU;
  else if (strcmp(s, "UU_CA")==0)
    sp = UU_CA;
  else if (strcmp(s, "UU_CC")==0)
    sp = UU_CC;
  else if (strcmp(s, "UU_CG")==0)
    sp = UU_CG;
  else if (strcmp(s, "UU_CU")==0)
    sp = UU_CU;
  else if (strcmp(s, "UU_GA")==0)
    sp = UU_GA;
  else if (strcmp(s, "UU_GC")==0)
    sp = UU_GC;
  else if (strcmp(s, "UU_GG")==0)
    sp = UU_GG;
  else if (strcmp(s, "UU_GU")==0)
    sp = UU_GU;
  else if (strcmp(s, "UU_UA")==0)
    sp = UU_UA;
  else if (strcmp(s, "UU_UC")==0)
    sp = UU_UC;
  else if (strcmp(s, "UU_UG")==0)
    sp = UU_UG;
  else if (strcmp(s, "UU_UU")==0)
    sp = UU_UU;
  else
    Die("Cannot map string to STACKED_PAIR_E constant\n");

  return sp;
}

/* ======================================================================
 * Function: key_from_string()
 * Incept: Ray Lang, 10/11/2005 [St. Louis] 
 *
 * Purpose: maps a string to a grammar key
 */
enum GRAMMAR_KEY key_from_string(char* s)
{
  /* local declaration */
  enum GRAMMAR_KEY k;

  if (strcmp(s,"RULE_ROW_NDX")==0)
    k = RULE_ROW_NDX;
  else if (strcmp(s,"RULE_COL_NDX")==0)
    k = RULE_COL_NDX;
  else if (strcmp(s,"NATOMS_K")==0)
    k = NATOMS_K;
  else if (strcmp(s,"ATOMTYPE_K")==0)
    k = ATOMTYPE_K;
  else if (strcmp(s,"EDIST_IDX_K")==0)
    k = EDIST_IDX_K;
  else if (strcmp(s,"LDIST_IDX_K")==0)
    k = LDIST_IDX_K;
  else if (strcmp(s,"NTERM_IDX_K")==0)
    k = NTERM_IDX_K;
  else if (strcmp(s,"NCOORDS_K")==0)
    k = NCOORDS_K;
  else if (strcmp(s,"COORDBASE_K")==0)
    k = COORDBASE_K;
  else if (strcmp(s,"OFFSET_K")==0)
    k = OFFSET_K;
  else if (strcmp(s,"CONTEXT_K")==0)
    k = CONTEXT_K;
  else if (strcmp(s,"D1_ITERATOR_STATE_K")==0)
    k = D1_ITERATOR_STATE_K;
  else if (strcmp(s,"D1_ITERATOR_MIN_K")==0)
    k = D1_ITERATOR_MIN_K;
  else if (strcmp(s,"D1_ITERATOR_MAX_K")==0)
    k = D1_ITERATOR_MAX_K;
  else if (strcmp(s,"D2_ITERATOR_STATE_K")==0)
    k = D2_ITERATOR_STATE_K;
  else if (strcmp(s,"D2_ITERATOR_MIN_K")==0)
    k = D2_ITERATOR_MIN_K;
  else if (strcmp(s,"D2_ITERATOR_MAX_K")==0)
    k = D2_ITERATOR_MAX_K;
  else if (strcmp(s,"ATOM_MIND_K")==0)
    k = ATOM_MIND_K;
  else if (strcmp(s,"IS_ALLTERMINALS_K")==0)
    k = IS_ALLTERMINALS_K;
  else if (strcmp(s,"N_K")==0)
    k = N_K;
  else if (strcmp(s,"EP_K")==0)
    k = EP_K;
  else if (strcmp(s,"ESC_K")==0)
    k = ESC_K;
  else if (strcmp(s,"IS_BASEPAIR_K")==0)
    k = IS_BASEPAIR_K;
  else if (strcmp(s,"MIN_K")==0)
    k = MIN_K;
  else if (strcmp(s,"MAX_K")==0)
    k = MAX_K;
  else if (strcmp(s,"LP_K")==0)
    k = LP_K;
  else if (strcmp(s,"LSC_K")==0)
    k = LSC_K;
  else if (strcmp(s,"M_K")==0)
    k = M_K;
  else if (strcmp(s,"PR_K")==0)
    k = PR_K;
  else if (strcmp(s,"NRULES_K")==0)
    k = NRULES_K;
  else if (strcmp(s,"TDIST_IDX_K")==0)
    k = TDIST_IDX_K;
  else if (strcmp(s,"NTD_K")==0)
    k = NTD_K;
  else if (strcmp(s,"TN_K")==0)
    k = TN_K;
  else if (strcmp(s,"TP_K")==0)
    k = TP_K;
  else if (strcmp(s,"TSC_K")==0)
    k = TSC_K;
  else if (strcmp(s,"NED_K")==0)
    k = NED_K;
  else if (strcmp(s,"EDIST_K")==0)
    k = EDIST_K;
  else if (strcmp(s,"NLD_K")==0)
    k = NLD_K;
  else if (strcmp(s,"LDIST_K")==0)
    k = LDIST_K;
  else if (strcmp(s,"NONTERM_MIN_K")==0)
    k = NONTERM_MIN_K;
  else if (strcmp(s,"RULE_MIN_K")==0)
    k = RULE_MIN_K;
  else if (strcmp(s,"NUM_GRAMMAR_KEYS")==0)
    k = NUM_GRAMMAR_KEYS;
  else
    Die("Cannot map %s to grammar key\n",s);

  return k;
}
