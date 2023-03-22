#include <iostream>
#include "simulation/simulation.h"
#include "simulation/simulationQuoromD.h"
#include "visualisation/visualisation.h"

#include <unistd.h>

using namespace std;

#define H 50
#define W 50
#define FAILURERATE 0.06
#define THRESHOLD 0.95

int main() {

    srand(time(NULL));
    int T[4] = {sizeof(T) / sizeof(*T)-1,3000,5000,10000};
    //probabilité de défaillance
    double P[16];
    P[0] = sizeof(P) / sizeof(*P)-1;
    for (int i = 1 ; i <= P[0]; i++){
        P[i] = (i-1)*0.01;
    }
    int LAMBDA[2] = {sizeof(LAMBDA) / sizeof(*LAMBDA)-1,5};

    clock_t debut, fin;
    debut = clock();
    SimulationQuoromD s(T,100,P,Voisinage::MOORE8,THRESHOLD,H,W,LAMBDA);
    s.start(TMPMAX);
    fin = clock();
    cout << "Temps ecoule en secondes : " <<(fin - debut)/CLOCKS_PER_SEC<< endl ;




    /* Grille G(W, H,typeCellue::QUOROMD);
     G.setLamba(LAMBDA[1]);
     G.setVoisinage(Voisinage::MOORE8);
     G.setCelluleDef(FAILURERATE);
     G.affichageGrille();
     G.MAJGrille();
     G.MAJGrille();
     G.affichageGrille();

     /*int x,y;
     for(int i = 0; i < W; i++){
         for(int j= 0; j < H; j++){
             if (G.getCellule(i,j)->getEtat() == DEFAILANTE){
                 x = i;
                 y = j;
             }
         }
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

    /*Visualisation v(H,W,&G);
    v.initVisualisation();
    v.loopEvent();*/

    return 0;
}