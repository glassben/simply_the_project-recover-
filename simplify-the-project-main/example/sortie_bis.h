// procedure de sortie du maillage au format .off utilisant un ordre topologique sur les points et les faces afin de permettre la comparaison des maillages grace a un "diff" des deux fichiers ".off" sous UNIX. 
#include <stdio.h>
#include <string.h>



#ifndef CONSTRUCTEUR_H
#include "constructeurs.h"  
#endif



FILE *fp;


// On recupere les variables globales 
extern liste_sommets L_sommets;
extern liste_faces L_faces;
extern liste_aretes L_aretes_retirees;








int sortie_OFF_bis(char* fichier);
// procedure qui transforme le maillage represente en memoire en maillage au format ".off" pouvant etre visualises par Geomview. La difference avec la fonction sortie.off est que cette fonction met un ordre topologique sur les points et sur les faces lors de la sortie ce qui permet de comparer les fichiers par un simple "diff". Le prix a payer pour cela est une modification de l'ordre de points et des faces en memoire. Pour une plus grande securite il est donc conseiller de n'utiliser cette procedure qu'en fin d'exection de programme ou de reeffectuer une acquisition de donnees. 








