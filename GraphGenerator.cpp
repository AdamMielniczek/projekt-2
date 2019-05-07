#include "GraphGenerator.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>

using namespace std;

GraphGenerator::GraphGenerator() {
}

GraphGenerator::GraphGenerator(int x) {
    int verticles2 = 0;
    float density = 0;

    do {
        cout << "Podaj liczbe wierzcholkow ";
        cin >> verticles2;
    } while (verticles2 < 2);


    this->verticles = verticles2;
    maxWeight = 9;
    minEdges = verticles - 1;								//minimalna ilosc krawedzi dla grafu spojnego
    maxEdges = ((verticles - 1)*verticles) / 2;
    int minDensity = ceil((minEdges / maxEdges) * 100);

    do {
        cout << "Podaj gestosc (minimum " << minDensity << "%) " << endl;
        cin >> density;
    } while (density < minDensity || density > 100);


    edges = ceil(maxEdges*(density / 100));					//pozadana liczba krawedzi
    int weight;
    result = new int *[2 * edges];

    //kreowanie drzewa
    vector <int> tab;									//vektor pamietajacy czy wierzcholek byl juz odwiedzony
    for (int i = 0; i < verticles; i++)	tab.push_back(i);

    srand(time(NULL));
    int next, previous;
    previous = rand() % verticles;
    tab[previous] = -1;
    for (int i = 1; i < minEdges + 1; i++) {
        while (true){
            next = rand() % verticles;
            if (tab[next] >= 0)
                break;
        }

        result[i - 1] = new int[3];
        result[i - 1][0] = previous;
        result[i - 1][1] = next;
        weight = (rand() % maxWeight) + 1;
        result[i - 1][2] = weight;
        tab[next] = -1;
        previous = next;
    }
    bool czyJest = false;
    for (int i = minEdges; i < edges; i++) {		// dodanie losowych krawedzi do drzewa
        while (true) {
            czyJest = false;
            previous = rand() % verticles;
            next = rand() % verticles;
            for (int j = 0; j < i; j++) {
                if ((result[j][0] == previous && result[j][1] == next) || (result[j][0] == next && result[j][1] == previous) || (next == previous)) {
                    czyJest = true;
                    break;
                }
            }
            if (!czyJest) {
                result[i] = new int[3];
                result[i][0] = previous;
                result[i][1] = next;
                weight = rand() % maxWeight + 1;
                result[i][2] = weight;
                break;
            }
        }

    }

    int help;
    for (int i = edges; i < edges * 2; i++) {

        while (true) {
            czyJest = false;
            previous = rand() % verticles;
            next = rand() % verticles;
            for (int j = 0; j < i; j++) {

                if ((result[j][0] == previous && result[j][1] == next) || (next == previous)) {
                    czyJest = true;
                    break;
                }

            }
            if (czyJest == false) {
                result[i] = new int[3];
                result[i][0] = previous;
                result[i][1] = next;
                weight = rand() % maxWeight + 1;
                result[i][2] = weight;
                break;
            }
        }

    }



    fstream plik("plik.txt", ios::out);				//wpisuje do pliku
    if (plik.good()) {
        plik << 2 * edges << " " << verticles << " " << result[0][0] << " " << result[verticles - 1][0] << "\n";
        for (int i = 0; i < 2 * edges; i++)	plik << result[i][0] << " " << result[i][1] << " " << result[i][2] << "\n";
        plik.close();
    }
}


GraphGenerator::~GraphGenerator() {
    for (int i = 0; i < 2 * edges; i++)
        delete result[i];
    result = NULL;
}
