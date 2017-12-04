#!/bin/bash

CASES=$(ls entradas/k5/*.5.txt)

echo $CASES

for ca in ${CASES[@]}; do
	MEE=${ca##*/}
	ME="${MEE%.[^.]*}"
	time (./subconjuntos 5 5 $ca 1) >  resultados/k5/$ME.1.txt 2>&1
	time (./subconjuntos 5 5 $ca 2) >  resultados/k5/$ME.2.txt 2>&1
done


CASES1=$(ls entradas/k5/*.8.txt)

echo $CASES

for ca in ${CASES1[@]}; do
	MEE=${ca##*/}
	ME="${MEE%.[^.]*}"
	time (./subconjuntos 8 5 $ca 1) >  resultados/k5/$ME.1.txt 2>&1
	time (./subconjuntos 8 5 $ca 2) >  resultados/k5/$ME.2.txt 2>&1
done


CASES2=$(ls entradas/k5/*.10.txt)

echo $CASES2

for ca in ${CASES2[@]}; do
	MEE=${ca##*/}
	ME="${MEE%.[^.]*}"
	time (./subconjuntos 10 5 $ca 1) >  resultados/k5/$ME.1.txt 2>&1
	time (./subconjuntos 10 5 $ca 2) >  resultados/k5/$ME.2.txt 2>&1
done

CASES3=$(ls entradas/k5/*.12.txt)

echo $CASES3

for ca in ${CASES3[@]}; do
	MEE=${ca##*/}
	ME="${MEE%.[^.]*}"
	time (./subconjuntos 12 5 $ca 1) >  resultados/k5/$ME.1.txt 2>&1
	time (./subconjuntos 12 5 $ca 2) >  resultados/k5/$ME.2.txt 2>&1
done

CASES4=$(ls entradas/k5/*.13.txt)

echo $CASES4

for ca in ${CASES4[@]}; do
	MEE=${ca##*/}
	ME="${MEE%.[^.]*}"
	time (./subconjuntos 13 5 $ca 1) >  resultados/k5/$ME.1.txt 2>&1
	time (./subconjuntos 13 5 $ca 2) >  resultados/k5/$ME.2.txt 2>&1
done
