#include <iostream>
#include <Eigen/Core>
#include "DE_trans.h"
#include "sigma.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

double g(double x)
{
  return sqrt(x)/(1 + x*x);
}

double p(double x)
{
  double sqrt2x = M_SQRT2 * sqrt(x);
  double val = (x + 1) * (atan(sqrt2x + 1) + atan(sqrt2x - 1)) * M_SQRT1_2;

  val += (x - 1) * log((x - sqrt2x + 1)/(x + sqrt2x + 1)) * 0.5 * M_SQRT1_2;

  return val - M_SQRT2 * sqrt2x;
}

int main()
{
  double a = 0;
  double b = 2;
  double d = 0.833; // Im[asinh(-log(sqrt(2))/pi +(3/4)*pi*I)]
  double x, y, err, maxerr;
  int DIV = 200;

  for (int N = 2; N <= 80; N += 2) {
    int n = 2*N + 1;
    double h = log(2 * d * N) / N;

    MatrixXd A_n(n,n);

    VectorXd g_n(n);
    VectorXd p_n(n);

    // A_n = h * I^(-1) * diag[phi'(jh)]
    for (int j = -N; j <= N; j++) {
      for (int i = -N; i <= N; i++) {
        A_n(i+N, j+N)  = 0.5 + (double)sigma[i - j];
        A_n(i+N, j+N) *= h * DE_trans_div(a, b, j*h);
      }
    }

    // g_n = (g(phi(-Nh)), ... , g(phi(Nh)))
    for (int j = -N; j <= N; j++) {
      g_n(j+N) = g(DE_trans(a, b, j*h));
    }

    p_n = A_n * A_n * g_n; // (A_n)^2 g_n

    maxerr = 0;
    for (int k = 1; k < DIV; k++) {
      x = (double)k * (b - a) / (double)DIV;
      y = 0;
      for (int j = -N; j <= N; j++) {
        y += p_n(j+N) * DE_basis_func(j, N, N, a, b, x, h);
      }
      err = abs(p(x) - y);
      maxerr = fmax(err, maxerr);
    }

    std::cout << n << "\t" << maxerr << std::endl;

  }

  return EXIT_SUCCESS;
}
