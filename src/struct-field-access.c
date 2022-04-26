

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "struct-define.h"
#include "struct-box-unbox.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Create a new MyCStruct object
// This function was generated from the MyCStruct struct definition
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP MyCStruct_(SEXP N_, SEXP strength_) {

  if (!isInteger(N_) && !isReal(N_)) {
    error("MyCStruct: Expected 'N' to be integer/numeric but got %s", type2char(TYPEOF(N_)));
  }

  if (!isReal(strength_)) {
    error("MyCStruct: Expected 'strength' to be numeric but got %s", type2char(TYPEOF(strength_)));
  }

  MyCStruct mycstruct;

  mycstruct.N     = asInteger(N_);
  mycstruct.strength = asReal(strength_);

  return MyCStruct_to_external_ptr(mycstruct);
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// set a named field in a MyCStruct object
// This function was generated from the MyCStruct struct definition
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP MyCStruct_set_(SEXP mycstruct_, SEXP field_, SEXP value_) {

  const char *field = CHAR(asChar(field_));
  MyCStruct *mycstruct = external_ptr_to_MyCStruct_ptr(mycstruct_);

  if (strcmp(field, "N") == 0) {
    if (!isInteger(value_) && !isReal(value_)) {
      error("MyCStruct->N: Expected 'N' to be integer/numeric but got %s", type2char(TYPEOF(value_)));
    }
    if (length(value_) != 1) {
      error("MyCStruct->N: Expected 'N' to have length=1 got %i", length(value_));
    }
    mycstruct->N = asInteger(value_);
  } else if (strcmp(field, "strength") == 0) {
    if (!isReal(value_)) {
      error("MyCStruct->strength: Expected 'strength' to be numeric but got %s", type2char(TYPEOF(value_)));
    }
    if (length(value_) != 1) {
      error("MyCStruct->strength: Expected 'strength' to have length=1 got %i", length(value_));
    }
    mycstruct->strength = asReal(value_);
  } else {
    error("MyCStruct_get_(): No such field: %s", field);
  }

  return mycstruct_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Get a named field from a MyCStruct object
// This function was generated from the MyCStruct struct definition
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP MyCStruct_get_(SEXP mycstruct_, SEXP field_) {

  const char *field = CHAR(asChar(field_));
  MyCStruct *mycstruct = external_ptr_to_MyCStruct_ptr(mycstruct_);

  if (strcmp(field, "N") == 0) {
    return ScalarInteger(mycstruct->N);
  } else if (strcmp(field, "strength") == 0) {
    return ScalarReal(mycstruct->strength);
  } else {
    error("MyCStruct_get_(): No such field: %s", field);
  }
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Copy a MyCStruct object
// This function was generated from the MyCStruct struct definition
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP MyCStruct_copy_(SEXP mycstruct_) {

  MyCStruct *orig = external_ptr_to_MyCStruct_ptr(mycstruct_);
  MyCStruct *copy = calloc(1, sizeof(MyCStruct));

  memcpy(copy, orig, sizeof(MyCStruct));

  return MyCStruct_ptr_to_external_ptr(copy);
}

