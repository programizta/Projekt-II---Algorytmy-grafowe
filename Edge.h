#pragma once

class Edge // jest to klasa reprezentuj�ca pojedyncz� kraw�d� grafu
{
public:

    int wp, wk, weight; // zmienne do okre�lenia wagi kraw�dzi
    bool operator()(const Edge &k1, const Edge &k2) // przeci��ony operator (), kt�ry pozwoli nam w �atwy spos�b okre�li� relacje logiczne pomi�dzy innymi
    {                                               // kraw�dziami w przypadku wynajdywania �cie�ek
        if (k1.weight > k2.weight) return true;
        if (k1.weight < k2.weight) return false;
        return false;
    }
};
