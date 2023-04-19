//
// Created by kevin on 20/03/23.
//

#include <thread>
#include "simulationQuoromD.h"


SimulationQuoromD::SimulationQuoromD(int *T, int nbTest, double *probaDef, VoisinageClassique v, double threshold, int height,
                                     int width, double *lambda) : Simulation(T, nbTest, probaDef, threshold) {
    this->v = v;
    this->lambda = lambda;
    this->nbTest = nbTest;
    this->G = new Grille(width, height, typeCellule::QUOROMD);
    this->G->setVoisinage(v);
    this->listExp = nullptr;
}

SimulationQuoromD::SimulationQuoromD(int nbTest,double threshold, int *T,double *lambda, double *probaDef,Grille *G) :Simulation(T, nbTest, probaDef, threshold) {
    this->lambda = lambda;
    this->nbTest = nbTest;
    this->G = G;
    this->v = G->getVoisinage();
    this->listExp = nullptr;
}

void SimulationQuoromD::start() {
    cout << "start simulation"<< endl;
    int nbIter,succes;

    int iLambda = 0;
    while(lambda[iLambda] != NULL) {

        //précalcule des différentes valeurs de probabilité pour QuoromD
        if (listExp != nullptr) free(listExp);
        calculeExp(lambda[iLambda], v);


        int iProba =0;
        while(probaDef[iProba] != NULL){

            int iT =0;
            while(T[iT] != NULL) {

                string data = "lambda:"+to_string( lambda[iLambda])+",probaDef:"+ to_string(probaDef[iProba] )+",T:"+
                              to_string(T[iT]);
                file::GetInstance()->write("-");
                file::GetInstance()->write(data);

                succes = 0;
                for (int k = 0; k < nbTest; k++) {
                    nbIter = 0;
                    
                    //On réinitialise le graphe correctement
                    G->reset(probaDef[iProba], lambda[iLambda], listExp);
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    while (nbIter < T[iT]) {
                        G->MAJGrille();
                        if (G->seuil(threshold)) {
                            succes++;
                            break;
                        }
                        nbIter++;
                    }
                }
                string s = to_string((double) succes / (double) nbTest);
                file::GetInstance()->write(s);
                iT++;
            }
            iProba++;
        }
        iLambda++;
    }
    cout << "end simulation"<< endl;
}



void SimulationQuoromD::startDensitySim() {
    cout << "start simulation"<< endl;

    int nbIter;

    int iLambda = 0;
    while(lambda[iLambda] != NULL) {

        //précalcule des différentes valeurs de probabilité pour QuoromD
        /*if (listExp != nullptr) free(listExp);
        calculeExp(lambda[iLambda], v);*/

        int iProba =0;
        while(probaDef[iProba] != NULL){

            int iT =0;
            while(T[iT] != NULL) {

                //On réinitialise le graphe correctement
                G->reset(probaDef[iProba], lambda[iLambda], listExp);
                string data = "lambda:"+to_string( lambda[iLambda])+",probaDef:"+ to_string(probaDef[iProba] )+",T:"+
                              to_string(T[iT]);
                file::GetInstance()->write("-");
                file::GetInstance()->write(data);
                nbIter = 0;
                while (nbIter < T[iT]) {
                    G->MAJGrille();
                    string s = to_string(nbIter) + "," +
                               to_string((double) G->nbAlerte() / ((double) (G->nbCellule() - G->nbDef())));
                    file::GetInstance()->write(s);
                    if (G->seuil(threshold)) {
                        break;
                    }
                    nbIter++;
                }
                iT++;
            }
            iProba++;
        }
        iLambda++;
    }
    cout << "end simulation"<< endl;
}

void SimulationQuoromD::calculeExp(double lambda, VoisinageClassique v) {
    int nbVoisin = 0;
    if (v == VoisinageClassique::MOORE8) nbVoisin = 8;
    else if (v == VoisinageClassique::MOORE9) nbVoisin = 9;
    else if (v == VoisinageClassique::TOOM) nbVoisin = 3;
    else if (v == VoisinageClassique::VONNEUMAN) nbVoisin = 5;

    this->listExp = (double *) malloc(sizeof(double) * (nbVoisin+1 ) * (nbVoisin ));
    // nombre de cellules voisinnes normales
    for (int i = 0; i <= nbVoisin; i++) {
        //nombre de cellules voisines
        for (int j = 1; j <= nbVoisin; j++) {
            double wn = exp(lambda * ((double) i / j));
            double wad = exp(lambda * ((double) (j - i) / j));
            int position = (j-1) * (nbVoisin+1) + i;
            this->listExp[position] = wn / (wn + wad);
            //cout << "i:"<< i <<" j:" << j << " v:"<< this->listExp[position]<< endl;
        }
    }
}

Grille *SimulationQuoromD::getGrille() {
    return G;
}
