
// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

SEXP extern MyCStruct_();
SEXP extern MyCStruct_get_();
SEXP extern MyCStruct_set_();
SEXP extern MyCStruct_copy_();

SEXP extern multiply_();

static const R_CallMethodDef CEntries[] = {

  {"MyCStruct_"    , (DL_FUNC) &MyCStruct_    , 2},
  {"MyCStruct_set_", (DL_FUNC) &MyCStruct_set_, 3},
  {"MyCStruct_get_", (DL_FUNC) &MyCStruct_get_, 2},
  {"MyCStruct_copy_", (DL_FUNC) &MyCStruct_copy_, 1},

  {"multiply_", (DL_FUNC) &multiply_, 1},

  {NULL , NULL, 0}
};


void R_init_cstructr(DllInfo *info) {
  R_registerRoutines(
    info,      // DllInfo
    NULL,      // .C
    CEntries,  // .Call
    NULL,      // Fortran
    NULL       // External
  );
  R_useDynamicSymbols(info, FALSE);
}



