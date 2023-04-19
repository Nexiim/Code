//
// Created by kevin on 20/03/23.
//

#ifndef CODE_SIMULATIONQUOROMD_H
#define CODE_SIMULATIONQUOROMD_H
#include "simulation.h"
#include <omp.h>
#include "../model/util/file.h"


class SimulationQuoromD : public Simulation{
public:
    SimulationQuoromD(int* T, int nbTest , double* probaDef, VoisinageClassique v, double threshold, int height, int width, double* lambda);

    SimulationQuoromD(int nbTest, double threshold, int *T, double *lambda, double *probaDef, Grille *G);

    void start();
    void start(Focus f);

    void startDensitySim();

    void calculeExp(double lambda, VoisinageClassique v);
    Grille* getGrille();

private:
    Grille *G;
    VoisinageClassique v;
    double* lambda;
    double* listExp;

    void simulationT();
    void simulationLambda();


};
#endif //CODE_SIMULATIONQUOROMD_H
