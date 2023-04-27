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
    Grille* getGrille();

private:

    void affichage();

protected:
    int height;
    int width;
    int pixelSize;
    SDL_Renderer *renderer;
    Grille* G;
    SDL_Event event;
    SDL_Window *window;
};

#endif //CODE_VISUALISATION_H
