#include <conio.h>
#include "Interface.h"

using namespace std;

string further = "\nAby kontynuowac kliknij dowolny klawisz...";

void Interface::choiceOfGraphGeneration()
{
    while(at_beginning)
    {
        cout << "Metody utworzenia grafu:\n\n1. Wygenerowanie losowego grafu\n2. Utworzenie grafu z pliku\n";
        cout << "\nWprowadz numer wyboru: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            system("CLS");
            randomGraph();
            functionChoice();
        }
        break;
        case 2:
        {
            system("CLS");
            graphFromFile();
            functionChoice();
        }
        break;
        }
    }
}

void Interface::functionChoice()
{
    while (!at_beginning)
    {
        system("CLS");
        cout << "Menu wyboru operacji:\n"
             << "1. Wyswietlenie reprezentacji listowej oraz macierzy incydencji grafu\n"
             << "2. Przeprowadzenie algorytmu Dijkstry\n"
             << "3. Przeprowadzenie algorytmu Prima\n"
             << "4. Wroc do glownego menu\n";
        cout << "Jaka opcje wybierasz? Wprowadz numer: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            system("CLS");
            graph->display();
            cout << further;
            getch();
        }
        break;
        case 2:
        {
            while(true)
            {
                system("CLS");
                cout << "Podaj wierzcholek startowy: ";
                cin >> b;
                if (b < graph->verticles) break;
                else cout << "Wprowadzono nieprawidlowy numer wierzcholka, podaj jego wartosc jeszcze raz\n" << endl;
            }

            while(true)
            {
                int choice_of_representation;
                cout << "Jakiej reprezentacji uzyc w algorytmie?" << endl << "1. Macierz Incydecji" << endl
                     << "2. Lista poprzednikow i nastepnikow" << endl;
                cin >> choice_of_representation;
                if (choice_of_representation == 1)
                {
                    system("CLS");
                    graph->DijkstraMatrix(b);
                    cout << further;
                    getch();
                    break;
                }
                else if (choice_of_representation == 2)
                {
                    system("CLS");
                    graph->DijkstraList(b);
                    cout << further;
                    getch();
                    break;
                }
            }
        }
        break;


        case 3:
        {
            while(true)
            {
                system("CLS");
                int choice_of_representation;
                cout << "Jakiej reprezentacji uzyc w algorytmie?" << endl << "1. Macierz Incydecji" << endl
                     << "2. Lista poprzednikow i nastepnikow" << endl;
                cin >> choice_of_representation;
                if (choice_of_representation == 1)
                {
                    system("CLS");
                    graph->Prim_matrix();
                    cout << further;
                    getch();
                    break;
                }
                else if (choice_of_representation == 2)
                {
                    system("CLS");
                    graph->PrimList();
                    cout << further;
                    getch();
                    break;
                }
            }

        }
        break;

        case 4:
        {
            delete graph;
            at_beginning = true;
            cout << "Wracam do glownego menu...\n";
            cout << further;
            getch();
            system("CLS");
        }
        break;
        }
    }
}

void Interface::randomGraph()
{
    system("CLS");
    at_beginning = false;
    while (true)
    {
        cout << "Podaj liczbe wierzcholkow grafu: ";
        cin >> w;
        if (w > 1) break;
        else cout << "Liczba wierzcholkow musi byc wieksza od 1! Jeszcze raz\n" << endl;
    }

    int maxK = w * (w - 1);
    double minG = ceil((((double) w - 1) * 100) / (double) maxK);

    while (true)
    {
        cout << "Wprowadz gestosc grafu (co najmniej " << minG << "%): ";
        cin >> g;
        if (g < minG || g > 100)
            cout << "Wprowadzona wartosc gestosci jest nieprawidlowa\n" << endl;
        else break;
    }

    ofstream save;
    double krawedzie = ceil((maxK * g) / 100);
    save.open("graf.txt");
    save << krawedzie << " " << w;
    save.close();
    graph = new Graph(w, krawedzie);
    graph->generateGraph();
}

void Interface::graphFromFile()
{
    at_beginning = false;
    ListElement *e1;
    string s, nazwa;
    int a = 0;
    int krawedzie, verticles;
    cout << "Podaj nazwe pliku z rozszerzeniem: ";
    cin >> nazwa;
    //nazwa = nazwa + ".txt";
    ifstream plik(nazwa);
    if (!plik)
    {
        cout << "Cos poszlo nie tak\n" << endl;
        at_beginning = true;

    }
    else
    {
        {
            plik >> krawedzie >> verticles;
            if (!plik || krawedzie < verticles - 1 || verticles <= 1 ||
                    krawedzie > (verticles * (verticles - 1)))
            {
                cout << "W pliku znajduja sie nieprawidlowe parametry grafu\n" << endl;

                at_beginning = true;
            }
            else
            {
                graph = new Graph(verticles, krawedzie);
                while (!plik.eof())
                {

                    plik >> graph->K[a].wp >> graph->K[a].wk >> graph->K[a].weight;
                    if (graph->K[a].wp >= verticles || graph->K[a].wk >= verticles ||
                            graph->K[a].weight < 1)
                    {
                        cout << "Wartosci krawedzi sa niepoprawnie zdefiniowane\n" << endl;
                        at_beginning = true;
                        break;
                    }

                    if (plik)
                    {
                        a++;
                    }
                    else
                    {
                        cout << "Wartosci krawedzi sa niepoprawnie zdefiniowane\n" << endl;
                        at_beginning = true;
                        break;
                    }
                }
                if (a == krawedzie)
                {
                    for (int i = 0; i < verticles; i++)
                        graph->incidence_matrix[i] = new int[krawedzie];
                    for (int i = 0; i < verticles; i++)
                        for (int j = 0; j < krawedzie; j++)
                        {
                            graph->incidence_matrix[i][j] = 0;
                        }

                    for (int i = 0; i < verticles; i++)
                        graph->neighborhood_list[i] = NULL;

                    for (int i = 0; i < krawedzie; i++)
                    {
                        int wp = graph->K[i].wp;
                        int wk = graph->K[i].wk;
                        e1 = new ListElement;
                        e1->w = wk;
                        e1->weight = graph->K[i].weight;
                        e1->next = graph->neighborhood_list[wp];
                        graph->neighborhood_list[wp] = e1;
                        graph->incidence_matrix[wp][i] = 1;
                        graph->incidence_matrix[wk][i] = -1;
                    }
                    plik.close();
                    graph->changeToUnscannedGraph();
                    if (!(graph->checkConsistence()))
                    {
                        cout << "Zawarte dane w pliku pozwalaja utworzyc graf, lecz nie jest on spojny!\n" << endl;
                        at_beginning = true;
                        delete graph;
                    }
                    else
                    {
                        functionChoice();
                    }

                }
                else if (!at_beginning)
                {
                    at_beginning = true;
                    cout << "W podanym pliku nie ma wystarczajacych danych dotyczacych utworzenia grafu.\n" << endl;
                }
            }
        }
    }
}
