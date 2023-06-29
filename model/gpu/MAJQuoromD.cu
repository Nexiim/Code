#include "MAJQuoromD.cuh"

__global__  void QuorumD(int seed, int *cels, int *celsSync, int *posVoisins, int *voisins,int *nbAlerte,double lambda){
    int i = blockIdx.x*blockDim.x + threadIdx.x;
    
    curandState localstate;
    curand_init(seed,i,0,&localstate);

    if (cels[i] == DEFAILANTE){
        celsSync[i] = DEFAILANTE;
        return;
    }
    
    int nbVoisinN = 0;
    int nbVoisinAD = 0;
    int nbVoisinT = 0;

    for (int a = posVoisins[i*2]; a <= posVoisins[i*2+1]; a++){
        if (voisins[a] == -1) break;
        if(cels[voisins[a]] == NORMAL) nbVoisinN++;
        else nbVoisinAD++;
        nbVoisinT++;
    }
    
    if (nbVoisinN == nbVoisinT){
        celsSync[i] = NORMAL;
        return;
    }

    if (nbVoisinAD == nbVoisinT) {
        celsSync[i] = ALERTE;
        atomicAdd(nbAlerte,1);
        return;
    }
    
    double wn = exp(lambda * ((double)nbVoisinN / (double)nbVoisinT));
    double wad = exp(lambda * ((double)nbVoisinAD / (double)nbVoisinT));
    double probaN = wn / (wn + wad);

    float r = curand_uniform(&localstate);

    if(r < probaN )celsSync[i] = NORMAL;
    else {
        atomicAdd(nbAlerte,1);
        celsSync[i] = ALERTE;
    }
    return;
}


