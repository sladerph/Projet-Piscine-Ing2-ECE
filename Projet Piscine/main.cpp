#include <iostream>

#include "graph.h"

int main()
{

    Graph g{};

    g.create("files/broadway.txt", "files/broadway_weights_0.txt");

    return 0;
}
