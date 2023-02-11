#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstdint>
#include <stdint.h>
#include <math.h>

//#include "matrix.hpp"
#include "util.hpp"
#include "lagrange.hpp"

#define BOUND_A 0.0
#define BOUND_B 2.0

using namespace std;

/**
 *
 * @param x le point pour lequel on veut évaluer la fonction f1
 *
 * @returns l'image de x par la fonction f1
 *
 * fonction qui retourne x/sqrt(x)
 *
 */
double f1(double x)
{
    return x / sqrt(x);
}

int main(int argc, char** argv){

    const uint64_t INTERPOLATION_X_NB = 10; // nombre de points d'interpolation
    const uint64_t ERROR_X_NB = 1000000; // nombre de points pour lesquels on veut tester l'erreur


    double *tab_x = xvals(BOUND_A, BOUND_B, INTERPOLATION_X_NB-1);

    double *tab_y = yvals(&f1, tab_x, INTERPOLATION_X_NB);

    std::cout << "Lagrange de x/sqrt(x) en x=0.55 est " << approx_lagrange(tab_x, tab_y, INTERPOLATION_X_NB, 0.55) << std::endl;

    double *x_errors = new double[ERROR_X_NB];

    double distAB = fabs(BOUND_B - BOUND_A);    

    for(int i = 0; i < ERROR_X_NB; i++){
        x_errors[i] = BOUND_A + i*distAB/ERROR_X_NB;
    }
   
    double* errorRel = (double*)calloc(ERROR_X_NB, sizeof(double));

    estimateRelError(errorRel, tab_x, tab_y, INTERPOLATION_X_NB, &f1, BOUND_A, BOUND_B, ERROR_X_NB);

    double maxRelError = getMax(errorRel, ERROR_X_NB);
    cout << " max relative error : " << maxRelError << endl;

    plot(x_errors, errorRel, ERROR_X_NB, "Relative approximation error for f1(x) with Lagrange", "testPlotFuncRelError");

    double* errorAbs = (double*)calloc(ERROR_X_NB, sizeof(double));
    estimateAbsError(errorAbs, tab_x, tab_y, INTERPOLATION_X_NB, &f1, BOUND_A, BOUND_B, ERROR_X_NB);
    double maxAbsError = getMax(errorAbs, ERROR_X_NB);
    cout << " max absolute error : " << maxAbsError << endl;
    
    plot(x_errors, errorAbs, ERROR_X_NB, "Absolute approximation error for f1(x) with Lagrange", "testPlotFuncAbsError");
      
    free(tab_x);    //Style C pour désallocation, à la place de delete[] en C++
    free(tab_y);
    free(errorRel);
    free(errorAbs);
    return 0;
}