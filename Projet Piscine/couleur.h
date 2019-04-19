#ifndef COULEUR_H_INCLUDED
#define COULEUR_H_INCLUDED

/// \file
/// \brief
/// \author

#include <string>
#include <cstdint>

class Color
{
    public :
        Color(int red, int green, int blue);
        Color();

        operator std::string() const;

    private :
        int m_red, m_green, m_blue;     ///< composantes rouge verte et bleue de la couleur
};

#endif // COULEUR_H_INCLUDED
