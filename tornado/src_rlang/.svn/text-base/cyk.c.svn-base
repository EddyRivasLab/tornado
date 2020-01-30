/* cyk.c
 * CYK algorithm for folding a sequence using a generalized RNA SCFG.
 * 
 * SRE, Wed Mar 23 09:44:43 2005
 * SVN $Id$
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <easel.h>
#include <esl_stack.h>
#include <esl_random.h>

#include "util.h"
#include "grammar.h"		/* CYKVAL is defined here, for scores. */
#include "parsetree.h"
#include "cyk.h"

static CYKVAL    dp_recursion(CYKVAL ***cyk, GRAMMAR *G, char *dsq, int L, 
			      int c[4], int j, int d, int w, ESL_STACK *alts);

/* Function:  CYK_Create()
 * Incept:    SRE, Fri Nov 19 09:53:21 2004 [St. Louis]
 *
 * Purpose:   Allocates a CYK DP matrix, indexed
 *            cyk[w][j][d].
 *
 * Args:      M - number of nonterminals in grammar
 *            L - length of sequence
 *
 * Returns:   ptr to allocated 3D CYK matrix
 *
 * Xref:      STL8/p132
 */
CYKVAL ***
CYK_Create(int M, int L)
{
  CYKVAL ***cyk;
  int    j,w;
  int    pos;

  cyk = malloc(sizeof(CYKVAL **) * M); /* M decks */
  for (w = 0; w < M; w++)
    {
      cyk[w]    = malloc(sizeof(CYKVAL *) * (L+1));
      cyk[w][0] = malloc(sizeof(CYKVAL)   * ((L+2)*(L+1))/2);
      pos = 1;
      for (j = 1; j <= L; j++)
	{
	  cyk[w][j] = cyk[w][0] + pos;
	  pos += j+1;
	}
    }
  return cyk;
}

/* Function:  CYK_Destroy()
 * Incept:    SRE, Wed Mar 23 09:52:56 2005 [St. Louis]
 *
 * Purpose:   Frees a CYK matrix allocated by CYK_Create().
 */
void
CYK_Destroy(CYKVAL ***cyk, int M)
{
  int w;
  for (w = 0; w < M; w++)
    {
      free(cyk[w][0]);
      free(cyk[w]);
    }
  free(cyk);
}

/* Function:  CYK_MatrixSize()
 * Incept:    SRE, Wed Mar 23 09:54:34 2005 [St. Louis]
 *
 * Purpose:   Returns the predicted memory requirement of a CYK
 *            matrix for a grammar of <M> nonterminals and
 *            a sequence of <L> residues, in MB.
 */
float
CYK_MatrixSize(int M, int L)
{
  int nbytes;

  nbytes  = sizeof(CYKVAL) * (L+2)*(L+1)/2;
  nbytes += sizeof(CYKVAL *) * (L+1);
  nbytes += sizeof(CYKVAL **) * M;
  return ((float) nbytes / 1024. / 1024.);
}

/* Function:  CYK_Dump()
 * Incept:    SRE, Wed Mar 23 09:55:43 2005 [St. Louis]
 *
 * Purpose:   Dumps a complete CYK matrix to a stream <fp>,
 *            for debugging.
 */
void
CYK_Dump(FILE *fp, CYKVAL ***cyk, int M, int L)
{
  int w;

  for (w = 0; w < M; w++)
    CYK_DumpOneDeck(fp, cyk[w], L);
}

/* Function:  CYK_DumpOneDeck()
 * Incept:    SRE, Wed Mar 23 09:56:57 2005 [St. Louis]
 *
 * Purpose:   Dump one deck (one nonterminal) of a CYK
 *            matrix to a stream <fp>, for debugging.
 */
void
CYK_DumpOneDeck(FILE *fp, CYKVAL **sc, int L)
{
  int j,d;

  for (j = 0; j <= L; j++)
    {
      for (d = 0; d <= j; d++)
	fprintf(fp, "%3d ", sc[j][d]);
      fputc('\n', fp);
    }
  fputc('\n', fp);
}


/* Function:  CYK_Fill()
 * Incept:    SRE, Wed Mar 23 10:04:28 2005 [St. Louis]
 *
 * Purpose:   Given a generalized SCFG <G>, and a digitized sequence <dsq>
 *            w/ residues 1..<L>, run the generalized CYK recursion
 *            to fill a matrix. Return the score of the sequence. 
 *            If <ret_cyk> is non-NULL, use it to return the CYK matrix.
 *            Caller can then retrieve a parsetree (using CYK_TraceParsetree())
 *            or simply a CT base-pair array (using CYK_TraceCT());
 *            caller must free cyk using CYK_Destroy(cyk, G->M) when
 *            done collecting its tracebacks.
 */
CYKVAL
CYK_Fill(GRAMMAR *G, char *dsq, int L, CYKVAL ****ret_cyk)
{
  CYKVAL ***cyk;		/* CYK DP matrix: M x (L x L triangular)     */
  int       j,d;		/* j,d coords of the CYK matrix              */
  int       c[4];		/* iklj coord quad constructed for recursion */
  int       w;		        /* counter over nonterminals                 */
  CYKVAL    sc;	                /* tmp variable, possible path score to maxr */

  cyk = CYK_Create(G->M, L);
  for (j = 0; j <= L; j++)
    for (d = 0; d <= j; d++)
      {
	c[COORD_J] = j;
	c[COORD_I] = j-d+1;
	for (w = 0; w < G->M; w++)
	  {
	    cyk[w][j][d] = -CYKINFTY;
	    if (d < G->nt_mind[w]) continue;
	    cyk[w][j][d] = dp_recursion(cyk, G, dsq, L, c, j, d, w, NULL);
	  } 
      } 
  sc = cyk[0][L][L];

  if (ret_cyk != NULL) *ret_cyk = cyk;
  else                  CYK_Destroy(cyk, G->M);

  return sc;
}


/* Function:  CYK_TraceCT()
 * Incept:    SRE, Wed Mar 23 10:10:30 2005 [St. Louis]
 *
 * Purpose:   Given a filled CYK matrix, stochastically sample one
 *            possible parse tree from it; return a CT base pair array
 *            (1..L) that annotates the predicted base pairs in <dsq>.
 *            Caller must free the ct array using free(ct).
 */
int
CYK_TraceCT(CYKVAL ***cyk, GRAMMAR *G, char *dsq, int L, int **ret_ct)
{
  RULE     *rp;		/* convenience ptr to a rule                   */
  ESL_STACK *ns;        /* integer pushdown stack for traceback */
  ESL_STACK *alts;	/* stack of alternate equal-scoring tracebacks */
  ESL_RANDOMNESS *rng;	/* random numbers for stochastic traceback */
  int *ct;		/* CT structure defining basepairs      */
  int  c[4];		/* iklj coord quadruplet for a recursion */
  int  a,b;		/* indices used for score lookups */
  int  w,y;		/* counters over nonterminals */
  int  e;		/* counter over atoms */
  int  r;		/* index of a rule */
  int  d1,d2;		/* optimum values of d1, d2 iterators */
  int  i,j,d;		/* seq coords */
  int  eofw;		/* "e of w", index of emission dist for this nonterm */
  CYKVAL bestsc;	/* max score over possible rules for nonterminal w  */
  int    nequiv;	/* number of equivalent alternatives for a traceback */
  int    x;		/* a random choice from nequiv */


  /* We're going to do a simple traceback that only
   * remembers who was a base pair, and keeps a ct[]
   * array. 
   */
  ct = malloc(sizeof(int) * (L+2));
  for (i = 0; i <= L+1; i++) ct[i] = 0;

  /* We implement a "stochastic" traceback, which chooses randomly
   * amongst equal-scoring alternative parse trees. This is particularly
   * essential for working with ambiguous grammars, for which 
   * choosing an arbitrary optimal parse tree by order of evaluation
   * can easily result in infinite loops. To do this, we will keep
   * a stack of the alternate solutions.
   */
  alts = esl_stack_ICreate();
  rng  = esl_randomness_CreateTimeseeded();

  /* Start an integer stack for traversing the traceback.
   * push w,i,j = 0,1,L to init. 
   */
  ns = esl_stack_ICreate();
  esl_stack_IPush(ns, 0);
  esl_stack_IPush(ns, 1);
  esl_stack_IPush(ns, L);

  while (esl_stack_ObjectCount(ns) != 0)
    {
      esl_stack_IPop(ns, &j);
      esl_stack_IPop(ns, &i);
      esl_stack_IPop(ns, &w);
      d = j-i+1;
      c[COORD_J] = j;
      c[COORD_I] = i;

      bestsc = dp_recursion(cyk, G, dsq, L, c, j, d, w, alts);

      /* Some assertions.
       */
      if (d < G->nt_mind[w])      Die("can't happen");
      if (bestsc != cyk[w][j][d]) Die("that can't happen either");
      
      /* Now we know one or more equiv solutions, and they're in
       * the stack <alts>, which keeps 3 numbers (r, d1, d2) for each
       * solution. Choose one of them at random.
       */
      nequiv = esl_stack_ObjectCount(alts) / 3; /* how many solutions? */
      x = esl_rnd_Choose(rng, nequiv);          /* uniformly, 0.nequiv-1 */
      esl_stack_DiscardTopN(alts, x*3);         /* dig down to choice */
      esl_stack_IPop(alts, &d2);                /* pop it off, in rev order */
      esl_stack_IPop(alts, &d1);
      esl_stack_IPop(alts, &r);

      /* Now we know a best rule; figure out where we came from,
       * and push that info onto the <ns> stack. We have to traverse all
       * the atoms in the rule. 
       */
      rp         = &(G->pr[w][r]);
      c[COORD_K] = c[COORD_I] + d1 - 1;
      c[COORD_L] = c[COORD_J] - d2 + 1;
      for (e = 0; e < rp->natoms; e++)
	{
	  switch (rp->atomtype[e]) {
	  case EPSILON_ATOM:
	    break;

	  case NONTERMINAL_ATOM: /* The main business of the traceback. */
	    a   = c[rp->coordbase[e][0]] + rp->offset[e][0];
	    b   = c[rp->coordbase[e][1]] + rp->offset[e][1];
	    y   = rp->nterm_idx[e];
	    esl_stack_IPush(ns, y);
	    esl_stack_IPush(ns, a);
	    esl_stack_IPush(ns, b);
	    break;

	    /* The main business of recording secondary structure in ct */
	  case EMISSION_ATOM:	
	    eofw       = rp->edist_idx[e];
	    if (G->edist[eofw].is_basepair && rp->ncoords[e] == 2) {
	      /* coord of first emitted base */
	      a = c[rp->coordbase[e][0]] + rp->offset[e][0];
	      /* coord of second emitted base */
	      b = c[rp->coordbase[e][1]] + rp->offset[e][1]; 
	      ct[a] = b;
	      ct[b] = a;
	    }
	    break;

	  case MONOSEGMENT_ATOM:
	    /* TODO */
	    break;

	  case DISEGMENT_ATOM:
	    break;

	  default: 
	    Die("no such atom");
	  } /* end switch over atom types */
	} /* end loop over atoms. */
    } /* end of while loop, while there's still traceback going */

  esl_stack_Destroy(ns);
  esl_stack_Destroy(alts);
  esl_randomness_Destroy(rng);
  *ret_ct = ct;
  return 1;
}

/* Function:  CYK_TraceParsetree()
 * Incept:    SRE, Wed Mar 23 10:16:01 2005 [St. Louis]
 *
 * Purpose:   Given a filled CYK matrix, stochastically sample one
 *            possible parse tree from it, and return the tree
 *            through <ret_T>. Caller must free the tree using 
 *            ParsetreeFree(T).
 */
int
CYK_TraceParsetree(CYKVAL ***cyk, GRAMMAR *G, char *dsq, int L, PARSETREE **ret_T)
{
  RULE     *rp;		/* convenience ptr to a rule                   */
  ESL_STACK *ns;        /* integer pushdown stack for traceback */
  ESL_STACK *alts;	/* stack of alternate equal-scoring tracebacks */
  ESL_RANDOMNESS *rng;	/* random numbers for stochastic traceback */
  PARSETREE *T;		/* parse tree we're constructing      */
  int  c[4];		/* iklj coord quadruplet for a recursion */
  int  a,b;		/* indices used for score lookups */
  int  w,y;		/* counters over nonterminals */
  int  e;		/* counter over atoms */
  int  r;		/* index of a rule */
  int  d1,d2;		/* optimum values of d1, d2 iterators */
  int  i,j,d;		/* seq coords */
  CYKVAL bestsc;	/* max score over possible rules for nonterminal w  */
  int    nequiv;	/* number of equivalent alternatives for a traceback */
  int    x;		/* a random choice from nequiv */
  int    curr;		/* index of current parse tree node */
  int    parent;	/* index of parent parse tree node */

  /* Initialize the parse tree.
   */
  T = Parsetree_Create();

  /* We implement a "stochastic" traceback, which chooses randomly
   * amongst equal-scoring alternative parse trees. This is particularly
   * essential for working with ambiguous grammars, for which 
   * choosing an arbitrary optimal parse tree by order of evaluation
   * can easily result in infinite loops. To do this, we will keep
   * a stack of the alternate solutions.
   */
  alts = esl_stack_ICreate();
  rng  = esl_randomness_CreateTimeseeded();

  /* Start an integer stack for traversing the traceback.
   * push parent,w,i,j = -1,0,1,L to init. 
   */
  ns = esl_stack_ICreate();
  esl_stack_IPush(ns, -1);
  esl_stack_IPush(ns, 0);
  esl_stack_IPush(ns, 1);
  esl_stack_IPush(ns, L);

  while (esl_stack_ObjectCount(ns) != 0)
    {
      esl_stack_IPop(ns, &j);
      esl_stack_IPop(ns, &i);
      esl_stack_IPop(ns, &w);
      esl_stack_IPop(ns, &parent);
      d = j-i+1;
      c[COORD_J] = j;
      c[COORD_I] = i;

      /* Add this node to the growing parse tree
       */
      curr = T->n;
      if (T->n == T->nalloc) Parsetree_Expand(T);
      T->node[curr].w     = w;
      T->node[curr].r     = -1;	/* rule is unknown for now */
      T->node[curr].i     = i;
      T->node[curr].j     = j;
      T->node[curr].k     = -1;
      T->node[curr].l     = -1;
      T->node[curr].up    = parent;
      T->node[curr].left  = -1;	/* left child unknown for now */
      T->node[curr].right = -1;	/* right child unknown for now */
      T->n++;
      if (parent != -1)
	{
	  if      (T->node[parent].left  == -1) T->node[parent].left  = curr;
	  else if (T->node[parent].right == -1) T->node[parent].right = curr;
	  else    Die("no room for child node");
	}

      /* Figure out how we got here, by one traceback step in the CYK matrix.
       */
      bestsc = dp_recursion(cyk, G, dsq, L, c, j, d, w, alts);

      /* Some assertions.
       */
      if (d < G->nt_mind[w])      Die("can't happen");
      if (bestsc != cyk[w][j][d]) Die("that can't happen either");
      
      /* Now we know one or more equiv solutions, and they're in
       * the stack <alts>, which keeps 3 numbers (r, d1, d2) for each
       * solution. Choose one of them at random.
       */
      nequiv = esl_stack_ObjectCount(alts) / 3; /* how many solutions? */
      x = esl_rnd_Choose(rng, nequiv);          /* uniformly, 0.nequiv-1 */
      esl_stack_DiscardTopN(alts, x*3);         /* dig down to choice */
      esl_stack_IPop(alts, &d2);                /* pop it off, in rev order */
      esl_stack_IPop(alts, &d1);
      esl_stack_IPop(alts, &r);

      /* Now we know a best rule; figure out where we came from,
       * and push the quad (parent, w, i, j) info onto the <ns> stack.
       * We have to traverse all the atoms in the rule, looking
       * for nonterminals w. 
       */
      rp         = &(G->pr[w][r]);
      c[COORD_K] = c[COORD_I] + d1 - 1;
      c[COORD_L] = c[COORD_J] - d2 + 1;
      for (e = 0; e < rp->natoms; e++)
	if (rp->atomtype[e] == NONTERMINAL_ATOM)
	  {
	    a   = c[rp->coordbase[e][0]] + rp->offset[e][0];
	    b   = c[rp->coordbase[e][1]] + rp->offset[e][1];
	    y   = rp->nterm_idx[e];
	    esl_stack_IPush(ns, curr);
	    esl_stack_IPush(ns, y);
	    esl_stack_IPush(ns, a);
	    esl_stack_IPush(ns, b);
	  }
    } /* end of while loop, while there's still traceback going */

  esl_stack_Destroy(ns);
  esl_stack_Destroy(alts);
  esl_randomness_Destroy(rng);
  *ret_T = T;
  return 1;
}



/* dp_recursion():
 * The actual business of the generalized CYK parser, for
 * calculating one CYK lattice cell.
 */
static CYKVAL
dp_recursion(CYKVAL ***cyk, GRAMMAR *G, char *dsq, int L, 
	     int c[4], int j, int d, int w, ESL_STACK *alts)
{
  RULE     *rp;			/* convenience ptr to a rule              */
  int       tofw;		/* "t of w", index of t dist for nonterm */
  int       eofw;		/* "e of w", index of e dist for nonterm   */
  int       a,b;		/* indices used for score lookups */
  int       y;			/* index of a nonterminal */
  int       r;			/* counter over possible rules */
  int       e;			/* counter over atoms for a rule */
  int       x;			/* lookup index for emitted residues */
  CYKVAL    sc;	                /* temp variable, possible path score to max */
  CYKVAL    bestsc;		/* best score seen so far */
  int       d1, d1_min;		/* d1 iterator, for coord k */
  int       d2, d2_min;		/* d2 iterator, for coord l */

  tofw   = G->tdist_idx[w];
  if (alts != NULL) esl_stack_Reuse(alts);
  bestsc = -CYKINFTY;
  for (r = 0; r < G->nrules[w]; r++)
    {
      /* There are three "boundary condition" tests here:
       *   1. The rule is incapable of generating a production of length < d.
       *   2. The rule contains only terminals, so it generates a fixed d, and
       *      this d ain't it.
       *   3. The transition probability into this rule is 0. Why is it there,
       *      then? Not for us to wonder why.   
       */
      if (d < G->rule_mind[w][r])                                 continue;
      if (G->pr[w][r].is_allterminals && d != G->rule_mind[w][r]) continue;
      if (G->tsc[tofw][r] == -CYKINFTY)                           continue; 
      rp  = &(G->pr[w][r]);

      /* Setup of the d1 iterator for this rule r.
       */
      if (rp->d1_iterator_state == ITERATOR_ON) {
	d1     = MIN(d, rp->d1_iterator_max);
	d1_min = MAX(0, rp->d1_iterator_min);
      } else if (rp->d1_iterator_state == ITERATOR_OFF) {
	d1     = 0;
	d1_min = 0;
      }

      do { /* Iterate over all valid values of d1. */
	c[COORD_K] = c[COORD_I] + d1 - 1;

	/* Setup of the d2 iterator for this rule r.
	 */
	if (rp->d2_iterator_state == ITERATOR_ON) {
	  d2     = MIN(d, rp->d2_iterator_max);
	  d2_min = MAX(0, rp->d2_iterator_min);
	} else if (rp->d2_iterator_state == ITERATOR_OFF) {
	  d2     = 0;
	  d2_min = 0;
	} else if (rp->d1_iterator_state == ITERATOR_TIED) {
	  d2     = d1;
	  d2_min = d1;
	}

	do { /* Iteration over all valid values of d2. */
	  c[COORD_L] = c[COORD_J] - d2 + 1;

	  /* This is the heart of it; 
	   * all our coords i,k,l,j; d,d1,d2 are set up (we think).
	   * add up all the contributions of each atom to the score.
	   */
	  sc = G->tsc[tofw][r]; /* start with the transition score; then add atoms */
	  for (e = 0; e < rp->natoms; e++)
	    {
	      switch (rp->atomtype[e]) {
	      case EPSILON_ATOM:
		break;		/* only costs the transition cost. */

	      case NONTERMINAL_ATOM:
		a   = c[rp->coordbase[e][0]] + rp->offset[e][0];
		b   = c[rp->coordbase[e][1]] + rp->offset[e][1];
		y   = rp->nterm_idx[e];
		if (a < 0 || a > L || b < 0 || b > L) /* boundaries */
		  sc = -CYKINFTY;
		else if (cyk[y][b][b-a+1] == -CYKINFTY)
		  sc = -CYKINFTY;
		else
		  sc += cyk[y][b][b-a+1]; /* b-a+1 because we're jd indexed */
		break;

	      case EMISSION_ATOM:
		x = EmissionAtomIndex(dsq, L, c, rp, e);

		/* TODO: sequence context calculation would go here. */

		eofw = rp->edist_idx[e];
		if (x == -1)	/* ambiguity in one or more residues */
		  sc += rp->ncoords[e] * log(0.25); /* arbitrary!! */
		else if (G->edist[eofw].esc[x] == -CYKINFTY)
		  sc = -CYKINFTY;
		else
		  sc  += G->edist[eofw].esc[x]; /* TODO: we haven't included context here */
		break;

	      case MONOSEGMENT_ATOM:
		/* TODO: monosegment recursion goes here */
		break;

	      case DISEGMENT_ATOM:
		/* TODO: pairedsegment recursion goes here */
		break;
			  
	      default:
		exit(1);
	      }/* end of switch over atom types */

	      /* if sc is ever -CYKINFTY, then don't need to look further; it's -CYKINFTY. */
	      if (sc == -CYKINFTY) break;
	    }/* this ends loop over atoms <e>; we've now constructed score <sc> for this rule <r> */
	  
	  if (sc >= bestsc && !(d == 0 && ! rp->is_allterminals)) {
	    /* That last test above is a special cheat. For d=0,
	     * *only* allow an epsilon rule. Not needed for
	     * unambiguous grammars, but for ambiguous grammars
	     * that have a rule pair like S-> SS | \epsilon,
	     * there's a nasty exploding (Yule?) process that may
	     * take a long time to terminate.
	     */
	    if (sc > bestsc) { /* if an outright winner, clear/reinit the stack */
	      if (alts != NULL) esl_stack_Reuse(alts);
	      bestsc   = sc;
	    }
	    if (alts != NULL) {
	      esl_stack_IPush(alts, r);   /* note order of the pushes: r,d1,d2; */
	      esl_stack_IPush(alts, d1);  /* thus the caller pops d2,d1,r.  */
	      esl_stack_IPush(alts, d2);
	    }
	  }

	} while (--d2 >= d2_min); /* end of the d2 iterator's do loop */
      } while (--d1 >= d1_min);   /* end of the d1 iterator's do loop */

    } /* end loop over r; all possible rules for this nonterm w */
  return bestsc;
}
