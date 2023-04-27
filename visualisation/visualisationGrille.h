//
// Created by kevin on 15/03/23.
//

#ifndef CODE_VISUALISATIONGRILLE_H
#define CODE_VISUALISATIONGRILLE_H

#include <SDL2/SDL.h>
#include "../model/graphe/graphe.h"
#include "../model/graphe/grille.h"
#include "visualisation.h"

class visualisationGrille : public visualisation{
public:
    visualisationGrille(int width,int height,Grille* G);

    void loopEvent();

    Grille* getGrille();

private:

    void affichage();

protected:
    Grille* G;

};

#endif //CODE_VISUALISATIONGRILLE_H
