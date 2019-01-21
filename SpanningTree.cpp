#include "SpanningTree.h"

using namespace std;

SpanningTree::SpanningTree(int wierzcholki, int kr)
{
    T = new ListElement *[wierzcholki];
    for (int i = 0; i < wierzcholki; i++)
    {
        T[i] = NULL;
    }
    sizeT = wierzcholki - 1;
    weight = 0;
    edges = kr;
    kk = new Edge[edges];
    a = 0;
}

SpanningTree::~SpanningTree()
{
    ListElement *e1, *e2;
    for (int i = 0; i <= sizeT; i++)
    {
        e1 = T[i];
        while (e1)
        {
            e2 = e1;
            e1 = e1->next;
            delete e2;
        }
    }
    delete[]T;
}

void SpanningTree::addEdge(Edge k)
{
    ListElement *e;

    weight += k.weight;
    e = new ListElement;
    e->w = k.wk;
    e->weight = k.weight;
    e->next = T[k.wp];
    T[k.wp] = e;

    e = new ListElement;
    e->w = k.wp;
    e->weight = k.weight;
    e->next = T[k.wk];
    T[k.wk] = e;

    kk[a] = k;
    a++;
}

void SpanningTree::display()
{
    cout << endl;
    for (int i = 0; i < a; i++)
    {

        cout << "Krawedz nr " << i + 1 << ": ";

        cout << kk[i].wp << "<-->" << kk[i].wk << " [" << kk[i].weight << "] ";

        cout << endl;
    }
    cout << endl << endl << "Waga drzewa MST: " << weight << endl << endl;
}
