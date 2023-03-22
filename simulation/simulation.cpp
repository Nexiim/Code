//
// Created by kevin on 15/03/23.
//
#include "simulation.h"


Simulation::Simulation(int *T, int nbTest, double *probaDef, double threshold) {
    this->T = T;
    this->nbTest = nbTest;
    this->probaDef = probaDef;
    this->threshold = threshold;
}

void Simulation::writeFile(string s) {
    file << s << endl;
}

void Simulation::openFile(string name) {
    file = ofstream(name, ios::out | ios::trunc);
}

void Simulation::closeFile() { file.close(); }

