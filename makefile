CC=gcc
CFLAGS=-Wall
LDFLAGS=-lm

main: main.o algogen.o BDE.o PBIL.o algoevolutionnaire.o p_center.o
	$(CC) -o main main.o algogen.o BDE.o PBIL.o algoevolutionnaire.o p_center.o

main.o : main.c headers/algogen.h headers/BDE.h headers/PBIL.h
	$(CC) -o main.o -c main.c $(CFLAGS)
	
algogen.o : src/algogen.c headers/algogen.h headers/algoevolutionnaire.h
	$(CC) -o algogen.o -c src/algogen.c $(LDFLAGS) $(CFLAGS)

BDE.o : src/BDE.c headers/BDE.h headers/algoevolutionnaire.h
	$(CC) -o BDE.o -c src/BDE.c $(CFLAGS)
	
PBIL.o : src/PBIL.c headers/PBIL.h headers/algoevolutionnaire.h
	$(CC) -o PBIL.o -c src/PBIL.c $(CFLAGS)

algoevolutionnaire.o : src/algoevolutionnaire.c headers/algoevolutionnaire.h headers/p_center.h
	$(CC) -o algoevolutionnaire.o -c src/algoevolutionnaire.c $(LDFLAGS) $(CFLAGS)
	 
p_center.o : src/p_center.c headers/p_center.h
	$(CC) -o p_center.o -c src/p_center.c $(LDFLAGS) $(CFLAGS)

clean :
	\rm -fr *.o *~ main
