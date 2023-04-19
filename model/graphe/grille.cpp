//
// Created by kevin on 21/03/23.
//

#include "grille.h"

/*Fonction lié à la grille*/
Grille::Grille(int witdh, int height, typeCellule c) : Graphe(witdh * height, c) {
    this->height = height;
    this->width = witdh;
    this->c =c;
    this->b = Bord::TORIQUE;
}

Grille::Grille(int witdh, int height, typeCellule c, double lambda) : Graphe(witdh * height, c, lambda) {
    this->height = height;
    this->width = witdh;
    this->c =c;
    this->b = Bord::TORIQUE;
}

Grille::Grille(int witdh, int height, typeCellule c, double lambda, double* precalcul) : Graphe(witdh * height, c, lambda, precalcul) {
    this->height = height;
    this->width = witdh;
    this->c =c;
    this->b = Bord::TORIQUE;
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
            this->getCellule(i,j)->setNbVoisinMax(VoisinageClassique::MOORE8);
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
            this->getCellule(i,j)->setNbVoisinMax(VoisinageClassique::MOORE9);
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
            this->getCellule(i,j)->setNbVoisinMax(VoisinageClassique::VONNEUMAN);
            this->getCellule(i, j)->addVoisin(this->getCellule(i, j));
            for (int a = -1; a < 2; a++) {
                for (int b = -1; b < 2; b++) {
                    if (a != b & a != -b) {
                        if(this->b == Bord::TORIQUE){
                            this->getCellule(i, j)->addVoisin(this->getCellule((this->width+(i + a))% this->width,
                                                                               (this->height+(j + b))% this->height));
                        }
                        else if(this->b == Bord::BORD) {
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
}

void Grille::Toom() {
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            if(this->b == Bord::TORIQUE) {
                this->getCellule(i, j)->addVoisin(this->getCellule((i + 1)%this->width, j));
                this->getCellule(i, j)->addVoisin(this->getCellule(i, (j+1)% this->height));
            }
            else if(this->b == Bord::BORD) {
                this->getCellule(i, j)->setNbVoisinMax(VoisinageClassique::TOOM);
                this->getCellule(i, j)->addVoisin(this->getCellule(i, j));
                if (i + 1 < this->width) this->getCellule(i, j)->addVoisin(this->getCellule(i + 1, j));
                if (j - 1 >= 0) this->getCellule(i, j)->addVoisin(this->getCellule(i, j - 1));
            }
        }
    }
}

void Grille::setVoisinage(VoisinageClassique v) {
    this->v = v;
    if (v == VoisinageClassique::MOORE8) this->Moore8();
    else if (v == VoisinageClassique::MOORE9) this->Moore9();
    else if (v == VoisinageClassique::TOOM) this->Toom();
    else if (v == VoisinageClassique::VONNEUMAN) this->VonNeumann();
    else {
        this->v = static_cast<VoisinageClassique>(NULL);
        cout << " erreur setup voisinage";
    }
}

void Grille::reset(double proba, double lambda, double *precalcul) {
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

int Grille::getWidth() {
    return this->width;
}

int Grille::getHeight() {
    return this->height;
}

VoisinageClassique Grille::getVoisinage() {
    return this->v;
}
