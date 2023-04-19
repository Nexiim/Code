//
// Created by kevin on 15/03/23.
//

#include "visualisation.h"



void Visualisation::initVisualisation() {
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return;
    }

    else {
        SDL_CreateWindowAndRenderer(width*pixelSize, height*pixelSize, 0, &window, &renderer);
    }
}

void Visualisation::affichage(){
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

void Visualisation::loopEvent() {
    bool sim = false;
    int s = 0;
    if (window) {
        int close = 0;
        affichage();
        while (!close) {
            affichage();
            // Events management
            if(sim){
                if(!G->seuil(0.95)) {
                    G->MAJGrille();
                }
                else sim = !sim;
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
                                G->MAJGrille();
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

Visualisation::Visualisation(int height, int witdh, Grille *G) {
    this->height= height;
    this->width = witdh;
    this->G = G;
    this->pixelSize = 1;
}

Grille* Visualisation::getGrille() {
    return G;
}



