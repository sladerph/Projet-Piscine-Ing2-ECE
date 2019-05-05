/// \file dna.h
/// \brief objet ADN pour l'évolution génétique.
/// \author Pierre Herduin

#include "dna.h"

DNA::DNA(Graph* structure) /// Constructeur.
{
    std::vector<Connection*> cons = structure->getConnections(); /// Récupère les connexions.

    m_size = cons.size();
    m_dominated = false;

    for (int i = 0; i < m_size; i++) /// Parcours les connexions.
    {
        /// Initialise aléatoirement.
        if (std::rand() % 100 < 50)
            m_dna.push_back(true);
        else
            m_dna.push_back(false);
    }

    /// Initialise à 0 les valeurs de fitness et de coûts.
    m_fitness = 0;
    m_sum_cost_a = 0;
    m_sum_cost_b = 0;
}

DNA::DNA() {} /// Constructeur par défaut pour la copie.

DNA* DNA::clone() /// Crée un nouvel objet DNA identique à this.
{
    DNA* d = new DNA(); /// Crée un nouvel objet vide.

    /// Lui assigner nos valeurs.
    d->setDNA(m_dna);
    d->setFitness(m_fitness);
    d->setSumA(m_sum_cost_a);
    d->setSumB(m_sum_cost_b);
    d->setSize(m_size);
    d->setDominated(m_dominated);
    d->setFront(m_front);

    /// Renvoyer l'objet créée.
    return d;
}

bool DNA::dominated(DNA* b) /// Vérifie si this est dominé par b.
{
    /// Si il n'est pas strictement meilleur que b sur au moins un objectif alors il est dominé par b.
    if (m_sum_cost_a < b->getSumA() || m_sum_cost_b < b->getSumB())
        return false;
    return true;
}

void DNA::mutate(int mutation_rate) /// Gère les mutations génétiques.
{
    for (int i = 0; i < m_size; i++) /// Parcours les connexions.
        if (std::rand() % 100 < mutation_rate) /// mutation_rate chances sur 100 de muter.
            m_dna[i] = !m_dna[i];
}

DNA* DNA::crossover(DNA* parent_b, Graph* structure) /// Crée un enfant à partir de this et parent_b.
{
    size_t n = std::rand() % m_dna.size(); /// Endroit de coupure choisi aléatoirement.

    DNA* dna = new DNA(structure); /// L'enfant.

    std::vector<bool> vec;

    for (size_t i = 0; i < m_dna.size(); i++) /// Parcours les connexions.
    {
        /// On assigne à l'enfant les gènes de ses parents.
        if (i < n) /// Si on a pas dépassé n, on prend dans le parent a (this).
            vec.push_back(m_dna[i]);
        else /// Sinon on prend dans le parent b.
            vec.push_back(parent_b->getDNA()[i]);
    }

    /// Assigne à l'enfant le vecteur créée ci-avant.
    dna->setDNA(vec);

    return dna; /// Renvoie l'enfant créée.
}

bool DNA::operator==(DNA* b) /// Opérateur d'égalité pour vérifier si deux objets DNA sont identiques.
{
    if (b == nullptr) return false;
    std::vector<bool> bdna = b->getDNA();

    for (size_t i = 0; i < m_dna.size(); i++)
        if (m_dna[i] != bdna[i]) /// Si les éléments sont différents, alors les objets aussi.
            return false;

    return true;
}

DNA::~DNA() {} /// Destructeur.







