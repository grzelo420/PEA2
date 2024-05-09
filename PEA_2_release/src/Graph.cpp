//
// Created by Jakub Grzegocki on 29.11.2023.
//

#include <fstream>
#include <time.h>
#include <ctime>
#include <string>
#include <iostream>
#include <vector>
#include "Graph.h"

Graph::Graph() {}

Graph::~Graph() {}

void Graph::ustawSciezke(vector<int> sciezka){
    sciezkaPomocnicza = sciezka;
}

vector<int> Graph::odczytajSciezke(const string& nazwaPliku) {
    ifstream plik(nazwaPliku);
    vector<int> sciezka;

    if (!plik.is_open()) {
        cerr << "Nie można otworzyc pliku do odczytu." << endl;
        return sciezka;
    }

    int wielkoscSciezki;
    plik >> wielkoscSciezki;

    for (int i = 0; i < wielkoscSciezki; ++i) {
        int miasto;
        plik >> miasto;
        sciezka.push_back(miasto);
    }

    cout << "Odczytano sciezke z pliku: " << nazwaPliku << endl;
    plik.close();
    sciezkaPomocnicza = sciezka;
    return sciezka;
}
int Graph::liczSciezke(vector<int> Najlepsza) {

    int koszt = 0;

    for(int i = 0; i < Najlepsza.size() - 1; ++i){
        koszt += macierz[Najlepsza[i]][Najlepsza[i + 1]];
    }
    koszt += macierz[Najlepsza[licznik_miast - 1]][Najlepsza[0]];

    return koszt;
}
int** Graph::zwrocMacierz() {
    return macierz;
}

int Graph::zwrocLicznik() {
    return licznik_miast;
}

string Graph::zwrocOpis() {
    if(licznik_miast){
        return opis_macierzy;
    }else{
        return "Nie wprowadzono macierzy \n";
    }
}

string Graph::toString(){

    string znaki = "";
    znaki.append(opis_macierzy);
    if(licznik_miast){
        for(int i=0; i< licznik_miast; i++){
            for(int j=0; j< licznik_miast; j++){
                if((macierz[i][j] < 10 and (macierz[i][j] >= 0)))
                    znaki += to_string(macierz[i][j]) + "    ";
                else if (((macierz[i][j] < 100 and (macierz[i][j] > 9)) or (macierz[i][j] < 0 )))
                    znaki += to_string(macierz[i][j]) + "   ";
                else if (macierz[i][j] == 100000000)
                    znaki += "N   ";
                else
                    znaki += to_string(macierz[i][j]) + "  ";
            }
            znaki += "\n";
        }
    }else{
        znaki = "Macierz jest pusta\n";
    }
    return znaki;
}

bool Graph::nieskonczonosci() {
    if(licznik_miast){
        for(int i = 0; i < licznik_miast; i++){
            macierz[i][i] = 9999;
        }
        return true;

    }else{
        return false;
    }
}

void Graph::generujLosowa(int wielkosc) {

    licznik_miast = wielkosc;
    int **nowa = nullptr;
    nowa = new int*[licznik_miast];

    srand(time(NULL));

    for(int i = 0; i<licznik_miast; i++){
        nowa[i] = new int[licznik_miast];
        for(int j=0; j<licznik_miast; j++){
            nowa[i][j] = rand() % 100 + 1;
        }
    }

    macierz = nowa;
    nieskonczonosci();

}

bool Graph::wczytajGraf(string plik) {
    int **tym;
    opis_macierzy = "";
    string tymOpis = "";
    ifstream wejscie;
    wejscie.open(plik);

    if(wejscie.fail() or wejscie.eof())
    {
        return false;
    }

    if(licznik_miast){
        for(int i = 0; i < licznik_miast; i++){
            delete[] macierz[i];
        }

        delete[] macierz;
    }

    getline(wejscie, tymOpis);
    opis_macierzy.append(tymOpis + "\n");
    getline(wejscie, tymOpis);
    opis_macierzy.append(tymOpis + "\n");
    getline(wejscie, tymOpis);
    opis_macierzy.append(tymOpis + "\n");
    wejscie >> tymOpis;
    opis_macierzy.append(tymOpis);
    wejscie >> licznik_miast;
    opis_macierzy.append(to_string(licznik_miast) + "\n");
    getline(wejscie, tymOpis);
    getline(wejscie, tymOpis);
    getline(wejscie, tymOpis);
    getline(wejscie, tymOpis);

    tym = new int *[licznik_miast];

    for (int i = 0 ; i< licznik_miast; i++){
        tym[i] = new int[licznik_miast];
    }

    for(int i = 0; i < licznik_miast; i++){
        for(int j = 0; j < licznik_miast; j++){
            wejscie >> tym[i][j];
        }
    }

    wejscie.close();
    macierz = tym;
    return true;

}
