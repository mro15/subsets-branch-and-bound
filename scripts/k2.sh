#!/bin/bash

CASES='ls instancias/*100.txt'

echo $CASES

for ca in ${CASES[@]}; do
	MEE=${ca##*/}
	ME="${MEE%.[^.]*}"
	head -n 5 $ca >>  entradas/k2/$ME.5.txt
done


CASES1='ls instancias/*500.txt'

echo $CASES1

for ca in ${CASES1[@]}; do
	MEE=${ca##*/}
	ME="${MEE%.[^.]*}"
	head -n 10 $ca >>  entradas/k2/$ME.10.txt
done


CASES2='ls instancias/*1000.txt'

echo $CASES2

for ca in ${CASES2[@]}; do
	MEE=${ca##*/}
	ME="${MEE%.[^.]*}"
	head -n 15 $ca >>  entradas/k2/$ME.15.txt
done

CASES3='ls instancias/*5000.txt'

echo $CASES3

for ca in ${CASES3[@]}; do
	MEE=${ca##*/}
	ME="${MEE%.[^.]*}"
	head -n 18 $ca >>  entradas/k2/$ME.18.txt
done

CASES4='ls instancias/*10000.txt'

echo $CASES4

for ca in ${CASES4[@]}; do
	MEE=${ca##*/}
	ME="${MEE%.[^.]*}"
	head -n 25 $ca >>  entradas/k2/$ME.25.txt
done
