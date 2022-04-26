
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "struct-define.h"
#include "struct-box-unbox.h"
#include "library.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This is an R-accessible C function that knows about R/SEXP and
// unpacks the objects and does the library call
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP multiply_(SEXP mycstruct_ptr_) {
  MyCStruct *mycstruct = external_ptr_to_MyCStruct_ptr(mycstruct_ptr_);
  double res = multiply(mycstruct);
  return ScalarReal(res);
}
