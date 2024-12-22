#include "acquisition.h"
#include "sortie.h"


int main(int argc,char *argv[]){

  if (argc!=3){
    printf("erreur dans le nombre de parametres : %d\n",argc);
    return 0;
  }
  else
    {
      printf("fichier en entree %s\n",argv[1]);
      acquisition(argv[1]);
      printf("\n\n");
      printf("fichier en sortie %s\n",argv[2]);
      sortie_OFF(argv[2]);
    }

}
