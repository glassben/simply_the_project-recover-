
#include <stdio.h>
#include <string.h>
#include "constructeurs.h"  
#include "listes.h"

int acquisition(char *fichier,float* M);
// programme qui lit un fichier au format ".NGB" et qui l'analyse afin de transformer le maillage de ce fichier en mailllage memoire utilisable par les fonctions utilisees pour effectuer un traitement "Progressive Mesh". Cette fonction prend en paramatre un flottant M dans lequel elle renverra la plus grande distance entre 2 points du maillage. (ce-ci pourra etre utile comme sentinelle dans certains programmes)
