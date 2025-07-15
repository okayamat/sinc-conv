#include <iostream>
#include <Eigen/Core>
#include <unsupported/Eigen/MatrixFunctions>
#include "SE_trans.h"
#include "sigma.h"
#define eulergamma 0.57721566490153286060651209008240

using Eigen::MatrixXd;
using Eigen::VectorXd;

double g(double x)
{
  return sqrt(x);
}

double p(double x)
{
  return 2*x*sqrt(x)*(-8 + 3*log(4*x))/9.0;
}

int main()
{
  double a = 0;
  double b = 2;
  double d = 3.14; // M_PI - eps
  double x, y, err, maxerr;
  int DIV = 200;

  for (int N = 2; N <= 80; N += 2) {
    int n = 2*N + 1;
    double h = sqrt(M_PI * d / N);

    MatrixXd A_n(n,n);
    MatrixXd F_n = MatrixXd::Identity(n, n);

    VectorXd g_n(n);
    VectorXd p_n(n);

    // A_n = h * I^(-1) * diag[psi'(jh)]
    for (int j = -N; j <= N; j++) {
      for (int i = -N; i <= N; i++) {
        A_n(i+N, j+N)  = 0.5 + (double)sigma[i - j];
        A_n(i+N, j+N) *= h * SE_trans_div(a, b, j*h);
      }
    }

    // g_n = (g(psi(-Nh)), ... , g(psi(Nh)))
    for (int j = -N; j <= N; j++) {
      g_n(j+N) = g(SE_trans(a, b, j*h));
    }

    F_n = A_n.log() - (eulergamma*F_n); // log(A_n) - gamma I_n
    p_n = A_n * F_n * g_n; // A_n (log(A_n) - gamma I_n) g_n

    maxerr = 0;
    for (int k = 1; k < DIV; k++) {
      x = (double)k * (b - a) / (double)DIV;
      y = 0;
      for (int j = -N; j <= N; j++) {
        y += p_n(j+N) * SE_basis_func(j, N, N, a, b, x, h);
      }
      err = abs(p(x) - y);
      maxerr = fmax(err, maxerr);
    }

    std::cout << n << "\t" << maxerr << std::endl;

  }

  return EXIT_SUCCESS;
}
