#include <iostream>
#include <cstdlib>
#include <time.h>

#include "graph.h"
#include "population.h"

struct Solution
{
    std::vector<bool> vec;
    float cost_a = 0;
    float cost_b = 0;
    bool  dominated = true;
};

int main()
{

    Graph g{};


//    g.create("files/triville.txt", "files/triville_weights_0.txt");
//    g.create("files/broadway.txt","files/broadway_weights_0.txt");
    g.create("files/manhattan.txt", "files/manhattan_weights_0.txt");
/*
    float totalWeight=0.0;
    std::vector<bool> boolVector = g.getPrim(0,&totalWeight);

    for(size_t i = 0; i < boolVector.size(); i++)
    {
        std::cout << boolVector[i];
    }
    std::cout<<std::endl<<"total weight : "<<totalWeight<<std::endl;
    std::cout<<"connexe ? "<< g.connectivityTest(boolVector)<<std::endl;
    std::cout<<"cycle ?   "<< g.testCycle(boolVector)<<std::endl;    /// true = cycle, false = pas de cycle (en partant de 0, donc tester avant si connexe)
*/


    std::vector<std::vector<bool>> poss = combinations(g.getOrdre() - 1, g.getSize(), &g);
    std::vector<Solution> sol;

    for (int i = 0; i < poss.size(); i++)
    {
        if (isCombinationValid(poss[i], &g))
        {
            Solution s;
            s.vec = poss[i];
            sol.push_back(s);
        }
    }

    int nb = 0;

    for (int i = 0; i < sol.size(); i++)
    {
        std::vector<bool> tmp = sol[i].vec;
        std::vector<Connection*> cons = g.getConnections();

        for (int j = 0; j < cons.size(); j++)
        {
            if (tmp[cons[j]->getIndex()])
            {
                std::vector<float> w = cons[j]->getWeights();
                sol[i].cost_a += w[0];
                sol[i].cost_b += w[1];
            }
        }
    }

/*
    for (int i = 0; i < sol.size(); i++)
    {
        for (int j = 0; j < sol.size(); j++)
        {
            if (i != j)
            {
                if (!(sol[i].cost_a < sol[j].cost_a || sol[i].cost_b < sol[j].cost_b))
                {
                    sol[i].dominated = true;
                    break;
                }
            }
        }
        if (!sol[i].dominated) nb++;
    }
*/
/*
    std::sort(sol.begin(), sol.end(), [](Solution a, Solution b) {return a.cost_a < b.cost_a;});
    float mini = 10000;
    for (int i = 0; i < sol.size(); i++)
    {
        if (sol[i].cost_b < mini)
        {
            mini = sol[i].cost_b;
            sol[i].dominated = false;
            nb++;
        }
    }
*/
    std::cout << nb << std::endl;



    //g.evaluation();   ///partie 2
    //g.secondEvaluation();     ///partie 3

    //g.show("output.svg", &boolVector);
    //g.showPrim("output.svg", &boolVector, true);

    ///Population p{1000, &g};

    ///p.solve();

    return 0;
}
