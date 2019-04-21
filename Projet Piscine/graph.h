#ifndef GRAPH_H
#define GRAPH_H

/// \file graph.h
/// \brief regroupe la classe graph les différentes fonction agissant sur le graphe et permettant de l'afficher ainsi
///que les fonctions accessoires qu'elles utilisent
/// \author Pierre Herduin, Mélodie Damas, Simon jolly

#include "node.h"
#include "connection.h"
#include "svgfile.h"
#include "utils.h"

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <queue>
#include <bits/stdc++.h>    /// \brief ajoutée pour le sort(vecteur.begin(),vecteur.end());
                            ///https://www.geeksforgeeks.org/sorting-vector-of-pairs-in-c-set-1-sort-by-first-and-second/

#define XOFFSET 50  /// \def XOFFSET 50
#define YOFFSET 50  /// \def YOFFSET 50


/// \struct Solution
/// \brief modèle de d'agencement du graphe constituant un éventuel optimum de pareto
struct Solution
{
    std::vector<bool> vec;  ///< vecteur de booléens de même taille que la liste d'arêtes : le booléen d'indice n décrit si l'arête d'indice n est active ou non
    float cost_a = 0;   ///< cout A de la solution
    float cost_b = 0;   ///<cout B de la solution
    bool  dominated = false;    ///<statut dominé ou non de la solution
};

/// \class Graph
/// \brief Classe représentant un graphe
/// La classe gère le traitement et l'affichage d'un graphe
class Graph
{
    public:

        /// \fn Graph()
        /// \brief Constructeur
        /// Constructeur de la classe Graph
        Graph();

        /// \fn ~Graph()
        /// \brief destructeur
        /// Destructeur de la classe Graph
        ~Graph();

        /// \fn void show(std::string filename = "output.svg", std::vector<bool>* path = nullptr)
        /// \brief permet de dessiner un graphe sur un fichier svg
        /// \param filename : nom du fichier svg sur lequel on veut dessiner
        /// \param path : pointeur sur vecteur de booléens de même taille que la liste d'arêtes : le booléen d'indice n décrit si l'arête d'indice n est active ou non
        void show(std::string filename = "output.svg", std::vector<bool>* path = nullptr);

        /// \fn void showPrim(std::string filename = "output.svg", std::vector<bool>* path = nullptr, bool onTopOfGraph = true)
        /// \brief permet de dessiner l'arbre couvrant de poids minimal sur un fichier svg
        /// \param filename : nom du fichier sur lequel on veut dessiner
        /// \param path : pointeur sur vecteur de booléens de même taille que la liste d'arêtes : le booléen d'indice n décrit si l'arête d'indice n est active ou non
        /// \param onTopOfGraph : booléen qui permet de savoir si on va dessiner l'arbre couvrant sur le graphe ou à coté
        void showPrim(std::string filename = "output.svg", std::vector<bool>* path = nullptr, bool onTopOfGraph = true);

        /// \fn bool create(std::string topology, std::string costs)
        /// \brief permet de créer un graphe en le chargeant à partir de fichiers textes
        /// \param topology : nom du fichier texte d'où on chargera les sommets et les arêtes du graphe
        /// \param  costs: nom du fichier texte d'où on chargera les poids des arêtes du graphe
        /// \return retourne un booléen qui indique si le chargement s'est bien déroulé ou non
        bool create(std::string topology, std::string costs);

        /// \fn Node* getNode(int index)
        /// \brief getter qui permet de récupérer le sommet d'indice Index
        /// \param  Index : indice du sommet que l'on veut récupérer
        /// \return le Sommet d'indice Index
        Node* getNode(int index);

        /// \fn Connection* getConnection(int index)
        /// \brief getter qui permet de récupérer une arête du graphe en passant son indice en paramètre
        /// \param  Index : indice de l'arête que l'on veut récupérer
        /// \return l'arêtd 'indice index
        Connection* getConnection(int index);       //retourne l'arête d'indice [index]

        /// \fn std::vector<Connection*> getConnections() const
        /// \brief getter qui permet de récupérer la liste des arêtes du graphe
        /// \return la liste des arêtes du graphe
        std::vector<Connection*> getConnections() const {return m_connections;};       //retourne la liste des arêtes du graphe

        /// \fn int getOrdre() const
        /// \brief getter qui permet d'obtenir le nombre de sommmet du graphe
        /// \return le nombre de sommet du graphe
        int getOrdre() const {return m_ordre;}; //retourne le nombre de sommets du graphe

        /// \fn int getSize() const
        /// \brief getter qui permet d'obtenir le nombre d'arête du graphe
        /// \return le nombre d'arête du graphe
        int getSize () const {return m_taille;};

        /// \fn std::vector<bool> getPrim(int weight, float* totalWeight)
        /// \brief retourne un vecteur de booléens décrivant le graphe couvrant de poids minimum. Weight permet de choisir entre
        /// les différents poids des arêtes. totalWeight sera modifié à l'intérieur du programme, et vaudra la somme des poids des arêtes
        /// \param weight : Indice dans le vecteur de poids du poids par lequel on veut trier les arêtes
        /// \param totalWeight : somme des poids des arêtes, qui est passé par adresse pour être modifié à l'intérieur du programme
        /// \return vecteur de booléens de même taille que la liste d'arêtes : le booléen d'indice n décrit si l'arête d'indice n est active ou non
        std::vector<bool> getPrim(int weight, float* totalWeight);

        /// \fn float getDijkstra(int weight, std::vector<bool> activeConnections)
        /// \brief retourne la somme des plus courts chemins entre toutes les paires de sommets du graphe
        /// \param weight : indice du poids pour lequel on veut étudier le graphe
        /// \param activeConnections : vecteur de booléens de même taille que la liste d'arêtes : le booléen d'indice n décrit si l'arête d'indice n est active ou non
        /// \return la somme de splus courts chemins entre toutes les paires de sommets du graphe
        float getDijkstra(int weight, std::vector<bool> activeConnections);

        /// \fn bool testCycle(std::vector<bool> connections)
        /// \brief renvoie true s'il y a un cycle, renvoie false sinon;
        /// \param connections : vecteur de booléens de même taille que la liste d'arêtes : le booléen d'indice n décrit si l'arête d'indice n est active ou non
        /// \return retourne true si il y a un cycle, false sinon
        bool testCycle(std::vector<bool> connections);

        /// \fn bool connectivityTest(std::vector<bool>connections)
        /// \brief renvoie true si le graphe est connexe, renvoie false sinon
        /// \param connections : vecteur de booléens de même taille que la liste d'arêtes : le booléen d'indice n décrit si l'arête d'indice n est active ou non
        /// \return retourne true si le graphe est connexe, false sinon
        bool connectivityTest(std::vector<bool>connections);


        /// \fn std::vector<std::vector<bool>> enumeration ()
        /// \brief fonction qui énumère toutes les arrangements d'arêtes possibles
        /// \return retourne la liste de tous les arrangements, sous forme de vecteur de booléens de même taille que la liste d'arêtes : le booléen d'indice n décrit si l'arête d'indice n est active ou non
        std::vector<std::vector<bool>> enumeration ();

        /// \fn std::vector<std ::vector<bool>> filtrage ()
        /// \brief fonction qui selectionne les solutions admissibles parmis les solutions existantes
        /// \return retourne la liste de toutes les solutions admissibles, , sous forme de vecteur de booléens de même taille que la liste d'arêtes : le booléen d'indice n décrit si l'arête d'indice n est active ou non
        std::vector<std ::vector<bool>> filtrage ();

        /// \fn void evaluation ()
        /// \brief fonction qui trie les solutions dominées et non dominées selon les 2 objectifs et les affiche
        void evaluation ();

        /// \fn void secondEvaluation()
        /// \brief semblable à evaluation(), mais pour 2 objectifs de natures différentes
        void secondEvaluation();

        /// \fn std::vector<std ::vector<bool>> secondfiltrage ()
        /// \brief semblable à filtrage(), mais sans filtrer les solutions qui contiennent des cycles
        /// \return retourne la liste de toutes les solutions admissibles, , sous forme de vecteur de booléens de même taille que la liste d'arêtes : le booléen d'indice n décrit si l'arête d'indice n est active ou non
        std::vector<std ::vector<bool>> secondfiltrage ();

        /// \fn std::vector<std::vector<bool>> secondEnumeration ()
        /// \brief semblable à enumeration(), mais ne filtre pas les cycles
        /// \return retourne la liste de tous les arrangements, sous forme de vecteur de booléens de même taille que la liste d'arêtes : le booléen d'indice n décrit si l'arête d'indice n est active ou non
        std::vector<std::vector<bool>> secondEnumeration ();

        /// \fn void bruteForcePareto()
        /// \brief fonction qui trie les solutions dominées et non dominées selon les 2 objectifs et les affiche
        void bruteForcePareto();

        void bruteForceParetoConsideringCycles();

    private:
        std::vector<Node*> m_nodes;     ///< liste des sommets du graphe
        std::vector<Connection*> m_connections;     ///< liste des arêtes du graphe

        int m_ordre;    ///< nombre de sommet du graphe
        double m_taille;        ///< nombre d'arêtes du graphe

        /// \fn void showNodes(Svgfile* svg) const
        /// \brief dessine un sommet sur le fichier svg passé en paramètre
        /// \param svg : fichier svg sur lequel on dessine
        void showNodes(Svgfile* svg) const;

        /// \fn void showConnections(Svgfile* svg, std::vector<bool>* path = nullptr) const
        /// \brief dessine les arête sur le fichier svg passé en paramètre
        /// \param svg : fichier svg sur lequel on dessisne
        /// \param path : pointeur sur vecteur de booléens de même taille que la liste d'arêtes : le booléen d'indice n décrit si l'arête d'indice n est active ou non
        void showConnections(Svgfile* svg, std::vector<bool>* path = nullptr) const;

        /// \fn void showBounds(Svgfile* svg)
        /// \brief dessine les contours du fichier svg passé en paramètre
        /// \param svg : fichier svg sur lequel on dessine
        void showBounds(Svgfile* svg);

        /// \fn Svgfile* createSvgfile(std::string filename = "output.svg")
        /// \brief crée un fichier svg dont le nom est passé en paramètre
        /// \param filename : nom du fichier svg que l'on va créer
        /// \return un pointeur sur le fichier svg créé
        Svgfile* createSvgfile(std::string filename = "output.svg");

        /// \fn std::vector<std::pair<float,int>> getNeighbours(Node* origin,int weight,std::vector<bool> activeConnections)
        /// \brief utilisée pour dijkstra : renvoie la liste des pairs <poids,id> des sommets voisins du sommet "origin" (l'activité ou non des connections est prise en compte pour déterminer les voisins)
        /// \param origin : sommet dont on cherche les voisins
        /// \param weight : indice du poids que l'on va retourner dans la paire
        /// \param activeConnections : vecteur de booléens de même taille que la liste d'arêtes : le booléen d'indice n décrit si l'arête d'indice n est active ou non
        /// \return la liste des paires des indexs des voisins et leur poids d'indice weight
        std::vector<std::pair<float,int>> getNeighbours(Node* origin,int weight,std::vector<bool> activeConnections);

        /// \fn float weightsSum(std::vector<bool> connections, int weight)
        /// \brief calcule la somme des poids des arêtes actives
        /// non utilisée
        /// \param connections : vecteur de booléens de même taille que la liste d'arêtes : le booléen d'indice n décrit si l'arête d'indice n est active ou non
        /// \param weight : indice du poids avec lequel on travaille
        /// \return la somme des poids d'indice weight de toutes les arêtes actives
        float weightsSum(std::vector<bool> connections, int weight);
};

/// \fn std::vector<Connection*> sortConnections(std::vector<Connection*> connections, int weight)
/// \brief trie les arêtes passées en paramètre en fonctions de leur poids d'indice [weight], dans l'ordre croissant
/// optimisée par une fonction sort de la STL
/// \param connections : liste des arêtes à trier
/// \param weight : indice du poids selon lequel on va trier les arêtes
/// \return la liste des arêtes, triées dans l'ordre des poids croissants
std::vector<Connection*> sortConnections(std::vector<Connection*> connections, int weight);

/// \fn std::vector<Connection*> sortConnectionsByIndex(std::vector<Connection*> connections)
/// \brief trie les connexions du vecteur en paramètre en fonction de leur id, dans l'ordre croissant
/// remplacée par une fonction sort de la STL
/// \param connections : liste des arêtes à trier
/// \return la liste des arêtes, triées dans l'ordre des indexs croissants
std::vector<Connection*> sortConnectionsByIndex(std::vector<Connection*> connections);

/// \fn std::vector<std::pair<float,int>> sortNodes(std::vector<std::pair<float,int>> Nodes)
/// \brief trie les paires <poids,id>, qui représentent des sommets, en fonction du paramètre poids et dans l'ordre croissant
/// remplacée par une fonction sort de la STL
/// \param Nodes : liste des paires <poids,id>, qui représentent des sommets
/// \return liste des paires triés dans l'ordre des poids croissants
std::vector<std::pair<float,int>> sortNodes(std::vector<std::pair<float,int>> Nodes);

/// \fn int howManyTrue(std::vector<bool>& subject)
/// \brief retourne le nombre de booléens ayant comme valeur true dans un vecteur de booléens
/// \param subject : référence sur un vecteur de booléens de même taille que la liste d'arêtes : le booléen d'indice n décrit si l'arête d'indice n est active ou non
/// \return nombre de booléens de valeur true dans le vecteur
int howManyTrue(std::vector<bool>& subject);

/// \fn std::vector<Connection*> sortConnections(std::vector<Connection*> connections, int weight)
/// \brief trie les arêtes passées en paramètre en fonctions de leur poids d'indice [weight], dans l'ordre croissant
/// optimisée par une fonction sort de la STL
/// \param connections : liste des arêtes à trier
/// \param weight : indice du poids selon lequel on va trier les arêtes
/// \return la liste des arêtes, triées dans l'ordre des poids croissants
std::vector<Connection*> sortConnections(std::vector<Connection*> connections, int weight);

/// \fn std::vector<Connection*> sortConnectionsByIndex(std::vector<Connection*> connections)
/// \brief trie les connexions du vecteur en paramètre en fonction de leur id, dans l'ordre croissant
/// remplacée par une fonction sort de la STL
/// \param connections : liste des arêtes à trier
/// \return la liste des arêtes, triées dans l'ordre des indexs croissants
std::vector<Connection*> sortConnectionsByIndex(std::vector<Connection*> connections);

/// \fn std::vector<std::pair<float,int>> sortNodes(std::vector<std::pair<float,int>> Nodes)
/// \brief trie les paires <poids,id>, qui représentent des sommets, en fonction du paramètre poids et dans l'ordre croissant
/// remplacée par une fonction sort de la STL
/// \param Nodes : liste des paires <poids,id>, qui représentent des sommets
/// \return liste des paires triés dans l'ordre des poids croissants
std::vector<std::pair<float,int>> sortNodes(std::vector<std::pair<float,int>> Nodes);

/// \fn bool add_1bit(bool a, bool b, bool& c)
/// \brief additionnneur 1 bit
/// \param a : paramètre 1 de l'addition
/// \param b : paramètre 2 de l'addition
/// \param c : retenue précédente et passée par adresse pour être modifiée et devenir la nouvelle retenue
/// \return résultat de l'addition
bool add_1bit(bool a, bool b, bool& c);

/// \fnbool connectionsComparator(const Connection* lhs, const Connection* rhs)
/// \brief comparateur pour trier les connexions par index, dans l'ordre croissant
/// https://www.tutorialspoint.com/Sorting-a-vector-of-custom-objects-using-Cplusplus-STL
/// \param lhs : élément 1 à comparer
/// \param rhs : élément 2 à comparer
/// \return true si le paramètre 1 a un index plus petit que le paramètre 2, false sinon
bool connectionsComparator(const Connection* lhs, const Connection* rhs);

/// \fn bool connectionsComparatorWeight0(const Connection* lhs,const Connection* rhs)
/// \brief comparateur pour trier les connexions par le poids d'indice 0, dans l'ordre croissant
/// https://www.tutorialspoint.com/Sorting-a-vector-of-custom-objects-using-Cplusplus-STL
/// \param lhs : élément 1 à comparer
/// \param rhs : élément 2 à comparer
/// \return true si le paramètre 1 a un poids d'indice 0 plus petit que le paramètre 2, false sinon
bool connectionsComparatorWeight0(const Connection* lhs,const Connection* rhs);

/// \fn bool connectionsComparatorWeight1(const Connection* lhs,const Connection* rhs)
/// \brief comparateur pour trier les connexions par le poids d'indice 1, dans l'ordre croissant
/// https://www.tutorialspoint.com/Sorting-a-vector-of-custom-objects-using-Cplusplus-STL
/// \param lhs : élément 1 à comparer
/// \param rhs : élément 2 à comparer
/// \return true si le paramètre 1 a un poids d'indice 1 plus petit que le paramètre 2, false sinon
bool connectionsComparatorWeight1(const Connection* lhs,const Connection* rhs);

/// \fn std::vector<std::vector<bool>> combinations(int k, int n, Graph* g)
/// \brief permet d'obtenir la liste des combinations possibles d'arrangements de k arêtes parmi les n arêtes du graphe
/// \param k : nombre d'arêtes des solutions recherchées
/// \param n : nombre total d'arêtes du graphe
/// \param g : pointeur sur le graphe
/// \return la liste des solutions de taille k
std::vector<std::vector<bool>> combinations(int k, int n, Graph* g);

/// \fn std::vector<bool> tradIntToBool(std::vector<int> vec, Graph* g)
/// \brief permet de transcrire la liste des arêtes actives en un vecteur de booléens qui décrit la totalité des arêtes
/// \param vec : liste des indexs des arêtes actives
/// \param g : pointeur sur le graphe
/// \return vecteur de booléens de même taille que la liste d'arêtes : le booléen d'indice n décrit si l'arête d'indice n est active ou non
std::vector<bool> tradIntToBool(std::vector<int> vec, Graph* g);

#endif // GRAPH_H
