/// \file connection.h
/// \brief contient la classe connection, qui représente une arête
/// \author Pierre Herduin

#include "connection.h"

Connection::Connection(int index, Node* a, Node* b)
{
    m_index  = index;
    m_node_a = a;
    m_node_b = b;
}

Connection::~Connection()
{
    //dtor
}
