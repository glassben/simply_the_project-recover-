#include "listes.h"

// On definit les variables globales 
extern liste_sommets L_sommets;
extern liste_faces L_faces;
extern liste_aretes L_aretes_retirees;


int present_liste_sommet(sommet *S1, liste_sommets L){
  // recherche si le sommet S1 est present dans la liste des sommets L 
  // attention cette procedure ne prend pas en compte l'information de chaque points.
  if (L==NULL)
    return 0;
  else
    if (meme_sommet(S1,L->S))
      return 1;
    else
      return present_liste_sommet(S1,L->suiv);
}


liste_sommets  ajouter_sommet(sommet *S, liste_sommets L){
  // renvoie la liste L a laquelle on a ajouter le sommet S
  liste_sommets tmp;
  tmp=(liste_sommets) malloc(sizeof(struct liste_sommets_elem));
  tmp->S=S;
  tmp->suiv=L;
  return tmp;
}

liste_sommets supprimer_sommet(sommet *S, liste_sommets L){
  // renvoie la liste L dans laquelle on a supprime le sommet S
  liste_sommets tmp;
  liste_sommets prec;
  sommet *S0;

  if (L==NULL)
    return NULL;
  // L contient au moins un element.
  prec=NULL;
  tmp=L;
  S0=tmp->S;
  while  (!(meme_sommet(S0,S))){
   prec=tmp;
   tmp=tmp->suiv;
   if (tmp==NULL)
     break;
   S0=tmp->S;
  }
  if ( (tmp==NULL) ) 
    return L;
  if (prec !=NULL){
    prec->suiv=tmp->suiv;
    return L;
  }
  else 
      return L->suiv;
}



int present_liste_face(face *F1, liste_faces L){
// fonction qui teste si la face F1 est present dans la liste L
  if (L==NULL)
    return 0;
  else
    if (meme_face(F1,L->F))
      return 1;
    else
      return present_liste_face(F1,L->suiv);
}

liste_faces  ajouter_face(face *F, liste_faces L){
// fonction qui renvoie la liste L auquel on a rajouter la face F en tete.
  liste_faces tmp;
  tmp=(liste_faces) malloc(sizeof(struct liste_faces_elem));
  tmp->F=F;
  tmp->suiv=L;
  return tmp;
}


liste_faces supprimer_face(face *F, liste_faces L){
  // renvoie la liste L dans laquelle on a supprime A
  if (L!=NULL){
    if (meme_face(L->F,F)) 
      return L->suiv;
    else {
      L->suiv=supprimer_face(F,L->suiv);
      return L;
    }
  }
  else
    return NULL;
}




int afficher_liste_sommet(liste_sommets L){
// affiche la liste des sommets passes en parametre.
  liste_sommets LL;
  LL=L;
  while (LL!=NULL){
  printf("\t sommet en x=%g, y=%g, z=%g \n",LL->S->x,LL->S->y,LL->S->z);
  LL=LL->suiv;
  }
}

int present_liste_arete(arete *A1, liste_aretes L){
// recherche si l'arete A est presente dans la liste L
  if (L==NULL)
    return 0;
  else
    if (meme_arete(A1,L->A))
      return 1;
    else
      return present_liste_arete(A1,L->suiv);
}


liste_aretes  ajouter_arete(arete *A,face *f, liste_aretes L){
// ajoute l'arete A de la face f a la liste d'arete L
// remarque : on stocke aussi la face a laquelle est associee l'arete afin de ne pas devoir parcourir l'integralite de la liste de face quand on veut travailler sur une arete (car la structure de base de tous les algo sont les faces)
  liste_aretes tmp;
  tmp=(liste_aretes) malloc(sizeof(struct liste_aretes_elem));
  tmp->A=A;
  tmp->f=f;
  tmp->suiv=L;
  return tmp;
}


liste_aretes supprimer_arete(arete *A, liste_aretes L){
// renvoie la liste L dans laquelle on a supprime A
  if (L!=NULL){
    if (meme_arete(L->A,A)) 
      return L->suiv;
    else {
      L->suiv=supprimer_arete(A,L->suiv);
      return L;
    }
  }
  else
    return NULL;
}

int afficher_liste_arete(liste_aretes L){
// affiche la liste d'arete L
  liste_aretes LL;
  sommet *S;
  LL=L;
  while (LL!=NULL){
  printf("\t arete de sommet :\n");
  printf("\t");
  afficher_sommet(LL->A->S0);
  printf("\t");
  afficher_sommet(LL->A->S1);
  LL=LL->suiv;
  }
}




int afficher_liste_face(liste_faces L){
// procedure qui affiche la liste de face L
  liste_faces LL;
  face *F;
  LL=L;
  while (LL!=NULL){
    F=LL->F;
    afficher_face(F);    
    LL=LL->suiv;
  }
}



liste_sommets intersection_liste_sommet(liste_sommets L1,liste_sommets L2){
// procedure qui renvoie une liste de sommets intersection des listes de sommets L1 et L2
  liste_sommets LL1;
  liste_sommets LL2;
  liste_sommets L_commun;
  
  L_commun=NULL;
  LL1=L1;
  LL2=L2;
    
  while (LL2!=NULL){
    if (present_liste_sommet(LL2->S,LL1)){
      L_commun=ajouter_sommet(LL2->S,L_commun);
    }
    
    LL2=LL2->suiv;
  }

  return L_commun;
}

liste_faces intersection_liste_face(liste_faces L1,liste_faces L2,liste_faces L3){
// procedure qui renvoie une liste de faces intersection des 3 listes de faces L1, L2, L3
  liste_faces LL1;
  liste_faces LL2;
  liste_faces LL3;
  liste_faces L_commun;
  LL1=L1;
  LL2=L2;
  LL3=L3;

  while (LL1!=NULL){
    while (LL2!=NULL){
      if (meme_face(LL1->F,LL2->F)){
	L_commun=ajouter_face(LL2->F,L_commun);
	LL2=LL2->suiv;
      }
    }
    LL2=L2;
    LL1=LL1->suiv;
  }

  LL1=L1; 
  while (LL1!=NULL){
    while (LL3!=NULL){
      if (meme_face(LL1->F,LL3->F)){
	L_commun=ajouter_face(LL3->F,L_commun);
	LL3=LL3->suiv;
      }
    }
    LL3=L3;
    LL1=LL1->suiv;
  }
  return L_commun;
}













