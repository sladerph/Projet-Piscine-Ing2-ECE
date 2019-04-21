#include "utils.h"

float mapLine(float val, float xa, float ya, float xb, float yb)
{
    ///On va chercher les paramètres de la fonction affine décrivant la droite passant par a et b
    float m = (yb - ya) / (xb - xa);        ///On calcule le coefficient directeur
    float p = ya - m * xa;          ///On calcule l'ordonnée à l'origine

    return m * val + p; ///on retourne l'ordonnée du point d'abscisse val
}

float dist(float xa, float ya, float xb, float yb)
{
    return std::sqrt(std::pow(xb - xa, 2) + std::pow(yb - ya, 2));      ///distance euclidienne
}

float factorial(float nb)
{
    if (nb < 0) return 0;
    if( nb ==0 ) return 1;

    float r = nb;

    for (int i = nb - 1; i > 1; i--)
        r *= i;
    return r;
}

float countCombinations(float k, float n)
{
    return factorial(n) / (factorial(k) * factorial(n - k));
}
