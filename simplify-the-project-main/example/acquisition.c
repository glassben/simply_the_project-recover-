

#include "acquisition.h"

FILE *fp;
// On recupere les variables globales 
extern liste_sommets L_sommets;
extern liste_faces L_faces;
extern liste_aretes L_aretes_retirees;

extern int NB_MAX_SOMMETS;
extern int NB_MAX_TRIANGLES;


float distance_max(float* M){
  liste_sommets Ls;
  liste_sommets LLs;
  float max;
  Ls=L_sommets;

  if (Ls==NULL){
    printf("erreur :Il n'y a pas de points dans la figure\n");
    exit(0);
  }
  if (Ls->suiv==NULL){
    printf("erreur :Il n'y a qu'un point dans la figure\n");
    exit(0);
  }
  LLs=Ls->suiv;
  // on a au moins deux points dans le schema.
  max=distance_au_carre(Ls->S,Ls->suiv->S);
  
  while (Ls!=NULL){
    LLs=Ls->suiv;
    while (LLs!=NULL){
       if (distance_au_carre(Ls->S,LLs->S)>max)
	max=distance_au_carre(Ls->S,LLs->S); 
      LLs=LLs->suiv;
    }
    Ls=Ls->suiv;
  }
  *M=max;
  
}


int acquisition(char *fichier,float* M){
  char tmp_b[100];
  char * tmp;
  char *ngb="NEIGHBOUR_FILE\n";
  float x,y,z;
  int i;
  int nb_points;
  int nb_triangles;
  int S0,S1,S2,F0,F1,F2,F3;
  FILE *fp2;
  // on prendra des tablleau avec 10 de plus que les constantes rentrees par l'utilisateur afinn de s'assurer qu'il ny aura pas de problemes d'indice.
  sommet * tab_sommets[NB_MAX_SOMMETS+10];
  face * tab_face[NB_MAX_TRIANGLES+10];
  int tab_voisin_face[NB_MAX_TRIANGLES+10][3];
  int tab_sommet_face[NB_MAX_TRIANGLES+10][3];
  int ind_pt_null_sommet,ind_pt_null_face;
  liste_faces tab_liste_face[NB_MAX_SOMMETS];
  face *F;
  face *f0;
  face *f1;
  face *f2;
  face *face;
  liste_faces commun,L_tmp_face;
  sommet *S;
  float MAX=0.0;


  // on initialise les variables 
  for (i=0;i<NB_MAX_SOMMETS;i++)
    tab_liste_face[i]=NULL;

  if ((fp=fopen(fichier,"r"))==NULL){
    printf("Erreur lors de l'ouverture du fichier %s\n",fichier);
    exit(1);
  } 
  // on verifie le type du fichier
  tmp=&tmp_b[1];
  // on recupere la premiere ligne du fichier
  fgets(tmp,100,fp);
  if (!strncmp(tmp,"NEIGHBOUR_FILE",14)){
    fscanf(fp,"%i\n %i\n",&nb_points,&nb_triangles);
    if (nb_points>NB_MAX_SOMMETS){
      printf("impossible d'acquerir les donnees car la variable\n");
      printf("globale NB_MAX_SOMMETS est plus petite que le nombre\n");
      printf("de sommets du maillage\n");
      exit(0);
    }
    if (nb_triangles>NB_MAX_TRIANGLES){
      printf("impossible d'acquerir les donnees car la variable\n");
      printf("globale NB_MAX_TRIANGLES est plus petite que le nombre\n");
      printf("de triangles du maillage\n");
      exit(0);
    }

    for (i=0;i<=nb_points-1;i++){
      // on lit les valeurs des points
      fscanf(fp,"\n%g\n %g\n %g\n", &x, &y, &z);
      // on cree ces points et on les entre dans le tableau
      S=creer_sommet(x,y,z,creer_info());
      tab_sommets[i]=S;
      // on l'ajoute a la liste des sommets 
      L_sommets=ajouter_sommet(S,L_sommets);
      // on lit les valeurs des normales (que ne n'utiliseront pas)
      fscanf(fp,"%f\n %f\n %f\n", &x, &y, &z);  
    }
   ind_pt_null_sommet=nb_points+2;
   tab_sommets[ind_pt_null_sommet]=NULL;
    
   ind_pt_null_face=nb_triangles+2;
   tab_face[ind_pt_null_face]=NULL;

    for (i=0;i<=nb_triangles-1;i++){
      fscanf(fp,"%i\n %i\n %i\n %i\n %i\n %i\n",&S0,&S1,&S2,&F0,&F1,&F2);
      //On creer les faces et on les entre dans le tableau des faces
      F=creer_face(tab_sommets[S0],tab_sommets[S1],tab_sommets[S2],NULL,NULL,NULL);
      tab_face[i]=F;
      L_faces=ajouter_face(F,L_faces);
      // on entre dans le tableau voisin_face les 3 faces voisines de la face f
      tab_voisin_face[i][0]=F0;
      tab_voisin_face[i][1]=F1;
      tab_voisin_face[i][2]=F2;
    }

    // si les faces voisines sont d'indice -1 c'est qu'elles sont NULL.
    for (i=0;i<=nb_triangles-1;i++){
      if (tab_voisin_face[i][0]==-1)
	tab_voisin_face[i][0]=ind_pt_null_face;
      if (tab_voisin_face[i][1]==-1)
	tab_voisin_face[i][1]=ind_pt_null_face;
      if (tab_voisin_face[i][2]==-1)
	tab_voisin_face[i][2]=ind_pt_null_face;
      chainer_face(tab_face[i],tab_face[tab_voisin_face[i][0]],tab_face[tab_voisin_face[i][1]],tab_face[tab_voisin_face[i][2]]);
    }
  }
  else
    {
      printf("type de fichier different de .ngb ou fichier non conforme a la syntaxe prevue.\n");
      fclose(fp);
      exit(0);
    }  
  fclose(fp);
  
  // On calcule desormais le carre dela plus grande distance entre 2 points
  // du schema.
  // Et on la retourne.
  distance_max(&MAX);
  *M=MAX;
}










