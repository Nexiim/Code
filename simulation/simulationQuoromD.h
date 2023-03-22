//
// Created by kevin on 20/03/23.
//

#ifndef CODE_SIMULATIONQUOROMD_H
#define CODE_SIMULATIONQUOROMD_H
#include "simulation.h"
#include <omp.h>


class SimulationQuoromD : public Simulation{
public:
    SimulationQuoromD(int* T, int nbTest , double* probaDef, Voisinage v, double threshold, int height, int width, int* lambda);

    void start();
    void start(Focus f);
    void startDensitySim();
    void startDensitySim(Focus f);
    void calculeExp(int lambda, Voisinage v);

private:
    Grille *G;
    Voisinage v;
    int* lambda;
    double* listExp;

    void simulationT();
    void simulationLambda();
    void simulationProbadef();

    void simulationDensityT();
    void simulationDensityLambda();
    void simulationDensityProbadef();
};
#endif //CODE_SIMULATIONQUOROMD_H
