//
// Created by kevin on 04/04/23.
//
#include <thread>
#include "model/graphe/grille.h"
#include "visualisation/visualisationGrille.h"
#include "simulation/simulationQuoromD.h"
#include "model/util/file.h"

#define H 500
#define W 500
#define FAILURERATE 0.04
#define THRESHOLD 0.95

void startSimulation(Graphe *G){
    file *f = file::GetInstance();
    SimulationQuoromD s(f->getNbTest(), f->getSeuil(),f->getNbIterationMax(), f->getParametre(), f->getProbaDef(), G);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    if( f->getEvolution() == Evolution::DENSITY) s.startDensitySim();
    else if (f->getEvolution() == Evolution::PROBABILITE) s.start();
}

void startVisualisation(Grille *G){
    visualisationGrille v(G->getHeight(),G->getWidth(),G);
    v.initVisualisation();
    v.loopEvent();
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    if(argc == 2) {
        cout << "lecture du fichier" << endl;
        file *f = file::GetInstance();
        f->loadFile(argv[1]);

        srand(f->getSeed());

        if (f->getTopologie() == Topologie::GRILLE) {
            Grille G(f->getSize()[0], f->getSize()[1], f->getCellue());
            G.setBordure(f->getBordure());
            G.setVoisinage(f->getVoisinnage());

            for (int i = 0; i < G.getCellule(20,20)->nbVoisin();i++){
                cout << G.getCellule(20,20)->getVoisin(i) << " ";
            }

            std::thread simulationThread(startSimulation, &G);
            if ( f->isVisualisation()) {
                std::thread visualisationThread(startVisualisation, &G);
                visualisationThread.join();
            }
            simulationThread.join();
        }
        else if(f->getTopologie() == Topologie::GRAPHE){

        }
        else{
            cout << "erreur création da la simulation" << endl;
        }
    }

}
