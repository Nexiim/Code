//
// Created by kevin on 14/03/23.
//

#include "graphe.cuh"

/*
Constructor
*/

Graphe::Graphe(int size, typeCellule c) {
    this->c = c;
    this->width = size*5;
    this->height = size*5;

    this->size = size;
    def = 0;

    cels = (Cellule**)malloc(size*sizeof(Cellule*));
    setupCUDA();

    for (int i = 0; i < size; i++) {
        if (c == typeCellule::DEFAULT) cels[i] = new Cellule();
        if (c == typeCellule::QUOROMD) cels[i] = new CelluleQuoromD();
        //if (c == typeCellule::CORRECTEUR) this->listeCellules.push_back(new Correcteur());    

        posCellule.push_back(make_pair(rand()%this->width,rand()%this->height));    
    }
    this->threshold = 0;
}

Graphe::Graphe(int size, typeCellule c, double lambda) {
    this->c = c;
    for (int i = 0; i < size; i++) {
        if (c == typeCellule::QUOROMD) cels[i] = new CelluleQuoromD(lambda);
    }
    this->threshold = 0;
}

Graphe::Graphe(int size, typeCellule c, double lambda, double* precalcul) {
    this->c = c;
    for (int i = 0; i < size; i++) {
        if (c == typeCellule::QUOROMD) cels[i] = new CelluleQuoromD(lambda, precalcul);
    }
    this->threshold = 0;
}



/*
fonction
*/

/*void Graphe::reset(){

}*/

void Graphe::reset(double proba, double lambda, double *precalcul) {
    posCellule.clear();

    for (int i = 0; i < nbCellule(); i++) {
        posCellule.emplace_back(rand()%this->width,rand()%this->height);
    }
    def = 0;
    for (int i = 0; i < nbCellule(); i++) {
            auto* cell = dynamic_cast<CelluleQuoromD*>(getCellule(i));
            cell->setLambda(lambda);
            cell->setPreCalcul(precalcul);
            double r = rand() / double(RAND_MAX);
            if (r < proba) {
                getCellule(i)->setEtat(DEFAILANTE);
                def++;
            }
            else getCellule(i)->setEtat(NORMAL);
    }
    threshold = 0;

    if (getVoisinage() == typeVoisinage::PLUSPROCHE)
        resetVoisinPlusProche();
}


void Graphe::setupCUDA(){
    cudaMalloc(&d_cels, size*sizeof(int));
    cudaMalloc(&d_celsSync, size*sizeof(int));
    cudaMalloc(&d_nbAlerte, sizeof(int));

    alerte = (int*)malloc(sizeof(int));
    *alerte = 0;
}

void Graphe::setVoisinCUDA(){
    int *pos = (int*)malloc(nbCellule()*2*sizeof(int));
    int *voisins = (int*)malloc(nbVoisinMax*nbCellule()*sizeof(int));
    int s = 0;

    for(int i = 0; i < nbCellule(); i++){
        int nbVoisin = getCellule(i)->nbVoisin();
        pos[i*2] = s;
        pos[i*2+1] = s + nbVoisin -1;

        for(int j = 0; j < nbVoisin; j++){
            voisins[s+j] = getCellule(getCellule(i)->getVoisin(j));
        }

        s = s + nbVoisin;
    }

    cudaMalloc(&d_posVoisins, nbCellule()*2*sizeof(int));
    cudaMalloc(&d_voisins,nbVoisinMax*nbCellule()*sizeof(int));

    cudaMemcpy(d_posVoisins, pos, nbCellule()*2*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_voisins, voisins, nbVoisinMax*nbCellule()*sizeof(int), cudaMemcpyHostToDevice);

    free(pos);
    free(voisins);
}

void Graphe::setVoisinsProche(int nbVoisins){
    t = typeVoisinage::PLUSPROCHE;
    nbVoisinMax = nbVoisins*2;
    calculPPV(nbVoisins);
    setVoisinCUDA();
}

void Graphe::resetVoisinPlusProche(){

    cout << "reset voisinage plus proche" << endl;
    for (int i = 0; i < this->nbCellule(); i++) {
        this->getCellule(i)->resetVoisin();
    }

    this->setVoisinsProche(nbVoisinMax);
}

void Graphe::calculPPV(int nbVoisins){

    int* plusProche = (int*)malloc(sizeof(int)*nbVoisins);
    auto* dist = (double*)(malloc(sizeof(double) * nbVoisins));

    for (int i = 0; i < nbCellule();i++){;
        getCellule(i)->setNbVoisinMax(typeVoisinage::PLUSPROCHE);
        for (int j = 0; j < nbVoisins; j++){
            dist[j] = numeric_limits<int>::max();;
        }

       for (int j = 0; j < nbCellule();j++){ 
            if (i != j){
                double distIJ = sqrt(pow((getCellulePosX(i) - getCellulePosX(j)),2) +
                                   pow((getCellulePosY(i) - getCellulePosY(j)),2));
                int max = numeric_limits<int>::min();
                int indiceMax = -1;

                for (int k =0; k < nbVoisins; k++){
                    if (dist[k] > max){
                        max = dist[k];
                        indiceMax = k;
                    }
                }
                if( max > distIJ){
                    plusProche[indiceMax] = j;
                    dist[indiceMax] = distIJ;
                }
            }
       }
       for (int j = 0; j < nbVoisins; j++){
            getCellule(i)->addVoisin(getCellule(plusProche[j]));
            //getCellule(plusProche[j])->addVoisin(getCellule(i));
       }
    }

    free(plusProche);
    free(dist);
}

/*
fonction des différentes mise à jours du graphe
*/

/*void Graphe::contamination() {
    for (int i = 0; i < this->nbCellule();i++)
            this->getCellule(i)->contamination();

    for (int i = 0; i < this->nbCellule();i++)
        this->getCellule(i)->nextT();
}
*/
void Graphe::MAJ() {
    if(c == typeCellule::QUOROMD){
        auto* cell = dynamic_cast<CelluleQuoromD*>(getCellule(0));
        double lambda = cell->getLambda();
        *alerte = 0;

        cudaMemcpy(d_nbAlerte, alerte, sizeof(int), cudaMemcpyHostToDevice);

        QuorumD<<<1,size>>>(rand(),d_cels, d_celsSync, d_posVoisins, d_voisins,d_nbAlerte,lambda);
        cudaDeviceSynchronize();

        cudaMemcpy(alerte, d_nbAlerte, sizeof(int), cudaMemcpyDeviceToHost);

        cout << "nb Alerte : " << *alerte << endl;

        int *C = (int*)malloc(size*sizeof(int));
        cudaMemcpy(C, d_celsSync, size*sizeof(int), cudaMemcpyDeviceToHost);

        for(int i = 0; i < nbCellule(); i++){
            if(C[i] == DEFAILANTE) getCellule(i)->setEtat(DEFAILANTE);
            else if(C[i] == ALERTE) getCellule(i)->setEtat(ALERTE);
            else getCellule(i)->setEtat(NORMAL);
        }

        cudaMemcpy(d_cels, C, size*sizeof(int), cudaMemcpyHostToDevice);

        threshold = (double)*alerte / ((double)(size - nbDef()));
    }
    else{
        #pragma omp parallel for
        for (int i = 0; i < this->nbCellule(); i++) {
            auto* cell = dynamic_cast<CelluleQuoromD*>(getCellule(i));
            cell->transition();
        }

        double nbDef = 0;
        double nbAlerte = 0;

        #pragma omp parallel for shared(nbDef,nbAlerte)
        for (int i = 0; i < this->nbCellule(); i++) {
                this->getCellule(i)->nextT();
                if (this->getCellule(i)->getEtat() == ALERTE) nbAlerte++;
                else if (this->getCellule(i)->getEtat() == DEFAILANTE) nbDef++;
        }

        threshold = nbAlerte / ((double)(size - nbDef));
    }
}

/* 
getter setter
*/

//Cellule *Graphe::getCellule(int i) { return get<0>(this->posCellule.at(i)); }
Cellule* Graphe::getCellule(int i) { return cels[i]; }

int Graphe::getCellule(Cellule *c){
    for (int i = 0; i< nbCellule(); i++){
        if(cels[i] == c) return i;
    }
    return -1;
}

int Graphe::getCellulePosX(int i) { return get<0>(posCellule.at(i)); }
int Graphe::getCellulePosY(int i) { return get<1>(posCellule.at(i)); }

void Graphe::copyCels(){
    int* copy = (int*)malloc(nbCellule()*sizeof(int));
    for (int i = 0; i < nbCellule(); i++) copy[i] = getCellule(i)->getEtat();
    cudaMemcpy(d_cels, copy, nbCellule()*sizeof(int), cudaMemcpyHostToDevice);
    free(copy);
}

void Graphe::setCelluleDef(double proba) {
    this->threshold = 0;
    for (int i = 0; i < this->nbCellule(); i++) {
        double r = rand() / double(RAND_MAX);
        if (r < proba) {
            this->getCellule(i)->setEtat(DEFAILANTE);
            def++;
        } else
            this->getCellule(i)->setEtat(NORMAL);
    }
    copyCels();
}


bool Graphe::seuil(double s) {
    if (threshold >= s)return true;
    else return false;
}

int Graphe::nbAlerte() {
    int s= 0;
    for (int i = 0; i < this->nbCellule(); i++)
        if (getCellule(i)->getEtat() == ALERTE) s++;
    return s;
}

int Graphe::nbDef() {
    return def;
}


int Graphe::nbCellule() {
    return this->size;
}

void Graphe::setLambda(double lambda) {
    if (this->c == typeCellule::QUOROMD){
        for (int i = 0; i < this->nbCellule(); i++){
            auto* cell = dynamic_cast<CelluleQuoromD*>(getCellule(i));
            cell->setLambda(lambda);
        }
    }
}
/*
void Graphe::setPreCalcul(double *preCalcul) {
    if (this->c == typeCellule::QUOROMD){
        for (int i = 0; i < this->nbCellule(); i++){
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
    return pair<int,int>(-1,-1);
}


int Graphe::getPosCelluleX(Cellule *c) {
    for (int i = 0; i < this->nbCellule(); i++){
       if (this->getCellule(i) == c){
            return getCellulePosX(i);
       }
    }
    return -1;
}

int Graphe::getPosCelluleY(Cellule *c) {
    for (int i = 0; i < this->nbCellule(); i++){
       if (this->getCellule(i) == c){
            return getCellulePosY(i);
       }
    }
    return -1;
}
*/

typeVoisinage Graphe::getVoisinage() {
    return this->t;
}