//
// Created by kevin on 26/04/23.
//

#include "visualisationGraphe.h"

visualisationGraphe::visualisationGraphe(Graphe *G) :visualisation(G->getWidth(),G->getHeight()){
    this->G = G;
    this->listeLigne;
}


void visualisationGraphe::affichage() {
    SDL_SetRenderDrawColor(renderer, 0, 0,0, 0);
    SDL_RenderClear(renderer);

    drawVoisinage();

    for (int i = 0; i < G->nbCellule(); i++) {
        if (G->getCellule(i)->getEtat() == NORMAL) SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
        else if (G->getCellule(i)->getEtat() == ALERTE) SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
        else SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);

        for (int a = 0; a < pixelSize; a++) {
            for (int b = 0; b < pixelSize; b++) {
                SDL_RenderDrawPoint(renderer, G->getCellulePosX(i)* pixelSize + a,
                                    G->getCellulePosY(i) * pixelSize + b);
            }
        }
    }

    
    SDL_RenderPresent(renderer);
}


    void visualisationGraphe::loopEvent() {

        bool sim  = false;
        bool drawV = true;
        if (window) {
            int close = 0;
            
            while (!close) {
                affichage();
                // Events management
                if (sim) {
                    if (!G->seuil(0.95)) {
                        G->MAJ();
                    } else sim = !sim;
                }
                while (SDL_PollEvent(&event)) {
                    //
                    switch (event.type) {

                        case SDL_QUIT:
                            // handling of close button
                            close = 1;
                            break;
                        case SDL_KEYDOWN:
                            switch (event.key.keysym.sym) {
                                case SDLK_a:
                                    sim = !sim;
                                    break;
                                case SDLK_z:
                                    drawV = !drawV;
                                    break;
                                case SDLK_t:
                                    G->contamination();
                                    break;
                            }
                    }
                }
            }
        }
    }
    void visualisationGraphe::drawVoisinage() {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        //if (this->listeLigne.empty()) {
            for (int i = 0; i < G->nbCellule(); i++) {
                try{           
                    int posIX = G->getCellulePosX(i);
                    int posIY = G->getCellulePosY(i);
  
                    for (int j = 0; j < G->getCellule(i)->nbVoisin(); j++) {
                        Cellule* voisin = G->getCellule(i)->getVoisin(j);
                        int posJX = G->getPosCelluleX(voisin);
                        int posJY = G->getPosCelluleY(voisin);

                        SDL_RenderDrawLine(renderer,
                                       posIX * pixelSize + pixelSize / 2,
                                       posIY * pixelSize + pixelSize / 2,
                                       posJX * pixelSize + pixelSize / 2,
                                       posJY* pixelSize + pixelSize / 2);
                    }
                }catch( const exception & e ) {
                cerr << e.what() << endl;
                }
            }
        //}
        /*else{
            for (auto & i : this->listeLigne){
                SDL_RenderDrawLine(renderer,
                                   i.first.first * pixelSize + pixelSize / 2,
                                   i.first.second * pixelSize + pixelSize / 2,
                                   i.second.first * pixelSize + pixelSize / 2,
                                   i.second.second * pixelSize + pixelSize / 2);
            }
        }*/
        SDL_RenderPresent(renderer);
    }
