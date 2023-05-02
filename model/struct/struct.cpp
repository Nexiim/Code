//
// Created by kevin on 21/03/23.
//

#include "struct.h"

std::string ToString(typeVoisinage v) noexcept{
    switch (v)
    {
        case typeVoisinage::VONNEUMAN: return "vonneuman";
        case typeVoisinage::MOORE8: return "moore8";
        case typeVoisinage::MOORE9: return "moore9";
        case typeVoisinage::TOOM: return "toom";
        case typeVoisinage::IRREGULIER: return "irregulié";
        case typeVoisinage::PLUSPROCHE: return "plusProche";
    }
    return "default";
}
