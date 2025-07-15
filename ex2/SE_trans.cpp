#include "SE_trans.h"

double sinc(double x)
{
  double ret = 1;

  if (x != 0) {
    ret = sin(M_PI * x)/(M_PI * x);
  }

  return ret;
}

double SE_trans(double a, double b, double t)
{
  return 0.5 * ( (b - a) * tanh(0.5*t) + (b + a) );
}

double SE_trans_inv(double a, double b, double x)
{
  return 2 * atanh( (2*x - (b + a))/(b - a) );
}

double SE_trans_div(double a, double b, double t)
{
  double numerator   = 0.5;
  double denominator = cosh( 0.5*t ) * cosh( 0.5*t );

  return 0.5*(b - a) * numerator / denominator;
}

double SE_basis_func(int j, int m,int n, double a,double b, double x, double h)
{
  double ret = 0;

  if (j == -m) {
    for (int i = -m+1; i <= n; i++) {
      ret -=
        sinc(SE_trans_inv(a, b, x)/h  - i) / (1 + exp(i*h));
    }
    ret += 1.0 / (1 + exp(SE_trans_inv(a, b, x)));
    ret *= 1 + exp(-m * h);
  }

  if (-m < j && j < n) {
    ret = sinc(SE_trans_inv(a, b, x)/h  - j);
  }

  if (j == n) {
    for (int i = -m; i < n; i++) {
      ret -=
        sinc(SE_trans_inv(a, b, x)/h  - i)/(1 + exp(-i*h));
    }
    ret += 1.0 / (1 + exp(- SE_trans_inv(a, b, x)));
    ret *= 1 + exp(-n * h);
  }

  return ret;
}
