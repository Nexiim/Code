//
// Created by kevin on 14/03/23.
//

#include "graphe.h"

/*
Constructor
*/

Graphe::Graphe(int size, typeCellule c) {
    this->c = c;
    this->width = size/8;
    this->height = size/8;
    for (int i = 0; i < size; i++) {
        if (c == typeCellule::DEFAULT) this->listeCellules.push_back(new Cellule());
        if (c == typeCellule::QUOROMD) this->listeCellules.push_back(new CelluleQuoromD());
        if (c == typeCellule::CORRECTEUR) this->listeCellules.push_back(new Correcteur());

        this->posCellule.emplace_back(rand()%this->width,rand()%this->height);
    }
    this->threshold = 0;
}

Graphe::Graphe(int size, typeCellule c, double lambda) {
    this->c = c;
    for (int i = 0; i < size; i++) {
        if (c == typeCellule::QUOROMD) this->listeCellules.push_back(new CelluleQuoromD(lambda));
    }
    this->threshold = 0;
}

Graphe::Graphe(int size, typeCellule c, double lambda, double* precalcul) {
    this->c = c;
    for (int i = 0; i < size; i++) {
        if (c == typeCellule::QUOROMD) this->listeCellules.push_back(new CelluleQuoromD(lambda, precalcul));
    }
    this->threshold = 0;
}

/*
fonction
*/

void Graphe::reset(double proba, double lambda, double *precalcul) {
    for (int i = 0; i < this->listeCellules.size(); i++) {
            auto* cell = dynamic_cast<CelluleQuoromD*>(getCellule(i));
            cell->setLambda(lambda);
            cell->setPreCalcul(precalcul);
            double r = rand() / double(RAND_MAX);
            if (r < proba) {
              this->getCellule(i)->setEtat(DEFAILANTE);
            } else
              this->getCellule(i)->setEtat(NORMAL);
    }
    this->threshold = 0;
}

void Graphe::setVoisinsProche(int nbVoisins){
    int* plusProche = (int*)malloc(sizeof(int)*nbVoisins);
    auto* dist = (double*)(malloc(sizeof(double) * nbVoisins));

    for (int i = 0; i < this->listeCellules.size();i++){

        for (int j = 0; j < nbVoisins; j++){
            dist[j] = numeric_limits<int>::max();
        }

       for (int j = 0; j < this->listeCellules.size();j++){
            if (i != j){
                  double distIJ = sqrt(pow((this->posCellule.at(i).first - this->posCellule.at(j).first),2) +
                                   pow((this->posCellule.at(i).second - this->posCellule.at(j).second),2));
                  for (int k =0; k < nbVoisins; k++){
                      if( dist[k] > distIJ){
                        plusProche[k] = j;
                        dist[k] = distIJ;
                        break;
                      }
                  }
            }
       }

       for (int j = 0; j < nbVoisins; j++){
            this->listeCellules.at(i)->addVoisin(this->listeCellules.at(plusProche[j]));
       }
    }

    free(plusProche);
    free(dist);
}

void Graphe::contamination() {
    for (int i = 0; i < this->listeCellules.size();i++)
            this->getCellule(i)->contamination();

    for (int i = 0; i < this->listeCellules.size();i++)
        this->getCellule(i)->nextT();
}

void Graphe::MAJ() {
    for (int i = 0; i < this->listeCellules.size(); i++) {
            this->getCellule(i)->transition();
    }

    double nbDef = 0;
    double nbAlerte = 0;

    for (int i = 0; i < this->listeCellules.size(); i++) {
            this->getCellule(i)->nextT();
            if (this->getCellule(i)->getEtat() == ALERTE) nbAlerte++;
            else if (this->getCellule(i)->getEtat() == DEFAILANTE) nbDef++;
    }
    this->threshold = nbAlerte / ((double)(width*height - nbDef));
}

/* 
getter setter
*/

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

void Graphe::setLambda(double lambda) {
    if (this->c == typeCellule::QUOROMD){
        for (int i = 0; i < this->listeCellules.size(); i++){
            auto* cell = dynamic_cast<CelluleQuoromD*>(getCellule(i));
            cell->setLambda(lambda);
        }
    }
}

void Graphe::setPreCalcul(double *preCalcul) {
    if (this->c == typeCellule::QUOROMD){
        for (int i = 0; i < this->listeCellules.size(); i++){
            auto* cell = dynamic_cast<CelluleQuoromD*>(getCellule(i));
            cell->setPreCalcul(preCalcul);
        }
    }
}

int Graphe::getHeight(){
    return this->height;
}


int Graphe::getWidth(){
    return this->width;
}

pair<int, int> Graphe::getPosCellule(int i) {
    return this->posCellule.at(i);
}


pair<int, int> Graphe::getPosCellule(Cellule *c) {
    for (int i = 0; i < this->listeCellules.size(); i++){
       if (this->listeCellules.at(i) == c){
            return this->posCellule.at(i);
       }
    }
    return pair<int,int>(-1,-1);
}



typeVoisinage Graphe::getVoisinage() {
    return this->t;
}