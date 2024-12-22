// package construisant les listes
#ifndef LISTES_H
#define LISTES_H
#include <stdio.h>
#include "constructeurs.h"



// les structres de listes 
struct liste_sommets_elem;
typedef struct liste_sommets_elem *liste_sommets;
struct liste_sommets_elem{
  sommet *S;
  struct liste_sommets_elem * suiv;
};

struct liste_faces_elem;
typedef struct liste_faces_elem *liste_faces;
struct liste_faces_elem{
  face *F;
  struct liste_faces_elem * suiv;
};

struct liste_aretes_elem;
typedef struct liste_aretes_elem *liste_aretes;
struct liste_aretes_elem{
  arete *A;
  face *f;
  struct liste_aretes_elem *suiv;
};




int present_liste_sommet(sommet *S1, liste_sommets L);
  // recherche si le sommet S1 est present dans la liste des sommets L 
  // attention cette procedure ne prend pas en compte l'information de chaque points.

liste_sommets  ajouter_sommet(sommet *S, liste_sommets L);
  // renvoie la liste L a laquelle on a ajouter le sommet S

liste_sommets supprimer_sommet(sommet *S, liste_sommets L);
  // renvoie la liste L dans laquelle on a supprime le sommet S


int present_liste_face(face *F1, liste_faces L);
// fonction qui teste si la face F1 est present dans la liste L

liste_faces  ajouter_face(face *F, liste_faces L);
// fonction qui renvoie la liste L auquel on a rajouter la face F en tete.



liste_faces supprimer_face(face *F, liste_faces L);
// procedure qui renvoie la liste L privee de F



int afficher_liste_sommet(liste_sommets L);
// affiche la liste des sommets passee en parametre.


int present_liste_arete(arete *A1, liste_aretes L);
// recherche si l'arete A est presente dans la liste L

liste_aretes  ajouter_arete(arete *A,face *f, liste_aretes L);
// ajoute l'arete A de la face f a la liste d'arete L
// remarque : on stocke aussi la face a laquelle est associee l'arete afin de ne pas devoir parcourir l'integralite de la liste de face quand on veut travailler sur une arete (car la structure de base de tous les algo sont les faces)



liste_aretes supprimer_arete(arete *A, liste_aretes L);
// renvoie la liste L dans laquelle on a supprime A


int afficher_liste_arete(liste_aretes L);
// affiche la liste d'arete L



int afficher_liste_face(liste_faces L);
// procedure qui affiche la liste de face L



liste_sommets intersection_liste_sommet(liste_sommets L1,liste_sommets L2);
// procedure qui renvoie une liste de sommets intersection des listes de sommets L1 et L2


liste_faces intersection_liste_face(liste_faces L1,liste_faces L2,liste_faces L3);
// procedure qui renvoie une liste intersection des 3 listes de faces L1, L2, L3


#endif
















