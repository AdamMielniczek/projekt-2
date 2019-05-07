#include "Operations.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>
using namespace std;


Operations::Operations() {

}


void Operations::createDirectedGraph() {				//wczytuje plik na podstawie ktorego utworzy tablice bazowa z danymi dla skierowanego
    fstream file("plik.txt", std::ios::in);
    if (file.is_open()) {
        file >> edges;
        file >> verticles;
        file >> startVerticle;
        file >> finishVerticle;
        directedGraph = new int *[edges];
        if (file.fail())
            cout << "blad" << endl;
        else {
            int source, destination, localWeight;
            for (int i = 0; i < edges; i++) {
                file >> source;
                file >> destination;
                file >> localWeight;

                if (file.fail()) {
                    cout << "blad" << endl;
                    break;
                }
                else {
                    directedGraph[i] = new int[3];
                    directedGraph[i][0] = source;
                    directedGraph[i][1] = destination;
                    directedGraph[i][2] = localWeight;
                }
            }
        }

        file.close();
    }
    else
        cout <<"blad" << endl;

}

void Operations::createUndirectedGraph() {			//tablica bez powtorzonych wierzcholkow potrzebna dla operacji na grafie nieskierowanym

    bool *duplicate;
    duplicate = new bool[edges];
    for (int i = 0; i < edges; i++)
        duplicate[i] = false;
    undirectedGraph = new int *[edges];
    for (int i = 0; i < edges; i++)
        undirectedGraph[i] = NULL;

    for (int i = 0; i < edges; i++) {
        for (int j = 0; j < i; j++) {
            if ((directedGraph[i][0] == directedGraph[j][0] && directedGraph[i][1] == directedGraph[j][1]) || (directedGraph[i][1] == directedGraph[j][0] && directedGraph[i][0] == directedGraph[j][1])) {
                duplicate[i] = false;
                break;
            }
            duplicate[i] = true;
        }
    }

    duplicate[0] = true;
    edgeY = 0;
    for (int i = 0; i < edges; i++) {
        if (duplicate[i] == true) {
            undirectedGraph[edgeY] = new int[3];
            undirectedGraph[edgeY][0] = directedGraph[i][0];
            undirectedGraph[edgeY][1] = directedGraph[i][1];
            undirectedGraph[edgeY][2] = directedGraph[i][2];
            edgeY++;
        }
    }

    delete[] duplicate;
}

void Operations::createMatrixForDirectedGraph() {
    matrixDirected = new int *[verticles];
    for (int i = 0; i < verticles; i++) {
        matrixDirected[i] = new int[verticles];
    }
    for (int i = 0; i < verticles; i++) {
        for (int j = 0; j < verticles; j++) {
            matrixDirected[i][j] = 0;
        }
    }
    for (int i = 0; i < edges; i++) {
        matrixDirected[directedGraph[i][0]][directedGraph[i][1]] = directedGraph[i][2];
    }

}

void Operations::createMatrixForUndirectedGraph() {
    matrixUndirected = new int *[verticles];
    for (int i = 0; i < verticles; i++) {
        matrixUndirected[i] = new int[verticles];
    }
    for (int i = 0; i < verticles; i++) {
        for (int j = 0; j < verticles; j++) {
            matrixUndirected[i][j] = 0;
        }
    }

    for (int i = 0; i < edgeY; i++) {
        matrixUndirected[undirectedGraph[i][0]][undirectedGraph[i][1]] = undirectedGraph[i][2];
        matrixUndirected[undirectedGraph[i][1]][undirectedGraph[i][0]] = undirectedGraph[i][2];
    }
}


void Operations::makeUndirectedNeighbourList() {
    listUndirectional = new elementOfList *[verticles];
    for (int i = 0; i < verticles; i++)
        listUndirectional[i] = NULL;

    for (int i = 0; i < edgeY; i++) {
        tmp = new elementOfList;
        tmp->n = undirectedGraph[i][1];
        tmp->weight = undirectedGraph[i][2];
        tmp->next = listUndirectional[undirectedGraph[i][0]];
        listUndirectional[undirectedGraph[i][0]] = tmp;


        tmp = new elementOfList;
        tmp->n = undirectedGraph[i][0];
        tmp->weight = undirectedGraph[i][2];
        tmp->next = listUndirectional[undirectedGraph[i][1]];
        listUndirectional[undirectedGraph[i][1]] = tmp;

    }
}

void Operations::makeDirectedNeighbourList(){
    neighbourList1 = new elementOfList *[verticles];
    for (int i = 0; i < verticles; i++)
        neighbourList1[i] = NULL;

    for (int i = 0; i < edges; i++) {

        tmp = new elementOfList;    // Tworzymy nowy element
        tmp->n = directedGraph[i][1];          // Numerujemy go
        tmp->weight = directedGraph[i][2];
        tmp->next = neighbourList1[directedGraph[i][0]];    // Dodajemy go na początek listy
        neighbourList1[directedGraph[i][0]] = tmp;
    }

}



void Operations::dijkstryList(int start) {
    unsigned long czas = 0;
    int *cost, *path, *Stack, stackPointer;
    int i, j, u, w;    //do petli
    bool *visited;
    DWORD go = GetTickCount();
    for (w = 0; w < 100; w++) {
        cost = new int[verticles];
        path = new int[verticles];
        visited = new bool[verticles];
        Stack = new int[verticles];
        stackPointer = 0;

        for (int i = 0; i < verticles; i++) {
            cost[i] = MAXINT;
            path[i] = -1;
            visited[i] = false;
        }


        cost[start] = 0;

        for (int i = 0; i < verticles; i++) {
            for (j = 0; visited[j]; j++);
            for (u = j++; j < verticles; j++)
                if (!visited[j] && (cost[j] < cost[u]))
                    u = j;

            visited[u] = true;


            for (tmp = neighbourList1[u]; tmp; tmp = tmp->next)
                if (!visited[tmp->n] && (cost[tmp->n] > cost[u] + tmp->weight)) {
                    cost[tmp->n] = cost[u] + tmp->weight;
                    path[tmp->n] = u;
                }
        }


    }
    DWORD end = GetTickCount();
    czas = end - go;
    cout << "czas czas z listy: " << czas << endl;

//    cout << "Startowy " << startVerticle << endl;
//    cout << "End    Dist    Path" << endl;
//    for (i = 0; i < verticles; i++) {
//        cout << i << ": ";
//        for (j = i; j > -1; j = path[j]) Stack[stackPointer++] = j;
//        cout << "   | " << cost[i] << " |   ";
//        while (stackPointer) cout << Stack[--stackPointer] << " ";
//        cout << endl;
//    }

        delete[] cost;
        delete[] path;
        delete[] Stack;
        delete[] visited;

}
    void Operations::dijkstryMatrix(int start) {
        unsigned long czas = 0;
        int *cost, *path, *Stack, stackPointer;
        int i, j, u, w; // do petli
        bool *visited;
        DWORD go = GetTickCount();
        for (w = 0; w < 100; w++) {
            cost = new int[verticles];
            path = new int[verticles];
            visited = new bool[verticles];
            Stack = new int[verticles];
            stackPointer = 0;

            for (int i = 0; i < verticles; i++) {
                cost[i] = MAXINT;
                path[i] = -1;
                visited[i] = false;
            }

            cost[start] = 0;


            for (int i = 0; i < verticles; i++) {
                for (j = 0; visited[j]; j++);
                for (u = j++; j < verticles; j++)
                    if (!visited[j] && (cost[j] < cost[u])) u = j;

                visited[u] = true;


                for (int g = 0; g < verticles; g++) {
                    if (matrixDirected[u][g] != 0) {
                        if (!visited[g] && (cost[g] > cost[u] + matrixDirected[u][g])) {
                            cost[g] = cost[u] + matrixDirected[u][g];
                            path[g] = u;
                        }
                    }
                }

            }

        }
        DWORD end = GetTickCount();
        czas = end - go;
        cout << "czas macierzowaej: " << czas << endl;


//        cout << "Startowy " << startVerticle << endl;
//        cout << "End    Dist    Path" << endl;
//        for (i = 0; i < verticles; i++) {
//            cout << i << ": ";
//            for (j = i; j > -1; j = path[j]) Stack[stackPointer++] = j;
//            cout << "   | " << cost[i] << " |   ";
//            while (stackPointer) cout << Stack[--stackPointer] << " ";
//            cout << endl;
//        }

        delete[] cost;
        delete[] path;
        delete[] Stack;
        delete[] visited;
    }

    bool Operations::readFromFile() {
        bool success = false;
        string filename;
        cout << "Podaj nazwe pliku z koncowka .txt " << endl;
        cin >> filename;

        fstream file(filename, std::ios::in);
        if (file.is_open()) {
            file >> edges;
            file >> verticles;
            file >> startVerticle;
            file >> finishVerticle;
            directedGraph = new int *[edges];
            if (file.fail())
                cout << "blad" << endl;
            else {
                int source, destination, localWeight;
                for (int i = 0; i < edges; i++) {
                    file >> source;
                    file >> destination;
                    file >> localWeight;

                    if (file.fail()) {
                        cout << "blad" << endl;
                        break;
                    } else {
                        directedGraph[i] = new int[3];
                        directedGraph[i][0] = source;
                        directedGraph[i][1] = destination;
                        directedGraph[i][2] = localWeight;
                    }
                }
            }

            file.close();
            success = true;
        } else {
            cout << "blad" << endl;
            success = false;
        }

        return success;
    }

Operations::~Operations() {

    for (int i = 0; i < edges; i++) {
        delete[] directedGraph[i];
        delete[] undirectedGraph[i];
    }
    directedGraph = NULL;
    undirectedGraph = NULL;

    for (int i = 0; i < verticles; i++) {
        delete[] matrixDirected[i];
        delete[] matrixUndirected[i];
    }

    matrixDirected = NULL;
    matrixUndirected = NULL;



}
