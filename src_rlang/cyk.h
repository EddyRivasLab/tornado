/* cyk.h
 * CYK algorithm for folding a sequence using a generalized RNA SCFG.
 * 
 * SRE, Wed Mar 23 09:51:42 2005 [St. Louis]
 * SVN $Id$
 */
#ifndef TORNADO_CYK_INCLUDED
#define TORNADO_CYK_INCLUDED

#include "grammar.h"		/* includes CYKVAL typedef */
#include "parsetree.h"

extern CYKVAL ***CYK_Create(int M, int L);
extern void      CYK_Destroy(CYKVAL ***cyk, int M);
extern float     CYK_MatrixSize(int M, int L);

extern void      CYK_Dump(FILE *fp, CYKVAL ***cyk, int M, int L);
extern void      CYK_DumpOneDeck(FILE *fp, CYKVAL **sc, int L);

extern CYKVAL CYK_Fill(GRAMMAR *G, char *dsq, int L, CYKVAL ****ret_cyk);
extern int    CYK_TraceCT(CYKVAL ***cyk, GRAMMAR *G, char *dsq, int L, 
			  int **ret_ct);
extern int    CYK_TraceParsetree(CYKVAL ***cyk, GRAMMAR *G, char *dsq, int L,
				 PARSETREE **ret_T);
#endif /*TORNADO_CYK_INCLUDED*/
