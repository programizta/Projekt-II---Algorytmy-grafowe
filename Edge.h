#pragma once

class Edge // jest to klasa reprezentuj¹ca pojedyncz¹ krawêdŸ grafu
{
public:

    int wp, wk, weight; // zmienne do okreœlenia wagi krawêdzi
    bool operator()(const Edge &k1, const Edge &k2) // przeci¹¿ony operator (), który pozwoli nam w ³atwy sposób okreœliæ relacje logiczne pomiêdzy innymi
    {                                               // krawêdziami w przypadku wynajdywania œcie¿ek
        if (k1.weight > k2.weight) return true;
        if (k1.weight < k2.weight) return false;
        return false;
    }
};
