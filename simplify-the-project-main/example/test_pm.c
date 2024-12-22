#include "constructeurs.h"
#include "acquisition.h"
#include "sortie.h"
#include "pm.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>


// On recupere les variables globales 
liste_sommets L_sommets;
liste_faces L_faces;
liste_aretes L_aretes_retirees;




// on definit les variables globales
int NB_MAX_SOMMETS=10000;
int NB_MAX_TRIANGLES=10000;

float dist_max=0.0;
int sortie_a_toutes_les_etapes=0;
int reconstruction=1;
int  autorisation_de_collapser_les_aretes_de_bord=0;
int bool_sortie_OFF=0;// si 0 sortie au format ".off" sinon sortie au format ".wrl"
int couleur_sommet=0;

float length(sommet *S1,sommet *S2){
  return ((S1->x - S2->x)*(S1->x-S2->x)+(S1->y - S2->y)*(S1->y-S2->y)+(S1->z - S2->z)*(S1->z-S2->z));
}



char  chiffre_char(int i){
  char *c;
  if (i==0)
    c="0";
  if (i==1)
    c="1";
 if (i==2)
    c="2";
 if (i==3)
    c="3";
 if (i==4)
    c="4";
 if (i==5)
    c="5";
 if (i==6)
    c="6";
 if (i==5)
    c="5";
 if (i==6)
    c="6";
 if (i==7)
    c="7";
 if (i==8)
    c="8";
 if (i==9)
    c="9";
return *c;
}







face* face_petite_arete(int *i){
  // fonction qui cherche dans la liste des faces celle qui contient la plus petite arete et la renvoie. Elle renvera dans i le numero de la face voisine avec laquelle elle partage cette arete.
  // on suppose qu'il y a au moins une face
  float min=2*dist_max;// valeur de l'arete minimale
  float min_tmp=2*dist_max;
  arete *A; //arete de taille minimale 
  liste_faces LL;
  sommet *S0;
  sommet *S1;
  sommet *S2;
  face *F;
  face *F_min=NULL;
  face *F_min_tmp=NULL;
  face *F_min_2;
  int a,b;
  liste_aretes La;
  int j;
  liste_faces face_impossibles;
  int changement;
  arete *A_tmp;
  sommet *S0_tmp;
  sommet *S1_tmp;
  int collapse;
  
  face_impossibles=NULL;
  A=creer_arete(NULL,NULL);
  A_tmp=creer_arete(NULL,NULL);

  LL=L_faces;
  while (LL!=NULL){
    if (F==LL->F)
      printf("\t\t\t erreur face_petite_arete\n");
    A_tmp=NULL;
    F=LL->F;
    F_min_tmp=F_min;
    min_tmp=min; 
    changement = 0;
    collapse=0;
    if (!(present_liste_face(F,face_impossibles))){  
      S0=F->S0;
      S1=F->S1;
      S2=F->S2;

      if (min>length(S0,S1)){
	S0_tmp=S0;
	S1_tmp=S1;
	min_tmp=length(S0,S1);
	F_min_tmp=F;
	changement=1;

	a=indice_sommet_face(S0_tmp,F_min_tmp);
	b=indice_sommet_face(S1_tmp,F_min_tmp);
	if ( ((a==0)&&(b==1)) || ((a==1)&&(b==0)) )
	  j=2;
	if ( ((a==2)&&(b==1)) || ((a==1)&&(b==2)) )
	  j=1;
	if ( ((a==0)&&(b==2)) || ((a==2)&&(b==0)) )
	  j=0;
	F_min_2=face_numero(j,F_min_tmp);
	if (autorisation_collapse(F_min_2,F_min_tmp)) {
	  //printf("autoristation\n");
	  F_min=F_min_tmp;
	  min=min_tmp;
	  A->S0=S0_tmp;
	  A->S1=S1_tmp;
	  collapse=1;
	}
      }
      if (min>length(S1,S2)){
	S0_tmp=S1;
	S1_tmp=S2;
	min_tmp=length(S1,S2);
	F_min_tmp=F;
	changement=1;

	a=indice_sommet_face(S0_tmp,F_min_tmp);
	b=indice_sommet_face(S1_tmp,F_min_tmp);
	if ( ((a==0)&&(b==1)) || ((a==1)&&(b==0)) )
	  j=2;
	if ( ((a==2)&&(b==1)) || ((a==1)&&(b==2)) )
	  j=1;
	if ( ((a==0)&&(b==2)) || ((a==2)&&(b==0)) )
	  j=0;
	F_min_2=face_numero(j,F_min_tmp);
	if (autorisation_collapse(F_min_2,F_min_tmp)) {
	  //printf("autoristation\n");
	  F_min=F_min_tmp;
	  min=min_tmp;
	  A->S0=S0_tmp;
	  A->S1=S1_tmp;
	  collapse=1;
	}
      }
      if (min>length(S0,S2)){
	S0_tmp=S0;
	S1_tmp=S2;
	min_tmp=length(S0,S2);
	F_min_tmp=F;
	changement=1;

	a=indice_sommet_face(S0_tmp,F_min_tmp);
	b=indice_sommet_face(S1_tmp,F_min_tmp);
	if ( ((a==0)&&(b==1)) || ((a==1)&&(b==0)) )
	  j=2;
	if ( ((a==2)&&(b==1)) || ((a==1)&&(b==2)) )
	  j=1;
	if ( ((a==0)&&(b==2)) || ((a==2)&&(b==0)) )
	  j=0;
	F_min_2=face_numero(j,F_min_tmp);
	if (autorisation_collapse(F_min_2,F_min_tmp)) {
	  //printf("autoristation\n");
	  F_min=F_min_tmp;
	  min=min_tmp;
	  A->S0=S0_tmp;
	  A->S1=S1_tmp;
	  collapse=1;
	}
      }
      if  ((changement)&&(!collapse)){
	  //printf("pas autoristation\n");
	  face_impossibles=ajouter_face(F_min_tmp,face_impossibles);
	}
      }
    
    LL=LL->suiv;
  }
  
  if ((F_min==NULL)){
    //printf("On renvoie NULL comme face selectionnee.\n");
    return NULL;
}
  else 
    {      
      a=indice_sommet_face(A->S0,F_min);
      b=indice_sommet_face(A->S1,F_min);
      if ( ((a==0)&&(b==1)) || ((a==1)&&(b==0)) )
	*i=2;
      if ( ((a==2)&&(b==1)) || ((a==1)&&(b==2)) )
	*i=1;
      if ( ((a==0)&&(b==2)) || ((a==2)&&(b==0)) )
	*i=0; 
    }
  return F_min;
}





  

int main(int argc,char *argv[]){
  int debug=0;
  liste_faces LL;
  face *f1;
  face *f2;
  sommet *S;
  int n,n_face;
  int i,j;
  char conv_i[]="0000.off";
  int m,c,d,u;
  int pid[100];
  int res;
  char *tmp;
  int ind_S1,ind_S2,ind_sommet_F1;
  sommet *S1;
  sommet *S2;
  face *F1;
  face *F2;
  liste_aretes La;



  
  if (argc!=5){
    printf("erreur dans le nombre de parametres : %d\n",argc);
    printf("Le programme test_pm permet de realiser l'operation\n");
    printf("de fusion des sommets puis l'operation inverse.\n");
    printf("Ce programme prend 4 parametres qui sont les suivants :\n");
    printf("Le fichier au format .NGB du maillage a simplifier.\n");
    printf("Le nom du fichier dans lequel on mettera le resultat.\n");
    printf("Le nombre d arete a retirer dans le maillage\n");
    printf("Le nom du fichier dans lequel on mettra le maillage resultat\n");
    printf("apres la reconstruction (a specifier mem si pas de reconstruction\n");
    return 0;
  }
  else
    {
      init();
      if (debug)
	printf("fichier en entree %s\n",argv[1]);
      acquisition(argv[1],&dist_max);
  
      if (debug)
	printf("distance_max %f\n",dist_max);


      LL=L_faces;
      if (debug)
	printf("On peut desormais supprimer des arete.\n");
      // on definit le nombre d'arete a retirer
      n=atoi(argv[3]);
      // printf("On decide du supprimer le %d plus petites aretes\n",n);

       // on verifie la coherence des donnee.
       if (doublon_face(L_faces)){
       printf("Definition dans les donnes de deux faces identiques\n");
       return -1;
       }
       else if (doublon_sommet(L_sommets)){
	 printf("Definition dans les donnes de deux sommets identiques\n");
	 return -1;
       }      
       else
	 NULL;// printf("donnes integres \n");

       for (i=0;i<n;i++){
	 //if (debug)  
	   printf("i-debut %d\n",i);
	 
	 f1=face_petite_arete(&n_face);
	 if (debug)
	   printf("face selectionne\n");
	 if (f1==NULL){
	    printf("\t On ne peut plus collapser, on a effectuer %d collapse\n",i);
	    if (bool_sortie_OFF==0)
	      sortie_OFF(argv[2]);
	    else 
	      sortie_WRL(argv[2]);
	    
	    goto reconstruction;
	    return -1;
	 }
	 if (n_face==0)
	   f2=f1->f0;
	 if (n_face==1)
	   f2=f1->f1;
	 if (n_face==2)
	   f2=f1->f2;

	 S=edge_collapse(f1,f2);
	 if (debug)  
	   printf("collapse fini \n");
	 // on effectue des tests pour verifier l integritee des donnees obtenues a la fin du edge collapse.

	 if (verif(i,f1,f2)==-1)
	   exit(0); 
	 	
	
	 if (bool_sortie_OFF!=0){
	   conv_i[4]='w';
	   conv_i[5]='r';
	   conv_i[6]='l';
	 }

	 if (sortie_a_toutes_les_etapes){
	 // on a donc une structure coherente. On sort le fichier en question
	   m=i/1000;
	   c=(i-m*1000)/100;
	   d=(i-c*100-1000*m)/10;
	   u=i-d*10-c*100-m*1000;
	   conv_i[0]=chiffre_char(m);
	   conv_i[1]=chiffre_char(c);
	   conv_i[2]=chiffre_char(d);
	   conv_i[3]=chiffre_char(u);
	   if (bool_sortie_OFF==0)
	     sortie_OFF(conv_i);
	   else
	     sortie_WRL(conv_i);
	 }
       }
       
       
       printf("fichier en sortie %s\n",argv[2]);
       if (bool_sortie_OFF==0)
	 sortie_OFF(argv[2]);
       else
	 sortie_WRL(argv[2]);

       reconstruction :{
	 if (!reconstruction)
	   exit(0);
	 i=1;
	 printf("desormais on reconstruit le modele.\n");
	
	 while (L_aretes_retirees!=NULL){
	   f1=L_aretes_retirees->f;
	   if (!verification_chainage(L_faces)){
	     exit(0);
	   }
	   
	   
	   if (verif(i,f1,f2)==-1)
	     exit(0);
	   
	   printf("------------------------- reconstruction %d\n",i++);
	   // on a dans le premier element de La les informations sur les sommets retires.
	   La=L_aretes_retirees;
	   
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
	   
	   
	   S=sommet_fusion(L_aretes_retirees->A->S0,L_aretes_retirees->A->S1);
	   if (vertex_split(S)!=1)
	     break;
	 }
       }
       printf("\tOn imprime la reconstruction dans %s\n\n",argv[4]);
       if (bool_sortie_OFF==0)
	 sortie_OFF_bis(argv[4]);
       else
	 sortie_WRL(argv[4]);      
    }
}


int verif(int i, face *f1, face *f2){  
  face *f;
  int arret=0;
  f=test_nb_arete_face();
  if (f!=NULL){
    printf("Grosse erreur : plus de une face chainee a une meme arete : iteration %d \n",i);
    printf("sortie dans : erreur.off \n");
    sortie_OFF_couleur("erreur.off",f,f);
    arret=1;
  }
  if (L_faces!=NULL)
    if (doublon_face(L_faces)){
      printf("definition de deux faces identiques  : iteration %d\n",i);
      arret=1;
    }
  if (doublon_sommet(L_sommets)){
    printf("definition de deux sommets identiques : iteration %d\n",i);
    arret=1;
  }
  if (!chainage_non_reccursif()){
    sortie_OFF_couleur("erreur.off",f1,f2);
    printf("le edge_collapse precedent a introduit un chainage reccursif des faces : iteration %d\n",i);
    printf("sortie dans : erreur.off\n");
    arret=1;
  }
  /*if (!(a_2voisins())){
    if (L_faces->suiv != NULL){
    printf("On a introduit une n'ayant qu'une ou zero faces voisines\n");
    sortie_OFF_couleur("1_voisin.off",f1,f2);
    arret=1;
    }
    }*/
  
  // printf("fin verification des voisins \n");
  if (!verification_chainage(L_faces)){
    printf("Chainage incoherent des faces\n");
    arret=1;
  }
  
  if (arret)
    exit(0);
}













