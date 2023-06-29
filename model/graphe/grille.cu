//
// Created by kevin on 21/03/23.
//

#include "grille.cuh"



/*Fonction lié à la grille*/
Grille::Grille(int witdh, int height, typeCellule c) : Graphe(witdh * height, c) {
    this->height = height;
    this->width = witdh;
    this->c =c;
    this->b = Bordure::BORD;
}

Grille::Grille(int witdh, int height, typeCellule c, double lambda) : Graphe(witdh * height, c, lambda) {
    this->height = height;
    this->width = witdh;
    this->c =c;
    this->b = Bordure::BORD;
}

Grille::Grille(int witdh, int height, typeCellule c, double lambda, double* precalcul) : Graphe(witdh * height, c, lambda, precalcul) {
    this->height = height;
    this->width = witdh;
    this->c =c;
    this->b = Bordure::BORD;
}

Cellule* Grille::getCellule(int i, int j) {
    return Graphe::getCellule((j * this->width) + i);
}



void Grille::reset(){
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {    
                this->getCellule(i, j)->setEtat(Etat::NORMAL);
        }
    }
    
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

int Grille::getWidth() {
    return this->width;
}

int Grille::getHeight() {
    return this->height;
}

void Grille::setBordure(Bordure b) {
    this->b = b;
}

typeVoisinage Grille::getVosinage(){
    return this->t;
}


void Grille::setVoisinage(typeVoisinage t){
    this->t = t;
    if (t == typeVoisinage::MOORE8) this->Moore8();
    else if (t == typeVoisinage::MOORE9) this->Moore9();
    else if (t == typeVoisinage::TOOM) this->Toom();
    else if (t == typeVoisinage::VONNEUMAN) this->VonNeumann();
    else if (t == typeVoisinage::VONNEUMAN4) this->VonNeumann4();
    else if (t == typeVoisinage::IRREGULIER) this->setVoisinageNorme(1);
    else {
        this->t = static_cast<typeVoisinage>(NULL);
        cout << " erreur setup voisinage";
    }
    setVoisinCUDA();
}

void Grille::setVoisinage(typeVoisinage t,double paramVoisinage){
    this->t = t;
    if (t == typeVoisinage::IRREGULIER) this->setVoisinageNorme(paramVoisinage);
    else {
        this->t = static_cast<typeVoisinage>(NULL);
        cout << " erreur setup voisinage";
    }
}


void Grille::setVoisinageNorme(double r) {
    nbVoisinMax = r*r;
    int Sizetab =25;
    int tab[Sizetab] ={0};
    cout << "voisinage circulaire" << endl;
    this->t = typeVoisinage::IRREGULIER;

    pair<double,double> points[this->getWidth()][this->getHeight()];

    for (int i = 0; i < this->getWidth(); i++){
        for (int j = 0; j <this->getHeight(); j++){
            points[i][j] = make_pair((((double) rand() / (RAND_MAX))-0.5),((double)rand() / (RAND_MAX))-0.5);
        }
    }
    double nbVoisinMoy =0;
    for (int i = 0; i < this->getWidth(); i++){
       for (int j = 0; j <this->getHeight(); j++){

            for (int  a = floor(i-r); a <= ceil(i+r); a++){
                for (int b = floor(j-r); b <= ceil(j+r); b++){
                    //cout << "a :" << a << "b :" << b << endl;
                    if (this->b == Bordure::BORD){
                        if (a >= 0 && a < this->getWidth() && b >=0 && b < this->getHeight()) {
                            /*on vérifie qu'on est dans le carrée inscrit dans le cercle
                            on utilise 1.5 mais il faut simplement une valeur supérieur sqrt(2)*/
                            if (abs(i - a) < floor(r)/1.5-1 & abs(j - b) < floor(r)/1.5-1) {
                                this->getCellule(i, j)->addVoisin(this->getCellule(a, b));
                            } else {
                            double distX = (i + points[i][j].first) - (a + points[a][b].first);
                            double distY = (j + points[i][j].second) - (b + points[a][b].second);
                            //cout << "first "<< i+points[i][j].first  << " " << a+points[a][b].first;
                            //cout << "second "<< j+points[i][j].second  << " " << b+points[a][b].second;

                            //cout << distX << " " << distY << endl;
                            double distEcuclidienne = sqrt(pow(distX, 2) + pow(distY, 2));
                            //cout << distEcuclidienne << endl;
                                if (distEcuclidienne < r) {
                                this->getCellule(i, j)->addVoisin(this->getCellule(a, b));
                                    //cout << "addVoisin" << endl;
                                }
                            }

                        }
                    }
                    else if(this->b == Bordure::TORIQUE){
                        int amod = (a+this->getWidth()) % this->getWidth() ;
                        int bmod = (b+this->getHeight()) % this->getHeight();
                       
                         double distX = abs((i + points[i][j].first) - (amod + points[amod][bmod].first));
                        distX = min(distX,this->getWidth()-distX);

                        double distY = abs((j + points[i][j].second) - (bmod + points[amod][bmod].second));
                        distY = min(distY,this->getHeight()-distY);

                        double distEcuclidienne = sqrt(pow(distX, 2) + pow(distY, 2));
                        //cout << distEcuclidienne << endl;
                        if (distEcuclidienne < r) {
                            this->getCellule(i, j)->addVoisin(this->getCellule(amod, bmod));
                        }
                    }
                    else{
                        //assert("setVoisinageNorme:bordure non explicite");
                    }

                }
            }
            int nbVoisin = this->getCellule(i, j)->nbVoisin();
            tab[nbVoisin] = tab[nbVoisin]+1;
            nbVoisinMoy = nbVoisinMoy + nbVoisin;
        }
    }

    nbVoisinMoy = nbVoisinMoy/(this->getHeight()*this->getWidth());
    cout << "nombre de voisin en moyenne :" << nbVoisinMoy<< endl;

    for (int i = 0; i < Sizetab; i++){
        cout << "tab["<< i << "]: " << tab[i] << endl;
    }

}

void Grille::setVoisinageNorme(int x, int y ,double r){
    nbVoisinMax = r*r;
    this->getCellule(x, y)->resetVoisin();
    pair<double,double> points[(int)(2*ceil(r))][(int)(2*ceil(r))];
    for (int i = 0; i < 2*ceil(r); i++){
        for (int j = 0; j < 2*ceil(r); j++){
            points[i][j] = make_pair((((double) rand() / (RAND_MAX))-0.5),((double)rand() / (RAND_MAX))-0.5);
        }
    }


    for (int i = -ceil(r); i < ceil(r); i++){
        for (int j = -ceil(r); j < ceil(r); j++){
            int cX = ceil(r);
            int cY = ceil(r);

            if ( cX+i >= 0 && cX+i < this->getWidth() && cY+j >=0 && cY+j < this->getHeight()) {

                double distX = x + points[cX][cY].first - x+i + points[cX+i][cY+j].first;
                double distY = y + points[cX][cY].second - y+j+ points[cX+i][cY+j].second;
                double distEcuclidienne = sqrt(pow(distX, 2) + pow(distY, 2));
                if (distEcuclidienne < r) {
                    this->getCellule(x, y)->addVoisin(this->getCellule(x+i, y+j));
                }
            }
        }
    }

}

void Grille::Moore8() {
    nbVoisinMax = 8;
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            this->getCellule(i,j)->setNbVoisinMax(typeVoisinage::MOORE8);
            for (int a = -1; a < 2; a++) {
                for (int b = -1; b < 2; b++) {
                    if (a != 0 || b != 0) {
                        if(this->b == Bordure::TORIQUE) {
                            this->getCellule(i, j)->addVoisin(this->getCellule((this->width+(i + a))% this->width,
                                                                               (this->height+(j + b))% this->height));
                        }
                        else if(this->b == Bordure::BORD) {
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

void Grille::Moore9() {
    nbVoisinMax = 9;
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            this->getCellule(i,j)->setNbVoisinMax(typeVoisinage::MOORE9);
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
    nbVoisinMax = 5;
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            this->getCellule(i,j)->setNbVoisinMax(typeVoisinage::VONNEUMAN);
            this->getCellule(i, j)->addVoisin(this->getCellule(i, j));
            for (int a = -1; a < 2; a++) {
                for (int b = -1; b < 2; b++) {
                    if (a != b & a != -b) {
                        if(this->b == Bordure::TORIQUE){
                            this->getCellule(i, j)->addVoisin(this->getCellule((this->width+(i + a))% this->width,
                                                                               (this->height+(j + b))% this->height));
                        }
                        else if(this->b == Bordure::BORD) {
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

void Grille::VonNeumann4() {
    nbVoisinMax = 4;
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            this->getCellule(i,j)->setNbVoisinMax(typeVoisinage::VONNEUMAN4);
            for (int a = -1; a < 2; a++) {
                for (int b = -1; b < 2; b++) {
                    if (a != b & a != -b) {
                        if(this->b == Bordure::TORIQUE){
                            this->getCellule(i, j)->addVoisin(this->getCellule((this->width+(i + a))% this->width,
                                                                               (this->height+(j + b))% this->height));
                        }
                        else if(this->b == Bordure::BORD) {
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
    nbVoisinMax = 3;
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            if(this->b == Bordure::TORIQUE) {
                this->getCellule(i, j)->addVoisin(this->getCellule((i + 1)%this->width, j));
                this->getCellule(i, j)->addVoisin(this->getCellule(i, (j+1)% this->height));
            }
            else if(this->b == Bordure::BORD) {
                this->getCellule(i, j)->setNbVoisinMax(typeVoisinage::TOOM);
                this->getCellule(i, j)->addVoisin(this->getCellule(i, j));
                if (i + 1 < this->width) this->getCellule(i, j)->addVoisin(this->getCellule(i + 1, j));
                if (j - 1 >= 0) this->getCellule(i, j)->addVoisin(this->getCellule(i, j - 1));
            }
        }
    }
}
