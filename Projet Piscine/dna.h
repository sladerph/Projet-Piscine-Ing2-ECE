#ifndef DNA_H
#define DNA_H

#include "graph.h"
#include "population.h"

#include <vector>

class DNA
{
    public:
        DNA(Graph* structure);
        ~DNA();

        DNA* crossover(DNA* parent_b, Graph* structure);
        void mutate();

        void setFitness(float f) {m_fitness = f;};
        void setSumA(float s) {m_sum_cost_a = s;};
        void setSumB(float s) {m_sum_cost_b = s;};
        void setDNA(std::vector<bool> vec) {m_dna = vec;};
        void setDominated(bool dom)  {m_dominated = dom;};

        std::vector<bool> getDNA() const {return m_dna;};
        float getFitness() const {return m_fitness;};
        float getSumA() const {return m_sum_cost_a;};
        float getSumB() const {return m_sum_cost_b;};
        bool  getDominated() const {return m_dominated;};

    private:
        std::vector<bool> m_dna;
        int m_size;
        float m_sum_cost_a;
        float m_sum_cost_b;
        float m_fitness;
        bool m_dominated;
};

#endif // DNA_H
