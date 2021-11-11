#!/bin/bash
echo "Renomear soluções originais para .original?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) rename .sol .sol.original *.sol ;break;;
        No ) break;;
    esac
done

VALG () {
    valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s --log-file=valgrind_$(date +"%Y_%m_%d_%T").log $1 $2 ; 
    mv valgrind* valg
}

DIFF="diff -s"

input=$(ls *.in)
mkdir -p valg
rm -f valg/*

for F in ${input}; do 
    sleep 1;
     "./roap" "${F}";
done;

FILES=$(ls *.sol)

mkdir -p diffs
rm -f diffs/*

for F in ${FILES}; do
    ${DIFF} ${F} $( echo ${F}.original ) > diffs/$( echo ${F}.diff ) ;
done;

pDIFFS () {
    cat diffs/* | less -R --use-color -Dd+r -Du+b 
}

echo "Imprimir as diffs no terminal?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) clear; pDIFFS; break;;
        No ) break;;
    esac
done

pVALG () {
    cat valg/* | less -R --use-color -Dd+r -Du+b
}

echo "Ver os logs do valgrind?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) pVALG; break;;
        No ) break;;
    esac
done

echo "Apagar soluções do programa (as originais mantêm-se)?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) rm -f *.sol ;break;;
        No ) exit;;
    esac
done
