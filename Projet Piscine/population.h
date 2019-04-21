#ifndef POPULATION_H
#define POPULATION_H

/// \file
/// \brief
/// \author

#include "dna.h"
#include "utils.h"

#include <windows.h>
#include <sstream>
#include <time.h>

class DNA;
class Graph;

class Population
{
    public:
        Population(int pop_size, Graph* structure, int mutation_rate = 5);
        ~Population();

        void evaluateFitness();
        void purify();
        bool reproduce();
        void checkDominated();
        void showNonDominated();
        void mutate();
        void checkClones();
        void checkPareto();

        std::vector<DNA*> getClosest(DNA* dna);

        void evaluateDominatedFront();

        bool isDominated(DNA* dna, std::vector<DNA*> comp);

        void solve();

    private:
        std::vector<DNA*> m_pop;
        std::vector<DNA*> m_pareto_bests;
        int m_pop_size;
        int m_generation;
        int m_mutation_rate;
        Graph* m_structure;

        void sortByFront();
        void updateFitness(int dom_front);
        void manageFrontCut(int n);
};



#endif // POPULATION_H
