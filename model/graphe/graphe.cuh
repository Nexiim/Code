//
// Created by kevin on 14/03/23.
//

#ifndef CODE_GRAPHE_H
#define CODE_GRAPHE_H

#include "../cellule/celluleQuoromD.h"
//#include "../cellule/codeCorrecteur/correcteur.h"
#include "../gpu/MAJQuoromD.cuh"
//#include <math.h>
//#include <omp.h>
#include <tuple>
#include <vector>
//#include <algorithm>
//#include <float.h>

/*
Classe Graphe qui représente le graphe sur lequel on effectue les simulations.
*/
class Graphe {
public:
    /*
    Constructeurs de la classe Graphe
    */

    Graphe(int size, typeCellule c);
    Graphe(int size, typeCellule c, double lambda);
    Graphe(int size, typeCellule c, double lambda, double* precalcul);

    /*
    Fonction pour initialiser les cellules et leur état à chaque simulation
    */
    virtual void reset(double proba, double lambda, double *precalcul);
    //virtual void reset();

    /*
    Fonction pour ajouter des voisins proches à chaque cellule
    */
    void setupCUDA();
    void setVoisinCUDA();

    void setVoisinsProche(int nbVoisins);
    void resetVoisinPlusProche();
    /*
    Fonction pour effectuer la contamination des cellules
    */
    //virtual void contamination();

    /*
    Fonction pour mettre à jour les états des cellules
    */
    virtual void MAJ();

    /*
    Fonctions getter et setter pour les cellules, les états et les seuils
    */
    Cellule* getCellule(int i);
    int getCellule(Cellule *c);

    int getCellulePosX(int i);
    int getCellulePosY(int i);

    void setCelluleDef(double proba);
    bool seuil(double s);

    /*
    Fonction qui retourne le nombre de cellules dans un état d'alerte donnée
    */

    int nbAlerte();
    int nbDef();
    int nbCellule();

    /*
    Fonction de précalcul et setter de lambda seulement utile pour QuorumD
    */

    void setLambda(double lambda);
    /*void setPreCalcul(double* precalcul);

    virtual int getWidth();
    virtual int getHeight();

    pair<int,int> getPosCellule(int i);

    int getPosCelluleX(Cellule *c);
    int getPosCelluleY(Cellule *c);*/

    typeVoisinage getVoisinage();

private:
    /*
    Variables membres de la classe Graphe
    */

    Cellule* *cels;

    int *d_cels, *d_celsSync, *d_posVoisins, *d_voisins, *d_nbAlerte;
    int *alerte;

    int def;

    vector<pair<int, int>> posCellule; 

    void copyCels();
    void calculPPV(int nbVoisins);

protected:
    /*
    Variables partagé de la classe Graphe et de ses sous classes
    */
    int nbVoisinMax;
    typeCellule c;
    typeVoisinage t;

    double threshold;
    int size;
    int width, height;

    /*
    Variables pour l'utilisation GPU
    */

};

#endif //CODE_GRAPHE_H
