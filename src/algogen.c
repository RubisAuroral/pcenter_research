#include "../headers/algogen.h"
#include "../headers/algoevolutionnaire.h"

extern Population *pop;
extern int taille_reel;
extern int taille_total;
extern int nbnode;
extern int pcenters;
extern double tm;
extern int t;
extern Graph *g;

int parent(int rm, int max, int min){ //Renvoie la position dans le tableau du parent choisi selon une roulette russe
	int value=rand()%rm+1;
	for(int i=0; i<taille_reel; i++){
		value-=max-pop[i].Cout+min; //Permet de donner des plus grandes probabilités aux coûts faibles.
		if(value<0 || i==taille_reel-1){
			return i;
		}
	}
	return -1;
}

void Croissement(int p1, int p2, int k){ //A partir d'une solution p1 et d'une solution p2, cette fonction crée deux enfants qui prenent les "croissement" premiers bits de chacun des parents et les "nbnode-croissement" derniers bits de l'autre parent
	int pcroissement = nbnode/4+rand()%(nbnode/2);
	for(int i=0; i<pcroissement; i++){
		pop[taille_reel+2*k].centers[i] = (pop[p1].centers[i]) ? true : false;
		pop[taille_reel+2*k+1].centers[i]= (pop[p2].centers[i]) ? true : false;
	}
	
	for(int i=pcroissement; i<nbnode; i++){
		pop[taille_reel+2*k].centers[i] = (pop[p2].centers[i]) ? true : false;
		pop[taille_reel+2*k+1].centers[i]= (pop[p1].centers[i]) ? true : false;
	}
	correction(pop[taille_reel+2*k].centers, pop[p1].centers, pcroissement); correction(pop[taille_reel+2*k+1].centers, pop[p2].centers, pcroissement);
}

void correction(bool *center, bool *correcteur, int pcroissement){ //Rend une solution utilisable, c'est à dire avec le bon nombre de bit à 1 d'une solution ( qui sera à terme, défini dans l'instance lu )
	int p=count(center);
	while(p>pcenters){
		int rdm=rand()%(nbnode-pcroissement)+pcroissement;
		if(center[rdm] && !correcteur[rdm]){
			center[rdm]=false;
			p--;
		}
	}
	while(p<pcenters){
		int rdm=rand()%(nbnode-pcroissement)+pcroissement;
		if(!center[rdm] && correcteur[rdm]){
			center[rdm]=true;
			p++;
		}
	}
	return;	
}

void mutationv2(){ //Deuxième version de la mutation : On mute gène à gène
	int it=0;
	int rdm;
	for(int i=0; i<taille_total; i++){
		int save[nbnode];
		memset(save, 0, nbnode*sizeof(int));
		for(int k=0; k<nbnode; k++){
			it=0;
			double m=(double)rand()/(double)RAND_MAX;
			if(m<=tm){
				while(intab(save, k)==1 && k<nbnode) k++;
				if(k>=nbnode) break;
				save[k]=1;
				pop[i].centers[k]=!pop[i].centers[k];
				rdm=rand()%nbnode;
				while((intab(save, rdm) || pop[i].centers[k]!=pop[i].centers[rdm]) && it<2000){
					rdm=rand()%nbnode;
					it++;
				}
				if(it<2000) pop[i].centers[rdm]=!pop[i].centers[rdm];
				else pop[i].centers[k]=!pop[i].centers[k];
				
				/*VERSION PAS BELLE if(!pop[i].centers[k]){
					pop[i].centers[k]=true;
					rdm=rand()%nbnode;
					while((intab(save, rdm) || !pop[i].centers[rdm]) && it<2000){
						rdm=rand()%nbnode;
						it++;
					}
					if(it<2000) pop[i].centers[rdm]=false;
					else pop[i].centers[k]=false;
				}
				else{
					pop[i].centers[k]=false;
					rdm=rand()%nbnode;
					while((intab(save, rdm) || pop[i].centers[rdm]) && it<2000){
						rdm=rand()%nbnode;
						it++;
					}
					if(it<2000) pop[i].centers[rdm]=true;
					else pop[i].centers[k]=true;
				}*/
				
				save[rdm]=1;
			}
		}
		pop[i].Cout=costPCenter(g, pop[i].centers);
	}
}

void mutation(){ // On mute un bit dans sa forme 1-bit ( l'autre statut ) et on en remplace un autre par
	int rdm, rdm2;
	for(int i=taille_reel; i<taille_total; i++){
		double m=(double)rand()/(double)RAND_MAX;
		if(m<=tm && count(pop[i].centers)!=0){
			rdm=rand()%nbnode;
			pop[i].centers[rdm]=!pop[i].centers[rdm];
			rdm2=rand()%nbnode;
			while(pop[i].centers[rdm]!=pop[i].centers[rdm2] || rdm==rdm2) rdm2=rand()%nbnode;
			pop[i].centers[rdm2]=!pop[i].centers[rdm2];
			
			/*VERSION PAS BELLE if(!pop[i].centers[rdm]){
				pop[i].centers[rdm]=true;
				rdm2=rand()%nbnode;
				while(!(pop[i].centers[rdm2]) || rdm==rdm2) rdm2=rand()%nbnode;
				pop[i].centers[rdm2]=false;
			}
			else{
				pop[i].centers[rdm]=false;
				rdm2=rand()%nbnode;
				while(pop[i].centers[rdm2] || rdm==rdm2) rdm2=rand()%nbnode;
				pop[i].centers[rdm2]=true;
			}*/
			
		}
		pop[i].Cout=costPCenter(g, pop[i].centers);
	}
}


void algogen(int nbgen){ //Procède à l'algo génétique
        int s, max, min, bestcout, bestgen;
	for(int j=0; j<taille_reel; j++){
		initGen0(j);
		pop[j].Cout=costPCenter(g, pop[j].centers);
	}
	bestcout=pop[0].Cout; bestgen=0;
	for(int gen=1; gen<nbgen+1; gen++){
		s=sommeCout();
		max=borne(1);
		min=borne(0);
		for(int j=0; j<taille_reel/2; j++){
			Croissement(parent(s, max, min), parent(s, max, min), j);
		}
		mutation();
		qsort(pop, taille_total, sizeof(Population), comparator);
		freetab(taille_reel, taille_total);
		if(pop[0].Cout < bestcout){
			bestcout = pop[0].Cout;
			bestgen=gen;
		}
	}
	printf("%d;%d;", pop[0].Cout, bestgen);
	printSolution(pop[0].centers); 
	freeall();
}
