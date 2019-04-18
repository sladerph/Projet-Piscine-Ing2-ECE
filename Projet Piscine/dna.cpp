#include "dna.h"

DNA::DNA(Graph* structure)
{
    std::vector<Connection*> cons = structure->getConnections();

    m_size = cons.size();
    m_dominated = false;

    for (int i = 0; i < m_size; i++)
    {
        if (std::rand() % 100 < 50)
            m_dna.push_back(true);
        else
            m_dna.push_back(false);
    }

    m_fitness = 0;
    m_sum_cost_a = 0;
    m_sum_cost_b = 0;
}

DNA::DNA() {}

DNA* DNA::clone()
{
    DNA* d = new DNA();

    d->setDNA(m_dna);
    d->setFitness(m_fitness);
    d->setSumA(m_sum_cost_a);
    d->setSumB(m_sum_cost_b);
    d->setSize(m_size);
    d->setDominated(m_dominated);

    return d;
}

void DNA::mutate()
{
    for (int i = 0; i < m_size; i++)
    {
        if (std::rand() % 100 < MUTATION_RATE)
        {
            m_dna[i] = !m_dna[i];
        }
    }
}

DNA* DNA::crossover(DNA* parent_b, Graph* structure)
{
    int n = std::rand() % m_dna.size();

    DNA* dna = new DNA(structure);

    std::vector<bool> vec;

    for (int i = 0; i < m_dna.size(); i++)
    {
        if (i < n)
            vec.push_back(m_dna[i]);
        else
            vec.push_back(parent_b->getDNA()[i]);
    }

    dna->setDNA(vec);

    return dna;
}

bool DNA::operator==(const DNA* b)
{
    std::vector<bool> bdna = b->getDNA();

    for (int i = 0; i < m_dna.size(); i++)
        if (m_dna[i] != bdna[i])
            return false;

    return true;
}

DNA::~DNA()
{
    //dtor
}







