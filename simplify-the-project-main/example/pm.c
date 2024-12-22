// Algorithme de compression et de decompression d'aretes.


#ifndef PM_H
#include "pm.h"

// On recupere les variables globales 
extern liste_sommets L_sommets;
extern liste_faces L_faces;
extern liste_aretes L_aretes_retirees;


int  init(){
  L_sommets=NULL;
  L_faces=NULL;
  L_aretes_retirees=NULL;
}


int test(int i){
  // procedure qui teste si l'on insere pas de chainage reccursif lors de edge collapse et de vertex split.
  // cette procedure est utilise lors de phases de debogage.
  if (!chainage_non_reccursif()){
    printf(" un chainage recursif introduit en %d\n",i);
    return 1;
       }
  return 0;
}



liste_sommets  tourner_et_empiler_sommet(sommet *S,face *F){
  // procedure sequentielle qui tourne autour du sommet S de la face F et renvoie une liste de sommets contenant les sommets voisins de S.
  // precondition : F n'est pas NULL.
  int droite;
  int gauche;
  int numero_sommet;
  face *Fg;
  face *Fd;
  int j=0;
  liste_sommets L;

  L=NULL;

  if (F==NULL){
    printf("erreur tourner_et_empiler_sommet\n");
    exit(0);
  }
  numero_sommet=indice_sommet_face(S,F);
  droite=mod((numero_sommet-1),3);
  // la face situee a droite de la face F par rapport au sommet S est la face numero "droite" dans le chainage des faces conciderees.
  // on passe a la face de droite 
  Fd=face_numero(droite,F);

  while (Fd!=NULL){
    if (meme_face(Fd,F))
      break;
    {    
      // on calcule l'indice de la face a droite de Fd par rapport au sommet S
      numero_sommet=indice_sommet_face(S,Fd); 
      droite=mod((numero_sommet-1),3);

      // on empile les sommets si necessaire
      if (!(present_liste_sommet(Fd->S0,L)))
	L=ajouter_sommet(Fd->S0,L);
      if (!(present_liste_sommet(Fd->S1,L)))
	L=ajouter_sommet(Fd->S1,L);
      if (!(present_liste_sommet(Fd->S2,L)))
	L=ajouter_sommet(Fd->S2,L);

      // on passe a la face droite 
      Fd=face_numero(droite,Fd);
    }
  }
  
   if (Fd==NULL){
     // on a rencontrer un pointeur NULL lors de la rotation vers la droite
     // alors on a atteint un bord => on recommence a tourner vers la gauche.
    numero_sommet=indice_sommet_face(S,F);
    gauche=mod((numero_sommet+1),3);
    // on passe a la face gauche de F
    Fg=face_numero(gauche,F);
    while (Fg!=NULL){
      if (meme_face(Fg,F))
	break;
      // on calcule l'indice de la face a gauche de Fg par rapport au sommet S
      numero_sommet=indice_sommet_face(S,Fg); 
      gauche=mod((numero_sommet+1),3); 
      
      // on empile les sommets si necessaire
      if (!(present_liste_sommet(Fg->S0,L)))
	L=ajouter_sommet(Fg->S0,L);
      if (!(present_liste_sommet(Fg->S1,L)))
	L=ajouter_sommet(Fg->S1,L);
      if (!(present_liste_sommet(Fg->S2,L)))
	L=ajouter_sommet(Fg->S2,L);
      
      // on passe a la face gauche
      Fg=face_numero(gauche,Fg);
      // on arrive necessairement a NULL lors de cette rotation vers la gauche car il y a un pointeur a NULL lors de la rotation vers la droite.
      }
   }
   return L;
}



int autorisation_collapse(face *F1,face *F2){
  // renvoie 1 si il est possible de collapser les face F1 et F2 et 0 sinon.
  int debug=0;
  face *F1_tmp_1;
  face *F1_tmp_2;
  face *F2_tmp_1;
  face *F2_tmp_2; 
  sommet *S1;
  sommet *S2;
  int bool;
  int sommet_non_commun;
  int ptr_null;
  int ptr_null_2;
  sommet *S;
  int config;
  int cpt;
  
  if ((F1==NULL)||(F2==NULL)){
    if (debug)
      printf("arete de bord \n");
    if (!autorisation_de_collapser_les_aretes_de_bord) 
      return 0;
    if (F2==NULL)
      if (F1==NULL)
	return 0;
      else
	{// on verifie que F1 n'a qu'un voisin null
	  //On recherche les sommets de l'arete sur laquelle on a effectue l'appel et on verifiez que la face n'a qu'un voisin NULL
	  cpt=0;
	  if (F1->f0==NULL){
	    cpt++;
	  S1=F1->S1;
	  S2=F1->S2;
	  }
	  if (F1->f1==NULL){
	    cpt++;
	  S1=F1->S2;
	  S2=F1->S0;
	  }
	  if (F1->f2==NULL){
	    cpt++;
	    S1=F1->S0;
	    S2=F1->S1;
	  }
	  if (cpt!=1)
	    return 0;
	  // sinon on est sur une arete de bord que l'on peux collapser
	  // sous certaines condition.
	  // on recherche les deux faces adjacentes a F1 et differentes de F2=NULL
	  F1_tmp_1=F1->f0;
	  if (F1_tmp_1==NULL){
	    F1_tmp_1=F1->f1;
	    F1_tmp_2=F1->f2; 
	  } 
	  else {
	    F1_tmp_2=F1->f1;
	    if (F1_tmp_2=NULL)
	      F1_tmp_2=F1->f2;
	  }
	  affichage_face_voisin(F1,1);
	  bool= a_2sommets_communs_bis(F1_tmp_1,F1_tmp_2,S1,S2) ;
	  return ((!bool));
	}
    else
      // on a alors (F1==NULL)
      {// on verifie que F2 n'a qu'un voisin null
	cpt=0;
	if (F2->f0==NULL){
	  cpt++;
	  S1=F2->S1;
	  S2=F2->S2;
	}
	if (F2->f1==NULL){
	  cpt++;
	  S1=F2->S2;
	  S2=F2->S0;
	}
	if (F2->f2==NULL){
	  cpt++;
	  S1=F2->S0;
	  S2=F2->S1;
	}
	if (cpt!=1)
	  return 0;

	// sinon on est sur une arete de bord que l'on peux collapser.
	// sous certaines condition
	// on recherche les deux faces adjacentes a F2 et differentes de F1=NULL
	F2_tmp_1=F2->f0;
	if (F2_tmp_1==F1){
	  F2_tmp_1=F2->f1;
	  F2_tmp_2=F2->f2; 
	} 
	else {
	  F2_tmp_2=F2->f1;
	  if (F2_tmp_2==F1)
	    F2_tmp_2=F2->f2;
	}
	bool= a_2sommets_communs(F2_tmp_1,F2_tmp_2);
	return ((!bool));
      }
    
  }


  //**************************************************************//
  // F1 et F2 ne sont pas NULL
  // on recherche les sommets communs a ces deux faces
  S1=sommet_numero(mod(numero_sommet_non_commun_face(F1,F2)+1,3),F1);
  S2=sommet_numero(mod(numero_sommet_non_commun_face(F1,F2)+2,3),F1);

  // on recherche les deux faces adjacentes a F1 et differentes de F2
  F1_tmp_1=F1->f0;
  if (meme_face(F1_tmp_1,F2)){
    F1_tmp_1=F1->f1;
    F1_tmp_2=F1->f2; 
  } 
  else {
    F1_tmp_2=F1->f1;
    if (meme_face(F1_tmp_2,F2))
      F1_tmp_2=F1->f2;
  }
  // on recherche les deux faces adjacentes a F2 et differentes de F1
  F2_tmp_1=F2->f0;
  if (meme_face(F2_tmp_1,F1)){
    F2_tmp_1=F2->f1;
    F2_tmp_2=F2->f2; 
  } 
  else {
    F2_tmp_2=F2->f1;
    if (meme_face(F2_tmp_2,F1))
      F2_tmp_2=F2->f2;
  }

  // on effectue le test afin de savoir si l'on a un sommet d'ordre 3.
  bool= a_2sommets_communs_bis(F1_tmp_1,F1_tmp_2,S1,S2);
  bool=bool || a_2sommets_communs_bis(F2_tmp_1,F2_tmp_2,S1,S2);
  
  // on teste desormais si on a moins de 2 pointeurs NULL dans les faces autour de  S1 et S2 sommets communs a F1 et F2
  sommet_non_commun=numero_sommet_non_commun_face(F1,F2);
  S=sommet_numero(mod(sommet_non_commun+1,3),F1);
  ptr_null=tourner_et_compter(S,F1);
  S=sommet_numero(mod(sommet_non_commun+2,3),F1);
  ptr_null=ptr_null+tourner_et_compter(S,F1);

  // on teste desormais si on a pas une configuration spatiale qui pose probleme.
  config=autorisation_configuration_spatiale(F1,F2);

  return ((!(bool)) && (ptr_null<3) && (config));
} 


int autorisation_configuration_spatiale(face *F1,face *F2){
  // procedure qui test si l'on est dans une configuration spatial propice a effectuer un collapse de l'arete entre F1 et F2 ou non.
  liste_sommets L1;
  liste_sommets L2;
  int  sommet_non_comm;
  sommet *S1;
  sommet *S2;
  sommet *S;
  face *f;
  int bool;

  if (F2!=NULL){
    sommet_non_comm=numero_sommet_non_commun_face(F1,F2);
    S1=sommet_numero(mod(sommet_non_comm+1,3),F1);
    S2=sommet_numero(mod(sommet_non_comm+2,3),F1);
  }
  else{
    //alors on a F2==NULL
    if (F1->f0==NULL){
      S1=F1->S1;
      S2=F1->S2;
    }
      if (F1->f1==NULL){
      S1=F1->S2;
      S2=F1->S0;
    }
    if (F1->f2==NULL){
      S1=F1->S0;
      S2=F1->S1;
    }    
  }
    
  L1=tourner_et_empiler_sommet(S1,F1);
  // On supprime de la liste les sommets de F1 et F2 si ils y sont present.
  L1=supprimer_sommet(F1->S0,L1);
  L1=supprimer_sommet(F1->S1,L1);
  L1=supprimer_sommet(F1->S2,L1);
  L1=supprimer_sommet(F2->S0,L1); 
  L1=supprimer_sommet(F2->S1,L1);
  L1=supprimer_sommet(F2->S2,L1);
  
  
   
  L2=tourner_et_empiler_sommet(S2,F1);
 
  // On supprime de la liste les sommets de F1 et F2 si ils y sont present.
  L2=supprimer_sommet(F1->S0,L2);
  L2=supprimer_sommet(F1->S1,L2);
  L2=supprimer_sommet(F1->S2,L2);
  L2=supprimer_sommet(F2->S0,L2);
  L2=supprimer_sommet(F2->S1,L2);
  L2=supprimer_sommet(F2->S2,L2);
  
  L1=intersection_liste_sommet(L1,L2);

  if (L1!=NULL)
    return 0;
  
  return 1;
}





int tourner_et_compter(sommet *S,face *F){
  // procedure sequentielle qui tourne autour du sommet S de la face F et renvoie le nombre de pointeur NULL rencontres lors de la rotation.
  // precondition : F n'est pas NULL
  int droite;
  int gauche;
  int numero_sommet;
  face *Fg;
  face *Fd;
  int j=0;
  int cpt=0;// variable stockant le nb de pointeurs NULL rencontre lors de la rotation
  
  if (F==NULL){
    printf("erreur\n");
    exit(0);
  }
  numero_sommet=indice_sommet_face(S,F);
  droite=mod((numero_sommet-1),3);
  // on passe a la face de droite 
  Fd=face_numero(droite,F);

  while (Fd!=NULL){
    //  on tourne jusqu'a ce que l'on tombe sur un pointeur NULL ou que l'on revienne sur la face de depart
    if (meme_face(Fd,F))
      break;
    {
      numero_sommet=indice_sommet_face(S,Fd); 
      droite=mod((numero_sommet-1),3);
      Fd=face_numero(droite,Fd);
    }
  }
  
   if (Fd==NULL){
     // on a rencontrer un pointeur NULL lors de la rotation vers la droite
     cpt++;
     // alors on a atteint un bord => on rencontrera aussi un pointeur NULL en tournant vers la gauche
   }
   return 2*cpt;
}










int tourner_autour_sommet_et_changer_sommet(sommet *S,face *F,sommet *S1){
  // procedure sequentielle qui tourne autour d'un sommet S appartenant a une face F
  // cette procedure change les pointeurs du sommet S des faces qu'elle parcours par le pointeur vers S1
  // on part du principe que le maillage est bien construit.
  int droite;
  int gauche;
  int numero_sommet;
  face *Fg;
  face *Fd;
  int j=0;
  

  numero_sommet=indice_sommet_face(S,F);
  droite=mod((numero_sommet-1),3);
  // on passe a la face de droite 
  Fd=face_numero(droite,F);

  while (Fd!=NULL){
    if (meme_face(Fd,F))
      break;
    {
      // on calcule l'indice de la face a droite du sommet S.
      numero_sommet=indice_sommet_face(S,Fd); 
      droite=mod((numero_sommet-1),3);
      // on change le sommet
      changer_sommet(Fd,S,S1);
      // on passe a la face droite 
      Fd=face_numero(droite,Fd);
    }
  }
 

  if (Fd==NULL){
    //printf("on part a gauche dans la rotation de edge collapse.\n");
    // alors on a atteint un bord => on recommence a tourner vers la gauche.
    // on calcule l'indice de la face de F a gauche du sommet S
    numero_sommet=indice_sommet_face(S,F);
    gauche=mod((numero_sommet+1),3);
    // on passe a la face gauche de F
    Fg=face_numero(gauche,F);
    while (Fg!=NULL){
      if (meme_face(Fg,F))
	break;
      // on calcule l'indice de la face de Fg a gauche du sommet S
      numero_sommet=indice_sommet_face(S,Fg); 
      gauche=mod((numero_sommet+1),3); 
      // on change le sommet
      changer_sommet(Fg,S,S1);
      // on passe a la face gauche
      Fg=face_numero(gauche,Fg);
      }
    }
  // on change le sommet de F
  changer_sommet(F,S,S1);
  return 1;
}

sommet*  edge_collapse_prog(face* F1,face* F2,sommet* S1,sommet* S2){
  // fonction qui realise la compression de l'arrete entre les sommets S1 et S2,
  // en faisant disparaitre du maillage les faces F1 et F2 
  // puis en rajoutant a la liste L des arretes deja retirees l'arrete (S1,S2)
  // cette fonction retourne le nouveau sommet du maillage
  // attention l'ordre de passage des parametres doit etre l'ordre trigonometrique.
  // Cette fonction renvoie le sommet issu de la compression de l'arete collapsee.
  int debug=0; // sert a lancer la procedure Test de verification d'integrite du maillage au cours de la transformation.
  int numero_face;
  sommet *S;
  arete *A;
  face *F1_tmp_1;
  face *F1_tmp_2;
  face *F2_tmp_1;
  face *F2_tmp_2;

  if (F1==NULL){
    printf("erreur : premier parametre de edge_collapse incompatible =NULL\n");
    exit(0);
  }
  
  if (F2==NULL){
    printf("erreur : deuxieme parametre de edge_collapse incompatible =NULL\n");
    exit(0);
  }

  // on creer un nouveau sommet fusion des sommets S1 et S2 grace a la procedure sommet_fusion.
  S=sommet_fusion(S1,S2);
  L_sommets=ajouter_sommet(S,L_sommets);
  // ce sommet remplacera les sommets S1 et S2
  // il faut alors tourner autour du point S1 et S2 pour mettre a jours les sommet c'est a dire remplacer S1 et S2 par S
  // on commence la compression par mettre a jours les pointeurs vers les sommets S1 et S2
  tourner_autour_sommet_et_changer_sommet(S1,F1,S);

  // on redefini les sommets de la face F1 et F2 qui ont ete modifie lors de la commande precedente
  changer_sommet(F1,S,S1);
  changer_sommet(F2,S,S1);

  tourner_autour_sommet_et_changer_sommet(S2,F2,S);
  // on redefini les sommets de la face F1 et F2 qui ont ete modifie lors de la commande precedente
  changer_sommet(F1,S,S2);
  changer_sommet(F2,S,S2);
  // on a alors supprime S1 et S2 au profit de S dans le maillage

  
  // on stocke les sommets dans un enregistrement arete retiree ansi qui la face F1
  A=creer_arete(S1,S2);
  L_aretes_retirees=ajouter_arete(A,F2,L_aretes_retirees);

  // reste a supprimer S1 et S2 de la liste des sommets et ajouter S a la liste des sommets.
  L_sommets=supprimer_sommet(S1,L_sommets);
  L_sommets=supprimer_sommet(S2,L_sommets);
  
  // on met a jours les pointeurs sur les faces.
  // on recherche les deux faces adjacentes a F1 et differentes de F2
  F1_tmp_1=F1->f0;
  if (meme_face(F1_tmp_1,F2)){
    F1_tmp_1=F1->f1;
    F1_tmp_2=F1->f2; 
  } 
  else 
    {
      F1_tmp_2=F1->f1;
      if (meme_face(F1_tmp_2,F2))
	F1_tmp_2=F1->f2;
    }

  // on recherche les deux faces adjacentes a F2 et differentes de F1
  F2_tmp_1=F2->f0;
  if (meme_face(F2_tmp_1,F1)){
    F2_tmp_1=F2->f1;
    F2_tmp_2=F2->f2; 
  } 
  else 
    {
      F2_tmp_2=F2->f1;
      if (meme_face(F2_tmp_2,F1))
	F2_tmp_2=F2->f2;
    }

  // on continue la compression par la mise a jours des faces
  if (F1_tmp_1!=NULL)
    changer_face(F1_tmp_1,F1,F1_tmp_2);
  if (F1_tmp_2!=NULL)
    changer_face(F1_tmp_2,F1,F1_tmp_1);
  
  if (F2_tmp_1!=NULL)
    changer_face(F2_tmp_1,F2,F2_tmp_2);
  if (F2_tmp_2!=NULL)
    changer_face(F2_tmp_2,F2,F2_tmp_1);
 
  // on supprime les deux faces de la liste des faces 
  L_faces=supprimer_face(F1,L_faces);
  L_faces=supprimer_face(F2,L_faces); 
  return S;
}





sommet * edge_collapse_bord(face *F){
// procedure qui effectue le collapse de l'are de la face F qui n'a pas de voisin. Attention on ne peux lui passer que des face ayant un seul voisin non NULL. Cette fonction renvoie le sommet issu de la compression de l'arete collapsee.
  int debug=0;
  int numero_face;
  sommet *S1;
  sommet *S2;
  sommet *S;
  arete *A;
  face *F_tmp_1;
  face *F_tmp_2;

  if (debug)
    printf("debut edge_collapse_bord\n");

  if (F==NULL){
    printf("erreur de parametre dans edge_collapse_bord : F=NULL\n");
    exit(0);
  }
    
  if (F->f0==NULL)
     numero_face=0;
  if (F->f1==NULL)
     numero_face=1;
  if (F->f2==NULL)
     numero_face=2;
  
  if (numero_face == 0){
    S1=F->S1;
    S2=F->S2;
  }
  if (numero_face == 1){
    S1=F->S2;
    S2=F->S0;
  }
  if (numero_face == 2){
    S1=F->S0;
    S2=F->S1;
  }

  // on creer un nouveau sommet fusion des sommets S1 et S2 a l'aide de la procedure sommet_fusion.
  S=sommet_fusion(S1,S2);
  L_sommets=ajouter_sommet(S,L_sommets);
  // ce sommet remplacera les sommets S1 et S2

  // il faut alors tourner autour du point S1 et S2 pour mettre a jours les sommets c'est a dire remplacer S1 et S2 par S
  // on commence la compression par mettre a jours les pointeurs vers les sommets S1 et S2
  tourner_autour_sommet_et_changer_sommet(S1,F,S);
  // on redefini le sommet de la face F qui a ete modifie lors de la commande precedente
  changer_sommet(F,S,S1);
  tourner_autour_sommet_et_changer_sommet(S2,F,S);
  // on redefini les sommets de la face F qui a ete modifie lors de la commande precedente
  changer_sommet(F,S,S2);
  // on a alors mis a jours les points des faces 
  // c'est a dire que l'on a supprimer S1 et S2 au profit de S dans le maillage
  
  
  // on stocke les sommets dans un enregistrement arete retiree ansi qui la face F1
  A=creer_arete(S1,S2);
  L_aretes_retirees=ajouter_arete(A,F,L_aretes_retirees);

  // reste a supprimer S1 et S2 de la liste des sommets et ajouter S a la liste des sommets.
  L_sommets=supprimer_sommet(S1,L_sommets);
  L_sommets=supprimer_sommet(S2,L_sommets);

  // on met a jours les pointeurs sur les faces.

  // on recherche les deux faces non NULL adjacentes a F
  F_tmp_1=F->f0;
  if (F_tmp_1==NULL){
    F_tmp_1=F->f1;
    F_tmp_2=F->f2; 
  } 
  else 
    {
      F_tmp_2=F->f1;
      if (F_tmp_2==NULL)
	F_tmp_2=F->f2;
    }

  // on continue la compression par la mise a jours des pointeurs des faces
  changer_face(F_tmp_1,F,F_tmp_2);
  changer_face(F_tmp_2,F,F_tmp_1);
  

  // on supprime la face retiree de la liste des faces du maillage. 
  L_faces=supprimer_face(F,L_faces);

  return S;
}

  


sommet*  edge_collapse(face* F1,face* F2){
  // procedure de dispatching entre edge_collapse_prog et edge_collapse_bord
  sommet * S_non_commun_F1_F2;
  sommet *S;
  

  if ((F1==NULL)||(F2==NULL)){
    if (F2!=NULL)
        S=edge_collapse_bord(F2);
    if (F1!=NULL)
        S=edge_collapse_bord(F1);
    return NULL;
  }
  else{
    //  printf("recherche du sommet commun aux deux faces\n");
    S_non_commun_F1_F2=sommet_numero(numero_sommet_non_commun_face(F1,F2),F1);
    if (meme_sommet(S_non_commun_F1_F2,F1->S0))
      S=edge_collapse_prog(F1,F2,F1->S1,F1->S2);
    else 
      if (meme_sommet(S_non_commun_F1_F2,F1->S1))
	S=edge_collapse_prog(F1,F2,F1->S0,F1->S2);
      else 
	if (meme_sommet(S_non_commun_F1_F2,F1->S2))
	  S=edge_collapse_prog(F1,F2,F1->S0,F1->S1);
	else
	  printf("erreur : on entre pas dans une des deux procedures de coollapse.\n");
  }
  return S;
}






int vertex_split(sommet *S){
  // procedure qui effectue l'inverse de edge collapse :
  // Elle re-introduit les deux faces supprimees lors du remplacement de deux sommets par S via la procedure Edge_collapse;
  int debug=0; // sert a lancer la procedure Test de verification d'integrite du maillage au cours de la transformation.
  liste_aretes La;
  sommet *S1;
  sommet *S2;
  sommet *S1_tmp;
  sommet *S2_tmp;
  face *F1;
  face *F2;
  int ind_S1,ind_S2;
  int  ind_sommet_F1;// indice du 3ieme sommet de la face F1
  int  ind_sommet_F2;// indice du 3ieme sommet de la face F2 si celle ci n'est pas null
  face *F1_tmp_1;
  face *F1_tmp_2;
  face *F2_tmp_1;
  face *F2_tmp_2;
  int ind_face_rot;// indice de la face vers laquelle va commencer la rotation
  int droite,gauche;
  int f;
  int ind_F1_1,ind_F1_2,ind_F2_1,ind_F2_2;


 if (debug)
  printf("vertex_split debut\n");
  // on recherche de quelle arete provient ce sommet
  La=L_aretes_retirees;
  while (La !=NULL){
    if (meme_sommet(sommet_fusion(La->A->S0,La->A->S1),S))
      break;
    La=La->suiv;
  }
  if  (La ==NULL){
    printf("erreur vertex_split : sommet non trouve dans la liste des aretes retirees\n");
    return -1;
  }
  // on a dans le premier element de La les informations sur les sommets retires.
  S1=La->A->S0;
  S2=La->A->S1;
  F1=La->f;
 
  // on recherche la deuxieme face supprimee lors de Edge_Collapse
   ind_S1=indice_sommet_face(S1,F1);
   ind_S2=indice_sommet_face(S2,F1);
   if (((ind_S1==0)&&(ind_S2==1))||((ind_S1==1)&&(ind_S2==0))){
     ind_sommet_F1=2;
     F2=La->f->f2;
   }
   if (((ind_S1==1)&&(ind_S2==2))||((ind_S1==2)&&(ind_S2==1))){
     ind_sommet_F1=0;
     F2=La->f->f0;
   }
   if (((ind_S1==2)&&(ind_S2==0))||((ind_S1==0)&&(ind_S2==2))){
     ind_sommet_F1=1;
     F2=La->f->f1;
   } 
   // on a retrouve les deux faces supprimees lors du vertex-split.
   // On regarde si les sommets non communs a ces faces sont deja present dans le maillage car dans le cas contraire, on ne peut pas inserer ces 2 faces.
   //printf("On verifie que le 3ieme point des faces que l'on veut inserer est bien deja present dans la figure\n");
   if (!present_liste_sommet(sommet_numero(ind_sommet_F1,F1),L_sommets)){
     printf("sommet non present dans F1.\n");
     return -1;
   }
   
   if (F2!=NULL){
     ind_sommet_F2=numero_sommet_non_commun_face(F2,F1);
     if (!present_liste_sommet(sommet_numero(ind_sommet_F2,F2),L_sommets)){
       printf("sommet non present dans F2.\n");
       return -1;
     }
   }

   // on recherche les deux faces adjacentes a F1 et differentes de F2
  F1_tmp_1=F1->f0;
  if (meme_face(F1_tmp_1,F2)){
    F1_tmp_1=F1->f1;
    F1_tmp_2=F1->f2; 
  } 
  else 
    {
      F1_tmp_2=F1->f1;
      if (meme_face(F1_tmp_2,F2))
	F1_tmp_2=F1->f2;
    }

  // on recherche les deux faces adjacentes a F2 et differentes de F1
  // si celle ci n'est pas null
  F2_tmp_1=NULL;
  F2_tmp_2=NULL;
  if (F2!=NULL){
    F2_tmp_1=F2->f0;
    if (meme_face(F2_tmp_1,F1)){
      F2_tmp_1=F2->f1;
      F2_tmp_2=F2->f2; 
    } 
    else 
      {
	F2_tmp_2=F2->f1;
	if (meme_face(F2_tmp_2,F1))
	  F2_tmp_2=F2->f2;
      }
  }

  if (debug)
    printf("\n\n on va effectuer le changement du chainage dans vs \n");
  if (F1_tmp_1!=NULL)
    changer_face_vs(F1_tmp_1,F1_tmp_2,F1,S,S1,S2);
  if (F1_tmp_2!=NULL)
    changer_face_vs(F1_tmp_2,F1_tmp_1,F1,S,S1,S2);
  if (F2_tmp_1!=NULL) 
    changer_face_vs(F2_tmp_1,F2_tmp_2,F2,S,S1,S2);
  if (F2_tmp_2!=NULL)
    changer_face_vs(F2_tmp_2,F2_tmp_1,F2,S,S1,S2); 
  if (debug)
    printf("\t chainage modifie\n");

 
  //on ajoute a la liste des faces les faces F1 et F2
  L_faces=ajouter_face(F1,L_faces);  
  if (F2!=NULL)
    L_faces=ajouter_face(F2,L_faces);  
  
  // il faut desormais mettre a jours les sommets 
  // pour ce faire on recupere les indices des deux sommets deja presents dans le maillage
  ind_S1=indice_sommet_face(S1,F1);
  ind_sommet_F1=numero_sommet_non_commun_face(F1,F2);

  if (ind_sommet_F1==3){
    // on a alors F2=NULL, il faut faire un autre test pour recuperer l'indice recherche.
    if (nb_voisins_NULL(F1)==1){
      // ce qui doit etre le cas car on a interdit les collapses qd 2 voisins sont NULL.
      if (F1->f0==NULL)
	ind_sommet_F1=0;
      if (F1->f1==NULL)
	ind_sommet_F1=1;
      if (F1->f2==NULL)
	ind_sommet_F1=2;
    }
    else 
      return -1;
  }


  if (debug)
    printf("On cherche dans quel sens on va effectuer la rotation afin de changer tous les sommets S en sommet S1 ou S2 selon le cas.\n");

  if ((ind_S1==2)&&(ind_sommet_F1==0)||(ind_S1==0)&&(ind_sommet_F1==2))
    ind_face_rot=1;
  else
    if ((ind_S1==1)&&(ind_sommet_F1==0)||(ind_S1==0)&&(ind_sommet_F1==1))
      ind_face_rot=2;
    else
      if ((ind_S1==1)&&(ind_sommet_F1==2)||(ind_S1==2)&&(ind_sommet_F1==1))
	ind_face_rot=0;

  // on regarde si il faut tourner a droite ou a gauche.  
  droite=(mod((ind_S1-1),3)==ind_face_rot);
  gauche=(mod((ind_S1+1),3)==ind_face_rot);
  if (!((droite&&!gauche)||(!droite&&gauche))){
    printf("erreur algo vertex split : rotation ni droite ni gauche\n");
    exit(0);
  }

  if (droite){
    rotation_vertex_split(ind_S1,F1,F2,S,S1,S2);
    if (F2!=NULL){
      ind_S2=indice_sommet_face(S2,F2);
      rotation_vertex_split(ind_S2,F2,F1,S,S2,S1);
    }
    
  
    if (F2!=NULL){
      ind_S1=indice_sommet_face(S1,F2);
      rotation_vertex_split(ind_S1,F2,F1,S,S2,S1);
    }

    ind_S2=indice_sommet_face(S2,F1);
    rotation_vertex_split(ind_S2,F1,F2,S,S1,S2);
    
    
  }
  else{
    rotation_vertex_split(ind_S1,F1,F2,S,S2,S1);
    if (F2!=NULL){
      ind_S2=indice_sommet_face(S2,F2);
      rotation_vertex_split(ind_S2,F2,F1,S,S1,S2);    
    }
    
 
    if (F2!=NULL){
      ind_S1=indice_sommet_face(S1,F2); 
      rotation_vertex_split(ind_S1,F2,F1,S,S1,S2);
    }
    
    ind_S2=indice_sommet_face(S2,F1);
    rotation_vertex_split(ind_S2,F1,F2,S,S2,S1);


  }

  // on retire S de la liste des sommets courants du maillage et on y ajoute S1 et S2
  L_sommets=supprimer_sommet(S,L_sommets);
  L_sommets=ajouter_sommet(S1,L_sommets);
  L_sommets=ajouter_sommet(S2,L_sommets);
  
  // on supprime l'arete A de la liste des arretes supprimees
  L_aretes_retirees=supprimer_arete(La->A,L_aretes_retirees);
  
  if (debug)
    printf("vertex_split fin\n");
  return 1;
}



int rotation_vertex_split(int ind_S1,face *F1,face *F2,sommet *S,sommet *S1,sommet * S2){
  // procedure tourne autour du sommet S a partir de F1 en partant vers la droite et remplace le sommet S par le sommet 1 dans toutes les faces qu'elle rencontre avant d arriver sur la face F2 ou sur un bord. Puis elle effectue un travail similaire en partant de F1 et en tournant vers la gauche mais cette fois ci en remplacant les sommets S rencontres par le sommet S2.
  liste_faces L;
  int droite,gauche;
  int numero_sommet;
  face *Fd,*Fg;

  droite=mod((ind_S1-1),3);
  // on passe a la face de droite 
  Fd=face_numero(droite,F1);
  while (Fd!=NULL){
    if (meme_face(Fd,F2))
      break;
    else {
      // on calcule l'indice de la prochaine face.
      numero_sommet=indice_sommet_face(S,Fd); 
      if (numero_sommet==-1)
	break;
      droite=mod((numero_sommet-1),3); 
      // on change le sommet
      changer_sommet(Fd,S,S1); 
      // on passe a la face droite 
      Fd=face_numero(droite,Fd);
    }
  }

  // on a fini la rotation vers la droite, on commence celle vers la gauche.
  gauche=mod((ind_S1+1),3);
  // on passe a la face gauche
  Fg=face_numero(gauche,F1);
  while (Fg!=NULL){
    if (meme_face(Fg,F2))
      break;
    // on calcule l'indice de la prochaine face.
    numero_sommet=indice_sommet_face(S,Fg); 
    if (numero_sommet==-1)
	break;
    gauche=mod((numero_sommet+1),3); 
    // on change le sommet
      changer_sommet(Fg,S,S2);
    // on passe a la face de gauche
    Fg=face_numero(gauche,Fg);
  }
  return 1;
}






#endif



























