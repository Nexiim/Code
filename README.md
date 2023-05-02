# Diagnostique décentralisé

Recherche de consensus pour le diagnostique décentralisé à l'aide d'automate cellulaire.


## Authors

- [@Engrand kevin](https://www.github.com/Nexiim)


## Demo

<p>Réprésentation Visuelle d'une grille, en rouge les cellule en état d'alerte, en noir les cellules défaillante et en blanc les cellules en état normal.</p>
<p align="center">
  <img src="https://user-images.githubusercontent.com/55401561/235657621-e514e135-ee06-4ce7-a7db-b9e779bfda77.png" a width="200" height="200"/>
</p>

<p>Représentation Visulle d'un graphe, en rouge les cellules défaillante, en vert les cellules dans un état normal, et en bleu les cellules dans un état d'alerte.
Les traits blancs représente le voisinage entre les cellules.</P>

<p align="center">
  <img src="https://user-images.githubusercontent.com/55401561/235660978-90af16f0-092e-41ca-b115-fd3d81784472.png" width="200" height="200" />
 </p>

## Usage/Exemples
<p>
Génération automatique des tests.
  
./Visualisation ficher.txt contenant :

topologie:Grille/Graphe
  
taille:x,y(grille)/x(graphe)
  
typeCellule:default/QuoromD
  
voisinnage:moore8/moore9/toom/vonNeumann/irregulier,x (grille)

parametre:x(QuorumD)
  
nbIteration:x
  
seuil:x(compris entre 0 et 1)
  
probaDef:x,y,z(liste de probabilité)
  
focus:probabilite, densite
  
visualisation:oui/non
  
seed:x(ou rien pour en générer une au hasard)
  
</p>
