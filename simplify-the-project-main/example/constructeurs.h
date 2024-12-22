// package construisant les constructeurs
#ifndef CONSTRUCTEUR_H
#define CONSTRUCTEUR_H
#include <stdio.h>
//On commence par definir les structures qui seront utilisees.
#include "information.h"

// La structure face et pointeurs sur face
struct face_b;
typedef struct face_b face;

typedef face* ptr_face;
struct face_b {
  sommet *S0;
  sommet *S1;
  sommet *S2;
  face *f0; 
  face *f1; 
  face *f2; 
};



// la structure arete et les pointeurs vers arete
struct arete_b{
  sommet *S0;
  sommet *S1;
};

typedef struct arete_b arete;



int afficher_sommet(sommet *S);
  // procedure qui affiche les coordonnees des sommets

int afficher_arete(arete *A);
// procedure qui affiche une arete A

int afficher_face(face *F);
// procedure qui affiche la face F


face* creer_face(sommet *S1,sommet *S2,sommet *S3,face *f0,face *f1,face *f2);
// fonction qui renvoie une face ayant pour sommet S1, S2 et S3 et pour faces voisine f0, f1, f2.


sommet *dupliquer_sommet(sommet *S1);
  // fonction qui renvoie un sommet qui est un duplicata du sommet passe en parametre.
// cette procedure ne sera pas utilisee.


arete* creer_arete(sommet *S1,sommet *S2);
// fonction qui renvoie une arete de sommets S1 et S2

int meme_sommet(sommet* S1,sommet* S2);
// fonction qui teste si les sommets S1 et S2 sont identiques

int meme_face(face *F1,face *F2);
  // verifie que les face F1 et F2 sont les meme en verifiant qu'elle comporte bien les memes sommets.
// cette procedure ne verifie pas que les voisin des face F1 et F2 sonte les memes


int meme_arete(arete *A1,arete *A2);
// fonction qui compare deux aretes



int changer_sommet(face *F,sommet *S1,sommet *S);
  // procedure qui remplace le sommet de la face F qui correspond a S1 par le pointeur vers le sommet S
  // Remarque : avec le codage prevu, cette procedure ne doit pas faire plus d'un remplacement
  // par appel. On y veillera et on renverra une erreur sinon.



int changer_face_vs(face *F , face *F1, face *F2,sommet *S,sommet *S1,sommet *S2);
// procedure appelee lors du vertex split et qui gere le chainage des faces dans le cas ou l'une des deux faces a inserer est a inserer a cote d'une face NULL.

int changer_face ( face *Face , face *Face1, face *Face2);
  // procedure qui change le pointeur de la face F pointant vers la face Face1 par le pointeur pointant vers la face Face2
  // cette procedure n'est sense effectuer qu'un echange par appel, ce que l on verifiera.


int remplacer(sommet *S1,sommet *S2);
// procedure qui remplace le sommet S1 par le sommet S2 en dur
// cette procedure ne sera pas utilisee.

int mod(int x, int y);
  // retourne x mod y (resultat positif)


face* face_numero(int n, face *F);
//  renvoie la face voisine de F ayant le  numero n. n est soit 0 soit 1 soit 2.

sommet * sommet_numero(int n, face *F);
// renvoie le sommet numero n de la face F


int indice_sommet_face(sommet *S,face *F);
// procedure qui renvoie le numero du sommet S dans la face F


int changer_face_numero(face *F,int n, face *Face);
// change la face numero n de F par la face Face.  n doit etre soit 0 soit 1 soit 2.


int appartient_a_la_face(sommet *S,face *f);
// teste si le sommet S appartient a la face f

int numero_sommet_non_commun_face(face *f1,face * f2);
  // procedure qui renvoie le numero du sommet de la face f1 qui n'appartient pas a la face f2
  // on verifiera que ces 2 faces ont bien 2 sommets en communs (qu'elles ont un arete en commun)
  // elle renverra 3 si f2=null


int a_2sommets_communs(face *f1,face *f2);
// procedure qui renvoie 1 si les faces f1 et f2 ont deux sommets communs.


int a_2sommets_communs_bis(face *f1,face *f2,sommet *Sommet1,sommet *Sommet2);
  // procedure qui renvoie 1 si les deux faces ont 2 sommets differents de S1 et de S2 communs et 0 sinon.


int chainer_face(face *f,face *f1,face *f2,face *f3);
  // procedure qui chaine les faces f1,f2,f3 a la face f en respectant les regles topologiques


int affichage_face_voisin(face *F, int num_face);
// procedur qui affiche la face F et les face qui lui sont voisines. Cette procedure est utilisee lors du debogage.


int nb_voisins_NULL(face *F);
// fonction qui renvoie le nombre de voisin de la face F a NULL.


float distance_au_carre(sommet *S1,sommet *S2);
// procedure qui renvoie la distance au carre entre S1 et S2


#endif






















































