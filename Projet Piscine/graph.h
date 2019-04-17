#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "connection.h"
#include "svgfile.h"

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <queue>
#include <bits/stdc++.h>    ///ajoutée pour le sort(vecteur.begin(),vecteur.end());
///https://www.geeksforgeeks.org/sorting-vector-of-pairs-in-c-set-1-sort-by-first-and-second/

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

        bool testCycle(std::vector<bool> connections);
        bool connectivityTest(std::vector<bool>connections);

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
std::vector<std::pair<float,int>> sortNodes(std::vector<std::pair<float,int>> Nodes);


#endif // GRAPH_H
