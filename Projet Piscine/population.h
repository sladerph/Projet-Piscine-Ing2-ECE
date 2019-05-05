#ifndef POPULATION_H
#define POPULATION_H

/// \file population.h
/// \brief Regroupe la classe Population et les fonctions intervenants dans l'algorithme g�n�tique.
/// \author Pierre Herduin

#include "dna.h"
#include "utils.h"

#include <windows.h>
#include <sstream>
#include <time.h>

/// \class DNA
/// \brief Inclue ici pour raison de double inclusion.
class DNA;

/// \class Graph
/// \brief Inclue ici pour raison de double inclusion.
class Graph;

/// \class Population
/// \brief Classe qui s'occupe de l'�volution g�n�tique d'un ensemble d'individus.
class Population
{
    public:

        /// \fn Population(int pop_size, Graph* structure, int mutation_rate = 5)
        /// \brief Constructeur.
        /// \param pop_size : le nombre d'individus dans la population.
        /// \param structure : pointeur sur le graphe sur lequel sont construits les individus.
        /// \param mutation_rate : pourcentage de chance de subir une mutation pour une connexion. Par d�faut : 5.
        Population(int pop_size, Graph* structure, int mutation_rate = 5);

        /// \fn ~Population()
        /// \brief Destructeur.
        ~Population();

        /// \fn void evaluateFitness()
        /// \brief Calcul le fitness (score) des individus.
        void evaluateFitness();

        /// \fn void purify()
        /// \brief Elimine les individus non valides (non connexes et de taille diff�rente � ordre - 1).
        void purify();

        /// \fn bool reproduce()
        /// \brief Assure la s�lection et reproduction naturelle.
        /// \return retourne vrai si la reproduction � r�ussie, faux sinon.
        bool reproduce();

        /// \fn void checkDominated()
        /// \brief V�rifie si les individus sont domin�s ou non.
        void checkDominated();

        /// \fn void showNonDominated()
        /// \brief Affiche les individus non domin�s.
        void showNonDominated();

        /// \fn void mutate()
        /// \brief Proc�de aux mutations g�n�tiques al�atoires.
        void mutate();

        /// \fn void checkClones()
        /// \brief Elimine les doublons.
        void checkClones();

        /// \fn void checkPareto()
        /// \brief Met � jour la liste des meilleurs solutions de pareto.
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
        /// \brief V�rifie si un �lement est domin� par un conteneur d'�lements.
        /// \param dna : element � verifier.
        /// \param comp : conteneur d'element contre qui confronter dna.
        /// \return retourne vrai si dna est domin�.
        bool isDominated(DNA* dna, std::vector<DNA*> comp);

        /// \fn void solve()
        /// \brief Assure le d�roulement de l'�volution g�n�tique.
        void solve();

    private:
        std::vector<DNA*> m_pop; ///< Vecteur de DNA* qui repr�sente la population.
        std::vector<DNA*> m_pareto_bests; ///< Vecteur de DNA* qui stocke les meilleures solutions trouv�es.
        int m_pop_size; ///< La taille de la population.
        int m_generation; ///< Le nombre de g�n�rations d�j� �coul�es.
        int m_mutation_rate; ///< Le pourcentage de chance de subir une mutation g�n�tique.
        Graph* m_structure; ///< La structure des individus de la population.

        /// \fn void sortByFront()
        /// \brief Trie les individus par front de domination montant.
        void sortByFront();

        /// \fn void updateFitness(int dom_front)
        /// \brief Met � jour le fitness.
        /// \param dom_front : nombre qui repr�sente le front de domination � consid�rer.
        void updateFitness(int dom_front);

        /// \fn void manageFrontCut(int n)
        /// \brief V�rifie si un front est coup� et g�re les �v�nements le cas �ch�ant.
        /// \param n : indice auquel le vecteur sera coup�.
        void manageFrontCut(int n);
};



#endif // POPULATION_H
