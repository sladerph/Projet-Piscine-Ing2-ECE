/// \file dna.h
/// \brief objet ADN pour l'�volution g�n�tique.
/// \author Pierre Herduin

#include "dna.h"

DNA::DNA(Graph* structure)
{
    std::vector<Connection*> cons = structure->getConnections(); /// R�cup�re les connexions.

    m_size = cons.size();
    m_dominated = false;

    for (int i = 0; i < m_size; i++) /// Parcours les connexions.
    {
        /// Initialise al�atoirement.
        if (std::rand() % 100 < 50)
            m_dna.push_back(true);
        else
            m_dna.push_back(false);
    }

    /// Initialise � 0 les valeurs de fitness et de co�ts.
    m_fitness = 0;
    m_sum_cost_a = 0;
    m_sum_cost_b = 0;
}

DNA::DNA() {}

DNA* DNA::clone()
{
    DNA* d = new DNA(); /// Cr�e un nouvel objet vide.

    /// Lui assigner nos valeurs.
    d->setDNA(m_dna);
    d->setFitness(m_fitness);
    d->setSumA(m_sum_cost_a);
    d->setSumB(m_sum_cost_b);
    d->setSize(m_size);
    d->setDominated(m_dominated);
    d->setFront(m_front);

    /// Renvoyer l'objet cr��e.
    return d;
}

bool DNA::dominated(DNA* b)
{
    /// Si il n'est pas strictement meilleur que b sur au moins un objectif alors il est domin� par b.
    if (m_sum_cost_a < b->getSumA() || m_sum_cost_b < b->getSumB())
        return false;
    return true;
}

void DNA::mutate(int mutation_rate)
{
    for (int i = 0; i < m_size; i++) /// Parcours les connexions.
        if (std::rand() % 100 < mutation_rate) /// mutation_rate chances sur 100 de muter.
            m_dna[i] = !m_dna[i];
}

DNA* DNA::crossover(DNA* parent_b, Graph* structure)
{
    size_t n = std::rand() % m_dna.size(); /// Endroit de coupure choisi al�atoirement.

    DNA* dna = new DNA(structure); /// L'enfant.

    std::vector<bool> vec;

    for (size_t i = 0; i < m_dna.size(); i++) /// Parcours les connexions.
    {
        /// On assigne � l'enfant les g�nes de ses parents.
        if (i < n) /// Si on a pas d�pass� n, on prend dans le parent a (this).
            vec.push_back(m_dna[i]);
        else /// Sinon on prend dans le parent b.
            vec.push_back(parent_b->getDNA()[i]);
    }

    /// Assigne � l'enfant le vecteur cr��e ci-avant.
    dna->setDNA(vec);

    return dna; /// Renvoie l'enfant cr��e.
}

bool DNA::operator==(const DNA* b)
{
    std::vector<bool> bdna = b->getDNA();

    for (size_t i = 0; i < m_dna.size(); i++)
        if (m_dna[i] != bdna[i]) /// Si les �l�ments sont diff�rents, alors les objets aussi.
            return false;

    return true;
}

DNA::~DNA() {}







