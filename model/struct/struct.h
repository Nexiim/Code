//
// Created by kevin on 21/03/23.
//

#ifndef CODE_STRUCT_H
#define CODE_STRUCT_H

#include <iostream>

enum class typeVoisinage: char{
    MOORE8,
    MOORE9,
    TOOM,
    VONNEUMAN,
    IRREGULIER,
    PLUSPROCHE
};

enum class typeCellule{
    QUOROMD,
    CORRECTEUR,
    DEFAULT
};

enum class Bordure :char{
    BORD,
    TORIQUE
};

enum class Topologie : char{
    GRILLE,
    GRAPHE
};

enum class Evolution{
    DENSITY,
    PROBABILITE
};

typedef enum{DEFAILANTE,ALERTE,NORMAL} Etat;

std::string ToString(typeVoisinage v) noexcept;

#endif //CODE_STRUCT_H
