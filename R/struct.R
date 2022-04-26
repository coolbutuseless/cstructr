
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Tools for MyCStruct objects
#'
#' Tools for MyCStruct objects
#'
#' These R functions have been generated from the struct defintion.
#'
#' @param mycstruct MyCStruct object
#' @param field name of struct field
#' @param value value to assign to field
#' @param n number of blank objects to create
#' @param x,... object and options passed to \code{as.character()}
#' @param N [unsigned int] Count of objects
#' @param strength [double] Some continuous parameters
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MyCStruct <- function(N = 0, strength = 0) {
  .Call(MyCStruct_, N, strength)
}


#' @rdname MyCStruct
#' @export
MyCStructs <- function(n) {
  lapply(seq(n), function(i) {
    MyCStruct()
  })
}


#' @rdname MyCStruct
#' @export
MyCStruct_copy <- function(mycstruct) {
  .Call(MyCStruct_copy_, mycstruct)
}


#' @rdname MyCStruct
#' @export
MyCStruct_set <- function(mycstruct, field, value) {
  invisible(.Call(MyCStruct_set_, mycstruct, field, value))
}


#' @rdname MyCStruct
#' @export
MyCStruct_get <- function(mycstruct, field) {
  .Call(MyCStruct_get_, mycstruct, field)
}


#' @rdname MyCStruct
#' @export
"$.MyCstruct_extptr" <- function(mycstruct, value) {
  MyCStruct_get(mycstruct, value)
}


#' @rdname MyCStruct
#' @export
'[[.MyCstruct_extptr'  <- `$.MyCstruct_extptr`


#' @rdname MyCStruct
#' @export
"$<-.MyCstruct_extptr" <- function(mycstruct, field, value) {
  MyCStruct_set(mycstruct, field, value)
}


#' @rdname MyCStruct
#' @export
'[[<-.MyCstruct_extptr' <- `$<-.MyCstruct_extptr`


#' @rdname MyCStruct
#' @export
print.MyCstruct_extptr <- function(x, ...) {
  cat(as.character(x))
}


#' Autocomplete helper for \code{MyCStruct} objects
#'
#' @param x object
#' @param pattern current pattern to match
#'
#' @importFrom utils .DollarNames
#' @export
.DollarNames.MyCstruct_extptr <- function(x, pattern) {
  c('N', 'strength')
}


#' @rdname MyCStruct
#' @export
as.character.MyCstruct_extptr <- function(x, ...) {
  fields <- c('N', 'strength')
  values <- vapply(fields, function(field) {
    val <- x[[field]]
    if (is_externalptr(val)) {
      deparse1(class(val))
    } else {
      paste( as.character(val), collapse = ", ")
    }
  }, character(1))
  res <- paste(fields, values, sep = " = ", collapse = ", ")
  paste0("MyCStruct(", res, ")")
}
