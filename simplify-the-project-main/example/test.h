// package construisant les test de coherence du maillage.
#ifndef TEST_H
#define TEST_H
#include <stdio.h>
#include "constructeurs.h"
#include "listes.h"


int doublon_face(liste_faces param);
// procedure qui teste si il y a ou non deux faces identiques dans la lise de faces param.


int doublon_sommet(liste_sommets param);
// procedure qui teste si il y a ou non deux sommets identiques dans la lise de sommets param.

int chainage_non_reccursif();
// procedure qui verifie qu'une face n'est pas chaine a elle meme dqns la liste de faces L_faces (variable globale).


int a_2voisins();
// verifie que chaques faces a bien au moins deux faces voisines
// a utiliser avec precaution car des collapses de faces de bord peuvent amener une face du maillage a n'avoir plus qu'une voisine.

int verification_chainage(liste_faces L);
// verifie que deux faces chainees ensemble ont bien deux sommets communs

face* test_nb_arete_face();
// procedure qui verifie qu'une arete est bien commune a deux faces au plus
// tres important lors de la verification de la coherence du maillage.


#endif








