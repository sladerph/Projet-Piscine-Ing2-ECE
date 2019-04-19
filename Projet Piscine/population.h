#ifndef POPULATION_H
#define POPULATION_H

/// \file
/// \brief
/// \author

#define MUTATION_RATE 5

#include "dna.h"

#include <windows.h>
#include <sstream>
#include <cmath>

class DNA;

class Population
{
    public:
        Population(int pop_size, Graph* structure);
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
        Graph* m_structure;

        void sortByFront();
        void updateFitness(int dom_front);
        void manageFrontCut(int n);
};

float mapLine(float val, float xa, float ya, float xb, float yb);
float dist(float xa, float ya, float xb, float yb);

#endif // POPULATION_H
