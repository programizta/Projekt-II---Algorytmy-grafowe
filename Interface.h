#pragma once
#include <cmath>
#include <fstream>
#include <iomanip>
#include <queue>
#include "Edge.h"
#include "Stack.h"
#include "Graph.h"

class Interface // klasa reprezentująca działanie całego programu
{
public:

    bool at_beginning = true;
    int choice; // wybór u¿ytkownika
    int w;
    int g;
    int b;
    Graph *graph; // wskaźnik, za pomocą którego tworzymy graf
    void choiceOfGraphGeneration(); // wybór generowania grafu
    void randomGraph(); // losowe wygenerowanie grafu
    void functionChoice(); // wybór funkcji
    void graphFromFile(); // utworzenie grafu z pliku
};
