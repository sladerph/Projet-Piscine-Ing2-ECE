#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <cmath>

/// \fn float mapLine(float val, float xa, float ya, float xb, float yb)
/// \brief calcule l'ordonn�e d'un point d'abscisse pass�e en param�tre
/// \param val : point dont on cherche l'ordonn�e
/// \param xa : abscisse du point a
/// \param ya : ordonn�e du point a
/// \param xb : abscisse du point b
/// \param yb : ordonn�e du point b
/// \return ordonn�e du point d'abscisse val
float mapLine(float val, float xa, float ya, float xb, float yb);

/// \fn float dist(float xa, float ya, float xb, float yb)
/// \brief calcule la distance euclidienne entre deux points dans un rep�re orthonorm�
/// \param xa : abscisse du point a
/// \param ya : ordonn�e du point a
/// \param xb : abscisse du point b
/// \param yb : ordonn�e du point b
/// \return distance euclidienne entre les points a et b
float dist(float xa, float ya, float xb, float yb);

/// \fn float factorial(float nb)
/// \brief calcule la factorielle du nombre pass� en param�tre
/// \param nb : nombre dont on cherche la factorielle
/// \return factorielle d nombre pass�e en param�tre
float factorial(float nb);

/// \fn float countCombinations(float k, float n)
/// \brief calcule le nombre d'agencement de k �l�ments parmis n places
/// \param k : nombre d'�l�ments � agencer
/// \param n : nombre de places disponibles
/// \return nombre d'agencement de k �l�ments parmis n places
float countCombinations(float k, float n);

#endif // UTILS_H_INCLUDED
