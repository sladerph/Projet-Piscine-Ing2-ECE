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
    size_t n = std::rand() % m_dna.size();

    DNA* dna = new DNA(structure);

    std::vector<bool> vec;

    for (size_t i = 0; i < m_dna.size(); i++)
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

    for (size_t i = 0; i < m_dna.size(); i++)
        if (m_dna[i] != bdna[i])
            return false;

    return true;
}

DNA::~DNA()
{
    //dtor
}






