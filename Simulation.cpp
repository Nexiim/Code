//
// Created by kevin on 04/04/23.
//
#include "model/graphe/grille.cuh"
#include "simulation/simulationQuoromD.h"
#include "model/util/file.h"

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

            if(f->getVoisinnage() == typeVoisinage::IRREGULIER)
                G.setVoisinage(f->getVoisinnage(),f->getVoisinageParam());
            else
                G.setVoisinage(f->getVoisinnage());

            SimulationQuoromD s(f->getNbTest(), f->getSeuil(),f->getNbIterationMax(), f->getParametre(), f->getProbaDef(), &G);

            if( f->getEvolution() == Evolution::DENSITY) s.startDensitySim();
            else if (f->getEvolution() == Evolution::PROBABILITE) s.start();
        }

        else if(f->getTopologie() == Topologie::GRAPHE){
            Graphe G(f->getSize()[0], f->getCellue());

            if(f->getVoisinnage() == typeVoisinage::PLUSPROCHE)
                G.setVoisinsProche(f->getVoisinageParam());
            else 
                cout << "erreur set voisinage" << endl;
            
            SimulationQuoromD s(f->getNbTest(), f->getSeuil(),f->getNbIterationMax(), f->getParametre(), f->getProbaDef(), &G);

            if( f->getEvolution() == Evolution::DENSITY) s.startDensitySim();
            else if (f->getEvolution() == Evolution::PROBABILITE) s.start();
        }

        else{
            cout << "erreur création da la simulation" << endl;
        }
    }

}
