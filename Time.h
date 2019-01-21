#pragma once
#include <chrono>

using namespace std;
using namespace std::chrono;

class Time // klasa odpowiedzialna za odmierzanie czasu poszczególnych algorytmów
{

public:

    high_resolution_clock::time_point beginning_time;
    high_resolution_clock::time_point end_time;

    void start(); // metoda rozpoczynająca odmierzanie czasu
    void stop(); // metoda kończąca odmierzanie czasu
    long executionTime(); // czas wykonywania
};
