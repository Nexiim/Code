//
// Created by kevin on 14/03/23.
//

#ifndef CODE_GRAPHE_H
#define CODE_GRAPHE_H

#include "../cellule/celluleQuoromD.h"
#include "../cellule/codeCorrecteur/correcteur.h"


class Graphe {
public:
    Graphe(int size, typeCellule);
    Graphe(int size, typeCellule, double lambda);
    Graphe(int size, typeCellule c, double lambda, double* precalcul);

    void reset();

    Cellule *getCellule(int i);

    void setCelluleDef(double proba);

    bool seuil(double s);

    int nbAlerte();
    int nbDef();
    int nbCellule();

    void contamination();

    void setLamba(double lambda);
    void setPreCalcul(double* precalcul);

private:
    vector<Cellule*> listeCellules;

protected:
    typeCellule c;
    double threshold;

};



#endif //CODE_GRAPHE_H
