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
