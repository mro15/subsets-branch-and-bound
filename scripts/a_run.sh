#!/bin/bash

CASES=$(ls entradas/k2/*.5.txt)

echo $CASES

for ca in ${CASES[@]}; do
	MEE=${ca##*/}
	ME="${MEE%.[^.]*}"
	time (./subconjuntos 5 2 $ca 1) >  resultados/k2/$ME.1.txt 2>&1
	time (./subconjuntos 5 2 $ca 2) >  resultados/k2/$ME.2.txt 2>&1
done


CASES1=$(ls entradas/k2/*.10.txt)

echo $CASES

for ca in ${CASES1[@]}; do
	MEE=${ca##*/}
	ME="${MEE%.[^.]*}"
	time (./subconjuntos 10 2 $ca 1) >  resultados/k2/$ME.1.txt 2>&1
	time (./subconjuntos 10 2 $ca 2) >  resultados/k2/$ME.2.txt 2>&1
done


CASES2=$(ls entradas/k2/*.15.txt)

echo $CASES2

for ca in ${CASES2[@]}; do
	MEE=${ca##*/}
	ME="${MEE%.[^.]*}"
	time (./subconjuntos 15 2 $ca 1) >  resultados/k2/$ME.1.txt 2>&1
	time (./subconjuntos 15 2 $ca 2) >  resultados/k2/$ME.2.txt 2>&1
done

CASES3=$(ls entradas/k2/*.18.txt)

echo $CASES3

for ca in ${CASES3[@]}; do
	MEE=${ca##*/}
	ME="${MEE%.[^.]*}"
	time (./subconjuntos 18 2 $ca 1) >  resultados/k2/$ME.1.txt 2>&1
	time (./subconjuntos 18 2 $ca 2) >  resultados/k2/$ME.2.txt 2>&1
done

CASES4=$(ls entradas/k2/*.25.txt)

echo $CASES4

for ca in ${CASES4[@]}; do
	MEE=${ca##*/}
	ME="${MEE%.[^.]*}"
	time (./subconjuntos 25 2 $ca 1) >  resultados/k2/$ME.1.txt 2>&1
	time (./subconjuntos 25 2 $ca 2) >  resultados/k2/$ME.2.txt 2>&1
done
