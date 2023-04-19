//
// Created by kevin on 17/04/23.
//

#include "correcteur.h"
Correcteur::Correcteur() {
 this->value = 0;
}

void Correcteur::transition() {
    if (getVoisin(0)->getValue() != -1 && getVoisin(1)->getValue() != -1) {
        if (getVoisin(0)->getValue() == getVoisin(1)->getValue())
            this->setValue((3 + getVoisin(0)->getValue() - 1) % 3);
        else this->setValue(-1);
    }
}

int Correcteur::getValue() {
    return value;
}

Correcteur *Correcteur::getVoisin(int i) {
    return dynamic_cast<Correcteur *>(this->voisins.at(i));
}

void Correcteur::setValue(int value) {
    this->value = value;
}

