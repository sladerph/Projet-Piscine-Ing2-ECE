#include "population.h"

Population::Population(int pop_size, Graph* structure)
{
    m_pop_size   = pop_size ;
    m_structure  = structure;
    m_generation = 0;

    for (int i = 0; i < pop_size; i++)
        m_pop.push_back(new DNA(structure));
}

void Population::solve()
{
    char choice = 'y';

    std::cout << std::endl << std::endl;

    while (choice != 'n' && choice != 'N') // User interruption loop.
    {
        int nb = 0;
        bool forced = false;

        while (nb < 10)
        {
            std::cout << "Starting generation " << m_generation << " !" << std::endl;

            evaluateFitness();

            checkClones();
            purify();

            if (m_pop.size() > 0)
                checkDominated();

            showNonDominated();

            if (m_pop.size() > 1)
            {
                if (!reproduce())
                {
                    nb = 10 + 1;
                    forced = true;
                }
                 else
                {
                    mutate();
                }
            }
            else
            {
                for (size_t i = 0; i < m_pop.size(); i++)
                {
                    delete m_pop[i];
                    m_pop.erase(m_pop.begin() + i);
                    i--;
                }
                for (int i = 0; i < m_pop_size; i++)
                    m_pop.push_back(new DNA(m_structure));
                std::cout << "No correct individual found, re-starting at random." << std::endl;
            }

            std::cout << "End of generation " << m_generation << " !" << std::endl;

            m_generation++;
            nb++;
        }

        if (forced)
        {
            std::cout << "Evolution can't be continued !" << std::endl;
            choice = 'n';
        }
        else
        {
            std::cout << "Do you want to continue the evolution ? (y/n) : ";
            std::cin  >> choice;
        }
    }
}

void Population::checkClones()
{
    for (size_t i = 0; i < m_pop.size(); i++)
    {
        DNA* me = m_pop[i];

        if (me->getDominated() == false)
        {
            for (size_t j = 0; j < m_pop.size(); j++)
            {
                DNA* you = m_pop[j];

                if (me != you && me->operator==(you))
                {
                    /*
                    delete you;
                    you = nullptr;
                    m_pop.erase(m_pop.begin() + j);
                    j--;
                    */
                    you->setDominated(true);
                    //std::cout << "Eliminate clone" << std::endl;
                }
            }
        }
    }
}

void Population::mutate()
{
    for (size_t i = 0; i < m_pop.size(); i++)
        m_pop[i]->mutate();
}

void Population::showNonDominated()
{
    std::stringstream ss;
    ss << m_generation;

    std::string str = "mkdir \"Genetic outputs\\" + ss.str();

    system(str.c_str());

    // New folder created.

    std::string path = "Genetic outputs/" + ss.str() + "/";

    for (size_t i = 0; i < m_pop.size(); i++)
    {
        if (m_pop[i]->getDominated() == false)
        {
            std::stringstream nb;
            nb << i;

            std::vector<bool> cons = m_pop[i]->getDNA();

            std::stringstream f, a, b;
            f << m_pop[i]->getFitness();
            a << m_pop[i]->getSumA();
            b << m_pop[i]->getSumB();

            std::string name = path + nb.str() + "__" + f.str() + "__" + a.str() + "__" + b.str() + ").svg";

//            m_structure->showPrim(path + nb.str() + ".svg", &cons, false);
            m_structure->showPrim(name, &cons, false);
        }
    }
    std::cout << std::endl;
}

void Population::checkDominated()
{
    for (size_t i = 0; i < m_pop.size(); i++)
    {
        DNA* a = m_pop[i];
        bool oka = true;
        bool okb = true;

        for (size_t j = 0; j < m_pop.size(); j++)
        {
            if (a != m_pop[j] && (oka || okb))
            {
                DNA* b = m_pop[j];

                if (b->getSumA() < a->getSumA())
                {
                    oka = false;
                }
                if (b->getSumB() < a->getSumB())
                {
                    okb = false;
                }
            }
        }

        if (!oka && !okb)
        {
            m_pop[i]->setDominated(true);
        }
    }
}

bool Population::reproduce()
{
    float mini = 1000000;
    float maxi = 0;
    DNA* min_dna = nullptr;

    for (size_t i = 0; i < m_pop.size(); i++)
    {
        if (m_pop[i]->getFitness() < mini)
        {
            mini = m_pop[i]->getFitness();
            min_dna = m_pop[i];
        }
        if (m_pop[i]->getFitness() > maxi) maxi = m_pop[i]->getFitness();
    }

    std::vector<DNA*> mating_pool;

    for (size_t i = 0; i < m_pop.size(); i++)
    {
        int nb = mapLine(m_pop[i]->getFitness(), mini, 100, maxi, 1);

        if (m_pop[i]->getDominated() == false) nb *= 2;

        for (int j = 0; j < nb; j++)
            mating_pool.push_back(m_pop[i]);
    }

    if (mating_pool.size() == 0) return false;

    std::vector<DNA*> new_ones;

    for (int i = 0; i < m_pop_size; i++)
    {
        int inda = std::rand() % mating_pool.size();
        int indb = std::rand() % mating_pool.size();

        new_ones.push_back(mating_pool[inda]->crossover(mating_pool[indb], m_structure));
    }

    delete new_ones[0];
    new_ones[0] = min_dna;

    for (size_t i = 0; i < m_pop.size(); i++)
        if (m_pop[i] != min_dna)
            delete m_pop[i];

    m_pop = new_ones;

    return true;
}

void Population::purify()
{
    for (size_t i = 0; i < m_pop.size(); i++)
    {
        int nb = 0;

        std::vector<bool> choices = m_pop[i]->getDNA();

        for (size_t j = 0; j < choices.size(); j++)
            if (choices[j]) nb++;

        if (nb != m_structure->getOrdre() - 1 || !m_structure->connectivityTest(choices))
        {
            delete m_pop[i];
            m_pop.erase(m_pop.begin() + i);
            i--;
        }
        else if (m_structure->testCycle(choices))
        {
            //m_pop[i]->setDominated(true);
        }
    }
}

void Population::evaluateFitness()
{
    for (size_t i = 0; i < m_pop.size(); i++)
    {
        DNA* dna = m_pop[i];

        std::vector<bool> choices = dna->getDNA();
        std::vector<Connection*> cons = m_structure->getConnections();

        float sum_a = 0;
        float sum_b = 0;

        for (size_t j = 0; j < cons.size(); j++)
        {
            if (choices[cons[j]->getIndex()]) // Chosen.
            {
                sum_a += cons[j]->getWeights()[0];
                sum_b += cons[j]->getWeights()[1];
            }
        }

        dna->setFitness(sum_a + sum_b);
        dna->setSumA(sum_a);
        dna->setSumB(sum_b);
    }
}

Population::~Population()
{
    //dtor
}

float mapLine(float val, float xa, float ya, float xb, float yb)
{
    float m = (yb - ya) / (xb - xa);
    float p = ya - m * xa;

    return m * val + p;
}




