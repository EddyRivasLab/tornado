/* sseval.c
 * Counts summary statistics on known secondary structures.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <easel.h>
#include <esl_alphabet.h>
#include <esl_getopts.h>
#include <esl_msa.h>
#include <esl_sqio.h>
#include <esl_vectorops.h>
#include <esl_wuss.h>

static ESL_OPTIONS options[] = {
 /* name          type       default  env_var  range  toggles reqs incompats */
  { "--infmt",  eslARG_STRING,    NULL,   NULL,  NULL,  NULL,  NULL, NULL },
  {  0, 0, 0, 0, 0, 0, 0, 0 },
};

static char usage[] = "\
Usage: ./sseval [-options] <infile>\n\
 where <infile> is a Stockholm format alignment file containing\n\
 known individual secondary structures.\n\
 \n\
 Available options are:\n\
  --infmt <s> : specify that format of <infile> is <s>\n\
";

int
main(int argc, char **argv)
{
  ESL_GETOPTS  *go;
  char         *seqfile;
  ESL_ALPHABET *abc;
  ESL_SQFILE   *sqfp;
  ESL_SQ       *sq;
  int          *ct;
  char         *fw;		/* full WUSS */
  int           L;
  int           i,j;
  int           status;

  int  *sng;	        /* counts of singlet residues, one structure */
  int  *tot_sng;	/* counts of singlet residues, cumulative */
  int   nsng;		/* total # of singlet bases, one structure */
  int   tot_nsng;	/* total # of single bases, cumulative */
  int   nsng_degen;	/* total # of degenerate singlet bases, one str */
  int   tot_nsng_degen; /* total # of degen single bases, cumulative */


  int **bp;		/* counts of base pairs, one structure */
  int **tot_bp;		/* counts of base pairs, cumulative */
  int   nbp;		/* total # of base pairs, one structure */
  int   tot_nbp;	/* total # of base pairs, cumulative */
  int   nbp_degen;	/* total # of degenerate base pairs, one str */
  int   tot_nbp_degen;	/* total # of degen bp, cumulative */

  char *informat;
  int   infmt;

  /*****************************************************************
   * Process command line
   */
  go = esl_getopts_Create(options, usage);
  esl_opt_ProcessCmdline(go, argc, argv);
  esl_opt_VerifyConfig(go);

  esl_opt_GetStringOption (go, "--infmt",  &informat);
  
  if (esl_opt_ArgNumber(go) != 1) 
    esl_fatal("Incorrect number of command line arguments.\n%s\n", usage); 

  seqfile = esl_opt_GetCmdlineArg(go, eslARG_STRING, NULL);

  infmt = eslMSAFILE_STOCKHOLM;
  if (informat != NULL)
    {
      infmt = esl_sqfile_FormatCode(informat);
      if (infmt == eslSQFILE_UNKNOWN) 
	esl_fatal("Unrecognized file format %s\n", informat);
    }
  esl_getopts_Destroy(go);


  /*****************************************************************
   * Init alphabet; open seqfile.
   */
  abc = esl_alphabet_Create(eslRNA);
  if (esl_sqfile_Open(seqfile, infmt, NULL, &sqfp) != eslOK)
    esl_fatal("failed to open %s", seqfile);
  sq = esl_sq_Create();

  /*****************************************************************
   * Alloc and init counters
   */
  sng     = malloc(sizeof(int) * abc->Kp);
  tot_sng = malloc(sizeof(int) * abc->Kp);
  esl_vec_ISet(tot_sng, abc->Kp, 0);
  tot_nsng = tot_nsng_degen = 0;

  bp    = malloc(sizeof(int *) * abc->Kp);
  bp[0] = malloc(sizeof(int)   * abc->Kp * abc->Kp);
  for (i = 1; i <= abc->Kp; i++) 
    bp[i] = bp[0] + abc->Kp * i;
  tot_bp    = malloc(sizeof(int *) * abc->Kp);
  tot_bp[0] = malloc(sizeof(int)   * abc->Kp * abc->Kp);
  for (i = 1; i <= abc->Kp; i++) 
    tot_bp[i] = tot_bp[0] + abc->Kp*i;
  esl_vec_ISet(tot_bp[0], abc->Kp*abc->Kp, 0);
  tot_nbp = tot_nbp_degen = 0;


  /*****************************************************************
   * OK, go; collect counts from all structures in the input file.
   */
  while ((status = esl_sq_Read(sqfp, sq)) == eslOK) 
    {
      esl_vec_ISet(sng,   abc->Kp, 0);
      esl_vec_ISet(bp[0], abc->Kp*abc->Kp, 0);
      nsng = nsng_degen = 0;
      nbp  = nbp_degen  = 0;

      L   = sq->n;
      esl_abc_CreateDigitalSequence(abc, sq->seq, L, &(sq->dsq));

      if (sq->ss == NULL) esl_fatal("No secondary structure for %s\n", sq->name);

      ct = malloc(sizeof(int) * (L+1));
      status = esl_wuss2ct(sq->ss, L, ct);
      if (status != eslOK) esl_fatal("esl_wuss2ct failed");

      fw = malloc(sizeof(char) * (L+1));
      status = esl_wuss_full(sq->ss, fw);
      if (status != eslOK) esl_fatal("esl_wuss_full failed");

      /* Now we have: sq->seq[0..L-1]    Original sequence.
       *              sq->dsq[1..L]      Digitized seq.
       *              ct[1..L]           CT array for base pairing.
       *              sq->ss[0..L-1]     Original WUSS annotation
       *              fw[0..L-1]         Full (output) WUSS annotation.
       */
      
      /* Accumulate singlet, bp counts for this seq
       */
      for (i = 1; i <= L; i++)
	if (ct[i] == 0)
	  {
	    sng[(int) sq->dsq[i]]++;
	    nsng++;
	    if (esl_abc_IsDegenerate(abc, sq->dsq[i])) nsng_degen++;
	  }
        else if (ct[i] > i)	/* count base pairs once */
	  {
	    bp [(int) sq->dsq[i]] [(int) sq->dsq[ct[i]]]++;
	    nbp++;
	    if (esl_abc_IsDegenerate(abc, sq->dsq[i])
		|| esl_abc_IsDegenerate(abc, sq->dsq[ct[i]]))
	      nbp_degen++;
	  }
      
      /* (per-seq output would go here) */

      /* Increment the cumulative counters
       */
      esl_vec_IAdd(tot_sng,   sng,   abc->Kp);
      esl_vec_IAdd(tot_bp[0], bp[0], abc->Kp*abc->Kp);
      tot_nsng       += nsng;
      tot_nsng_degen += nsng_degen;
      tot_nbp        += nbp;
      tot_nbp_degen  += nbp_degen;

      free(ct);
      free(fw);
      free(sq->dsq); sq->dsq = NULL;
      free(sq->ss);  sq->ss  = NULL; 
      esl_sq_Reuse(sq);
    }
  if (status == eslEFORMAT) 
    esl_fatal("Parse failed at line %d:\n%s\n", sqfp->linenumber, sqfp->errbuf);
  else if (status != eslEOF)
    esl_fatal("Parse failed at line %d\n", sqfp->linenumber);

  /*****************************************************************
   * Output.
   */
  printf("Single-stranded residue counts (A,C,G,T, other):\n");
  for (i = 0; i < abc->K; i++)
    printf("%6d ", tot_sng[i]);
  printf("%6d\n\n", tot_nsng_degen);
  
  printf("Base pairs (not counting %d that have degeneracies):\n", tot_nbp_degen);
  for (i = 0; i < abc->K; i++)
    {
      for (j = 0; j < abc->K; j++)
	printf("%6d ", tot_bp[i][j]);
      printf("\n");
    }

  /*****************************************************************
   * Clean up and exit
   */
  free(sng);
  free(tot_sng);
  free(bp[0]); 
  free(bp);
  free(tot_bp[0]);
  free(tot_bp);
  esl_sq_Destroy(sq);
  esl_sqfile_Close(sqfp);
  esl_alphabet_Destroy(abc);
  exit (0);
}



