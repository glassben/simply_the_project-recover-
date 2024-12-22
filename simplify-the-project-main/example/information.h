#ifndef INFORMATION_H
#define INFORMATION_H




// la structure information associee a un sommet
struct information_b{
  float r;// valeur de la composante de coloration rouge (comprise entre 0 et 1)
  float g;// valeur de la composante de coloration verte (comprise entre 0 et 1)
  float b;// valeur de la composante de coloration bleue (comprise entre 0 et 1)
  int numero_affichage;// sert lors de la generation du .off en sortie de l'algo
};
typedef struct information_b information;


// La structure sommet et les pointeurs vers cette structure
typedef float type_coordonnee;



struct sommet_b {
  type_coordonnee x;
  type_coordonnee y;
  type_coordonnee z;
  information *info; 
};

typedef struct sommet_b sommet;

sommet* creer_sommet(type_coordonnee x,type_coordonnee y,type_coordonnee z,information *info);
// fonction qui cree et renvoie un sommet ayant pour coordonnee (x,y,z) et une information info 


information* creer_info();
// procedure qui renvoe un pointeur vers une information. Utilisee lors de la creation des points du maillage.

int afficher_info(sommet *S);
// procedure d'affichage de l'information associee a un point.


information* info_fusion(sommet *S1,sommet *S2);
// procedure qui renvoie l'information que devra contenir le point fusion des points S1 et S2 lors du edge collapse.


sommet* sommet_fusion(sommet * S1, sommet * S2);
  // procedure qui renvoie le sommet fusion de S1 et S2




#endif


