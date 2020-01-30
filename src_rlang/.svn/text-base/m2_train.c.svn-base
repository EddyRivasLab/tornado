/* m2_train.c
 * Training program for milestone 2: 
 * Parameter estimation for a Nussinov generalized grammar, from
 * database of known structures.
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
#include "parsetree.h"
#include "sscyk.h"

static ESL_OPTIONS options[] = {
 /* name          type       default  env_var  range  toggles reqs incompats */
  { "-s",       eslARG_INT,      "1",     NULL, "n>0",  NULL,  NULL, NULL },
  { "--cfiles", eslARG_STRING,    NULL,   NULL,  NULL,  NULL,  NULL, NULL },
  { "--infmt",  eslARG_STRING,    NULL,   NULL,  NULL,  NULL,  NULL, NULL },
  {  0, 0, 0, 0, 0, 0, 0, 0 },
};

static char usage[] = "\
Usage: ./m2_train [-options] <infile> <outfile>\n\
 where <infile> is a Stockholm format alignment file containing\n\
 known individual secondary structures, for training grammar on.\n\
 Grammar parameters are saved to <outfile>.\n\
 \n\
 Available options are:\n\
  -s <n>      : average across a sample <n> parse trees per parse [1]\n\
  --cfiles <s>: save individual counts files to <s>.1, <s>.2, etc.\n\
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
  GRAMMAR      *Gct;		/* grammar just for collecting indiv counts */
  PARSETREE    *T;
  SSCYKVAL   ***cyk;
  int           L;
  int           i;
  int           ntrees;
  int           status;
  int           nseq;

  char *cfiles;
  char *csavefile;
  char *informat;
  int   infmt;

  /* Process command line
   */
  go = esl_getopts_Create(options, usage);
  esl_opt_ProcessCmdline(go, argc, argv);
  esl_opt_VerifyConfig(go);

  esl_opt_GetStringOption (go, "--cfiles",  &cfiles);
  esl_opt_GetStringOption (go, "--infmt",   &informat);
  esl_opt_GetIntegerOption(go, "-s",        &ntrees);
  
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



  /* OK, go; collect counts from all structures in the input file.
   */
  abc = esl_alphabet_Create(eslRNA);
  G   = Grammar_CreateNussinovTest();
  Grammar_SetMinDistances(G);
  Grammar_Zero(G);
  /*  Grammar_Dump(stdout, G); */
  if (cfiles != NULL) 
    {
      Gct = Grammar_CreateNussinovTest();
      csavefile = malloc(sizeof(char) * (strlen(cfiles) + 12));
      /* +12 because max number for 32-bit int is length 10, + . + \0 */
    }

  if (esl_sqfile_Open(seqfile, infmt, NULL, &sqfp) != eslOK)
    Die("failed to open %s", seqfile);
  sq = esl_sq_Create();

  nseq = 0;
  while ((status = esl_sq_Read(sqfp, sq)) == eslOK) 
    {
      nseq++;
      if (cfiles != NULL) 
	{
	  Grammar_Zero(Gct);
	}
      L   = sq->n;
      esl_abc_CreateDigitalSequence(abc, sq->seq, L, &(sq->dsq));

      if (! ssCYK_Fill(G, sq->ss, L, &cyk))
	Die("Couldn't fill cyk matrix for structure for %s\n", sq->name);

      for (i = 0; i < ntrees; i++)
	{
	  if (! ssCYK_Trace(cyk, G, sq->ss, L, &T))
	    Die("Couldn't trace cyk matrix for structure for %s\n", sq->name);
	  /* Parsetree_Dump(stdout, T);  */
	  Parsetree_Count(T, G,   sq->dsq, L, 1./(double)ntrees); 
	  if (cfiles != NULL) 
	    Parsetree_Count(T, Gct, sq->dsq, L, 1./(double)ntrees); 
	  Parsetree_Destroy(T);
	}

      if (cfiles != NULL)
	{
	  sprintf(csavefile, "%s.%d", cfiles, nseq);
	  if ((fp = fopen(csavefile, "w")) == NULL)
	    Die("couldn't open checkpoint file %s", csavefile);
	  Grammar_Write_Counts(fp, Gct);
	  fclose(fp);
	}

      CYK_Destroy(cyk, G->M);
      free(sq->dsq); sq->dsq = NULL;
      free(sq->ss);  sq->ss  = NULL; 
      esl_sq_Reuse(sq);
    }

  if (status == eslEFORMAT) 
    Die("Parse failed at line %d:\n%s\n", sqfp->linenumber, sqfp->errbuf);
  else if (status != eslEOF)
    Die("Parse failed at line %d\n", sqfp->linenumber);
  esl_sq_Destroy(sq);
  esl_sqfile_Close(sqfp);

  Grammar_Write_Counts(stdout, G);
  Grammar_Priorify(G);
  Grammar_Normalize(G);
  if ((fp = fopen(outfile, "w")) == NULL) 
    Die("failed to open %s for output", outfile);
  Grammar_Write(fp, G);
  fclose(fp);

  Grammar_Destroy(G);
  if (cfiles != NULL) 
    {
      Grammar_Destroy(Gct);
      free(csavefile);
    }
  esl_alphabet_Destroy(abc);
  exit (0);
}



