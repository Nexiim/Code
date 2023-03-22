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
        SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    }
}

void Visualisation::affichage(){
    for (int j = 0; j < height; j++) {
        for (int i = 0; i <width; ++i) {
            if (G->getCellule(i,j)->getEtat() == NORMAL) SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            else if (G->getCellule(i,j)->getEtat() == ALERTE) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            else SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

            SDL_RenderDrawPoint(renderer, i, j);
        }
    }
    SDL_RenderPresent(renderer);
}

void Visualisation::loopEvent() {

    if (window) {
        int close = 0;
        affichage();
        while (!close) {
            // Events management
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
                                while(!G->seuil(0.95)) {
                                    G->MAJGrille();
                                    affichage();
                                }

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
}



