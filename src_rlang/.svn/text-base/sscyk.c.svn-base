/* sscyk.c
 * 
 * Convert a known secondary structure annotation (WUSS format)
 * to a parse tree of a generalized grammar. Used for parameter
 * estimation. 
 * 
 * If grammar is structurally ambiguous, randomly selects one
 * possible parse tree.
 * 
 * Algorithm is currently a CYK parser, w/ stochastic traceback;
 * essentially a copy of the parser in generalized_cyk.c. Using CYK
 * seems like a profligate waste of time, for a nonstochastic CFG
 * parsing problem. There are much faster nonstochastic CYK parsers,
 * but it is not clear that they are appropriate. LR(k) parsers, for
 * example, do not appear to be general enough to deal with all the
 * SCFG designs we will use; it appears to be easy to write down many
 * plausible, useful RNA folding SCFGs that lead to reduce/reduce and
 * shift/reduce conflicts in an LR(k) parser. However, I haven't fully
 * explored alternative parsers. It may be possible to achieve
 * substantial optimization with a more efficient parser.
 *
 * SRE, Tue Mar  8 11:35:42 2005
 * SVN $Id$
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <easel.h>
#include <esl_stack.h>
#include <esl_random.h>

#include "util.h"
#include "grammar.h"
#include "parsetree.h"
#include "sscyk.h"

static int dp_recursion(SSCYKVAL ***cyk, GRAMMAR *G, char *ss, int L, 
			int c[4], int j, int d, int w, ESL_STACK *alts);


/* Function:  ssCYK_Fill()
 * Incept:    SRE, Wed Mar 23 09:19:04 2005 [St. Louis]
 *
 * Purpose:   Given a grammar <G>, and a known secondary structure
 *            string <ss> in WUSS format (0..<L>-1), do a 
 *            constrained CYK fill. Returns 1 if the structure
 *            has one or more parse trees; returns 0 if the structure
 *            has no possible parse tree. Returns the CYK matrix
 *            through <ret_cyk>. The caller can use this to recover
 *            one or more parse trees using ssCYK_Trace(). When done, 
 *            free the CYK matrix by calling ssCYK_Destroy(cyk, G->M).
 */
int
ssCYK_Fill(GRAMMAR *G, char *ss, int L, SSCYKVAL ****ret_cyk)
{
  SSCYKVAL ***cyk;		/* DP matrix, M x L x L triangular */
  int         j,d;		/* j,d coords in CYK matrix        */
  int         c[4];		/* iklj coord quad constructed for recursion */
  int         w;		/* counter over nonterminals */
  int         reachable;	/* TRUE if we can derived i..j from this w */

  cyk = ssCYK_Create(G->M, L);

  for (j = 0; j <= L; j++)
    for (d = 0; d <= j; d++)
      {
	c[COORD_J] = j;
	c[COORD_I] = j-d+1;

	for (w = 0; w < G->M; w++)
	  {
	    cyk[w/32][j][d] &= ~(1<<(w%32)); /* set w OFF */
	    if (d < G->nt_mind[w]) continue;
	    reachable = dp_recursion(cyk, G, ss, L, c, j, d, w, NULL);
	    if (reachable)
	      cyk[w/32][j][d] |= (1<<(w%32)); /* set w ON */
	  }
      }
  reachable = cyk[0][L][L] & (1<<0); /* could we parse the complete ss? */

  /* dump_cyk_matrix(cyk, G->M, L); */
  
  if (ret_cyk != NULL) *ret_cyk = cyk;
  else                  ssCYK_Destroy(cyk, G->M);

  return reachable;
}


/* Function:  ssCYK_Trace()
 * Incept:    SRE, Wed Mar 23 09:28:07 2005 [St. Louis]
 *
 * Purpose:   Given a filled ssCYK matrix <cyk>, for a parse of the
 *            WUSS-format secondary structure <ss> (indexed 0..<L>-1)
 *            with grammar <G>, do a "stochastic" traceback of <cyk>
 *            to randomly sample one possible parse tree. Returns 1
 *            on success, and passes the tree back via <ret_T>. 
 *            Caller frees the tree with Parsetree_Free(T).
 */
int
ssCYK_Trace(SSCYKVAL ***cyk, GRAMMAR *G, char *ss, int L, PARSETREE **ret_T)
{
  RULE     *rp;		/* convenience ptr to a rule                   */
  ESL_STACK *ns;        /* integer pushdown stack for traceback */
  ESL_STACK *alts;	/* stack of alternate equal-scoring tracebacks */
  ESL_RANDOMNESS *rng;	/* random numbers for stochastic traceback */
  PARSETREE *T;         /* parse tree we're constructing */
  int  c[4];		/* iklj coord quadruplet for a recursion */
  int  a,b;		/* indices used for score lookups */
  int  w,y;		/* counters over nonterminals */
  int  parent;		/* index of a parent parsetree node */
  int  curr;		/* index of current parsetree code */
  int  e;		/* counter over atoms */
  int  r;		/* index of a rule */
  int  d1,d2;		/* optimum values of d1, d2 iterators */
  int  i,j,d;		/* seq coords */
  int  reachable;       /* TRUE if w *=> i..j */
  int  nequiv;	        /* number of equivalent alternatives for a traceback */
  int  x;		/* a random choice from nequiv */

  /* Initialize the parse tree.
   */
  T = Parsetree_Create();

  /* Initialize <alts> and <rng>, for stochastic traceback among
   * possibly ambiguous alternative parsetrees.
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

      /* Add this node to the parse tree.
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

      /* Figure out how we can traceback from here.
       */
      reachable = dp_recursion(cyk, G, ss, L, c, j, d, w, alts);

      /* That should've worked; alts now should contain one or more
       * alternatives for possible rules to use. Make sure.
       */
      if (!reachable) Die("can't reach w,i,j");
      
      /* Choose one of the alternatives at random
       */
      nequiv = esl_stack_ObjectCount(alts) / 3; /* how many solutions? */
      x = esl_rnd_Choose(rng, nequiv);          /* uniformly, 0.nequiv-1 */
      esl_stack_DiscardTopN(alts, x*3);         /* dig down to choice */
      esl_stack_IPop(alts, &d2);                /* pop it off, in rev order */
      esl_stack_IPop(alts, &d1);
      esl_stack_IPop(alts, &r);

      /* Record the rule. 
       * Then, for each nonterminal w in that rule, push relevant quad
       * (parent, w, i, j) onto <ns> stack.
       */
      rp              = &(G->pr[w][r]);
      c[COORD_K]      = c[COORD_I] + d1 - 1;
      c[COORD_L]      = c[COORD_J] - d2 + 1;
      T->node[curr].r = r;
      T->node[curr].k = c[COORD_K];
      T->node[curr].l = c[COORD_L];

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
    } /* end of while loop, while there's still traceback to do */

  esl_stack_Destroy(ns);
  esl_stack_Destroy(alts);
  esl_randomness_Destroy(rng);
  *ret_T = T;
  return 1;
}


/* Function:  ssCYK_Create(), ssCYK_Destroy()
 * Incept:    SRE, Fri Nov 19 09:53:21 2004 [St. Louis]
 *
 * Purpose:   Allocate (free) an ssCYK DP matrix, indexed
 *            cyk[w/32][j][d]; bit w%32 is TRUE/FALSE for
 *            whether state w can produce j,d.
 *
 * Args:      M - number of nonterminals in grammar
 *            L - length of sequence
 *
 * Returns:   alloc: ptr to allocated 3D CYK matrix
 *            free:  void
 *
 * Xref:      STL8/p132
 */
SSCYKVAL ***
ssCYK_Create(int M, int L)
{
  SSCYKVAL ***cyk;
  int    j,w;
  int    pos;
  int    ndecks;

  ndecks = M/32 + 1;
  cyk = malloc(sizeof(SSCYKVAL **) * ndecks);
  for (w = 0; w < ndecks; w++)	/* w counts over decks of 32 nonterminals */
    {
      cyk[w]    = malloc(sizeof(SSCYKVAL *) * (L+1));
      cyk[w][0] = malloc(sizeof(SSCYKVAL)   * ((L+2)*(L+1))/2);
      pos = 1;
      for (j = 1; j <= L; j++)
	{
	  cyk[w][j] = cyk[w][0] + pos;
	  pos += j+1;
	}
    }
  return cyk;
}
void
ssCYK_Destroy(SSCYKVAL ***cyk, int M)
{
  int w, ndecks;

  ndecks = M/32 + 1;
  for (w = 0; w < ndecks; w++)
    {
      free(cyk[w][0]);
      free(cyk[w]);
    }
  free(cyk);
}

/* Function:  ssCYK_Dump()
 * Incept:    SRE, Wed Mar 23 09:34:39 2005 [St. Louis]
 *
 * Purpose:   Dumps a ssCYK matrix to a stream (often stdout).
 */
void
SSCYK_Dump(FILE *fp, SSCYKVAL ***cyk, int M, int L)
{
  int j,d;
  int w;

  for (w = 0; w < M; w++)
    {
      for (j = 0; j <= L; j++)
	{
	  for (d = 0; d <= j; d++)
	    if (cyk[w/32][j][d] & 1<<(w%32)) fprintf(fp, "1 ");
	    else                             fprintf(fp, "0 ");
	  fputc('\n', fp);
	}
      fputc('\n', fp);
    }

}



static int
dp_recursion(SSCYKVAL ***cyk, GRAMMAR *G, char *ss, int L, 
	     int c[4], int j, int d, int w, ESL_STACK *alts)
{
  RULE     *rp;			/* convenience ptr to a rule              */
  int       eofw;		/* "e of w", index of emission dist */
  int       a,b;		/* indices used for score lookups */
  int       y;			/* index of a nonterminal */
  int       r;			/* counter over possible rules */
  int       e;			/* counter over atoms for a rule */
  int       n;			/* counter over emitted residues */
  int       d1, d1_min;		/* d1 iterator, for coord k */
  int       d2, d2_min;		/* d2 iterator, for coord l */
  int       ruleworks;		/* TRUE if this rule works */
  int       status;		/* TRUE if any rule works */

  status = FALSE;
  if (alts != NULL) esl_stack_Reuse(alts);
  for (r = 0; r < G->nrules[w]; r++)
    {
      /* There are three "boundary condition" tests here:
       *   1. The rule is incapable of generating a production of length < d.
       *   2. The rule contains only terminals, so it generates a fixed d, and
       *      this d ain't it.
       *   3. d=0, but this rule isn't an epsilon rule; 
       *      as a special case, we require that d=0 be generated by 
       *      an epsilon production, and disallow rules like S->SS, to
       *      prevent a runaway (Yule?) process.
       */
      rp  = &(G->pr[w][r]);
      if (d < G->rule_mind[w][r])                                 continue;
      if (G->pr[w][r].is_allterminals && d != G->rule_mind[w][r]) continue;
      if (d == 0 && ! rp->is_allterminals)                        continue;

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
           * Figure out if this rule can generate i..j.
	   */
	  ruleworks = TRUE;	/* 'til proven otherwise */
	  for (e = 0; e < rp->natoms && ruleworks == TRUE; e++)
	    {
	      switch (rp->atomtype[e]) {
	      case EPSILON_ATOM:
		if (d > 0) ruleworks = FALSE;
		break;
		
	      case NONTERMINAL_ATOM:
		a   = c[rp->coordbase[e][0]] + rp->offset[e][0];
		b   = c[rp->coordbase[e][1]] + rp->offset[e][1];
		y   = rp->nterm_idx[e];
		if (a < 0 || a > L || b < 0 || b > L) /* boundaries */
		  ruleworks = FALSE;
		else if ((cyk[y/32][b][b-a+1] & (1<<(y%32))) == 0)
		  ruleworks = FALSE;
		break;

	      case EMISSION_ATOM:
		eofw = rp->edist_idx[e];
		if (G->edist[eofw].is_basepair) 
		  {		/* assume coord 0 is left, 1 is right */
		    a = c[rp->coordbase[e][0]] + rp->offset[e][0]; 
		    b = c[rp->coordbase[e][1]] + rp->offset[e][1]; 
		    if      (b < a) exit(1);
		    else if (a < 1 || a > L)                  ruleworks = 0;
		    else if (b < 1 || b > L)                  ruleworks = 0;
		    else if (strchr("<([{", ss[a-1]) == NULL) ruleworks = 0;
		    else if (strchr(">)]}", ss[b-1]) == NULL) ruleworks = 0;
		  }
		else
		  {
		    for (n = 0; n < rp->ncoords[e]; n++)
		      {
			a = c[rp->coordbase[e][n]] + rp->offset[e][n]; 
			if      (a < 1 || a > L) 
			  ruleworks = 0;
			else if (strchr("<>()[]{}", ss[a-1]) != NULL)
			  ruleworks = 0;
		      }
		  }
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

	    }/* this ends loop over atoms <e>; we know if "ruleworks". */
	  
	  if (ruleworks)
	    {
	      status = TRUE;	/* at least one rule works */
	      if (alts != NULL) 
		{		/* store alternative solutions */
		  esl_stack_IPush(alts, r);   /* push: r,d1,d2; */
		  esl_stack_IPush(alts, d1);  /* (caller pops d2,d1,r) */
		  esl_stack_IPush(alts, d2);
		}
	    }
	} while (--d2 >= d2_min); /* end of the d2 iterator's do loop */
      } while (--d1 >= d1_min);   /* end of the d1 iterator's do loop */

    } /* end loop over r; all possible rules for this nonterm w */
  return status;
}


