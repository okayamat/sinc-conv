#include <iostream>
#include <Eigen/Core>
#include "DE_trans.h"
#include "sigma.h"
int fresnl(double xxa, double *ssa, double *cca );

using Eigen::MatrixXd;
using Eigen::VectorXd;

double g(double x)
{
  return sqrt(x);
}

double p(double x)
{
  double t = sqrt(x * M_2_PI);
  double s, c;

  fresnl(t, &s, &c);

  double val = sqrt(x) * (s*s + c*c) + sqrt(M_2_PI) * (s*cos(x) - c*sin(x));

  return M_PI * val;
}

int main()
{
  double a = 0;
  double b = 2;
  double d = 1.57; // M_PI_2 - eps
  double x, y, err, maxerr;
  int DIV = 200;

  for (int N = 2; N <= 80; N += 2) {
    int n = 2*N + 1;
    double h = log(2 * d * N) / N;

    MatrixXd A_n(n,n);
    MatrixXd F_n(n,n);
    MatrixXd G_n(n,n);
    MatrixXd I_n = MatrixXd::Identity(n,n);

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

//  p_n = A_n * A_n.matrixFunction(atanfn);
    F_n = A_n * A_n;
    G_n = -(1.0/19.0)*F_n + (1.0/17.0)*I_n;
    G_n =       G_n  *F_n - (1.0/15.0)*I_n;
    G_n =       G_n  *F_n + (1.0/13.0)*I_n;
    G_n =       G_n  *F_n - (1.0/11.0)*I_n;
    G_n =       G_n  *F_n + (1.0/ 9.0)*I_n;
    G_n =       G_n  *F_n - (1.0/ 7.0)*I_n;
    G_n =       G_n  *F_n + (1.0/ 5.0)*I_n;
    G_n =       G_n  *F_n - (1.0/ 3.0)*I_n;
    G_n =       G_n  *F_n +            I_n;
    p_n = A_n * G_n * g_n;

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
