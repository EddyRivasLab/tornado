/* m2_collate.c
 * Auxiliary training program for milestone 2: 
 * Parameter estimation for a Nussinov generalized grammar, given
 * a file of filenames, each of which contains counts for one
 * known structure, produced by the "m2_train --cfiles" option.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <easel.h>
#include <esl_fileparser.h>
#include <esl_getopts.h>

#include "util.h"
#include "grammar.h"
#include "parsetree.h"
#include "sscyk.h"

static ESL_OPTIONS options[] = {
 /* name          type       default  env_var  range  toggles reqs incompats */
  {  0, 0, 0, 0, 0, 0, 0, 0 },
};

static char usage[] = "\
Usage: ./m2_collate <cfile.fof> <outfile>\n\
 where <cfile.fof> is a file of filenames: each of these filenames is\n\
 a counts file produced by m2_train --cfiles.\n\
 Grammar parameters are saved to <outfile>.\n\
";

int
main(int argc, char **argv)
{
  ESL_GETOPTS    *go;
  char           *foffile;
  char           *outfile;
  FILE           *fofp;  
  ESL_FILEPARSER *efp;
  char           *filename;
  FILE           *fp;
  GRAMMAR        *G;
  int             status;

  /* Process command line
   */
  go = esl_getopts_Create(options, usage);
  esl_opt_ProcessCmdline(go, argc, argv);
  esl_opt_VerifyConfig(go);

  if (esl_opt_ArgNumber(go) != 2) 
    Die("Incorrect number of command line arguments.\n%s\n", usage); 

  foffile = esl_opt_GetCmdlineArg(go, eslARG_STRING, NULL);
  outfile = esl_opt_GetCmdlineArg(go, eslARG_STRING, NULL);

  esl_getopts_Destroy(go);

  /* Initialize the grammar; open the .fof file.
   */
  G   = Grammar_CreateNussinovTest();
  Grammar_Zero(G);

  if ((fofp = fopen(foffile, "r")) == NULL)
    Die("Failed to open .fof file %s", foffile);
  if ((efp = esl_fileparser_Create(fofp)) == NULL)
    Die("Failed to create fileparser for .fof file %s", foffile);
  esl_fileparser_SetCommentChar(efp, '#');
  
  /* Read all the counts files in, accumulating their counts in G.
   */
  while ((status = esl_fileparser_GetToken(efp, &filename, NULL)) == eslOK) 
    {
      if ((fp = fopen(filename, "r")) == NULL)
	Die("Failed to open count checkpoint file %s\n", filename);
      Grammar_Read_Counts(fp, G);
      fclose(fp);
    }
  if (status != eslEOF)
    Die("Something went wrong in reading .fof file %s\n", foffile);

  esl_fileparser_Destroy(efp);
  fclose(fofp);
  
  /* Write the final counts out; 
   * parameterize the grammar G from the counts, and save the params.
   */
  Grammar_Write_Counts(stdout, G);
  Grammar_Priorify(G);
  Grammar_Normalize(G);
  if ((fp = fopen(outfile, "w")) == NULL) 
    Die("failed to open %s for output", outfile);
  Grammar_Write(fp, G);
  fclose(fp);

  Grammar_Destroy(G);
  exit (0);
}



