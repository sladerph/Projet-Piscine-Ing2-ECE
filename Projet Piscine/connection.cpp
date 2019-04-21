/// \file connection.h
/// \brief contient la classe connection, qui repr�sente une ar�te
/// \author Pierre Herduin

#include "connection.h"

Connection::Connection(int index, Node* a, Node* b)
{
    m_index  = index;
    m_node_a = a;
    m_node_b = b;
}

Connection::Connection(int index, Node* a, Node* b,std::vector<float> weights)
            :m_index{index},m_node_a{a},m_node_b{b},m_weights{weights}
{

}


Connection::~Connection()
{
    //dtor
}
