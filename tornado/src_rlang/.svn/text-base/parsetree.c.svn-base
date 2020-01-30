/* parsetree.c
 * The generalized parse tree structure.
 * 
 * SRE, Fri Mar 11 10:21:47 2005 [St. Louis]
 * SVN $Id$
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "util.h"
#include "grammar.h"
#include "parsetree.h"


/* Function:  Parsetree_Create()
 * Incept:    SRE, Fri Mar 11 10:23:44 2005 [St. Louis]
 *
 * Purpose:   Allocates a new parse tree structure.
 * 
 * Returns:   NULL on allocation failure.
 */
PARSETREE *
Parsetree_Create(void)
{
  PARSETREE *T;

  T = malloc(sizeof(PARSETREE));
  if (T == NULL) Die("parsetree malloc failed");

  T->node = malloc(sizeof(PTREENODE) * PARSETREE_ALLOCSIZE);
  if (T->node == NULL) Die("parsetree malloc failed");

  T->n      = 0;
  T->nalloc = PARSETREE_ALLOCSIZE;
  return T;
}


/* Function:  Parsetree_Expand()
 * Incept:    SRE, Fri Mar 11 10:35:01 2005 [St. Louis]
 *
 * Purpose:   Doubles the node allocation inside of a
 *            parsetree. Caller usually tests if 
 *            T->n == T->nalloc to decide whether an
 *            Expand() is needed.
 */
void
Parsetree_Expand(PARSETREE *T)
{
  T->node = realloc(T->node, sizeof(PTREENODE) * (T->nalloc*2));
  if (T->node == NULL) Die("parsetree realloc failed");
  T->nalloc *= 2;
}


/* Function:  Parsetree_Destroy()
 * Incept:    SRE, Fri Mar 11 10:32:03 2005 [St. Louis]
 *
 * Purpose:   Deallocates a parsetree.
 */
void
Parsetree_Destroy(PARSETREE *T)
{
  if (T == NULL) return;
  if (T->node != NULL) free(T->node);
  free(T);
  return;
}

/* Function:  Parsetree_Dump()
 * Incept:    SRE, Sat Mar 19 06:54:05 2005 [St. Louis]
 *
 * Purpose:   For debugging purposes; dump a tabular view of the
 *            contents of <T> to the stream <fp>.
 */
void
Parsetree_Dump(FILE *fp, PARSETREE *T)
{
  int i;
  
  printf("%2s %2s %2s %4s %4s %4s %4s %4s %4s %4s\n",
	 "#", "w", "r", "i", "k", "l", "j", "up", "left", "rght");
  printf("%2s %2s %2s %4s %4s %4s %4s %4s %4s %4s\n",
	 "--", "--", "--", "----", "----", "----", "----", "----", "----", "----");
  for (i = 0; i < T->n; i++)
    {
      printf("%2d %2d %2d %4d %4d %4d %4d %4d %4d %4d\n",
	     i,
	     T->node[i].w, T->node[i].r, 
	     T->node[i].i, T->node[i].k, T->node[i].l, T->node[i].j,
	     T->node[i].up, T->node[i].left, T->node[i].right);
    }
}


/* 
 * 
 * The grammar <G> is in counts form. Caller zeros it before
 * starting to count parse trees into it. We're counting into
 * three fields: <G->tp>, the transition probabilities; 
 * <G->edist>, the emission probabilities; and <G->ldist>,
 * the length distributions. All of these allow tying, so
 * we're also looking at <G->tdist_idx>, <G->pr[][].edist_idx]>
 * and <G->pr[][].ldist_idx>. 
 * 
 * The parsetree is already laid out & numbered in a preorder tree
 * traversal - so, no need to use a pushdown stack to traverse the
 * tree.
 */
void
Parsetree_Count(PARSETREE *T, GRAMMAR *G, char *dsq, int L, double wgt)
{
  int curr;			/* node in the parse tree */
  int w;			/* index of current nonterminal */
  int r;			/* which rule this nonterminal used */
  int tofw;			/* index of transition distribution for nonterm w*/
  RULE *rp;			/* convenience ptr to a rule */
  int c[4];			/* coords */
  int x;			/* index of an emission */
  int e;			/* counter over atoms */

  for (curr = 0; curr < T->n; curr++)
    {
      w          = T->node[curr].w;
      r          = T->node[curr].r;
      c[COORD_I] = T->node[curr].i;
      c[COORD_J] = T->node[curr].j;
      c[COORD_K] = T->node[curr].k;
      c[COORD_L] = T->node[curr].l;

      rp   = &(G->pr[w][r]);
      tofw = G->tdist_idx[w];

      G->tp[tofw][r] += wgt;

      for (e = 0; e < rp->natoms; e++)
	if (rp->atomtype[e] == EMISSION_ATOM)
	  {
	    x = EmissionAtomIndex(dsq, L, c, rp, e);
	    if (x != -1) G->edist[rp->edist_idx[e]].ep[x] += wgt;
	  }
    }
}
