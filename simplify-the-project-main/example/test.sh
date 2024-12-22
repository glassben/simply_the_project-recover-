#!/bin/sh

rm -f *.off
for fichier in `ls /NGB/`
do
    mkdir $fichier
    echo "------------------------"$fichier"--------------------"
    test_pm /NGB/$fichier test/res_$fichier.off 1000 test/tmp  > $fichier/res_$fichier
    echo "on compare la figure avant et apres le test"
    mv 0*.off $fichier/
done

