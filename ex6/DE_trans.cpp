#include "DE_trans.h"

double sinc(double x)
{
  double ret = 1;

  if (x != 0) {
    ret = sin(M_PI * x)/(M_PI * x);
  }

  return ret;
}

double DE_trans(double a, double b, double t)
{
/*return 0.5 * ( (b - a) * tanh( M_PI_2 * sinh(t) ) + (b + a) );*/
  return b / (1 + exp(-M_PI*sinh(t))) + a / (1 + exp(M_PI*sinh(t)));
}

double DE_trans_inv(double a, double b, double x)
{
  return asinh( M_2_PI * atanh( (2*x - (b + a))/(b - a) ) );
}

double DE_trans_div(double a, double b, double t)
{
  double numerator   = M_PI_2 * cosh(t);
  double denominator = cosh( M_PI_2 * sinh(t) ) * cosh( M_PI_2 * sinh(t) );

  return 0.5*(b - a) * numerator / denominator;
}

double DE_basis_func(int j, int m,int n, double a,double b, double x, double h)
{
  double ret = 0;

  if (j == -m) {
    for (int i = -m+1; i <= n; i++) {
      ret -=
        sinc(DE_trans_inv(a, b, x)/h  - i) / (1 + exp(M_PI * sinh(i*h)));
    }
    ret += 1.0 / (1 + exp(M_PI * sinh(DE_trans_inv(a, b, x))) );
    ret *= 1 + exp(M_PI * sinh(-m * h));
  }

  if (-m < j && j < n) {
    ret = sinc(DE_trans_inv(a, b, x)/h  - j);
  }

  if (j == n) {
    for (int i = -m; i < n; i++) {
      ret -=
        sinc(DE_trans_inv(a, b, x)/h  - i)/(1 + exp(- M_PI * sinh(i*h)));
    }
    ret += (x - a)/(b - a);
    ret *= 1 + exp(- M_PI * sinh(n * h));
  }

  return ret;
}
