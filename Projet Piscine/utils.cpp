

/// \author Pierre Herduin, Mélodie Damas, Simon jolly

#include "utils.h"

float mapLine(float val, float xa, float ya, float xb, float yb)
{
    ///On va chercher les paramètres de la fonction affine décrivant la droite passant par a et b
    float m = (yb - ya) / (xb - xa);        ///On calcule le coefficient directeur
    float p = ya - m * xa;          ///On calcule l'ordonnée à l'origine

    return m * val + p; ///on retourne l'ordonnée du point d'abscisse val
}

float dist(float xa, float ya, float xb, float yb)
{
    return std::sqrt(std::pow(xb - xa, 2) + std::pow(yb - ya, 2));      ///distance euclidienne
}

float factorial(float nb)
{
    if (nb < 0) return 0;
    if( nb ==0 ) return 1;

    float r = nb;

    for (int i = nb - 1; i > 1; i--)
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

void setConsoleColor(int text_color, int background_color)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, background_color * 16 + text_color);
}

void menu()
{
    int choice;
    int w_index;
    setConsoleColor(LIGHT_MAGENTA);
    std::cout << std::endl << "Welcome into the Graph analysis tool !" << std::endl << std::endl << std::endl;

    std::vector<FileInfo> files = findGraphFiles();

    setConsoleColor(LIGHT_RED);
    do
    {
        std::cout << "First of all, you have to open a graph among the followings : " << std::endl << std::endl;
        setConsoleColor(GREEN);
        for (int i = 0; i < files.size(); i++)
            std::cout << " - " << i + 1 << " --> " << files[i].name.substr(0, files[i].name.find(".txt")) << std::endl;
        setConsoleColor(LIGHT_RED);
        std::cout << std::endl << "Make your choice : ";
        std::cin  >> choice;
        videCin();
        std::cout << std::endl;
        videCin();
    } while (choice <= 0 || choice > files.size());

    FileInfo selected_file = files[choice - 1];

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
        videCin();
        std::cout << std::endl;
        videCin();
    } while (choice <= 0 || choice > selected_file.weights.size());

    setConsoleColor(LIGHT_CYAN);
    std::cout << "Opening the graph " << selected_file.name.substr(0, selected_file.name.find(".txt")) << " with ";
    std::cout << selected_file.weights[choice - 1].substr(0, selected_file.weights[choice - 1].find(".txt"));

    std::cout << std::endl << std::endl << std::endl;

    w_index = choice - 1;

    Graph g;
    if (!g.create("files/" + selected_file.name, "files/" + selected_file.weights[choice - 1]))
    {
        setConsoleColor(LIGHT_RED);
        std::cout << "FATAL ERROR -- UNABLE TO OPEN THE FILE" << std::endl << std::endl;
        setConsoleColor(WHITE);
        exit(-1);
    }

    while (true)
    {
        setConsoleColor(LIGHT_RED);
        std::cout << "Please choose between the following options :" << std::endl << std::endl;
        setConsoleColor(GREEN);
        std::cout << "  - 0 --> Quit." << std::endl << std::endl;
        std::cout << "  - 1 --> Show the graph." << std::endl << std::endl;
        std::cout << "  - 2 --> Change the graph." << std::endl << std::endl;
        std::cout << "  - 3 --> Find minimum spanning tree (Prim's algorithm)." << std::endl << std::endl;
        std::cout << "  - 4 --> Test the connexity of the graph." << std::endl << std::endl;
        std::cout << "  - 5 --> Dual objective spanning tree optimization (brute force) (\"Partie 2\")." << std::endl << std::endl;
        std::cout << "  - 6 --> Dual objective optimization (cost / distance) (brute force) (\"Partie 3\")." << std::endl << std::endl;
        std::cout << "  - 7 --> Dual objective spanning tree optimization (genetic algorithm)." << std::endl << std::endl;
        setConsoleColor(LIGHT_RED);
        std::cout << "Make your choice : ";
        std::cin  >> choice;
        videCin();
        std::cout << std::endl << std::endl << std::endl;
        videCin();

        switch (choice)
        {
            case 0:
            {
                setConsoleColor(WHITE);
                g.reset();
                exit(0);
            }
            case 1:
            {
                std::string filename;

                setConsoleColor(CYAN);
                std::cout << "Enter the name of the file (without '.svg') : ";
                std::cin  >> filename;
                videCin();
                std::cout << std::endl << std::endl;

                filename = filename + ".svg";

                g.show(filename);

                std::cout << std::endl << std::endl;
                break;
            }
            case 2:
            {
                files = findGraphFiles();

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
                    videCin();
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
                    videCin();
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
            case 3:
            {
                float total_weight = 0;
                int w_choice;

                setConsoleColor(CYAN);
                do
                {
                    std::cout << "Which weight should be evaluated ?" << std::endl << std::endl;
                    for (int i = 0; i < g.getConnections()[0]->getWeights().size(); i++)
                        std::cout << "  - " << i + 1 << std::endl << std::endl;
                    std::cout << "Enter your choice : ";
                    std::cin  >> w_choice;
                    videCin();
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
                std::cout << std::endl << "Do you want to draw the spanning tree on top of the graph ? (y / n) : ";
                std::cin  >> c;
                videCin();

                if (c == 'n' || c == 'N') top = false;

                std::cout << std::endl << std::endl;
                g.showPrim(filename, &vec, top);
                std::cout << std::endl << std::endl;

                Sleep(2000);
                clearScreen();
                std::cout << std::endl;
                break;
            }
            case 4:
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
            case 5:
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
            case 6:
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
            case 7:
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
                videCin();
                std::cout << std::endl << "Enter the mutation rate (1 - 100) : ";
                std::cin  >> mut_rate;
                videCin();

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


