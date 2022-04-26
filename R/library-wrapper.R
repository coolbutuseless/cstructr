

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Call the C library function with an externalptr
#'
#' @param mycstruct externalptr to a MyCStruct object
#'
#' @return NULL
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
multiply <- function(mycstruct) {
  .Call(multiply_, mycstruct)
}
