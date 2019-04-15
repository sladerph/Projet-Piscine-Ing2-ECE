#include "graph.h"

Graph::Graph()
{
    //ctor
}

Graph::~Graph()
{
    //dtor
}

bool Graph::create(std::string topology, std::string costs)
{
    std::ifstream file_topo, file_costs;
    std::string line;

    file_topo.open(topology);

    if (!file_topo.is_open())
    {
        std::cout << "Unable to open the file " << topology << std::endl;
        return false;
    }

    getline(file_topo, line);

    m_ordre = std::stoi(line);

    for (int i = 0; i < m_ordre; i++)
    {
        getline(file_topo, line);

        float x, y;

        std::stoi(line);
        x = std::stoi(line);
        y = std::stoi(line);

        m_nodes.push_back(new Node(i, x, y));
    }

    getline(file_topo, line);

    int nb_cons = std::stoi(line);

    for (int i = 0; i < nb_cons; i++)
    {
        getline(file_topo, line);

        int  ia, ib;

        std::stoi(line);
        ia = std::stoi(line);
        ib = std::stoi(line);

        Node* a = getNode(ia);
        Node* b = getNode(ib);

        m_connections.push_back(new Connection(i, a, b));
    }

    file_topo.close();

    file_costs.open(costs);

    if (!file_costs.is_open())
    {
        std::cout << "Unable to open the file " << costs << std::endl;
        return false;
    }

    getline(file_costs, line);

    std::stoi(line);
    int nb_w = std::stoi(line);

    for (int i = 0; i < nb_cons; i++)
    {
        getline(file_costs, line);
        std::stoi(line);

        for (int j = 0; j < nb_w; j++)
        {
            float w = std::stoi(line);

            Connection* c = getConnection(i);

            c->addWeight(w);
        }
    }

    file_costs.close();

    return true;
}

Node* Graph::getNode(int index)
{
    for (int i = 0; i < m_nodes.size(); i++)
    {
        if (m_nodes[i]->getIndex() == index)
        {
            return m_nodes[i];
        }
    }

    return nullptr;
}

Connection* Graph::getConnection(int index)
{
    for (int i = 0; i < m_connections.size(); i++)
    {
        if (m_connections[i]->getIndex() == index)
        {
            return m_connections[i];
        }
    }

    return nullptr;
}










