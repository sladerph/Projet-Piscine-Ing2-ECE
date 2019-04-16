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

        void show(std::string filename = "output.svg", std::vector<bool>* path = nullptr);
        void showPrim(std::string filename = "output.svg", std::vector<bool>* path = nullptr);

        bool create(std::string topology, std::string costs);

        Node* getNode(int index);
        Connection* getConnection(int index);

        std::vector<bool> getPrim(int weight, float* totalWeight);
        float getDijkstra(int weight);

    private:
        std::vector<Node*> m_nodes;
        std::vector<Connection*> m_connections;

        int m_ordre;

        void showNodes(Svgfile* svg) const;
        void showConnections(Svgfile* svg, std::vector<bool>* path = nullptr) const;
        void showBounds(Svgfile* svg);
        Svgfile* createSvgfile(std::string filename = "output.svg");

        std::vector<std::pair<float,int>> getNeighbours(Node* origin,int weight);

};

std::vector<Connection*> sortConnections(std::vector<Connection*> connections, int weight);
std::vector<std::pair<float,int>> sortNodes(std::vector<std::pair<float,int>> Nodes, int weight);

#endif // GRAPH_H
