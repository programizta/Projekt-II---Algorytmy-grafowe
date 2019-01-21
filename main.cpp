#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Interface.h"

using namespace std;

int main()
{
    srand(time(NULL));

    Interface inter;
    inter.choiceOfGraphGeneration();
}
