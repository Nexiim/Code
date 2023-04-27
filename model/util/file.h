//
// Created by kevin on 05/04/23.
//

#ifndef CODE_FILE_H
#define CODE_FILE_H

#include <mutex>
#include "../struct/struct.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class file {
private:

    static file* pinstance_;
    static std::mutex mutex_;

    char* filename;

    Topologie topologie;
    Bordure bordure;
    int* size;
    typeCellule cellule;
    VoisinageClassique voisinnage;
    double* parametre;
    int* nbIterationMax;
    double seuil;
    double* probaDef;
    Evolution evolution;
public:
    Evolution getEvolution() const;

    int getNbTest() const;

private:
    int nbTest;
    bool visualisation;
    int seed;

protected:
    file(){}

public:
    int *getSize() const;

protected:
    ~file() {}

public:

    file(file &other) = delete;

    void operator=(const file &) = delete;

    static file *GetInstance();

    void loadFile(char* nameFile);

    Topologie getTopologie() const;

    Bordure getBordure() const;

    typeCellule getCellue() const;

    VoisinageClassique getVoisinnage() const;

    double *getParametre() const;

    int* getNbIterationMax() const;

    double getSeuil() const;

    double *getProbaDef() const;

    bool isVisualisation() const;

    int getSeed() const;

    void write(string s);

};



#endif //CODE_FILE_H
