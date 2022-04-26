

SEXP MyCStruct_to_external_ptr(MyCStruct mycstruct);
MyCStruct external_ptr_to_MyCStruct(SEXP mycstruct_);

SEXP MyCStruct_ptr_to_external_ptr(MyCStruct *mycstruct);
MyCStruct * external_ptr_to_MyCStruct_ptr(SEXP mycstruct_);

MyCStruct *list_of_external_ptrs_to_MyCStruct_array_ptr(SEXP list_);
SEXP MyCStruct_array_ptr_to_list_of_external_ptrs(MyCStruct *array, int N);
