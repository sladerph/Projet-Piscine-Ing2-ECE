#include "couleur.h"
#include "svgfile.h"
#include <iostream>

Color::Color(int red, int green, int blue)
    : m_red{red}, m_green{green}, m_blue{blue}
{ }


Color::Color()
    : Color(0, 0, 0) // D�l�gation de constructeur
{ }

Color::operator std::string() const
{
    return Svgfile::makeRGB(m_red, m_green, m_blue);
}
