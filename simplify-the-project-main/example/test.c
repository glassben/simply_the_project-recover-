
#include "test.h"



// On definit les variables globales 
extern liste_sommets L_sommets;
extern liste_faces L_faces;
extern liste_aretes L_aretes_retirees;


int doublon_face(liste_faces param){
  //fonction qui teste si il y a deux faces identiques dans la liste de face param. 
  liste_faces LL;
  liste_faces L;
  
  L=param;
  LL=L->suiv;
  while (L!=NULL){
    while (LL!=NULL){
      if (meme_face(LL->F,L->F))
	return 1;
      LL=LL->suiv;
    }
    L=L->suiv;
  }
  return 0;

}


int doublon_sommet(liste_sommets param){
  // fonction qui teste si li y a deux sommets identiques dans la liste de sommets param.
  liste_sommets LL;
  liste_sommets L;
  
  L=param;
  LL=L->suiv;
  while (L!=NULL){
    while (LL!=NULL){
      if (meme_sommet(LL->S,L->S))
	return 1;
      LL=LL->suiv;
    }
    L=L->suiv;
  }
  return 0;

}

int chainage_non_reccursif(){
  // fonction qui verifie qu'il n'y a aps de chainage reccursif (une face chainee a elle meme) dans la liste de face du maillage
  liste_faces L;
  face *F;
  L=L_faces;
  while (L!=NULL){
    F=L->F;
    
    if (meme_face(F,F->f0)){
      affichage_face_voisin(F,0);
      return 0;
      }
    if (meme_face(F,F->f1)){
      affichage_face_voisin(F,0);
      return 0;
      }
    if (meme_face(F,F->f2)){
      affichage_face_voisin(F,0);
      return 0;
}
    L=L->suiv;
  }
  return 1;
}






int a_2voisins(){
  // procedure qui verifie si chaque face du shema a au moins 2 faces voisines ou non.
  // a utiliser avec precaution 
  //utile pour les surfaces fermees mais a ne pas utiliser si il y a des bord.
  liste_faces Lf;
  face *F;
  int nb_faces;
  int bool=1;
  
  Lf=L_faces; 
  while (Lf!=NULL){
    nb_faces=0;
    F=Lf->F;
    if (F->f0!=NULL)
      nb_faces++;
    if (F->f1!=NULL)
      nb_faces++;
    if (F->f2!=NULL)
      nb_faces++;
    bool=bool&&(nb_faces>0);
    Lf=Lf->suiv;
  }
  return bool;
}


int bien_chaine(face *F,face *F1){
  // procedure qui verifie que les faces F et F1 ont bien deux sommets communs.
  if (F1==NULL)
    return 1;
  return ( (appartient_a_la_face(F->S0,F1)) && (appartient_a_la_face(F->S1,F1)) && (!(appartient_a_la_face(F->S2,F1))) )||( (appartient_a_la_face(F->S1,F1))&&(appartient_a_la_face(F->S2,F1)) && (!(appartient_a_la_face(F->S0,F1))) )||( (appartient_a_la_face(F->S2,F1))&&(appartient_a_la_face(F->S0,F1)) && (!(appartient_a_la_face(F->S1,F1))) );
}


int verification_chainage(liste_faces L){
  // verifie aue les face du shema sont bien chainees.
  liste_faces LL;
  face *F;
  int bool=1;

 LL=L;
 while (LL!=NULL){ 
   F=LL->F;
   bool=bool && bien_chaine(F,F->f0) && bien_chaine(F,F->f1) && bien_chaine(F,F->f2);
   if (!bool){
     printf("Chainage incoherent au niveau des points\n");
     affichage_face_voisin(F,0);
     break;}
   LL=LL->suiv;
 } 
return bool;
}



face * test_nb_arete_face(){
  // procedure qui verifie qu'une arete du maillage est commune a 1 ou 2 faces maximum. Sinon on a une incoherence structurelle.
  // elle verifie de plus que l'on a pas deux faces confondues dans la liste des faces.
  liste_sommets Ls;
  liste_faces Lf;
  liste_faces LLf;
  face *F;
  face *F1;
  int cpt0,cpt1,cpt2;
  int bool0,bool1,bool2;
  sommet *S0;
  sommet *S1;
  sommet *S2;


  Lf=L_faces;
  while (Lf!=NULL){
    LLf=Lf->suiv;
    F=Lf->F;
    S0=F->S0;
    S1=F->S1;
    S2=F->S2;
    cpt0=0;
    cpt1=0;
    cpt2=0;
    
    while (LLf!=NULL){
      F1=LLf->F;
      
      bool0=appartient_a_la_face(S0,F1);
      bool1=appartient_a_la_face(S1,F1);
      bool2=appartient_a_la_face(S2,F1);
      if (bool0 && bool1 && bool2){
	printf("Erreur on a deux faces confondues");
	return F1;
      }
      if (bool1+bool2==2)
	// alors on a une arete commune
	cpt0++;
      if (bool0+bool2==2)
	// alors on a une arete commune
	cpt1++;
      if (bool0+bool1==2)
	// alors on a une arete commune
	cpt2++;


      if ((cpt0>1)||(cpt1>1)||(cpt2>1)){
	printf("l'arrete a plus de 1 voisin\n");
	return F;
      }
      LLf=LLf->suiv;
    }
    Lf=Lf->suiv;
  }
  return NULL;
}
