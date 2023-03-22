//
// Created by kevin on 14/03/23.
//

#ifndef CODE_GRAPHE_H
#define CODE_GRAPHE_H

#include "../cellule/celluleQuoromD.h"

enum class typeCellue{
    QUOROMD,
    DEFAULT
};

class Graphe {
public:
    Graphe(int size,typeCellue);
    Graphe(int size,typeCellue,int lambda);
    Graphe(int size,typeCellue c,int lambda,double* precalcul);

    void reset();

    Cellule *getCellule(int i);

    void setCelluleDef(double proba);

    bool seuil(double s);

    int nbAlerte();
    int nbDef();
    int nbCellule();

    void setLamba(int lambda);
    void setPreCalcul(double* precalcul);

private:
    vector<Cellule*> listeCellules;

protected:
    typeCellue c;
    double threshold;

};



#endif //CODE_GRAPHE_H
