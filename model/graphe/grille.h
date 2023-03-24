//
// Created by kevin on 21/03/23.
//

#ifndef CODE_GRILLE_H
#define CODE_GRILLE_H

#include "graphe.h"



class Grille : public Graphe {
public:
    Grille(int width, int height,typeCellue c);
    Grille(int width, int height,typeCellue c,double lambda);
    Grille(int width, int height,typeCellue c,double lambda,double* preCalcul);

    void reset(double proba,double lambda,double* precalcul);

    Cellule *getCellule(int i, int j);

    void affichageGrille();

    void MAJGrille();

    void setVoisinage(VoisinageClassique v);
    int getWidth();
    int getHeight();

private:
    int width;
    int height;

    void Moore8();
    void Moore9();
    void VonNeumann();
    void Toom();
};


#endif //CODE_GRILLE_H
