#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "connection.h"
#include "svgfile.h"

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_set>

#define XOFFSET 50
#define YOFFSET 50

class Graph
{
    public:
        Graph();
        ~Graph();

        void show(std::string filename = "output.svg") const;

        bool create(std::string topology, std::string costs);

        Node* getNode(int index);
        Connection* getConnection(int index);

        std::vector<bool> getPrim(int weight, float* totalWeight);

    private:
        std::vector<Node*> m_nodes;
        std::vector<Connection*> m_connections;

        int m_ordre;

};

std::vector<Connection*> sortConnections(std::vector<Connection*> connections, int weight);


#endif // GRAPH_H
