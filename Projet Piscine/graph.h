#ifndef GRAPH_H
#define GRAPH_H

/// \file graph.h
/// \brief regroupe la classe graph les diff�rentes fonction agissant sur le graphe et permettant de l'afficher ainsi
///que les fonctions accessoires qu'elles utilisent
/// \author Pierre Herduin, M�lodie Damas, Simon jolly

#include "node.h"
#include "connection.h"
#include "svgfile.h"

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <queue>
#include <bits/stdc++.h>    /// \brief ajout�e pour le sort(vecteur.begin(),vecteur.end());
                            ///https://www.geeksforgeeks.org/sorting-vector-of-pairs-in-c-set-1-sort-by-first-and-second/

#define XOFFSET 50  /// \def XOFFSET 50
#define YOFFSET 50  /// \def YOFFSET 50


/// \class Graph
/// \brief Classe repr�sentant un graphe
/// La classe g�re le traitement et l'affichage d'un graphe
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
        /// \param path : pointeur sur vecteur de bool�ens de m�me taille que la liste d'ar�tes : le bool�en d'indice n d�crit si l'ar�te d'indice n est active ou non
        void show(std::string filename = "output.svg", std::vector<bool>* path = nullptr);

        /// \fn void showPrim(std::string filename = "output.svg", std::vector<bool>* path = nullptr, bool onTopOfGraph = true)
        /// \brief permet de dessiner l'arbre couvrant de poids minimal sur un fichier svg
        /// \param filename : nom du fichier sur lequel on veut dessiner
        /// \param path : pointeur sur vecteur de bool�ens de m�me taille que la liste d'ar�tes : le bool�en d'indice n d�crit si l'ar�te d'indice n est active ou non
        /// \param onTopOfGraph : bool�en qui permet de savoir si on va dessiner l'arbre couvrant sur le graphe ou � cot�
        void showPrim(std::string filename = "output.svg", std::vector<bool>* path = nullptr, bool onTopOfGraph = true);

        /// \fn bool create(std::string topology, std::string costs)
        /// \brief permet de cr�er un graphe en le chargeant � partir de fichiers textes
        /// \param topology : nom du fichier texte d'o� on chargera les sommets et les ar�tes du graphe
        /// \param  costs: nom du fichier texte d'o� on chargera les poids des ar�tes du graphe
        /// \return retourne un bool�en qui indique si le chargement s'est bien d�roul� ou non
        bool create(std::string topology, std::string costs);

        /// \fn Node* getNode(int index)
        /// \brief getter qui permet de r�cup�rer le sommet d'indice Index
        /// \param  Index : indice du sommet que l'on veut r�cup�rer
        /// \return le Sommet d'indice Index
        Node* getNode(int index);

        /// \fn Connection* getConnection(int index)
        /// \brief getter qui permet de r�cup�rer une ar�te du graphe en passant son indice en param�tre
        /// \param  Index : indice de l'ar�te que l'on veut r�cup�rer
        /// \return l'ar�td 'indice index
        Connection* getConnection(int index);       //retourne l'ar�te d'indice [index]

        /// \fn std::vector<Connection*> getConnections() const
        /// \brief getter qui permet de r�cup�rer la liste des ar�tes du graphe
        /// \return la liste des ar�tes du graphe
        std::vector<Connection*> getConnections() const {return m_connections;};       //retourne la liste des ar�tes du graphe

        /// \fn int getOrdre() const
        /// \brief getter qui permet d'obtenir le nombre de sommmet du graphe
        /// \return le nombre de sommet du graphe
        int getOrdre() const {return m_ordre;}; //retourne le nombre de sommets du graphe

        /// \fn std::vector<bool> getPrim(int weight, float* totalWeight)
        /// \brief retourne un vecteur de bool�ens d�crivant le graphe couvrant de poids minimum. Weight permet de choisir entre
        /// les diff�rents poids des ar�tes. totalWeight sera modifi� � l'int�rieur du programme, et vaudra la somme des poids des ar�tes
        /// \param weight : Indice dans le vecteur de poids du poids par lequel on veut trier les ar�tes
        /// \param totalWeight : somme des poids des ar�tes, qui est pass� par adresse pour �tre modifi� � l'int�rieur du programme
        /// \return vecteur de bool�ens de m�me taille que la liste d'ar�tes : le bool�en d'indice n d�crit si l'ar�te d'indice n est active ou non
        std::vector<bool> getPrim(int weight, float* totalWeight);

        /// \fn float getDijkstra(int weight, std::vector<bool> activeConnections)
        /// \brief retourne la somme des plus courts chemins entre toutes les paires de sommets du graphe
        /// \param weight : indice du poids pour lequel on veut �tudier le graphe
        /// \param activeConnections : vecteur de bool�ens de m�me taille que la liste d'ar�tes : le bool�en d'indice n d�crit si l'ar�te d'indice n est active ou non
        /// \return la somme de splus courts chemins entre toutes les paires de sommets du graphe
        float getDijkstra(int weight, std::vector<bool> activeConnections);

        /// \fn bool testCycle(std::vector<bool> connections)
        /// \brief renvoie true s'il y a un cycle, renvoie false sinon;
        /// \param connections : vecteur de bool�ens de m�me taille que la liste d'ar�tes : le bool�en d'indice n d�crit si l'ar�te d'indice n est active ou non
        /// \return retourne true si il y a un cycle, false sinon
        bool testCycle(std::vector<bool> connections);

        /// \fn bool connectivityTest(std::vector<bool>connections)
        /// \brief renvoie true si le graphe est connexe, renvoie false sinon
        /// \param connections : vecteur de bool�ens de m�me taille que la liste d'ar�tes : le bool�en d'indice n d�crit si l'ar�te d'indice n est active ou non
        /// \return retourne true si le graphe est connexe, false sinon
        bool connectivityTest(std::vector<bool>connections);


        /// \fn std::vector<std::vector<bool>> enumeration ()
        /// \brief fonction qui �num�re toutes les arrangements d'ar�tes possibles
        /// \return retourne la liste de tous les arrangements, sous forme de vecteur de bool�ens de m�me taille que la liste d'ar�tes : le bool�en d'indice n d�crit si l'ar�te d'indice n est active ou non
        std::vector<std::vector<bool>> enumeration ();

        /// \fn std::vector<std ::vector<bool>> filtrage ()
        /// \brief fonction qui selectionne les solutions admissibles parmis les solutions existantes
        /// \return retourne la liste de toutes les solutions admissibles, , sous forme de vecteur de bool�ens de m�me taille que la liste d'ar�tes : le bool�en d'indice n d�crit si l'ar�te d'indice n est active ou non
        std::vector<std ::vector<bool>> filtrage ();

        /// \fn void evaluation ()
        /// \brief fonction qui trie les solutions domin�es et non domin�es selon les 2 objectifs et les affiche
        void evaluation ();

        /// \fn void secondEvaluation()
        /// \brief semblable � evaluation(), mais pour 2 objectifs de natures diff�rentes
        void secondEvaluation();

        /// \fn std::vector<std ::vector<bool>> secondfiltrage ()
        /// \brief semblable � filtrage(), mais sans filtrer les solutions qui contiennent des cycles
        /// \return retourne la liste de toutes les solutions admissibles, , sous forme de vecteur de bool�ens de m�me taille que la liste d'ar�tes : le bool�en d'indice n d�crit si l'ar�te d'indice n est active ou non
        std::vector<std ::vector<bool>> secondfiltrage ();

        /// \fn std::vector<std::vector<bool>> secondEnumeration ()
        /// \brief semblable � enumeration(), mais ne filtre pas les cycles
        /// \return retourne la liste de tous les arrangements, sous forme de vecteur de bool�ens de m�me taille que la liste d'ar�tes : le bool�en d'indice n d�crit si l'ar�te d'indice n est active ou non
        std::vector<std::vector<bool>> secondEnumeration ();

    private:
        std::vector<Node*> m_nodes;     ///< liste des sommets du graphe
        std::vector<Connection*> m_connections;     ///< liste des ar�tes du graphe

        int m_ordre;    ///< nombre de sommet du graphe
        double m_taille;        ///< nombre d'ar�tes du graphe

        /// \fn void showNodes(Svgfile* svg) const
        /// \brief dessine un sommet sur le fichier svg pass� en param�tre
        /// \param svg : fichier svg sur lequel on dessine
        void showNodes(Svgfile* svg) const;

        /// \fn void showConnections(Svgfile* svg, std::vector<bool>* path = nullptr) const
        /// \brief dessine les ar�te sur le fichier svg pass� en param�tre
        /// \param svg : fichier svg sur lequel on dessisne
        /// \param path : pointeur sur vecteur de bool�ens de m�me taille que la liste d'ar�tes : le bool�en d'indice n d�crit si l'ar�te d'indice n est active ou non
        void showConnections(Svgfile* svg, std::vector<bool>* path = nullptr) const;

        /// \fn void showBounds(Svgfile* svg)
        /// \brief dessine les contours du fichier svg pass� en param�tre
        /// \param svg : fichier svg sur lequel on dessine
        void showBounds(Svgfile* svg);

        /// \fn Svgfile* createSvgfile(std::string filename = "output.svg")
        /// \brief cr�e un fichier svg dont le nom est pass� en param�tre
        /// \param filename : nom du fichier svg que l'on va cr�er
        /// \return un pointeur sur le fichier svg cr��
        Svgfile* createSvgfile(std::string filename = "output.svg");

        /// \fn std::vector<std::pair<float,int>> getNeighbours(Node* origin,int weight,std::vector<bool> activeConnections)
        /// \brief utilis�e pour dijkstra : renvoie la liste des pairs <poids,id> des sommets voisins du sommet "origin" (l'activit� ou non des connections est prise en compte pour d�terminer les voisins)
        /// \param origin : sommet dont on cherche les voisins
        /// \param weight : indice du poids que l'on va retourner dans la paire
        /// \param activeConnections : vecteur de bool�ens de m�me taille que la liste d'ar�tes : le bool�en d'indice n d�crit si l'ar�te d'indice n est active ou non
        /// \return la liste des paires des indexs des voisins et leur poids d'indice weight
        std::vector<std::pair<float,int>> getNeighbours(Node* origin,int weight,std::vector<bool> activeConnections);

        /// \fn float weightsSum(std::vector<bool> connections, int weight)
        /// \brief calcule la somme des poids des ar�tes actives
        /// non utilis�e
        /// \param connections : vecteur de bool�ens de m�me taille que la liste d'ar�tes : le bool�en d'indice n d�crit si l'ar�te d'indice n est active ou non
        /// \param weight : indice du poids avec lequel on travaille
        /// \return la somme des poids d'indice weight de toutes les ar�tes actives
        float weightsSum(std::vector<bool> connections, int weight);
};

/// \fn std::vector<Connection*> sortConnections(std::vector<Connection*> connections, int weight)
/// \brief trie les ar�tes pass�es en param�tre en fonctions de leur poids d'indice [weight], dans l'ordre croissant
/// optimis�e par une fonction sort de la STL
/// \param connections : liste des ar�tes � trier
/// \param weight : indice du poids selon lequel on va trier les ar�tes
/// \return la liste des ar�tes, tri�es dans l'ordre des poids croissants
std::vector<Connection*> sortConnections(std::vector<Connection*> connections, int weight);

/// \fn std::vector<Connection*> sortConnectionsByIndex(std::vector<Connection*> connections)
/// \brief trie les connexions du vecteur en param�tre en fonction de leur id, dans l'ordre croissant
/// remplac�e par une fonction sort de la STL
/// \param connections : liste des ar�tes � trier
/// \return la liste des ar�tes, tri�es dans l'ordre des indexs croissants
std::vector<Connection*> sortConnectionsByIndex(std::vector<Connection*> connections);

/// \fn std::vector<std::pair<float,int>> sortNodes(std::vector<std::pair<float,int>> Nodes)
/// \brief trie les paires <poids,id>, qui repr�sentent des sommets, en fonction du param�tre poids et dans l'ordre croissant
/// remplac�e par une fonction sort de la STL
/// \param Nodes : liste des paires <poids,id>, qui repr�sentent des sommets
/// \return liste des paires tri�s dans l'ordre des poids croissants
std::vector<std::pair<float,int>> sortNodes(std::vector<std::pair<float,int>> Nodes);

/// \fn int howManyTrue(std::vector<bool> subject)
/// \brief retourne le nombre de bool�ens ayant comme valeur true dans un vecteur de bool�ens
/// \param subject : vecteur de bool�ens de m�me taille que la liste d'ar�tes : le bool�en d'indice n d�crit si l'ar�te d'indice n est active ou non
/// \return nombre de bool�ens de valeur true dans le vecteur
int howManyTrue(std::vector<bool> subject);

/// \fn bool add_1bit(bool& r_sortie ,bool r_entree,bool a, bool b)
/// \brief additionneur 1 bit
/// \param r_sortie : retenue de fin d'addition, pass�e par adresse pour �tre modifi�e dans la fonction
/// \param r_entr�e : retenue de l'addition pr�c�dente
/// \param a : �l�ment 1 de l'addition
/// \param b : �l�ment 2 de l'addition
/// \return retourne le r�sultat de l'addition
bool add_1bit(bool& r_sortie ,bool r_entree,bool a, bool b);

/// \fnbool connectionsComparator(const Connection* lhs, const Connection* rhs)
/// \brief comparateur pour trier les connexions par index, dans l'ordre croissant
/// https://www.tutorialspoint.com/Sorting-a-vector-of-custom-objects-using-Cplusplus-STL
/// \param lhs : �l�ment 1 � comparer
/// \param rhs : �l�ment 2 � comparer
/// \return true si le param�tre 1 a un index plus petit que le param�tre 2, false sinon
bool connectionsComparator(const Connection* lhs, const Connection* rhs);

/// \fn bool connectionsComparatorWeight0(const Connection* lhs,const Connection* rhs)
/// \brief comparateur pour trier les connexions par le poids d'indice 0, dans l'ordre croissant
/// https://www.tutorialspoint.com/Sorting-a-vector-of-custom-objects-using-Cplusplus-STL
/// \param lhs : �l�ment 1 � comparer
/// \param rhs : �l�ment 2 � comparer
/// \return true si le param�tre 1 a un poids d'indice 0 plus petit que le param�tre 2, false sinon
bool connectionsComparatorWeight0(const Connection* lhs,const Connection* rhs);

/// \fn bool connectionsComparatorWeight1(const Connection* lhs,const Connection* rhs)
/// \brief comparateur pour trier les connexions par le poids d'indice 1, dans l'ordre croissant
/// https://www.tutorialspoint.com/Sorting-a-vector-of-custom-objects-using-Cplusplus-STL
/// \param lhs : �l�ment 1 � comparer
/// \param rhs : �l�ment 2 � comparer
/// \return true si le param�tre 1 a un poids d'indice 1 plus petit que le param�tre 2, false sinon
bool connectionsComparatorWeight1(const Connection* lhs,const Connection* rhs);

#endif // GRAPH_H
