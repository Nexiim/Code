//
// Created by kevin on 24/03/23.
//

#ifndef CODE_VOISINAGE_H
#define CODE_VOISINAGE_H


#include "../graphe/grille.h"

class Voisinage {
public:
    Voisinage(Grille* G);

    void setVoisinageNorme(double r);
    void setVoisinageNorme(int x, int y, double r);

private:
    Grille* G;

};


#endif //CODE_VOISINAGE_H
