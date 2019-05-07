#ifndef PROJEKT_2_V2_OPERATIONS_H
#define PROJEKT_2_V2_OPERATIONS_H
#pragma once
class Operations {

private:
    struct elementOfList {
        elementOfList *next;
        int n;
        int weight;
    };

    int verticles;
    int edges;

    int **directedGraph;
    int **undirectedGraph;
    int **matrixDirected;
    int **matrixUndirected;
    int **resultsForMatrix;
    int **resultForList;

    int edgeY;

    elementOfList **listUndirectional;
    elementOfList **neighbourList1, *tmp, *tmpDelete;
    const int MAXINT = 2147483647;

public:
    int startVerticle, finishVerticle;

    Operations();

    void createDirectedGraph();
    void createUndirectedGraph();

    void createMatrixForDirectedGraph();
    void createMatrixForUndirectedGraph();

    void printMatrixDirected();
    void printMatrixUndirected();

    void makeUndirectedNeighbourList();
    void makeDirectedNeighbourList();

    void printUndirectedNeighbourList();
    void printDirectedNeighbourList();

    void primMatrix();
    void primList();

    void dijkstryMatrix(int);
    void dijkstryList(int);

    bool readFromFile();

    ~Operations();
};

#endif

