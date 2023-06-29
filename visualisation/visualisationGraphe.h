//
// Created by kevin on 26/04/23.
//

#ifndef CODE_VISUALISATIONGRAPHE_H
#define CODE_VISUALISATIONGRAPHE_H

#include <SDL2/SDL.h>
#include "../model/graphe/graphe.cuh"
#include "visualisation.h"

class visualisationGraphe : public visualisation{
public:
    visualisationGraphe(Graphe* G);

    void loopEvent();

private:

    void affichage();
    void drawVoisinage();

protected:
    Graphe* G;
    vector<pair<pair<int,int>,pair<int,int>>> listeLigne;
};


#endif //CODE_VISUALISATIONGRAPHE_H
