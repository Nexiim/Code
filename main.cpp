#include <iostream>
#include "simulation/simulation.h"
#include "simulation/simulationQuoromD.h"
#include "visualisation/visualisation.h"
#include "model/Voisinage/Voisinage.h"
#include "model/cellule/codeCorrecteur/correcteur.h"
#include "visualisation/codeCorrecteur/VisuCodeCorrecteur.h"

#include <unistd.h>

using namespace std;

#define H 30
#define W 30
#define FAILURERATE 0.04
#define THRESHOLD 0.95

int main() {

    Grille G(H,W,typeCellule::CORRECTEUR);
    G.setVoisinage(VoisinageClassique::TOOM);

    VisuCodeCorrecteur v(H,W,&G);
    v.initVisualisation();

    int c1 =0;
    int c2 = 0;
    for (int i = 0; i < G.getWidth(); i++){
        c1 = c2;
        for (int j =0; j < G.getHeight(); j++) {
            Correcteur* c = dynamic_cast<Correcteur *>(G.getCellule(i,j));
            c1 = (c1 +1)%3;
            c->setValue(c1);
        }
        c2 = (c2+1)%3;
    }

    v.loopEvent();


    /*srand(time(NULL));
    int T[2] = {sizeof(T) / sizeof(*T)-1,  50000};
    //probabilité de défaillance
    double P[2];
    P[0] = sizeof(P) / sizeof(*P)-1;
    P[1] = FAILURERATE;
    /*for (int i = 1 ; i <= P[0]; i++){
        P[i] = 0.05+(i-2)*0.01;
    }*/
    /*double LAMBDA[2] = {sizeof(LAMBDA) / sizeof(*LAMBDA)-1,2.275};

    Grille G(3, 3,typeCellule::QUOROMD);
    G.setLamba(5.0);
    G.setVoisinage(VoisinageClassique::VONNEUMAN);
    G.getCellule(1,1)->setEtat(DEFAILANTE);

    int a = 0;
    for (int i = 0; i <10000; i++){
        G.MAJGrille();
        if (G.getCellule(1,0)->getEtat() == ALERTE) a++;
        G.getCellule(1,0)->setEtat(NORMAL);
        G.getCellule(0,1)->setEtat(NORMAL);
        G.getCellule(2,1)->setEtat(NORMAL);
        G.getCellule(1,2)->setEtat(NORMAL);
    }
    cout << a/10000. << endl;*/

    /*G.setLamba(LAMBDA[1]);
    G.setVoisinage(VoisinageClassique::VONNEUMAN);
    G.setCelluleDef(FAILURERATE);

    Visualisation v(H,W,&G);
    v.initVisualisation();
    v.loopEvent();*/

    /*clock_t debut, fin;
    debut = clock();
    SimulationQuoromD s(T, 1, P, VoisinageClassique::VONNEUMAN, THRESHOLD, H, W, LAMBDA);
    s.startDensitySim(Focus::PROBADEF);

    fin = clock();
    cout << "Temps ecoule en secondes : " <<(fin - debut)/CLOCKS_PER_SEC<< endl ;*/

    /*test par contamination à partir d'un voisinage "circulaire"*/

    /*Grille G(W, H, typeCellule::QUOROMD);
    Voisinage v = Voisinage(&G);

    int x = W/2;
    int y = H/2;

    /*for (int i = 0; i <W;i++){
        for (int j = 0; j <W;j++){
            v.setVoisinageNorme(i,j,2);
        }
    }*/
    /*v.setVoisinageNorme(2.);

    G.getCellule(x,y)->setEtat(Etat::ALERTE);

    for (int a = 0; a < G.getCellule(x,y)->nbVoisin(); a++){
        if (G.getCellule(x,y)->getVoisin(a)->getEtat() == Etat::NORMAL)
            G.getCellule(x,y)->getVoisin(a)->setEtat(Etat::ALERTE);
        else
            G.getCellule(x,y)->getVoisin(a)->setEtat(Etat::DEFAILANTE);
    }

    Visualisation visu(H,W,&G);
    visu.initVisualisation();
    visu.loopEvent();*/


   /* Grille G(W, H,typeCellule::QUOROMD);
     G.setLamba(LAMBDA[1]);
     G.setVoisinage(VoisinageClassique::MOORE8);
     G.setCelluleDef(FAILURERATE);
     //G.setPreCalcul(listExp);

     Visualisation v(H,W,&G);
     v.initVisualisation();
     v.loopEvent();*/

     /*G.affichageGrille();
     int x = 5;
     int y = 0;
    /*for (int a = 0; a < G.getCellule(x,y)->nbVoisin(); a++){
        G.getCellule(x,y)->getVoisin(a)->setEtat(Etat::DEFAILANTE);
    }*/
    /*for (int j = 0; j <10 ;j++) {
        for (int i = 0; i < 10; i++) {
            G.MAJGrille();
        }
        G.affichageGrille();
    }*/

     /*int x,y;
     for(int i = 0; i < W; i++){
         for(int j= 0; j < H; j++){
             if (G.getCellule(i,j)->getEtat() == DEFAILANTE){
                 x = i;
                 y = j;
             }
         }
     }
     cout <<"i : "<<x <<"j :"<< y << endl;
     for (int a = 0; a < G.getCellule(x,y)->nbVoisin(); a++){
         cout << G.getCellule(x,y)->getVoisin(a)->getEtat() << endl ;
     }
    G.MAJGrille();
    G.affichageGrille();

    for (int a = 0; a < G.getCellule(x,y)->nbVoisin(); a++){
        cout << G.getCellule(x,y)->getVoisin(a)->getEtat() << endl ;
    }*/


    //cout << "i: "<< x << "j: "<< y ;

    /*for (int i =0; i < G.getCellule(x,y)->nbVoisin();i++){
        cout << " v" << i << ": " << G.getCellule(x,y)->getVoisin(i)->getEtat();
    }
    cout << endl;*/

    /*G.reset(FAILURERATE,LAMBDA[1],nullptr);
    G.affichageGrille();*/


    /* for (int i =0; i < G.getCellule(x,y)->nbVoisin();i++){
         cout << " v" << i << ": " << G.getCellule(x,y)->getVoisin(i)->getEtat();
     }
     cout << endl;*/



    return 0;
}