//
// Created by Jakub Grzegocki on 29.11.2023.
//

#ifndef PEA_2_RELEASE_SYMULOWANEWYZARZANIE_H
#define PEA_2_RELEASE_SYMULOWANEWYZARZANIE_H

#include <vector>
#include "Graph.h"

class SymulowaneWyzarzanie {

private:
    int **macierz;
    int wielkosc;

    double temperaturaB = 0;
    double stopienSchladzania = 0;
    double granicaCzas;
    std::vector<int> rozw;

public:


    void wypiszWyniki(const vector<int>& najlepsza, int wynik, double znalezionyCzas, double temperatura);
    vector<int> rozpocznij();
    vector<int> permutacjaLosowa(int wielkosc);
    vector<int> permutacjaPoczatkowa(int wielkosc);
    int znajdzNajblizszeMiasto(int miast, const vector<bool>& odwiedzone);
    double liczTemperature();
    int liczSciezke(vector <int> sciezka);
    double zwrocPrawdopodobienstwo(int roznica, double temperatura);
    SymulowaneWyzarzanie(Graph graf, int czas, double stopien);
    ~SymulowaneWyzarzanie();

    vector<int> odczytajSciezke(const string &nazwaPliku);

    void zapiszSciezke(const vector<int> &sciezka, const string &nazwaPliku);
};


#endif //PEA_2_RELEASE_SYMULOWANEWYZARZANIE_H
