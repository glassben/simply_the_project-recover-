#include "information.h"



sommet* creer_sommet(type_coordonnee x,type_coordonnee y,type_coordonnee z,information *info){
// fonction qui cree et renvoie un sommet ayant pour coordonnees (x,y,z) et une information info 
  sommet *S;
  S=(sommet *)malloc(sizeof(sommet)); 
  S->x=x;
  S->y=y;
  S->z=z;
  S->info=info;
  return S;
}


information* creer_info(){
// procedure qui renvoie un pointeur vers une information. Utilisee lors de la creation des points du maillage.
  information * i;
  i=(information *)malloc(sizeof(information));
  return i;
}

int afficher_info(sommet *S){
// procedure d'affichage de l'information associee a un point.
  return 1;
}

information* info_fusion(sommet *S1,sommet *S2){
  // procedure qui renvoie l'information que devra contenir le point fusion des points S1 et S2 lors du edge collapse.
  information *i;

  i=creer_info();
  i->r=(S1->info->r+S2->info->r)/2;
  i->g=(S1->info->g+S2->info->g)/2;
  i->b=(S1->info->b+S2->info->b)/2;
}



sommet* sommet_fusion(sommet * S1, sommet * S2){
  // procedure qui renvoie le sommet fusion de S1 et S2
  return creer_sommet((S1->x+S2->x)/2,(S1->y+S2->y)/2,(S1->z+S2->z)/2,info_fusion(S1,S2));
}








