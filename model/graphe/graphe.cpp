//
// Created by kevin on 14/03/23.
//

#include "graphe.h"

/*Fonction lié au graphe*/

Graphe::Graphe(int size,typeCellue c) {
    this->c = c;
    for (int i = 0; i < size; i++) {
        if (c == typeCellue::DEFAULT) this->listeCellules.push_back(new Cellule());
        if (c == typeCellue::QUOROMD) this->listeCellules.push_back(new CelluleQuoromD);
    }
    this->threshold = 0;
}
Graphe::Graphe(int size,typeCellue c,double lambda) {
    this->c = c;
    for (int i = 0; i < size; i++) {
        if (c == typeCellue::QUOROMD) this->listeCellules.push_back(new CelluleQuoromD(lambda));
    }
    this->threshold = 0;
}
Graphe::Graphe(int size,typeCellue c,double lambda,double* precalcul) {
    this->c = c;
    for (int i = 0; i < size; i++) {
        if (c == typeCellue::QUOROMD) this->listeCellules.push_back(new CelluleQuoromD(lambda,precalcul));
    }
    this->threshold = 0;
}

Cellule *Graphe::getCellule(int i) { return this->listeCellules.at(i); }

void Graphe::setCelluleDef(double proba) {
    for (int i = 0; i < this->listeCellules.size(); i++) {
        double r = rand() / double(RAND_MAX);
        if (r < proba) {
            this->getCellule(i)->setEtat(DEFAILANTE);
        } else
            this->getCellule(i)->setEtat(NORMAL);
    }
}

void Graphe::reset() {
    for (int i = 0; i < this->listeCellules.size(); i++) {
        this->getCellule(i)->resetVoisin();
    }
}

bool Graphe::seuil(double s) {
    if (threshold >= s)return true;
    else return false;
}

int Graphe::nbAlerte() {
    int s= 0;
    for (int i = 0; i < this->listeCellules.size(); i++)
        if (getCellule(i)->getEtat() == ALERTE) s++;
    return s;
}

int Graphe::nbDef() {
    int s= 0;
    for (int i = 0; i < this->listeCellules.size(); i++)
        if (getCellule(i)->getEtat() == DEFAILANTE) s++;
    return s;
}


int Graphe::nbCellule() {
    return listeCellules.size();
}

void Graphe::setLamba(double lambda) {
    if (this->c == typeCellue::QUOROMD){
        for (int i = 0; i < this->listeCellules.size(); i++){
            CelluleQuoromD* cell = static_cast<CelluleQuoromD*>(getCellule(i));
            cell->setLambda(lambda);
        }
    }
}

void Graphe::setPreCalcul(double *preCalcul) {
    if (this->c == typeCellue::QUOROMD){
        for (int i = 0; i < this->listeCellules.size(); i++){
            CelluleQuoromD* cell = static_cast<CelluleQuoromD*>(getCellule(i));
            cell->setPreCalcul(preCalcul);
        }
    }
}






