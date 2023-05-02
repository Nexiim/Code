//
// Created by kevin on 14/03/23.
//

#ifndef CODE_GRAPHE_H
#define CODE_GRAPHE_H

#include "../cellule/celluleQuoromD.h"
#include "../cellule/codeCorrecteur/correcteur.h"
#include <math.h>

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

    /*
    Fonction pour ajouter des voisins proches à chaque cellule
    */
    void setVoisinsProche(int nbVoisins);

    /*
    Fonction pour effectuer la contamination des cellules
    */
    void contamination();

    /*
    Fonction pour mettre à jour les états des cellules
    */
    virtual void MAJ();

    /*
    Fonctions getter et setter pour les cellules, les états et les seuils
    */
    Cellule *getCellule(int i);
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
    void setPreCalcul(double* precalcul);

    virtual int getWidth();
    virtual int getHeight();

    pair<int,int> getPosCellule(Cellule* c);
    pair<int,int> getPosCellule(int i);
    typeVoisinage getVoisinage();

private:
    /*
    Variables membres de la classe Graphe
    */

    vector<Cellule *> listeCellules;
    vector<pair<int, int>> posCellule; 

protected:
    /*
    Variables partagé de la classe Graphe et de ses sous classes
    */
   
    typeCellule c;
    typeVoisinage t;
    double threshold;
    int width, height;
};

#endif //CODE_GRAPHE_H
