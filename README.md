# sinc-conv
Sinc convolution for a finite interval

## Overview
These programs approximate the indefinite convolutions conducted in [1],
which are approximated by the following two formulas:

* Sinc convolution combined with the Single-Exponential (SE) transformation [2]
* Sinc convolution combined with the Double-Exponential (DE) transformation [1]

The name of the program denotes the example number and the approximation
formula. For example, the program SE_ex1.cpp approximates the indefinite
convolution in Example 1 using the Sinc convolution combined with the SE
transformation.

For all examples, Eigen (https://eigen.tuxfamily.org/) is needed for
linear algebra computation. In some examples, Cephes Math Library is
used for computation of Fresnel integrals, and necessary files (mconf.h,
polevl.cpp, fresnl.cpp) are included.

Each program investigates maximum approximation error among 200 equally
spaced points over the interval (0, 2), increasing a truncation number N
as N = 2, 4, 6, 8, 10, ..., then outputs n=2N+1 (the number of function
evaluation) and maximum error.

## Results
Outputs by those programs are stored in data/ directory, with .dat extension.
Gnuplot programs for creating graphs are also stored in the directory.

computation environment:

OS: macOS Monterey  
CPU: 2.4 GHz (quad core) Intel Core i5  
Memory: 16 GB 2133 MHz LPDDR3  
Compiler: Apple clang version 14.0.0  
Library: Eigen 3.4.0

## References
[1] T. Okayama:
 Refinement of the theory and convergence of the Sinc convolution,
 in preparation.  
[2] F. Stenger:
 Collocating convolutions, Mathematics of Computation, Vol. 64 (1995),
 pp. 211--235.
