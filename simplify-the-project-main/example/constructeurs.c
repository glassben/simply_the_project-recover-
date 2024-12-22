// package construisant les constructeurs

#include <stdio.h>
#include "constructeurs.h"




int afficher_sommet(sommet *S){
  // procedure qui affiche les coordonnees des sommets
  if (S!=NULL){
    printf("\t sommet en x=%g, y=%g, z=%g ",S->x,S->y,S->z);
    afficher_info(S); 
    printf("\n");
  }
  else
    printf("\t Affichage d'un sommet non defini : NULL.\n");
}


int afficher_arete(arete *A){
// procedure qui affiche une arete A
  if (A!=NULL){
  printf("\t arete de sommet :\n");
  printf("\t");
  afficher_sommet(A->S0);
  printf("\t");
  afficher_sommet(A->S1);
  }
  else
    printf("\t Essai d'affichage d'une arete non definie : NULL.\n");
}




int afficher_face(face *F){
// procedure qui affiche la face F
  sommet *S;
  if (F==NULL){
    printf("\t pas de face dans cette direction (NULL)\n");
    return 0;
  }
  printf("\t les sommets de la face sont :\n");
  S=F->S0;
  if (S!=NULL)
    printf("\t\t sommet en x=%g, y=%g, z=%g \n",S->x,S->y,S->z);
  else
    printf("probleme : sommet de la face NULL.");
    
  S=F->S1;
  if (S!=NULL)
    printf("\t\t sommet en x=%g, y=%g, z=%g \n",S->x,S->y,S->z); 
  else
    printf("probleme : sommet de la face NULL.");
  
   S=F->S2;
   if (S!=NULL)
     printf("\t\t sommet en x=%g, y=%g, z=%g \n",S->x,S->y,S->z);
   else
     printf("probleme : sommet de la face NULL.");
}



face* creer_face(sommet *S1,sommet *S2,sommet *S3,face *f0,face *f1,face *f2){
// fonction qui renvoie une face ayant pour sommet S1, S2 et S3 et pour faces voisine f0, f1, f2.
 face *F;
 F=(face *) malloc(sizeof(face));
 F->S0= S1;
 F->S1= S2;
 F->S2= S3;
 F->f0= f0;
 F->f1= f1;
 F->f2= f2;
return F;
}


sommet *dupliquer_sommet(sommet *S1){
  // procedure qui renvoie un somet qui est un duplicata du sommet passe en parametre.
// cette procedure ne sera pas utilisee.
  sommet *S;
  S=(sommet *)malloc(sizeof(sommet)); 
  S->x=S1->x;
  S->y=S1->y;
  S->z=S1->z;
  S->info=S1->info;
  return S;

}


arete* creer_arete(sommet *S1,sommet *S2){
// procedure qui cree une arete de sommets S1 et S2
  arete *A;
  A=(arete *)malloc(sizeof(arete));   
  A->S0=S1;
  A->S1=S2;
  return A;
}




int meme_sommet(sommet* S1,sommet* S2){
// procedure qui test si les sommets S1 et S2 sont identiques
  return ((((float)S1->x==(float)S2->x) && ((float)S1->y==(float)S2->y)) && ((float)S1->z==(float)S2->z));
}



int meme_face(face *F1,face *F2){
  // verifie que les face F1 et F2 sont les meme en verifiant qu'elle comporte bien les memes sommets.
  int bool=0;
   if ((F1==NULL) && (F2==NULL))
     return 1;
  if ((F1==NULL) || (F2==NULL))
    return 0;
  bool = bool || ((meme_sommet(F1->S0,F2->S0))&&(meme_sommet(F1->S1,F2->S1))&&(meme_sommet(F1->S2,F2->S2)));
  bool = bool || ((meme_sommet(F1->S0,F2->S0))&&(meme_sommet(F1->S1,F2->S2))&&(meme_sommet(F1->S2,F2->S1)));
  
  bool = bool || ((meme_sommet(F1->S0,F2->S1))&&(meme_sommet(F1->S1,F2->S0))&&(meme_sommet(F1->S2,F2->S2)));
  bool = bool || ((meme_sommet(F1->S0,F2->S1))&&(meme_sommet(F1->S1,F2->S2))&&(meme_sommet(F1->S2,F2->S0)));
  
  bool = bool || ((meme_sommet(F1->S0,F2->S2))&&(meme_sommet(F1->S1,F2->S0))&&(meme_sommet(F1->S2,F2->S1)));
  bool = bool || ((meme_sommet(F1->S0,F2->S2))&&(meme_sommet(F1->S1,F2->S1))&&(meme_sommet(F1->S2,F2->S0)));
  return bool;
}



int meme_arete(arete *A1,arete *A2){
// procedure qui compare deux aretes
  return ((meme_sommet(A1->S0,A2->S0)&&meme_sommet(A1->S1,A2->S1))||(meme_sommet(A1->S1,A2->S0)&&meme_sommet(A1->S1,A2->S0)));
}


int indice_sommet_face(sommet *S,face *F){
  // fonction qui renvoie l'indice du sommet S dans le face F
  if (meme_sommet(S,F->S0))
    return 0;
  if (meme_sommet(S,F->S1))
    return 1;
  if (meme_sommet(S,F->S2))
    return 2;
  return -1;
}


int changer_sommet(face *F,sommet *S1,sommet *S){
  // procedure qui remplace le sommet de la face F qui correspond a S1 par le pointeur vers le sommet S
  // Remarque : avec le codage prevu, cette procedure ne doit pas faire plus d'un remplacement
  // par appel. On y veillera et on renverra une erreur sinon.
  int nb_chang=0;
  int bool;
  face *tmp_f;
  if (F==NULL)
    return 0;
  if (meme_sommet(F->S0,S1))
    nb_chang++;
  
  if (meme_sommet(F->S1,S1))
    nb_chang++;
  
  if (meme_sommet(F->S2,S1))
    nb_chang++;
  
  if (nb_chang>1){
    printf("erreur dans changer_sommet : echange de plus de deux sommets dans la meme face.\n");
    exit(0);
  }
  else{
    if (meme_sommet(F->S0,S1))
      F->S0=S;
    if (meme_sommet(F->S1,S1))
      F->S1=S;
    if (meme_sommet(F->S2,S1))
      F->S2=S;
  } 
  if (nb_chang==0)
    printf("pas de changement \n");
}



int changer_face_vs(face *F , face *F1, face *F2,sommet *S,sommet *S1,sommet *S2){
// procedure appelee lors du vertex split et qui gere le chainage des faces dans le cas ou l'une des deux faces a inserer est a inserer a cote d'une face NULL.
  int res;
  int ind_S;
  int ind_S1,ind_S2;
  sommet *S3;
  int ind_S3=-1;
  int ind_chainage;
  int ind_F;
  int ind_sommet_commun;
  res=changer_face(F,F1,F2);
  if (res==1)
    // tout c'est bien passe.
    return 1;
  // on est pas parvenu a faire changer le chainage des faces car F1=NULL.
  // On a 2 cas possibles : F a une face NULL ou F a 2 faces NULL
  // on va donc utiliser les points du schema pour determiner comment il faut chainer les faces. 
  // on sait que le sommet S est le sommet de F2 qui n'est ni S1 ni S2, tout deux sommets de F1.
  // on recherche les indices de ces sommets
  ind_S=indice_sommet_face(S,F);
  // on determine le 3ieme sommet du triangle F2 
  ind_S1=indice_sommet_face(S1,F2);
  ind_S2=indice_sommet_face(S2,F2);

  if (((ind_S1==0)&&(ind_S2==1))||((ind_S1==1)&&(ind_S2==0)))
    ind_S3=2;
  if (((ind_S1==1)&&(ind_S2==2))||((ind_S1==2)&&(ind_S2==1)))
    ind_S3=0;
  if (((ind_S1==2)&&(ind_S2==0))||((ind_S1==0)&&(ind_S2==2)))
    ind_S3=1;
  S3=sommet_numero(ind_S3,F2);
  // ce troisieme sommet appartient necessairement a F sinon l'insertion serait impossible.
  // on cherche l'indice de ce sommet dans F
  ind_S3=indice_sommet_face(S3,F);
  if ((ind_S3<0)||(ind_S3>2)){
    printf("erreur changer_face_vs : ind_S3 != 0, 1 ou 2\n");
    exit(0);
  }
  // on peut desormais determiner l'endroit auquel il faut chainer F2 a F.
  if (((ind_S==0)&&(ind_S3==1))||((ind_S==1)&&(ind_S3==0)))
    ind_chainage=2;
  if (((ind_S==1)&&(ind_S3==2))||((ind_S==2)&&(ind_S3==1)))
    ind_chainage=0;
  if (((ind_S==2)&&(ind_S3==0))||((ind_S==0)&&(ind_S3==2)))
    ind_chainage=1;
  // reste a chainer les face a l'endroit voulu.
  changer_face_numero(F,ind_chainage,F2);
  return 1;
}


int changer_face(face *Face , face *Face1, face *Face2){
  // procedure qui change le pointeur de la face F pointant vers la face F1 par le pointeur
  // pointant vers la face F2
  // cette procedure n'est sense effectue qu'un echange par appel.
  int nb_chang=0;
  int n;
  face tmp;

  if (Face==NULL){
    printf("erreur changer_face : Face NULL\n");
    exit(0);
  }

  if (Face->f0 != NULL)
    if (meme_face(Face->f0,Face1)){
      nb_chang++;
      Face->f0=Face2;
    }


  if (Face->f1 != NULL)
    if (meme_face(Face->f1,Face1)){
      nb_chang++;
      Face->f1=Face2;
    }
  
  if (Face->f2 != NULL)
    if (meme_face(Face->f2,Face1)){
      nb_chang++;
      Face->f2=Face2;
    }
  
  if (Face1==NULL){
    // on doit alors recherche a quelle place il nous faut chainer cette nouvelle face
    //    printf("il est la le pb mais seulement avec un passage venant de Vertix_split cf pas de somets commums, on va traiter se probleme dans la fin de changer_face_vs\n");
      return -1;
      // on a un appel depuis vertex split
  }
  
  if (nb_chang>1){
    printf("erreur changer_face : echange de plus de deux faces\n");
    exit(0);
  }
  if (nb_chang==0){
    printf("on effectue 0 changement dans la procedure changer face \n");
    return -1;
  }
  return 1;
}


int remplacer(sommet *S1,sommet *S2){
// procedure qui remplace le sommet S1 par le sommet S2 en dur
// cette procedure ne sera pas utilisee.
  S1->x= S2->x;
  S1->y= S2->y;
  S1->z= S2->z;  
  S1->info= S2->info;  
}


int mod(int x, int y){
  // retourne x mod y (resultat positif)
  if ((x % y)>=0)
    return (x % y); 
  else
    return y+(x % y); 
}


face* face_numero(int n, face *F){
// renvoie la face numero n de F. n est soit 0 soit 1 soit 2.
  if (n==0)
    return F->f0;
  if (n==1)
    return F->f1;
  if (n==2)
    return F->f2;
}

sommet * sommet_numero(int n, face *F){
// renvoie le sommet numero n de la face F
  if (n==0)
    return F->S0;
  if (n==1)
    return F->S1;
  if (n==2)
    return F->S2;
  printf("erreur sommmet_numero : n doit etre 0, 1 ou 2\n");
  exit(0);
}



int changer_face_numero(face *F,int n, face *Face){
  // change la face numero n de F par la face Face. n doit etre soit 0 soit 1 soit 2.
  if ((n>2)||(n<0)){
    printf("erreur de passage de parametres dans la fonction changer_face_numero : n!=0,1,2\n");
    return -1;
  }
  if (F==NULL){
    printf("erreur de passage de parametres dans la fonction changer_face_numero : F=NULL\n");
    return -1;
  }
  if (n==0)
    F->f0=Face;
  if (n==1)
    F->f1=Face;
  if (n==2)
    F->f2=Face;
  return 2;
}

int appartient_a_la_face(sommet *S,face *f){
  // renvoie 1 si le sommet S appartient a la face F. Renvoie 0 sinon.
  if (S==NULL)
    return 0;
  if (meme_sommet(S,f->S0))
    return 1;
  if (meme_sommet(S,f->S1))
    return 1;
  if (meme_sommet(S,f->S2)) 
    return 1;
  return 0;
}

int numero_sommet_non_commun_face(face *f1,face * f2){
  // procedure qui renvoie le numero du sommet de la face f1 qui n'appartient pas a la face f2
  // on verifiera que ces 2 faces ont bien 2 sommets en communs (qu'elles ont un arete en commun)
  // elle renverra 3 si f2==NULL
  sommet *S0;
  sommet *S1;  
  sommet *S2;
  int commun_0;
  int commun_1;
  int commun_2;

  if (f1==NULL){
    printf("erreur numero_sommet_non_commun_face : f1 = NULL\n");
    return -1;
  }
  if (f2==NULL){
    return 3;
  }
  S0=f1->S0;
  S1=f1->S1;  
  S2=f1->S2;

  commun_0=appartient_a_la_face(S0,f2);
  commun_1=appartient_a_la_face(S1,f2);
  commun_2=appartient_a_la_face(S2,f2);
  if (commun_0+ commun_1+ commun_2!=2){
     printf("erreur numero_sommet_non_commun_face : faces f1 et f2 non adjacentes\n");
     afficher_face(f1);
     afficher_face(f2);
    return -1;
  }
  if (!commun_0)
    return 0;
  if (!commun_1)
    return 1;
  if (!commun_2)
    return 2;  
}

int a_2sommets_communs(face *f1,face *f2){
  // procedure qui renvoie 1 si les deux faces ont 2 sommets commun et 0 sinon.
  sommet *S0;
  sommet *S1;  
  sommet *S2;
  int commun_0;
  int commun_1;
  int commun_2;

  if (f1==NULL){
    return 0;
  }
  if (f2==NULL){
    return 0;
  }
  S0=f1->S0;
  S1=f1->S1;
  S2=f1->S2;
 
  commun_0=appartient_a_la_face(S0,f2);
  commun_1=appartient_a_la_face(S1,f2);
  commun_2=appartient_a_la_face(S2,f2);
  if (commun_0+ commun_1+ commun_2==2){
   return 1;
  }
  return 0;

}



int a_2sommets_communs_bis(face *f1,face *f2,sommet *Sommet1,sommet *Sommet2){
  // procedure qui renvoie 1 si les deux faces ont 2 sommets differents de S1 et de S2 commun et 0 sinon.
  sommet *S0;
  sommet *S1;  
  sommet *S2;
  int commun_0;
  int commun_1;
  int commun_2;

  if (f1==NULL){
    return 0;
  }
  if (f2==NULL){
    return 0;
  }
  S0=f1->S0;
  S1=f1->S1;
  S2=f1->S2;
  if (meme_sommet(S0,Sommet1)||meme_sommet(S0,Sommet2))
    S0=NULL;
  if (meme_sommet(S1,Sommet1)||meme_sommet(S1,Sommet2))
    S1=NULL;
  if (meme_sommet(S2,Sommet1)||meme_sommet(S2,Sommet2))
    S2=NULL;
  commun_0=appartient_a_la_face(S0,f2);
  commun_1=appartient_a_la_face(S1,f2);
  commun_2=appartient_a_la_face(S2,f2);
  if (commun_0+ commun_1+ commun_2==2){
   return 1;
  }
  return 0;

}

int chainer_face(face *f,face *f1,face *f2,face *f3){
  // procedure qui chaine les faces f1,f2,f3 a la face f en respectant les regles topologiques
  int  n_sommet1;
  int  n_sommet2;
  int  n_sommet3;
  
  f->f0=NULL;
  f->f1=NULL;
  f->f2=NULL;

  n_sommet1 = numero_sommet_non_commun_face(f,f1);
  n_sommet2 = numero_sommet_non_commun_face(f,f2);
  n_sommet3 = numero_sommet_non_commun_face(f,f3);
  
  if ((n_sommet1==-1)||(n_sommet2==-1)||(n_sommet3==-1)){
    printf("erreur chainer_face :  faces non adjacentes passees en argument.\n");
    return 0;
  }
  if (n_sommet1!=3)
    changer_face_numero(f,n_sommet1, f1);
  if (n_sommet2!=3)
    changer_face_numero(f,n_sommet2, f2);
  if (n_sommet3!=3)
    changer_face_numero(f,n_sommet3, f3);
}


int affichage_face_voisin(face *F,int num_face){
// procedure qui affiche la face F et les faces qui lui sont voisines. Cette procedure est utilisee lors du debogage.
  printf("face %d\n",num_face);
  afficher_face(F);
  if (F!=NULL){
    printf("\t voisins de face %d\n",num_face);  
    afficher_face(F->f0);
    afficher_face(F->f1);
    afficher_face(F->f2);
  }
}





int nb_voisins_NULL(face *F){
// fonction qui renvoie le nombre de voisin de la face F a NULL.
  int cpt=0;
  if (F->f0==NULL)
    cpt ++;
  if (F->f2==NULL)
    cpt ++;
  if (F->f1==NULL)
    cpt ++;
  return cpt;
}



float distance_au_carre(sommet *S1,sommet *S2){
// procedure qui renvoie le carre de la distance entre S1 et S2.
  return (S1->x-S2->x)*(S1->x-S2->x)+(S1->y-S2->y)*(S1->y-S2->y)+(S1->z-S2->z)*(S1->z-S2->z);

}

























