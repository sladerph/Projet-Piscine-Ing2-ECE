#ifndef POPULATION_H
#define POPULATION_H

#define MUTATION_RATE 5

#include "dna.h"

#include <windows.h>
#include <sstream>

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

        void solve();

    private:
        std::vector<DNA*> m_pop;
        int m_pop_size;
        int m_generation;
        Graph* m_structure;
};

float mapLine(float val, float xa, float ya, float xb, float yb);

#endif // POPULATION_H
