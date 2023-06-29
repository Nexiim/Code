#ifndef MAJQUOROMD_H
#define MAJQUOROMD_H

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <curand.h>
#include <curand_kernel.h>

#include"../cellule/celluleQuoromD.h"

__global__ void QuorumD(int seed, int *cels, int *celsSync, int *posVoisins, int *voisins,int *nbAlerte,double lambda);



#endif //MAJQUOROMD_H