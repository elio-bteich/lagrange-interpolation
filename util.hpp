#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <iostream>

void estimateRelError(double* error, double *xvals, double *yvals, uint64_t n, double func (double), double a, double b, uint64_t nSamples);
void estimateAbsError(double* error, double *xvals, double *yvals, uint64_t n, double func (double), double a, double b, uint64_t nSamples);
double  getMax              (const double* array, uint64_t n);
void    plot                (double *xvals, double *yvals, uint64_t N, char* title, char* filename);
