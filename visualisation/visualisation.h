//
// Created by kevin on 26/04/23.
//

#ifndef CODE_VISUALISATION_H
#define CODE_VISUALISATION_H

#include <SDL2/SDL.h>

class visualisation {
    public:
        visualisation(int width, int height);
        visualisation(int width, int height,int pixelSize);

        void initVisualisation();

        void loopEvent();

    protected:
        int height;
        int width;
        int pixelSize;
        SDL_Renderer *renderer;
        SDL_Event event;
        SDL_Window *window;
};


#endif //CODE_VISUALISATION_H
