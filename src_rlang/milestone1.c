/* Test program for milestone 1: 
 * get CYK parser running with a +1 Nussinov.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <easel.h>
#include <esl_alphabet.h>
#include <esl_getopts.h>
#include <esl_msa.h>
#include <esl_sqio.h>
#include <esl_wuss.h>

#include "util.h"
#include "grammar.h"
#include "cyk.h"
#include "nussinov.h"

static ESL_OPTIONS options[] = {
 /* name          type    default  env_var  range toggles reqs incompats */
  { "-1",       eslARG_NONE,     FALSE,   NULL,  NULL,  NULL,  NULL, NULL },
  { "--infmt",  eslARG_STRING,    NULL,   NULL,  NULL,  NULL,  NULL, NULL },
  {  0, 0, 0, 0, 0, 0, 0, 0 },
};

static char usage[] = "\
Usage: ./milestone1 [-options] <infile> <outputfile>\n\
 where <infile> is a Stockholm format alignment file\n\
 Available options are:\n\
  -1          : use hardcoded Nussinov +1 CYK, not generalized CYK\n\
  --infmt <s> : specify that format of <infile> is <s>\n\
";

int
main(int argc, char **argv)
{
  ESL_GETOPTS  *go;
  char         *seqfile;
  char         *outfile;
  ESL_ALPHABET *abc;
  ESL_SQFILE   *sqfp;
  FILE         *fp;
  ESL_SQ       *sq;
  GRAMMAR      *G;
  int           L;
  CYKVAL     ***cyk;
  CYKVAL        sc;
  int          *ct;           /* base pairing structure 1..n */
  int           status;
  float         mb;		/* CYK memory usage in MB */

  int   do_hardcode;        	
  char *informat;
  int   infmt;

  /* Process command line
   */
  go = esl_getopts_Create(options);
  esl_opt_ProcessCmdline(go, argc, argv);
  esl_opt_VerifyConfig(go);

  esl_opt_GetBooleanOption(go, "-1",       &do_hardcode);
  esl_opt_GetStringOption (go, "--infmt",  &informat);
  
  if (esl_opt_ArgNumber(go) != 2) 
    Die("Incorrect number of command line arguments.\n%s\n", usage); 

  seqfile = esl_opt_GetCmdlineArg(go, eslARG_STRING, NULL);
  outfile = esl_opt_GetCmdlineArg(go, eslARG_STRING, NULL);

  infmt = eslMSAFILE_STOCKHOLM;
  if (informat != NULL)
    {
      infmt = esl_sqfile_FormatCode(informat);
      if (infmt == eslSQFILE_UNKNOWN) 
	Die("Unrecognized file format %s\n", informat);
    }
  esl_getopts_Destroy(go);


  /* OK, go.
   */
  abc = esl_alphabet_Create(eslRNA);
  G   = Grammar_CreateNussinovTest();
  Grammar_SetMinDistances(G);
  /*  Grammar_Dump(stdout, G); */


  if ((fp = fopen(outfile, "w")) == NULL) 
    Die("failed to open %s for output", outfile);

  if (esl_sqfile_Open(seqfile, infmt, NULL, &sqfp) != eslOK)
    Die("failed to open %s", seqfile);
  sq = esl_sq_Create();

  while ((status = esl_sq_Read(sqfp, sq)) == eslOK) 
    {
      L   = sq->n;
      esl_abc_CreateDigitalSequence(abc, sq->seq, L, &(sq->dsq));

      if (do_hardcode)
	{
	  mb  = TestMatrixSize(L);
	  sc  = TestNussinovCYK(sq->dsq, L, &ct);
	}
      else
	{
	  mb  = CYK_MatrixSize(G->M, L);
	  sc  = CYK_Fill(G, sq->dsq, L, &cyk);
	  CYK_TraceCT(cyk, G, sq->dsq, L, &ct);
	  CYK_Destroy(cyk, G->M);
	}

      printf("%-35s sc = %5d  %6.1f MB RAM   len %4d\n", 
	     sq->name, sc, mb, sq->n);

      sq->ss  = malloc(sizeof(char) * (L+1));
      status = esl_ct2wuss(ct, L, sq->ss);
      if (status != eslOK) abort();

      esl_sq_Write(fp, sq, eslMSAFILE_STOCKHOLM);

      free(sq->dsq); sq->dsq = NULL;
      free(sq->ss);  sq->ss  = NULL; 
      free(ct);
      esl_sq_Reuse(sq);
    }

  if (status == eslEFORMAT) 
    Die("Parse failed at line %d:\n%s\n", sqfp->linenumber, sqfp->errbuf);
  else if (status != eslEOF)
    Die("Parse failed at line %d\n", sqfp->linenumber);

  Grammar_Destroy(G);
  esl_sq_Destroy(sq);
  esl_sqfile_Close(sqfp);
  esl_alphabet_Destroy(abc);
  fclose(fp);
  exit (0);
}



