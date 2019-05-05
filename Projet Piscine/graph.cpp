/// \file graph.cpp
/// \brief regroupe les diff�rentes fonction agissant sur le graphe et permettant de l'afficher ainsi que les fonctions accessoires qu'elles utilisent
/// \author Pierre Herduin, M�lodie Damas, Simon jolly

#include "graph.h"


Graph::Graph() /// Constructeur par d�faut.
{}

Graph::Graph(std::vector<Node*>nodes, std::vector<Connection*>connections, int ordre, double taille) /// Constructeur avec param�tres.
        :m_nodes{nodes},m_connections{connections},m_ordre{ordre},m_taille{taille}
{

}

void Graph::show(std::string filename, std::vector<bool>* path) /// G�re l'affichage.
{
    Svgfile* svg = createSvgfile(filename); /// Cr�ation du fichier svg.

    showConnections(svg, path); /// Affichage des connectipns.
    showNodes(svg); /// Affichage des noeuds.
    showBounds(svg); /// Affichage des bords.

    delete svg; /// D�truit l'instance du fichier pour le fermer et terminer son �dition.
}

void Graph::showBounds(Svgfile* svg) /// Affichage des bords.
{
    svg->addLine(0, 0, svg->getWidth(), 0, "black");
    svg->addLine(0, 0, 0, svg->getHeight(), "black");
    svg->addLine(svg->getWidth(), 0, svg->getWidth(), svg->getHeight(), "black");
    svg->addLine(svg->getWidth(), svg->getHeight(), 0, svg->getHeight(), "black");
}

void Graph::showPrim(std::string filename, std::vector<bool>* path, bool onTopOfGraph) /// Affichage d'un graphe partiel.
{
    if (!path) return;

    if (!onTopOfGraph) /// Affichage du graphe partiel seul.
    {
        Svgfile* svg = createSvgfile(filename);

        for (size_t i = 0; i < m_connections.size(); ++i)
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

                for (size_t j = 0; j < weights.size(); ++j)
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
    else /// Affichage du graphe partiel par dessus le graphe original.
        show(filename, path);
}

Svgfile* Graph::createSvgfile(std::string filename) /// Cr�ation d'un fichier svg.
{
    float x_max  = 0;
    float y_max  = 0;

    for (size_t i = 0; i < m_nodes.size(); ++i) /// Calcul des dimensions du graphe.
    {
        if (m_nodes[i]->getX() > x_max)
            x_max = m_nodes[i]->getX();

        if (m_nodes[i]->getY() > y_max)
            y_max = m_nodes[i]->getY();
    }

    return new Svgfile(filename, x_max + 2 * XOFFSET, y_max + 2 * YOFFSET);

}

void Graph::showConnections(Svgfile* svg, std::vector<bool>* path) const /// Affichage des connections.
{
    for (size_t i = 0; i < m_connections.size(); ++i)
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

        if (path) /// Eventuel affichage de l'ar�te du sous graphe si il est fournis.
            if (path->operator[](m_connections[i]->getIndex()))
                svg->addLine(xa, ya, xb, yb, "green", 3);
            else
                svg->addLine(xa, ya, xb, yb, "black");
        else
            svg->addLine(xa, ya, xb, yb, "black");

        for (size_t j = 0; j < weights.size(); ++j)
        {
            svg->addText(mx + j * 20, my, weights[j], "red", "middle");

            if (j < weights.size() - 1)
            {
                svg->addText(mx + j * 10 + 10, my, ";", "red", "middle");
            }
        }
    }
}

void Graph::showNodes(Svgfile* svg) const /// Affichage des noeuds.
{
    int radius = 20;

    for (size_t i = 0; i < m_nodes.size(); ++i)
    {
        float x = m_nodes[i]->getX();
        float y = m_nodes[i]->getY();
        int ind = m_nodes[i]->getIndex();

        svg->addDisk(x, y, radius, Svgfile::makeRGB(0, 0, 0));
        svg->addText(x, y, ind, Svgfile::makeRGB(255, 255, 255), "middle");
    }
}

bool Graph::create(std::string topology, std::string costs) /// Cr�ation d'un graphe � partir de deux fichiers texte.
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

    for (int i = 0; i < m_ordre; ++i)
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

    for (int i = 0; i < nb_cons; ++i)
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

Node* Graph::getNode(int index) /// Getter pour r�cup�rer le noeud avec un certain index.
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

Connection* Graph::getConnection(int index) /// Getter pour r�cup�rer l'ar�te avec un certain index.
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

Graph::~Graph() /// Destructeur.
{
}

std::vector<bool> Graph::getPrim(int weight, float* totalWeight) /// Ex�cute l'algorithme de Prim sur le graphe.
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

bool connectionsComparatorWeight0(const Connection* lhs,const Connection* rhs) /// Comparateur de poids 0 pour les ar�tes.
{
    return lhs->getWeights()[0] < rhs->getWeights()[0];
}

bool connectionsComparatorWeight1(const Connection* lhs,const Connection* rhs) /// Comparateur de poids 1 pour les ar�tes.
{
    return lhs->getWeights()[1] < rhs->getWeights()[1];
}

std::vector<Connection*> sortConnections(std::vector<Connection*> connections, int weight) /// Trie des ar�tes.
{
    if(weight==0)
    {
        std::sort(connections.begin(),connections.end(),connectionsComparatorWeight0);
    }
    else if(weight==1)
    {
        std::sort(connections.begin(),connections.end(),connectionsComparatorWeight1);
    }
    return connections;
}

bool connectionsComparator(const Connection* lhs, const Connection* rhs) /// Comparateur d'index des ar�tes.
   {return lhs->getIndex() < rhs->getIndex();}

std::vector<Connection*> sortConnectionsByIndex(std::vector<Connection*> connections) /// Trie les ar�tes par index.
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

float Graph::getDijkstra(int weight, std::vector<bool> activeConnections) /// Ex�cute l'algorithme de Dijkstra.
{   /// Le vecteur de bool est re�u � l'envers
    std::vector<std::pair<float,int>> successorsVector;     ///<paires de <poids,id> des sommets d�couverts mais pas marqu�s
    std::vector<std::pair<float,int>> dijkstraResults;      ///<paires de <poids,id> repr�sentant les sommets et le poids du cplus court chemin depuis le sommet de base �tudi� et le sommet d'index "id"

    std::unordered_set<int> unusedIdList;   ///<liste des id des sommets non-d�couverts
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



std::vector<std::pair<float,int>> sortNodes(std::vector<std::pair<float,int>> Nodes) /// Trie les noeuds.
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


std::vector<std::pair<float,int>> Graph::getNeighbours(Node* origin,int weight,std::vector<bool> activeConnections) /// Cherche les voisins d'un noeud.
{
    std::vector<std::pair<float,int>> neighboursId;
    for(auto it : m_connections)
    {
        if(activeConnections[(it->getIndex())])
        {
            if(it->getNodeA()->getIndex()==origin->getIndex())
                neighboursId.push_back(std::make_pair(it->getWeights()[weight],it->getNodeB()->getIndex()));
            else if (it->getNodeB()->getIndex()==origin->getIndex())
                neighboursId.push_back(std::make_pair(it->getWeights()[weight],it->getNodeA()->getIndex()));
        }
    }
    return neighboursId;
}

bool Graph::connectivityTest(std::vector<bool>connections) /// V�rifie si le graphe est connexe.
{
    std::vector<bool> discoveredList(m_ordre, false);
    int nb = 1;
    Node* current;
    std::queue<int> nodeQueue;
    nodeQueue.push(m_nodes[0]->getIndex());
    discoveredList[m_nodes[0]->getIndex()] = true;
    do
    {
        current = m_nodes[nodeQueue.front()];
        nodeQueue.pop();
        for(auto it : m_connections)
        {
            if (connections[it->getIndex()])
            {
                Node* a = it->getNodeA();
                Node* b = it->getNodeB();
                int inda = a->getIndex();
                int indb = b->getIndex();
                if(a == current && !discoveredList[indb])
                {
                    discoveredList[indb] = true;
                    nodeQueue.push(indb);
                    nb++;
                }
                else if (b == current && !discoveredList[inda])
                {
                    discoveredList[inda] = true;
                    nodeQueue.push(inda);
                    nb++;
                }
                if (nb == m_ordre) ///tester si tous les sommets ont �t� d�couverts.
                    return true;
            }
        }
    } while (!nodeQueue.empty());

    return false;
}

bool Graph::testCycle(std::vector<bool> connections) /// V�rifie si le graphe poss�de des cycles.
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

float Graph::weightsSum(std::vector<bool> connections, int weight) /// Calcul la somme des poids du sous graphe pass� en param�tre.
{
    float totalWeight=0;
    for(size_t i = 0; i < connections.size(); i++)
    {
        if(connections[i])
            totalWeight+=m_connections[i]->getWeights()[weight];
    }
    return totalWeight;
}

bool add_1bit(bool a, bool b, bool& c) /// Additionneur 1 bit.
{
    bool r = (!a && !b && c) || (!a && b && !c) || (a && b && c) || (a && !b && !c);
         c = (b && c) || (a && b) || (a && c);
    return r;
}


///fonction qui �num�re toutes les solutions existantes :

std::vector<std::vector<bool>> Graph::enumeration()
{
    std::vector<bool> zero(m_taille, false);  ///on initialise toutes les solutions avec autant de z�ro que d'arretes :
    std::vector<std::vector<bool>> sol_exist(pow(2, m_taille), zero);    ///on cr�e 2^taille solutions
    std::vector<std::vector<bool>> retour;

    ///on creer le nombre 1  :
    std::vector<bool> one(m_taille - 1, false);
    one.push_back(true);
    int target_size = m_ordre - 1;

    ///on parcours toute les solutions apr�s la premi�re(celle ci reste � 0)
    for (int i = 1; i < pow(2, m_taille); i++)
    {
       ///A l'aide d'un additionneur 1 bit, on cr�e un additionneur m_taille bits
       ///Ainsi la solution d'apr�s est la somme de la soluton d'avant et du nombre 1
       bool r = false;

       for (int j = m_taille - 1; j >= 0; j--)
           sol_exist[i][j] = add_1bit(sol_exist[i - 1][j], one[j], r);

       if (howManyTrue(sol_exist[i]) == target_size)   ///on ne retourne que les solutions qui ont le nombre d'ar�tes suffisant pour �tre connexe et sans cycle
            retour.push_back(sol_exist[i]);
    }
    return retour;
}


std::vector<std::vector<bool>>  Graph::filtrage()
{
/// Fonction qui selectionne les solutions admissibles parmis les solutions existantes :
    std::vector<std::vector<bool>> solExist = enumeration();

    clock_t ms = clock()  ;
    float   s  = ms / 1000;
    float   mn = s  / 60  ;

    std::cout<<"fin d'enumeration : time : " << ms << "ms ==> " << s << "s ==> " << mn << "min !" << std::endl;

    std::vector<std::vector<bool>> solAdmis;
    std::vector <int> sommetSelect;

    for (size_t i=0; i<solExist.size();++i) ///on parcours le vecteur des solutions existantes
    {
        ///On va maintenant regarder si la solution existante est connexe :
        ///pour cela on fait appel a la fonction testconnectivity

       ///si la condition est v�rifi�e : connectivit�
        if(connectivityTest(solExist[i])/*&&arreteOk==true*/)
        ///On va maintenant regarder si la solution existante est connexe :
        ///pour cela on fait appel a la fonction testconnectivity
        if(connectivityTest(solExist[i]))
        {
            ///alors la solution est admissible, on la rajoute donc dans le vecteur de solutions admissibles
            solAdmis.push_back(solExist[i]);
        }
    }
    return solAdmis;
}

void Graph::reset() /// R�initialise un graphe comme si l'objet venait d'�tre instanci�.
{
    for (int i = 0; i < m_nodes.size(); i++)
        delete m_nodes[i];
    for (int i = 0; i < m_connections.size(); i++)
        delete m_connections[i];
    m_nodes.clear();
    m_connections.clear();
    m_ordre = 0;
    m_taille = 0;
}

/// Fonction qui trie les solutions domin�es et non domin�es selon les 2 objectifs et les affiche :

void Graph::evaluation()
{
    ///on r�cup�re le vecteur de solutions admissibles :

    std::vector<std::vector<bool>> solAdmis = filtrage();

    ///vecteurs de float correspondants aux sommes des poids1 pour somme1 et poids2 pour somme2 :
    ///pour chaque solutions correspondantes du vecteur solutions admissibles

    std::vector<float> somme1(solAdmis.size(), 0);
    std::vector<float> somme2(solAdmis.size(), 0);

    ///vecteur de booleen qui indique pour chaque solution si elle est domin� ou non
    std::vector<bool> dominee(solAdmis.size(), false);

    float x_min = 1000;
    float x_max = 0;
    float y_min = 1000;
    float y_max = 0;

    ///on effectue la somme des poids des arretes pour chaque solution :

    ///on parcours toutes les solutions :

    for (size_t j = 0; j < solAdmis.size(); j++)
    {
        ///pour chaque solutions, on parcours ses arretes
        for(int i = 0; i < m_taille; i++)
        {
            ///si les arretes sont selection�es dans la solution
            if(solAdmis[j][i])
            {
                ///on rajoute leur poids aux sommes
                std::vector<float> w = m_connections[m_taille - 1 - i]->getWeights();
                somme1[j] += w[0];
                somme2[j] += w[1];

            }
        }
    }

    ///Maintenant que nous avons nos sommes, nous allons regarder si les solutions sont domin�es ou non :
    for (int l =0; l<solAdmis.size();++l)
    {   ///on parcours toutes les solutions
        if (somme1[l] < x_min) x_min = somme1[l];
        if (somme1[l] > x_max) x_max = somme1[l];
        if (somme2[l] < y_min) y_min = somme2[l];
        if (somme2[l] > y_max) y_max = somme2[l];
    }

    ///Maintenant que nous avons nos sommes, nous allons regarder si les solutions sont domin�es ou non :

    for (size_t l = 0; l < solAdmis.size(); l++) ///on parcours toutes les solutions
    {
       for (size_t k = 0; k < solAdmis.size(); k++) ///chacune d'elle est compar� au reste des solutions
       {
            if (l!=k) /// ne pas comparer une solution avec elle m�me ni avec une solution domin�e
            {
                if(!(somme1[k] > somme1[l] || somme2[k] > somme2[l]))
                {
                    dominee[l] = true; ///elle est dominee
                    break; ///on arrete la boucle car on a deja prouv� qu'elle est dominee
                }
            }
       }
    }

    ///On va maintenant pouvoir les afficher sur un diagramme 2D :
    ///On cr�e un autre svg :
    Svgfile* svgg = new Svgfile ("outpuut.svg", 1000, 800);


    ///On parcours toutes les solutions admises et on les dessine, soit en vert pour les solutions non domin�es
    ///soit en rouge pour les solutions domin�es

    for(size_t l = 0; l < solAdmis.size(); l++)
    {
        float x = mapLine(somme1[l], x_min, 100, x_max, 900);
        float y = mapLine(somme2[l], y_min, 700, y_max, 100);

        if(!dominee[l])
          svgg->addDisk(x, y, 5, "green");
        else
            svgg->addDisk(x, y, 5, "red");
    }

    /// Affichage des axes
    svgg->addLine(10, 750, 10 , 50 , "black", 2);
    svgg->addLine(10, 750, 950, 750, "black", 2);
    svgg->addTriangle(950, 745, 950, 755, 970, 750, "black", 2, "black");
    svgg->addTriangle(5, 50, 15, 50, 10, 30, "black", 2, "black");

    delete svgg;
}

void Graph::secondEvaluation() /// Fonction d'�valuation des solutions trouv�es pour la deuxi�me partie.
{
    std::vector<std::vector<bool>> admissibles = secondfiltrage();
    std :: vector <float> somme1 (admissibles.size(),0);
    std :: vector <float> somme2(admissibles.size(),0);

    ///vecteur de booleen qui indique pour chaque solution si elle est domin� ou non
    std :: vector<bool> dominee (admissibles.size(),false);
    for (size_t j=0; j<admissibles.size();++j)
    {
        ///pour chaque solutions, on parcours ses arretes
        for(int i =0; i<m_taille;++i)
        {
            ///si les arretes sont selection�es dans la solution
            if(admissibles[j][i]==true)
            {
                ///on rajoute leur poids aux sommes
                somme1[j]+=+m_connections[m_taille-1-i]->getWeights()[0];
            }
        }
        somme2[j]=getDijkstra(1,admissibles[j]);
    }

    ///Maintenant que nous avons nos sommes, nous allons regarder si les solutions sont domin�es ou non :

    for (size_t l =0; l<admissibles.size();++l) ///on parcours toutes les solutions
    {

       for (size_t k =0; k<admissibles.size();++k) ///chacune d'elle est compar� au reste des solutions
       {
            if (l!=k) ///ne pas comparer une solution avec elle m�me
            {
                if(somme1[k]<=somme1[l] && somme2[k]<=somme2[l])
                {
                    dominee[l]=true; ///elle est dominee
                    k=admissibles.size()-1; ///on arrete la boucle car on a deja prouv� qu'elle est dominee
                }
            }
       }
    }


    ///On va maintenant pouvoir les afficher sur un diapgramme 2D :

    ///On cr�e un autre svg :
    Svgfile* svgg= new Svgfile ("outpuuut.svg", 1000,800);


    ///On parcours toutes les solutions admises et on les dessine, soit en vert pour les solutions non domin�es
    ///soit en rouge pour les solutions domin�es

    ///Probl�mes pour l'affichage des axes
    //svgg->addLine(0,400,0,100,"black",10);
    //svgg->addLine(0,400,300,400,"black",10);
    for(size_t l=0; l<admissibles.size();++l)
    {
        if(dominee[l]==false)
        {///std::cout<<"non dominee  "<<somme1[l]<<"  "<<somme2[l]<<std::endl;
          svgg->addDisk(somme1[l]*10,400-(somme2[l])*2,5,"green");
        }
        else
        {///std::cout<<"dominee  "<<somme1[l]<<"  "<<somme2[l]<<std::endl;
            svgg->addDisk(somme1[l]*10,400-(somme2[l])*2,5,"red");
        }

    }

    //rajouter les axes plus tard ?  poid1 en abscisse poids2 en ordonn�e
}

std::vector<std ::vector<bool>> Graph::secondfiltrage () /// Filtrage pour la deuxi�me partie.
{
    std::vector < std:: vector<bool> > solExist= this->secondEnumeration();
    std::vector<std::vector<bool>> admissibles;
    for(size_t i = 0; i < solExist.size(); ++i)
    {
        if(connectivityTest(solExist[i]))
            admissibles.push_back(solExist[i]);
    }
    return admissibles;
}

std::vector < std::vector<bool> > Graph ::  secondEnumeration () /// Enum�rations des solutions potentielles pour la partie 2.
{
    std :: vector<bool> zero (m_taille,false);  ///on initialise toutes les solutions avec autant de z�ro que d'arretes :
    std::vector < std::vector<bool> >  sol_exist (pow(2,m_taille),zero);    ///on cr�e 2^taille solutions
    std::vector < std::vector<bool> > retour;
    ///on creer le nombre 1  :
    std::vector <bool> one (m_taille-1,false);
    one.push_back(true);

    ///on parcours toute les solutions apr�s la premi�re(celle ci reste a 0)
    for (int i = 1; i< pow(2,m_taille);++i )
    {
       ///A l'aide d'un additionneur 1 bit, on cr�e un additionneur m_taille bits
       ///Ainsi la solution d'apr�s est la somme de la soluton d'avant et du nombre 1
       bool r = false;
       for (int j = (m_taille-1); j >= 0; --j)
           sol_exist[i][j]=add_1bit(sol_exist[i - 1][j], one[j], r);

       if(howManyTrue(sol_exist[i]) >= (m_ordre-1))   ///on ne retourne que les solutions qui ont le nombre d'ar�tes suffisant pour �tre connexe
            retour.push_back(sol_exist[i]);
    }
       return retour;
}

int howManyTrue(std::vector<bool>& subject) /// Renvoie le nombre d'�lements true dans le vecteur subject.
{
    int n = 0;
    for(int i = 0; i < subject.size(); i++)
        if (subject[i]) n++;

    return n;
}


std::vector<std::vector<bool>> combinations(int k, int n, Graph* g) /// Calcule les combinaisons de k parmis n.
{
    std::vector<std::vector<bool>> sol;
    std::vector<int> vec;

    for (int i = 0; i < k; i++) vec.push_back(i);

    int index = k - 1;
    int nb    = countCombinations(k, n);

    sol.push_back(tradIntToBool(vec, g));

    while (sol.size() < nb)
    {
        int comp = (n - 1) - (k - index - 1);

        while (vec[index] < comp)
        {
            vec[index]++;
            sol.push_back(tradIntToBool(vec, g));
        }
        index--;
        vec[index]++;

        bool changed = false;
        for (int i = 0; i < k - index - 1; i++)
        {
            if (vec[index + i + 1] != vec[index + i] + 1 && vec[index + i] + 1 < n - (k - (index + i) - 1))
            {
                vec[index + i + 1] = vec[index + i] + 1;
                changed = true;
            }
        }
        if (changed)
            index = k - 1;
        sol.push_back(tradIntToBool(vec, g));
    }

    return sol;
}

std::vector<bool> tradIntToBool(std::vector<int> vec, Graph* g) /// Traduit un vecteur de int en vecteur de bool adapt� au graphe.
{
    std::vector<bool> cons(g->getSize(), false);

    for (int i = 0; i < vec.size(); i++)
        cons[vec[i]] = true;
    return cons;
}

void Graph::bruteForcePareto(std::string filename) /// Trouve les solutions de pareto par la m�thode brute force.
{                                                  /// Echoue sur les graphes trop grands, par manque de m�moire.
    float t, dt, start;
    dt = clock();
    start = dt;
    std::sort(m_connections.begin(), m_connections.end(), &connectionsComparator);
    std::vector<std::vector<bool>> poss = combinations(m_ordre - 1, m_taille, this);

    t = clock();
    std::cout << "All Possibilities : " << (t - dt) / 1000 << "s" << std::endl << std::endl;
    dt = t;

    std::vector<Solution> sol;
    int n = 0;
    float x_min = 1000;
    float x_max = 0;
    float y_min = 1000;
    float y_max = 0;

    for (int i = 0; i < poss.size(); i++)
    {
        if (connectivityTest(poss[i]))
        {
            Solution s;
            s.vec = poss[i];

            int nb = 0;
            for (int j = 0; j < m_connections.size(); j++)
            {
                if (s.vec[j]) //m_connections[j]->getIndex()])
                {
                    std::vector<float> w = m_connections[j]->getWeights();
                    s.cost_a += w[0];
                    s.cost_b += w[1];
                    nb++;
                    if (nb == m_ordre - 1) break;
                }
            }
            sol.push_back(s);
            n++;

            if (s.cost_a < x_min) x_min = s.cost_a;
            if (s.cost_b < y_min) y_min = s.cost_b;
            if (s.cost_a > x_max) x_max = s.cost_a;
            if (s.cost_b > y_max) y_max = s.cost_b;
        }
    }

    t = clock();
    std::cout << n << " elements detected as solutions + calc costs : " << (t - dt) / 1000 << "s" << std::endl << std::endl;
    dt = t;

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
    }

    t = clock();
    std::cout << "Domination : " << (t - dt   ) / 1000 << "s" << std::endl << std::endl;
    std::cout << "Total : "      << (t - start) / 1000 << "s" << std::endl << std::endl;
    dt = t;

     ///On va maintenant pouvoir les afficher sur un diagramme 2D :
    ///On cr�e un autre svg :
    Svgfile* svg = new Svgfile (filename, 1000, 800);

    std::cout << std::endl << std::endl;


    ///On parcours toutes les solutions admises et on les dessine, soit en vert pour les solutions non domin�es
    ///soit en rouge pour les solutions domin�es

    for(size_t l = 0; l < sol.size(); l++)
    {
        float x = mapLine(sol[l].cost_a, x_min, 100, x_max, 900);
        float y = mapLine(sol[l].cost_b, y_min, 700, y_max, 100);

        if(!sol[l].dominated)
            svg->addDisk(x, y, 5, "green");
        else
            svg->addDisk(x, y, 5, "red");
    }

    /// Affichage des axes
    svg->addLine(10, 750, 10 , 50 , "black", 2);
    svg->addLine(10, 750, 950, 750, "black", 2);
    svg->addTriangle(950, 745, 950, 755, 970, 750, "black", 2, "black");
    svg->addTriangle(5, 50, 15, 50, 10, 30, "black", 2, "black");

    delete svg;
}

void Graph::bruteForceParetoConsideringCycles(std::string filename) /// Calcule les optimum de pareto en autorisant les cycles avec la m�thode brute force.
{
    float t, dt, start;

    std::sort(m_connections.begin(), m_connections.end(), &connectionsComparator);
    std::vector<std::vector<bool>> poss;

    dt = clock();
    start = dt;
    for(int i = (m_ordre - 1); i <=  m_taille ; i++ )
    {
        std::vector<std::vector<bool>> v = combinations(i, m_taille, this);
        for(auto it : v)
            poss.push_back(it);
    }

     t = clock();
    std::cout << "All Possibilities : " << t / 1000 << "s" << std::endl;
    dt = t;

    std::vector<Solution> sol;
    int n = 0;
    float x_min = 1000;
    float x_max = 0;
    float y_min = 1000;
    float y_max = 0;

    for (int i = 0; i < poss.size(); i++)
    {
        if (connectivityTest(poss[i]))
        {
            Solution s;
            s.vec = poss[i];

            for (int j = 0; j < m_connections.size(); j++)
            {
                if (s.vec[j])
                {
                    std::vector<float> w = m_connections[j]->getWeights();
                    s.cost_a += w[0];
                }
            }
            s.cost_b=getDijkstra(1,s.vec);
            sol.push_back(s);
            n++;

            if (s.cost_a < x_min) x_min = s.cost_a;
            if (s.cost_b < y_min) y_min = s.cost_b;
            if (s.cost_a > x_max) x_max = s.cost_a;
            if (s.cost_b > y_max) y_max = s.cost_b;
        }
    }

    t = clock();
    std::cout << n << " elements valid + calc costs : " << (t - dt) / 1000 << "s" << std::endl;
    dt = t;

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
    }

    t = clock();
    std::cout << "Domination : " << (t - dt   ) / 1000 << "s" << std::endl;
    std::cout << "Total : "      << (t - start) / 1000 << "s" << std::endl;
    dt = t;

     ///On va maintenant pouvoir les afficher sur un diagramme 2D :
    ///On cr�e un autre svg :
    Svgfile* svg = new Svgfile (filename, 1000, 800);


    ///On parcours toutes les solutions admises et on les dessine, soit en vert pour les solutions non domin�es
    ///soit en rouge pour les solutions domin�es
    for(size_t l = 0; l < sol.size(); l++)
    {
        float x = mapLine(sol[l].cost_a, x_min, 100, x_max, 900);
        float y = mapLine(sol[l].cost_b, y_min, 700, y_max, 100);  //std::abs(400 - somme2[l] * 10);

        if(!sol[l].dominated)
            svg->addDisk(x, y, 5, "green");
        else
            svg->addDisk(x, y, 5, "red");
    }

    /// Affichage des axes
    svg->addLine(10, 750, 10 , 50 , "black", 2);
    svg->addLine(10, 750, 950, 750, "black", 2);
    svg->addTriangle(950, 745, 950, 755, 970, 750, "black", 2, "black");
    svg->addTriangle(5, 50, 15, 50, 10, 30, "black", 2, "black");

    delete svg;
}

Graph createManually() /// Cr�e un graphe manuellement.
{                      /// Fonction inachev�e.
    std::vector<Node*> nodes;
    std::vector<Connection*> connections;
    int ordre=0;
    double taille=0.0;
    int nbWeights=0;


    bool fini=false;
    int choix=-1;

    float x=-1,y=-1;

    std::vector<float> weights;
    Node* nodeA=nullptr;
    int indexA=-1;
    Node* nodeB=nullptr;
    int indexB=-1;
    float tempWeight =0;

    Graph temoin{};

    do
    {
        std::cout<<"Combien y aura-t-il de poids par aretes ?"<<std::endl;
        std::cin>>nbWeights;
        if(!(nbWeights>=0 && nbWeights < std::numeric_limits<int>::max()))
            std::cout<<std::endl<<"Erreur de saisie : reessayez"<<std::endl;
    }while(!(nbWeights>=0 && nbWeights < std::numeric_limits<int>::max()));

    do
    {
        do
        {
            std::cout<<"Que souhaitez vous faire ?"<<std::endl<<"0) - Abandonner"<<std::endl<<"1) - Terminer et creer le graphe"<<std::endl<<"2) - Ajouter un sommet au graphe"
                <<std::endl<<"3) - Ajouter une arete au graphe"<<std::endl<<"4) - Afficher la liste des sommets"<<std::endl<<"5) - Afficher la liste des aretes"<<std::endl<<std::endl;
            std::cin>>choix;
            if(!(choix >= 0 && choix <=3))
                std::cout<<std::endl<<"Erreur de saisie : reessayez"<<std::endl;
            if(choix==3 && connections.size()==countCombinations(2,nodes.size()))   ///On check si des ar�tes non existantes pourraient �tre ajout�es
            {
                std::cout<<std::endl<<"Il n'y a pas assez de sommets pour ajouter des nouvelles aretes : Veuillez commencer par ajouter des sommets"<<std::endl;
                choix=-1;
            }
        }while(!(choix >= 0 && choix <=5));
        switch(choix)
        {
            case 0 :
                std::cout<<std::endl<<"Abandon de la creation du graphe"<<std::endl<<std::endl;
                return temoin;
                break;
            case 1 :
                std::cout<<std::endl<<"Creation du graphe"<<std::endl;
                fini=true;
                break;
            case 2 :
                x=-1;
                y=-1;
                do
                {
                    std::cout<<std::endl<<"Saisir l'abscisse du sommet"<<std::endl;
                    std::cin>>x;
                    if(!(x>=0 && x < std::numeric_limits<float>::max()))
                        std::cout<<std::endl<<"Erreur de saisie : reessayez"<<std::endl;
                }while(!(x>=0 && x < std::numeric_limits<float>::max()));
                do
                {
                    std::cout<<std::endl<<"Saisir l'ordonnee du sommet"<<std::endl;
                    std::cin>>y;
                    if(!(y>=0 && y < std::numeric_limits<float>::max()))
                        std::cout<<std::endl<<"Erreur de saisie : reessayez"<<std::endl;
                }while(!(y>=0 && y < std::numeric_limits<float>::max()));
                nodes.push_back(new Node{(int) nodes.size(),x,y});
                break;
            case 3 :    ///ajouter une ar�te au graphe
                weights.clear();
                nodeA=nullptr;
                indexA=-1;
                nodeB=nullptr;
                indexB=-1;

                do
                {
                    std::cout<<std::endl<<"Quel est l'index du sommet A ?"<<std::endl;
                    std::cin>>indexA;
                    std::cout<<std::endl<<"Quel est l'index du sommet B ?"<<std::endl;
                    std::cin>>indexB;
                    if(!(indexA>=0 && indexA < nodes.size()))
                        std::cout<<"Le sommet d'indice "<<indexA<<" n'est pas enregistre : veuillez resaisir les sommets"<<std::endl;
                    if(!(indexB>=0 && indexB < nodes.size()))
                        std::cout<<"Le sommet d'indice "<<indexB<<" n'est pas enregistre : veuillez resaisir les sommets"<<std::endl;
                    if(indexA==indexB)
                        std::cout<<"Les sommets sont les memes : Veuillez reessayer"<<std::endl;
                }while(!(indexA>=0 && indexA < nodes.size() && indexB >=0 && indexB < nodes.size() && indexA!=indexB));
                nodeA = nodes[indexA];
                nodeB = nodes[indexB];

                for(int k =0; k<nbWeights; k++)
                {
                    tempWeight=0;
                    do
                    {
                        std::cout<<"Quel est son poids d'indice "<<k<<" ?"<<std::endl;
                        std::cin>>tempWeight;
                        if(!(tempWeight>=0 && tempWeight<std::numeric_limits<float>::max()))
                            std::cout<<"Erreur de saisie : ressayez"<<std::endl;
                    }while(!(tempWeight>=0 && tempWeight<std::numeric_limits<float>::max()));
                }
                connections.push_back(new Connection{(int) connections.size(),nodeA,nodeB,weights});
                weights.push_back(tempWeight);
                break;
            case 4 :
                for(auto it : nodes)
                    std::cout<<"sommet "<<it->getIndex()<<" : x = "<<it->getX()<<"  y = "<<it->getY()<<std::endl;
                std::cout<<std::endl;
                break;
            case 5 :
                for(auto it : connections)
                {
                    std::cout<<"arete "<<it->getIndex()<<" : sommet A = "<<it->getNodeA()->getIndex()<<"  sommet B = "<<it->getNodeB()->getIndex()<<std::endl<<"      ";
                    int indexpoids=0;
                    for(auto other: it->getWeights())
                    {
                        std::cout<<"poids d'indice "<<indexpoids<<" : "<<other;
                        indexpoids++;
                    }
                    std::cout<<std::endl;
                }
                std::cout<<std::endl;
                break;
        }
    }while(!fini);
    ordre=nodes.size();
    taille=connections.size();

    Graph g{nodes,connections,ordre,taille};
    std::cout<<"Le graphe a ete successivement cree !"<<std::endl;

    return g;
}
