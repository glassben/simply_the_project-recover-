// premier essai d'algortithme de compression d'une arrete.


#ifndef PM_H
#define PM_H


#include <stdio.h>
#include "constructeurs.h"
#include "sortie.h"
#include "acquisition.h"
#include "listes.h"
#include "test.h"




// On recupere les variables globales 
extern liste_sommets L_sommets;
extern liste_faces L_faces;
extern liste_aretes L_aretes_retirees;

extern int  autorisation_de_collapser_les_aretes_de_bord;




int  init();
// fonction qui initialise les variables globales.

int autorisation_collapse(face *F1,face *F2);
// renvoie 1 si il est possible de collapser les face F1 et F2 et 0 sinon.
// pour plus de detail voir doc utilisateur


sommet*  edge_collapse_prog(face* F1,face* F2,sommet* S1,sommet* S2);
  // fonction qui realise la compression de l'arrete entre les sommets S1 et S2,
  // en faisant disparaitre du maillage les faces F1 et F2 
  // puis en rajoutant a la liste L des arretes deja retirees l'arrete (S1,S2)
  // cette fonction retourne le nouveau sommet du maillage
  // attention l'ordre de passage des parametres doit etre l'ordre trigonometrique.
  // Cette fonction renvoie le sommet issu de la compression de l'arete collapsee.
sommet * edge_collapse_bord(face *F);
//fonction qui effectue le collapse de l'arÅÍte de la face F qui n'a pas de voisin
// Attention on ne peux lui passer que des faces ayant un seul voisin non NULL.

sommet*  edge_collapse(face* F1,face* F2);
// procedure de dispatching entre edge_collapse_prog et edge_collapse_bord


int vertex_split(sommet *S);
// procedure qui effectue le vertex split de l'arete dont la compression a cree le sommet S.


#endif











































































































