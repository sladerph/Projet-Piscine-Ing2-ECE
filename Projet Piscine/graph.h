#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "connection.h"

#include <string>
#include <iostream>
#include <fstream>

class Graph
{
    public:
        Graph();
        ~Graph();

        bool create(std::string topology, std::string costs);

        Node* getNode(int index);
        Connection* getConnection(int index);

    private:
        std::vector<Node*> m_nodes;
        std::vector<Connection*> m_connections;

        int m_ordre;

};

#endif // GRAPH_H
