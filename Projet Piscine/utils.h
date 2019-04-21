#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <iostream>
#include <limits>
#include <cmath>
#include <windows.h>

#define BLACK			0
#define BLUE			1
#define GREEN			2
#define CYAN			3
#define RED				4
#define MAGENTA			5
#define BROWN			6
#define LIGHT_GRAY		7
#define DARK_GRAY		8
#define LIGHT_BLUE		9
#define LIGHT_GREEN		10
#define LIGHT_CYAN		11
#define LIGHT_RED		12
#define LIGHT_MAGENTA	13
#define YELLOW			14
#define WHITE			15

#include "graph.h"
#include "population.h"

struct FileInfo
{
    std::string name;
    std::vector<std::string> weights;
};

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

/// \fn void videCin()
/// \brief Vide le tampon de saisie clavier. Fonction r�alis�e par un professeur de l'ECE.
void videCin();

void setConsoleColor(int text_color, int background_color = BLACK); /// https://openclassrooms.com/forum/sujet/tuto-couleur-console-windows
void menu();
void clearScreen();

std::vector<FileInfo> findGraphFiles();

#endif // UTILS_H_INCLUDED
