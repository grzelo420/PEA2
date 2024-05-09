//
// Created by Jakub Grzegocki on 29.11.2023.
//

#include "Menu.h"
#include <iostream>
#include "SymulowaneWyzarzanie.h"
#include <chrono>
using namespace std::chrono;

using namespace std;



void Menu::lista(){
    cout<<endl<<"1) ftv55.atsp  - 1608"<<endl;
    cout<<"2) ftv170.atsp - 2755"<<endl;
    cout<<"3) rgb358.atsp - 1163"<<endl;
    cout<<"4) ry48p.atsp  - brak danych"<<endl;
    cout<<"wybierz: ";
}

Menu::Menu(){

//    std::cout << "===========================\n"
//              << "1) Wprowadz ograniczenie czasowe\n"
//              << "2) Wprowadz wspolczynnik temperatury\n"
//              << "3) Wczytaj graf z pliku\n"
//              << "4) Wczytaj graf z listy\n"
//              << "5) Symulowanie wyzarzania\n"
//              << "6) Wczytaj sciezke z pliku i odtworz\n"
//              << "7) Przeprowadz testy\n"
//              << "8) Zakoncz program\n"
//              << "===========================\n"
//              << "Wybor: ";
    konsola.append("MENU:\n");
    konsola.append("1) Wprowadz ograniczenie czasowe\n");
    konsola.append("2) Wprowadz wspolczynnik temperatury\n");
    konsola.append("3) Wczytaj graf z pliku\n");
    konsola.append("4) Wczytaj graf z listy\n");
    konsola.append("5) Symulowanie wyzarzania\n");
    konsola.append("6) Wczytaj sciezke z pliku i odtworz\n");
    konsola.append("7) Przeprowadz testy\n");
    konsola.append("8) Zakoncz program\n");
    konsola.append("\n");
    konsola.append("Wybor: ");
}

Menu::~Menu() {}

void Menu::uruchom(){

    int wybor = 0;
    string testownik[4];
    testownik[0] = "C:\\Users\\Jakub Grzegocki\\Desktop\\E2\\cmake-build-release\\ftv55.atsp";
    testownik[1] = "C:\\Users\\Jakub Grzegocki\\CLionProjects\\PEA_2_release\\src\\ftv170.atsp";
    testownik[2] = "C:\\Users\\Jakub Grzegocki\\CLionProjects\\PEA_2_release\\src\\rbg358.atsp";
    testownik[3] = "C:\\Users\\Jakub Grzegocki\\CLionProjects\\PEA_2_release\\src\\ry48p.atsp";


    while(true) {
        cout << "ograniczenie czasowe: " << czas << " s" << endl;
        cout << "wspolczynnik temp:    " << wspolTemp << endl;
        cout << "opis grafu:" << endl;
        cout << graf.zwrocOpis();
        cout << konsola;

        cin >> wybor;

        switch (wybor) {
            case 1: {
                do {
                    cout << "podaj czas w sekundach: ";
                    cin >> czas;
                } while (czas == 0);
                break;
            }
            case 2: {
                do {
                    cout << "wspolczynnik temperatury (0.01-0.99): ";
                    cin >> wspolTemp;
                } while (wspolTemp == 0.0);
                break;
            }
            case 3: {
                do {
                    std::cout << "podaj sciezke pliku: ";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    getline(cin, plik);
                    cout << endl << plik;
                } while (plik == "");
                graf.wczytajGraf(plik);
                break;
            }
            case 4: {
                int wyb = 0;
                do {
                    lista();
                    cin >> wyb;
                    graf.wczytajGraf(testownik[wyb - 1]);
                } while (wyb == 0);
                break;
            }
            case 5: {
                if (czas != 0 and wspolTemp != 0) {

                    SymulowaneWyzarzanie sw(graf, czas, wspolTemp);
                    vector<int> najlepsza = sw.rozpocznij();
                    cin.get();
                    int wybor;
                    cout << "Czy chcesz zapisac sciezke do pliku? 1)tak 2)nie" << endl;
                    cin >> wybor;
                    if (wybor == 1) {
                        string nazwa;
                        do {
                            cout << "Podaj nazwe pliku: ";
                            cin >> nazwa;
                        } while (nazwa == "");
                        sw.zapiszSciezke(najlepsza, nazwa);
                    }
                } else {
                    cerr << "Prosze uzupelnic brakujace dane (ograniczenie czasowe, wspolczynnik temp.)" << endl;
                }
                break;}

            case 6: {
                if(graf.zwrocOpis()!=""){
                    vector<int> najlepsza;
                    string sciezka;
                    int kosztNajlepsza;
                    cout<<"Podaj sciezke do pliku z zapisana trasa:"<<endl;
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    getline(cin, sciezka);
                    cout<<"Sciezka pliku: "<<sciezka<<endl;
                    najlepsza = graf.odczytajSciezke(sciezka);
                    kosztNajlepsza = graf.liczSciezke(najlepsza);
                    if(kosztNajlepsza!=0) {
                        cout << "Koszt wczytanej sciezki: " << kosztNajlepsza << endl;
                    }else{cout<<" Koszt zerowy: "<<endl;}
                }else{ cerr<<"Brak wczytanego grafu!"<<endl;}

                break;
            }
            case 7: {
                if (czas != 0 and wspolTemp != 0) {
                    vector<int> najlepsza;
                    cout << "Testowanie rgb358.atsp" << endl;
                    for(int i = 0; i < 10; i ++){
                    graf.wczytajGraf(testownik[0]);
                    SymulowaneWyzarzanie sw(graf, czas, wspolTemp);
                    najlepsza = sw.rozpocznij();
                    cout<<"SCIEZKA KOSZT: "<<sw.liczSciezke(najlepsza)<<endl;
                    cin.get();
                    string nazwa = "rgb358_";
                    nazwa += to_string(i+1);
                    nazwa += ".txt";
                    cout<<nazwa<<endl;
                    sw.zapiszSciezke(najlepsza, nazwa);
                    }
                }
                break;
            }
            case 8:{
                return;
            }
                cin.ignore();
                system("cls");
            }


        }
    }
