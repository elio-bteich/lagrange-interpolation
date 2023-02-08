#include <iostream>
#include <cmath>
#include <limits>

double *xvals(double a, double b, uint64_t n);
double *yvals(double (*f)(double), double *tab_x, uint64_t n);
double base_lagrange(double *tab_x, int n, int i, double x);
double approx_lagrange(double *tab_x, double *tab_y, uint64_t n, double x);