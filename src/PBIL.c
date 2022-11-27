#include "../headers/PBIL.h"
#include "../headers/algoevolutionnaire.h"

extern Population *pop;
extern int taille_reel;
extern int taille_total;
extern int nbnode;
extern int pcenters;
extern double ta;
extern Graph *g;

void initpv(double *p){ // On initialise le tableau de probabilité à 0.5 pour chaque gène
	for(int i=0; i<nbnode; i++) p[i]=0.5;
}

double sommep(double *p){ // Fait la somme de toutes les valeurs du tableau de probabilité
	double sp=0;
	for(int i=0; i<nbnode; i++) sp+=p[i];
	return sp;
} 

void generateSolution(double *p, int i, double mrdm){ // Suivant le vecteur de probabilité qu'on a, passe un bit à 1
	double rdm = (double)rand() / (double)(RAND_MAX / mrdm);
	for(int j=0; j<nbnode; j++){
		rdm-=p[j];
		if(rdm<=0){
			pop[i].centers[j]=true;
			return;
		}
	}
}

void PBIL(int nbgen){
	double *p=(double *)malloc(nbnode*sizeof(double));
	initpv(p);
	Population best;
	best.centers=(bool *)malloc(nbnode*sizeof(bool));
	int bestgen;
	best.Cout=9999;
	for(int gen=1; gen<nbgen+1; gen++){
		double sommeproba=sommep(p);
		for(int i=0; i<taille_total; i++){
			while(count(pop[i].centers)!=pcenters){ //Tant qu'on a pas le bon nombre de pcentre, place un bit à 1
				generateSolution(p, i, sommeproba);
			}
			pop[i].Cout=costPCenter(g, pop[i].centers);
		}
		qsort(pop, taille_total, sizeof(Population), comparator);
		if(pop[0].Cout<best.Cout){
			best.Cout=pop[0].Cout;
			for(int j=0; j<nbnode; j++) best.centers[j]=pop[0].centers[j];
			bestgen=gen;
		}
		for(int i=0; i<=taille_total/100; i++){ //Met à jour le vecteur de probabilité sur les 1% meilleurs
			for(int j=0; j<nbnode; j++){
				p[j]=p[j]*(1-ta)+pop[i].centers[j]*ta;
			}
		}
		if(gen!=nbgen) freetab(0, taille_total); // réinitialise toutes les solutions : On ne les garde pas sauf à la dernière génération.
	}
	printf("%d;", pop[0].Cout);
	printf("%d;", bestgen);
	printSolution(pop[0].centers);
	freeall();
	/*printf("\n\n");
	for(int i=0; i<nbnode; i++){
		printf("%.3f ", p[i]);
	}
	printf("\n");*/
}
