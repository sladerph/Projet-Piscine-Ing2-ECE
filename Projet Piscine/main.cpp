#include <iostream>
#include <cstdlib>

#include "graph.h"
#include "population.h"

int main()
{

    Graph g{};

    g.create("files/triville.txt", "files/triville_weights_0.txt");

    float totalWeight=0.0;
    std::vector<bool> boolVector = g.getPrim(0,&totalWeight);

    for(size_t i = 0; i < boolVector.size(); i++)
    {
        std::cout << boolVector[i];
    }
    std::cout<<std::endl<<"total weight : "<<totalWeight<<std::endl;

    //g.show("output.svg", &boolVector);
    //g.showPrim("output.svg", &boolVector, false);

    Population p{100, &g};

    //p.showNonDominated();
    p.solve();

    return 0;
}
