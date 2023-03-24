cmake_minimum_required(VERSION 3.24)
project(Code)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Code main.cpp model/cellule/cellule.h model/cellule/cellule.cpp model/graphe/graphe.h model/graphe/graphe.cpp visualisation/visualisation.cpp visualisation/visualisation.h simulation/simulation.cpp simulation/simulation.h simulation/simulationQuoromD.cpp simulation/simulationQuoromD.h model/cellule/celluleQuoromD.cpp model/cellule/celluleQuoromD.h model/graphe/grille.cpp model/graphe/grille.h model/struct/struct.h model/struct/struct.cpp model/Voisinage/Voisinage.cpp model/Voisinage/Voisinage.h)
target_link_libraries(Code ${SDL2_LIBRARIES})