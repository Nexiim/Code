//
// Created by kevin on 20/03/23.
//

#ifndef CODE_SIMULATIONQUOROMD_H
#define CODE_SIMULATIONQUOROMD_H
#include "simulation.h"
#include <omp.h>


class SimulationQuoromD : public Simulation{
public:
    SimulationQuoromD(int* T, int nbTest , double* probaDef, VoisinageClassique v, double threshold, int height, int width, double* lambda);

    void start();
    void start(Focus f);

    void startDensitySim();
    void startDensitySim(Focus f);

    void calculeExp(double lambda, VoisinageClassique v);

private:
    Grille *G;
    VoisinageClassique v;
    double* lambda;
    double* listExp;

    void simulationT();
    void simulationLambda();

    void simulationDensityT();
    void simulationDensityLambda();
    void simulationDensityProbadef();
};
#endif //CODE_SIMULATIONQUOROMD_H
