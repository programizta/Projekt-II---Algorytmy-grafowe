#pragma once
#include "ListElement.h"

class Stack
{
    ListElement *s; // deklaracja listy jednokierunkowej

public:

    Stack();
    ~Stack();
    bool empty(); // metoda sprawdzaj�ca czy stos jest pusty
    int top();
    void pop(); // metoda usuwaj�ca element z listy
    void push(int w); // metoda dodaj�ca element do listy
};
