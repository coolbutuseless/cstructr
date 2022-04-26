
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "struct-define.h"
#include "struct-box-unbox.h"



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Finalize a MyCStruct which we copied into dynamically allocated memory
// Generated from struct definition
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MyCStruct_finalizer(SEXP mycstruct_) {
  Rprintf("MyCStruct finalizer called to free the C pointer memory\n");
  MyCStruct *mycstruct = R_ExternalPtrAddr(mycstruct_);
  free(mycstruct);
  R_ClearExternalPtr(mycstruct_);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// C MyCStruct to R ExternalPtr
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP MyCStruct_to_external_ptr(MyCStruct mycstruct) {

  MyCStruct *mycstruct_copy;
  mycstruct_copy = calloc(1, sizeof(MyCStruct));

  memcpy(mycstruct_copy, (void *)&mycstruct, sizeof(MyCStruct));

  SEXP res_ = PROTECT(R_MakeExternalPtr(mycstruct_copy, R_NilValue, R_NilValue));
  R_RegisterCFinalizer(res_, MyCStruct_finalizer);
  SET_CLASS(res_, mkString("MyCstruct_extptr"));

  UNPROTECT(1);
  return res_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// $ ExternalPtr to C MyCStruct
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MyCStruct external_ptr_to_MyCStruct(SEXP mycstruct_) {

  if (!inherits(mycstruct_, "MyCstruct_extptr")) error("Expecting 'mycstruct_' to be an 'MyCstruct_extptr' ExternalPtr");

  MyCStruct *mycstruct = TYPEOF(mycstruct_) != EXTPTRSXP ? NULL : (MyCStruct *)R_ExternalPtrAddr(mycstruct_);
  if (mycstruct == NULL) error("MyCStruct pointer is invalid/NULL");

  // Need to return a concrete instance of a mycstruct
  MyCStruct mycstruct_concrete;
  memcpy(&mycstruct_concrete, mycstruct, sizeof(MyCStruct));

  return mycstruct_concrete;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// C "MyCStruct *" to R ExternalPtr
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP MyCStruct_ptr_to_external_ptr(MyCStruct *im) {

  SEXP res_ = PROTECT(R_MakeExternalPtr(im, R_NilValue, R_NilValue));
  SET_CLASS(res_, mkString("MyCstruct_extptr"));

  UNPROTECT(1);
  return res_;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// R ExternalPtr to C "MyCStruct *" (length = 1)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MyCStruct * external_ptr_to_MyCStruct_ptr(SEXP mycstruct_) {
  if (!inherits(mycstruct_, "MyCstruct_extptr")) error("Expecting 'mycstruct_' to be an 'MyCstruct_extptr' ExternalPtr");

  MyCStruct *mycstruct = TYPEOF(mycstruct_) != EXTPTRSXP ? NULL : (MyCStruct *)R_ExternalPtrAddr(mycstruct_);
  if (mycstruct == NULL) error("MyCStruct pointer is invalid/NULL");

  return mycstruct;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// R "List of ExternalPtrs" to C "MyCStruct Array Ptr"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MyCStruct *list_of_external_ptrs_to_MyCStruct_array_ptr(SEXP list_) {

  if (!isVectorList(list_)) {
    error("external_ptr_to_mycstruct_array: Expected List argument but got %s", type2char(TYPEOF(list_)));
  }

  int N = length(list_);
  if (N == 0) {
    return NULL;
  }

  MyCStruct *array = calloc(N, sizeof(MyCStruct));

  for (int i=0; i<N; i++) {
    MyCStruct *tmp = external_ptr_to_MyCStruct_ptr(VECTOR_ELT(list_, i));
    memcpy(&array[i], tmp, sizeof(MyCStruct));
  }


  return array;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// C "MyCStruct Array Ptr" to R "List of ExternalPtrs"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP MyCStruct_array_ptr_to_list_of_external_ptrs(MyCStruct *array, int N) {

  SEXP list_ = PROTECT(allocVector(VECSXP, N));

  for (int i=0; i<N; i++) {
    SET_VECTOR_ELT(list_, i, MyCStruct_ptr_to_external_ptr(&array[i]));
  }
  SET_CLASS(list_, mkString("MyCstruct_extptrPtr"));

  UNPROTECT(1);
  return list_;
}
