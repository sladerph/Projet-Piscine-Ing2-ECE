#ifndef CONNECTION_H
#define CONNECTION_H

/// \file connection.h
/// \brief Contient la classe connection, qui représente une arête d'un graphe.
/// \author Pierre Herduin, Mélodie Damas, Simon jolly

#include "node.h"

#include <vector>

/// \class Node
/// \brief  inclue ici pour raison de double inclusion
class Node;


/// \class Connection
/// \brief Classe représentant une arête du graphe
class Connection
{
    public:
        /// \fn Connection(int index, Node* a, Node* b)
        /// \brief Constructeur de la classe Connection
        /// \param Index : index de l'arête, son identité
        /// \param a : sommet A de l'arête
        /// \param b : sommet B de l'arête
        Connection(int index, Node* a, Node* b);

        /// \fn Connection(int index, Node* a, Node* b)
        /// \brief Constructeur
        /// constructeur de la classe Connection
        /// \param Index : index de l'arête, son identité
        /// \param a : sommet A de l'arête
        /// \param b : sommet B de l'arête
        /// \param weights : liste des poids de l'arête
        Connection(int index, Node* a, Node* b,std::vector<float> weights);

        /// \fn ~Connection()
        /// \brief Destructeur
        /// Destructeur de la classe Connection
        ~Connection();

        /// \fn int getIndex() const
        /// \brief getter permettant d'obtenir l'index d'une arête
        /// \return l'index de l'arête
        int getIndex() const {return m_index;};

        /// \fn Node* getNodeA() const
        /// \brief  getter permettant d'obtenir le sommet A d'une arête
        /// \return le sommet A d'une arête
        Node* getNodeA() const {return m_node_a;};

        /// \fn Node* getNodeB() const
        /// \brief  getter permettant d'obtenir le sommet B d'une arête
        /// \return le sommet B d'une arête
        Node* getNodeB() const {return m_node_b;};

        /// \fn std::vector<float> getWeights() const
        /// \brief  getter permettant d'obtenir la liste des poids de l'arête
        /// \return la liste des poids de l'arête
        std::vector<float> getWeights() const {return m_weights;};

        /// \fn void addWeight(float w)
        /// \brief  permet d'ajouter un poids à la liste de poids d'une arête
        /// \param  w : valeur du poids ajouté
        void addWeight(float w) {m_weights.push_back(w);};

    private:
        int m_index;        ///< Index de l'arête

        Node* m_node_a;     ///< sommet A de l'arête
        Node* m_node_b;     ///< sommet B de l'arête

        std::vector<float> m_weights;       ///< liste des poids de l'arête

};

#endif // CONNECTION_H
