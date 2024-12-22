
#include <stdio.h>
#include <string.h>



#ifndef CONSTRUCTEUR_H
#include "constructeurs.h"  
#endif

#ifndef LISTES_H
#include "listes.h"  
#endif



FILE *fp;

// On recupere les variables globales 
extern liste_sommets L_sommets;
extern liste_faces L_faces;
extern liste_aretes L_aretes_retirees;
extern bool_sortie_OFF;
extern couleur_sommet;



int sortie_OFF(char* fichier){
// procedure qui transforme le maillage represente en memoire en maillage au format ".off" pouvant etre visualises par Geomview
  int nb_points;
  int nb_faces;
  liste_sommets Ls;
  liste_faces Lf;
  char tmp_b[100];
  char * tmp;
  sommet *S;
  int cpt;
  face *F; 
int i;

  // on compte le nombre de points de la structure
  Ls=L_sommets;
  nb_points=0;
  while (Ls!=NULL){
    nb_points++;
    Ls=Ls->suiv;
  }
 
  // on compte le nombre de faces de la structure
  Lf=L_faces;
  nb_faces=0;
  while (Lf!=NULL){
    nb_faces++;
    Lf=Lf->suiv;
  }
 
  // on ouvre le fichier dans lequel on va ecrire
  if ((fp=fopen(fichier,"w"))==NULL){
    printf("Erreur lors de l'ouverture du fichier %s\n",fichier);
    exit(1);
  } 

  tmp="OFF\n";
  fputs(tmp,fp);
  // on ecrit le nombre de points et le nombre de faces
  fprintf(fp,"%i %i 0\n",nb_points,nb_faces);
  // on inscrit les coordonnees des points et des normales (nulles)
  Ls=L_sommets;
  cpt=0;
  while (Ls!=NULL){
    S=Ls->S;
    fprintf(fp,"%f %f %f \n",S->x,S->y,S->z);
    if (S->info==NULL)
      S->info=creer_info();
    S->info->numero_affichage=cpt; 
    cpt++; 
    Ls=Ls->suiv;
  }
 
  // on inscrit les faces
  Lf=L_faces;
  while (Lf!=NULL){
    F=Lf->F;
    if (present_liste_sommet(F->S0,L_sommets)&&present_liste_sommet(F->S1,L_sommets)&&present_liste_sommet(F->S2,L_sommets))
      fprintf(fp,"3 %d %d %d\n",F->S0->info->numero_affichage,F->S1->info->numero_affichage,F->S2->info->numero_affichage);
    else
      printf("erreur sommet non present dans le graphe mais present dans une face.\n");
    Lf=Lf->suiv;
  }  
  close(fp);

}



int sortie_WRL(char* fichier){
// procedure qui transforme le maillage represente en memoire en maillage au format ".wrl"
  int nb_points;
  int nb_faces;
  liste_sommets Ls;
  liste_faces Lf;
  char tmp_b[100];
  char * tmp;
  sommet *S;
  int cpt;
  face *F; 
   
  // on compte le nombre de points de la structure
  Ls=L_sommets;
  nb_points=0;
  while (Ls!=NULL){
    nb_points++;
    Ls=Ls->suiv;
  }
  
  // on compte le nombre de faces de la structure
  Lf=L_faces;
  nb_faces=0;
  while (Lf!=NULL){
    nb_faces++;
    Lf=Lf->suiv;
  }
  
  // on ouvre le fichier dans lequel on va ecrire
  if ((fp=fopen(fichier,"w"))==NULL){
    printf("Erreur lors de l'ouverture du fichier %s\n",fichier);
    exit(1);
  } 
  
  tmp="#VRML V1.0 ascii\n";
  fputs(tmp,fp);
  tmp="\n";
  fputs(tmp,fp);
  tmp="Coordinate3 {\n";
  fputs(tmp,fp);
  tmp="  point [\n";
  fputs(tmp,fp);
  // on inscrit les coordonnees des points et des normales (nulles)
  Ls=L_sommets;
  cpt=0;
  while (Ls!=NULL){
    S=Ls->S;
    fprintf(fp,"   %f  %f  %f,\n",S->x,S->y,S->z);
    S->info->numero_affichage=cpt; 
    cpt++;
    Ls=Ls->suiv;
  }
  tmp="  ]\n";
  fputs(tmp,fp);
  tmp="}\n";
  fputs(tmp,fp);
  tmp="\n";
  fputs(tmp,fp);
  tmp="IndexedFaceSet {\n";
  fputs(tmp,fp);
  tmp="coordIndex [\n";
  fputs(tmp,fp);
  // on inscrit les faces
  Lf=L_faces;
  while (Lf!=NULL){
    F=Lf->F;
    fprintf(fp,"  %d, %d, %d, -1,\n",F->S0->info->numero_affichage,F->S1->info->numero_affichage,F->S2->info->numero_affichage);
    Lf=Lf->suiv;
  }  
  tmp="  ]\n";
  fputs(tmp,fp);
  tmp="}\n";
  fputs(tmp,fp);

  close(fp);
}






int sortie_OFF_couleur(char* fichier,face *F1,face *F2){
// procedure qui transforme le maillage represente en memoire en maillage au format ".off" pouvant etre visualises par Geomview. Cette procedure colore en rouge les face F1 et F2 et en bleu les faces voisines des faces F1 et F2.
  int nb_points;
  int nb_faces;
  liste_sommets Ls;
  liste_faces Lf;
  char tmp_b[100];
  char * tmp;
  sommet *S;
  int cpt;
  face *F; 
  int i;

  // on compte le nombre de points de la structure
  Ls=L_sommets;
  nb_points=0;
  while (Ls!=NULL){
    nb_points++;
    Ls=Ls->suiv;
  }
 
  // on compte le nombre de faces de la structure
  Lf=L_faces;
  nb_faces=0;
  while (Lf!=NULL){
    nb_faces++;
    Lf=Lf->suiv;
  }
 
  // on ouvre le fichier "tmp" dans lequel on va ecrire
  if ((fp=fopen(fichier,"w"))==NULL){
    printf("Erreur lors de l'ouverture du fichier %s\n",fichier);
    exit(1);
  } 

  tmp="OFF\n";
  fputs(tmp,fp);
  // on ecrit le nombre de points et le nombre de faces
  fprintf(fp,"%i %i 0\n",nb_points,nb_faces);
  // on inscrit les coordonnees des points et des normales (nulles)
  Ls=L_sommets;
  cpt=0;
  while (Ls!=NULL){
    S=Ls->S;
    fprintf(fp,"%f %f %f \n",S->x,S->y,S->z);
    if (S->info==NULL)
      S->info=creer_info();
    S->info->numero_affichage=cpt; 
    cpt++; 
    Ls=Ls->suiv;
  }
 
  // on inscrit les faces
  Lf=L_faces;
  while (Lf!=NULL){
    F=Lf->F;
    if (present_liste_sommet(F->S0,L_sommets)&&present_liste_sommet(F->S1,L_sommets)&&present_liste_sommet(F->S2,L_sommets))
      // on colore en rouge les faces F1 et F2.
      if (meme_face(F,F1)||meme_face(F,F2))
	  fprintf(fp,"3 %d %d %d 1.0 0.0 0.0\n",F->S0->info->numero_affichage,F->S1->info->numero_affichage,F->S2->info->numero_affichage);
      else
	// on colore en bleu les faces voisine de F1 et F2.
	if  ((meme_face(F,F1->f0)||meme_face(F,F2->f0)|| meme_face(F,F1->f1)||meme_face(F,F2->f1)|| meme_face(F,F1->f2)||meme_face(F,F2->f2))&&(!(meme_face(F,F1) || meme_face(F,F2))))
	  fprintf(fp,"3 %d %d %d 0.0 0.0 1.0\n",F->S0->info->numero_affichage,F->S1->info->numero_affichage,F->S2->info->numero_affichage);
	else
	  // on inscrit les autres faces.
	  fprintf(fp,"3 %d %d %d\n",F->S0->info->numero_affichage,F->S1->info->numero_affichage,F->S2->info->numero_affichage);
    else
      printf("erreur sommet non present dans le graphe mais present dans une face.\n");
    Lf=Lf->suiv;
  }  
 
  
  close(fp);
  return 1;
}




int sortie_COFF(char* fichier){
// procedure qui transforme le maillage represente en memoire en maillage au format "coff" pouvant etre visualises par Geomview. Ce format necessite la presence de champs "r","g","b" dans les informations associees aux points afin de pouvoir effectuer une sortie en couleur.
  int nb_points;
  int nb_faces;
  liste_sommets Ls;
  liste_faces Lf;
  char tmp_b[100];
  char * tmp;
  sommet *S;
  int cpt;
  face *F; 
int i;

  // on compte le nombre de points de la structure
  Ls=L_sommets;
  nb_points=0;
  while (Ls!=NULL){
    nb_points++;
    Ls=Ls->suiv;
  }
 
  // on compte le nombre de faces de la structure
  Lf=L_faces;
  nb_faces=0;
  while (Lf!=NULL){
    nb_faces++;
    Lf=Lf->suiv;
  }
 
  // on ouvre le fichier dans lequel on va ecrire
  if ((fp=fopen(fichier,"w"))==NULL){
    printf("Erreur lors de l'ouverture du fichier %s\n",fichier);
    exit(1);
  } 

  tmp="COFF\n";
  fputs(tmp,fp);
  // on ecrit le nombre de points et le nombre de faces
  fprintf(fp,"%i %i 0\n",nb_points,nb_faces);
  // on inscrit les coordonnees des points et des normales (nulles)
  Ls=L_sommets;
  cpt=0;
  while (Ls!=NULL){
    S=Ls->S;
    fprintf(fp,"%f %f %f %f %f %f 0.5\n",S->x,S->y,S->z,S->info->r,S->info->g,S->info->b);
    if (S->info==NULL)
      S->info=creer_info();
    S->info->numero_affichage=cpt; 
    cpt++; 
    Ls=Ls->suiv;
  }
 
  // on inscrit les faces
  Lf=L_faces;
  while (Lf!=NULL){
    F=Lf->F;
    if (present_liste_sommet(F->S0,L_sommets)&&present_liste_sommet(F->S1,L_sommets)&&present_liste_sommet(F->S2,L_sommets))
      fprintf(fp,"3 %d %d %d\n",F->S0->info->numero_affichage,F->S1->info->numero_affichage,F->S2->info->numero_affichage);
    else
      printf("erreur sommet non present dans le graphe mais present dans une face.\n");
    Lf=Lf->suiv;
  }  
  close(fp);

}

int sortie(char *fichier){
// fonction qui selon les variables globales effectue le dispatching sur les fonctions de sorties definies ci-dessus
  if (bool_sortie_OFF==0)
    if (!couleur_sommet)
      sortie_OFF(fichier);
    else
      sortie_COFF(fichier);
  else
    sortie_WRL(fichier);
}



