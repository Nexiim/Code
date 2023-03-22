//
// Created by kevin on 21/03/23.
//

#include "grille.h"

/*Fonction lié à la grille*/
Grille::Grille(int witdh, int height,typeCellue c) : Graphe(witdh * height,c) {
    this->height = height;
    this->width = witdh;
    this->c =c;
}

Grille::Grille(int witdh, int height,typeCellue c,int lambda) : Graphe(witdh * height,c,lambda) {
    Grille(witdh,height,c);
}

Grille::Grille(int witdh, int height,typeCellue c,int lambda,double* precalcul) : Graphe(witdh * height,c,lambda, precalcul) {
    Grille(witdh,height,c);
}

Cellule* Grille::getCellule(int i, int j) {
    return Graphe::getCellule((j * this->width) + i);
}

void Grille::MAJGrille() {

    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            this->getCellule(i, j)->transition();
        }
    }

    double nbDef = 0;
    double nbAlerte = 0;


    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            this->getCellule(i, j)->nextT();
            if (this->getCellule(i,j)->getEtat() == ALERTE) nbAlerte++;
            else if (this->getCellule(i,j)->getEtat() == DEFAILANTE) nbDef++;
        }
    }
    this->threshold = nbAlerte / ((double)(width*height - nbDef));
}

void Grille::affichageGrille() {
    for (int j = 0; j < this->height; j++) {
        for (int i = 0; i < this->width; i++) {
            std::cout << " " << this->getCellule(i, j)->getEtat();
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Grille::Moore8() {
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            this->getCellule(i,j)->setNbVoisinMax(Voisinage::MOORE8);
            for (int a = -1; a < 2; a++) {
                for (int b = -1; b < 2; b++) {
                    if (a != 0 || b != 0) {
                        if (((i + a) >= 0) & ((i + a) <= (this->width - 1)) & ((j + b) >= 0) &
                            ((j + b) <= (this->height - 1))) {
                            this->getCellule(i, j)->addVoisin(this->getCellule(i + a, j + b));
                        }
                    }
                }
            }
        }
    }
}

void Grille::Moore9() {
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            this->getCellule(i,j)->setNbVoisinMax(Voisinage::MOORE9);
            for (int a = -1; a < 2; a++) {
                for (int b = -1; b < 2; b++) {
                    if (((i + a) >= 0) & ((i + a) <= (this->width - 1)) & ((j + b) >= 0) &
                        ((j + b) <= (this->height - 1))) {
                        this->getCellule(i, j)->addVoisin(this->getCellule(i + a, j + b));
                    }
                }
            }
        }
    }
}

void Grille::VonNeumann() {
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            this->getCellule(i,j)->setNbVoisinMax(Voisinage::VONNEUMAN);
            this->getCellule(i, j)->addVoisin(this->getCellule(i, j));
            for (int a = -1; a < 2; a++) {
                for (int b = -1; b < 2; b++) {
                    if (a != b & a != -b) {
                        if (((i + a) >= 0) & ((i + a) <= (this->width - 1)) & ((j + b) >= 0) &
                            ((j + b) <= (this->height - 1))) {
                            this->getCellule(i, j)->addVoisin(this->getCellule(i + a, j + b));
                        }
                    }
                }
            }
        }
    }
}

void Grille::Toom() {
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            this->getCellule(i,j)->setNbVoisinMax(Voisinage::TOOM);
            this->getCellule(i, j)->addVoisin(this->getCellule(i, j));
            if (i + 1 < this->width) this->getCellule(i, j)->addVoisin(this->getCellule(i + 1, j));
            if (j - 1 >= 0) this->getCellule(i, j)->addVoisin(this->getCellule(i, j - 1));
        }
    }
}

void Grille::setVoisinage(Voisinage v) {
    if (v == Voisinage::MOORE8) this->Moore8();
    else if (v == Voisinage::MOORE9) this->Moore9();
    else if (v == Voisinage::TOOM) this->Toom();
    else if (v == Voisinage::VONNEUMAN) this->VonNeumann();
    else cout << " erreur setup voisinage";
}

void Grille::reset(double proba, int lambda, double *precalcul) {
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            auto* cell = dynamic_cast<CelluleQuoromD*>(getCellule(i,j));
            cell->setLambda(lambda);
            cell->setPreCalcul(precalcul);
            double r = rand() / double(RAND_MAX);
            if (r < proba) {
                this->getCellule(i,j)->setEtat(DEFAILANTE);
            } else
                this->getCellule(i,j)->setEtat(NORMAL);
        }
    }
    this->threshold = 0;
}