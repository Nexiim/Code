//
// Created by kevin on 26/04/23.
//

#include "visualisation.h"

visualisation::visualisation(int width, int height) {
    this->width = width;
    this->height = height;
    this->pixelSize = 8;
}

visualisation::visualisation(int width, int height,int pixelSize) {
    this->width = width;
    this->height = height;
    this->pixelSize = pixelSize;
}


void visualisation::initVisualisation() {
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
