#ifndef DNA_H
#define DNA_H

/// \file dna.h
/// \brief objet ADN pour l'évolution génétique.
/// \author Pierre Herduin

#include "graph.h"
#include "population.h"

#include <vector>

class Graph;

/// \class DNA
/// \brief Cette classe représente un graphe codé par un vecteur de booléens, vrai indiquant que l'arrête est active.
class DNA
{
    public:

        /// \fn DNA(Graph* structure)
        /// \brief Constructeur.
        /// Ce constructeur initialise les données en fonction du graphe passé en paramètre.
        /// \param structure : pointeur sur le graphe sur lequel cet objet est dimensionné.
        DNA(Graph* structure);

        /// \fn DNA()
        /// \brief Constructeur par défaut qui ne fait rien.
        DNA();

        /// \fn ~DNA()
        /// \brief Destructeur par défaut qui ne fait rien.
        ~DNA();

        /// \fn DNA* crossover(DNA* parent_b, Graph* structure)
        /// \brief Fonction qui crée un enfant à partir de this et du parent_b.
        /// \param parent_b : pointeur sur le deuxième parent.
        /// \param structure : pointeur sur le graphe qui servira pour le constructeur de l'enfant.
        /// \return retourne un pointeur sur l'enfant créée.
        DNA* crossover(DNA* parent_b, Graph* structure);

        /// \fn void mutate(int mutation_rate)
        /// \brief Fonction qui effectue des mutatations aléatoires du code génétique (vecteur de booléens)
        /// \param mutation_rate : le pourcentage de chance que l'élément subisse une mutation.
        void mutate(int mutation_rate);

        /// \fn bool dominated(DNA* b)
        /// \brief Fonction qui vérifie si l'objet est dominé par b.
        /// \param b : pointeur sur l'objet contre lequel this est testé.
        bool dominated(DNA* b);

        /// \fn void setFitness(float f)
        /// \brief Fonction qui change la valeur du fitness.
        /// \param f : nouveau fitness.
        void setFitness(float f) {m_fitness = f;};

        /// \fn void setSumA(float s)
        /// \brief Fonction qui change la valeur de la somme des coûts 1.
        /// \param s : nouvelle valeur de la somme des coûts 1.
        void setSumA(float s) {m_sum_cost_a = s;};

        /// \fn void setSumB(float s)
        /// \brief Fonction qui change la valeur de la somme des coûts 2.
        /// \param s : nouvelle valeur de la somme des coûts 2.
        void setSumB(float s) {m_sum_cost_b = s;};

        /// \fn void setDNA(std::vector<bool> vec)
        /// \brief Fonction qui change la valeur du vecteur de booléens.
        /// \param vec : le nouveau vecteur.
        void setDNA(std::vector<bool> vec) {m_dna = vec;};

        /// \fn void setDominated(bool dom)
        /// \brief Fonction qui change la valeur du booléen qui indique si l'objet est dominé.
        /// \param dom : la nouvelle valeur.
        void setDominated(bool dom)  {m_dominated = dom;};

        /// \fn void setSize(int s)
        /// \brief Fonction qui change la valeur de la taille.
        /// \param s : la nouvelle valeur de la taille.
        void setSize(int s) {m_size = s;};

        /// \fn void setFront(int f)
        /// \brief Fonction qui change la valeur du front de domination (nombre d'objets qui dominent this).
        /// \param f : la nouvelle valeur du front de domination.
        void setFront(int f) {m_front = f;};

        /// \fn std::vector<bool> getDNA() const
        /// \brief Fonction constante qui récupère le vecteur de booléens.
        /// \return retourne le vecteur de booléens.
        std::vector<bool> getDNA() const {return m_dna;};

        /// \fn float getFitness() const
        /// \brief Fonction constante qui récupère le fitness.
        /// \return retourne le fitness.
        float getFitness() const {return m_fitness;};

        /// \fn float getSumA() const
        /// \brief Fonction constante qui récupère la somme des coûts 1.
        /// \return retourne la somme des coûts 1.
        float getSumA() const {return m_sum_cost_a;};

        /// \fn float getSumB() const
        /// \brief Fonction constante qui récupère la somme des coûts 2.
        /// \return retourne la somme des coûts 2.
        float getSumB() const {return m_sum_cost_b;};

        /// \fn bool getDominated() const
        /// \brief Fonction constante qui récupère le booléen de domination.
        /// \return retourne le booléen de domination.
        bool  getDominated() const {return m_dominated;};

        /// \fn int getFront() const
        /// \brief Fonction constante qui récupère le front de domination.
        /// \return retourne le front de domination.
        int   getFront() const {return m_front;};

        /// \fn bool operator==(const DNA* b)
        /// \brief Fonction operateur qui regarde si deux éléments de type DNA* sont identiques.
        /// \param b : l'élément à comparer avec this.
        /// \return retourne le front de domination.
        bool operator==(const DNA* b);

        /// \fn DNA* clone()
        /// \brief Fonction qui crée un clone de this.
        /// \return retourne le clone de this.
        DNA* clone();

    private:
        std::vector<bool> m_dna; /// vecteur qui indique si la connexion est active.
        int m_size; /// La taille du vecteur.
        int m_front; /// Le nombre d'éléments qui le dominent.
        float m_sum_cost_a; /// La somme des coûts 1.
        float m_sum_cost_b; /// La somme des coûts 2.
        float m_fitness; /// Le fitness.
        bool m_dominated; /// booléen pour savoir si this est dominé.
};

#endif // DNA_H
