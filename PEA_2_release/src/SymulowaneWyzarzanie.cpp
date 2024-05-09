//
// Created by Jakub Grzegocki on 29.11.2023.
//

#include <random>
#include <vector>
#include <algorithm>
#include <ctime>
#include <time.h>
#include <math.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include "SymulowaneWyzarzanie.h"
#include "Graph.h"
#define PROB 9999

using namespace std;

void SymulowaneWyzarzanie::wypiszWyniki(const vector<int>& najlepsza, int wynik, double znalezionyCzas, double temperatura) {
//
    cout << endl << "Koszt: " << wynik << endl;
    cout << "Znaleziona w czasie: " << znalezionyCzas << " s" << endl;
    cout << "Temperatura w momencie przerwania: " << temperatura << endl;
    cout << "wyrazenie exp(-1/Tk) = " <<exp(-1/temperatura) << endl;
    cout << "Sciezka: ";
    for(int i = 0; i < wielkosc; i++) {
        cout << najlepsza[i] << " -> ";
    }
}
vector<int> SymulowaneWyzarzanie::rozpocznij() {

    vector<int> najlepszeKoszty;
    // Utworzenie greedy
    vector<int> greedy = permutacjaPoczatkowa(wielkosc);

    // Utworzenie permutacji zachlannie jako rozwiązania początkowego
    vector<int> permutacja(greedy);

    // Inicjalizacja wektora przechowującego najlepsze znalezione rozwiązanie
    vector<int> najlepsza(permutacja);

    // Przypisanie permutacji jako kolejnego możliwego rozwiązania
    vector<int> nowaSciezka(permutacja);


    int greedyLicz = liczSciezke(greedy);
    // Wyświetlenie ścieżki początkowej wygenerowanej algorytmem zachłannym aby mieć odniesienie do rozwiązania
    cout<<"Koszt sciezki poczatkowej: "<<liczSciezke(permutacja)<<endl;
    for(int i = 0; i < wielkosc; i++) {
        cout << greedy[i] << " -> ";
    }

    // rozpoczęcie zliczania czasu aby móc określać czas trwania algorytmu, który jest warunkiem stopu działania
    auto start = std::chrono::high_resolution_clock::now();
    int miasto1, miasto2;
    double tempO = 0.01;
    double temperatura = temperaturaB;
    int wynik = liczSciezke(greedy);
    double czas = 0;
    double czasPrzerwania = 0;
    int era = wielkosc;
    era *= 6;
    // Główna pętla algorytmu
    while (true) {

        // Pętla schładzania temperatury
        while (temperatura >= tempO) {
            //era = 6 * wielkosc;
            nowaSciezka = permutacja;
            int nastepnyKoszt; //= liczSciezke(nowaSciezka);
            double prawdo = zwrocPrawdopodobienstwo(wynik-nastepnyKoszt, temperatura);

            //if(prawdo!=0){
           // cout<<"Prawdopodobienstwo: "<<prawdo<<endl;}
            double porow = ((double)rand() / RAND_MAX);
            for (int i = 0; i <= era ; i++) {   // Pętla iteracyjna dla ery
                do {
                    miasto1 = rand() % wielkosc;
                    miasto2 = rand() % wielkosc;
                } while (miasto1 == miasto2);

                swap(nowaSciezka[miasto1], nowaSciezka[miasto2]);

                nastepnyKoszt = liczSciezke(nowaSciezka);
//                if(nastepnyKoszt<3000){
//                cout<<"Nastepny koszt: "<<nastepnyKoszt<<endl;}
                if (wynik-nastepnyKoszt > 0) {  // Jeśli nowa permutacja jest lepsza
                    wynik = nastepnyKoszt;
                    najlepsza = nowaSciezka;
                    najlepszeKoszty.push_back(wynik);
                    cout<<"==========================="<<endl;
                    cout<<"Znaleziono nowa najlepsza: "<<liczSciezke(najlepsza)<<endl;
                    auto stopgen  = std::chrono::high_resolution_clock::now();
                    czasPrzerwania = std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(stopgen - start).count();

                    permutacja = nowaSciezka;
                }else if (prawdo > porow) {
                    cout<<"Weszlo"<<endl;
                    permutacja = nowaSciezka;
                    break;
                }

               // cout<<"Porow: "<<porow<<endl;

                // Warunek akceptacji nowej permutacji z pewnym prawdopodobieństwem
//                if (prawdo > porow) {
//                    permutacja = nowaSciezka;
//                    break;
//                }
//                else {
//                    // jesli permutacja zostanie odrzucona to swap ustawia nam permutacje na poprzednią i kontynuujemy dzialanie
//                    swap(nowaSciezka[miasto1], nowaSciezka[miasto2]);
//                }
                //cout<<"WYNIK: "<<wynik<<endl;
                // Sprawdzenie, czy czas wykonania nie przekroczył ustalonej granicy
                auto stop = std::chrono::high_resolution_clock::now();
                czas = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count();
                auto czas2 = std::chrono::duration_cast<std::chrono::duration<double>>(stop-start).count();
                if (czas2 > granicaCzas) {
                    wypiszWyniki(najlepsza, wynik, (czasPrzerwania*1e-9), temperatura);
                    cout<<endl;
                    //wypiszWyniki(sciezka2, wynikZachlanny, czasPrzerwania, temperatura);
                    return najlepsza;  // Zwrócenie najlepszej znalezionej permutacji po osiągnięciu granicy czasu
                }
            }
            temperatura *= stopienSchladzania; // Schłodzenie temperatury
        }

//        system("pause");
//        cout<<"temperatura: "<<temperatura<<endl;
        temperatura = temperaturaB; // Powrót do początkowej temperatury po schłodzeniu
       // cout<<"Szukam nowej permutacji"<<endl;
        //permutacja = permutacjaLosowa(wielkosc); // Wygenerowanie nowej losowej permutacji

        //cout<<"KOSZT PERMUTACJI LOSOWEJ"<<liczSciezke(permutacja)<<endl;
    }
    for(int i = 0; i < najlepszeKoszty.size(); i++){
        cout<<i<<") "<<najlepszeKoszty[i]<<endl;
    }

}

vector<int> SymulowaneWyzarzanie::permutacjaPoczatkowa(int wielkosc){
    vector<int> sciezkaZachlanna;
    sciezkaZachlanna.push_back(0);  // Dodaj pierwsze miasto do ścieżki

    vector<bool> odwiedzone(wielkosc, false);
    odwiedzone[0] = true;

    for (int i = 1; i < wielkosc; ++i) {
        int aktualneMiasto = sciezkaZachlanna.back();
        int najblizszeMiasto = znajdzNajblizszeMiasto(aktualneMiasto, odwiedzone);
        cout<<"Najblizsze miasto : "<<najblizszeMiasto<<endl;
        sciezkaZachlanna.push_back(najblizszeMiasto);
        odwiedzone[najblizszeMiasto] = true;
    }

    return sciezkaZachlanna;
}

int SymulowaneWyzarzanie::znajdzNajblizszeMiasto(int miasto, const vector<bool>& odwiedzone) {
    int najblizszeMiasto = -1;
    int najkrotszaOdleglosc = numeric_limits<int>::max();
    for (int i = 0; i < wielkosc; ++i) {
        if (!odwiedzone[i] && i != miasto && macierz[miasto][i] < najkrotszaOdleglosc) {
            najblizszeMiasto = i;
            najkrotszaOdleglosc = macierz[miasto][i];
            cout<<"Najkrotsza Odleglosc: "<<macierz[miasto][i]<<endl;
        }
    }
    return najblizszeMiasto;
}

vector<int> SymulowaneWyzarzanie::permutacjaLosowa(int wielkosc) {
    vector<int> tym;
    tym.reserve(wielkosc);
    for(int i = 0 ; i < wielkosc ; ++i){
        tym.push_back(i);
    }
    random_shuffle(tym.begin(), tym.end());

//    for (int element : tym) {
//        cout << element << " ";
//    }
//    cout << endl;
    return tym;
}

double SymulowaneWyzarzanie::liczTemperature() {

    //wygenerowanie ziarna i ustawienie dystrybucji od 0 do wymiaru macierzy - 1
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, wielkosc - 1);
    vector<int> losowa;
    vector<int> sasiad;
    int miasto1, miasto2, roznicaOdleglosci, sumaRoznic, delta = 0;

    for(int i = 0; i < PROB; i++){
        //losowanie
        while(miasto1 == miasto2){
            miasto1 = rand() % wielkosc;
            miasto2 = rand() % wielkosc;
//            miasto1 = dist(gen);
//            miasto2 = dist(gen);
        }
        // wygenerowanie permutacji losowej
        losowa = permutacjaLosowa(wielkosc);
        // wygenerowanie permutacji sąsiedniej
        vector<int> sasiad(losowa);

        swap(sasiad[miasto1], sasiad[miasto2]);
        delta = liczSciezke(losowa) - liczSciezke(sasiad);
        // wygenerowanie permutacji sąsiedniej
        roznicaOdleglosci = fabs(delta);
        sumaRoznic += roznicaOdleglosci;

    }
    double sredniaRoznica = sumaRoznic / PROB;
    double temperatura = -sredniaRoznica / log(0.3); // ustawione na mniej niz 0.99 ze wzgledu na lepsza wydajnosc algorytmu
    return temperatura;

}

int SymulowaneWyzarzanie::liczSciezke(vector<int> sciezka) {
    int koszt = 0;
    for(int i = 0; i < sciezka.size() - 1; ++i){
        koszt += macierz[sciezka[i]][sciezka[i+1]];
    }
    koszt += macierz[sciezka[wielkosc-1]][sciezka[0]];
    return koszt;
}

double SymulowaneWyzarzanie::zwrocPrawdopodobienstwo(int r, double t) {
    //cout<<"Prawdopodobienstwo: "<<exp(r/t)<<endl;
    return exp(r/t);

}

void SymulowaneWyzarzanie::zapiszSciezke(const vector<int>& sciezka1, const string& nazwaPliku) {
    ofstream plik(nazwaPliku);
    if (!plik.is_open()) {
        cerr << "Nie można otworzyc pliku do zapisu." << endl;
        return;
    }

    plik << sciezka1.size() << endl;
    for (int miasto : sciezka1) {
        cout << miasto << " -> ";
        plik << miasto << endl;
    }

    cout << "Zapisano sciezke do pliku: " << nazwaPliku << endl;
    plik.close();
}

vector<int> SymulowaneWyzarzanie::odczytajSciezke(const string& nazwaPliku) {
    ifstream plik(nazwaPliku);
    vector<int> sciezka;

    if (!plik.is_open()) {
        cerr << "Nie można otworzyć pliku do odczytu." << endl;
        return sciezka;
    }

    int wielkoscSciezki;
    plik >> wielkoscSciezki;

    for (int i = 0; i < wielkoscSciezki; ++i) {
        int miasto;
        plik >> miasto;
        sciezka.push_back(miasto);
    }

    cout << "Odczytano scieżkę z pliku: " << nazwaPliku << endl;
    plik.close();
    return sciezka;
}

SymulowaneWyzarzanie::SymulowaneWyzarzanie(Graph graf, int czas, double stopien) {
    macierz = graf.zwrocMacierz();
    wielkosc = graf.zwrocLicznik();
    granicaCzas = czas;
    stopienSchladzania = stopien;
    temperaturaB = liczTemperature();
    cout<<"temperatura: "<<temperaturaB;
}


SymulowaneWyzarzanie::~SymulowaneWyzarzanie() {

}
