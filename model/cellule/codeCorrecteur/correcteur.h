//
// Created by kevin on 17/04/23.
//

#ifndef CODE_CORRECTEUR_H
#define CODE_CORRECTEUR_H


#include "../cellule.h"

class Correcteur : public Cellule{
public:
    Correcteur();

    void transition();

    int getValue();
    void setValue(int value);

    Correcteur* getVoisin(int i);
private:
    int value;
};


#endif //CODE_CORRECTEUR_H
