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
#include <bits/stdc++.h>    ///ajout�e pour le sort(vecteur.begin(),vecteur.end());
///https://www.geeksforgeeks.org/sorting-vector-of-pairs-in-c-set-1-sort-by-first-and-second/

#define XOFFSET 50
#define YOFFSET 50

class Graph
{
    public:
        Graph();
        ~Graph();

        void show(std::string filename = "output.svg", std::vector<bool>* path = nullptr);
        void showPrim(std::string filename = "output.svg", std::vector<bool>* path = nullptr, bool onTopOfGraph = true);

        bool create(std::string topology, std::string costs);

        Node* getNode(int index);       //retourne le sommet d'indice [index]
        Connection* getConnection(int index);       //retourne l'ar�te d'indice [index]
        std::vector<Connection*> getConnections() const {return m_connections;};       //retourne la liste des ar�tes du graphe
        int getOrdre() const {return m_ordre;}; //retourne le nombre de sommets du graphe

        std::vector<bool> getPrim(int weight, float* totalWeight);
        //retourne un vecteur de bool�ens d�crivant le graphe couvrant de poids minimum. Weight permet de choisir entre les diff�rents poids des ar�tes
        //totalWeight sera modifi� � l'int�rieur du programme, et vaudra la somme des poids des ar�tes

        float getDijkstra(int weight, std::vector<bool> activeConnections);
        //retourne la somme de tous les plus courts chemins, en prenant en compte le poids d'indice [weight] de chaque ar�te
        //le vecteur de bool permet de dire si les connexions sont actives ou non

        bool testCycle(std::vector<bool> connections);      //renvoie true s'il y a un cycle, renvoie false sinon;
        bool connectivityTest(std::vector<bool>connections);        //renvoie true si le graphe est connexe, renvoie false sinon

        ///fonction qui �num�re toutes les solutions existantes :
        std::vector<std::vector<bool>> enumeration ();
        ///fonction qui selectionne les solutions admissibles parmis les solutions existantes :
        std::vector<std ::vector<bool>> filtrage ();
        ///fonction qui trie les solutions domin�es et non domin�es selon les 2 objectifs et les affiche :
        void evaluation ();

    private:
        std::vector<Node*> m_nodes;     //liste des sommets du graphe
        std::vector<Connection*> m_connections;     //liste des ar�tes du graphe

        int m_ordre;    //nombre de sommet du graphe
        double m_taille;

        void showNodes(Svgfile* svg) const;
        void showConnections(Svgfile* svg, std::vector<bool>* path = nullptr) const;
        void showBounds(Svgfile* svg);
        Svgfile* createSvgfile(std::string filename = "output.svg");

        std::vector<std::pair<float,int>> getNeighbours(Node* origin,int weight,std::vector<bool> activeConnections);
        //utilis� pour dijkstra : renvoie la liste des pairs <poids,id> des sommets voisins du sommet "origin" (l'activit� ou non des connections
        //est prise en compte pour d�terminer les voisins

        float weightsSum(std::vector<bool> connections, int weight);

};

std::vector<Connection*> sortConnections(std::vector<Connection*> connections, int weight);
//trie les connexions pass�es en param�tre en fonctions de leur poids d'indice [weight], dans l'ordre croissant

std::vector<Connection*> sortConnectionsByIndex(std::vector<Connection*> connections);
//trie les connexions du vecteur en param�tre en fonction de leur id, dans l'ordre croissant

std::vector<std::pair<float,int>> sortNodes(std::vector<std::pair<float,int>> Nodes);
//trie les paires <poids,id>, qui repr�sentent des sommets, en fonction du param�tre poids et dans l'ordre croissant

///additionneur 1 bit :
bool add_1bit(bool& r_sortie ,bool r_entree,bool a, bool b);

#endif // GRAPH_H
