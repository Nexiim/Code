#include"model/graphe/graphe.cuh"
#include"model/graphe/grille.cuh"

using namespace std;

#define H 10
#define W 10

#define FAILURERATE 0.05
#define THRESHOLD 0.95

#define WINRATE 0.95
#define ITERMAX 1

/*void startSimulation(Grille *G){
    int nbTest =1;

    int nbSuccess = 0;
    int nbIter = 0;

    int lambda = 8;
    double norme =2.0;

    //nombre de dichotomie effectué
    int prec = 1;

    G->setVoisinageNorme(norme);

    for (int n = 0; n < prec; n++){
        G->setLambda(lambda);
    
        for (int i = 0; i < nbTest; i++){
            while(nbIter < ITERMAX){
                nbIter++;
                if(G->seuil(THRESHOLD)){
                   nbSuccess++;
                break;
                }
                G->MAJ();
            }         
        }
    }
}

void startVisualisation(Grille *G){
    visualisationGrille v(G->getHeight(),G->getWidth(),G);
    v.initVisualisation();
    v.loopEvent();
}*/


int main() {
    //srand(0);

    //Graphe* G;

    Grille* G;
    
    G = new Grille(H,W,typeCellule::QUOROMD);
    
    G->setCelluleDef(FAILURERATE);
    G->setBordure(Bordure::TORIQUE);
    G->setLambda(10.);

    G->setVoisinage(typeVoisinage::VONNEUMAN4);

    for (int i = 0; i < 10; i++){
        G->MAJ();
        G->affichageGrille();
    }   

    /*std::thread simulationThread(startSimulation, G);
   // std::thread visualisationThread(startVisualisation, G);

    //visualisationThread.join();
    simulationThread.join();*/
}