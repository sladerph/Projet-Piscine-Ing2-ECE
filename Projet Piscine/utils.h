#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

/// \file utils.h
/// \brief diverses fonctions utilitaires
/// \author Pierre Herduin

#include <iostream>
#include <limits>
#include <cmath>
#include <windows.h>


/// Liste des couleurs disponibles pour la coloration du texte en console
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
    std::string name;       /// <nom du fichier contenant les sommets et les ar�tes
    std::vector<std::string> weights;       ///liste des fichiers d�crivant les diff�rents agencements de poids relatifs aux fichier contenant les sommets et ar�tes
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

/// \fn
/// \brief Permet de changer la couleur de la police et d'arri�re plan en console vers la couleur pass�e en param�tre
/// https://openclassrooms.com/forum/sujet/tuto-couleur-console-windows
/// \param text_color : couleur de la police qu'on souhaite avoir
/// \param background_color : couleur de l'arri�re plan de la console que l'on souhaite avoir (noir par d�faut)
void setConsoleColor(int text_color, int background_color = BLACK);

/// \fn void menu()
/// \brief Menu d'accueil du programme, qui permet d'utiliser les diff�rentes fonctionnalit� impl�ment�es
void menu();

/// \fn void clearScreen()
/// \brief Efface le contenu de la console
void clearScreen();

/// \fn std::vector<FileInfo> findGraphFiles()
/// \brief Permet de r�cup�rer les diff�rents fichiers depuis lesquels on va charger les graphes
/// \return la liste des fichiers r�cup�r�s, organis�s en structures FileInfo
std::vector<FileInfo> findGraphFiles();

#endif // UTILS_H_INCLUDED
