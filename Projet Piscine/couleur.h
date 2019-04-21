#ifndef COULEUR_H_INCLUDED
#define COULEUR_H_INCLUDED

/// \file couleur.h
/// \brief contient la classe couleur
/// \author Pierre Herduin

#include <string>
#include <cstdint>

/// \class Color
/// \brief Représente une couleur. On l'utilisera pour le dessin sur fichier svg
class Color
{
    public :
        /// \fn Color(int red, int green, int blue)
        /// \brief Constructeur de la classe Color
        /// \param red : composante rouge initiale de la couleur
        /// \param green : composante verte initiale de la couleur
        /// \param blue : composante bleue initiale de la couleur
        Color(int red, int green, int blue);

        /// \fn Color()
        /// \brief Constructeur de la classe Couleur
        Color();

        /// surcharge de l'opérateur std::string()
        operator std::string() const;

    private :
        int m_red, m_green, m_blue;     ///< composantes rouge verte et bleue de la couleur
};

#endif // COULEUR_H_INCLUDED
