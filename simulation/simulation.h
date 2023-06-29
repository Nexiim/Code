//
// Created by kevin on 15/03/23.
//

#ifndef CODE_SIMULATION_H
#define CODE_SIMULATION_H

#include <fstream>
#include "../model/graphe/graphe.cuh"
#include "../model/graphe/grille.cuh"



class Simulation {
public:
    Simulation(int* T, int nbTest, double* probaDef,double threshold);

    void writeFile(string s);
    void openFile(string name);
    void closeFile();

private:

protected:
    ofstream file;
    int nbTest;
    double threshold;
    int* T;
    double* probaDef;

};



#endif //CODE_SIMULATION_H
