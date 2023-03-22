//
// Created by kevin on 21/03/23.
//

#include "struct.h"

std::string ToString(Voisinage v) noexcept{
    switch (v)
    {
        case Voisinage::VONNEUMAN: return "vonneuman";
        case Voisinage::MOORE8: return "moore8";
        case Voisinage::MOORE9: return "moore9";
        case Voisinage::TOOM: return "toom";
    }
    return "default";
}
