
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



int plus_petit_sommet(sommet *S1,sommet *S2){
  // renvoie 1 si S1 et inferieur a S2 avec la topologie concideree.
  return ( (S1->x<S2->x) || ((S1->x==S2->x)&&(S1->y<S2->y)) ||  ((S1->x==S2->x)&&(S1->y==S2->y)&&(S1->z<S2->z)) );
}

int plus_petit_face(face *F1,face *F2){
  // renvoie 1 si F1 est inferieur a F2 avec la topologie concideree.
  int i0,i1,i2;// numero affichage des sommets F1
  int j0,j1,j2;// numero affichage des sommets F2

  i0=F1->S0->info->numero_affichage;
  i1=F1->S1->info->numero_affichage; 
  i2=F1->S2->info->numero_affichage;
  j0=F2->S0->info->numero_affichage;
  j1=F2->S1->info->numero_affichage;
  j2=F2->S2->info->numero_affichage;

  return ((i0<j0)||((i0==j0)&&(i1<j1))||((i0==j0)&&(i1==j1)&&(i2<j2)));
}




liste_sommets trier_liste_sommet(liste_sommets L){
  // procedure qui trie la liste des sommets de sorte a obtenir une liste de sommets dans l'ordre decroissant (relation d'ordre totale de R3)
  liste_sommets tmp;
  liste_sommets min;
  liste_sommets ls;
  liste_sommets LL;
  LL=L;
    if (LL==NULL)
    return NULL;
  // la liste comporte au moins un element.
  // on recherche le minimum de la liste 
  min=LL;
  tmp=LL->suiv;
  while (tmp!=NULL){
    if (plus_petit_sommet(tmp->S,min->S))
      min=tmp;
    tmp=tmp->suiv;  
  }
  ls=(liste_sommets) malloc(sizeof(struct liste_sommets_elem));
  ls->S=min->S;
  LL=supprimer_sommet(min->S,LL);
  ls->suiv=trier_liste_sommet(LL);
  return ls;
}


liste_faces trier_liste_face(liste_faces L){
  liste_faces tmp;
  liste_faces min;
  liste_faces lf;

  if (L==NULL)
    return NULL;
  // la liste comporte au moins un element.
  // on recherche le minimum de la liste 
  min=L;
  tmp=L->suiv;
  while (tmp!=NULL){
    if (plus_petit_face(tmp->F,min->F))
      min=tmp;
    tmp=tmp->suiv;  
  }
  lf=(liste_faces) malloc(sizeof(struct liste_faces_elem));
  lf->F=min->F;
  lf->suiv = trier_liste_face(supprimer_face(min->F,L));
  return lf;
}










int sortie_OFF_bis(char* fichier){
// procedure qui transforme le maillage represente en memoire en maillage au format ".off" pouvant etre visualises par Geomview. La difference avec la fonction sortie.off est que cette fonction met un ordre topologique sur les points et sur les faces lors de la sortie ce qui permet de comparer les fichiers par un simple "diff". Le prix a payer pour cela est une modification de l'ordre de points et des faces en memoire. Pour une plus grande securite il est donc conseiller de n'utiliser cette procedure qu'en fin d'exection de programme ou de reeffectuer une acquisition de donnees. 
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
  //fichier=(char *) nom_fichier;
  if ((fp=fopen(fichier,"w"))==NULL){
    printf("Erreur lors de l'ouverture du fichier %s\n",fichier);
    exit(1);
  } 

  tmp="OFF\n";
  fputs(tmp,fp);
  // on ecrit le nombre de points et le nombre de face
  fprintf(fp,"%i %i 0\n",nb_points,nb_faces);
  // on inscrit les coordonnees des points et des normales (nulles)
  L_sommets=trier_liste_sommet(L_sommets);
  Ls=L_sommets;
  cpt=0;
  while (Ls!=NULL){
    S=Ls->S;
    fprintf(fp,"%f %f %f \n",S->x,S->y,S->z);
    //fprintf(fp,"%f %f %f \n",(float)0,(float)0,(float)0 );
    if (S->info==NULL)
      S->info=creer_info();
    S->info->numero_affichage=cpt; 
    cpt++; 
    Ls=Ls->suiv;
  }


  // on inscrit les faces
  L_faces=trier_liste_face(L_faces);
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





