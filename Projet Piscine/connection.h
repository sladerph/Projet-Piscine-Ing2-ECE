#ifndef CONNECTION_H
#define CONNECTION_H

/// \file connection.h
/// \brief contient la classe connection, qui repr�sente une ar�te
/// \author Pierre Herduin

#include "node.h"

#include <vector>

/// \class Node
/// \brief  inclue ici pour raison de double inclusion
class Node;


/// \class Connection
/// \brief Classe repr�sentant une ar�te du graphe
class Connection
{
    public:
        /// \fn Connection(int index, Node* a, Node* b)
        /// \brief Constructeur
        /// constructeur de la classe Connection
        /// \param Index : index initial de l'ar�te
        /// \param a : sommet A initial de l'ar�te
        /// \param b : sommet B initial de l'ar�te
        Connection(int index, Node* a, Node* b);

        /// \fn Connection(int index, Node* a, Node* b)
        /// \brief Constructeur
        /// constructeur de la classe Connection
        /// \param Index : index initial de l'ar�te
        /// \param a : sommet A initial de l'ar�te
        /// \param b : sommet B initial de l'ar�te
        /// \param weights : liste des poids de l'ar�te
        Connection(int index, Node* a, Node* b,std::vector<float> weights);

        /// \fn ~Connection()
        /// \brief Destructeur
        /// Destructeur de la classe Connection
        ~Connection();

        /// \fn int getIndex() const
        /// \brief getter permettant d'obtenir l'index d'une ar�te
        /// \return l'index de l'ar�te
        int getIndex() const {return m_index;};

        /// \fn Node* getNodeA() const
        /// \brief  getter permettant d'obtenir le sommet A d'une ar�te
        /// \return le sommet A d'une ar�te
        Node* getNodeA() const {return m_node_a;};

        /// \fn Node* getNodeB() const
        /// \brief  getter permettant d'obtenir le sommet B d'une ar�te
        /// \return le sommet B d'une ar�te
        Node* getNodeB() const {return m_node_b;};

        /// \fn std::vector<float> getWeights() const
        /// \brief  getter permettant d'obtenir la liste des poids de l'ar�te
        /// \return la liste des poids de l'ar�te
        std::vector<float> getWeights() const {return m_weights;};

        /// \fn void addWeight(float w)
        /// \brief  permet d'ajouter un poids � la liste de poids d'une ar�te
        /// \param  w : valeur du poids ajout�
        void addWeight(float w) {m_weights.push_back(w);};

    private:
        int m_index;        ///< Index de l'ar�te

        Node* m_node_a;     ///< sommet A de l'ar�te
        Node* m_node_b;     ///< sommet B de l'ar�te

        std::vector<float> m_weights;       ///< liste des poids de l'ar�te

};

#endif // CONNECTION_H
