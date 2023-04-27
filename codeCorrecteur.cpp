//
// Created by kevin on 19/04/23.
//


#include "model/graphe/grille.h"
#include "visualisation/codeCorrecteur/VisuCodeCorrecteur.h"

#define H 30
#define W 30

void setupGrille(Grille *G){
    int c1 = 0;
    int c2 = 0;
    for (int i = 0; i < G->getWidth(); i++) {
        c1 = c2;
        for (int j = 0; j < G->getHeight(); j++) {
            Correcteur *c = dynamic_cast<Correcteur *>(G->getCellule(i, j));
            c1 = (c1 + 1) % 3;
            c->setValue(c1);
        }
        c2 = (c2 + 1) % 3;
    }
}

int main() {

    Grille G(H, W, typeCellule::CORRECTEUR);
    G.setBordure(Bordure::TORIQUE);
    G.setVoisinage(VoisinageClassique::TOOM);

    setupGrille(&G);

    VisuCodeCorrecteur v(H, W, &G);
    v.initVisualisation();

    v.loopEvent();
}