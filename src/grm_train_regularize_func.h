#ifndef TORNADO_TRAIN_REGULARIZE_FUNC_INCLUDE
#define TORNADO_TRAIN_REGULARIZE_FUNC_INCLUDE

#include <stdio.h>

#include <easel.h>
#include <esl_sq.h>

#include "grammar.h"
#include "grm.h"
#include "grm_minimizer.h"

struct regularize_data {
  struct cgd_data  cgd_data;
  int              nv; /* dimension of model parameters */
  int              nc; /* dimension of hyperparameters */
  double           *C;  /* hyperparameters */
};

extern int GrmTrainREG(ESL_GETOPTS *go, struct cfg_s *cfg);
extern int GrmTrainREG_MM(ESL_GETOPTS *go, struct cfg_s *cfg);

#endif /* TORNADO_TRAIN_REGULARIZE_FUNC_INCLUDE */
  
