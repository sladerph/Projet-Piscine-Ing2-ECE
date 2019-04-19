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
    srand(time(NULL));
    char choice = 'y';

    std::cout << std::endl << std::endl;

    std::vector<DNA*> last_pareto;

    int tot = 0;

    while (choice != 'n' && choice != 'N') // User interruption loop.
    {
        int nb = 0;
        bool forced = false;
        bool pareto_changed;

        do
        {
            std::cout << "Starting generation " << m_generation << " !" << std::endl;

            pareto_changed = false;

            evaluateFitness();

            checkClones();
            purify();

            checkDominated();

            checkPareto();

            if (last_pareto.size() > 0)
            {
                if (last_pareto.size() != m_pareto_bests.size())
                    pareto_changed = true;
                else
                {
                    int nb_ok = 0;
                    for (int i = 0; i < last_pareto.size(); i++)
                    {
                        for (int j = 0; j < m_pareto_bests.size(); j++)
                        {
                            if (last_pareto[i]->operator==(m_pareto_bests[j]) == true)
                            {
                                nb_ok++;
                                break;
                            }
                        }
                    }

                    if (nb_ok != last_pareto.size()) pareto_changed = true;
                }
            }

            last_pareto = m_pareto_bests;

            if (pareto_changed)
                showNonDominated();

            if (m_pop.size() > 1)
            {
                if (!reproduce())
                {
                    nb = 10 + 1;
                    forced = true;
                }
                 else
                    mutate();
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
            tot++;
        } while (nb < 100 && (!pareto_changed || tot < 10));

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

void Population::sortByFront()
{
    for (int i = 0; i < m_pop.size() - 1; i++)
    {
        DNA* a = m_pop[i];
        DNA* b = m_pop[i + 1];

        if (a->getFront() > b->getFront())
        {
            DNA* tmp = a;
            a = b;
            b = tmp;
            i = 0;
        }
    }
}

void Population::evaluateDominatedFront()
{
    for (int i = 0; i < m_pop.size(); i++)
    {
        DNA* a = m_pop[i];
        a->setFront(0);

        if (!a->getDominated())
        {
            for (int j = 0; j < m_pop.size(); j++)
            {
                DNA* b = m_pop[j];

                if (a != b)
                    if (a->dominated(b))
                        a->setFront(a->getFront() + 1);
            }
        }
    }
}

bool Population::isDominated(DNA* dna, std::vector<DNA*> comp)
{
    bool dom = false;

    for (int j = 0; j < comp.size(); j++)
    {
        if (dna != comp[j])
        {
            DNA* b = comp[j];

            if (dna->dominated(b))
            {
                dom = true;
                break;
            }
        }
    }

    return dom;
}

void Population::checkPareto()
{
    for (int i = 0; i < m_pop.size(); i++)
        if (m_pop[i]->getDominated() == false)
            m_pareto_bests.push_back(m_pop[i]->clone());

    for (int i = 0; i < m_pareto_bests.size(); i++)
    {
        DNA* a = m_pareto_bests[i];

        for (int j = 0; j < m_pareto_bests.size(); j++)
        {
            DNA* b = m_pareto_bests[j];

            if (a != b && a->operator==(b))
            {
                delete b;
                m_pareto_bests.erase(m_pareto_bests.begin() + j);
                j--;
            }
        }

        if (isDominated(a, m_pareto_bests))
        {
            delete a;
            m_pareto_bests.erase(m_pareto_bests.begin() + i);
            i--;
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

    str = str + "\\Pareto_bests";

    system(str.c_str());

    for (int i = 0; i < m_pop.size(); i++)
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
    path = path + "Pareto_bests/";

    for (int i = 0; i < m_pareto_bests.size(); i++)
    {
        std::vector<bool> cons = m_pareto_bests[i]->getDNA();

        std::stringstream nb;
        nb << i;

        std::stringstream f, a, b;
        f << m_pareto_bests[i]->getFitness();
        a << m_pareto_bests[i]->getSumA();
        b << m_pareto_bests[i]->getSumB();

        std::string name = path + nb.str() + "__" + f.str() + "__" + a.str() + "__" + b.str() + ").svg";

        m_structure->showPrim(name, &cons, false);
    }
    std::cout << std::endl;
}

void Population::checkDominated()
{
    for (size_t i = 0; i < m_pop.size(); i++)
    {
        DNA* a = m_pop[i];

        if (isDominated(a, m_pop))
            m_pop[i]->setDominated(true);
    }
}

void Population::manageFrontCut(int n)
{
    int curr_front = 0;
    bool changed;

    for (int i = 0; i < m_pop.size(); i++)
    {
        DNA* a = m_pop[i];
        changed = false;

        int j;
        for (j = i; j < m_pop.size(); j++)
        {
            DNA* b = m_pop[j];

            if (a->getFront() != b->getFront())
            {
                changed = true;
                curr_front = b->getFront();
                break;
            }
        }

        if (changed)
        {
            int front_size = j - i;
            if (n - i < front_size)
            {
                updateFitness(curr_front - 1);
                std::vector<DNA*> vec;
                for (int k = i; k <= j; k++) vec.push_back(m_pop[k]);

                for (int k = 0; k < vec.size() - 1; k++)
                {
                    DNA* va = vec[k];
                    DNA* vb = vec[k + 1];

                    if (va->getFitness() > vb->getFitness())
                    {
                        DNA* tmp = m_pop[i + k];
                        m_pop[i + k] = m_pop[i + k + 1];
                        m_pop[i + k + 1] = tmp;

                        tmp = vec[k];
                        vec[k] = vb;
                        vec[k + 1] = tmp;
                        k = 0;
                    }
                }
            }
            else
                i = j;
        }
    }
}

bool Population::reproduce()
{
    evaluateDominatedFront();
    sortByFront(); // Sorting the population by ascending domination level.

    int n_cut  = m_pop.size() / 2; // Slice in the middle.
    std::vector<DNA*> parents ;
    std::vector<DNA*> new_ones;
    std::vector<DNA*> mating_pool;

    manageFrontCut(n_cut);

    for (int i = 0; i < n_cut; i++)
        parents.push_back(m_pop[i]);


    float mini = 1000;
    float maxi = 0   ;

    for (int i = 0; i < parents.size(); i++)
    {
        if (parents[i]->getFitness() < mini)
            mini = parents[i]->getFitness();
        if (parents[i]->getFitness() > maxi)
            maxi = parents[i]->getFitness();
    }

    for (int i = 0; i < parents.size(); i++)
    {
        DNA* a = parents[i];

        int n = (int) mapLine(a->getFitness(), mini, 100, maxi, 10);

        if (a->getDominated() == false) n += 20;

        for (int j = 0; j < n; j++)
            mating_pool.push_back(a);
    }

    for (int i = 0; i < m_pop_size; i++)
    {
        int inda = std::rand() % mating_pool.size();
        int indb = std::rand() % mating_pool.size();

        new_ones.push_back(mating_pool[inda]->crossover(mating_pool[indb], m_structure));
    }

    for (size_t i = 0; i < m_pop.size(); i++)
        delete m_pop[i];

    m_pop = new_ones;

    for (int i = 0; i < m_pareto_bests.size(); i++)
        m_pop.push_back(m_pareto_bests[i]->clone());

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

std::vector<DNA*> Population::getClosest(DNA* dna)
{
    std::vector<DNA*> sol;

    DNA* good_a = dna;
    DNA* good_b = dna;

    float da = 100;
    float db = 100;

    for (int i = 0; i < m_pop.size(); i++)
    {
        DNA* a = m_pop[i];

        if (a != dna)
        {
            if (dna->getFront() > a->getFront()) continue;
            if (dna->getFront() < a->getFront()) break;

            float tda = a->getSumA() - dna->getSumA();
            float tdb = a->getSumB() - dna->getSumB();

            if (tda < da && tda > 0)
            {
                da = tda;
                good_a = a;
            }
            if (tdb < db && tdb > 0)
            {
                db = tdb;
                good_b = a;
            }
        }
    }

    if (good_a != dna) sol.push_back(good_a);
    else sol.push_back(nullptr);
    if (good_b != dna) sol.push_back(good_b);
    else sol.push_back(nullptr);

    return sol;
}

void Population::updateFitness(int dom_front)
{
    for (int i = 0; i < m_pop.size(); i++)
    {
        DNA* a = m_pop[i];

        //if (a->getDominated()) return;

        if (a->getFront() < dom_front) continue;
        if (a->getFront() > dom_front) break;

        std::vector<DNA*> closest = getClosest(a);
        DNA* b = closest[0];
        DNA* c = closest[1];

        if (b && c)
        {
            float xa = b->getSumA();
            float ya = b->getSumB();
            float xb = c->getSumA();
            float yb = c->getSumB();
            float w  = std::abs(xb - xa);
            float h  = std::abs(yb - ya);

//            float d  = dist(xa, ya, xb, yb);
            float d  = w + h;
            float n  = mapLine(d, 2, 0, 10, a->getFitness() / 2);
            a->setFitness(a->getFitness() - n);
        }
        else if (b == nullptr && c == nullptr)
        {
            continue;
        }
        else if (b == nullptr)
        {
            float xa = a->getSumA();
            float ya = a->getSumB();
            float xb = c->getSumA();
            float yb = c->getSumB();
            float d  = dist(xa, ya, xb, yb);
            float n  = mapLine(d, 1, 0, 10, a->getFitness() / 2);
            a->setFitness(a->getFitness() - n);
        }
        else if (c == nullptr)
        {
            float xa = a->getSumA();
            float ya = a->getSumB();
            float xb = b->getSumA();
            float yb = b->getSumB();
            float d  = dist(xa, ya, xb, yb);
            float n  = mapLine(d, 1, 0, 10, a->getFitness() / 2);
            a->setFitness(a->getFitness() - n);
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

float dist(float xa, float ya, float xb, float yb)
{
    return std::sqrt(std::pow(xb - xa, 2) + std::pow(yb - ya, 2));
}








