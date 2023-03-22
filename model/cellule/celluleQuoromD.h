//
// Created by kevin on 21/03/23.
//

#ifndef CODE_CELLULEQUOROMD_H
#define CODE_CELLULEQUOROMD_H

#include "cellule.h"

class CelluleQuoromD : public Cellule {
public:
    CelluleQuoromD(int lambda);
    CelluleQuoromD(int lambda,double* preCalculExp);
    CelluleQuoromD(){};

    void transition();

    void setLambda(int lambda);
    int getLambda();
    void setPreCalcul(double* preCalcul);

private:
    int lambda;
    double* preCalculExp;

};

#endif //CODE_CELLULEQUOROMD_H
