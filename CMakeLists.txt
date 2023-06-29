cmake_minimum_required(VERSION 3.18)

project(Code LANGUAGES CXX CUDA)

find_package(CUDA QUIET REQUIRED)

set(
    CUDA_NVCC_FLAGS
    ${CUDA_NVCC_FLAGS};
    -O3 -gencode arch=compute_22,code=sm_22
    )

find_package(SDL2 REQUIRED)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

include_directories(${SDL2_INCLUDE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})


set(BASIC_SOURCE "")
list(APPEND BASIC_SOURCE 

    #model
    model/cellule/cellule.h
    model/cellule/celluleQuoromD.h
   
    model/struct/struct.h
    model/util/file.h 
    model/cellule/codeCorrecteur/correcteur.cpp
    #simulation
    simulation/simulation.cpp
    simulation/simulationQuoromD.cpp

    #model
    model/cellule/cellule.cpp
    model/cellule/celluleQuoromD.cpp
   
    model/struct/struct.cpp
    model/util/file.cpp
    model/cellule/codeCorrecteur/correcteur.h

    #simulation
    simulation/simulation.h
    simulation/simulationQuoromD.h
)

set(VISU_SOURCE "")
list(APPEND VISU_SOURCE
    #visualisation
    visualisation/visualisation.cpp 
    visualisation/visualisationGrille.cpp
    visualisation/visualisationGraphe.cpp
    visualisation/codeCorrecteur/VisuCodeCorrecteur.cpp

    #visualisation
    visualisation/visualisation.h
    visualisation/visualisationGrille.h
    visualisation/visualisationGraphe.h
    visualisation/codeCorrecteur/VisuCodeCorrecteur.h

)

set(CUDA_SOURCE "")
list(APPEND CUDA_SOURCE
    model/gpu/MAJQuoromD.cuh
    model/graphe/graphe.cuh
    model/graphe/grille.cuh

    model/gpu/MAJQuoromD.cu
    model/graphe/graphe.cu
    model/graphe/grille.cu
)


add_executable(Test ${BASIC_SOURCE} ${CUDA_SOURCE} main.cpp)
add_executable(Simulation ${BASIC_SOURCE} ${CUDA_SOURCE} Simulation.cpp)
add_executable(CodeCorrecteur ${BASIC_SOURCE} codeCorrecteur.cpp)
add_executable(Percolation ${BASIC_SOURCE} Percolation.cpp)

target_link_libraries(Test)
target_link_libraries(Simulation )
target_link_libraries(CodeCorrecteur )
target_link_libraries(Percolation )
