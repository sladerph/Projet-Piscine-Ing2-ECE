#include "utils.h"

/// \file utils.cpp
/// \brief diverses fonctions utilitaires
/// \author Pierre Herduin

float mapLine(float val, float xa, float ya, float xb, float yb)
{
    ///On va chercher les param�tres de la fonction affine d�crivant la droite passant par a et b
    float m = (yb - ya) / (xb - xa);        ///On calcule le coefficient directeur
    float p = ya - m * xa;          ///On calcule l'ordonn�e � l'origine

    return m * val + p; ///on retourne l'ordonn�e du point d'abscisse val
}

float dist(float xa, float ya, float xb, float yb)
{
    return std::sqrt(std::pow(xb - xa, 2) + std::pow(yb - ya, 2));      ///distance euclidienne
}

float factorial(float nb)
{
    if (nb < 0) return 0;       /// on n'appliquera pas la fonction factorielle aux nombres n�gatifs
    if( nb ==0 ) return 1;      /// cas particulier : 0! = 1

    float r = nb;

    for (int i = nb - 1; i > 1; i--)    ///calcul de l'image du param�tre en entr�e par la fonction factorielle
        r *= i;
    return r;
}

float countCombinations(float k, float n)
{
    return factorial(n) / (factorial(k) * factorial(n - k));
}

/// Vide tampon clavier - Code du professeur.
void videCin()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void setConsoleColor(int text_color, int background_color)      ///R�gle les couleurs de police et d'arri�re plan dans la console
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, background_color * 16 + text_color);
}

void menu() ///Menu d'accueil du programme, qui permet d'utiliser les diff�rentes fonctionnalit� impl�ment�es
{
    int choice;
    int w_index;
    setConsoleColor(LIGHT_MAGENTA);     ///On r�gle la couleur de la police au fur et � mesure du programme
    std::cout << std::endl << "Welcome into the Graph analysis tool !" << std::endl << std::endl << std::endl;

    std::vector<FileInfo> files = findGraphFiles(); ///On r�cup�re tous les fichiers contenant les information des graphes � charger

    setConsoleColor(LIGHT_RED);
    do  ///On fait choisir � l'utilisateur un fichier de graphe � charger parmi la liste
    {
        std::cout << "First of all, you have to open a graph among the followings : " << std::endl << std::endl;
        setConsoleColor(GREEN);
        for (int i = 0; i < files.size(); i++)
            std::cout << " - " << i + 1 << " --> " << files[i].name.substr(0, files[i].name.find(".txt")) << std::endl;
        setConsoleColor(LIGHT_RED);
        std::cout << std::endl << "Make your choice : ";
        std::cin  >> choice;
        std::cout << std::endl;
        videCin();      ///On prend soin de vider le tampon clavier au fuir et � mesure du programme
    } while (choice <= 0 || choice > files.size());     ///On blinde la saisie du num�ro du graphe � charger

    FileInfo selected_file = files[choice - 1];     ///on d�clare une structure FileInfo avec les fichiers dugraphe choisi

    setConsoleColor(LIGHT_RED);
    do      ///On demande � l'utilisateur de choisir le fichier de poids qu'il souhaite appliquer au graphe charg�
    {
        std::cout << "Now, please chose the weights of the graph among the followings : " << std::endl << std::endl;
        setConsoleColor(GREEN);
        for (int i = 0; i < selected_file.weights.size(); i++)
            std::cout << " - " << i + 1 << " --> " << selected_file.weights[i].substr(0, selected_file.weights[i].find(".txt")) << std::endl;
        setConsoleColor(LIGHT_RED);
        std::cout << std::endl << "Make your choice : ";
        std::cin  >> choice;
        std::cout << std::endl;
        videCin();
    } while (choice <= 0 || choice > selected_file.weights.size());     ///On blinde la saisie du num�ro du fichier de poids � charger

    setConsoleColor(LIGHT_CYAN);
    std::cout << "Opening the graph " << selected_file.name.substr(0, selected_file.name.find(".txt")) << " with ";     ///On r�capitule pour l'utilisateur les choix de graphes et de poids qu'il a fait
    std::cout << selected_file.weights[choice - 1].substr(0, selected_file.weights[choice - 1].find(".txt"));

    std::cout << std::endl << std::endl << std::endl;

    w_index = choice - 1;       ///on d�termine l'index du fichier de poids dans la structure pr�c�demment cr��e

    Graph g;
    if (!g.create("files/" + selected_file.name, "files/" + selected_file.weights[choice - 1]))     ///On charge le graphe � partir des fichiers choisis et on v�rifie que le chargement s'est d�roul� correctement
    {
        setConsoleColor(LIGHT_RED);
        std::cout << "FATAL ERROR -- UNABLE TO OPEN THE FILE" << std::endl << std::endl;
        setConsoleColor(WHITE);
        exit(-1);
    }

    while (true)
    {
        setConsoleColor(LIGHT_RED);
        std::cout << "Please choose between the following options :" << std::endl << std::endl;     ///Affichage du menu des diff�rentes options propos�es par le programme pour travailler avec le graphe
        setConsoleColor(GREEN);
        std::cout << "  - 0 --> Quit." << std::endl << std::endl;
        std::cout << "  - 1 --> Show the graph." << std::endl << std::endl;
        std::cout << "  - 2 --> Change the graph." << std::endl << std::endl;
        std::cout << "  - 3 --> Find minimum spanning tree (Prim's algorithm)." << std::endl << std::endl;
        std::cout << "  - 4 --> Test the connexity of the graph." << std::endl << std::endl;
        std::cout << "  - 5 --> Dual objective spanning tree optimization (brute force) (\"Partie 2\")." << std::endl << std::endl;
        std::cout << "  - 6 --> Dual objective optimization (cost / distance) (brute force) (\"Partie 3\")." << std::endl << std::endl;
        std::cout << "  - 7 --> Dual objective spanning tree optimization (genetic algorithm)." << std::endl << std::endl;
        std::cout << "  - 8 --> Create a graph manually." << std::endl << std::endl;
        setConsoleColor(LIGHT_RED);
        std::cout << "Make your choice : ";     ///on demande � l'utilisateur de choisir parmi les options propos�es
        std::cin  >> choice;
        std::cout << std::endl << std::endl << std::endl;
        videCin();

        switch (choice)     ///On d�taille ensuite l'action du programme dans chaque cas pouvant �tre choisi par l'utilisateur
        {
            case 0:         ///1er cas : on sort du menu
                setConsoleColor(WHITE);
                exit(0);
            case 1:         ///2e cas : On dessine le graphe sur un fichier svg
            {
                std::string filename;

                setConsoleColor(CYAN);
                std::cout << "Enter the name of the file (without '.svg') : ";
                std::cin  >> filename;
                std::cout << std::endl << std::endl;

                filename = filename + ".svg";

                g.show(filename);

                std::cout << std::endl << std::endl;
                break;
            }
            case 2:
            {
                files = findGraphFiles();   ///3e cas : on charge un autre graphe parmi ceux propos�s, par la m�me m�thode que pr�c�demment

                setConsoleColor(LIGHT_RED);
                do
                {
                    std::cout << "You have to open a graph among the followings : " << std::endl << std::endl;
                    setConsoleColor(GREEN);
                    for (int i = 0; i < files.size(); i++)
                        std::cout << " - " << i + 1 << " --> " << files[i].name.substr(0, files[i].name.find(".txt")) << std::endl;
                    setConsoleColor(LIGHT_RED);
                    std::cout << std::endl << "Make your choice : ";
                    std::cin  >> choice;
                    std::cout << std::endl;
                    videCin();
                } while (choice <= 0 || choice > files.size());

                selected_file = files[choice - 1];

                setConsoleColor(LIGHT_RED);
                do
                {
                    std::cout << "Now, please chose the weights of the graph among the followings : " << std::endl << std::endl;
                    setConsoleColor(GREEN);
                    for (int i = 0; i < selected_file.weights.size(); i++)
                        std::cout << " - " << i + 1 << " --> " << selected_file.weights[i].substr(0, selected_file.weights[i].find(".txt")) << std::endl;
                    setConsoleColor(LIGHT_RED);
                    std::cout << std::endl << "Make your choice : ";
                    std::cin  >> choice;
                    std::cout << std::endl;
                    videCin();
                } while (choice <= 0 || choice > selected_file.weights.size());

                setConsoleColor(LIGHT_CYAN);
                std::cout << "Opening the graph " << selected_file.name.substr(0, selected_file.name.find(".txt")) << " with ";
                std::cout << selected_file.weights[choice - 1].substr(0, selected_file.weights[choice - 1].find(".txt"));

                std::cout << std::endl << std::endl << std::endl;

                w_index = choice - 1;

                g.reset();
                if (!g.create("files/" + selected_file.name, "files/" + selected_file.weights[choice - 1]))
                {
                    setConsoleColor(LIGHT_RED);
                    std::cout << "FATAL ERROR -- UNABLE TO OPEN THE FILE" << std::endl << std::endl;
                    setConsoleColor(WHITE);
                    exit(-1);
                }

                Sleep(2000);
                clearScreen();
                std::cout << std::endl;
                break;
            }
            case 3:         ///4e cas : on applique l'algorithme de Prim au graphe charg�
            {
                float total_weight = 0;
                int w_choice;

                setConsoleColor(CYAN);
                do
                {
                    std::cout << "Which weight should be evaluated ?" << std::endl << std::endl;    ///On demande � l'utilisateur selon quel poids doit on appliquer Prim
                    for (int i = 0; i < g.getConnections()[0]->getWeights().size(); i++)
                        std::cout << "  - " << i + 1 << std::endl << std::endl;
                    std::cout << "Enter your choice : ";
                    std::cin  >> w_choice;
                    w_choice--;
                    videCin();
                } while (w_choice < 0 || w_choice >= g.getConnections()[0]->getWeights().size());

                std::vector<bool> vec = g.getPrim(w_choice, &total_weight);
                std::stringstream ss;
                std::stringstream sw;
                ss << w_choice;
                sw << w_index;
                std::string filename  = selected_file.name.substr(0, selected_file.name.find(".txt")) + " - weights " + sw.str();
                            filename += " - Prim - weight " + ss.str() + ".svg";

                char c;
                bool top = true;
                std::cout << std::endl << "Do you want to draw the spanning tree on top of the graph ? (y / n) : ";     ///on propose � l'utilisateur d'afficher le graphe produit par l'algorithme de Prim
                std::cin  >> c;

                if (c == 'n' || c == 'N') top = false;

                std::cout << std::endl << std::endl;
                g.showPrim(filename, &vec, top);
                std::cout << std::endl << std::endl;

                Sleep(2000);
                clearScreen();
                std::cout << std::endl;
                break;
            }
            case 4:         ///5e cas : on teste la connectivit� du graphe
            {
                if (g.connectivityTest(std::vector<bool>(g.getSize(), true)))
                {
                    setConsoleColor(LIGHT_GREEN);
                    std::cout << "The graph is connex !" << std::endl << std::endl;
                }
                else
                {
                    setConsoleColor(LIGHT_RED);
                    std::cout << "The graph is not connex !" << std::endl << std::endl;
                }

                Sleep(2000);
                clearScreen();
                std::cout << std::endl;
                break;
            }
            case 5:     ///6e cas : optimisation de l'arbre couvrant bi-objectif (Partie 2 du projet)
            {
                std::stringstream sw;
                sw << w_index;
                std::string filename  = selected_file.name.substr(0, selected_file.name.find(".txt")) + " - weights " + sw.str();
                            filename += " - Pareto-front.svg";

                setConsoleColor(CYAN);
                g.bruteForcePareto(filename);

                Sleep(2000);
                clearScreen();
                std::cout << std::endl;
                break;
            }
            case 6:     ///7e cas : Optimistion bi-objectif cout/distance (Partie 3 du projet)
            {
                std::stringstream sw;
                sw << w_index;
                std::string filename  = selected_file.name.substr(0, selected_file.name.find(".txt")) + " - weights " + sw.str();
                            filename += " - Pareto-front-considering-cycles.svg";

                setConsoleColor(CYAN);
                g.bruteForceParetoConsideringCycles(filename);

                Sleep(2000);
                clearScreen();
                std::cout << std::endl;
                break;
            }
            case 7:     ///8e cas : Optimisaiton bi-objectifs par le biais d'un algorithme g�n�tique (Extension du projet)
            {
                setConsoleColor(LIGHT_MAGENTA);
                std::cout << "You are about to use a genetic algorithm in order to try to find the pareto optimal solutions." << std::endl;
                std::cout << "You will have to chose the size of the population and the mutation rate." << std::endl
                          << "Note that a higher population size means longer generations, but also higher"
                          << "probabilities to find optimal solutions quickly (in terms of generations)."
                          << "It also means a better diversity. I would recommend a size of 500 as a minimum." << std::endl << std::endl
                          << "The mutation rate is the probability for a connection to be toggled. It is an integer"
                          << "between 1 and 100. I would recommend 5." << std::endl << std::endl;

                setConsoleColor(CYAN);
                int pop_size = 0;
                int mut_rate = 5;
                std::cout << "Enter the population size : ";
                std::cin  >> pop_size;
                std::cout << std::endl << "Enter the mutation rate (1 - 100) : ";
                std::cin  >> mut_rate;

                if (pop_size < 100) pop_size = 100;
                else if (pop_size > 100000) pop_size = 100000;
                if (mut_rate < 1) mut_rate = 1;
                else if (mut_rate > 100) mut_rate = 100;

                clearScreen();
                Population p{pop_size, &g, mut_rate};
                p.solve();

                clearScreen();
                std::cout << endl;

                break;
            }
            case 8:
            {

                break;
            }
        }
    }
}

std::vector<FileInfo> findGraphFiles()
{
    std::vector<std::string> files;
    std::vector<FileInfo> infos;

    WIN32_FIND_DATA file;
    HANDLE hSearch;

    hSearch = FindFirstFile("files/*.txt", &file);

    if (hSearch != INVALID_HANDLE_VALUE)
    {
        do {
            files.push_back(file.cFileName);
        } while (FindNextFile(hSearch, &file));

        FindClose(hSearch);
    }

    for (int i = 0; i < files.size(); i++)
    {
        if (files[i].find("weights") == std::string::npos) // It contains the weights.
        {
            FileInfo f;
            f.name = files[i];
            infos.push_back(f);
            files.erase(files.begin() + i);
            i--;
        }
    }

    for (int i = 0; i < infos.size(); i++)
    {
        FileInfo f = infos[i];
        for (int j = 0; j < files.size(); j++)
        {
            if (files[j].find(f.name.substr(0, f.name.find(".txt"))) != std::string::npos)
            {
                infos[i].weights.push_back(files[j]);
                files.erase(files.begin() + j);
                j--;
            }
        }
    }

    return infos;
}

void clearScreen()
{
    system("cls");
}


