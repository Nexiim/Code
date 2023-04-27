//
// Created by kevin on 14/03/23.
//

#ifndef CODE_GRAPHE_H
#define CODE_GRAPHE_H

#include "../cellule/celluleQuoromD.h"
#include "../cellule/codeCorrecteur/correcteur.h"
#include <math.h>


class Graphe {
public:
    Graphe(int size, typeCellule);
    Graphe(int size, typeCellule, double lambda);
    Graphe(int size, typeCellule c, double lambda, double* precalcul);

    void reset(double proba,double lambda,double* precalcul);

    Cellule *getCellule(int i);
    pair<int,int> getPosCellule(int i);

    void setCelluleDef(double proba);

    bool seuil(double s);

    int nbAlerte();
    int nbDef();
    int nbCellule();

    void MAJ();
    void contamination();

    void setVoisinsProche(int nbVoisins);

    void setLambda(double lambda);
    void setPreCalcul(double* precalcul);

    int getWidth() const;
    int getHeight() const;
    pair<int,int> getPosCellule(Cellule* c);

private:
    vector<Cellule*> listeCellules;
    vector<pair<int,int>> posCellule;

    int width{},height{};

protected:
    typeCellule c;
    double threshold;

};



#endif //CODE_GRAPHE_H
