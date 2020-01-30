/* grammar.c
 * Implementation of a generalized RNA SCFG data structure.
 * 
 * SRE, Wed Mar 23 10:32:58 2005 [St. Louis]
 * SVN $Id$
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

#include <easel.h>
#include <esl_fileparser.h>
#include <esl_vectorops.h>

#include "util.h"
#include "grammar.h"

static int
integer_power(int base, int n)
{				/* n>=0 and small. */
  int result = 1;
  while (n--) result *= base;
  return result;
}

GRAMMAR *
Grammar_Create(void)
{
  GRAMMAR *G;
  G      = malloc(sizeof(GRAMMAR));
  G->M     = 0;
  G->ntd   = 0;
  G->ned   = 0;
  G->nld   = 0;
  G->ldist = NULL;
  return G;
}

/* Function:  Grammar_Zero()
 * Incept:    SRE, Fri Mar 18 08:57:15 2005 [St. Louis]
 *
 * Purpose:   Zeros all the probability distributions (transitions,
 *            emissions, and lengths) in preparation for counting new
 *            training data into the SCFG.
 */
void
Grammar_Zero(GRAMMAR *G)
{
  int i;			/* counter over distributions */
  int n;			/* number of emissions  */

  /* Transition distributions
   */
  for (i = 0; i < G->ntd; i++)
    esl_vec_DSet(G->tp[i], G->tn[i], 0.);
  
  /* Emission distributions
   */
  for (i = 0; i < G->ned; i++)
    {
      n = integer_power(4, G->edist[i].n);
      esl_vec_DSet(G->edist[i].ep, n, 0.);
    }

  /* Length distributions */
  for (i = 0; i < G->nld; i++)
    esl_vec_DSet(G->ldist[i].lp, G->ldist[i].max+1, 0.);
}


void
Grammar_Destroy(GRAMMAR *G)
{
  int eofw, lofw;
  
  for (eofw = 0; eofw < G->ned; eofw++)
    {
      free(G->edist[eofw].ep);
      free(G->edist[eofw].esc);
    }
  if (G->edist != NULL) 
    free(G->edist);

  for (lofw = 0; lofw < G->nld; lofw++)
    {
      free(G->ldist[lofw].lp);
      free(G->ldist[lofw].lsc);
    }
  if (G->ldist != NULL) 
    free(G->ldist);

  free(G);
}

/* Function:  Grammar_Dump()
 * Incept:    SRE, Wed Nov 24 07:39:36 2004 [St. Louis]
 *
 * Purpose:   Prints out contents of a grammar, for debugging
 *            purposes.
 *
 * Args:      G - the grammar
 *
 * Returns:   (void)
 */
void
Grammar_Dump(FILE *fp, GRAMMAR *G)
{
  int w;			/* counter over nonterminals */
  int r;			/* counter over production rules */
  int a;			/* counter over atoms in rule */
  int c;			/* counter over coords in an atom */
  int tofw;			/* "t of w": transition dist for this nonterm */
  RULE *rp;


  fprintf(fp, "Nonterminals : %d\n", G->M);
  for (w = 0; w < G->M; w++)
    {
      fprintf(fp, "NT #%d -> [mind=%d] [%d rules] \n", w, G->nt_mind[w], G->nrules[w]);
      tofw = G->tdist_idx[w];
      for (r = 0; r < G->nrules[w]; r++)
	{
	  rp = &(G->pr[w][r]);
	  fprintf(fp, "\trule %d, p=%.4f, sc=%d: [mind=%d] %d atoms:\n", r, 
		 G->tp[tofw][r], G->tsc[tofw][r], 
		 G->rule_mind[w][r], rp->natoms);
	  
	  for (a = 0; a < rp->natoms; a++)
	    {
	      fprintf(fp, "\t\tatom %2d [mind=%2d]", a, rp->atom_mind[a]);

	      switch (rp->atomtype[a]) {
	      case EPSILON_ATOM:     fprintf(fp, "[\epsilon]"); break;
	      case NONTERMINAL_ATOM: fprintf(fp, "NT #%d ", rp->nterm_idx[a]); break;
	      case EMISSION_ATOM:    fprintf(fp, "emit: "); break;
	      case MONOSEGMENT_ATOM: fprintf(fp, "unimplemented!"); break;
	      case DISEGMENT_ATOM:   fprintf(fp, "unimplemented!"); break;
	      default:               Die("unrecognized atomtype");
	      }
	      
	      putchar('(');
	      for (c = 0; c < rp->ncoords[a]; c++)
		{
		  if (c != 0) putchar(',');
		  switch (rp->coordbase[a][c]) {
		  case COORD_I: putchar('i'); break;
		  case COORD_J: putchar('j'); break;
		  case COORD_K: putchar('k'); break;
		  case COORD_L: putchar('l'); break;
		  default:      Die("unrecognized coord");
		  }
		  if      (rp->offset[a][c] > 0) fprintf(fp, "+%d", rp->offset[a][c]);
		  else if (rp->offset[a][c] < 0) fprintf(fp, "%d",  rp->offset[a][c]);
		}
	      putchar(')');
	      putchar('\n');
	    }
	}

    }
  
}



/* Function:  Grammar_CreateNussinovTest()
 * Incept:    SRE, Sun Nov 21 15:57:43 2004 [St. Louis]
 *
 * Purpose:   The grammar is:
 *                  S -> \epsilon | a S a' | a S | S a | S S 
 *                  
 *            Nonterminals     : 1
 *            Production rules : 5
 *              rule 0:  epsilon.      
 *              rule 1:  emit-i + S(i+1,j-1) + emit-j
 *              rule 2:  emit-i + S(i+1,j)
 *              rule 3:  emit-j + S(i,j-1)
 *              rule 4:  S(i,k) + S(k+1,j)
 */
GRAMMAR *
Grammar_CreateNussinovTest(void)
{
  GRAMMAR *G;
  int      r;
  int      x;

  G = Grammar_Create();
  G->M = 1;			/* 1 nonterminal, S */
  G->nrules[0] = 5;

  /* Set up one transition dist to use: all zero score.
   */
  G->tdist_idx[0] = 0;		/* NT 0 uses distribution #0 */
  G->ntd          = 1;		
  G->tn[0]        = G->nrules[0]; /* Distribution #0 has this many rules  */
  for (r = 0; r < G->nrules[0]; r++)
    {
      G->tp[0][r] = 0.;
      G->tsc[0][r] = 0;
    }

  /* Set up two emission distributions to use.
   * #0 = singlet emission.
   * #1 = pair emission.
   */
  G->ned          = 2;
  G->edist        = malloc(sizeof(EDIST) * 2);
  G->edist[0].n           = 1;		/* singlet */
  G->edist[0].ep          = malloc(sizeof(double) *4);
  G->edist[0].esc         = malloc(sizeof(double) *4);
  G->edist[0].is_basepair = FALSE;

  G->edist[1].n           = 2;		/* doublet */
  G->edist[1].ep          = malloc(sizeof(double) *16);
  G->edist[1].esc         = malloc(sizeof(double) *16);
  G->edist[1].is_basepair = TRUE;

  for (x = 0; x < 4; x++) { 
    G->edist[0].ep[x]  = 0.0;	/* probabilities unused */
    G->edist[0].esc[x] = 0;	/* singlets score 0. */    
  }

  for (x = 0; x < 16; x++) { 
    G->edist[1].ep[x]  = 0.0;	    /* probabilities unused. */
    G->edist[1].esc[x] = -CYKINFTY; /* prohibit anything but base pairs. */
  }
  /* +1 per base pair, ad hoc scoring: */
  G->edist[1].esc[3] = G->edist[1].esc[6] = G->edist[1].esc[9] = G->edist[1].esc[12] = 1;

  /* Rule #0 (of 5): S -> \epsilon, null production.
   * 1 atom: \epsilon.
   */
  G->pr[0][0].natoms            = 1;
  /* atom 0: \epsilon */
  G->pr[0][0].atomtype[0]       = EPSILON_ATOM;
  G->pr[0][0].edist_idx[0]      = 0;
  G->pr[0][0].ncoords[0]        = 0;	
  /* don't need iterators */
  G->pr[0][0].d1_iterator_state = ITERATOR_OFF;
  G->pr[0][0].d2_iterator_state = ITERATOR_OFF;

  /* Rule #1 (of 5): S -> a S a'. 
   * 2 atoms: pairemission, and nonterminal
   */
  G->pr[0][1].natoms            = 2;
  /* atom 0 */
  G->pr[0][1].atomtype[0]       = EMISSION_ATOM;
  G->pr[0][1].edist_idx[0]      = 1;       /* pairwise emission dist */
  G->pr[0][1].ncoords[0]        = 2;	   /* pair emitter */
  G->pr[0][1].coordbase[0][0]   = COORD_I;  /* of residue i */
  G->pr[0][1].offset[0][0]      = 0;        /* (i+0) */
  G->pr[0][1].coordbase[0][1]   = COORD_J;  /* and residue j */
  G->pr[0][1].offset[0][1]      = 0;        /* (i+0) */
  /* atom 1 */
  G->pr[0][1].atomtype[1]       = NONTERMINAL_ATOM;
  G->pr[0][1].nterm_idx[1]      = 0;
  G->pr[0][1].ncoords[1]        = 2;	
  G->pr[0][1].coordbase[1][0]   = COORD_I;  /* i+1 */
  G->pr[0][1].offset[1][0]      = 1;        
  G->pr[0][1].coordbase[1][1]   = COORD_J;  /* j-1 */
  G->pr[0][1].offset[1][1]      = -1;        
  /* don't need iterators */
  G->pr[0][1].d1_iterator_state = ITERATOR_OFF;
  G->pr[0][1].d2_iterator_state = ITERATOR_OFF;

  /* Rule #2 (of 5): S -> a S. 
   * 2 atoms, a singlet emitter i, and nonterminal i+1,j.
   */
  G->pr[0][2].natoms            = 2;
  /* atom 0 */
  G->pr[0][2].atomtype[0]       = EMISSION_ATOM;
  G->pr[0][2].edist_idx[0]      = 0;
  G->pr[0][2].ncoords[0]        = 1;	   /* singlet emitter */
  G->pr[0][2].coordbase[0][0]   = COORD_I;  /* of residue i */
  G->pr[0][2].offset[0][0]      = 0;        /* (i+0) */
  /* atom 1 */
  G->pr[0][2].atomtype[1]       = NONTERMINAL_ATOM;
  G->pr[0][2].nterm_idx[1]      = 0;
  G->pr[0][2].ncoords[1]        = 2;	
  G->pr[0][2].coordbase[1][0]   = COORD_I;  /* i+1 */
  G->pr[0][2].offset[1][0]      = 1;        
  G->pr[0][2].coordbase[1][1]   = COORD_J;  /* j */
  G->pr[0][2].offset[1][1]      = 0;        
  /* don't need iterators */
  G->pr[0][2].d1_iterator_state = ITERATOR_OFF;
  G->pr[0][2].d2_iterator_state = ITERATOR_OFF;


  /* Rule #3 (of 5): S -> S a
   * 2 atoms: nonterminal i,j-1 and j.
   */
  G->pr[0][3].natoms            = 2;
  /* atom 0: nonterminal S(i,j-1) */
  G->pr[0][3].atomtype[0]       = NONTERMINAL_ATOM;
  G->pr[0][3].nterm_idx[0]      = 0;
  G->pr[0][3].ncoords[0]        = 2;	
  G->pr[0][3].coordbase[0][0]   = COORD_I;  /* i */
  G->pr[0][3].offset[0][0]      = 0;        
  G->pr[0][3].coordbase[0][1]   = COORD_J;  /* j-1 */
  G->pr[0][3].offset[0][1]      = -1;        
  /* atom 1: emission of x_j */
  G->pr[0][3].atomtype[1]       = EMISSION_ATOM;
  G->pr[0][3].edist_idx[1]      = 0;
  G->pr[0][3].ncoords[1]        = 1;	   /* singlet emitter */
  G->pr[0][3].coordbase[1][0]   = COORD_J;  /* of residue j */
  G->pr[0][3].offset[1][0]      = 0;        /* (j+0) */
  /* don't need iterators */
  G->pr[0][3].d1_iterator_state = ITERATOR_OFF;
  G->pr[0][3].d2_iterator_state = ITERATOR_OFF;
  

  /* Rule #4 (last of 5, 0..4): S -> S S
   * 2 atoms: nonterminal S(i,k) and nonterminal S(k+1,j)
   * We need the d1 iterator to get a valid k.
   */
  G->pr[0][4].natoms            = 2;
  /* atom 0: nonterminal S(i,k) */
  G->pr[0][4].atomtype[0]       = NONTERMINAL_ATOM;
  G->pr[0][4].nterm_idx[0]      = 0;
  G->pr[0][4].ncoords[0]        = 2;	
  G->pr[0][4].coordbase[0][0]   = COORD_I;  /* i */
  G->pr[0][4].offset[0][0]      = 0;        
  G->pr[0][4].coordbase[0][1]   = COORD_K;  /* k */
  G->pr[0][4].offset[0][1]      = 0;        
  /* atom 1: nonterminal S(k+1,j) */
  G->pr[0][4].atomtype[1]       = NONTERMINAL_ATOM;
  G->pr[0][4].nterm_idx[1]      = 0;
  G->pr[0][4].ncoords[1]        = 2;	
  G->pr[0][4].coordbase[1][0]   = COORD_K;  /* k+1 */
  G->pr[0][4].offset[1][0]      = 1;
  G->pr[0][4].coordbase[1][1]   = COORD_J;  /* j */
  G->pr[0][4].offset[1][1]      = 0;
  /* need d1 iterator */
  G->pr[0][4].d1_iterator_state = ITERATOR_ON;
  G->pr[0][4].d1_iterator_min   = 0; /* FIXME: or should it be -1 for unused? */
  G->pr[0][4].d1_iterator_max   = INT_MAX; 
  G->pr[0][4].d2_iterator_state = ITERATOR_OFF;

  return G;
}


/* Function:  Grammar_SetMinDistances()
 * Incept:    SRE, Sat Nov 20 17:04:01 2004 [St. Louis]
 *
 * Purpose:   Takes a generalized grammar under construction, and sets
 *            the minimum distances (_mind) information that we need
 *            for initialization/boundary conditions.
 *
 * Args:      G   - grammar under construction.
 *
 * Returns:   Same grammar, but now with _mind minimum distances set.
 *
 * Xref:      STL8/p132-133.
 */
void
Grammar_SetMinDistances(GRAMMAR *G)
{
  int d;			/* subsequence lengths (distances) */
  int dmax;			/* maximum d to allow before choking */
  int w;			/* indices of nonterminals         */
  int r;			/* counter over production rules   */
  int a;			/* counter over atoms              */
  int atoms_finished;
  int nt_finished;
  int atoms_sum;

  /* 1. Initialize all emission _mind's to their min length; 
   *    all nonterminal atom _mind's to -1 representing "not set yet";
   *    all rule and nt _mind's to -1 as well.
   *    
   *    Additionally, scan each rule for nonterminals. If it has
   *    none, it is composed of only terminals (including epsilon), 
   *    and therefore generates a fixed-length production that is
   *    always = rule_mind. Set is_allterminals flag if this is true.
   */
  for (w = G->M-1; w >= 0; w--)	/* for all nonterminals... */
    {
      G->nt_mind[w] = -1;
      for (r = 0; r < G->nrules[w]; r++) /* for all rules... */
	{
	  G->rule_mind[w][r] = -1;
	  G->pr[w][r].is_allterminals = TRUE; /* 'til proven otherwise */
	  for (a = 0; a < G->pr[w][r].natoms; a++) /* for all atoms... */
	    {
	      switch (G->pr[w][r].atomtype[a]) {
	      case EPSILON_ATOM:
		G->pr[w][r].atom_mind[a] = 0;
		break;
	      case EMISSION_ATOM:
		G->pr[w][r].atom_mind[a] = G->pr[w][r].ncoords[a];
		break;
	      case NONTERMINAL_ATOM: 
		G->pr[w][r].is_allterminals = FALSE;
		G->pr[w][r].atom_mind[a]    = -1; 
		break;
	      case MONOSEGMENT_ATOM:
		G->pr[w][r].atom_mind[a] = G->ldist[G->pr[w][r].ldist_idx[a]].min;
		break;
	      case DISEGMENT_ATOM:
		G->pr[w][r].atom_mind[a] = 2 * G->ldist[G->pr[w][r].ldist_idx[a]].min;
		break;
	      default: Die("no such atom type");
	      }
	    }
	}
    }

  /* 2. Now, starting from d=0, try to fill in the rest.
   * 
   *    We already know the minlength of any EMISSION,
   *    MONOSEGMENT, or PAIRSEGMENT atom. It's the NONTERMINAL atoms
   *    that we have to determine. The minlength of a NONTERMINAL is
   *    the minimum of the minlength of its production rules; the
   *    minlength of a rule is the sum of the minlengths of its atoms.
   *    
   *    I don't see an easier way to do this than to start at d=0, see
   *    which nonterminals can be given a minlength of 0 (setting
   *    atoms and rules that can be set along the way); bump d++, and
   *    reiterate; basically a kind of DP algorithm. I've tried to
   *    think through recursive tree traversal strategies, but don't
   *    think there's an efficient one.
   *    
   *    The trap to avoid: the *first* settable length for a rule is
   *    not necessarily the *minimum* length for the rule. Watch out
   *    for a situation like:
   *       S -> T | a
   *       T -> [aaaaa] | aS
   *    where the first settable length for T is 5, but the minimum
   *    length is actually 2 via the second production, because S
   *    turns out to have a minlength of 1.
   */
  dmax = 10000;			/* an arbitrarily large d, just to prevent infinite loop */
  for (d = 0; d <= dmax; d++) {
    nt_finished = TRUE;		
    for (w = G->M-1; w >= 0; w--)	/* for all nonterminals... */
      {
	/* Already finished this nonterminal? Then skip it.
	 */
	if (G->nt_mind[w] != -1) continue;

	/* Else, check all rules for this nonterminal.  Note that by
         * definition, *none* of the rules for this nonterminal can be
         * done yet, else we'd have minlength for the nonterminal.
	 */
	for (r = 0; r < G->nrules[w]; r++) /* for all rules... */
	  {
	    atoms_finished = TRUE;
	    atoms_sum      = 0;
	    for (a = 0; a < G->pr[w][r].natoms; a++) /* for all atoms... */
	      {
		/* Only NONTERMINAL atoms can be undetermined at this point. 
		 * Note that if it can't be set yet, this resets it to -1 anyway;
		 * don't actually need to check if it can be set or not.
		 */
		if (G->pr[w][r].atom_mind[a] == -1)
		  G->pr[w][r].atom_mind[a] = G->nt_mind[G->pr[w][r].nterm_idx[a]];

		/* If it's still undetermined,
		 * flip the atoms_finished flag to FALSE.
		 */
		if (G->pr[w][r].atom_mind[a] == -1) atoms_finished = FALSE;
		else  atoms_sum += G->pr[w][r].atom_mind[a];
	      } /* end loop over atoms a */

	    /* When we do have min lengths for all nonterminal atoms, 
	     * we know the min length of the rule, for sure.
	     */
	    if (atoms_finished && G->rule_mind[w][r] == -1) 
	      G->rule_mind[w][r] = atoms_sum;

	    /* But, the key: the min length of a nonterminal is not
	     * the minlength of the first rule we finish; *now* we have
	     * to test against d, and be patient; our d will come.
	     */
	    if (G->nt_mind[w] == -1 &&
		G->rule_mind[w][r] != -1 &&
		G->rule_mind[w][r] <= d)
	      G->nt_mind[w] = G->rule_mind[w][r];
	  } /* end loop over rules r */

	if (G->nt_mind[w] != -1) nt_finished = FALSE;
      } /* end loop over nonterminals w */

    /* Once we have all the nonterminals, we know everything we need to know.
     * Break out of the iteration, and finish up with one more pass through the
     * grammar.
     */
    if (nt_finished) break;
  } /* end loop over d */
  if (d > dmax) Die("failed to initialize grammar");

  /* Now, we have all the nonterminal minimum lengths. That lets us
   * make one final pass through the entire grammar, and set all the
   * atom and rule minimum lengths. (It should be better to make this
   * final pass, as opposed to plodding through d stepwise 'til we're
   * done.) The code is basically the same as above, most comments
   * removed.
   */
  for (w = G->M-1; w >= 0; w--)	/* for all nonterminals... */
    {
      for (r = 0; r < G->nrules[w]; r++) /* for all rules... */
	{
	  if (G->rule_mind[w][r] != -1) continue; 
	  atoms_sum      = 0;
	  for (a = 0; a < G->pr[w][r].natoms; a++) /* for all atoms... */
	    {
	      if (G->pr[w][r].atom_mind[a] == -1) /* can only be a nonterminal... */
		G->pr[w][r].atom_mind[a] = G->nt_mind[G->pr[w][r].nterm_idx[a]];
	      atoms_sum += G->pr[w][r].atom_mind[a];
	    }
	  if (G->rule_mind[w][r] == -1) 
	    G->rule_mind[w][r] = atoms_sum;
	} /* end loop over rules r */
    } /* end loop over nonterminals w */

  /* Was all that necessary? Seems there should be a better way.
   * In any case, we have all our minlengths set in G; return.
   */
}


/* Function:  Grammar_Write_Counts()
 * Incept:    SRE, Fri Mar 18 12:56:34 2005 [St. Louis]
 *
 * Purpose:   Save the parameters of a grammar <G> to an open stream <fp>, 
 *            as counts.
 *
 * Xref:      STL9/52.
 */
void
Grammar_Write_Counts(FILE *fp, GRAMMAR *G)
{
  int i;			/* index over distributions */
  int x;			/* index over rules, emissions, or lengths */
  int n;			/* number of emissions */
  
  /* The transitions.
   * <#> <n> <p_1>..<p_n>
   */
  fprintf(fp, "# Transition probability distributions.\n");
  fprintf(fp, "# <ntd>\n");
  fprintf(fp, "#   <#> <nr> <p_1>..<p_n> for each 1..<ntd>.\n");
  fprintf(fp, "%d\n", G->ntd);
  for (i = 0; i < G->ntd; i++)
    {
      fprintf(fp, "  %-2d %-2d ", i, G->tn[i]);
      for (x = 0; x < G->tn[i]; x++)
	fprintf(fp, "%7.1f ", G->tp[i][x]);
      fprintf(fp, "\n");
    }
  fprintf(fp, "\n");

  /* The emissions.
   */
  fprintf(fp, "# Emission probability distributions.\n");
  fprintf(fp, "# <ned>\n");
  fprintf(fp, "#   <#> <nemit>\n");
  fprintf(fp, "#     <p_1> .. <p_{4^n}> for each 1..<ned>\n"); 
  fprintf(fp, "%d\n", G->ned);
  for (i = 0; i < G->ned; i++)
    {
      n = integer_power(4, G->edist[i].n);
      fprintf(fp, "  %2d  %1d\n    ", i, G->edist[i].n);
      for (x = 0; x < n; x++)
	{
	  if (x > 0  && (x%4 == 0)) fprintf(fp, "\n    ");
	  fprintf(fp, "%7.1f ", G->edist[i].ep[x]);
	}
      fprintf(fp, "\n");
    }
  fprintf(fp, "\n");

  /* The length distributions.
   */
  fprintf(fp, "# Length probability distributions (if any).\n");
  fprintf(fp, "# <nld>\n");
  fprintf(fp, "#    <#> <min> <max>\n");
  fprintf(fp, "#       <len>  <lp[len]>\n");
  fprintf(fp, "%d\n", G->nld);
  for (i = 0; i < G->nld; i++)
    {
      fprintf(fp, "  %d %d %d\n", i, G->ldist[i].min, G->ldist[i].max);
      for (x = G->ldist[i].min; x <= G->ldist[i].max; x++)
	fprintf(fp, "    %3d  %7.1f\n", x, G->ldist[i].lp[x]);
      fprintf(fp, "\n");
    }      
}

/* Function:  Grammar_Read_Counts()
 * Incept:    SRE, Sun Mar 20 18:41:44 2005 [St. Louis]
 *
 * Purpose:   Read in grammar counts from an open stream <fp>, 
 *            incrementing what's already in <G>. We use this
 *            to read saved "checkpoint" files, for bootstrapping and simple 
 *            parallelization.
 */
void
Grammar_Read_Counts(FILE *fp, GRAMMAR *G)
{
  ESL_FILEPARSER *efp;
  char *tok;
  int   n;
  int   status;
  int   i;
  int   x,nx;

  if ((efp = esl_fileparser_Create(fp)) == NULL)
    Die("Failed to open parser for input parameter file");
  esl_fileparser_SetCommentChar(efp, '#');

  /* Transitions section.
   * <ntd>
   * for each i=0..ntd-1: 
   *   <i> <tn[i]>
   *   for each x=0..tn[i]-1:
   *      <log tp[i][x]> 
   */
  if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
  if (G->ntd != atoi(tok)) Die("count file mismatches G");

  for (i = 0; i < G->ntd; i++)
    {
      if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
      if (atoi(tok) != i) goto FAILURE;
      if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
      if (G->tn[i] != atoi(tok)) Die("count file mismatches G");

      for (x = 0; x < G->tn[i]; x++)
	{
	  if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
	  G->tp[i][x] += atoi(tok);
	}
    }
  
  /* Emissions section.
   * <ned>
   * for each i=0..ned-1:
   *   <i>  <edist[i].n>
   *   for each x = 0..n-1:
   *      <log edist[i].ep[x]>
   */
  if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
  if (G->ned != atoi(tok)) Die("count file mismatches G");

  for (i = 0; i < G->ned; i++)
    {
      if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
      if (atoi(tok) != i) goto FAILURE;
      if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
      if (G->edist[i].n != atoi(tok)) Die("count file mismatches G");
      nx = integer_power(4, G->edist[i].n);
      
      for (x = 0; x < nx; x++)
	{
	  if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
	  G->edist[i].ep[x] += atoi(tok);
	}
    }

  /* Length distributions section.
   * <nld>
   * for each i=0..nld-1:
   *    <i> <min> <max>
   *    for each x = <min>..<max>:
   *       <x> <log(ldist[i].lp[x])>
   */
  if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
  if (G->nld != atoi(tok)) Die("count file mismatches G");

  for (i = 0; i < G->nld; i++)
    {
      if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
      if (atoi(tok) != i) goto FAILURE;
      if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
      if (G->ldist[i].min != atoi(tok)) Die("G and count file mismatch");
      if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
      if (G->ldist[i].max != atoi(tok)) Die("G and count file mismatch");

      for (x = G->ldist[i].min; x <= G->ldist[i].max; x++)
	{
	  if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
	  if (atoi(tok) != x) goto FAILURE;
	  if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
	  G->ldist[i].lp[x] += atoi(tok);
	}
    }

  esl_fileparser_Destroy(efp);
  return;

 FAILURE:
  Die("Parse failed.");
}


/* Function:  Grammar_Write()
 * Incept:    SRE, Sun Mar 20 18:38:24 2005
 *
 * Purpose:   Save the parameters of a grammar <G> to an open stream <fp>, as 
 *            log probabilities.
 *
 * Xref:      STL9/52.
 */
void
Grammar_Write(FILE *fp, GRAMMAR *G)
{
  int i;			/* index over distributions */
  int x;			/* index over rules, emissions, or lengths */
  int n;			/* number of emissions */
  
  /* The transitions.
   * <#> <n> <p_1>..<p_n>
   */
  fprintf(fp, "# Transition probability distributions.\n");
  fprintf(fp, "# <ntd>\n");
  fprintf(fp, "#   <#> <nr> <p_1>..<p_n> for each 1..<ntd>.\n");
  fprintf(fp, "%d\n", G->ntd);
  for (i = 0; i < G->ntd; i++)
    {
      fprintf(fp, "  %-2d %-2d ", i, G->tn[i]);
      for (x = 0; x < G->tn[i]; x++)
	fprintf(fp, "%7f ", log(G->tp[i][x]));
      fprintf(fp, "\n");
    }
  fprintf(fp, "\n");

  /* The emissions.
   */
  fprintf(fp, "# Emission probability distributions.\n");
  fprintf(fp, "# <ned>\n");
  fprintf(fp, "#   <#> <nemit> <p_1> .. <p_{4^n}> for each 1..<ned>\n"); 
  fprintf(fp, "%d\n", G->ned);
  for (i = 0; i < G->ned; i++)
    {
      n = integer_power(4, G->edist[i].n);
      fprintf(fp, "  %2d  %1d\n    ", i, G->edist[i].n);
      for (x = 0; x < n; x++)
	{
	  if (x > 0  && (x%4 == 0)) fprintf(fp, "\n    ");
	  fprintf(fp, "%7f ", log(G->edist[i].ep[x]));
	}
      fprintf(fp, "\n");
    }
  fprintf(fp, "\n");

  /* The length distributions.
   */
  fprintf(fp, "# Length probability distributions (if any).\n");
  fprintf(fp, "# <nld>\n");
  fprintf(fp, "#    <#> <min> <max>\n");
  fprintf(fp, "#       <len>  <lp[len]>\n");
  fprintf(fp, "%d\n", G->nld);
  for (i = 0; i < G->nld; i++)
    {
      fprintf(fp, "  %d %d %d\n", i, G->ldist[i].min, G->ldist[i].max);
      for (x = G->ldist[i].min; x <= G->ldist[i].max; x++)
	fprintf(fp, "    %3d  %7f\n", x, log(G->ldist[i].lp[x]));
      fprintf(fp, "\n");
    }      
}


/* Function:  Grammar_Read()
 * Incept:    SRE, Sun Mar 20 18:41:44 2005 [St. Louis]
 *
 * Purpose:   Read in grammar parameters from an open stream <fp>.
 *            The grammar must already have space for p's and sc's 
 *            allocated; and is_basepair must be set appropriately
 *            for any base pair emission distributions.
 */
void
Grammar_Read(FILE *fp, GRAMMAR *G)
{
  ESL_FILEPARSER *efp;
  char *tok;
  int   n;
  int   status;
  int   i;
  int   x,nx;

  if ((efp = esl_fileparser_Create(fp)) == NULL)
    Die("Failed to open parser for input parameter file");
  esl_fileparser_SetCommentChar(efp, '#');

  /* Transitions section.
   * <ntd>
   * for each i=0..ntd-1: 
   *   <i> <tn[i]>
   *   for each x=0..tn[i]-1:
   *      <log tp[i][x]> 
   */
  if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
  G->ntd = atoi(tok);

  for (i = 0; i < G->ntd; i++)
    {
      if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
      if (atoi(tok) != i) goto FAILURE;
      if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
      G->tn[i] = atoi(tok);

      for (x = 0; x < G->tn[i]; x++)
	{
	  if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
	  G->tp[i][x] = exp(atof(tok));
	}
      esl_vec_DNorm(G->tp[i], G->tn[i]);
    }
  
  /* Emissions section.
   * <ned>
   * for each i=0..ned-1:
   *   <i>  <edist[i].n>
   *   for each x = 0..n-1:
   *      <log edist[i].ep[x]>
   */
  if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
  G->ned = atoi(tok);

  for (i = 0; i < G->ned; i++)
    {
      if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
      if (atoi(tok) != i) goto FAILURE;
      if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
      G->edist[i].n = atoi(tok);
      nx = integer_power(4, G->edist[i].n);
      
      for (x = 0; x < nx; x++)
	{
	  if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
	  G->edist[i].ep[x] = exp(atof(tok));
	}
      esl_vec_DNorm(G->edist[i].ep, nx);
    }

  /* Length distributions section.
   * <nld>
   * for each i=0..nld-1:
   *    <i> <min> <max>
   *    for each x = <min>..<max>:
   *       <x> <log(ldist[i].lp[x])>
   */
  if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
  G->nld = atoi(tok);

  for (i = 0; i < G->nld; i++)
    {
      if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
      if (atoi(tok) != i) goto FAILURE;
      if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
      G->ldist[i].min = atoi(tok);
      if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
      G->ldist[i].max = atoi(tok);

      for (x = G->ldist[i].min; x <= G->ldist[i].max; x++)
	{
	  if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
	  if (atoi(tok) != x) goto FAILURE;
	  if ((status = esl_fileparser_GetToken(efp, &tok, &n)) != eslOK) goto FAILURE;
	  G->ldist[i].lp[x] = exp(atof(tok));
	}
      esl_vec_DNorm(G->ldist[i].lp, G->ldist[i].max+1);
    }

  esl_fileparser_Destroy(efp);
  return;

 FAILURE:
  Die("Parse failed.");
}


/* Function:  Grammar_Priorify()
 * Incept:    SRE, Mon Mar 21 11:50:54 2005 [St. Louis]
 *
 * Purpose:   Given a grammar <G> containing counts, add a +1 
 *            Laplace prior.
 *            
 *            (Eventually, we might make this more sophisticated,
 *            w/ Dirichlets.)
 */
void
Grammar_Priorify(GRAMMAR *G)
{
  int i, n;

  /* transitions */
  for (i = 0; i < G->ntd; i++)
    esl_vec_DIncrement(G->tp[i], G->tn[i], 1.0);

  /* emissions */
  for (i = 0; i < G->ned; i++)
    {
      n = integer_power(4, G->edist[i].n);
      esl_vec_DIncrement(G->edist[i].ep, n, 1.0);
    }

  /* lengths (don't add +1 to anything less than min) */
  for (i = 0; i < G->nld; i++)
    esl_vec_DIncrement(G->ldist[i].lp + G->ldist[i].min, 
		       G->ldist[i].max - G->ldist[i].min + 1, 
		       1.0);
}

/* Function:  Grammar_Normalize()
 * Incept:    SRE, Mon Mar 21 12:06:44 2005 [St. Louis]
 *
 * Purpose:   Given a grammar <G> containing counts (including pseudocounts
 *            from a prior, if any), normalize all parameter distributions
 *            to probabilities.
 */
void
Grammar_Normalize(GRAMMAR *G)
{
  int i, n;

  /* transitions */
  for (i = 0; i < G->ntd; i++)
    esl_vec_DNorm(G->tp[i], G->tn[i]);

  /* emissions */
  for (i = 0; i < G->ned; i++)
    {
      n = integer_power(4, G->edist[i].n);
      esl_vec_DNorm(G->edist[i].ep, n);
    }

  /* lengths */
  for (i = 0; i < G->nld; i++)
    esl_vec_DNorm(G->ldist[i].lp + G->ldist[i].min, 
		  G->ldist[i].max - G->ldist[i].min + 1);
}


  
/* Function:  Grammar_Scorify()
 * Incept:    SRE, Mon Mar 21 12:06:44 2005 [St. Louis]
 *
 * Purpose:   Given a grammar <G> containing valid probability parameters,
 *            calculate the score parameters (tsc, esc, lsc). Currently
 *            these are simply log probabilities, and CYK is returning
 *            log P(seq, structure | G). Eventually we might make these 
 *            log odds relative to a null model.
 */
void
Grammar_Scorify(GRAMMAR *G)
{
  int i, x, n;

  /* transitions */
  for (i = 0; i < G->ntd; i++)
    for (x = 0; x < G->tn[i]; x++)
      G->tsc[i][x] = Prob2Score(G->tp[i][x], 1.0);

  /* emissions */
  for (i = 0; i < G->ned; i++)
    {
      n = integer_power(4, G->edist[i].n);
      for (x = 0; x < n; x++)
	G->edist[i].esc[x] = Prob2Score(G->edist[i].ep[x], 1.0);
    }

  /* lengths */
  for (i = 0; i < G->nld; i++)
    for (x = G->ldist[i].min; x <= G->ldist[i].max; x++)
      G->ldist[i].lsc[x] = Prob2Score(G->ldist[i].lp[x], 1.0);
}


  
