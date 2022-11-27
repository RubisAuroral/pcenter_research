#include "../headers/BDE.h"
#include "../headers/algoevolutionnaire.h"

extern Population *pop;
extern int taille_reel;
extern int nbnode;
extern int pcenters;
extern double tm;
extern double tc;
extern int t;
extern Graph *g;

void mutation_bde(int i){ //Procède à la mutation de base de BDE : Selon une probabilité et une condition, il prendra le gène de la solution rdm, soit il prendra son inverse
	int rdm=rand()%taille_reel;
	int rdm2=rand()%taille_reel;
	int rdm3=rand()%taille_reel;
	while(rdm==i) rdm=rand()%taille_reel;
	while(rdm2==i || rdm2==rdm) rdm2=rand()%taille_reel;
	while(rdm3==i || rdm3==rdm2 || rdm3==rdm) rdm3=rand()%taille_reel;
	for(int j=0; j<nbnode; j++){
		double m=(double)rand()/(double)RAND_MAX;
		if(pop[rdm2].centers[j]!=pop[rdm3].centers[j] && m<tm /*A définir*/) pop[taille_reel+i].centers[j]=!pop[rdm].centers[j];
		else pop[taille_reel+i].centers[j]=pop[rdm].centers[j];
	}
	correction_BDE(pop[taille_reel+i].centers, pop[rdm].centers);
}

void mutationv2_bde(int i){ //Mutation modifié de BDE : Les indices rdm; rdm2 et rdm3 sont générés à chaque itération de la boucle et non avant le début de la boucle
	for(int j=0; j<nbnode; j++){
		int rdm=rand()%taille_reel;
		int rdm2=rand()%taille_reel;
		int rdm3=rand()%taille_reel;
		while(rdm==i) rdm=rand()%taille_reel;
		while(rdm2==i || rdm2==rdm) rdm2=rand()%taille_reel;
		while(rdm3==i || rdm3==rdm2 || rdm3==rdm) rdm3=rand()%taille_reel;
		double m=(double)rand()/(double)RAND_MAX;
		if(pop[rdm2].centers[j]!=pop[rdm3].centers[j] && m<tm /*A définir*/) pop[taille_reel+i].centers[j]=!pop[rdm].centers[j];
		else pop[taille_reel+i].centers[j]=pop[rdm].centers[j];
	}
	correction_normal(i);
}

void binomialCrossover(int i){ //Réalise le binomial crossover : Selon une probabilité, la nouvelle solution prendra soit le gène du mutant d'indice i, soit celui de la solution de même indice
	bool *correcteur = (bool *)malloc(nbnode*sizeof(bool));;
	for(int j=0; j<nbnode; j++){
		correcteur[j]=pop[taille_reel+i].centers[j];
		double c=(double)rand()/(double)RAND_MAX;
		if(c>tc /*A définir*/) pop[taille_reel+i].centers[j]=pop[i].centers[j];
	}
	correction_BDE(pop[taille_reel+i].centers, correcteur);
}

void selection(int i){ //Pour un indice i, il garde la meilleure solution entre l'individu nouvellement crée et l'individu d'origine : Celui qui a le meilleur coût.
	if(pop[i].Cout>pop[taille_reel+i].Cout){
		for(int j=0; j<nbnode; j++) pop[i].centers[j]=pop[taille_reel+i].centers[j];
		pop[i].Cout=pop[taille_reel+i].Cout;
	}
}

void correction_BDE(bool *center, bool *correcteur){ //Lorsqu'une solution a trop ou pas assez de pcentre, on sélectionne des bits de correcteur pour remettre au bon nombre la solution center
	int p=count(center);
	while(p>pcenters){
		int rdm=rand()%nbnode;
		if(center[rdm] && !correcteur[rdm]){
			center[rdm]=false;
			p--;
		}
	}
	while(p<pcenters){
		int rdm=rand()%nbnode;
		if(!center[rdm] && correcteur[rdm]){
			center[rdm]=true;
			p++;
		}
	}
}

void correction_normal(int i){ //Lorsqu'une solution a trop ou pas assez de pcentre, il ajoute/retire aléatoirement suffisamment de pcentre pour que la solution devienne "correcte"
	int p=count(pop[taille_reel+i].centers);
	while(p>pcenters){
		int rdm=rand()%nbnode;
		if(pop[taille_reel+i].centers[rdm]){
			pop[taille_reel+i].centers[rdm]=false;
			p--;
		}
	}
	while(p<pcenters){
		int rdm=rand()%nbnode;
		if(!pop[taille_reel+i].centers[rdm]){
			pop[taille_reel+i].centers[rdm]=true;
			p++;
		}
	}
}

void BDE(int nbgen){
	Population best; int bestgen=0;
	best.Cout=4000;
	for(int j=0; j<taille_reel; j++){
		initGen0(j);
		pop[j].Cout=costPCenter(g, pop[j].centers);
	}
	for(int gen=1; gen<nbgen+1; gen++){
		for(int i=0; i<taille_reel; i++){
			mutation_bde(i);
			binomialCrossover(i);
			if(!same(pop[i].centers, pop[taille_reel+i].centers)){
				pop[taille_reel+i].Cout=costPCenter(g, pop[taille_reel+i].centers);
				if(pop[taille_reel+i].Cout<best.Cout){
					best=pop[taille_reel+i];
					bestgen=gen;
				}
				selection(i);
			}
		}
	}
	qsort(pop, taille_reel, sizeof(Population), comparator);
	printf("%d;", pop[0].Cout);
	printf("%d;", bestgen);
	printSolution(pop[0].centers);
	freeall();
	/*printf("\n");
	printf("%d\n", best.Cout);
	printSolution(best.centers);*/
}
