#pragma once
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <queue>
#include <ctime>
#include "Edge.h"
#include "ListElement.h"
#include "Stack.h"
#include "SpanningTree.h"
#include "Time.h"
#define MAXINT 2147483647 // definicja największej liczby całkowitej (32-bitowej)

class Graph
{
public:

    Graph(int w, int m); // konstruktor grafu
    ~Graph(); // destruktor grafu (dynamicznej tablicy)
    Edge *K, *KO;
    int **incidence_matrix, **unscanned_graph_matrix; // wskaxniki na dunamiczne macierze incydencji i grafu nieskierowanego
    ListElement **neighborhood_list, **unscanned_graph_list;
    int verticles; // deklaracja wierzchołków
    int edges; // deklaracja krawędzi
    int density; // deklaracja gęstości grafu
    int inverted_edges; // deklaracja odwróconych krawędzi
    ListElement *e1, *e2; // wskaźniki na elementy listy grafu
    bool *visited; // pomocnicza zmienna logiczna, która jest odpowiedzialna za sprawdzenie czy wierzchołek został już odwiedzony

    void Prim_matrix(); // utworzenie reprezentacji macierzowej grafu dla algorytmu Prima
    void display(); // metoda wyświetlająca macierz incydencji oraz listę następników i poprzedników
    void PrimList(); // utworzenie listy poprzedników i następników dla reprezentacji grafu w algorytmie Prima
    void DijkstraMatrix(int w); // utworzenie reprezentacji macierzowej grafu dla algorytmu Dijkstry
    void DijkstraList(int w); // utworzenie listy poprzedników i następników dla reprezentacji grafu w algorytmie Dijkstry
    void DFSList(int w);
    void DFSMatrix(int w);
    bool checkConsistence(); // metoda sprawdzająca spójność grafu
    void generateGraph(); // metoda generująca graf spójny w pamięci komputera
    void generateEdges(); // wygenerowanie krawędzi dla grafu
    void changeToUnscannedGraph(); // zamiana grafu skierowanego na graf nieskierowany
};
