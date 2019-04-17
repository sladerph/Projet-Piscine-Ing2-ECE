#include <iostream>
#include <cstdlib>

#include "graph.h"
#include "population.h"

int main()
{

    Graph g{};

    //g.create("files/triville.txt", "files/triville_weights_0.txt");
    g.create("files/manhattan.txt", "files/manhattan_weights_0.txt");



    float total = g.getDijkstra(0);
    std::cout<<"poids total de tous les plus courts chemins : "<<total<<std::endl;

    float totalWeight=0.0;
    std::vector<bool> boolVector = g.getPrim(0,&totalWeight);

    for(size_t i = 0; i < boolVector.size(); i++)
    {
        std::cout << boolVector[i];
    }
    std::cout<<std::endl<<"total weight : "<<totalWeight<<std::endl;
    std::cout<<"connexe ? "<< g.connectivityTest(boolVector)<<std::endl;
    std::cout<<"cycle ?   "<< g.testCycle(boolVector)<<std::endl;    /// true = cycle, false = pas de cycle (en partant de 0, donc tester avant si connexe)
    //g.show("output.svg", &boolVector);
//    g.showPrim("output.svg", &boolVector, true);

    Population p{1000, &g};

    //p.showNonDominated();
    p.solve();

    return 0;
}
