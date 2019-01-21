#pragma once
#include "Edge.h"
#include "ListElement.h"
#include <iostream>
#include <cstdio>

class SpanningTree // klasa, która reprezentuje drzewo rozpinające w pamięci komputera
{
    ListElement **T; // wskaźnik na dynamiczną listę następników i poprzedników
    Edge *kk;
    int sizeT;
    int weight; // wartości wag krawędzi
    int edges; // liczba krawędzi
    int a;

public:

    SpanningTree(int verticles, int kr);
    ~SpanningTree();
    void addEdge(Edge k); // dodanie krawędzi do grafu
    void display();
};
