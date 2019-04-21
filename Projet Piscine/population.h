#ifndef POPULATION_H
#define POPULATION_H

/// \file
/// \brief
/// \author Pierre Herduin, Mélodie Damas, Simon jolly

#include "dna.h"
#include "utils.h"

#include <windows.h>
#include <sstream>
#include <time.h>

class DNA;
class Graph;

/// \class Population
/// \brief Classe qui s'occupe de l'évolution génétique d'un ensemble d'individus.
class Population
{
    public:

        /// \fn Population(int pop_size, Graph* structure, int mutation_rate = 5)
        /// \brief Constructeur.
        /// \param pop_size : le nombre d'individus dans la population.
        /// \param structure : pointeur sur le graphe sur lequel sont construits les individus.
        /// \param mutation_rate : pourcentage de chance de subir une mutation pour une connexion. Par défaut : 5.
        Population(int pop_size, Graph* structure, int mutation_rate = 5);

        /// \fn ~Population()
        /// \brief Destructeur.
        ~Population();

        /// \fn void evaluateFitness()
        /// \brief Calcul le fitness des individus.
        void evaluateFitness();

        /// \fn void purify()
        /// \brief Elimine les individus non valides (non connexes et de taille différente à ordre - 1).
        void purify();

        /// \fn bool reproduce()
        /// \brief Assure la sélection et reproduction naturelle.
        /// \return retourne vrai si la reproduction à réussie, faux sinon.
        bool reproduce();

        /// \fn void checkDominated()
        /// \brief Vérifie si les individus sont dominés ou non.
        void checkDominated();

        /// \fn void showNonDominated()
        /// \brief Affiche les individus non dominés.
        void showNonDominated();

        /// \fn void mutate()
        /// \brief Procède aux mutations génétiques aléatoires.
        void mutate();

        /// \fn void checkClones()
        /// \brief Elimine les doublons.
        void checkClones();

        /// \fn void checkPareto()
        /// \brief Met à jour la liste des meilleurs solutions de pareto.
        void checkPareto();

        /// \fn std::vector<DNA*> getClosest(DNA* dna)
        /// \brief Retourne un vecteur contenant les deux elements les plus proches (sur le diagramme de pareto) ou nullptr si l'elements n'existe pas.
        /// \param dna : l'objet dont on doit trouver les deux elements les plus proches.
        /// \return Retourne un vecteur contenant les deux elements les plus proches (sur le diagramme de pareto) ou nullptr si l'elements n'existe pas.
        std::vector<DNA*> getClosest(DNA* dna);

        /// \fn void evaluateDominatedFront()
        /// \brief Calcul les fronts de domination.
        void evaluateDominatedFront();

        /// \fn bool isDominated(DNA* dna, std::vector<DNA*> comp)
        /// \brief vérifie si un element est dominé par un conteneur d'elements.
        /// \param dna : element à verifier.
        /// \param comp : conteneur d'element contre qui confronter dna.
        /// \return retourne vrai si dna est dominé.
        bool isDominated(DNA* dna, std::vector<DNA*> comp);

        /// \fn void solve()
        /// \brief Assure le déroulement de l'évolution génétique.
        void solve();

    private:
        std::vector<DNA*> m_pop;
        std::vector<DNA*> m_pareto_bests;
        int m_pop_size;
        int m_generation;
        int m_mutation_rate;
        Graph* m_structure;

        /// \fn void sortByFront()
        /// \brief Trie les individus par front de domination montant.
        void sortByFront();

        /// \fn void updateFitness(int dom_front)
        /// \brief Met à jour le fitness.
        /// \param dom_front : nombre qui représente le front de domination à considérer.
        void updateFitness(int dom_front);

        /// \fn void manageFrontCut(int n)
        /// \brief Vérifie si un front est coupé et gère les évènements le cas échéant.
        /// \param n : indice auquel le vecteur sera coupé.
        void manageFrontCut(int n);
};



#endif // POPULATION_H
