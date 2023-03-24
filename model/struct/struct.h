//
// Created by kevin on 21/03/23.
//

#ifndef CODE_STRUCT_H
#define CODE_STRUCT_H

#include <iostream>

enum class VoisinageClassique : char{
    MOORE8,
    MOORE9,
    TOOM,
    VONNEUMAN
};

std::string ToString(VoisinageClassique v) noexcept;

#endif //CODE_STRUCT_H
