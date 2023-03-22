//
// Created by kevin on 15/03/23.
//

#ifndef CODE_VISUALISATION_H
#define CODE_VISUALISATION_H

#include <SDL2/SDL.h>
#include "../model/graphe/graphe.h"
#include "../model/graphe/grille.h"

class Visualisation{
public:
    Visualisation(int height,int witdh,Grille* G);

    void initVisualisation();

    void loopEvent();
private:
    int height;
    int width;
    Grille* G;
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    void affichage();
};

#endif //CODE_VISUALISATION_H
