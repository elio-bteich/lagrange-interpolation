#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstdint>
#include <stdint.h>
#include <math.h>
#include <string>
#include <iomanip>

#include "util.hpp"
#include "lagrange.hpp"

#define BOUND_A 0.0
#define BOUND_B 2.0

using namespace std;

/**
 *
 * @param x le point pour lequel on veut évaluer la fonction func
 *
 * @returns l'image de x par la fonction func
 *
 * fonction qui retourne x/sqrt(x)
 *
 */
double func(double x)
{
    return x / sqrt(x);
}

int main(int argc, char **argv)
{

    const uint64_t INTERPOLATION_X_NB = 10; // nombre de points d'interpolation
    const uint64_t X_NB = 10000;          // nombre de points d'echantillonage de la courbe

    double *tab_x = xvals(BOUND_A, BOUND_B, INTERPOLATION_X_NB - 1);

    double *tab_y = yvals(&func, tab_x, INTERPOLATION_X_NB);

    cout << setprecision(16) << "Lagrange de x/sqrt(x) en x=0.55 est " << approx_lagrange(tab_x, tab_y, INTERPOLATION_X_NB, 0.55) << endl;

    cout << "f(0.55) = " << func(0.55) << endl;

    double *x_echant = new double[X_NB];

    double distAB = fabs(BOUND_B - BOUND_A);

    for (int i = 0; i < X_NB; i++)
    {
        x_echant[i] = BOUND_A + i * distAB / X_NB;
    }

    //double *y_echant = yvals(&func, x_echant, X_NB);
    double *y_echant = new double[X_NB];
    for (int i = 0; i < X_NB; i++) {
        y_echant[i] = approx_lagrange(tab_x, tab_y, INTERPOLATION_X_NB, x_echant[i]);
    }

    double *y_func = yvals(&func, x_echant, X_NB);

    plot(x_echant, y_func, X_NB, "courbe de x/sqrt(x)", "plotFunc");

    string string_description = "approx de Lagrange pour x/sqrt(x) avec n=" + to_string(INTERPOLATION_X_NB);

    const char* char_description = string_description.c_str();


    plot(x_echant, y_echant, X_NB, const_cast<char*>(char_description), "plotInterpolation");

    double *errorRel = (double *)calloc(X_NB, sizeof(double));

    estimateRelError(errorRel, tab_x, tab_y, INTERPOLATION_X_NB, &func, BOUND_A, BOUND_B, X_NB);

    double maxRelError = getMax(errorRel, X_NB);
    cout << " max relative error : " << maxRelError << endl;

    string_description = "Erreur relative de l'approx de Lagrange pour x/sqrt(x) avec n=" + to_string(INTERPOLATION_X_NB);

    char_description = string_description.c_str();

    plot(x_echant, errorRel, X_NB, const_cast<char*>(char_description), "plotRelError");

    double *errorAbs = (double *)calloc(X_NB, sizeof(double));
    estimateAbsError(errorAbs, tab_x, tab_y, INTERPOLATION_X_NB, &func, BOUND_A, BOUND_B, X_NB);
    double maxAbsError = getMax(errorAbs, X_NB);
    cout << " max absolute error : " << maxAbsError << endl;

    string_description = "Erreur absolue de l'approx de Lagrange pour x/sqrt(x) avec n=" + to_string(INTERPOLATION_X_NB);

    char_description = string_description.c_str();

    plot(x_echant, errorAbs, X_NB, const_cast<char*>(char_description), "plotAbsError");

    free(tab_x); // Style C pour désallocation, à la place de delete[] en C++
    free(tab_y);
    free(errorRel);
    free(errorAbs);
    return 0;
}