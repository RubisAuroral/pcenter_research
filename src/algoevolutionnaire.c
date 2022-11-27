#include "../headers/algoevolutionnaire.h"
#include "../headers/p_center.h"

extern Population *pop;
extern int taille_reel;
extern int taille_total;
extern int nbnode;
extern int pcenters;

int comparator(const void * a, const void * b){ //Fonction de comparaison utilisé pour faire le tri rapide ( ordre croissant )
	Population * val1 = (struct Population*)a;
	Population * val2 = (struct Population*)b;
	return val1->Cout - val2->Cout;
}

int sommeCout(){ //Renvoie la somme de tous les Cout - Fonction utilisé pour l'aléatoire de roulette russe, pour le choix des parents
	int somme;
	for(int i=0; i<taille_reel; i++){
		somme+=pop[i].Cout;
	}
	return somme;
}

void initstruct(){ //Initialise en mémoire la structure pop
	for(int j=0; j<taille_total; j++){
		pop[j].centers=(bool *)malloc(nbnode*sizeof(bool));
	}
}

int borne(int def){ // Permet d'obtenir ou le coût minimal, ou le coût maximal en fonction de l'entier pris en paramètre (1 pour le max, 0 pour le min)
	int min=pop[0].Cout, max=pop[0].Cout;
	for(int i=1; i<taille_reel; i++){ // définit le coût min et le coût max de l'ensemble de la population
		if(def==1){
			if(pop[i].Cout>max) max=pop[i].Cout;
		}
		else if(pop[i].Cout<min) min=pop[i].Cout;
	}
	if(def==1) return max;
	else return min;
}

void printSolution(bool *center){ //Affiche les pCenters d'une solution
	for(int k=0; k<nbnode; k++){
		if(center[k]){
			printf("%d ", k);
		}
		/*else{
			//printf("1");
			if(out!=NULL)fprintf(out, "1");
		}*/
	}
	printf("\n");
}

void printInBinary(bool *center){ //Affiche une solution sous sa forme binaire
	for(int k=0; k<nbnode; k++){
		if(center[k]) printf("1");
		else printf("0");
	}
	printf("\n");
}

int count(bool *center){ //Compte le nombre de 1 de la représentation binaire d'une solution
	int nb=0;
	for(int i=0; i<nbnode; i++) if(center[i]) nb++;
	return nb;
}

bool intab(int *tab, int n){ // Vérifie si un entier est dans un tableau. Retourne 1 si c'est le cas
	if(tab[n]==1) return true;
	return false;
}

void initGen0(int n){ //Initie la "génération 0" avec des solutions générés "aléatoirement"
	int p2=0;
	for(int k=0; k<nbnode; k++) pop[n].centers[k]=false;
	while(p2<pcenters){
		int r=rand()%nbnode;
		if(!pop[n].centers[r]){
			p2++;
			pop[n].centers[r]=true;
		}
	}
}

bool same(bool *center1, bool *center2){
	for(int k=0; k<nbnode; k++) if(center1[k]!=center2[k]) return false;
	return true;
}

void freetab(int bornemin, int bornemax){ // Remet les solutions "oubliables" à faux
	for(int i=bornemin; i<bornemax; i++){
		for(int k=0; k<nbnode; k++){
			pop[i].centers[k]=false;
		}
	}
}

void freeall(){ // Libère en mémoire la structure pop
	for(int i=taille_reel; i<taille_total; i++){
		free(pop[i].centers);
	}
	free(pop);
}
