#include "lagrange.hpp"
#include "util.hpp"

/**
 * 
 * Role: décompose un intervalle [A,B] en n sous-intervale
 * 
 * Préconditions: a <= b et n >= 0
 *
 * @param a borne gauche de l'intervalle
 * @param b borne droite de l'intervalle
 * @param n nombre de sous-intervalle
 *
 * @returns tableau des n+1 x equidistants entre a et b
 *
 * NB: si un point d'interpollation est égale à 0 on le décale un peu
 * vers la droite pour éviter les divisions par 0
 *
 */
double *xvals(double a, double b, uint64_t n)
{
    double *tab_x = new double[n + 1];

    for (uint64_t k = 0; k < n + 1; k++)
    {
        tab_x[k] = (a + k * (b - a)) / n;

        if (tab_x[k] == 0.0)
        {
            tab_x[k] = std::numeric_limits<double>::min();
        }
    }

    return tab_x;
}

/**
 * 
 * Role: construit un tableau d'images des points de tab_x par la fonction f
 * 
 * Préconditions: n >= 0
 * 
 * @param f pointeur vers une fonction qui prend en paramètre un double et retourne un double
 * @param tab_x tableau des points d'interpolations
 * @param n taille du tableau des points d'interpolations
 *
 * @returns tableau des images des points d'interpolations par la fonction f
 *
 */
double *yvals(double (*f)(double), double *tab_x, uint64_t n)
{
    double *tab_y = new double[n];

    for (uint64_t k = 0; k < n; k++)
    {
        tab_y[k] = (*f)(tab_x[k]);
    }

    return tab_y;
}

/**
 * 
 * Role: Evalue le polynome de base de lagrange d'indice i au point x
 * 
 * Préconditions: 0 <= i < n 
 *
 * @param tab_x tableau des x des points d'interpolations
 * @param n taille du tableau tab_x
 * @param i indice du polynome de base
 * @param x point pour lequel on veut évaluer le polynome de base
 *
 * @returns l'image du polynome de base de lagrange d'indice i au point x
 *
 */
double base_lagrange(double *tab_x, int n, int i, double x)
{
    double res = 1.0;

    for (int j = 0; j < n; j++)
    {
        if (j != i)
        {
            res *= (x - tab_x[j]) / (tab_x[i] - tab_x[j]);
        }
    }

    return res;
}

/**
 * 
 * Role: Evalue le polynome de lagrange au point x
 * 
 * Préconditions: n > 0, tab_x et tab_y ont la même taille
 *
 * @param tab_x tableau des x des points d'interpolations
 * @param tab_y tableau des images des points d'interpolations
 * @param n taille du tableau tab_x et tab_y
 * @param x point pour lequel on veur évaluer le polynome de lagrange
 *
 * @returns l'image du polynome de lagrange au point x
 *
 */
double approx_lagrange(double *tab_x, double *tab_y, uint64_t n, double x)
{
    double res = 0.0;

    for (int i = 0; i < n; i++)
    {
        res += tab_y[i] * base_lagrange(tab_x, n, i, x);
    }

    return res;
}
