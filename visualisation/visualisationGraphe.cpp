//
// Created by kevin on 26/04/23.
//

#include "VisualisationGraphe.h"

VisualisationGraphe::VisualisationGraphe(Graphe *G) {
    this->width = G->getWidth();
    this->height = G->getHeight();
    this->G = G;
}

void VisualisationGraphe::initVisualisation() {
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return;
    }

    else {
        SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    }
}

void VisualisationGraphe::affichage(){
    for (int i =0; i < G->nbCellule(); i++){
        if (G->getCellule(i)->getEtat() == NORMAL) SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        else if (G->getCellule(i)->getEtat() == ALERTE) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        else SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

        for(int a = 0; a < pixelSize; a++){
            for (int b = 0; b < pixelSize; b++){
                SDL_RenderDrawPoint(renderer, G->getPosCellule(i).first*pixelSize+a, G->getPosCellule(i).second*pixelSize+b);
            }
        }
    }
    for (int j = 0; j < height; j++) {
        for (int i = 0; i <width; ++i) {
            if (G->getCellule(i,j)->getEtat() == NORMAL) SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            else if (G->getCellule(i,j)->getEtat() == ALERTE) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            else SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            for(int a = 0; a < pixelSize; a++){
                for (int b = 0; b < pixelSize; b++){
                    SDL_RenderDrawPoint(renderer, i*pixelSize+a, j*pixelSize+b);
                }
            }
        }
    }
    SDL_RenderPresent(renderer);
}
