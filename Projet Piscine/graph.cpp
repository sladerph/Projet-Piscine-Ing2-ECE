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

void Graph::showPrim(std::string filename, std::vector<bool>* path, bool onTopOfGraph)
{
    if (!path) return;

    if (!onTopOfGraph)
    {
        Svgfile* svg = createSvgfile(filename);

        for (size_t i = 0; i < m_connections.size(); i++)
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

                for (size_t j = 0; j < weights.size(); j++)
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

    for (size_t i = 0; i < m_nodes.size(); i++)
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
    for (size_t i = 0; i < m_connections.size(); i++)
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

        for (size_t j = 0; j < weights.size(); j++)
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

    for (size_t i = 0; i < m_nodes.size(); i++)
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
    m_taille=nb_cons;

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
    for (size_t i = 0; i < m_nodes.size(); i++)
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
    for (size_t i = 0; i < m_connections.size(); i++)
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
    std::vector<bool> shortestPath (m_connections.size(),false);   //d�clare un vecteur de bool�en, et le rempli d'autant de "false" qu'il y a d'ar�tes
    std::unordered_set<int> usedIdList;     //liste des sommets d�couverts
    std::unordered_set<int> unusedIdList;   //liste des sommets non-d�couverts
    std::vector<Connection*> sortedConnections = sortConnections(m_connections, weight);    //tri des ar�tes par un de leur poids, dans l'ordre croissant
    for(int i = 1; i < m_ordre; i++)    //tous les sommets sont non-d�couverts
        unusedIdList.insert(i);
    usedIdList.insert(m_nodes[0]->getIndex());      //initialisation
    while(!unusedIdList.empty())
    {
        for(size_t i = 0; i < sortedConnections.size(); i++)        //algorithme de Prim : l'ar�te de poids minimal qui a un seul de ses sommets dans la
        {                                                           //composante connexe sera choisie et ajout�e
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
            *totalWeight+=m_connections[i]->getWeights()[weight];       //on calcule la somme des poids des ar�tes du graphe couvrant de poids minimal
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

std::vector<Connection*> sortConnectionsByIndex(std::vector<Connection*> connections)
{
    Connection* temp;
    for(size_t i = 0; i < connections.size()-1; i++)
    {
        if(connections[i]->getIndex() > connections[i+1]->getIndex())
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

float Graph::getDijkstra(int weight, std::vector<bool> activeConnections)
{
    std::vector<std::pair<float,int>> successorsVector;     //paires de <poids,id> des sommets d�couverts mais pas marqu�s
    std::vector<std::pair<float,int>> dijkstraResults;
    //paires de <poids,id> repr�sentant les sommets et le poids du cplus court chemin depuis le sommet de base �tudi� et le sommet d'index "id"

    std::unordered_set<int> unusedIdList;   //liste des id des sommets non-d�couverts
    Node* current;
    float currentWeight = 0;
    float totalWeight = 0;
    int j = 0;
    for(j = 0; j < m_ordre; j++)
    {
        for(int i = 0; i < m_ordre; i++)
            unusedIdList.insert(i);
        unusedIdList.erase(j);
        successorsVector.push_back(std::make_pair(0.0,j));
        currentWeight = 0;
        do
        {
            current=getNode(successorsVector.begin()->second);
            currentWeight=successorsVector.begin()->first;
            dijkstraResults.push_back(*successorsVector.begin());
            successorsVector.erase(successorsVector.begin());
            for(auto it : getNeighbours(current,weight,activeConnections))
            {
                it.first+=currentWeight;
                if(unusedIdList.find(it.second)!=unusedIdList.end())
                {
                    successorsVector.push_back(it);
                    //successorsVector=sortNodes(successorsVector);
                    std::sort(successorsVector.begin(),successorsVector.end());   ///le sort est peut-�tre l�g�rement plus rapide
                    unusedIdList.erase(it.second);
                }
                else
                {
                    for(size_t k = 0; k < successorsVector.size(); k++)
                    {
                        if(successorsVector[k].second==it.second)
                        {
                            if(successorsVector[k].first > it.first)
                            {
                                successorsVector[k].first=it.first;
                            }
                        }
                    }
                }
            }
        }while(!successorsVector.empty());

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


std::vector<std::pair<float,int>> Graph::getNeighbours(Node* origin,int weight,std::vector<bool> activeConnections)
{
    std::vector<std::pair<float,int>> neighboursId;
    for(auto it : m_connections)
    {
        if(activeConnections[it->getIndex()])
        {
            if(it->getNodeA()->getIndex()==origin->getIndex())
                neighboursId.push_back(std::make_pair(it->getWeights()[weight],it->getNodeB()->getIndex()));
            else if (it->getNodeB()->getIndex()==origin->getIndex())
                neighboursId.push_back(std::make_pair(it->getWeights()[weight],it->getNodeA()->getIndex()));
        }
    }
    return neighboursId;
}

bool Graph::connectivityTest(std::vector<bool>connections)
{
    m_connections = sortConnectionsByIndex(m_connections);
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

    if(discoveredList.size()<(size_t)m_ordre)   //tester si tous les sommets ont �t� d�couverts (cast de m_ordre en size_t pour l'homog�n�it�)
        return false;
    return true;
}

bool Graph::testCycle(std::vector<bool> connections)
{
    int nbConnections=0;
    {
        for (size_t i = 0; i < connections.size(); i++)
        {
            if(connections[i])
                nbConnections++;
        }
    }
    if(connectivityTest(connections)&&(nbConnections==(m_ordre-1)))
        return false;
    return true;
}

float Graph::weightsSum(std::vector<bool> connections, int weight)
{
    float totalWeight=0;
    for(size_t i = 0; i < connections.size(); i++)
    {
        if(connections[i])
            totalWeight+=m_connections[i]->getWeights()[weight];
    }
    return totalWeight;
}

///additionneur 1 bit :

bool add_1bit(bool& r_sortie ,bool r_entree,bool a, bool b)
{

            bool sol;

            if(a==false&&b==false&&r_entree==false)
            {
                sol=false;
                r_sortie=false;
            }
             if(a==false&&b==false&&r_entree==true)
            {
                sol=true;
                r_sortie=false;
            }
             if(a==false&&b==true&&r_entree==false)
            {
                sol=true;
                r_sortie=false;
            }
             if(a==false&&b==true&&r_entree==true)
            {
                sol=false;
                r_sortie=true;
            }
             if(a==true&&b==false&&r_entree==false)
            {
                sol=true;
                r_sortie=false;
            }
             if(a==true&&b==false&&r_entree==true)
            {
                sol=false;
                r_sortie=true;
            }
             if(a==true&&b==true&&r_entree==false)
            {
                sol=false;
                r_sortie=true;
            }
             if(a==true&&b==true&&r_entree==true)
            {
                sol=true;
                r_sortie=true;
            }

            return sol;
}


///fonction qui �num�re toutes les solutions existantes :

std::vector < std::vector<bool> > Graph ::  enumeration ()
{
    std::vector < std::vector<bool> >  sol_exist;
    std :: vector<bool> zero;

    ///on initialise toutes les solutions avec autant de z�ro que d'arretes :
    for(int k=0; k<m_taille; k++)
    {
        zero.push_back(false);
    }
    ///on cr�e 2^taille solutions

    for (int l = 0; l< pow(2,m_taille);l++ )
    {
         sol_exist.push_back(zero);
    }

    ///on creer le nombre 1  :
    std::vector <bool> one;
    for(int k=0; k<m_taille; k++)
    {
        one.push_back(false);
    }
    one[m_taille-1]=true;

    ///on parcours toute les solutions apr�s la premi�re(celle ci reste a 0)
    for (int i = 1; i< pow(2,m_taille);i++ )
    {
       ///A l'aide d'un additionneur 1 bit, on cr�e un additionneur m_taille bits
       ///Ainsi la solution d'apr�s est la somme de la soluton d'avant et du nombre 1
       bool r_entree=false;
       bool r_sortie;
       for (int j=(m_taille-1);j>=0;j--)
       {
           sol_exist[i][j]=add_1bit(r_sortie,r_entree,sol_exist[i-1][j],one[j]);
           r_entree=r_sortie;
       }

    }

       return sol_exist;
}

///fonction qui selectionne les solutions admissibles parmis les solutions existantes :

std::vector < std:: vector<bool> >  Graph :: filtrage ()
{
    std::vector < std:: vector<bool> > solExist= this->enumeration();
    std::vector < std::vector<bool> >  solAdmis;
    bool arreteOk=false;
    bool connexe;
    std::vector <int> sommetSelect;


    for (size_t i=0; i<solExist.size();i++) ///on parcours le vecteur des solutions existantes
    {
        int select=0;
        arreteOk=false;

        for(size_t j=0;j<solExist[i].size();j++) ///on parcours la solution existante et on compte
        {
            if(solExist[i][j]) ///si une arrete est selectionee
            {
                select++; ///on augmente select
            }

        }
        ///on a ainsi le nombre d'arretes selectionees

        ///on regarde si la solution existante poss�de ordre-1 arretes :

        if( select == (m_ordre-1))
        {
            arreteOk=true;  ///on a donc une condition verifi�
        }

        ///On va maintenant regarder si la solution existante est connexe :
        ///pour cela on fait appel a la fonction testconnectivity

        connexe=connectivityTest(solExist[i]);

       ///si les deux conditions sont v�rifi�es : connectivit� + non cycle
        if(connexe==true&&arreteOk==true)
        {
            ///alors la solution est admissible, on la rajoute donc dans le vecteur de solutions admissibles
            solAdmis.push_back(solExist[i]);
        }



    }
    return solAdmis;

}


///fonction qui trie les solutions domin�es et non domin�es selon les 2 objectifs et les affiche :

void Graph ::  evaluation ()
{
    ///on r�cup�re le vecteur de solutions admissibles :

    std::vector < std::vector<bool> > solAdmis=this->filtrage();

    ///vecteurs de float correspondants aux sommes des poids1 pour somme1 et poids2 pour somme2 :
    ///pour chaque solutions correspondantes du vecteur solutions admissibles

    std :: vector <float> somme1 (solAdmis.size(),0);
    std :: vector <float> somme2 (solAdmis.size(),0);

    ///vecteur de booleen qui indique pour chaque solution si elle est domin�e ou non
    std :: vector<bool> dominee (solAdmis.size(),false);

    ///on effectue la somme des poids des arretes pour chaque solution :
    ///on parcours toutes les solutions :

    for (size_t j=0; j<solAdmis.size();j++)
    {
        ///pour chaque solutions, on parcours ses arretes
        for(int i =0; i<m_taille;i++)
        {
            ///si les arretes sont selection�es dans la solution
            if(solAdmis[j][i]==true)
            {
                ///on rajoute leur poids aux sommes
                somme1[j]=somme1[j]+m_connections[m_taille-1-i]->getWeights()[0];

                somme2[j]=somme2[j]+m_connections[m_taille-1-i]->getWeights()[1];


            }
        }
        std::cout<<"sommet : ";
        for(auto it : solAdmis[j])
            std::cout<<it;
        std::cout<<"   "<<somme2[j]<<std::endl;
    }

    ///Maintenant que nous avons nos sommes, nous allons regarder si les solutions sont domin�es ou non :

    for (size_t l =0; l<solAdmis.size();l++) ///on parcours toutes les solutions
    {

       for (size_t k =0; k<solAdmis.size();k++) ///chacune d'elle est compar� au reste des solutions
       {
            if (l!=k) ///ne pas comparer une solution avec elle m�me
            {
                if(somme1[k]<=somme1[l] && somme2[k]<=somme2[l])
                {
                    dominee[l]=true; ///elle est dominee
                    k=solAdmis.size()-1; ///on arrete la boucle car on a deja prouv� qu'elle est dominee
                }
            }
       }
    }


    ///On va maintenant pouvoir les afficher sur un diapgramme 2D :

    ///On cr�e un autre svg :
    Svgfile* svgg= new Svgfile ("outpuut.svg", 1000,800);


    ///On parcours toutes les solutions admises et on les dessine, soit en vert pour les solutions non domin�es
    ///soit en rouge pour les solutions domin�es

    ///Probl�mes pour l'affichage des axes
    //svgg->addLine(0,400,0,100,"black",10);
    //svgg->addLine(0,400,300,400,"black",10);
    //svgg->addGrid(100,1,"black");
    for(size_t l=0; l<solAdmis.size();l++)
    {
        if(dominee[l]==false)
        {std::cout<<somme1[l]<<"  "<<somme2[l]<<std::endl;
          svgg->addDisk(somme1[l]*10,400-(somme2[l])*10,5,"green");
        }
        else
        {std::cout<<somme1[l]<<"  "<<somme2[l]<<std::endl;
            svgg->addDisk(somme1[l]*10,400-(somme2[l])*10,5,"red");
        }

    }

    //rajouter les axes plus tard ?  poid1 en abscisse poids2 en ordonn�e




}

