#ifndef NODE_H
#define NODE_H

/// \file node.h
/// \brief regroupe la classe Node et les diff�rentes fonction agissant sur les sommets du graphe
/// \author Pierre Herduin, Simon jolly

#include "connection.h"

#include <vector>

/// \class Connection
/// \brief classe repr�sentant une ar�te, red�clar�e pour cause de double inclusion
class Connection;


/// \class Node
/// \brief Classe repr�sentant un sommet du graphe
class Node
{
    public:
        /// \fn Node(int index, float x, float y)
        /// \brief Constructeur de la classe Node
        /// \param index  : index initial du sommet.
        /// \param x : abscisse initiale du sommet
        /// \param y : ordonn�e initiale du sommet
        Node(int index, float x, float y);

        /// \fn ~Node()
        /// \brief destructeur
        /// Destructeur de la classe Node
        ~Node();

        /// \fn int   getIndex() const
        /// \brief getter permettant d'obtenir l'index d'un sommet
        /// \return Index du sommet
        int   getIndex() const {return m_index;};

        /// \fn float getX    () const
        /// \brief getter permettant d'obtenir l'abscisse d'un sommet
        /// \return l'abscisse du sommet
        float getX    () const {return m_x    ;};

        /// \fn float getY    () const
        /// \brief getter permettant d'obtenir l'ordonnee d'un sommet
        /// \return l'ordonnee du sommet
        float getY    () const {return m_y    ;};

    private:
        int m_index;    ///< Index du sommet

        float m_x;      ///< abscisse du sommet
        float m_y;      ///<  ordonn�e du sommet

        std::vector<Connection*> m_connections;     ///< liste des ar�tes connect�es � ce sommet
        std::vector<Node*> m_nodes;         ///<  liste des sommets voisins
};

#endif // NODE_H
