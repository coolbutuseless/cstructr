
<!-- README.md is generated from README.Rmd. Please edit that file -->

# cstructr

<!-- badges: start -->

![](https://img.shields.io/badge/cool-useless-green.svg)
<!-- badges: end -->

`{cstructr}` is a demonstration package illustrating how a C struct may
be wrapped and manipulated from within R as an external pointer.

This is a “full-service” implementation which makes the internal values
of the struct accessible from R via getters and setters.

For bespoke solutions, a lot of the code could be excised to just keep
some core functions.

#### Note: The code in this package was auto-generated by parsing the C struct definition and the C library function declaration.

#### C Struct Definition

``` c
typedef struct {
  int N;
  double strength;
} MyCStruct;
```

#### C Library Function Declaration

``` c
double multiply(MyCStruct *mycstruct);
```

## Installation

You can install from
[GitHub](https://github.com/coolbutuseless/cstructr) with:

``` r
# install.package('remotes')
remotes::install_github('coolbutuseless/cstructr')
```

## Create and Manipulate

``` r
library(cstructr)
mycstruct <- MyCStruct(N = 1, strength = 13)
mycstruct
#> MyCStruct(N = 1, strength = 13)

class(mycstruct)
#> [1] "MyCstruct_extptr"
typeof(mycstruct)
#> [1] "externalptr"

mycstruct$N
#> [1] 1
mycstruct$strength
#> [1] 13

mycstruct$N <- 3
mycstruct
#> MyCStruct(N = 3, strength = 13)

rm(mycstruct)
gc()
#> MyCStruct finalizer called to free the C pointer memory
#>           used (Mb) gc trigger (Mb) limit (Mb) max used (Mb)
#> Ncells  544954 29.2    1223177 65.4         NA   667668 35.7
#> Vcells 1015387  7.8    8388608 64.0      16384  1824692 14.0
```

Create multiple structs at once

``` r
lots <- MyCStructs(n = 3)
class(lots)
#> [1] "list"
lots
#> [[1]]
#> MyCStruct(N = 0, strength = 0)
#> [[2]]
#> MyCStruct(N = 0, strength = 0)
#> [[3]]
#> MyCStruct(N = 0, strength = 0)
```

## Call a C library function

1.  Write a “bridge function” wrapper (in C) that maps from R objects to
    C objects
2.  Call the C library function from this wrapper
3.  Return the result to R in an appropriate container

An example of a C function in a library is as follows. C libraries know
nothing about R or SEXP objects.

``` c
double multiply(MyCStruct *mycstruct) {
  return mycstruct->N * mycstruct->strength;
}
```

The “bridge” function between R and the C library call is written in C
as follows.

This function unpacks the externalptr to a real `MyCStruct` pointer,
calls the C library function, and then returns the results as an R real
numeric value.

``` c
SEXP multiply_(SEXP mycstruct_ptr_) {
  MyCStruct *mycstruct = external_ptr_to_MyCStruct_ptr(mycstruct_ptr_);
  double res = multiply(mycstruct);
  return ScalarReal(res);
}
```

The call from R is:

``` r
multiply <- function(mycstruct) {
  .Call(multiply_, mycstruct)
}
```

All these functions combine such that we can create a pointer to a C
struct in R, and then call the C library function as follows

``` r
library(cstructr)
mycstruct <- MyCStruct(N=2, strength = 4.5)
multiply(mycstruct)
#> [1] 9
```

## Auto-generation of bridge function

A lot of the code to wrap a C function and make it callable from R is
standard boilerplate.

For simple library functions, you could auto-generate a lot of this R +
C code from the C function declaration.