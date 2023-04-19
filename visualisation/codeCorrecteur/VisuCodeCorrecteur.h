//
// Created by kevin on 18/04/23.
//

#ifndef CODE_VISUCODECORRECTEUR_H
#define CODE_VISUCODECORRECTEUR_H


#include "../visualisation.h"
#include "../../model/cellule/codeCorrecteur/correcteur.h"


class VisuCodeCorrecteur : public Visualisation{

public:

    VisuCodeCorrecteur(int height,int witdh,Grille* G);

    void loopEvent();
    void affichage();
};


#endif //CODE_VISUCODECORRECTEUR_H
