/// \file node.cpp
/// \brief regroupe la classe Node et les différentes fonction agissant sur les sommets du graphe
/// \author Pierre Herduin, Simon jolly

#include "node.h"
#include <iostream>

Node::Node(int index, float x, float y)
{
    m_index = index;
    m_x     = x    ;
    m_y     = y    ;
}

Node::~Node()
{
    //dtor
}
