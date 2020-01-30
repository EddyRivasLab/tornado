/* sscyk.h
 * 
 * SRE, Wed Mar 23 09:13:28 2005 [St. Louis]
 * SVN $Id$
 */
#ifndef TORNADO_SSCYK_INCLUDED
#define TORNADO_SSCYK_INCLUDED

#include "grammar.h"
#include "parsetree.h"

/* SSCYKVAL: values in the sscyk matrix
 * 
 * For memory efficiency, the values in the cyk matrix are treated as
 * bitfields, since we only need to know 1 or 0 (possible or not
 * possible) in each cell. The code assumes that SSCYKVAL has at least
 * 32 bits available. Typedef'ing it as unsigned int should be fine on
 * most machines. If SSCYKVAL is <32 bits on your machine, the sscyk
 * code will fail. It can be >32 bits; we'll just use the low-order 32
 * bits and waste the rest.
 */
typedef unsigned int SSCYKVAL;

extern SSCYKVAL ***ssCYK_Create(int M, int L);
extern void        ssCYK_Destroy(SSCYKVAL ***cyk, int M);
extern void        ssCYK_Dump(FILE *fp, SSCYKVAL ***cyk, int M, int L);

extern int ssCYK_Fill(GRAMMAR *G, char *ss, int L, SSCYKVAL ****ret_cyk);
extern int ssCYK_Trace(SSCYKVAL ***cyk, GRAMMAR *G, char *ss, int L, 
		       PARSETREE **ret_T);



#endif /*TORNADO_SSCYK_INCLUDED*/
