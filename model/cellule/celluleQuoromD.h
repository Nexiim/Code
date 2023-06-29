//
// Created by kevin on 21/03/23.
//

#ifndef CODE_CELLULEQUOROMD_H
#define CODE_CELLULEQUOROMD_H

#include "cellule.h"

class CelluleQuoromD : public Cellule {
public:
    CelluleQuoromD(double lambda);
    CelluleQuoromD(double lambda,double* preCalculExp);
    CelluleQuoromD();

    void transition();

    void setLambda(double lambda);
    void setLambdaAdaptatif();

    double getLambda();
    void setPreCalcul(double* preCalcul);

private:
    double lambda;
    double* preCalculExp;

};

#endif //CODE_CELLULEQUOROMD_H
