//
// Created by kevin on 21/03/23.
//

#ifndef CODE_GRILLE_H
#define CODE_GRILLE_H

#include "graphe.h"



class Grille : public Graphe {
public:
    Grille(int width, int height,typeCellue c);
    Grille(int width, int height,typeCellue c,int lambda);
    Grille(int width, int height,typeCellue c,int lambda,double* preCalcul);

    void reset(double proba,int lambda,double* precalcul);

    Cellule *getCellule(int i, int j);

    void affichageGrille();

    void MAJGrille();

    void setVoisinage(Voisinage v);

private:
    int width;
    int height;

    void Moore8();
    void Moore9();
    void VonNeumann();
    void Toom();
};


#endif //CODE_GRILLE_H