#include <iostream>
#include "simulation/simulation.h"
#include "simulation/simulationQuoromD.h"
#include "visualisation/visualisation.h"
#include "model/Voisinage/Voisinage.h"

#include <unistd.h>

using namespace std;

#define H 500
#define W 500
#define FAILURERATE 0.06
#define THRESHOLD 0.95

int main() {

    srand(time(NULL));
    int T[4] = {sizeof(T) / sizeof(*T)-1,1000,2000,5000};
    //probabilité de défaillance
    double P[16];
    P[0] = sizeof(P) / sizeof(*P)-1;
    for (int i = 1 ; i <= P[0]; i++){
        P[i] = (i-1)*0.01;
    }
    double LAMBDA[2] = {sizeof(LAMBDA) / sizeof(*LAMBDA)-1,2};

    Grille G(W, H,typeCellue::QUOROMD);
    Voisinage v = Voisinage(&G);
    v.setVoisinageNorme(20);

    int x = 250;
    int y = 250;

    for (int a = 0; a < G.getCellule(x,y)->nbVoisin(); a++){
        if (G.getCellule(x,y)->getVoisin(a)->getEtat() == Etat::NORMAL)
            G.getCellule(x,y)->getVoisin(a)->setEtat(Etat::ALERTE);
        else
            G.getCellule(x,y)->getVoisin(a)->setEtat(Etat::DEFAILANTE);
    }
    Visualisation visu(H,W,&G);
    visu.initVisualisation();
    visu.loopEvent();



    /*clock_t debut, fin;
    debut = clock();
    SimulationQuoromD s(T, 100, P, VoisinageClassique::MOORE8, THRESHOLD, H, W, LAMBDA);
    s.start(Focus::TMPMAX);
    fin = clock();
    cout << "Temps ecoule en secondes : " <<(fin - debut)/CLOCKS_PER_SEC<< endl ;*/





   /* Grille G(W, H,typeCellue::QUOROMD);
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