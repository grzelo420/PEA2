//
// Created by Jakub Grzegocki on 29.11.2023.
//

#ifndef PEA_2_RELEASE_MENU_H
#define PEA_2_RELEASE_MENU_H

#include <string>
#include "Graph.h"

using namespace std;

class Menu {
private:

    string konsola = "";
    string plik = "";
    Graph graf;
    int czas = 0;
    double wspolTemp = 0;
public:
    void uruchom();
    void lista();
    Menu();
    ~Menu();
};


#endif //PEA_2_RELEASE_MENU_H
