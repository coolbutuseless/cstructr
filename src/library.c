
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "struct-define.h"
#include "library.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This is a dummy function that is emulating part of an external C library
// This function doesn't understand anything to do with R or SEXPs
//
// However, I am using 'Rprintf' instead of 'printf' for this demonstration
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double multiply(MyCStruct *mycstruct) {
  return mycstruct->N * mycstruct->strength;
}
