int test_4(){
  face * f1;
  face * f2;
  face * f3;
  face * f4;
  face * f5;
  face * f6;
  face * f7;
  face * f8;
  sommet * a;
  sommet * b;
  sommet * c;
  sommet * d;
  sommet * e;
  sommet * f;
  sommet * g;
  sommet * h;
  sommet * i;
  liste_sommets L_sommet_tmp;
  face * ff1;
  face * fff1;
  face * ffff1;
  sommet * aa;
  printf("On redefinit le maillage afin de tester la fonction edge_collapse\n");
  init();
  a=creer_sommet((float)1,(float)4,(float)0,creer_info());
  L_sommets=ajouter_sommet(a,L_sommets);

  b=creer_sommet((float)3,(float)4,(float)0,creer_info());
  L_sommets=ajouter_sommet(b,L_sommets);

  c=creer_sommet((float)2,(float)3,(float)0,creer_info());
  L_sommets=ajouter_sommet(c,L_sommets);

  d=creer_sommet((float)0,(float)2,(float)0,creer_info());
  L_sommets=ajouter_sommet(d,L_sommets);

  e=creer_sommet((float)2,(float)1,(float)0,creer_info());
  L_sommets=ajouter_sommet(e,L_sommets);

  f=creer_sommet((float)4,(float)2,(float)0,creer_info());
  L_sommets=ajouter_sommet(f,L_sommets);

  g=creer_sommet((float)1,(float)0,(float)0,creer_info());
  L_sommets=ajouter_sommet(g,L_sommets);

  h=creer_sommet((float)4,(float)0,(float)0,creer_info());
  L_sommets=ajouter_sommet(h,L_sommets);
  //creer_sommet(2,2,0,creer_info());
  //sommet=ajouter_sommmet(i,L_sommet);
  f1=creer_face(a,c,b,NULL,NULL,NULL);
  f2=creer_face(b,c,f,NULL,NULL,NULL);
  f3=creer_face(a,d,c,NULL,NULL,NULL);
  f4=creer_face(d,g,e,NULL,NULL,NULL);
  f5=creer_face(g,h,e,NULL,NULL,NULL);
  f6=creer_face(e,h,f,NULL,NULL,NULL);
  f7=creer_face(c,d,e,NULL,NULL,NULL);
  f8=creer_face(c,e,f,NULL,NULL,NULL);
  printf("On a cree les faces, on les chaines.\n");
  chainer_face(f1,NULL,f2,f3);
  
  chainer_face(f2,NULL,f1,f8);
  
  chainer_face(f3,NULL,f1,f7);
  
  chainer_face(f4,NULL,f7,f5);
  
  chainer_face(f5,NULL,f4,f6);
  
  chainer_face(f6,NULL,f5,f8);
  
  chainer_face(f7,f3,f4,f8);
  
  chainer_face(f8,f2,f6,f7);

  printf("On affiche les sommets \n");
  afficher_liste_sommet(L_sommets);
 
  printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
   printf("On verifie le chainage.\n");
  afficher_face(f1);
  printf("\t voisins de face 1\n");  
  afficher_face(f1->f0);
  afficher_face(f1->f1);
  afficher_face(f1->f2);
  printf("test sur la face 2\n");
  printf("face 2\n");
  afficher_face(f2);
  printf("\t voisins de face 2\n");  
  afficher_face(f2->f0);
  afficher_face(f2->f1);
  afficher_face(f2->f2);
  printf("test sur la face 3\n");
  printf("face 3\n");
  afficher_face(f3);
  printf("\t voisins de face 3\n");  
  afficher_face(f3->f0);
  afficher_face(f3->f1);
  afficher_face(f3->f2);
  printf("test sur la face 4\n");
  printf("face 4\n");
  afficher_face(f4);
  printf("\t voisins de face 4\n");  
  afficher_face(f4->f0);
  afficher_face(f4->f1);
  afficher_face(f4->f2);
  printf("test sur la face 5\n");
  printf("face 5\n");
  afficher_face(f5);
  printf("\t voisins de face 5\n");  
  afficher_face(f5->f0);
  afficher_face(f5->f1);
  afficher_face(f5->f2);
  printf("test sur la face 6\n");
  printf("face 6\n");
  afficher_face(f6);
  printf("\t voisins de face 6\n");  
  afficher_face(f6->f0);
  afficher_face(f6->f1);
  afficher_face(f6->f2);
  printf("test sur la face 7\n");
  printf("face 7\n");
  afficher_face(f7);
  printf("\t voisins de face 7\n");  
  afficher_face(f7->f0);
  afficher_face(f7->f1);
  afficher_face(f7->f2);
  printf("test sur la face 8\n");
  printf("face 8\n");
  afficher_face(f8);
  printf("\t voisins de face 8\n");  
  afficher_face(f8->f0);
  afficher_face(f8->f1);
  afficher_face(f8->f2); 
 
  printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

  //  printf("On teste la procedure edge_collapse \n");
  i=edge_collapse(f7,f8,c,e,L_aretes_retirees);
  
  printf("On affiche les deux faces supprimees\n");
  afficher_face(f7);  
  afficher_face(f8);
    
  printf("On affiche les sommets \n");
  afficher_liste_sommet(L_sommets);

  printf("On affiche les faces \n");
  afficher_liste_face(L_faces);
  
  
  //printf("On teste la procedure vertex_split \n");
  vertex_split(i);

   printf("On affiche les sommets \n");
  afficher_liste_sommet(L_sommets);


  printf("On affiche les faces \n");
  afficher_liste_face(L_faces);
  printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  printf("On affiche les faces \n");
  afficher_liste_face(L_faces);
  
   printf("On verifie le chainage.\n");
  afficher_face(f1);
  printf("\t voisins de face 1\n");  
  afficher_face(f1->f0);
  afficher_face(f1->f1);
  afficher_face(f1->f2);
  printf("test sur la face 2\n");
  printf("face 2\n");
  afficher_face(f2);
  printf("\t voisins de face 2\n");  
  afficher_face(f2->f0);
  afficher_face(f2->f1);
  afficher_face(f2->f2);
  printf("test sur la face 3\n");
  printf("face 3\n");
  afficher_face(f3);
  printf("\t voisins de face 3\n");  
  afficher_face(f3->f0);
  afficher_face(f3->f1);
  afficher_face(f3->f2);
  printf("test sur la face 4\n");
  printf("face 4\n");
  afficher_face(f4);
  printf("\t voisins de face 4\n");  
  afficher_face(f4->f0);
  afficher_face(f4->f1);
  afficher_face(f4->f2);
  printf("test sur la face 5\n");
  printf("face 5\n");
  afficher_face(f5);
  printf("\t voisins de face 5\n");  
  afficher_face(f5->f0);
  afficher_face(f5->f1);
  afficher_face(f5->f2);
  printf("test sur la face 6\n");
  printf("face 6\n");
  afficher_face(f6);
  printf("\t voisins de face 6\n");  
  afficher_face(f6->f0);
  afficher_face(f6->f1);
  afficher_face(f6->f2);
  printf("test sur la face 7\n");
  printf("face 7\n");
  afficher_face(f7);
  printf("\t voisins de face 7\n");  
  afficher_face(f7->f0);
  afficher_face(f7->f1);
  afficher_face(f7->f2);
  printf("test sur la face 8\n");
  printf("face 8\n");
  afficher_face(f8);
  printf("\t voisins de face 8\n");  
  afficher_face(f8->f0);
  afficher_face(f8->f1);
  afficher_face(f8->f2); 
 
 // printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");   
 
}



int test(){
  // programme qui teste l'ensemble des procedures crees ci_dessus
  face * f1;
  face * f2;
  face * f3;
  face * f4;
  face * f5;
  face * f6;
  face * f7;
  face * f8;
  sommet * a;
  sommet * b;
  sommet * c;
  sommet * d;
  sommet * e;
  sommet * f;
  sommet * g;
  sommet * h;
  liste_sommets L_sommet_tmp;
  face * ff1;
  face * fff1;
  face * ffff1;
  sommet * aa;
  printf("On redefinit le maillage afin de tester la fonction edge_collapse\n");
  init();
  a=creer_sommet(1,4,0,NULL);
  L_sommets=ajouter_sommet(a,L_sommets);
  b=creer_sommet(3,4,0,NULL);
  L_sommets=ajouter_sommet(b,L_sommets);
  c=creer_sommet(2,3,0,NULL);
  L_sommets=ajouter_sommet(c,L_sommets);
  d=creer_sommet(0,2,0,NULL);
  L_sommets=ajouter_sommet(d,L_sommets);
  e=creer_sommet(2,1,0,NULL);
  L_sommets=ajouter_sommet(e,L_sommets);
  f=creer_sommet(4,2,0,NULL);
  L_sommets=ajouter_sommet(f,L_sommets);
  g=creer_sommet(1,0,0,NULL);
  L_sommets=ajouter_sommet(g,L_sommets);
  h=creer_sommet(4,0,0,NULL);
  L_sommets=ajouter_sommet(h,L_sommets);
  f1=creer_face(a,c,b,NULL,NULL,NULL);
  f2=creer_face(b,c,f,NULL,NULL,NULL);
  f3=creer_face(a,d,c,NULL,NULL,NULL);
  f4=creer_face(d,g,e,NULL,NULL,NULL);
  f5=creer_face(g,h,e,NULL,NULL,NULL);
  f6=creer_face(e,h,f,NULL,NULL,NULL);
  f7=creer_face(c,d,e,NULL,NULL,NULL);
  f8=creer_face(c,e,f,NULL,NULL,NULL);
  printf("On a cree les faces, on les chaines.\n");

  chainer_face(f1,NULL,f2,f3);
  
  chainer_face(f2,NULL,f1,f8);
  
  chainer_face(f3,NULL,f1,f7);
  
  chainer_face(f4,NULL,f7,f5);
  
  chainer_face(f5,NULL,f4,f6);
  
  chainer_face(f6,NULL,f5,f8);
  
  chainer_face(f7,f3,f4,f8);
  
  chainer_face(f8,f2,f6,f7);

  printf("definition terminee.\n");
  printf("On verifie le chainage.\n");
  afficher_face(f1);
  printf("\t voisins de face 1\n");  
  afficher_face(f1->f0);
  afficher_face(f1->f1);
  afficher_face(f1->f2);
  printf("test sur la face 2\n");
  printf("face 2\n");
  afficher_face(f2);
  printf("\t voisins de face 2\n");  
  afficher_face(f2->f0);
  afficher_face(f2->f1);
  afficher_face(f2->f2);
  printf("test sur la face 3\n");
  printf("face 3\n");
  afficher_face(f3);
  printf("\t voisins de face 3\n");  
  afficher_face(f3->f0);
  afficher_face(f3->f1);
  afficher_face(f3->f2);
  printf("test sur la face 4\n");
  printf("face 4\n");
  afficher_face(f4);
  printf("\t voisins de face 4\n");  
  afficher_face(f4->f0);
  afficher_face(f4->f1);
  afficher_face(f4->f2);
  printf("test sur la face 5\n");
  printf("face 5\n");
  afficher_face(f5);
  printf("\t voisins de face 5\n");  
  afficher_face(f5->f0);
  afficher_face(f5->f1);
  afficher_face(f5->f2);
  printf("test sur la face 6\n");
  printf("face 6\n");
  afficher_face(f6);
  printf("\t voisins de face 6\n");  
  afficher_face(f6->f0);
  afficher_face(f6->f1);
  afficher_face(f6->f2);
  printf("test sur la face 7\n");
  printf("face 7\n");
  afficher_face(f7);
  printf("\t voisins de face 7\n");  
  afficher_face(f7->f0);
  afficher_face(f7->f1);
  afficher_face(f7->f2);
  printf("test sur la face 8\n");
  printf("face 8\n");
  afficher_face(f8);
  printf("\t voisins de face 8\n");  
  afficher_face(f8->f0);
  afficher_face(f8->f1);
  afficher_face(f8->f2);
  // on peut desormais lancer edge_collapse
  //  printf(")))))))))))))))))))))))))))))))))))))))))))))))");

  printf("On effectue la fusion c et e et la disparition des face f7 et f8.\n");
  edge_collapse(f7,f8,c,e,L_aretes_retirees);
  // printf(")))))))))))))))))))))))))))))))))))))))))))))))");
  printf("on affiche les sommets apres la fusion\n");
  afficher_liste_sommet(L_sommets);
  printf("on affiche les faces apres la fusion\n");  
  afficher_liste_face(L_faces);
  printf("on affiche la liste des aretes retirees lors de la fusion\n");  
  afficher_liste_arete(L_aretes_retirees);

  printf("°+°+°+°+°+°+°+°+°+°+°+°\n");
  printf("On verifie desormais que les faces obtenues apres la fusion ont les bonnes faces voisines\n");
  printf("test sur la face 1\n");
  printf("face 1\n");
  afficher_face(f1);
  printf("\t voisins de face 1\n");  
  afficher_face(f1->f0);
  afficher_face(f1->f1);
  afficher_face(f1->f2);
  printf("test sur la face 2\n");
  printf("face 2\n");
  afficher_face(f2);
  printf("\t voisins de face 2\n");  
  afficher_face(f2->f0);
  afficher_face(f2->f1);
  afficher_face(f2->f2);
  printf("test sur la face 3\n");
  printf("face 3\n");
  afficher_face(f3);
  printf("\t voisins de face 3\n");  
  afficher_face(f3->f0);
  afficher_face(f3->f1);
  afficher_face(f3->f2);
  printf("test sur la face 4\n");
  printf("face 4\n");
  afficher_face(f4);
  printf("\t voisins de face 4\n");  
  afficher_face(f4->f0);
  afficher_face(f4->f1);
  afficher_face(f4->f2);
  printf("test sur la face 5\n");
  printf("face 5\n");
  afficher_face(f5);
  printf("\t voisins de face 5\n");  
  afficher_face(f5->f0);
  afficher_face(f5->f1);
  afficher_face(f5->f2);
  printf("test sur la face 6\n");
  printf("face 6\n");
  afficher_face(f6);
  printf("\t voisins de face 6\n");  
  afficher_face(f6->f0);
  afficher_face(f6->f1);
  afficher_face(f6->f2);
}


int test_2(){
  face * f1;
  face * f2;
  face * f3;
  face * f4;
  face * f5;
  face * f6;
  face * f7;
  face * f8;
  face * f9;
  face * f10;
  face * f11;
  sommet * a;
  sommet * b;
  sommet * c;
  sommet * d;
  sommet * e;
  sommet * f;
  sommet * g;
  sommet * h;
  sommet * x;
  sommet * y;
  sommet * i;
  init();


  init();
  a=creer_sommet(1,4,0,NULL);
  b=creer_sommet(3,4,0,NULL);
  c=creer_sommet(2,3,0,NULL);
  d=creer_sommet(0,2,0,NULL);
  e=creer_sommet(2,1,0,NULL);
  f=creer_sommet(4,2,0,NULL);
  g=creer_sommet(1,0,0,NULL);
  h=creer_sommet(4,0,0,NULL);
  f1=creer_face(a,b,c,NULL,NULL,NULL);
  f2=creer_face(b,f,c,NULL,NULL,NULL);
  f3=creer_face(a,c,d,NULL,NULL,NULL);
  f4=creer_face(d,e,g,NULL,NULL,NULL);
  f5=creer_face(g,h,e,NULL,NULL,NULL);
  f6=creer_face(e,h,f,NULL,NULL,NULL);
  f7=creer_face(c,d,e,NULL,NULL,NULL);
  f8=creer_face(c,f,e,NULL,NULL,NULL);
  printf("On a cree les faces, on les chaines.\n");
 chainer_face(f1,NULL,f2,f3);

 chainer_face(f2,NULL,f1,f8);

 chainer_face(f3,NULL,f1,f7);

 chainer_face(f4,NULL,f7,f5);

 chainer_face(f5,NULL,f4,f6);

 chainer_face(f6,NULL,f5,f8);

 chainer_face(f7,f3,f4,f8);

 chainer_face(f8,f2,f6,f7);




  // on peut desormais lancer edge_collapse
  //printf(")))))))))))))))))))))))))))))))))))))))))))))))");

  printf("On effectue la fusion c et e et la disparition des face f7 et f8.\n");
  i=edge_collapse(f7,f8,c,e,L_aretes_retirees);

  printf("On effectue la fusion i et f et la disparition des face f2 et f6.\n");
  edge_collapse(f2,f6,i,f,L_aretes_retirees);

  //printf(")))))))))))))))))))))))))))))))))))))))))))))))");
  printf("on affiche les sommets apres la fusion\n");
  afficher_liste_sommet(L_sommets);
  printf("on affiche les faces apres la fusion\n");  
  afficher_liste_face(L_faces);
  printf("on affiche la liste des aretes retirees lors de la fusion\n");  
  afficher_liste_arete(L_aretes_retirees);
  
  printf("°+°+°+°+°+°+°+°+°+°+°+°\n");
  printf("On verifie desormais que les faces obtenues apres la fusion ont les bonnes faces voisines\n");
  printf("test sur la face 1\n");
  printf("face 1\n");
  afficher_face(f1);
  printf("\t voisins de face 1\n");  
  afficher_face(f1->f0);
  afficher_face(f1->f1);
  afficher_face(f1->f2);
  printf("test sur la face 3\n");
  printf("face 3\n");
  afficher_face(f3);
  printf("\t voisins de face 3\n");  
  afficher_face(f3->f0);
  afficher_face(f3->f1);
  afficher_face(f3->f2);
  printf("test sur la face 4\n");
  printf("face 4\n");
  afficher_face(f4);
  printf("\t voisins de face 4\n");  
  afficher_face(f4->f0);
  afficher_face(f4->f1);
  afficher_face(f4->f2);
  printf("test sur la face 5\n");
  printf("face 5\n");
  afficher_face(f5);
  printf("\t voisins de face 5\n");  
  afficher_face(f5->f0);
  afficher_face(f5->f1);
  afficher_face(f5->f2);
  printf("test sur la face 9\n");
  printf("face 9\n");
  afficher_face(f9);
  printf("\t voisins de face 9\n");  
  afficher_face(f9->f0);
  afficher_face(f9->f1);
  afficher_face(f9->f2);
  printf("test sur la face 10\n");
  printf("face 10\n");
  afficher_face(f10);
  printf("\t voisins de face 10\n");  
  afficher_face(f10->f0);
  afficher_face(f10->f1);
  afficher_face(f10->f2);  
  printf("test sur la face 11\n");
  printf("face 11\n");
  afficher_face(f11);
  printf("\t voisins de face 11\n");  
  afficher_face(f11->f0);
  afficher_face(f11->f1);
  afficher_face(f11->f2);
}

int test_3(){
  face * f1;
  face * f2;
  face * f3;
  face * f4;
  face * f5;
  face * f6;
  face * f7;
  face * f8;
  sommet * a;
  sommet * b;
  sommet * c;
  sommet * d;
  sommet * e;
  sommet * f;
  sommet * g;
  sommet * h;
  liste_sommets L_sommet_tmp;
  face * ff1;
  face * fff1;
  face * ffff1;
  sommet * aa;
  printf("On redefinit le maillage afin de tester la fonction edge_collapse\n");
  init();
  a=creer_sommet(1,4,0,NULL);
  b=creer_sommet(3,4,0,NULL);
  c=creer_sommet(2,3,0,NULL);
  d=creer_sommet(0,2,0,NULL);
  e=creer_sommet(2,1,0,NULL);
  f=creer_sommet(4,2,0,NULL);
  g=creer_sommet(1,0,0,NULL);
  h=creer_sommet(4,0,0,NULL);
  f1=creer_face(a,c,b,NULL,NULL,NULL);
  f2=creer_face(b,c,f,NULL,NULL,NULL);
  f3=creer_face(a,d,c,NULL,NULL,NULL);
  f4=creer_face(d,g,e,NULL,NULL,NULL);
  f5=creer_face(g,h,e,NULL,NULL,NULL);
  f6=creer_face(e,h,f,NULL,NULL,NULL);
  f7=creer_face(c,d,e,NULL,NULL,NULL);
  f8=creer_face(c,e,f,NULL,NULL,NULL);
  printf("On a cree les faces, on les chaines.\n");
  chainer_face(f1,NULL,f2,f3);
  
  chainer_face(f2,NULL,f1,f8);
  
  chainer_face(f3,NULL,f1,f7);
  
  chainer_face(f4,NULL,f7,f5);
  
  chainer_face(f5,NULL,f4,f6);
  
  chainer_face(f6,NULL,f5,f8);
  
  chainer_face(f7,f3,f4,f8);
  
  chainer_face(f8,f2,f6,f7);
  /* printf("--------------------------------------------\n");
  printf("On tourne autout de c depart de f1\n");
  tourner_autour_sommet(c,f1);
  printf("--------------------------------------------\n");
  printf("On tourne autout de d depart en f3\n");
  tourner_autour_sommet(d,f3);
  printf("--------------------------------------------\n");
  printf("On tourne autout de d depart en f7\n");
  tourner_autour_sommet(d,f7);
  printf("--------------------------------------------\n");
  printf("On tourne autout de d depart en f4\n");
  tourner_autour_sommet(d,f4);*/
  
}


int test_4(){
  // on teste la fonction tourner_autour_sommet_et_changer_sommet
  face * f1;
  face * f2;
  face * f3;
  face * f4;
  face * f5;
  face * f6;
  face * f7;
  face * f8;
  sommet * a;
  sommet * b;
  sommet * c;
  sommet * d;
  sommet * e;
  sommet * f;
  sommet * g;
  sommet * h;
  sommet * i;
  liste_sommets L_sommet_tmp;
  face * ff1;
  face * fff1;
  face * ffff1;
  sommet * aa;
  printf("On redefinit le maillage afin de tester la fonction tourner_autour_sommet_et_changer_sommet\n");
  init();
  a=creer_sommet(1,4,0,NULL);
  b=creer_sommet(3,4,0,NULL);
  c=creer_sommet(2,3,0,NULL);
  d=creer_sommet(0,2,0,NULL);
  e=creer_sommet(2,1,0,NULL);
  f=creer_sommet(4,2,0,NULL);
  g=creer_sommet(1,0,0,NULL);
  h=creer_sommet(4,0,0,NULL);
  i=creer_sommet(2,2,0,NULL);
  f1=creer_face(a,c,b,NULL,NULL,NULL);
  f2=creer_face(b,c,f,NULL,NULL,NULL);
  f3=creer_face(a,d,c,NULL,NULL,NULL);
  f4=creer_face(d,g,e,NULL,NULL,NULL);
  f5=creer_face(g,h,e,NULL,NULL,NULL);
  f6=creer_face(e,h,f,NULL,NULL,NULL);
  f7=creer_face(c,d,e,NULL,NULL,NULL);
  f8=creer_face(c,e,f,NULL,NULL,NULL);
  printf("On a cree les faces, on les chaines.\n");
  chainer_face(f1,NULL,f2,f3);
  
  chainer_face(f2,NULL,f1,f8);
  
  chainer_face(f3,NULL,f1,f7);
  
  chainer_face(f4,NULL,f7,f5);
  
  chainer_face(f5,NULL,f4,f6);
  
  chainer_face(f6,NULL,f5,f8);
  
  chainer_face(f7,f3,f4,f8);
  
  chainer_face(f8,f2,f6,f7);

  printf("On affiche les faces \n");
  afficher_face(f4);
  afficher_face(f5);
  afficher_face(f6);
  afficher_face(f7);
  afficher_face(f8);


  printf("On teste la procedure \n");


  tourner_autour_sommet_et_changer_sommet(e,f4,i);

  printf("On affiche les faces \n");
  afficher_face(f4);
  afficher_face(f5);
  afficher_face(f6);
  afficher_face(f7);
  afficher_face(f8);

}


int test_6(){
  // on supprime puis reinsere (c,b)
  face * f1;
  face * f2;
  face * f3;
  face * f7;
 
  sommet * a;
  sommet * b;
  sommet * c;
  sommet * d;
  sommet * e;
  sommet * f;
  sommet * i;
  liste_sommets L_sommet_tmp;
  face * ff1;
  face * fff1;
  face * ffff1;
  sommet * aa;
  printf("On redefinit le maillage afin de tester la fonction edge_collapse\n");
  init();
  a=creer_sommet((float)1,(float)4,(float)0,creer_info());
  L_sommets=ajouter_sommet(a,L_sommets);

  b=creer_sommet((float)3,(float)4,(float)0,creer_info());
  L_sommets=ajouter_sommet(b,L_sommets);

  c=creer_sommet((float)2,(float)3,(float)0,creer_info());
  L_sommets=ajouter_sommet(c,L_sommets);

  d=creer_sommet((float)0,(float)2,(float)0,creer_info());
  L_sommets=ajouter_sommet(d,L_sommets);

  e=creer_sommet((float)2,(float)1,(float)0,creer_info());
  L_sommets=ajouter_sommet(e,L_sommets);

  f=creer_sommet((float)4,(float)2,(float)0,creer_info());
  L_sommets=ajouter_sommet(f,L_sommets);

  //creer_sommet(2,2,0,creer_info());
  //sommet=ajouter_sommmet(i,L_sommet);
  f1=creer_face(a,c,b,NULL,NULL,NULL);
  f2=creer_face(b,c,f,NULL,NULL,NULL);
  f3=creer_face(a,d,c,NULL,NULL,NULL);
  f7=creer_face(c,d,e,NULL,NULL,NULL);
  f8=creer_face(c,e,f,NULL,NULL,NULL);
  printf("On a cree les faces, on les chaines.\n");
  chainer_face(f1,NULL,f2,f3);
  
  chainer_face(f2,NULL,f1,f8);
  
  chainer_face(f3,NULL,f1,f7);
  
  chainer_face(f7,f3,NULL,f8);
  
  chainer_face(f8,f2,NULL,f7);

  printf("On teste la procedure edge_collapse losque l'on est au bord\n");
  i=edge_collapse(f2,f1,c,b,L_aretes_retirees);
  
  /*printf("On affiche les deux faces supprimees\n");
  afficher_face(f1);  
  afficher_face(f2);
    
  printf("On affiche les sommets \n");
  afficher_liste_sommet(L_sommets);

  printf("On affiche les faces \n");
  afficher_liste_face(L_faces);
  */
  
  printf("On teste la procedure vertex_split lorsque l'on est au bord\n");
  vertex_split(i);


  printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
   printf("On affiche les faces \n");
   afficher_liste_face(L_faces);
  
   printf("On verifie le chainage.\n");
  printf("face 1\n");
   afficher_face(f1);
  printf("\t voisins de face 1\n");  
  afficher_face(f1->f0);
  afficher_face(f1->f1);
  afficher_face(f1->f2);
  printf("test sur la face 2\n");
  printf("face 2\n");
  afficher_face(f2);
  printf("\t voisins de face 2\n");  
  afficher_face(f2->f0);
  afficher_face(f2->f1);
  afficher_face(f2->f2);
  printf("test sur la face 3\n");
  printf("face 3\n");
  afficher_face(f3);
  printf("\t voisins de face 3\n");  
  afficher_face(f3->f0);
  afficher_face(f3->f1);
  afficher_face(f3->f2);
  printf("test sur la face 7\n");
  printf("face 7\n");
  afficher_face(f7);
  printf("\t voisins de face 7\n");  
  afficher_face(f7->f0);
  afficher_face(f7->f1);
  afficher_face(f7->f2);
  printf("test sur la face 8\n");
  printf("face 8\n");
  afficher_face(f8);
  printf("\t voisins de face 8\n");  
  afficher_face(f8->f0);
  afficher_face(f8->f1);
  afficher_face(f8->f2); 
 
  // printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");   
 
}




int test_5(){
   // on supprime puis reinsere (e,f)
  face * f1;
  face * f2;
  face * f3;
  face * f4;
  face * f5;
  face * f6;
  face * f7;
  face * f8;
  sommet * a;
  sommet * b;
  sommet * c;
  sommet * d;
  sommet * e;
  sommet * f;
  sommet * g;
  sommet * h;
  sommet * i;
  liste_sommets L_sommet_tmp;
  face * ff1;
  face * fff1;
  face * ffff1;
  sommet * aa;
  printf("On redefinit le maillage afin de tester la fonction edge_collapse\n");
  init();
  a=creer_sommet((float)1,(float)4,(float)0,creer_info());
  L_sommets=ajouter_sommet(a,L_sommets);

  b=creer_sommet((float)3,(float)4,(float)0,creer_info());
  L_sommets=ajouter_sommet(b,L_sommets);

  c=creer_sommet((float)2,(float)3,(float)0,creer_info());
  L_sommets=ajouter_sommet(c,L_sommets);

  d=creer_sommet((float)0,(float)2,(float)0,creer_info());
  L_sommets=ajouter_sommet(d,L_sommets);

  e=creer_sommet((float)2,(float)1,(float)0,creer_info());
  L_sommets=ajouter_sommet(e,L_sommets);

  f=creer_sommet((float)4,(float)2,(float)0,creer_info());
  L_sommets=ajouter_sommet(f,L_sommets);

  g=creer_sommet((float)1,(float)0,(float)0,creer_info());
  L_sommets=ajouter_sommet(g,L_sommets);

  h=creer_sommet((float)4,(float)0,(float)0,creer_info());
  L_sommets=ajouter_sommet(h,L_sommets);
  //creer_sommet(2,2,0,creer_info());
  //sommet=ajouter_sommmet(i,L_sommet);
  f1=creer_face(a,c,b,NULL,NULL,NULL);
  f2=creer_face(b,c,f,NULL,NULL,NULL);
  f3=creer_face(a,d,c,NULL,NULL,NULL);
  f4=creer_face(d,g,e,NULL,NULL,NULL);
  f5=creer_face(g,h,e,NULL,NULL,NULL);
  f6=creer_face(e,h,f,NULL,NULL,NULL);
  f7=creer_face(c,d,e,NULL,NULL,NULL);
  f8=creer_face(c,e,f,NULL,NULL,NULL);
  printf("On a cree les faces, on les chaines.\n");
  chainer_face(f1,NULL,f2,f3);
  
  chainer_face(f2,NULL,f1,f8);
  
  chainer_face(f3,NULL,f1,f7);
  
  chainer_face(f4,NULL,f7,f5);
  
  chainer_face(f5,NULL,f4,f6);
  
  chainer_face(f6,NULL,f5,f8);
  
  chainer_face(f7,f3,f4,f8);
  
  chainer_face(f8,f2,f6,f7);

  printf("On teste la procedure edge_collapse losque l'on est au bord\n");
  i=edge_collapse(f7,f8,c,e,L_aretes_retirees);
  
  printf("On affiche les deux faces supprimees\n");
  afficher_face(f7);  
  afficher_face(f8);
    
  printf("On affiche les sommets \n");
  afficher_liste_sommet(L_sommets);

  printf("On affiche les faces \n");
  afficher_liste_face(L_faces);
  
  
  //printf("On teste la procedure vertex_split lorsque l'on est au bord\n");
  vertex_split(i);

   printf("On affiche les sommets \n");
  afficher_liste_sommet(L_sommets);


  printf("On affiche les faces \n");
  afficher_liste_face(L_faces);
  printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  printf("On affiche les faces \n");
  afficher_liste_face(L_faces);
  
   printf("On verifie le chainage.\n");
  afficher_face(f1);
  printf("\t voisins de face 1\n");  
  afficher_face(f1->f0);
  afficher_face(f1->f1);
  afficher_face(f1->f2);
  printf("test sur la face 2\n");
  printf("face 2\n");
  afficher_face(f2);
  printf("\t voisins de face 2\n");  
  afficher_face(f2->f0);
  afficher_face(f2->f1);
  afficher_face(f2->f2);
  printf("test sur la face 3\n");
  printf("face 3\n");
  afficher_face(f3);
  printf("\t voisins de face 3\n");  
  afficher_face(f3->f0);
  afficher_face(f3->f1);
  afficher_face(f3->f2);
  printf("test sur la face 4\n");
  printf("face 4\n");
  afficher_face(f4);
  printf("\t voisins de face 4\n");  
  afficher_face(f4->f0);
  afficher_face(f4->f1);
  afficher_face(f4->f2);
  printf("test sur la face 5\n");
  printf("face 5\n");
  afficher_face(f5);
  printf("\t voisins de face 5\n");  
  afficher_face(f5->f0);
  afficher_face(f5->f1);
  afficher_face(f5->f2);
  printf("test sur la face 6\n");
  printf("face 6\n");
  afficher_face(f6);
  printf("\t voisins de face 6\n");  
  afficher_face(f6->f0);
  afficher_face(f6->f1);
  afficher_face(f6->f2);
  printf("test sur la face 7\n");
  printf("face 7\n");
  afficher_face(f7);
  printf("\t voisins de face 7\n");  
  afficher_face(f7->f0);
  afficher_face(f7->f1);
  afficher_face(f7->f2);
  printf("test sur la face 8\n");
  printf("face 8\n");
  afficher_face(f8);
  printf("\t voisins de face 8\n");  
  afficher_face(f8->f0);
  afficher_face(f8->f1);
  afficher_face(f8->f2); 
 
 // printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");   
 
}


//////////////////////test 6//////////////////////
int main(int argc,char *argv[]){
  liste_faces LL;
  face *f1;
  sommet *S;
  if (argc!=3){
    printf("erreur dans le nombre de parametres : %d\n",argc);
    return 0;
  }
  else
    {
      init();
      printf("fichier en entree %s\n",argv[1]);
      acquisition(argv[1]);
      /*LL=L_faces;
      	printf("On affiche la liste des faces\n");
      afficher_liste_sommet(L_sommets);
      printf("On affiche la liste des sommets\n");
      afficher_liste_face(L_faces);
           printf("On verifie le chainage apres la fonction d'acquisition.\n");
      if (LL==NULL)
	printf("LL=NULL\n");

      while (LL!=NULL){
	printf("coucou");
	f1=LL->F;
	LL=LL->suiv;
	printf("\t face \n");
	afficher_face(f1);
	printf("\t voisins de face\n");  
	afficher_face(f1->f0);
	afficher_face(f1->f1);
	afficher_face(f1->f2);
      }
      */
       printf("On peut desormais supprimer une arete.\n");
      if (L_faces->F->f0!=NULL){
	printf("\t collapse 0 : on supprime les faces :\n");
	afficher_face(L_faces->F);
	afficher_face(L_faces->F->f0);
	S=edge_collapse(L_faces->F,L_faces->F->f0);
      }
      else
	if (L_faces->F->f1!=NULL){
	  S=edge_collapse(L_faces->F,L_faces->F->f1);
	  printf("\t collapse 1\n");
	}
	else
	  if (L_faces->F->f2!=NULL){
	    edge_collapse(L_faces->F,L_faces->F->f2);
	    printf("\t collapse 2\n");
      }
      afficher_liste_sommet(L_sommets);
      printf("On re-introduit le sommet que l'on vient de retirer\n");
      vertex_split(S);
      printf("fichier en sortie %s\n",argv[2]);
      sortie_OFF(argv[2]);
    
      printf("On affiche la liste des somets\n");
      afficher_liste_sommet(L_sommets);
      printf("On affiche la liste des faces\n");
      afficher_liste_face(L_faces);
      printf("On verifie le chainage en sortie\n");
      LL=L_faces;
  
      if (LL==NULL)
	printf("LL=NULL\n");
      /*
      while (LL!=NULL){
	printf("coucou");
	f1=LL->F;
	LL=LL->suiv;
	printf("\t face \n");
	afficher_face(f1);
	printf("\t voisins de face\n");  
	afficher_face(f1->f0);
	afficher_face(f1->f1);
	afficher_face(f1->f2);
      }
      */
    }

}





int main(){
  // teste la fonction collapse possible.
  face * f1;
  face * f2;
  face * f3;
  face * f4;
  face * f5;
  face * f6;
  face * f7;
  face * f8;
  sommet * a;
  sommet * b;
  sommet * c;
  sommet * d;
  sommet * e;
  sommet * f;
  sommet * g;
  sommet * h;
  sommet * i;

  printf("On redefinit le maillage afin de tester la fonction edge_collapse\n");
  init();
  a=creer_sommet((float)1,(float)4,(float)0,creer_info());
  L_sommets=ajouter_sommet(a,L_sommets);

  b=creer_sommet((float)3,(float)4,(float)0,creer_info());
  L_sommets=ajouter_sommet(b,L_sommets);

  c=creer_sommet((float)2,(float)3,(float)0,creer_info());
  L_sommets=ajouter_sommet(c,L_sommets);

  d=creer_sommet((float)0,(float)2,(float)0,creer_info());
  L_sommets=ajouter_sommet(d,L_sommets);

  e=creer_sommet((float)2,(float)1,(float)0,creer_info());
  L_sommets=ajouter_sommet(e,L_sommets);

  f1=creer_face(a,c,b,NULL,NULL,NULL);
  f2=creer_face(a,c,d,NULL,NULL,NULL);
  f3=creer_face(b,a,d,NULL,NULL,NULL);
  f4=creer_face(b,c,e,NULL,NULL,NULL);

  printf("On a cree les faces, on les chaines.\n");
 
  chainer_face(f1,f4,f2,f3);
  
  chainer_face(f2,NULL,f1,f3);
  
  chainer_face(f3,NULL,f1,f2);
  
  chainer_face(f4,NULL,f1,NULL);


  printf("On a chaine les chaines.\n");
  printf("collapse impossible : %d\n\n",autorisation_collapse(f1,f4));
  printf("collapse possible : %d\n\n",autorisation_collapse(f1,f3));

  init();
  a=creer_sommet((float)1,(float)4,(float)0,creer_info());
  L_sommets=ajouter_sommet(a,L_sommets);

  b=creer_sommet((float)3,(float)4,(float)0,creer_info());
  L_sommets=ajouter_sommet(b,L_sommets);

  c=creer_sommet((float)2,(float)3,(float)0,creer_info());
  L_sommets=ajouter_sommet(c,L_sommets);

  d=creer_sommet((float)0,(float)2,(float)0,creer_info());
  L_sommets=ajouter_sommet(d,L_sommets);

  e=creer_sommet((float)2,(float)1,(float)0,creer_info());
  L_sommets=ajouter_sommet(e,L_sommets);

  f=creer_sommet((float)4,(float)2,(float)0,creer_info());
  L_sommets=ajouter_sommet(f,L_sommets);

  g=creer_sommet((float)1,(float)0,(float)0,creer_info());
  L_sommets=ajouter_sommet(g,L_sommets);

  h=creer_sommet((float)4,(float)0,(float)0,creer_info());
  L_sommets=ajouter_sommet(h,L_sommets);
  //creer_sommet(2,2,0,creer_info());
  //sommet=ajouter_sommmet(i,L_sommet);
  f1=creer_face(a,c,b,NULL,NULL,NULL);
  f2=creer_face(b,c,f,NULL,NULL,NULL);
  f3=creer_face(a,d,c,NULL,NULL,NULL);
  f4=creer_face(d,g,e,NULL,NULL,NULL);
  f5=creer_face(g,h,e,NULL,NULL,NULL);
  f6=creer_face(e,h,f,NULL,NULL,NULL);
  f7=creer_face(c,d,e,NULL,NULL,NULL);
  f8=creer_face(c,e,f,NULL,NULL,NULL);
  printf("On a cree les faces, on les chaines.\n");
  chainer_face(f1,NULL,f2,f3);
  
  chainer_face(f2,NULL,f1,f8);
  
  chainer_face(f3,NULL,f1,f7);
  
  chainer_face(f4,NULL,f7,f5);
  
  chainer_face(f5,NULL,f4,f6);
  
  chainer_face(f6,NULL,f5,f8);
  
  chainer_face(f7,f3,f4,f8);
  
  chainer_face(f8,f2,f6,f7);


  printf("On a chaine les chaines.\n");
  printf("collapse possible : %d\n\n",autorisation_collapse(f8,f7));
  printf("collapse possible : %d\n\n",autorisation_collapse(f1,f2));

}
