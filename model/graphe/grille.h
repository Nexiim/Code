//
// Created by kevin on 21/03/23.
//

#ifndef CODE_GRILLE_H
#define CODE_GRILLE_H

#include "graphe.h"

class Grille : public Graphe {
public:
    // Constructeur prenant en paramètre la largeur, la hauteur et le type de cellule
    Grille(int width, int height, typeCellule c);
    
    // Constructeur prenant en paramètre la largeur, la hauteur, le type de cellule, la probabilité de départ et un tableau de précalcul
    Grille(int width, int height, typeCellule c, double lambda, double* preCalcul);

    // Constructeur prenant en paramètre la largeur, la hauteur, le type de cellule et la probabilité de départ
    Grille(int width, int height, typeCellule c, double lambda);

    // Renvoie la cellule à la position (i,j) dans la grille
    Cellule *getCellule(int i, int j);

    // Affiche la grille dans la console
    void affichageGrille();

    // Met à jour la grille
    void MAJ();

    // Définit le type de bordure utilisé pour la grille
    void setBordure(Bordure b);

    // Renvoie la largeur de la grille
    int getWidth();

    // Renvoie la hauteur de la grille
    int getHeight();

    typeVoisinage getVosinage();

    void setVoisinage(typeVoisinage t);

    // Met à jour les cellules selon un voisinage irrégulié
    void setVoisinageNorme(double r);
    void setVoisinageNorme(int x, int y, double r);

    // Met à jour les cellules selon le voisinage de Moore 8
    void Moore8();

    // Met à jour les cellules selon le voisinage de Moore 9
    void Moore9();

    // Met à jour les cellules selon le voisinage de Von Neumann
    void VonNeumann();

    // Met à jour les cellules selon le voisinage de Toom
    void Toom();

private:
    // Largeur de la grille
    int width{};
    // Hauteur de la grille
    int height{};
    // Type de bordure utilisé
    Bordure b;
};


#endif //CODE_GRILLE_H
