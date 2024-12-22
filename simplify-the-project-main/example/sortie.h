#ifndef SORTIE_H
#include <stdio.h>
#include <string.h>
#include "listes.h"


// On recupere les variables globales 
extern liste_sommets L_sommets;
extern liste_faces L_faces;
extern liste_aretes L_aretes_retirees;

extern int NB_MAX_SOMMETS;
extern int NB_MAX_TRIANGLES;

extern int bool_sortie_OFF;// si 0 sortie au format ".off" sinon sortie au format ".wrl"

extern int couleur_sommet;// si bool_sortie_OFF=0, ce booleen determine si on associe une couleur a chaque sommet ou non.


int sortie_OFF(char* fichier);
// procedure qui transforme le maillage represente en memoire en maillage au format ".off" pouvant etre visualises par Geomview

int sortie_WRL(char* fichier);
// procedure qui transforme le maillage represente en memoire en maillage au format ".wrl"

int sortie_OFF_couleur(char* fichier,face *F1,face *F2);
// procedure qui transforme le maillage represente en memoire en maillage au format ".off" pouvant etre visualises par Geomview. Cette procedure collore en rouge les faces F1 et F2 et en bleu les faces voisines des faces F1 et F2.


int sortie_COFF(char* fichier);
// procedure qui transforme le maillage represente en memoire en maillage au format "coff" pouvant etre visualise par Geomview. Ce format necessite la presence de champs "r","g","b" dans les informations associees aux points afin de pouvoir effectuer une sortie en couleur.


int sortie(char *fichier);
// fonction qui selon les variables globales effectue le dispatching sur les fonctions de sorties ci-dessus

#endif










