//
// Created by kevin on 05/04/23.
//


#include "file.h"

file* file::pinstance_{nullptr};
std::mutex file::mutex_;

file *file::GetInstance() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new file();
    }
    return pinstance_;
}

void file::loadFile(char* nameFile) {
    this->filename = nameFile;
    fstream f(nameFile);  //Ouverture d'un fichier en lecture
    if(f)
    {
        string ligne; //Une variable pour stocker les lignes lues

        while(getline(f, ligne)) //Tant qu'on n'est pas à la fin, on lit
        {
            string parsed;
            stringstream s(ligne);

            string categorie = ligne.substr(0, ligne.find(':'));
            ligne.erase(0, ligne.find(':') + 1);

            if (categorie == "topologie"){
                if (ligne == "grille") topologie = Topologie::GRILLE;
                else if (ligne == "graphe") topologie = Topologie::GRAPHE;
                else cout << "erreur de topologie" << endl;
            }

            else if (categorie == "taille"){
                if (topologie == Topologie::GRAPHE){
                    if (ligne.find(',') != -1) cout << "erreur sur la taille de la grille" << endl;
                    else{
                        int t[1]= {stoi(ligne)};
                        size = t;
                    }
                }
                else if(topologie == Topologie::GRILLE){
                    if (ligne.find(',') == -1) cout << "erreur sur la taille de la graphe" << endl;
                    else{
                        string arg1 = ligne.substr(0, ligne.find(','));
                        ligne.erase(0, ligne.find(',') + 1);
                        if (ligne.find(',') != -1) cout << "erreur sur la taille de la graphe" << endl;
                        else{
                            size = (int*)(::malloc(sizeof(int) * 2));
                            size[0] = stoi(arg1);
                            size[1] = stoi(ligne);
                        }
                    }
                }
            }

            else if(categorie == "typeCellule"){
                if (ligne == "default") cellule = typeCellule::DEFAULT;
                else if(ligne == "QuoromD") cellule = typeCellule::QUOROMD;
                else cout << "erreur sur le type de cellule" << endl;
            }

            else if(categorie == "voisinnage"){
                if(topologie == Topologie::GRILLE) {
                    if (ligne == "moore8") voisinnage = VoisinageClassique::MOORE8;
                    else if (ligne == "moore9") voisinnage = VoisinageClassique::MOORE9;
                    else if (ligne == "toom") voisinnage = VoisinageClassique::TOOM;
                    else if (ligne == "vonNeumann") voisinnage = VoisinageClassique::VONNEUMAN;
                    else cout << "erreur de voisinnage" << endl;
                }
                else cout << "erreur de voisinnage sur un graphe" << endl;
            }

            else if(categorie == "visualisation"){
                if(ligne == "oui") visualisation = true;
                else if(ligne == "non") visualisation = false;
                else cout << "visualisation non spécifié" << endl;
            }

            else if(categorie == "seed"){
                if(ligne.empty()){
                    int pos = f.tellg();
                    f.seekg(pos-1,ios::beg);
                    int seedSelect = rand();
                    f << seedSelect << endl;
                    seed = seedSelect;
                }
                else seed = stoi(ligne);
            }

            else if(categorie == "seuil"){
                if (ligne.empty()) cout << "seuil non spécifie" << endl;
                else seuil = stod(ligne);
            }

            else if(categorie == "nbIteration"){
                int nbARG = 1;
                vector<double> v;
                while (ligne.find(',') != -1){
                    nbARG++;
                    string p = ligne.substr(0, ligne.find(','));
                    v.push_back(stod(p));
                    ligne.erase(0, ligne.find(',') + 1);
                }
                //dernier élement de la ligne
                string p = ligne;
                if (ligne.empty()) cout << "nombre d'itération non spécifie" << endl;
                else{
                    v.push_back(stoi(p));
                    nbIterationMax = (int*)(malloc(sizeof(int)*nbARG+1));
                    for (int i =0; i < v.size();i++){
                        nbIterationMax[i] = v.at(i);
                    }
                    nbIterationMax[nbARG] = NULL;
                }
            }

            else if(categorie == "focus"){
                if(ligne.empty()) focus = Focus::DEFAULT;
                else if (ligne == "temps") focus = Focus::TMPMAX;
                else if (ligne == "probaDef") focus = Focus::PROBADEF;
                else if (ligne == "lambda"){
                    if (cellule == typeCellule::QUOROMD) focus = Focus::LAMBDA;
                    else cout << "focus un lambda impossible sans cellule QuoromD";
                }
                else cout << "erreur sur le focus" << endl;
            }

            else if(categorie == "probaDef"){
                int nbARG = 1;
                vector<double> v;
                while (ligne.find(',') != -1){
                    nbARG++;
                    string p = ligne.substr(0, ligne.find(','));
                    v.push_back(stod(p));
                    ligne.erase(0, ligne.find(',') + 1);
                }
                //dernier élement de la ligne
                string p = ligne;
                if(ligne.empty()) cout << "erreur sur la probabilité de défaillance" << endl;
                else{
                    v.push_back(stod(p));
                    probaDef = (double*)(malloc(sizeof(double)*nbARG+1));
                    for (int i =0; i < v.size();i++){
                        probaDef[i] = v.at(i);
                    }
                    probaDef[nbARG] = NULL;
                }
            }

            else if( categorie == "lambda"){
                if (cellule == typeCellule::QUOROMD){
                        int nbARG = 1;
                        vector<double> v;
                        while (ligne.find(',') != -1){
                            nbARG++;
                            string p = ligne.substr(0, ligne.find(','));
                            v.push_back(stod(p));
                            ligne.erase(0, ligne.find(',') + 1);
                        }
                        //dernier élement de la ligne
                        string p = ligne;
                        if(ligne.empty()) cout << "erreur sur lambda" << endl;
                        else{
                            v.push_back(stod(p));
                            lambda = (double*)(malloc(sizeof(double)*nbARG+1));
                            for (int i =0; i < v.size();i++){
                                lambda[i] = v.at(i);
                            }
                            lambda[nbARG] = NULL;
                        }
                }
            }

            else if(categorie == "nbTest"){
                nbTest = stod(ligne);
            }

            else if(categorie == "evolution"){
                if(ligne.empty()) cout  << "evolution étudier non spécifié" << endl;
                else if(ligne == "densite") evolution = Evolution::DENSITY;
                else if(ligne == "probabilite") evolution = Evolution::PROBABILITE;
                else cout << "evolution mal spécifié"<< endl;
            }
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
}

Topologie file::getTopologie() const{
    return topologie;
}

int *file::getSize() const {
    return size;
}

typeCellule file::getCellue() const {
    return cellule;
}

VoisinageClassique file::getVoisinnage() const {
    return voisinnage;
}

double *file::getLambda() const {
    return lambda;
}

int* file::getNbIterationMax() const {
    return nbIterationMax;
}

double file::getSeuil() const {
    return seuil;
}

double *file::getProbaDef() const {
    return probaDef;
}

Focus file::getFocus() const {
    return focus;
}

bool file::isVisualisation() const {
    return visualisation;
}

int file::getSeed() const {
    return seed;
}

Evolution file::getEvolution() const {
    return evolution;
}

int file::getNbTest() const {
    return nbTest;
}

void file::write(string s) {
    fstream f(filename);  //Ouverture d'un fichier en lecture
    f.seekp(0, ios::end);
    f << s << endl;
}
