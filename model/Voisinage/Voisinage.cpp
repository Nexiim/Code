//
// Created by kevin on 24/03/23.
//

#include "Voisinage.h"

Voisinage::Voisinage(Grille* G) {
    this->G = G;
}

void Voisinage::setVoisinageNorme(double r) {
    pair<double,double> points[G->getWidth()][G->getWidth()];

    for (int i = 0; i < G->getWidth(); i++){
        for (int j = 0; j <G->getWidth(); j++){
            points[i][j] = make_pair((((double) rand() / (RAND_MAX))-0.5),((double)rand() / (RAND_MAX))-0.5);
        }
    }

    for (int i = 0; i < G->getWidth(); i++){
        for (int j = 0; j <G->getHeight(); j++){

            for (int  a = floor(i-r); a <= ceil(i+r); a++){
                for (int b = floor(j-r); b <= ceil(j+r); b++){

                    if (a >= 0 && a < G->getWidth() && b >=0 && b < G->getHeight()) {
                        /*on vérifie qu'on est dans le carrée inscrit dans le cercle
                         on utilise 1.5 mais il faut simplement une valeur supérieur sqrt(2)*/
                        if (abs(i - a) < floor(r)/1.5-1 & abs(j - b) < floor(r)/1.5-1) {
                            G->getCellule(i, j)->addVoisin(G->getCellule(a, b));
                        } else {
                        double distX = i + points[i][j].first - a + points[a][b].first;
                        double distY = j + points[i][j].second - b + points[a][b].second;
                        double distEcuclidienne = sqrt(pow(distX, 2) + pow(distY, 2));
                        if (distEcuclidienne < r) {
                            G->getCellule(i, j)->addVoisin(G->getCellule(a, b));
                        }
                    }

                    }

                }
            }
        }
    }

}
