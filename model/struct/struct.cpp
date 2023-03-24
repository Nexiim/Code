//
// Created by kevin on 21/03/23.
//

#include "struct.h"

std::string ToString(VoisinageClassique v) noexcept{
    switch (v)
    {
        case VoisinageClassique::VONNEUMAN: return "vonneuman";
        case VoisinageClassique::MOORE8: return "moore8";
        case VoisinageClassique::MOORE9: return "moore9";
        case VoisinageClassique::TOOM: return "toom";
    }
    return "default";
}
