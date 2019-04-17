#include "graph.h"

Graph::Graph()
{
    //ctor
}

void Graph::show(std::string filename, std::vector<bool>* path)
{
    Svgfile* svg = createSvgfile(filename);

    showConnections(svg, path);
    showNodes(svg);
    showBounds(svg);

    delete svg;
}

void Graph::showBounds(Svgfile* svg)
{
    svg->addLine(0, 0, svg->getWidth(), 0, "black");
    svg->addLine(0, 0, 0, svg->getHeight(), "black");
    svg->addLine(svg->getWidth(), 0, svg->getWidth(), svg->getHeight(), "black");
    svg->addLine(svg->getWidth(), svg->getHeight(), 0, svg->getHeight(), "black");
}

void Graph::showPrim(std::string filename, std::vector<bool>* path)
{
    if (!path) return;

    char choice;
    std::cout << "\n\nDo you want to draw Prim's result on top of the complete graph ? (y / n) : ";
    std::cin  >> choice;

    if (choice == 'n' || choice == 'N')
    {
        Svgfile* svg = createSvgfile(filename);

        for (int i = 0; i < m_connections.size(); i++)
        {
            if (path->operator[](m_connections[i]->getIndex()))
            {
                Node* a = m_connections[i]->getNodeA();
                Node* b = m_connections[i]->getNodeB();

                float xa = a->getX();
                float ya = a->getY();
                float xb = b->getX();
                float yb = b->getY();

                float mx = (xa + xb) / 2;
                float my = (ya + yb) / 2;

                svg->addLine(xa, ya, xb, yb, "green", 3);

                std::vector<float> weights = m_connections[i]->getWeights();

                for (int j = 0; j < weights.size(); j++)
                {
                    svg->addText(mx + j * 20, my, weights[j], "red", "middle");

                    if (j < weights.size() - 1)
                    {
                        svg->addText(mx + j * 10 + 10, my, ";", "red", "middle");
                    }
                }
            }
        }
        showNodes(svg);
        showBounds(svg);

        delete svg;
    }
    else
        show(filename, path);
}

Svgfile* Graph::createSvgfile(std::string filename)
{
    float x_max  = 0;
    float y_max  = 0;

    for (int i = 0; i < m_nodes.size(); i++)
    {
        if (m_nodes[i]->getX() > x_max)
            x_max = m_nodes[i]->getX();

        if (m_nodes[i]->getY() > y_max)
            y_max = m_nodes[i]->getY();
    }

    return new Svgfile(filename, x_max + 2 * XOFFSET, y_max + 2 * YOFFSET);

}

void Graph::showConnections(Svgfile* svg, std::vector<bool>* path) const
{
    for (int i = 0; i < m_connections.size(); i++)
    {
        Node* a = m_connections[i]->getNodeA();
        Node* b = m_connections[i]->getNodeB();

        float xa = a->getX();
        float ya = a->getY();
        float xb = b->getX();
        float yb = b->getY();

        float mx = (xa + xb) / 2;
        float my = (ya + yb) / 2;

        std::vector<float> weights = m_connections[i]->getWeights();

        if (path)
            if (path->operator[](m_connections[i]->getIndex()))
                svg->addLine(xa, ya, xb, yb, "green", 3);
            else
                svg->addLine(xa, ya, xb, yb, "black");
        else
            svg->addLine(xa, ya, xb, yb, "black");

        for (int j = 0; j < weights.size(); j++)
        {
            svg->addText(mx + j * 20, my, weights[j], "red", "middle");

            if (j < weights.size() - 1)
            {
                svg->addText(mx + j * 10 + 10, my, ";", "red", "middle");
            }
        }
    }
}

void Graph::showNodes(Svgfile* svg) const
{
    int radius = 20;

    for (int i = 0; i < m_nodes.size(); i++)
    {
        float x = m_nodes[i]->getX();
        float y = m_nodes[i]->getY();
        int ind = m_nodes[i]->getIndex();

        svg->addDisk(x, y, radius, Svgfile::makeRGB(0, 0, 0));
        svg->addText(x, y, ind, Svgfile::makeRGB(255, 255, 255), "middle");
    }
}

bool Graph::create(std::string topology, std::string costs)
{
    std::ifstream file_topo, file_costs;
    std::string line;
    std::string::size_type sz;

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

        std::stoi(line, &sz);
        line = line.substr(sz);
        x = std::stoi(line, &sz);
        line = line.substr(sz);
        y = std::stoi(line);

        m_nodes.push_back(new Node(i, x, y));
    }

    getline(file_topo, line);

    int nb_cons = std::stoi(line);

    for (int i = 0; i < nb_cons; i++)
    {
        getline(file_topo, line);

        int  ia, ib;

        std::stoi(line, &sz);
        line = line.substr(sz);
        ia = std::stoi(line, &sz);
        line = line.substr(sz);
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

    std::stoi(line, &sz);
    line = line.substr(sz);
    int nb_w = std::stoi(line);

    for (int i = 0; i < nb_cons; i++)
    {
        getline(file_costs, line);
        std::stoi(line, &sz);
        line = line.substr(sz);

        for (int j = 0; j < nb_w; j++)
        {
            float w = std::stof(line, &sz);
            line = line.substr(sz);

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

Graph::~Graph()
{
    //dtor
}

std::vector<bool> Graph::getPrim(int weight, float* totalWeight)
{
    std::vector<bool> shortestPath (m_connections.size(),false);
    std::unordered_set<int> usedIdList;
    std::unordered_set<int> unusedIdList;
    std::vector<Connection*> sortedConnections = sortConnections(m_connections, weight);
    for(int i = 0; i < m_ordre; i++)
        unusedIdList.insert(i);
    unusedIdList.erase(m_nodes[0]->getIndex());
    usedIdList.insert(m_nodes[0]->getIndex());
    while(!unusedIdList.empty())
    {
        for(size_t i = 0; i < sortedConnections.size(); i++)
        {
            if((usedIdList.find(sortedConnections[i]->getNodeA()->getIndex())==usedIdList.end())
               ^(usedIdList.find(sortedConnections[i]->getNodeB()->getIndex())==usedIdList.end()))
            {
                shortestPath[sortedConnections[i]->getIndex()] = true;
                if(usedIdList.find(sortedConnections[i]->getNodeA()->getIndex())==usedIdList.end())
                {
                    unusedIdList.erase(sortedConnections[i]->getNodeA()->getIndex());
                    usedIdList.insert(sortedConnections[i]->getNodeA()->getIndex());
                }
                else
                {
                    unusedIdList.erase(sortedConnections[i]->getNodeB()->getIndex());
                    usedIdList.insert(sortedConnections[i]->getNodeB()->getIndex());
                }
                i=0;
            }
        }
    }
    for(size_t i=0; i < shortestPath.size(); i++)
    {
        if(shortestPath[i])
        {
            *totalWeight+=m_connections[i]->getWeights()[weight];
        }
    }
    return shortestPath;
}


std::vector<Connection*> sortConnections(std::vector<Connection*> connections, int weight)
{
    Connection* temp;
    for(size_t i = 0; i < connections.size()-1; i++)
    {
        if(connections[i]->getWeights()[weight] > connections[i+1]->getWeights()[weight])
        {
            temp = connections[i];
            connections[i]=connections[i+1];
            connections[i+1]=temp;
            i=0;
        }
    }
    std::vector<Connection*> connectionVector;
    for(size_t i = 0; i < connections.size(); i++)
        connectionVector.push_back(connections[i]);
    return connectionVector;
}



float Graph::getDijkstra(int weight)
{
    std::vector<std::pair<float,int>> successorsQueue;
    std::vector<std::pair<float,int>> dijkstraResults;
    std::unordered_set<int> unusedIdList;
    Node* current;
    float currentWeight = 0;
    float totalWeight = 0;
    int j = 0;
    for(j = 0; j < m_ordre; j++)
    {
        for(int i = 0; i < m_ordre; i++)
            unusedIdList.insert(i);
        unusedIdList.erase(j);
        successorsQueue.push_back(std::make_pair(0.0,j));
        currentWeight = 0;
        do
        {
            current=getNode(successorsQueue.begin()->second);
            currentWeight=successorsQueue.begin()->first;
            dijkstraResults.push_back(*successorsQueue.begin());
            successorsQueue.erase(successorsQueue.begin());
            for(auto it : getNeighbours(current,weight))
            {
                it.first+=currentWeight;
                if(unusedIdList.find(it.second)!=unusedIdList.end())
                {
                    successorsQueue.push_back(it);
                    //successorsQueue=sortNodes(successorsQueue);
                    std::sort(successorsQueue.begin(),successorsQueue.end());   ///le sort est peut-être légèrement plus rapide
                    unusedIdList.erase(it.second);
                }
                else
                {
                    for(size_t k = 0; k < successorsQueue.size(); k++)
                    {
                        if(successorsQueue[k].second==it.second)
                        {
                            if(successorsQueue[k].first > it.first)
                            {
                                successorsQueue[k].first=it.first;
                            }
                        }
                    }
                }
            }
        }while(!successorsQueue.empty());

        for(auto it : dijkstraResults)
        {
            totalWeight+=it.first;

        }

        dijkstraResults.clear();
    }
    return totalWeight;
}

std::vector<std::pair<float,int>> sortNodes(std::vector<std::pair<float,int>> Nodes)
{
    std::pair<float,int> temp;
    std::vector<std::pair<float,int>> retour;
    for(size_t i = 0; i < Nodes.size()-1; i++)
    {
        if(Nodes[i].first > Nodes[i+1].first)
        {
            temp = Nodes[i];
            Nodes[i] = Nodes[i+1];
            Nodes[i+1]=temp;
            i=0;
        }
    }
    for(auto it : Nodes)
        retour.push_back(it);
    return retour;
}


std::vector<std::pair<float,int>> Graph::getNeighbours(Node* origin,int weight)
{
    std::vector<std::pair<float,int>> neighboursId;
    for(auto it : m_connections)
    {
        if(it->getNodeA()->getIndex()==origin->getIndex())
            neighboursId.push_back(std::make_pair(it->getWeights()[weight],it->getNodeB()->getIndex()));
        else if (it->getNodeB()->getIndex()==origin->getIndex())
            neighboursId.push_back(std::make_pair(it->getWeights()[weight],it->getNodeA()->getIndex()));
    }
    return neighboursId;
}

bool Graph::connectivityTest(std::vector<bool>connections)
{
    std::unordered_set<int> discoveredList;
    Node* current;
    std::queue<int> nodeQueue;
    nodeQueue.push(m_nodes[0]->getIndex());
    discoveredList.insert(m_nodes[0]->getIndex());
    do
    {
        current=m_nodes[nodeQueue.front()];
        nodeQueue.pop();
        for(auto it : m_connections)
        {
            if(connections[it->getIndex()])
            {
                if((it->getNodeA()->getIndex()==current->getIndex())
                   &&(discoveredList.find(it->getNodeB()->getIndex())==discoveredList.end()))
                {
                    discoveredList.insert(it->getNodeB()->getIndex());
                    nodeQueue.push(it->getNodeB()->getIndex());
                }
                else if(it->getNodeB()->getIndex()==current->getIndex()
                        &&(discoveredList.find(it->getNodeA()->getIndex())==discoveredList.end()))
                {
                    discoveredList.insert(it->getNodeA()->getIndex());
                    nodeQueue.push(it->getNodeA()->getIndex());
                }
            }
        }
    }while(!nodeQueue.empty());

    if(discoveredList.size()<m_ordre)
        return false;
    std::cout<<"connexe :"<<std::endl;
    return true;
}

bool Graph::testCycle(std::vector<bool> connections)
{
    std::unordered_set<int> usedList;
    int test=0;
    for(int i = 0; i < connections.size(); i++)
    {
        test=0;
        if(connections[i])
        {
            if(usedList.find(m_connections[i]->getNodeA()->getIndex())==usedList.end())
            {
                usedList.insert(m_connections[i]->getNodeA()->getIndex());
            }
            else
            {
                test++;
            }
            if(usedList.find(m_connections[i]->getNodeB()->getIndex())==usedList.end())
            {
                usedList.insert(m_connections[i]->getNodeB()->getIndex());
            }
            else
            {
                test++;
            }
            if(test==2)
                return true;
        }
    }
    return false;
}

