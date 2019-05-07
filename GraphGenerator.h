
#ifndef PROJEKT_2_V2_GRAPHGENERATOR_H
#define PROJEKT_2_V2_GRAPHGENERATOR_H
#pragma once
class GraphGenerator {

private:
    int maxWeight, minEdges, edges, verticles;
    double maxEdges;
    int **result;

public:
    GraphGenerator();
    GraphGenerator(int);
    ~GraphGenerator();
};



#endif //PROJEKT_2_V2_GRAPHGENERATOR_H


