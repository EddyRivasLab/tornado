/* util.c
 * Miscellaneous utilities needed by Tornado
 * 
 * SRE, Mon Mar 21 14:47:11 2005 [St. Louis]
 * SVN $Id$
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <math.h>

#include "grammar.h"
#include "util.h"



/* Function: Die()
 *
 * Purpose:  Print an error message and die. The arguments
 *           are formatted exactly like arguments to printf().
 *
 * Return:   None. Exits the program.
 */
/* VARARGS0 */
void
Die(char *format, ...)
{
  va_list  argp;
                                /* format the error mesg */
  fprintf(stderr, "\nFATAL: ");
  va_start(argp, format);
  vfprintf(stderr, format, argp);
  va_end(argp);
  fprintf(stderr, "\n");
  fflush(stderr);
                                /* exit  */
  exit(1);
}



/* Function: Prob2Score()
 * 
 * Purpose:  Convert a probability to a scaled integer log odds score. 
 *           Round to nearest integer (i.e. use of +0.5 and floor())
 *           Return the score. (Use null=1.0 for straight log likelihood scores.)
 */
int
Prob2Score(double p, double null)
{
  if   (p == 0.0) return -CYKINFTY;
  else            return (int) floor(0.5 + INTSCALE * log(p/null));
}

/* Function: Score2Prob()
 * 
 * Purpose:  Convert an integer log odds score back to a probability;
 *           needs the null model probability, if any, to do the conversion.
 *           (Use null=1.0 for log likelihood scores.)
 */
double
Score2Prob(int sc, double null)
{
  if (sc == -CYKINFTY) return 0.;
  else                 return (null * exp((double) sc / INTSCALE));
}



/* Function:  EmissionAtomIndex()
 * Incept:    SRE, Tue Mar 22 17:12:05 2005 [St. Louis]
 *
 * Purpose:   Calculates and returns array index of the residue emission(s) from
 *            an EMISSION_ATOM. If any of the involved residues are ambiguous,
 *            returns -1 instead.
 *
 * Args:      dsq - digitized sequence 
 *            L   - length of dsq
 *            c   - coord array (ijkl) relative to dsq's 1..L
 *            rp  - pointer to a production rule
 *            e   - index of emission atom in rule rp
 *
 * Returns:   array index of emission in edist[].ep or .esc;
 *            or -1, if any of the residues are ambiguous.
 *
 * Throws:    (no abnormal error conditions)
 *
 * Xref:      
 */
int
EmissionAtomIndex(char *dsq, int L, int c[4], RULE *rp, int e)
{
  int x;
  int eofw;
  int i;
  int a;

  eofw = rp->edist_idx[e];
  x = 0;
  for (i = 0; i < rp->ncoords[e]; i++)
    {
      a = c[rp->coordbase[e][i]] + rp->offset[e][i];
      assert(a >= 1 && a <= L);
      if (dsq[a] >= 4) return -1;  /* only accept 0..3 */
      x = x*4 + dsq[a];
    }
  return x;
}
