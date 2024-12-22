#!/bin/sh

i=0;

if test $# -eq 3
then
    rm -rf $3
    mkdir $3
 
    cd $3

    ~lenski/STAGE/Src/test_pm "../../NGB/"$1".NGB" "res.off" $2 "tmp.off"
    if test $2 -le 9
    then    
       borne=$2
    else
       borne=9
    fi
    
    while test $i -le $borne
    do
    mv "000"$i "res_"000$i".off"

    i=`expr $i + 1`
    done
    if test $2 -le 99
    then    
       borne=$2
    else
       borne=99
    fi
    
    while test $i -le  $borne
    do
    mv "00"$i "res_00"$i".off"

    i=`expr $i + 1`
    done
     
    if test $2 -le 999
    then    
       borne=$2
    else
       borne=999
    fi
    
    while test $i -le  $borne
    do
     mv "0"$i "res_"0$i".off"
	
    i=`expr $i + 1`
    done

    if test $2 -le 9999
    then    
       borne=$2
    else
       borne=9999
    fi
    
    while test $i -le  $borne
    do
    mv $i "res_"$i".off"

    i=`expr $i + 1`
    done

rm -f 1vs
rm -f fin_ec.off
rm -f res.off
rm -f base.off
else
echo "mauvais passage de parametres"
echo "Parametre 1 : nom du fichier .NGB dans le repertoire NGB"
echo "Parametre 2 : nombre d'aretes a supprimer"
echo "Paramatre 3 : nom du dossier a creer dans lequel vont etre rentre les resultats"

fi
  

