#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <iostream>
#include <limits>
#include <cmath>
#include <windows.h>


///On attribue une valeur à chaque couleur, que l'on utilisera pour la coloration du texte en console
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


/// \struct FileInfo
/// \brief Rassemble les informations relatives aux fichiers contenant les informations des graphes
struct FileInfo
{
    std::string name;       /// <nom du fichier contenant les sommets et les arêtes
    std::vector<std::string> weights;       ///liste des fichiers décrivant les différents agencements de poids relatifs aux fichier contenant les sommets et arêtes
};

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

/// \fn void videCin()
/// \brief Vide le tampon de saisie clavier. Fonction réalisée par un professeur de l'ECE.
void videCin();

/// \fn
/// \brief Permet de changer la couleur de la police et d'arrière plan en console vers la couleur passée en paramètre
/// https://openclassrooms.com/forum/sujet/tuto-couleur-console-windows
/// \param text_color : couleur de la police qu'on souhaite avoir
/// \param background_color : couleur de l'arrière plan de la console que l'on souhaite avoir (noir par défaut)
void setConsoleColor(int text_color, int background_color = BLACK);

/// \fn void menu()
/// \brief Menu d'accueil du programme, qui permet d'utiliser les différentes fonctionnalité implémentées
void menu();

/// \fn void clearScreen()
/// \brief Efface le contenu de la console
void clearScreen();

/// \fn std::vector<FileInfo> findGraphFiles()
/// \brief Permet de récupérer les différents fichiers depuis lesquels on va charger les graphes
/// \return la liste des fichiers récupérés, organisés en structures FileInfo
std::vector<FileInfo> findGraphFiles();

#endif // UTILS_H_INCLUDED
