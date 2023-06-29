//
// Created by kevin on 21/03/23.
//

#include "struct.h"

std::string ToString(typeVoisinage v) noexcept{
    switch (v)
    {
        case typeVoisinage::VONNEUMAN: return "vonneuman";
        case typeVoisinage::VONNEUMAN4: return "vonneuman4";
        case typeVoisinage::MOORE8: return "moore8";
        case typeVoisinage::MOORE9: return "moore9";
        case typeVoisinage::TOOM: return "toom";
        case typeVoisinage::IRREGULIER: return "irregulie";
        case typeVoisinage::PLUSPROCHE: return "plusProche";
    }
    return "default";
}


std::string ToString(typeCellule c) noexcept{
    switch (c)
    {
        case typeCellule::QUOROMD:return "quorumD";
        case typeCellule::CORRECTEUR:return "correcteur";
        case typeCellule::DEFAULT:return "default";
    }
    return "cellule none";
}
