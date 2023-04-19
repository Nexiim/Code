//
// Created by kevin on 21/03/23.
//

#include "celluleQuoromD.h"

CelluleQuoromD::CelluleQuoromD(){
    this->preCalculExp = nullptr;
}

CelluleQuoromD::CelluleQuoromD(double lambda){
    this->lambda = lambda;
    this->preCalculExp = nullptr;
}

CelluleQuoromD::CelluleQuoromD(double lambda, double *preCalculExp) {
    this->lambda = lambda;
    this->preCalculExp = preCalculExp;
}

void CelluleQuoromD::transition(){
    if (this->etat != DEFAILANTE) {
        //cout << this->nbVoisin() << endl;
        int nbVoisinN = this->countVoisin(NORMAL);
        int nbVoisinAD = this->nbVoisin() - nbVoisinN;

        if (nbVoisinAD == this->nbVoisin()) this->etatSuivant = ALERTE;
        else if (nbVoisinN == this->nbVoisin()) this->etatSuivant = NORMAL;

        else {
            double probaN;
            if (this->preCalculExp == nullptr) {
                auto v = (double) this->nbVoisin();
                double wn = exp(lambda * (nbVoisinN / v));
                double wad = exp(lambda * (nbVoisinAD / v));
                probaN = wn / (wn + wad);
                //cout << probaN << endl;
            }
            else {
                int base = this->nbVoisinMax+1;
                int j = this->nbVoisin();
                int i = nbVoisinN;
                int position = (j-1)*base+i;
                probaN = this->preCalculExp[position];
            }


            double r = rand() / double(RAND_MAX);

            if (r < probaN) this->etatSuivant = NORMAL;
            else this->etatSuivant = ALERTE;
        }
    }
}

void CelluleQuoromD::setLambda(double lambda) {
    this->lambda = lambda;
}

double CelluleQuoromD::getLambda() {
    return lambda;
}

void CelluleQuoromD::setPreCalcul(double* preCalcul) {
    this->preCalculExp = preCalcul;
}



