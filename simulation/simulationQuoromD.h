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
    SimulationQuoromD(int* T, int nbTest , double* probaDef, typeVoisinage v, double threshold, int height, int width, double* lambda);
    SimulationQuoromD(int *T, int nbTest, double *probaDef, typeVoisinage v,double paramVoisinage, double threshold, int height, int width, double *lambda);
    SimulationQuoromD(int nbTest, double threshold, int *T, double *lambda, double *probaDef, Grille *G);
    SimulationQuoromD(int nbTest, double threshold, int *T, double *lambda, double *probaDef, Graphe *G);

    void start();
    void startDensitySim();

    void calculeExp(double lambda, typeVoisinage v);
    Graphe* getGraphe();

private:
    Graphe* G;
    typeVoisinage v;
    double* lambda;
    double* listExp;

};
#endif //CODE_SIMULATIONQUOROMD_H
