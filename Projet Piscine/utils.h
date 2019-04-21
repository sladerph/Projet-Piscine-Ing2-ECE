#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <cmath>

/// \fn float mapLine(float val, float xa, float ya, float xb, float yb)
/// \brief calcule l'ordonnée d'un point d'abscisse passée en paramètre
/// \param val : point dont on cherche l'ordonnée
/// \param xa : abscisse du point a
/// \param ya : ordonnée du point a
/// \param xb : abscisse du point b
/// \param yb : ordonnée du point b
/// \return ordonnée du point d'abscisse val
float mapLine(float val, float xa, float ya, float xb, float yb);

/// \fn float dist(float xa, float ya, float xb, float yb)
/// \brief calcule la distance euclidienne entre deux points dans un repère orthonormé
/// \param xa : abscisse du point a
/// \param ya : ordonnée du point a
/// \param xb : abscisse du point b
/// \param yb : ordonnée du point b
/// \return distance euclidienne entre les points a et b
float dist(float xa, float ya, float xb, float yb);

/// \fn float factorial(float nb)
/// \brief calcule la factorielle du nombre passé en paramètre
/// \param nb : nombre dont on cherche la factorielle
/// \return factorielle d nombre passée en paramètre
float factorial(float nb);

/// \fn float countCombinations(float k, float n)
/// \brief calcule le nombre d'agencement de k éléments parmis n places
/// \param k : nombre d'éléments à agencer
/// \param n : nombre de places disponibles
/// \return nombre d'agencement de k éléments parmis n places
float countCombinations(float k, float n);

#endif // UTILS_H_INCLUDED
