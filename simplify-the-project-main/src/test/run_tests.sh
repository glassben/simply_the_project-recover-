total_error=0
initial_time=$(date +%s%N)

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' #Neutral Color

echo "==================== TESTS UNITAIRES ===================="

echo ""

echo "==================== Acquisition ===================="

start_timer=$(date +%s%N)

passed=0
total=0

for file in test_acquisition/*.py
do
    if python3 $file 2>&1 \
    | grep -q -e "Error"
    then
        echo -ne "${RED}[FAILED]${NC}   : ${file##*/}       \n"
        total_error=$((total_error + 1))
    else
        echo -ne "${GREEN}[PASSED]${NC}   : ${file##*/}       \n"
        passed=$((passed + 1))
    fi
    total=$((total + 1))
done

echo -e "Temps d'exécution : $(echo "scale=3; ($(date +%s%N) - $start_timer) / 1000000000" | bc) s"
echo -ne "[Total : $passed/$total]  \n"

echo "==================== Affichage des maillages ===================="

start_timer=$(date +%s%N)

passed=0
total=0

for file in test_affiche_mesh/*.py
do
    if python3 $file 2>&1 \
    | grep -q -e "Error"
    then
        echo -ne "${RED}[FAILED]${NC}   : ${file##*/}       \n"
        total_error=$((total_error + 1))
    else
        echo -ne "${GREEN}[PASSED]${NC}   : ${file##*/}       \n"
        passed=$((passed + 1))
    fi
    total=$((total + 1))
done

echo -e "Temps d'exécution : $(echo "scale=3; ($(date +%s%N) - $start_timer) / 1000000000" | bc) s"
echo -ne "[Total : $passed/$total]  \n"

echo "==================== Structure de tas ===================="

start_timer=$(date +%s%N)

passed=0
total=0

for file in test_error_heap/*.py
do
    if python3 $file 2>&1 \
    | grep -q -e "Error"
    then
        echo -ne "${RED}[FAILED]${NC}   : ${file##*/}       \n"
        total_error=$((total_error + 1))
    else
        echo -ne "${GREEN}[PASSED]${NC}   : ${file##*/}       \n"
        passed=$((passed + 1))
    fi
    total=$((total + 1))
done

echo -e "Temps d'exécution : $(echo "scale=3; ($(date +%s%N) - $start_timer) / 1000000000" | bc) s"
echo -ne "[Total : $passed/$total]  \n"

echo "==================== Calcul des coûts ===================="

start_timer=$(date +%s%N)

passed=0
total=0

for file in test_errors/*.py
do
    if python3 $file 2>&1 \
    | grep -q -e "Error"
    then
        echo -ne "${RED}[FAILED]${NC}   : ${file##*/}       \n"
        total_error=$((total_error + 1))
    else
        echo -ne "${GREEN}[PASSED]${NC}   : ${file##*/}       \n"
        passed=$((passed + 1))
    fi
    total=$((total + 1))
done

echo -e "Temps d'exécution : $(echo "scale=3; ($(date +%s%N) - $start_timer) / 1000000000" | bc) s"
echo -ne "[Total : $passed/$total]  \n"

echo "==================== Manipulation des maillages ===================="

start_timer=$(date +%s%N)

passed=0
total=0

for file in test_mesh_manipulation/*.py
do
    if python3 $file 2>&1 \
    | grep -q -e "Error"
    then
        echo -ne "${RED}[FAILED]${NC}   : ${file##*/}       \n"
        total_error=$((total_error + 1))
    else
        echo -ne "${GREEN}[PASSED]${NC}   : ${file##*/}       \n"
        passed=$((passed + 1))
    fi
    total=$((total + 1))
done

echo -e "Temps d'exécution : $(echo "scale=3; ($(date +%s%N) - $start_timer) / 1000000000" | bc) s"
echo -ne "[Total : $passed/$total]  \n"

echo "==================== Synthèse ===================="

echo -e "Temps total d'exécution : $(echo "scale=3; ($(date +%s%N) - $initial_time) / 1000000000" | bc) s"

if [ $total_error -eq 0 ]
then
    echo -e "${GREEN}Tous les tests ont été passés avec succès !${NC}"
    exit 0
else
    echo -e "${RED} Nombre de tests ratés : $total_error ${NC}"
    exit 1
fi