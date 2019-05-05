/// \file node.cpp
/// \brief regroupe la classe Node et les diff�rentes fonction agissant sur les sommets du graphe
/// \author Pierre Herduin, Simon jolly

#include "node.h"
#include <iostream>

Node::Node(int index, float x, float y) /// Constructeur.
{
    m_index = index;
    m_x     = x    ;
    m_y     = y    ;
}

Node::~Node() /// Destructeur.
{
    //dtor
}
