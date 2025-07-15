#include <cmath>

#if !defined(___SE_trans___)
#define ___SE_trans___

double SE_trans(double a, double b, double t);

double SE_trans_inv(double a, double b, double x);

double SE_trans_div(double a, double b, double t);

double SE_basis_func(int j, int m,int n, double a,double b, double x, double h);

#endif // ___SE_trans___
