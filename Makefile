all: subconjuntos.o
	g++ -o subconjuntos subconjuntos.o

clean:
	rm *.o subconjuntos

