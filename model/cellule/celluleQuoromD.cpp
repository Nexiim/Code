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

    if (this->etat != DEFAILANTE && this->nbVoisin() != 0) {
        int N = this->nbVoisin();
        //cout << this->nbVoisin() << endl;
        int nbVoisinN = this->countVoisin(NORMAL);
        int nbVoisinAD = N - nbVoisinN;
        Etat q;

        if (nbVoisinN == 0) q = ALERTE;
        else if (nbVoisinN == N) q = NORMAL;

        else {
            double probaN;
            if (this->preCalculExp == nullptr) {
                double v = (double) N;
                double wn = exp(lambda * (nbVoisinN / v));
                double wad = exp(lambda * (nbVoisinAD / v));
                probaN = wn / (wn + wad);
                
            }
            else {
                int base = this->nbVoisinMax+1;
                int j = N;
                int i = nbVoisinN;
                int position = (j-1)*base+i;
                probaN = this->preCalculExp[position];
            }

            std::random_device rd;
            std::mt19937 gen(rd());

            std::bernoulli_distribution d(probaN);

            if (d(gen)) q = NORMAL;
            else q = ALERTE;
        }
        this->etatSuivant = q;
    }
}

void CelluleQuoromD::setLambda(double lambda) {
    this->lambda = lambda;
}

void CelluleQuoromD::setLambdaAdaptatif(){

}

double CelluleQuoromD::getLambda() {
    return lambda;
}

void CelluleQuoromD::setPreCalcul(double* preCalcul) {
    this->preCalculExp = preCalcul;
}



