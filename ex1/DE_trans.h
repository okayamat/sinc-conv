#include <cmath>

#if !defined(___DE_trans___)
#define ___DE_trans___

double DE_trans(double a, double b, double t);

double DE_trans_inv(double a, double b, double t);

double DE_trans_div(double a, double b, double t);

double DE_basis_func(int j, int m,int n, double a,double b, double x, double h);

#endif // ___DE_trans___
