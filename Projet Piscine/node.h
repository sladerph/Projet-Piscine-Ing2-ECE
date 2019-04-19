#ifndef NODE_H
#define NODE_H

/// \file node.h
/// \brief regroupe la classe Node et les différentes fonction agissant sur les sommets du graphe
/// \author Pierre Herduin, Simon jolly

#include "connection.h"

#include <vector>

/// \class Connection
/// \brief classe représentant une arête, redéclarée pour cause de double inclusion
class Connection;


/// \class Node
/// \brief Classe représentant un sommet du graphe
class Node
{
    public:
        /// \fn Node(int index, float x, float y)
        /// \brief constructeur
        /// Constructeur de la classe Node
        /// \param index  : index initial du sommet.
        /// \param x : abscisse initiale du sommet
        /// \param y : ordonnée initiale du sommet
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
        float m_y;      ///<  ordonnée du sommet

        std::vector<Connection*> m_connections;     ///< liste des arêtes connectées à ce sommet
        std::vector<Node*> m_nodes;         ///<  liste des sommets voisins
};

#endif // NODE_H
