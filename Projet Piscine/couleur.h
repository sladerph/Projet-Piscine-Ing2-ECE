#ifndef COULEUR_H_INCLUDED
#define COULEUR_H_INCLUDED

#include <string>
#include <cstdint>

class Color
{
    public :
        Color(int red, int green, int blue);
        Color();

        operator std::string() const;

    private :
        int m_red, m_green, m_blue;
};

#endif // COULEUR_H_INCLUDED
