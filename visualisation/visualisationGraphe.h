//
// Created by kevin on 26/04/23.
//

#ifndef CODE_VISUALISATIONGRAPHE_H
#define CODE_VISUALISATIONGRAPHE_H

#include <SDL2/SDL.h>
#include "../model/graphe/graphe.h"

class VisualisationGraphe {
public:
    VisualisationGraphe(Graphe* G);

    void initVisualisation();

    void loopEvent();

private:

    void affichage();

protected:
    int height;
    int width;
    int pixelSize;
    SDL_Renderer *renderer;
    Graphe* G;
    SDL_Event event;
    SDL_Window *window;
};


#endif //CODE_VISUALISATIONGRAPHE_H
