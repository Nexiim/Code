//
// Created by kevin on 18/04/23.
//

#include "VisuCodeCorrecteur.h"


void VisuCodeCorrecteur::affichage() {
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; ++i) {
            int v = dynamic_cast<Correcteur *>(G->getCellule(i, j))->getValue();
            if (v == -1) SDL_SetRenderDrawColor(renderer, 0,0, 0, 0);
            else if (v == 0) SDL_SetRenderDrawColor(renderer, 255,0, 0, 0);
            else if (v == 1) SDL_SetRenderDrawColor(renderer, 0,255, 0, 0);
            else if (v == 2)SDL_SetRenderDrawColor(renderer, 0,0, 255, 0);
            for(int a = 0; a < pixelSize; a++){
                for (int b = 0; b < pixelSize; b++){
                    SDL_RenderDrawPoint(renderer, i*pixelSize+a, j*pixelSize+b);
                }
            }
        }
    }
    SDL_RenderPresent(renderer);
}

VisuCodeCorrecteur::VisuCodeCorrecteur(int height, int witdh, Grille *G) : Visualisation(height, witdh, G) {
    this->pixelSize =5;
}

void VisuCodeCorrecteur::loopEvent() {
    bool sim = false;
    int x,y;
    Correcteur *c;
    if (window) {
        int close = 0;
        affichage();
        while (!close) {
            affichage();
            // Events management
            if(sim){
                for (int i =0; i < G->getWidth();i++){
                    for (int j =0; j < G->getHeight();j++){
                        c = dynamic_cast<Correcteur *>(G->getCellule(i, j));
                        c->transition();
                    }
                }
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
                                x = rand()%G->getWidth();
                                y = rand()%G->getHeight();
                                c = dynamic_cast<Correcteur *>(G->getCellule(x, y));
                                c->transition();
                                break;
                            case SDLK_t:
                                for (int i = 0; i < G->getWidth(); i++){
                                    for (int j =0; j < G->getHeight(); j++) {
                                        if (rand()%100 < 50) {
                                            int r = rand()%3;
                                            Correcteur *c = dynamic_cast<Correcteur *>(G->getCellule(i, j));
                                            c->setValue(r);
                                        }
                                    }
                                }
                                break;
                        }
                }
            }
        }
    }
}
