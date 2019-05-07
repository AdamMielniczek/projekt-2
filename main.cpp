#include <iostream>
#include <windows.h>
#include "GraphGenerator.h"
#include "Operations.h"

using namespace std;

void randomGraph() {


    GraphGenerator generator(5);
    Operations graph;
    graph.createDirectedGraph();
    graph.createUndirectedGraph();
    graph.createMatrixForDirectedGraph();
    graph.createMatrixForUndirectedGraph();
    graph.makeDirectedNeighbourList();
    graph.makeUndirectedNeighbourList();

    int choice = 0;
    do {
        cout << endl;

        cout << "wybierz opcje " << endl;
        cout << "[1] algorytm dijkstry dla grafu skierowanego na bazie reprezentacji macierzowej" << endl;
        cout << "[2] algorytm dijkstry dla grafu skierowanego na bazie reprezentacji listowej" << endl;
        cout << "[3] koniec" << endl << endl;
        cin >> choice;

        switch (choice) {

            case 1:
                graph.dijkstryMatrix(graph.startVerticle);
                break;
            case 2:
                graph.dijkstryList(graph.startVerticle);
                break;
            default:
                //cout << "bledny wybor" << endl;
                break;
        }

    } while (choice != 3);
}

void readGraph() {
    bool success;
    Operations graph;
    do {
        success = graph.readFromFile();
    } while (success != true);

    graph.createUndirectedGraph();
    graph.createMatrixForDirectedGraph();
    graph.createMatrixForUndirectedGraph();
    graph.makeDirectedNeighbourList();
    graph.makeUndirectedNeighbourList();

    int choice = 0;
    do {
        cout << endl;
        cout << "wybierz opcje " << endl;
        cout << "[1] algorytm dijkstry dla grafu skierowanego na bazie reprezentacji macierzowej" << endl;
        cout << "[2] algorytm dijkstry dla grafu skierowanego na bazie reprezentacji listowej" << endl;
        cout << "[3] koniec" << endl << endl;
        cin >> choice;

        switch (choice) {

            case 1:
                graph.dijkstryMatrix(graph.startVerticle);
                break;
            case 2:
                graph.dijkstryList(graph.startVerticle);
                break;
            default:
                //cout << "bledny wybor" << endl;
                break;
        }

    } while (choice != 3);


}


int main() {

    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Program sluzy do badania efektywnosci algorytmow grafowych dijkstry w zaleznosci od sposobu reprezentajci grafu w pamieci komputera. " << endl;
    cout << "Graf jest wczytywany z pliku badz losowany, przy czym przy wczytywniu z pliku zapisywane sa jego 2 wersje: 1) skierowany - kazda para wierzcholkow jest brana pod uwage, 2) nieskierowany - jesli w pliku pojawi sie krawedz powtorzona, jest ona ignorowana" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    int randomOrFile = 0;

    do {
        cout << "wybierz sposob wygenerowania grafu " << endl;
        cout << "[1] losowo" << endl;
        cout << "[2] z pliku" << endl;
        cout << "[3] wyjscie" << endl << endl;
        cin >> randomOrFile;

        switch (randomOrFile) {
            case 1:
                randomGraph();
                break;

            case 2:
                readGraph();
                break;
            case 3:
                break;
            default:
                cout << "bledny wybor" << endl;
                break;
        }
    } while (randomOrFile != 3);




    //system("PAUSE");
}