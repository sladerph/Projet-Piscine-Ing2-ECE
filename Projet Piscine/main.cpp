#include <iostream>

#include "graph.h"

int main()
{

    Graph g{};

    g.create("files/broadway.txt", "files/broadway_weights_0.txt");

    g.show();

    float totalWeight=0.0;
    std::vector<bool> boolVector = g.getPrim(0,&totalWeight);
    for(size_t i = 0; i < boolVector.size(); i++)
    {
        std::cout<<boolVector[i];
    }
    std::cout<<std::endl<<"total weight : "<<totalWeight<<std::endl;


    return 0;
}
