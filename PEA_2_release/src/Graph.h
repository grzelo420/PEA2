//
// Created by Jakub Grzegocki on 29.11.2023.
//

#include <string>
#include <vector>
#ifndef PEA_2_RELEASE_GRAPH_H
#define PEA_2_RELEASE_GRAPH_H

using namespace std;

class Graph {

private:
    string opis_macierzy = " ";
    int **macierz = nullptr;
    int licznik_miast = 0;
    vector<int> sciezkaPomocnicza;
public:

    string zwrocOpis();
    string toString();
    bool nieskonczonosci();
    bool wczytajGraf(string plik);
    int zwrocLicznik();
    int** zwrocMacierz();
    Graph();
    ~Graph();

    void generujLosowa(int wielkosc);
    int liczSciezke(vector<int> Najlepsza);
    void ustawSciezke(vector<int> sciezka);
    vector<int> odczytajSciezke(const string &nazwaPliku);
};


#endif //PEA_2_RELEASE_GRAPH_H
