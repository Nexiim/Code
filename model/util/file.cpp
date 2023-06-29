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
    this->f = fstream(filename); 
    if(this->f)
    {
        string ligne; //Une variable pour stocker les lignes lues

        while(getline(this->f, ligne)) //Tant qu'on n'est pas à la fin, on lit
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

            else if (categorie == "bordure"){
                if (ligne == "bord") bordure = Bordure::BORD;
                else if (ligne == "torique") bordure = Bordure::TORIQUE;
                else cout << "erreur de bordure" << endl;
            }


            else if (categorie == "taille"){
                if (topologie == Topologie::GRAPHE){
                    if (ligne.find(',') != -1) cout << "erreur sur la taille de la grille" << endl;
                    else{
                        size = (int*)(::malloc(sizeof(int) * 1));
                        size[0] = stoi(ligne);
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
                else if(ligne == "QuorumD") cellule = typeCellule::QUOROMD;
                else cout << "erreur sur le type de cellule" << endl;
            }

            else if(categorie == "voisinnage"){
                if(topologie == Topologie::GRILLE) {
                    if (ligne == "moore8") voisinnage = typeVoisinage::MOORE8;
                    else if (ligne == "moore9") voisinnage = typeVoisinage::MOORE9;
                    else if (ligne == "toom") voisinnage = typeVoisinage::TOOM;
                    else if (ligne == "vonNeumann") voisinnage = typeVoisinage::VONNEUMAN;
                    else if (ligne == "vonNeumann4") voisinnage = typeVoisinage::VONNEUMAN4;
                    else{

                        if (ligne.find(',') == -1) cout << "erreur de voisinnage grille" << endl;
                        else{
                            string arg1 = ligne.substr(0, ligne.find(','));
                            ligne.erase(0, ligne.find(',') + 1);
                            if (arg1 == "irregulier"){
                                voisinnage = typeVoisinage::IRREGULIER;
                                paramVoisinage = stod(ligne);
                            }
                            else cout << "erreur de voisinnage grille" << endl;
                        }                                  
                    }
                }

                else if(topologie == Topologie::GRAPHE){
                    
                    if (ligne.find(',') == -1) cout << "argument neccésaire pour le voisinage" << endl;
                    else{
                        string arg1 = ligne.substr(0, ligne.find(','));
                        ligne.erase(0, ligne.find(',') + 1);

                        if (arg1 == "plusProcheVoisin"){
                            if (ligne.find(',') != -1) cout << "trop d'arguments pour le vosinage" << endl;
                            else{
                                argVoisinage = (double*)(::malloc(sizeof(double) * 1));
                                paramVoisinage = stod(ligne);
                                voisinnage = typeVoisinage::PLUSPROCHE;
                            }
                        }
                        else cout << "erreur de voisinnage graphe" << endl;
                    }        
                }
                else cout << "erreur de voisinnage topologie inconnue" << endl;
            }

            else if(categorie == "visualisation"){
                if(ligne == "oui") visualisation = true;
                else if(ligne == "non") visualisation = false;
                else cout << "visualisation non spécifié" << endl;
            }

            else if(categorie == "seed"){
                if(ligne.empty()){
                    int pos = f.tellg();
                    this->f.seekg(pos-1,ios::beg);
                    int seedSelect = rand();
                    this->f << seedSelect << endl;
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

            else if( categorie == "parametre"){
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
                            parametre = (double*)(malloc(sizeof(double)*nbARG+1));
                            for (int i =0; i < v.size();i++){
                                parametre[i] = v.at(i);
                            }
                            parametre[nbARG] = NULL;
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

typeVoisinage file::getVoisinnage() const {
    return voisinnage;
}

double *file::getParametre() const {
    return parametre;
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
    this->f = fstream(filename); 
    this->f.seekp(0, ios::end);
    this->f << s << endl;
}

Bordure file::getBordure() const {
    return bordure;
}

double file::getVoisinageParam() const{
    return paramVoisinage;
}
