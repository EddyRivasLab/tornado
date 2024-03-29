/* grm_sccyk.h
 * CYK algorithm for scoring a given structure using a generalized RNA SCFG.
 * 
 * ER, Mon Sep 22 11:39:08 EDT 2008 [Janelia]
 * SVN $Id$
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <easel.h>
#include <esl_sqio.h>
#include <esl_stack.h>
#include <esl_random.h>
#include <esl_wuss.h>

#include "grammar.h"		/* SCVAL is defined here, for scores. */
#include "grm_config.h"
#include "grm_cyk.h"
#include "grm_gmx.h"
#include "grm_parsetree.h"
#include "grm_sccyk.h"
#include "grm_sscyk.h"
#include "grm_util.h"

static int    dp_recursion(SCVAL *ret_bestsc, GMX *cyk, GRAMMAR *G, ESL_DSQ *dsq, BPT *bpt, int L, 
			   int c[4], int j, int d, int w, ESL_STACK *alts, char *errbuf);
static int    dp_aux_recursion_oneatthetime(GMX *cyk, GRAMMAR *G, ESL_DSQ *dsq, BPT *bpt, int L, 
					    int c[4], int j, int d, int dmid, int dmid_max, int v, char *errbuf);
static int    dp_aux_recursion_dmid(SCVAL *ret_bestsc, GMX *cyk, GRAMMAR *G, BPT *bpt, ESL_DSQ *dsq, int L, 
				    int c[4], RULE *rp, DRULE *jdr, LDIST *ldist, int d, int dmid, int d1, int d2, char *errbuf);
static int    dp_aux_stemr_recursion(SCVAL *cykstem, GRAMMAR *G, RULE *rp, DRULE *stemr, BPT *bpt, ESL_DSQ *dsq, 
				     int L, int d, int mid, int mid_max, int c[4], char *errbuf, int verbose);
static int    dp_recursion_atom_nonterminal(SCVAL *sc, SCVAL ***cyk, GRAMMAR *G, ATOM *A, 
					    int d, int L, int c[4], int rule_mind,  char *errbuf, int verbose);
static int    dp_recursion_atom_emission(SCVAL *sc, GRAMMAR *G, ATOM *A, BPT *bpt, 
					 ESL_DSQ *dsq, int L, int c[4], char *errbuf, int verbose);
static int    dp_recursion_atom_emission_iscompatible(ATOM *A, BPT *bpt, int L, int c[4], int *ret_iscompatible, char *errbuf, int verbose);
static int    dp_recursion_atom_monosegment(SCVAL *sc, GRAMMAR *G, ATOM *A, BPT *bpt, 
					    ESL_DSQ *dsq, int L, int c[4], char *errbuf, int verbose);
static int    dp_recursion_atom_disegment_full(SCVAL *sc, GRAMMAR *G, RULE *rp, ATOM *A, 
					       BPT *bpt, ESL_DSQ *dsq, int L, int c[4], char *errbuf, int verbose);
static int    dp_recursion_atom_disegment_joint(SCVAL *sc, SCVAL **cykaux,
						GRAMMAR *G, RULE *rp, DRULE *jdr, ATOM *A, BPT *bpt, 
						ESL_DSQ *dsq, int L, int d, int mid, int c[4], 
						ESL_STACK *alts, char *errbuf, int verbose);
static int    dp_recursion_atom_disegment_joint_order4(SCVAL *sc, GRAMMAR *G, RULE *rp, ATOM *A, 
						       BPT *bpt, ESL_DSQ *dsq, int L, int c[4], char *errbuf, int verbose);
static int    dp_recursion_atom_disegment_joint_order3(SCVAL *sc, SCVAL **cykaux,
						       GRAMMAR *G, RULE *rp, DRULE *jdr, ATOM *A, 
						       int L, int d, int mid, char *errbuf, int verbose);
static int    dp_recursion_atom_disegment_tied(SCVAL *sc, SCVAL *cykstem, GRAMMAR *G, RULE *rp, DRULE *stemr, ATOM *A, 
					       int L, int d, int mid, char *errbuf, int verbose);

/* Function:  scCYK()
 * Incept:    ER,  Tue Jun  9 09:18:20 EDT 2009 [Janelia]
 *
 * Purpose:   Put together scCYK_FILL with scCYK_TraceCT
 */
int
scCYK(GRAMMAR *G, ESL_SQ *sq, SCVAL *ret_sc, BPT **ret_gct, BPT **ret_fct, int priorify, double wgt, int fitlen, int fitparam, int fitbc, char *errbuf, int be_verbose)
{
  GMX     *cyk   = NULL; /* CYK DP matrix: M x (L x L triangular)     */
  BPT     *gct   = NULL; /* given base pairing structure 1..n */
  BPT     *fct   = NULL; /* found base pairing structure 1..n */
  int      status;

 /* no structure to score */
  if (sq->ss == NULL) ESL_XFAIL(eslFAIL, errbuf, "No structure to score!");
  
  /* Make sure the grammar can acommodate the sequences
   * Modify the length distributions if necessary.
   * Also modify transition parameters/ldist targetL if asked to
   */
  if ((status = GMX_GrammarCompatible(G, sq, priorify, wgt, fitlen, fitparam, fitbc, errbuf, be_verbose)) != eslOK) goto ERROR;

  /* Make sure the grammar can acommodate the given structure.
   * Modify the length distributions if necessary.
   */
  if ((status = scCYK_GrammarCompatible(G, sq, &gct, errbuf))             != eslOK) goto ERROR;
  /* Fill the cyk matrix */
  if ((status = scCYK_Fill(G, sq, &cyk, ret_sc, gct, errbuf, be_verbose)) != eslOK) goto ERROR;
  /* Report a traceback */
  if ((status = scCYK_TraceCT(cyk, G, sq, gct, &fct, errbuf, be_verbose)) != eslOK) goto ERROR;

  if (be_verbose) {
    char *fss = NULL;
    ESL_ALLOC(fss, sizeof(char) * (sq->salloc));
    esl_ct2wuss(fct->ct[0], sq->n, fss);
    printf("sccyk structure:\n%s\n", fss);
    free(fss);
  }

  if      (ret_gct != NULL) *ret_gct = gct;
  else if (gct     != NULL)  bpt_Destroy(gct);
  if      (ret_fct != NULL) *ret_fct = fct;
  else if (fct     != NULL)  free(fct);
  
 if (cyk != NULL) GMX_Destroy(cyk);  
  return eslOK;

 ERROR:
  if (gct != NULL) bpt_Destroy(gct);
  if (fct != NULL) bpt_Destroy(fct);
  if (cyk != NULL) GMX_Destroy(cyk);  
  return status;
}

/* Function:  scCYK_Fill()
 * Incept:    ER,  Mon Sep 22 11:41:44 EDT 2008 [Janelia]
 *
 * Purpose:   Given a generalized SCFG <G>, and a digitized sequence <dsq>
 *            w/ residues 1..<L>, and a structure run the generalized CYK recursion
 *            to fill a matrix. Return the score of the sequence and structure. 
 *            If <ret_cyk> is non-NULL, use it to return the CYK matrix.
 *            Caller can then retrieve a parsetree (using CYK_TraceParsetree())
 *            or simply a CT base-pair array (using CYK_TraceCT());
 *            caller must free cyk using CYK_Destroy(cyk) when
 *            done collecting its tracebacks.
 */
int
scCYK_Fill(GRAMMAR *G, ESL_SQ *sq, GMX **ret_cyk, SCVAL *ret_sc, BPT *gct, char *errbuf, int verbose)
{
  GMX     *cyk   = NULL; /* CYK DP matrix: M x (L x L triangular)     */
  int      L;		 /* sequence length                           */
  int      j,d;		 /* j,d coords of the CYK matrix              */
  int      c[4];	 /* iklj coord quad constructed for recursion */
  int      w;	  	 /* counter over nonterminals                 */
  SCVAL    sc;	         /* tmp variable, possible path score to maxr */
  int      status;

  L = sq->n;

 if ((cyk = GMX_Create(G->M, G->K, G->S, L)) == NULL) 
    ESL_XFAIL(eslFAIL, errbuf, "matrix creation failed");

  if (verbose) {
    char *gss = NULL;
    ESL_ALLOC(gss, sizeof(char) * (sq->salloc));
    esl_ct2wuss(gct->ct[0], sq->n, gss);
    printf("given structure:\n%s\n", gss);
    free(gss);
  }

  for (j = 0; j <= L; j++)
    for (d = 0; d <= j; d++)
      {
	c[COORD_J] = j;
	c[COORD_I] = j-d+1;

	/* The start terminal has to be filled last */
	for (w = G->M-1; w >= 0; w--) {
	  if ((status = dp_recursion(&(cyk->dp[w][j][d]), cyk, G, sq->dsq, gct, L, c, j, d, w, NULL, errbuf)) != eslOK) goto ERROR;
	  if (0) printf("\nscCYK %f w=%d[%s] i=%d j=%d d=%d\n", cyk->dp[w][j][d], w, G->nt[w].ntname, j-d+1, j, d);
	}	   
      } 
  
  sc = cyk->dp[G->ntS_idx][L][L];
  if (sc <= -eslINFINITY) ESL_XFAIL(eslFAIL, errbuf, "Structure %s\nfor sequence %s cannot be parsed by the grammar", sq->ss+1, sq->name);
 
  
  if (ret_cyk != NULL) *ret_cyk = cyk;
  else                 GMX_Destroy(cyk);
  *ret_sc = sc;

  return eslOK;

 ERROR:
  return status;
}

/* Function:  CYK_GrammarCompatible()
 * Incept:    ER, Wed Sep  3 10:00:01 EDT 2008 [Janelia]
 *
 * Purpose:   Given a grammar <G>,  modify <G> if necessary to
 *            fit a given sequence to fold.
 *
 * Returns:   <eslOK> on success; This function will modify the
 *            grammar <G> length distributions to fit the sequence to fold.
 *            
 */
int
scCYK_GrammarCompatible(GRAMMAR *G, ESL_SQ *sq, BPT **ret_bpt, char *errbuf)
{
  BPT  *bpt  = NULL;    /* base pairing structure 1..n */
  int   L = sq->n;
  int   ns_min = 0;
  int   x;
  int   status;
  
  if (sq->ss != NULL && L != strlen(sq->ss+1)) 
    ESL_XFAIL(eslFAIL, errbuf, "scCYK_GrammarCompatible(): len = %d Bad structure? ss_len = %lu\n", L, strlen(sq->ss+1)); 

  /* convert to ct, and check it is a consistent ss */
  bpt = bpt_Create(G->nbptype, L+2);
  
  /* remove pseudoknots from annotation */
  if (sq->ss != NULL) {
    if ((status = esl_wuss_nopseudo(sq->ss+1, sq->ss+1)) != eslOK) 
      ESL_XFAIL(eslFAIL, errbuf, "scCYK_GrammarCompatible(): esl_wuss_nopseudo() failed.\n");
    
    if ((status = esl_wuss2ct(sq->ss+1, L, bpt->ct[0])) != eslOK)   /* ct  = ss in ct format, no pks */
      ESL_XFAIL(eslFAIL, errbuf, "scCYK_GrammarCompatible(): Error converting ss to ct format. Bad structure?\n");
  }
  if (sq->nxr > 0) {
    for (x = 0; x < sq->nxr; x ++) {
      if (sq->xr[x] != NULL) {
	if ((status = esl_wuss_nopseudo(sq->xr[x], sq->xr[x])) != eslOK) 
	  ESL_XFAIL(eslFAIL, errbuf, "scCYK_GrammarCompatible(): esl_wuss_nopseudo() failed.\n");   
	if ((status = esl_wuss2ct(sq->xr[x], L, bpt->ct[x])) != eslOK)   /* ct  = ss in ct format, no pks */
	  ESL_XFAIL(eslFAIL, errbuf, "scCYK_GrammarCompatible(): Error converting ss to ct format. Bad structure?\n"); 
      }
    }
  }
  
  /* grammar does not impose any restriction 
   * for hairpinloops or stems
   */
  if (G->force_min_loop == 0 && G->force_min_stem == 1) { 
    if (bpt != NULL) { *ret_bpt = bpt; return eslOK;   }
    else           
      ESL_XFAIL(eslFAIL, errbuf, "scCYK_GrammarCompatible(): NULL ct\n"); 
  }
  
  /* Open hairpinloops to at least force_min_loop nts */
  if (ssCYK_CTOpenHairpinloop(G->force_min_loop, bpt->ct[0], L) != eslOK) 
    ESL_XFAIL(eslFAIL, errbuf, "scCYK_GrammarCompatible(): in ssCYK_CTOpenHairpinloop()\n"); 
  
  /* remove stems with fewer than force_min_stem basepairs */
  if ((status = ssCYK_CTRemoveShortstem(G->force_min_stem, G->force_min_loop, ns_min, bpt->ct[0], L, errbuf)) != eslOK)
    goto ERROR;
  
  /* modified ct 2 wuss */
  if (esl_ct2wuss(bpt->ct[0], L, sq->ss+1)  != eslOK) 
    ESL_XFAIL(eslFAIL, errbuf, "scCYK_GrammarCompatible(): Error in esl_ct2wuss\n"); 
  if (esl_wuss_full(sq->ss+1, sq->ss+1) != eslOK)
    ESL_XFAIL(eslFAIL, errbuf, "scCYK_GrammarCompatible(): Error converting ct to wuss format. Bad structure?\n"); 
  
  if (sq->nxr > 0) {
    for (x = 0; x < sq->nxr; x ++) {
      if (esl_ct2wuss(bpt->ct[x+1], L, sq->xr[x]+1)  != eslOK) 
	ESL_XFAIL(eslFAIL, errbuf, "scCYK_GrammarCompatible(): Error in esl_ct2wuss\n"); 
      if (esl_wuss_full(sq->xr[x]+1, sq->xr[x]+1) != eslOK)
	ESL_XFAIL(eslFAIL, errbuf, "scCYK_GrammarCompatible(): Error converting ct to wuss format. Bad structure?\n");  
    }
  }

  if (bpt != NULL) *ret_bpt = bpt;
  else              bpt_Destroy(bpt);
  return eslOK;
  
 ERROR:
  if (bpt != NULL) bpt_Destroy(bpt);
  return status;
}


/* Function:  scCYK_RuleScore()
 * Incept:    ER,  Fri Feb  6 14:18:36 EST 2009 [Janelia]
 *
 * Purpose:   Calculates the inside score up to a rule.
 *            It can be used as part of the inside recursion.
 *            If used independently, it needs to have the inside
 *            matrix filled up to i,j.
 */
extern int
scCYK_RuleScore(SCVAL *ret_rsc, GMX *cyk, RULE *rp, DRULE *dr, GRAMMAR *G, ESL_DSQ *dsq, BPT *bpt, int L, int *c, int mid, 
		ESL_STACK *alts, char *errbuf, int verbose)
{
  ATOM     *A;                   	/* convenience ptr to an atom */
  SCVAL     rsc = 0;                    /* score of a rule */
  int       i,j,k,l;                    /* coordenate indices */
  int       d,d1,d2;
  int       mid_min, mid_max;
  int       e;		        	/* counter over atoms for a rule */
  int       add_atom;                   /* TRUE if we need to add the atom contribution */
  int       need_aux = FALSE;           /* TRUE if we need to calculate the auxiliar matrices */
  int       status;
  
  if ( rp->d2_iterator_state == ITERATOR_TIED                  ||
      (rp->d2_iterator_state == ITERATOR_JOINT && alts == NULL)   )
      need_aux = TRUE;

  /* the coordenates */
  i = c[COORD_I];
  j = c[COORD_J];
  k = c[COORD_K];
  l = c[COORD_L];

  /* these are the definition of d, d1, d2 */
  d  = j - i + 1;
  d1 = k - i + 1;
  d2 = j - l + 1;

  /* disegments use the mid variable */
  mid_min = mid_max = 0;
  if (need_aux == TRUE) 
    {
      mid_max = d-dr->mindlr-dr->ds_off[COORD_I]+dr->ds_off[COORD_J];
      mid_min = ESL_MAX(0, dr->mindin); 
    }
  if (mid < mid_min || mid > mid_max)
    ESL_XFAIL(eslFAIL, errbuf, "scCYK_RuleScore failed at rule %s mid %d [mid_min=%d,mid_max=%d]", rp->rule_syntax, mid, mid_min, mid_max);
  
  /* fill the auxiliary value dp->aux[rp->jdr_idx][mid]  */
  if (need_aux == TRUE)
    {
      if (rp->d2_iterator_state == ITERATOR_JOINT)
	if ((status = dp_aux_recursion_oneatthetime(cyk, G, dsq, bpt, L, c, j, d, mid, mid_max, rp->jdr_idx, errbuf)) != eslOK) goto ERROR;
      
      /* also fill the auxiliar value stem with the emissions contribution */
      if (rp->d2_iterator_state == ITERATOR_TIED) 
	if ((status = dp_aux_stemr_recursion(cyk->stem, G, rp, dr, bpt, dsq, L, d, mid, mid_max, c, errbuf, verbose)) != eslOK) goto ERROR;
    }

  /* This is the heart of it; 
   * all our coords i,k,l,j; d,d1,d2 are set up (we think).
   * add up all the contributions of each atom to the score.
   */
  for (e = 0; e < rp->natoms; e++)
    {
      A = &(rp->atom[e]);
      
      add_atom = TRUE; /* consider all atoms by default */
      
      /* if a joint disegment, add only the atoms outside the disegment */
      if (need_aux == TRUE && rp->is_jdr == TRUE && dr->inatom[e] == TRUE) add_atom = FALSE;
      
      if (add_atom == TRUE) {

	switch (A->atomtype) {
	case EPSILON_ATOM:
	  break;		/* only costs the transition cost. */
	case NONTERMINAL_ATOM:
	  if ((status = dp_recursion_atom_nonterminal(&rsc, cyk->dp, G, A, d, L, c, rp->rule_mind, errbuf, verbose)) != eslOK) goto ERROR;
	  break;
	case EMISSION_ATOM: 
	  if ((status = dp_recursion_atom_emission(&rsc, G, A, bpt, dsq, L, c, errbuf, verbose))                      != eslOK) goto ERROR;
	  break;
	case MONOSEGMENT_ATOM:
	  if ((status = dp_recursion_atom_monosegment(&rsc, G, A, bpt, dsq, L, c, errbuf, verbose))                   != eslOK) goto ERROR;
	  break;
	  
	case DISEGMENT_ATOM:
	  switch(rp->d2_iterator_state) {
	  case ITERATOR_OFF:
	    ESL_XFAIL(eslFAIL, errbuf, "scCYK dp_recursion(): bad d2 iterator state for disegment atom %s", A->atom_syntax);
	    break;
	  case ITERATOR_ON:
	    if ((status = dp_recursion_atom_disegment_full(&rsc, G, rp, A, bpt, dsq, L, c, errbuf, verbose))                              != eslOK) goto ERROR;
	    break;
	  case ITERATOR_TIED:
	    if ((status = dp_recursion_atom_disegment_tied(&rsc, cyk->stem, G, rp, dr, A, L, d, mid, errbuf, verbose))                    != eslOK) goto ERROR;
	    break;
	  case ITERATOR_JOINT:
	    if ((status = dp_recursion_atom_disegment_joint(&rsc, cyk->aux, G, rp, dr, A, bpt, dsq, L, d, mid, c, alts, errbuf, verbose)) != eslOK) goto ERROR;
	    break;
	  default:
	    ESL_XFAIL(eslFAIL, errbuf, "scCYK dp_recursion(): bad iterator type for rule %s atom %s", rp->rule_syntax, A->atom_syntax);
	  }
	  break;
	  
	default:
	  ESL_XFAIL(eslFAIL, errbuf, "scCYK dp_recursion(): bad atom type. rule %s atom %s", rp->rule_syntax, A->atom_syntax);
	}/* end of switch over atom types */

	if (verbose) 
	  printf("Rsc:i=%d j=%d d1=%d d2=%d mid %d NT %s rule %s atom %s score %f \n", 
		 j-d+1, j, d1, d2, mid, G->nt[rp->nt_idx].ntname, rp->rule_syntax, A->atom_syntax, rsc);
	
	/* if sc is ever -eslINFINITY, then don't need to look further; it's -eslINFINITY. */
	if (rsc == -eslINFINITY) break;
      }
      
    }/* this ends loop over atoms <e>; we've now constructed score <sc> for this rule <r> */

  *ret_rsc = rsc;

  return eslOK;

 ERROR:
  return status;
}

/* Function:  CYK_TraceCT()
 * Incept:    SRE, Wed Mar 23 10:10:30 2005 [St. Louis]
 * Modified:  ER,  Jan 25 11:05:24 EST 2008 [Janelia]
 *
 * Purpose:   Given a filled CYK matrix, stochastically sample one
 *            possible parse tree from it; return a CT base pair array
 *            (1..L) that annotates the predicted base pairs in <dsq>.
 *            Caller must free the ct array using free(ct).
 *
 * Returns:   <eslOK> on success; 
 */
int
scCYK_TraceCT(GMX *cyk, GRAMMAR *G, ESL_SQ *sq, BPT *gct, BPT **ret_fct, char *errbuf, int verbose)
{
  ESL_DSQ        *dsq =  sq->dsq;
  ESL_RANDOMNESS *rng;	        /* random numbers for stochastic traceback */
  ESL_STACK      *ns;           /* integer pushdown stack for traceback */
  ESL_STACK      *alts;	        /* stack of alternate equal-scoring tracebacks */
  RULE           *rp;		/* convenience ptr to a rule */
  ATOM           *atom;	        /* convenience ptr to an atom */
  int             L;            /* sequence length */
  BPT           *fct = NULL;	/* CT structure defining basepairs */
  int            c[4];		/* iklj coord quadruplet for a recursion */
  int            w;		/* counter over nonterminals */
  int            e;		/* counter over atoms */
  int            r;		/* index of a rule */
  int            d1,d2;		/* optimum values of d1, d2 iterators */
  int            i,j,d;		/* seq coords */
  SCVAL          bestsc;	/* max score over possible rules for nonterminal w  */
  int            nequiv;	/* number of equivalent alternatives for a traceback */
  int            x;		/* a random choice from nequiv */
  float          tol = 0.001;
  int            status;

  L = cyk->L;

  /* We're going to do a simple traceback that only
   * remembers who was a base pair, and keeps a ct[]
   * array. 
   */
  fct = bpt_Create(G->nbptype, L+2);

  if (cyk->dp[G->ntS_idx][L][L] == -eslINFINITY) {
    if (ret_fct != NULL) *ret_fct = fct;
    if (verbose) printf("no traceback.\n");
    return eslOK;
  }

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
   * push w,i,j = G->ntS_idx,1,L to init. 
   */
  ns = esl_stack_ICreate();
  esl_stack_IPush(ns, G->ntS_idx);
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
      
      if ((status = dp_recursion(&bestsc, cyk, G, dsq, gct, L, c, j, d, w, alts, errbuf)) != eslOK) goto ERROR;
      
       /* Some assertions.
       */
      if (d < G->nt[w].nt_mind)       
	ESL_XFAIL(eslFAIL, errbuf, "scCYK_TraceCT(): can't happen");  
      if (fabs(bestsc - cyk->dp[w][j][d]) > tol) 
	ESL_XFAIL(eslFAIL, errbuf, "scCYK_TraceCT(): that can't happen either. w=%d i=%d j=%d d=%d bestsc %f cyk %f", w, j-d+1, j, d, bestsc, cyk->dp[w][j][d]);
      
      /* Now we know one or more equiv solutions, and they're in
       * the stack <alts>, which keeps 3 numbers (r, d1, d2) for each
       * solution. Choose one of them at random.
       */
      nequiv = esl_stack_ObjectCount(alts) / 3; /* how many solutions? */
      x = esl_rnd_Roll(rng, nequiv);            /* uniformly, 0.nequiv-1 */
      esl_stack_DiscardTopN(alts, x*3);         /* dig down to choice */
      esl_stack_IPop(alts, &d2);                /* pop it off, in rev order */
      esl_stack_IPop(alts, &d1);
      esl_stack_IPop(alts, &r);

      /* Now we know a best rule; figure out where we came from,
       * and push that info onto the <ns> stack. We have to traverse all
       * the atoms in the rule. 
       */
      rp         = &(G->nt[w].pr[r]);
      c[COORD_K] = c[COORD_I] + d1 - 1;
      c[COORD_L] = c[COORD_J] - d2 + 1;

      if (verbose) {
	printf("-----------------------------------\n"); 
	printf("j=%d d=%d d1=%d d2=%d\n", j, d, d1, d2);
	printf("i=%d j=%d k=%d l=%d\n", 
	       c[COORD_I], c[COORD_J], c[COORD_K], c[COORD_L]);
	printf("tracing %s %f\n",G->nt[w].ntname, bestsc);
	printf("   rule(%d) %s\n", r+1, rp->rule_syntax);
      }

      for (e = 0; e < rp->natoms; e++)
	{
	  atom = &(rp->atom[e]);

	  switch (atom->atomtype) {
	  case EPSILON_ATOM:
	    break;

	   /* The main business of the traceback. */ 
	  case NONTERMINAL_ATOM: 
	    if ((status = Stack_NonterminalAtom(atom, ns, c, L, errbuf)) != eslOK)
	      goto ERROR;
	    break;
	    
	    /* The main business of recording secondary structure in ct */
	  case EMISSION_ATOM:
	    if ((status = TraceCT_EmissionAtom(atom, fct, c, L, errbuf)) != eslOK)
	      goto ERROR;
	    break;
	    
	  case MONOSEGMENT_ATOM:
	    /* TODO - don't need to add anything to the ct from here, or do I? */
	    break;
	    
	  case DISEGMENT_ATOM:
	    if ((status = TraceCT_DisegmentAtom(atom, rp, fct->ct[0], c, L, errbuf)) != eslOK)
	      goto ERROR;
	    break;
	    
	  default: 
	    ESL_XFAIL(eslFAIL, errbuf, "scCYK_TraceCT(): no such atom");
	  } /* end switch over atom types */
	} /* end loop over atoms. */
   } /* end of while loop, while there's still traceback going */
  
  if (verbose) {
    char *fss = NULL;
    ESL_ALLOC(fss, sizeof(char) * (sq->salloc));
    esl_ct2wuss(fct->ct[0], sq->n, fss);
    printf("CT structure:\n%s\n", fss);
    free(fss);
  }
  
  esl_stack_Destroy(ns);
  esl_stack_Destroy(alts);
  esl_randomness_Destroy(rng);
  if (ret_fct != NULL) *ret_fct = fct;

  return eslOK;

 ERROR:
  if (fct  != NULL) free(fct);
  if (ns   != NULL) esl_stack_Destroy(ns);
  if (alts != NULL) esl_stack_Destroy(alts);
  if (rng  != NULL) esl_randomness_Destroy(rng);
  return status;
}

/* dp_recursion():
 * The actual business of the generalized CYK parser, for
 * calculating one CYK lattice cell.
 *
 * in filling   mode atls == NULL and uses the order(L^3) algorithm
 * in traceback mode alts != NULL and uses the order(L^4) algorithm
 */
static int
dp_recursion(SCVAL *ret_bestsc, GMX *cyk, GRAMMAR *G, ESL_DSQ *dsq, BPT *bpt, int L, 
	     int c[4], int j, int d, int w, ESL_STACK *alts, char *errbuf)
{
  NT       *nt;		        	/* convenience ptr to a NT */
  RULE     *rp;		        	/* convenience ptr to a rule */
  TDIST    *tdist;              	/* convenience ptr to an tdist */
  DRULE    *dr = NULL;                	/* convenience ptr to the joint-disegment rules */
  SCVAL     sc;	                        /* temp variable, possible path score to max */
  SCVAL     bestsc;	        	/* best score seen so far */
  int       tofw;	        	/* "t of w", index of t dist for nonterm */
  int       r;		        	/* counter over possible rules */
  int       d1, d1_min;	        	/* d1 iterator, for coord k */
  int       d2, d2_min;	        	/* d2 iterator, for coord l */
  int       mid, mid_min, mid_max;      /* for rules containing disegments */
  int       verbose = FALSE;
  int       status;

  nt    = &(G->nt[w]);
  tofw  = nt->tdist_idx;
  tdist = &(G->tdist[tofw]);

  if (alts != NULL) esl_stack_Reuse(alts);
  
  bestsc = -eslINFINITY;
  if (d < nt->nt_mind) { *ret_bestsc = bestsc; return eslOK; }
  
   for (r = 0; r < nt->nrules; r++)
    {
      rp  = &(nt->pr[r]);

      /* There are three "boundary condition" tests here:
       *   1. The rule is incapable of generating a production of length < d.
       *   2. The rule contains only terminals, so it generates a fixed d, and
       *      this d ain't it.
       *   3. The transition probability into this rule is 0. Why is it there,
       *      then? Not for us to wonder why.   
       */
      if (d < rp->rule_mind)                         continue;
      if (rp->is_allterminals && d != rp->rule_mind) continue;
      if (tdist->tsc[r] == -eslINFINITY)             continue; 
      
      /* identify a drule if this is one */
      if (rp->is_jdr   == TRUE) dr = &(G->jdr[rp->jdr_idx]);
      if (rp->is_stemr == TRUE) dr = &(G->stemr[rp->stemr_idx]);
      
      /* Setup of the d1 iterator for this rule r.
       */
      switch (rp->d1_iterator_state) {
      case ITERATOR_ON:  
	if (rp->d2_iterator_state == ITERATOR_JOINT) {
	  if (alts != NULL) { /* mtx traceback: use the full L^4 algorithm */
	    d1     = ESL_MIN(d-rp->d2_iterator_min-dr->mindin-dr->ds_off[COORD_K]+dr->ds_off[COORD_L], rp->d1_iterator_max); 
	    d1_min = ESL_MAX(0, rp->d1_iterator_min); 
	  }
	  else { /* mtx fill: do not set; we use mid instead in a L^3 algorithm */
	    d1     = 0; 
	    d1_min = 0; 
	  }
	}
	else if (rp->d2_iterator_state == ITERATOR_TIED) { 
	  /* we do not iterate over d1/d2 but mid instead */
	  d1     = 0;
	  d1_min = 0;
	}
	else {
	  d1     = ESL_MIN(d, rp->d1_iterator_max);
	  d1_min = ESL_MAX(0, rp->d1_iterator_min);
	}
	break;
      case ITERATOR_OFF:   
	d1     = 0;
	d1_min = 0;
	break;  
      default: ESL_XFAIL(eslFAIL, errbuf, "CYK dp_recursion(): bad d1 iterator state");
      }

      do { /* Iterate over all valid values of d1. */
	c[COORD_K] = c[COORD_I] + d1 - 1;

	/* Setup of the d2 iterator for this rule r.
	 */
	switch (rp->d2_iterator_state) {
	case ITERATOR_ON:   
 	  d2     = ESL_MIN(ESL_MIN(d-d1,rp->d2_iterator_max), rp->d2_iterator_max-d1);
	  d2_min = ESL_MAX(0,    rp->d2_iterator_min);
	  break;
	case ITERATOR_OFF:   
	  d2     = 0;
	  d2_min = 0;
	  break;  
	case ITERATOR_TIED:   
	  /* we do not iterate over d1/d2 but mid instead */
	  d2     = 0;  
	  d2_min = 0;  
	  break;  
	case ITERATOR_JOINT: 
	  if (alts != NULL) { /* mtx traceback: use the full L^4 algorithm */
	    d2     = ESL_MIN(d-d1-dr->mindin-dr->ds_off[COORD_K]+dr->ds_off[COORD_L], rp->d2_iterator_max);
	    d2_min = ESL_MAX(0, rp->d2_iterator_min);
	  }
	  else { /* mtx fill: do not set; we use mid instead in a L^3 algorithm */
	    d2     = 0; 
	    d2_min = 0; 
	  }
	  break;  
	default: ESL_XFAIL(eslFAIL, errbuf, "CYK dp_recursion(): bad d2 iterator state"); break;
	}

	do { /* Iteration over all valid values of d2. */
	  c[COORD_L] = c[COORD_J] - d2 + 1;
	  
	  /* Setup of the mid iterator for this rule r.
	   * mid is defined as the nts inside the disegment.
	   */
	  /* do not iterate over mid by default */
	  mid_max = 0;
	  mid_min = 0;

	  /* mid is used for a joint disegment 
	   * when using the L^3 algorithm (filling) */
	  if (alts == NULL &&
	      rp->d2_iterator_state == ITERATOR_JOINT) 
	    {
	      mid_max = d-dr->mindlr-dr->ds_off[COORD_I]+dr->ds_off[COORD_J];
	      mid_min = ESL_MAX(0, dr->mindin);
	    }
	  
	  /* mid is also used in a tied disegment,
	   * so that the by starting with mid_max the size
	   * of the disegment goes from smaller to larger */
	  if (rp->d2_iterator_state == ITERATOR_TIED) 
	    {
	      mid_max = d-dr->mindlr-dr->ds_off[COORD_I]+dr->ds_off[COORD_J];
	      mid_min = ESL_MAX(0, dr->mindin);
	    }

	  mid = mid_max;


	  do { /* Iteration over all valid values of mid.
		* This is the alternative to a L^4 algorithm when the
		* contibution of the disegment is JOINT (ie depends only
		* on d1+d2). 
		* For a tied disegment we also use mid instead of d1/d2
		*/
	    
	    /* For a tied disegment, set the values of d1 and d2 for this mid.
	     * That way, we can evaluate the atoms in any order we want   
	     */
	    if (rp->d2_iterator_state == ITERATOR_TIED) 
	      {
		d1_min = d1 = (d-mid + dr->ds_off[COORD_I] + dr->ds_off[COORD_J])/2 - dr->ds_off[COORD_K];
		d2_min = d2 = d1 + dr->ds_off[COORD_K] - dr->ds_off[COORD_I] + dr->ds_off[COORD_L] - dr->ds_off[COORD_J];
		
		c[COORD_K] = c[COORD_I] + d1 - 1;
		c[COORD_L] = c[COORD_J] - d2 + 1;
	      }
	    
	    /* This is the heart of it; 
	     * all our coords i,k,l,j; d,d1,d2 are set up (we think).
	     * add up all the contributions of each atom to the score.
	     */

	    /* start with the rule score */
	    if (0&&(j==75&&j-d+1==7&&w==15&&(r==6||r==5||r==12))) verbose = TRUE; else verbose = FALSE;
	    if ((status = scCYK_RuleScore(&sc, cyk, rp, dr, G, dsq, bpt, L, c, mid, alts, errbuf, verbose)) != eslOK) goto ERROR;
	    
 	    if (sc > -eslINFINITY && tdist->tsc[r] > -eslINFINITY)
	    sc += tdist->tsc[r]; /* add the transition score */

	    if (0&&((j==75&&j-d+1==7&&w==15)||(j==74&&j-d+1==9&&w==15))&&sc > -10) 
	      printf("  --rule %s i=%d j=%d d1=%d d2=%d sc %f bestsc %f\n\n", rp->rule_syntax, j-d+1, j, d1, d2, sc, bestsc);

	    if (sc >= bestsc && !(d == 0 && !rp->is_allterminals && rp->natoms > 1)) {
	      /* That last test above is a special cheat. For d=0,
	       * *only* allow an epsilon rule. Not needed for
	       * unambiguous grammars, but for ambiguous grammars
	       * that have a rule pair like S-> SS | \epsilon,
	       * there's a nasty exploding (Yule?) process that may
	       * take a long time to terminate.
	       *
	       * ER:
	       * watch out for the case P->S  S->e
	       * in this case d=0 should be allowed to rule P->S,
	       * thus the extra condition rp->natoms > 1
	       *
	       * There is another runaway process that we have 
	       * take care of already:
	       * S1(d) --> S1(d)S2(0) --> S1(d)S2(0) e --> S1(d)S2(0) e e ...
 	       *
	       */
	      if (sc > bestsc) { /* if an outright winner, clear/reinit the stack */
		if (alts != NULL) esl_stack_Reuse(alts);
		bestsc   = sc;
	      }
	      if (alts != NULL) {
		esl_stack_IPush(alts, r);       /* note order of the pushes: r,d1,d2; */
		esl_stack_IPush(alts, d1);  /* thus the caller pops d2,d1,r.  */
		esl_stack_IPush(alts, d2);
	      }
	    }
	    
	  } while (--mid >= mid_min); /* end of the mid iterator's do loop */
	} while (--d2 >= d2_min); /* end of the d2 iterator's do loop */
      } while (--d1 >= d1_min);   /* end of the d1 iterator's do loop */
      
    } /* end loop over r; all possible rules for this nonterm w */

   *ret_bestsc = bestsc;
   if (0&&w==1&&j==30&&j-d+1==12) printf("  --bestsc[w=%d][i=%d,j=%d] %f\n", w, j-d+1, j, bestsc);

   return eslOK;

 ERROR:
  return status;
}

/* dp_aux_recursion_aux():
 * first, fill auxiliary matrices for joint disegments
 */
static int
dp_aux_recursion_oneatthetime(GMX *cyk, GRAMMAR *G, ESL_DSQ *dsq, BPT *bpt, int L, 
			      int c[4], int j, int d, int dmid, int dmid_max, int v, char *errbuf)
{
  NT       *nt;		        	/* convenience ptr to a NT */
  RULE     *rp;		        	/* convenience ptr to a rule */
  ATOM     *dsa;		        /* convenience ptr to the disegment atom */
  DRULE    *jdr;                	/* convenience ptr to the joint-disegment rule */
  LDIST    *ldist;                      /* convenience ptr to an ldist */
  SCVAL     bestsc;	        	/* best score seen so far */
  int       d1;	                	/* d1 iterator, for coord k */
  int       d2;                         /* d2 iterator, for coord l */
  int       r_idx;	                /* this rule index */
  int       a;
  int       status;

  jdr   = &(G->jdr[v]);
  nt    = &(G->nt[jdr->nt_idx]);
  r_idx = jdr->rule_idx;
  rp    = &(nt->pr[r_idx]);
  dsa   = &(rp->atom[jdr->dsa_idx]);
  
  if (dsa->nldists != 1 || dsa->ncoords != 4)	    
    ESL_XFAIL(eslFAIL, errbuf, "aux_recursion failed at rule %s dsa %s (nldists=%d ncoords=%d)", 
	      rp->rule_syntax, dsa->atom_syntax, dsa->nldists, dsa->ncoords);

  ldist = &(G->ldist[dsa->ldist_idx[0]]);

 /* initialize */
  if (dmid == d) cyk->aux[v][d] = -eslINFINITY;
  if (d < rp->rule_mind) return eslOK;
  
 /* initialize */
  if (dmid == dmid_max) cyk->aux[v][dmid]= -eslINFINITY;

  /* expand rule from (i+1,j) to (i,j)  emit i */
  a = c[COORD_I] + jdr->ds_off[COORD_I];
  if (a < 1 || a > L) 
    ESL_XFAIL(eslFAIL, errbuf, "aux_recursion failed at rule %s dsa %s [a=%d]", rp->rule_syntax, dsa->atom_syntax, a);
  
  if (bpt->ct[0][a] == 0) { /* residue is unpaired */
    if (dsq[a] < 4) bestsc = cyk->aux[v][dmid] + ldist->esc[dsq[a]];
    else            bestsc = cyk->aux[v][dmid] + log(0.25); /* ambiguity in residue */
  }
  else /* residue is paired. cannot be part of an intloop */             
    bestsc = -eslINFINITY; 
  
  /* New possible case for all dmin: push the inside of the disegment to the left. */
  d1 = ESL_MIN(jdr->mindl+jdr->ds_off[COORD_I]-jdr->ds_off[COORD_K], rp->d1_iterator_max);
  d2 = ESL_MIN(d-d1-dmid-jdr->ds_off[COORD_K]+jdr->ds_off[COORD_L],  rp->d2_iterator_max);
  if ((status = dp_aux_recursion_dmid(&bestsc, cyk, G, bpt, dsq, L, c, rp, jdr, ldist, d, dmid, d1, d2, errbuf)) != eslOK) goto ERROR;
  
  /* New possible cases for dmin_max: push the inside of the disegment to the right. */
  if (dmid == dmid_max) {
    d1 = ESL_MIN(jdr->mindl-jdr->ds_off[COORD_K]+1,           rp->d1_iterator_max);
    d2 = ESL_MIN(d-d1-dmid-jdr->ds_off[COORD_K]+jdr->ds_off[COORD_L], rp->d2_iterator_max);
    while (d2 >= ESL_MIN(jdr->mindr+jdr->ds_off[COORD_L]-jdr->ds_off[COORD_J], rp->d2_iterator_max)) 
      {
	if ((status = dp_aux_recursion_dmid(&bestsc, cyk, G, bpt, dsq, L, c, rp, jdr, ldist, d, dmid, d1, d2, errbuf)) != eslOK) goto ERROR;
	d1 ++;
	d2 = d - d1 - dmid - jdr->ds_off[COORD_K] + jdr->ds_off[COORD_L];  
      }
  }
 
  cyk->aux[v][dmid] = bestsc;

  return eslOK;

 ERROR:
  return status;
}

static int
dp_aux_recursion_dmid(SCVAL *ret_bestsc, GMX *cyk, GRAMMAR *G, BPT *bpt, ESL_DSQ *dsq, int L, 
		      int c[4], RULE *rp, DRULE *jdr, LDIST *ldist, int d, int dmid, int d1, int d2, char *errbuf)
{
  ATOM     *A;                  	/* convenience ptr to an atom */
  int       cc[4];
  SCVAL     sc;	                        /* temp variable, possible path score to max */
  SCVAL     bestsc;	        	/* best score seen so far */
  int       e;		        	/* counter over atoms for the rule */
  int       a, b;
  int       x;
  int       status;
  int       verbose = FALSE;

  if (d1 < 0)     
    ESL_XFAIL(eslFAIL, errbuf, "aux_recursion_mid failed at rule %s. Negative d1 iterator %d", 
	      rp->rule_syntax, d1);
  if (d2 < 0) 
    ESL_XFAIL(eslFAIL, errbuf, "aux_recursion_mid failed at rule %s. Negative d2 iterator %d", 
	      rp->rule_syntax, d2);
  
  cc[COORD_I] = c[COORD_I];
  cc[COORD_J] = c[COORD_J];

  cc[COORD_K] = cc[COORD_I] + d1 - 1;
  cc[COORD_L] = cc[COORD_J] - d2 + 1;
  
  
  bestsc = *ret_bestsc;
   
  sc = 0.0; /* no transition score here */

  /* add residues from i+ds_off[COORD_I] to k+ds_off[COORD_K] */
  a = cc[COORD_I] + jdr->ds_off[COORD_I];
  b = cc[COORD_K] + jdr->ds_off[COORD_K];
  if (a < 1 || a > L+1 || b < 0 || b > L)  /* boundaries */
    ESL_XFAIL(eslFAIL, errbuf, "aux_recursion failed at rule %s. Negative ", rp->rule_syntax);

  for (x = 0; x < b-a+1; x ++) {
    if (bpt->ct[0][a+x] == 0) { /* residue is unpaired */
      if (dsq[a+x] < 4) 
	{
	  if (ldist->esc[dsq[a+x]] <= -eslINFINITY) sc  = -eslINFINITY; 
	  else                                      sc += ldist->esc[dsq[a+x]];	  
	}
      else 
	{
	  sc += log(0.25);	 
	}
    }
    else { /* residue is paired to something */
      sc = -eslINFINITY;
    } 
  }
  
  /* add residues from l+ds_off[COORD_L] to j+ds_off[COORD_J] */
  a = cc[COORD_L] + jdr->ds_off[COORD_L];
  b = cc[COORD_J] + jdr->ds_off[COORD_J];
  if (a < 1 || a > L+1 || b < 0 || b > L)  /* boundaries */
    ESL_XFAIL(eslFAIL, errbuf, "aux_recursion_mid failed at rule %s. Negative ", rp->rule_syntax);

  for (x = 0; x < b-a+1; x ++) {
    if (bpt->ct[0][a+x] == 0) { /* residue is unpaired */
      if (dsq[a+x] < 4) 
	{
	  if (ldist->esc[dsq[a+x]] <= -eslINFINITY) sc  = -eslINFINITY; 
	  else                                      sc += ldist->esc[dsq[a+x]];	  
	}
      else 
	{
	  sc += log(0.25);	 
	}
    }
    else { /* residue is paired to something */
      sc = -eslINFINITY;
    } 
  }
     
  /* Here we only add atoms interior to the disegment atom.
   */
  for (e = 0; e < rp->natoms; e++)
    {
      if (jdr->inatom[e] == TRUE) {
	
	A = &(rp->atom[e]);
	
	switch(A->atomtype) {
	case EPSILON_ATOM:
	  break;	
	case NONTERMINAL_ATOM:
	  if ((status = dp_recursion_atom_nonterminal(&sc, cyk->dp, G, A, d, L, cc, rp->rule_mind, errbuf, FALSE)) != eslOK) goto ERROR;
	  break;
	case EMISSION_ATOM:
	  if ((status = dp_recursion_atom_emission(&sc, G, A, bpt, dsq, L, cc, errbuf, verbose))                    != eslOK) goto ERROR;
	  break;
	case MONOSEGMENT_ATOM:
	  if ((status = dp_recursion_atom_monosegment(&sc, G, A, bpt, dsq, L, cc, errbuf, verbose))                 != eslOK) goto ERROR;
	  break;
	default:
	  ESL_XFAIL(eslFAIL, errbuf, "aux_recursion_mid failed at  rule %s, atom %s. Not such atomtype", 
		    rp->rule_syntax, A->atom_syntax);
	  break;	  
	}/* end of switch over atom types */
      }
    }
  
  if (sc > bestsc) { /* if an outright winner, clear/reinit the stack */
    bestsc = sc;
  }

  *ret_bestsc = bestsc;

  return eslOK;
  
 ERROR:
  return status;
}

int
dp_aux_stemr_recursion(SCVAL *cykstem, GRAMMAR *G, RULE *rp, DRULE *stemr, BPT *bpt, ESL_DSQ *dsq, 
		       int L, int d, int mid, int mid_max, int c[4], char *errbuf, int verbose)
{
  ATOM   *dsa;        /* Convenience ptr to the disegment atom */
  SCVAL   esc;        /* emission score */
  int     cc[4];
  int     len;        /* length of segments */
  int     dd1, dd2;   /* indices for covering the two arms of the disegment */
  int     i,j,k,l;    /* indices used for score lookups */
  int     n;	      /* counter over emitted residues */
  int     s;	      /* index of disegment rule */
  int     ll;
  int     status;

  s = rp->stemr_idx;

  cc[COORD_I] = c[COORD_I]; 
  cc[COORD_J] = c[COORD_J]; 

  /* The disegment atom */
  dsa = &(rp->atom[stemr->dsa_idx]);
  
  /* length of stem */
  len = d - mid - stemr->ds_off[COORD_I] + stemr->ds_off[COORD_J];
  if (len < 0) ESL_XFAIL(eslFAIL, errbuf, "length of tied disegment is negative? %d\n", len);
  if (len%2 != 0) return eslOK;  /* do nothing, no contribution in this case */
  len /= 2;
  if (verbose) printf("\n stemr %s d %d mid %d mid_max %d len %d cykstem %f\n", dsa->atom_syntax, d, mid, mid_max, len, cykstem[s]);
  
  /* Calculate the emissions contribution */
  if (mid == mid_max) {

    /* This is the minimum disegment,
     * have to add all the emission contributions */
    cykstem[s] = 0;
    
    ll = 1;
    while (ll <= len) {
      dd1 = ll - stemr->ds_off[COORD_K] + stemr->ds_off[COORD_I];
      dd2 = ll + stemr->ds_off[COORD_L] - stemr->ds_off[COORD_J];

      cc[COORD_K] = cc[COORD_I] + dd1 - 1;
      cc[COORD_L] = cc[COORD_J] - dd2 + 1;
      
      for (n = 0; n < dsa->ncoords; n ++) {
	switch(dsa->coordbase[n]) {
	case COORD_I: 
	  i = cc[dsa->coordbase[n]] + dsa->offset[n];
	  break;
	case COORD_J:
	  j = cc[dsa->coordbase[n]] + dsa->offset[n];
	  break;
	case COORD_K:
	  k = cc[dsa->coordbase[n]] + dsa->offset[n];
	  break;
	case COORD_L:
	  l = cc[dsa->coordbase[n]] + dsa->offset[n];
	  break;
	default:     
	  ESL_XFAIL(eslFAIL, errbuf, "coord not found. rule %s, atom %s", rp->rule_syntax, dsa->atom_syntax);
	  break;
	}
      }
      if (verbose) printf("i %d j %d k %d l %d ctk %d ctl %d\n", i, j, k, l, bpt->ct[0][k], bpt->ct[0][l]);

      if (bpt->ct[0][k] != l || bpt->ct[0][l] != k) 
	{     
	  cykstem[s] = -eslINFINITY; 
	  break;
	}
      else 
	{
	  if ((status = TiedDiseg_ScoreInnerMostPair(&esc, dsq, L, cc, G, dsa, stemr, errbuf)) != eslOK) goto ERROR;
	  if (esc > -eslINFINITY) cykstem[s] += esc;
	  else                    cykstem[s]  = -eslINFINITY;
  	}

      if (verbose) printf("cykstem ll %d ci %d cj %d ck %d cl %d cykstem %f \n", 
			  ll, cc[COORD_I], cc[COORD_J], cc[COORD_K], cc[COORD_L], cykstem[s]);
     
      ll ++; 
     }
  }
  else {
    /* Just need to update adding the new basepair */
    dd1 = len - stemr->ds_off[COORD_K] + stemr->ds_off[COORD_I];
    dd2 = len + stemr->ds_off[COORD_L] - stemr->ds_off[COORD_J];

    cc[COORD_K] = cc[COORD_I] + dd1 - 1;
    cc[COORD_L] = cc[COORD_J] - dd2 + 1;
    
    for (n = 0; n < dsa->ncoords; n ++) {
      switch(dsa->coordbase[n]) {
      case COORD_I: 
	i = cc[dsa->coordbase[n]] + dsa->offset[n];
	break;
      case COORD_J:
	j = cc[dsa->coordbase[n]] + dsa->offset[n];
	break;
      case COORD_K:
	k = cc[dsa->coordbase[n]] + dsa->offset[n];
	break;
      case COORD_L:
	l = cc[dsa->coordbase[n]] + dsa->offset[n];
	break;
      default:     
	ESL_XFAIL(eslFAIL, errbuf, "coord not found. rule %s, atom %s", rp->rule_syntax, dsa->atom_syntax);
	break;
      }
    }
    
    if (bpt->ct[0][k] != l || bpt->ct[0][l] != k) cykstem[s] = -eslINFINITY; 
    else {
      if ((status = TiedDiseg_ScoreInnerMostPair(&esc, dsq, L, cc, G, dsa, stemr, errbuf)) != eslOK) goto ERROR;
      if (esc > -eslINFINITY) cykstem[s] += esc;
      else                    cykstem[s]  = -eslINFINITY;
    }	  
    
    if (verbose) printf("cykstem len %d ci %d cj %d ck %d cl %d cykstem %f \n", 
			len, cc[COORD_I], cc[COORD_J], cc[COORD_K], cc[COORD_L], cykstem[s]);
  }

  return eslOK;

 ERROR:
  return eslFAIL;
}

int
dp_recursion_atom_nonterminal(SCVAL *sc, SCVAL ***cyk, GRAMMAR *G, ATOM *A, int d, int L, int c[4], int rule_mind, char *errbuf, int verbose)
{
  int       a,b;		/* indices used for score lookups */
  int       y;			/* index of a nonterminal */
  int       status;

  if (A->ncoords != 2)
   ESL_XFAIL(eslFAIL, errbuf, "wrong number of coords (%d) for atom %s", A->ncoords, A->atom_syntax);
   
  a   = c[A->coordbase[0]] + A->offset[0];
  b   = c[A->coordbase[1]] + A->offset[1];
  y   = A->nterm_idx;
  
  if (verbose) printf("%s a %d b %d L %d b-a+1 %d atom_mind %d cyk %f\n", A->atom_syntax, a, b, L, b-a+1, A->atom_mind, cyk[y][b][b-a+1]);

  if (y<0) ESL_XFAIL(eslFAIL, errbuf, "y? %d\n", y);

  if (a < 0 || a > L+1                     ||
      b < 0 || b > L+1                     ||
      b-a+1 < A->atom_mind                 ||
      b-a+1 > d - (rule_mind-A->atom_mind)   )  /* boundaries */
    { (*sc) = -eslINFINITY; return eslOK; }

  /* check for a rule involving a runaway process:
   * The nonterminal that originated the rule 
   * appears as a nonterminal atom, and
   * with the same (nonzero) distance.
   */
  if (!strcmp(A->atom_syntax, G->nt[A->nt_idx].ntname))
    {
      if (d > 0 && b-a+1 == d) 
	{ (*sc) = -eslINFINITY; return eslOK; }
    }

  if (cyk[y][b][b-a+1] == -eslINFINITY)
    { (*sc) = -eslINFINITY; return eslOK; }

  (*sc) += cyk[y][b][b-a+1]; /* b-a+1 because we're jd indexed */
  
  return eslOK;

 ERROR:
  return eslFAIL;
}

int
dp_recursion_atom_emission(SCVAL *sc, GRAMMAR *G, ATOM *A, BPT *bpt, ESL_DSQ *dsq, int L, int c[4], char *errbuf, int verbose)
{
  EDIST    *edist;       	/* convenience ptr to an edist */
  int       eofw;		/* "e of w", index of e dist for emission atom */
  int       x;			/* lookup index for emitted residues */
  int       z;			/* lookup index for context of emitted residues */
  int       iscompatible;
  int       status;

  /* If the emission atom includes basepairs, check
   * that those satisfy the min_loop requeriments. 
   * This check is necessary only if the min_loop has been forced
   * to something other that what is "natural" for the grammar.
   */
  
  if (GMX_ForceGrammarMinloop(G, A, L, c) != eslOK) 
    {
      (*sc) = -eslINFINITY;
      return eslOK; 
    }

  if ((status = dp_recursion_atom_emission_iscompatible(A, bpt, L, c, &iscompatible, errbuf, verbose)) != eslOK) goto ERROR;

  if (!iscompatible)
    {
      (*sc) = -eslINFINITY;
      return eslOK; 
    }

  eofw = EmissionAtomEdistIndex(dsq, L, c, A, &x, &z);
  if (eofw < 0 || eofw > G->ned) { printf("\neofw %d\n", eofw); return eslFAIL; }
  edist = &(G->edist[eofw]);
  if (verbose) printf("---->sc %f x %d z %d eofw %d %s score %f\n", (*sc), x, z, eofw, edist->ename, edist->esc[x]);

  /* off limits */ 
  if (z == -2 || x == -2)  { (*sc) = -eslINFINITY;  return eslOK; } 

  if (x == -1)	/* ambiguity in one or more residues */
    (*sc) += A->ncoords * log(0.25); /* arbitrary!! */
  else if (edist->esc[x] == -eslINFINITY)
    (*sc) = -eslINFINITY;
  else
    (*sc) += edist->esc[x];
  
  return eslOK;

 ERROR:
  return status;
}

int 
dp_recursion_atom_emission_iscompatible(ATOM *A, BPT *bpt, int L, int c[4], int *ret_iscompatible, char *errbuf, int verbose)
{
  int a, b;	         	/* index used for score lookups */
  int bp;			/* counter over nbasepairs in atom */
  int n;			/* counter over emitted residues */
  int iscompatible = TRUE;
  int x;
  int status;

  for (n = 0; n < A->ncoords; n++)
    { 
      a = c[A->coordbase[n]] + A->offset[n]; 
      if (!EmissionAtomCoordIsPaired(A, n)) {
	for (x = 0; x < bpt->n; x ++) {
	  if (bpt->ct[x][a] != 0) iscompatible = FALSE; break;
	}
      }
    }
  
  for (bp = 0; bp < A->nbasepairs; bp ++) {
    
    a = c[A->coordbase[A->bp[bp].basepair_coordl_idx]] + A->offset[A->bp[bp].basepair_coordl_idx]; 
    b = c[A->coordbase[A->bp[bp].basepair_coordr_idx]] + A->offset[A->bp[bp].basepair_coordr_idx]; 
    
    if (a == L+1 || b == L+1) { *ret_iscompatible = FALSE; return eslOK; }
    
    if (a < 1 || a > L+1) ESL_XFAIL(eslFAIL, errbuf, "i=%d j=%d bad bondaries for atom %s, L=%d", a, b, A->atom_syntax, L);
    if (b < 1 || b > L+1) ESL_XFAIL(eslFAIL, errbuf, "i=%d j=%d bad bondaries for atom %s, L=%d", a, b, A->atom_syntax, L);
    
    for (x = 0; x < bpt->n; x ++) {
      if (bpt->type[x] == A->bp[bp].basepairtype) {
	if (bpt->ct[x][a] != b) iscompatible = FALSE;
	if (bpt->ct[x][b] != a) iscompatible = FALSE;
      }
    }
  }
  
  *ret_iscompatible = iscompatible;
  return eslOK;

 ERROR:
  return status;
}


int
dp_recursion_atom_monosegment(SCVAL *sc, GRAMMAR *G, ATOM *A, BPT *bpt, ESL_DSQ *dsq, int L, int c[4], char *errbuf, int verbose)
{
  LDIST    *ldist;     /* convenience ptr to an ldist */
  int       a,b;       /* indices used for score lookups */
  int       x;	       /* index of a sequence positions */
  int       len;       /* length of segments */
  int       status;
  
  if (A->nldists != 1) ESL_XFAIL(eslFAIL, errbuf, "wrong number of ldist (%d) for atom %s", A->nldists, A->atom_syntax);
  if (A->ncoords != 2) ESL_XFAIL(eslFAIL, errbuf, "wrong number of coords (%d) for atom %s", A->ncoords, A->atom_syntax);
  
  ldist = &(G->ldist[A->ldist_idx[0]]);
  
  a = c[A->coordbase[0]] + A->offset[0];
  b = c[A->coordbase[1]] + A->offset[1];
  
  if (a < 0 || a > L+1 || b < 0 || b > L) ESL_XFAIL(eslFAIL, errbuf, "bad bondaries for atom %s", A->atom_syntax);		  
  len = b - a + 1;
  
  for (x = 0; x < len; x ++) {
    if (bpt->ct[0][a+x] == 0) { /* residue is unpaired */
      if (dsq[a+x] < 4) 
	{
	  if (ldist->esc[dsq[a+x]] <= -eslINFINITY) (*sc)  = -eslINFINITY; 
	  else                                      (*sc) += ldist->esc[dsq[a+x]];	
	}
      else 
	{
	  (*sc) += log(0.25);	 
	}
    }
    else { /* residue is paired to something */
      (*sc) = -eslINFINITY;
    } 
  }

  if (len < ldist->min || len > ESL_MIN(L,ldist->max)) /* boundaries */
    (*sc) = -eslINFINITY;
  else if (ldist->lsc[len-ldist->min] <= -eslINFINITY)
    (*sc) = -eslINFINITY;
  else if ((*sc) > -eslINFINITY)
    (*sc) += ldist->lsc[len-ldist->min];

  if (verbose) 
    printf("MONO %s a=%d b=%d len=%d lmin=%d lsc %f sc %f\n", 
	   ldist->lname, a, b, len, ldist->min, ldist->lsc[len-ldist->min], *sc);

  return eslOK;

 ERROR:
  return status;
}

int
dp_recursion_atom_disegment_full(SCVAL *sc, GRAMMAR *G, RULE *rp, ATOM *A, 
				 BPT *bpt, ESL_DSQ *dsq, int L, int c[4], char *errbuf, int verbose)
{
  LDIST    *ldist;           /* convenience ptr to an ldist */
  int       i,j,k,l;         /* indices used for score lookups */
  int       x;	             /* index of a sequence positions */
  int       n;               /* counter over coordenates */
  int       l1, l2, lsum;    /* length of segments */
  int       len;             /* index of a disegment */
  int       dim;
  int       status;
  
  if (A->nldists != 1) ESL_XFAIL(eslFAIL, errbuf, "wrong number of ldist (%d) for atom %s", A->nldists, A->atom_syntax);
  if (A->ncoords != 4) ESL_XFAIL(eslFAIL, errbuf, "wrong number of coords (%d) for atom %s", A->ncoords, A->atom_syntax);

  ldist = &(G->ldist[A->ldist_idx[0]]);
  
  for (n = 0; n < A->ncoords; n ++) {
    switch(A->coordbase[n]) {
    case COORD_I: 
      i = c[A->coordbase[n]] + A->offset[n];
      break;
    case COORD_J:
      j = c[A->coordbase[n]] + A->offset[n];
      break;
    case COORD_K:
      k = c[A->coordbase[n]] + A->offset[n];
      break;
    case COORD_L:
      l = c[A->coordbase[n]] + A->offset[n];
      break;
    default:     
      ESL_XFAIL(eslFAIL, errbuf, "coord not found. rule %s, atom %s", rp->rule_syntax, A->atom_syntax);
       break;
    }
  }
  
  if (i < 0 || i > L)         { (*sc) = -eslINFINITY; return eslOK; } 
  if (j < 0 || j > L)         { (*sc) = -eslINFINITY; return eslOK; } 
  if (k < 0 || k > L)         { (*sc) = -eslINFINITY; return eslOK; } 
  if (l < 0 || l > L)         { (*sc) = -eslINFINITY; return eslOK; } 
  if (k-i+1 < 0 || j-l+1 < 0) { (*sc) = -eslINFINITY; return eslOK; } 
  l1   = k-i+1;
  l2   = j-l+1;
  lsum = l1 + l2;
  dim  = ldist->max + 1;
  len  = l2 * dim + l1;

  /* add the contribution of residues */
  for (x = i; x <= k; x ++) {
    if (bpt->ct[0][x] == 0) { /* residue is unpaired */
      if (dsq[x] < 4) 
	{
	  if (ldist->esc[dsq[x]] <= -eslINFINITY) (*sc)  = -eslINFINITY; 
	  else                                    (*sc) += ldist->esc[dsq[x]];	  
	}
      else 
	{
	  (*sc) += log(0.25);	 
	}
    }
    else { /* residue is paired to something */
      (*sc) = -eslINFINITY;
    } 
  }
  for (x = l; x <= j; x ++) {
    if (bpt->ct[0][x] == 0) { /* residue is unpaired */
      if (dsq[x] < 4) 
	{
	  if (ldist->esc[dsq[x]] <= -eslINFINITY) (*sc)  = -eslINFINITY; 
	  else                                    (*sc) += ldist->esc[dsq[x]];	  
	}
      else 
	{
	  (*sc) += log(0.25);	 
	}
    }
    else { /* residue is paired to something */
      (*sc) = -eslINFINITY;
    } 
  }
  
  /* add the disegment length contribution */
  if (lsum < ldist->min || lsum > ESL_MIN(L,ldist->max)) /* boundaries */
    (*sc) = -eslINFINITY;
  else if (ldist->lsc[len] == -eslINFINITY)
    (*sc) = -eslINFINITY;
  else if ((*sc) > -eslINFINITY)
    (*sc) += ldist->lsc[len];
  if (0&&i==8&&j==32) printf("\ndisegment_full i=%d j=%d k=%d l=%d L=%d sc %f ldist %f\n", 
				 i, j, k, l, L, *sc, ldist->lsc[len]);
  
  return eslOK;

 ERROR:
  return eslFAIL;
}

int
dp_recursion_atom_disegment_joint(SCVAL *sc, SCVAL **cykaux, GRAMMAR *G, RULE *rp, DRULE *jdr, ATOM *A, 
				  BPT *bpt, ESL_DSQ *dsq, int L, int d, int mid, int c[4], ESL_STACK *alts, char *errbuf, int verbose)
{
  int       status;

  if (alts != NULL) {
    if ((status = dp_recursion_atom_disegment_joint_order4(sc, G, rp, A, bpt, dsq, L, c, errbuf, verbose))          != eslOK) goto ERROR;
  }
  else {
    if ((status = dp_recursion_atom_disegment_joint_order3(sc, cykaux, G, rp, jdr, A, L, d, mid, errbuf, verbose)) != eslOK) goto ERROR;
  }
  return eslOK;

 ERROR:
  return eslFAIL;
}

int
dp_recursion_atom_disegment_joint_order4(SCVAL *sc, GRAMMAR *G, RULE *rp, ATOM *A, 
					 BPT *bpt, ESL_DSQ *dsq, int L, int c[4], char *errbuf, int verbose)
{
  LDIST    *ldist;     /* convenience ptr to an ldist */
  int       i,j,k,l;   /* indices used for score lookups */
  int       x;	       /* index of a sequence positions */
  int       n;         /* counter over coordenates */
  int       len;       /* length of segments */
  int       status;
  
  if (A->nldists != 1) ESL_XFAIL(eslFAIL, errbuf, "wrong number of ldist (%d) for atom %s", A->nldists, A->atom_syntax);
  if (A->ncoords != 4) ESL_XFAIL(eslFAIL, errbuf, "wrong number of coords (%d) for atom %s", A->ncoords, A->atom_syntax);

  ldist = &(G->ldist[A->ldist_idx[0]]);
  
  for (n = 0; n < A->ncoords; n ++) {
    switch(A->coordbase[n]) {
    case COORD_I: 
      i = c[A->coordbase[n]] + A->offset[n];
      break;
    case COORD_J:
      j = c[A->coordbase[n]] + A->offset[n];
      break;
    case COORD_K:
      k = c[A->coordbase[n]] + A->offset[n];
      break;
    case COORD_L:
      l = c[A->coordbase[n]] + A->offset[n];
      break;
    default:     
      ESL_XFAIL(eslFAIL, errbuf, "coord not found. rule %s, atom %s", rp->rule_syntax, A->atom_syntax);
       break;
    }
  }
  
  if (i < 0 || i > L)         { (*sc) = -eslINFINITY; return eslOK; } 
  if (j < 0 || j > L)         { (*sc) = -eslINFINITY; return eslOK; } 
  if (k < 0 || k > L)         { (*sc) = -eslINFINITY; return eslOK; } 
  if (l < 0 || l > L)         { (*sc) = -eslINFINITY; return eslOK; } 
  if (k-i+1 < 0 || j-l+1 < 0) { (*sc) = -eslINFINITY; return eslOK; } 
  len = k-i+1 + j-l+1;

  /* add the contribution of residues */
  for (x = i; x <= k; x ++) {
    if (bpt->ct[0][x] == 0) { /* residue is unpaired */
      if (dsq[x] < 4) 
	{
	  if (ldist->esc[dsq[x]] <= -eslINFINITY) (*sc)  = -eslINFINITY; 
	  else                                    (*sc) += ldist->esc[dsq[x]];	  
	}
      else 
	{
	  (*sc) += log(0.25);	 
	}
    }
    else { /* residue is paired to something */
      (*sc) = -eslINFINITY; return eslOK; 
    } 
  }
  for (x = l; x <= j; x ++) {
    if (bpt->ct[0][x] == 0) { /* residue is unpaired */
      if (dsq[x] < 4) 
	{
	  if (ldist->esc[dsq[x]] <= -eslINFINITY) (*sc)  = -eslINFINITY; 
	  else                                    (*sc) += ldist->esc[dsq[x]];	  
	}
      else 
	{
	  (*sc) += log(0.25);	 
	}
    }
    else { /* residue is paired to something */
      (*sc) = -eslINFINITY; return eslOK; 
    } 
  }
  
  /* add the disegment length contribution */
  if (len < ldist->min || len > ESL_MIN(L,ldist->max)) /* boundaries */
    (*sc) = -eslINFINITY;
  else if (ldist->lsc[len-ldist->min] == -eslINFINITY)
    (*sc) = -eslINFINITY;
  else if ((*sc) > -eslINFINITY)
    (*sc) += ldist->lsc[len-ldist->min];
  if (verbose) printf("\ndisegment_joint_order4 i=%d j=%d k=%d l=%d L=%d sc %f ldist %f\n", 
				 i, j, k, l, L, *sc, ldist->lsc[len-ldist->min]);
  
  return eslOK;

 ERROR:
  return eslFAIL;
}

int
dp_recursion_atom_disegment_joint_order3(SCVAL *sc, SCVAL **cykaux, 
					 GRAMMAR *G, RULE *rp, DRULE *jdr, ATOM *A, 
					 int L, int d, int mid, char *errbuf, int verbose)
{
  LDIST    *ldist;     /* convenience ptr to an ldist */
  int       len;       /* length of disegment */
  int       v;         /* index of the auxiliary matrix */
  int       status;
  
  if (A->nldists != 1) ESL_XFAIL(eslFAIL, errbuf, "wrong number of ldist (%d) for atom %s", A->nldists, A->atom_syntax);
  if (A->ncoords != 4) ESL_XFAIL(eslFAIL, errbuf, "wrong number of coords (%d) for atom %s", A->ncoords, A->atom_syntax);

  ldist = &(G->ldist[A->ldist_idx[0]]);
  
  /* length of disegment */
  len = d - mid + jdr->ds_off[COORD_J] - jdr->ds_off[COORD_I];
  
  /* add the contribution of what is inside the disegment */
  v = rp->jdr_idx;
  if ((*sc) > -eslINFINITY) { 
    if (cykaux[v][mid] > -eslINFINITY) (*sc) += cykaux[v][mid]; 
    else                              (*sc)  = -eslINFINITY; 
  }
  
  /* add the disegment length contribution */
  if (len < ldist->min || len > ESL_MIN(L,ldist->max)) /* boundaries */
    (*sc) = -eslINFINITY;
  if ((*sc) > -eslINFINITY && ldist->lsc[len-ldist->min] > -eslINFINITY)
    (*sc) += ldist->lsc[len-ldist->min];
  else 
    (*sc) = -eslINFINITY;

  if (verbose) printf("\ndisegment_joint_order3 d=%d mid=%d len=%d sc %f aux %f ldist %f\n", d, mid, len, *sc, cykaux[v][mid],ldist->lsc[len-ldist->min]);
  
  return eslOK;

 ERROR:
  return eslFAIL;
}

int
dp_recursion_atom_disegment_tied(SCVAL *sc, SCVAL *cykstem, GRAMMAR *G, RULE *rp, DRULE *stemr, ATOM *A, 
				 int L, int d, int mid, char *errbuf, int verbose)
{  
  LDIST  *ldist;     /* convenience ptr to an ldist */
  int     len;       /* length of segments */
  int     s;         /* index of the stemr */
  int     status;
 
  if (A->nldists != 1) ESL_XFAIL(eslFAIL, errbuf, "wrong number of ldist (%d) for atom %s", A->nldists, A->atom_syntax);
  if (A->ncoords != 4) ESL_XFAIL(eslFAIL, errbuf, "wrong number of coords (%d) for atom %s", A->ncoords, A->atom_syntax);
  
  ldist = &(G->ldist[A->ldist_idx[0]]);
   
  /* length of stem */
  len = d - mid - stemr->ds_off[COORD_I] + stemr->ds_off[COORD_J];
  if (len%2 != 0) { (*sc) = -eslINFINITY; return eslOK; }
  len /= 2;
  
 /* add emissions to score */
  s = rp->stemr_idx;
  if ((*sc) > -eslINFINITY) { 
    if (cykstem[s] > -eslINFINITY) (*sc) += cykstem[s];
    else                           (*sc)  = -eslINFINITY;
  }

  /* add the length contribution (transition probability) */
  if (len < ldist->min || len > ESL_MIN(L, ldist->max)) /* boundaries */
    (*sc) = -eslINFINITY;
  if ((*sc) > -eslINFINITY && ldist->lsc[len-ldist->min] > -eslINFINITY)
    (*sc) += ldist->lsc[len-ldist->min];
  else 
    (*sc) = -eslINFINITY;

  if (verbose) printf("TIED d %d mid %d len %d cykstem %f sc %f\n", d, mid, len, cykstem[s], (*sc));

  return eslOK;

 ERROR:
  return eslFAIL;
}

