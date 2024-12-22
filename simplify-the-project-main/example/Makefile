pm_prog.o : pm_prog.c
	gcc -c pm_prog.c

pm_prog :  pm_prog.o pm.o sortie.o acquisition.o test_pm.o sortie_bis.o test.o listes.o information.o
	gcc -o  pm_prog pm_prog.o sortie.o acquisition.o pm.o constructeurs.o sortie_bis.o test.o listes.o information.o	

pm : pm.o constructeurs.o sortie.o acquisition.o  test.o listes.o information.o
	gcc -o pm pm.o constructeurs.o sortie.o acquisition.o  test.o listes.o information.o

test_pm.o : test_pm.c
	gcc -c test_pm.c


test_pm : pm.o sortie.o acquisition.o test_pm.o sortie_bis.o test.o listes.o information.o
	gcc -o  test_pm test_pm.o sortie.o acquisition.o pm.o constructeurs.o sortie_bis.o test.o listes.o information.o

information.o : information.c
	gcc -c information.c


constructeurs.o : constructeurs.c information.c
	gcc -c constructeurs.c


pm.o : pm.c constructeurs.o 
	gcc -c pm.c

test.o : test.c 
	gcc -c test.c

listes.o : listes.c
	gcc -c listes.c


acquisition.o : acquisition.c
	gcc -c acquisition.c


acquisition : acquisition.o constructeurs.o 
	gcc -o acquisition acquisition.o constructeurs.o


sortie_bis.o : sortie_bis.c sortie_bis.h
	gcc -c sortie_bis.c

sortie.o : sortie.c sortie.h
	gcc -c sortie.c


test_acquisition_sortie : test_acquisition_sortie.o  sortie.o acquisition.o test.o listes.o
	gcc -o test_acquisition_sortie test_acquisition_sortie.o sortie.o acquisition.o  constructeurs.o test.o listes.o

test_acquisition_sortie.o : test_acquisition_sortie.c
	gcc -c test_acquisition_sortie.c


