/*
	PROGRAMME REALISÉ PAR
	     MENET ALAN
*/

#include "headers/algogen.h"
#include "headers/BDE.h"
#include "headers/PBIL.h"

Population *pop;
int taille_reel;
int taille_total;
int nbnode;
int pcenters;
int t;
double tm;
double tc;
double ta;
Graph *g;

int main(int argc, char *argv[]){
        if(argc<10){
        	fprintf(stderr, "Pour lancer le script, faites la commande ./main -f filepath -p population -m taux mutation -G nbgen -g/b/pv\n");
        	exit(EXIT_FAILURE); 
        }
	int nbgen=0;
	char *file=NULL;
	bool tf=false, tG=false, tp=false, ttc=false, ttm=false, tta=false, pv=false, ag=false, b=false;
        for(int i=1; i<argc-1; i++){
        	if(!strcmp(argv[i], "-f")){
        		if(tf){
        			fprintf(stderr, "Vous avez mis deux -f\n");
        			exit(EXIT_FAILURE);
        		}
        		file = (char *) malloc(strlen(argv[i+1])*sizeof(char));
        		strcpy(file, argv[i+1]);
        		tf=true;
        	}
        	
        	if(!strcmp(argv[i],"-G")){
        		if(tG){
        			fprintf(stderr, "Vous avez mis deux -G\n");
        			exit(EXIT_FAILURE);
        		}
        		nbgen=atoi(argv[i+1]);
        		tG=true;	
        	}
        	
        	if(!strcmp(argv[i],"-p")){
        		if(tp){
        			fprintf(stderr, "Vous avez mis deux -p\n");
        			exit(EXIT_FAILURE);
        		}
        		taille_reel=atoi(argv[i+1]);
        		tp=true;
        	}
        	
        	if(!strcmp(argv[i],"-m")){
        		if(ttm){
        			fprintf(stderr, "Vous avez mis deux -m\n");
        			exit(EXIT_FAILURE);
        		}
        		tm=atof(argv[i+1])/100;
        		ttm=true;
        	}
        	
        	if(!strcmp(argv[i],"-c")){
        		if(ttc){
        			fprintf(stderr, "Vous avez mis deux -c\n");
        			exit(EXIT_FAILURE);
        		}
        		tc=atof(argv[i+1])/100;
        		ttc=true;	
        	}
        	
        	if(!strcmp(argv[i],"-a")){
        		if(tta){
        			fprintf(stderr, "Vous avez mis deux -a\n");
        			exit(EXIT_FAILURE);
        		}
        		ta=atof(argv[i+1]);
        		if(ta>0.1){
        			fprintf(stderr, "Votre taux d'apprentissage est trop élevé\n");
        			exit(EXIT_FAILURE);
        		}
        		tta=true;	
        	}
        	
        	if(!strcmp(argv[i],"-b") && (!pv || !ag)) b=true;
        	if(!strcmp(argv[i],"-pv") && (!b || !ag)) pv=true;
        	if(!strcmp(argv[i],"-g") && (!pv || !b)) ag=true;
        }
        if(!(tf && tG && tp)){
        	fprintf(stderr, "Mauvais arguments...\nIl vous faut -f filename -G nbgen -p population -m taux de mutation...\n");
        	exit(EXIT_FAILURE);
        }
        if(access(file, F_OK) == -1){
        	fprintf(stderr, "le fichier %s n'existe pas\n", file);
        	exit(EXIT_FAILURE);
        }
        if(taille_reel%2==1 && ag) taille_total=(taille_reel*2)-1;
        else taille_total=taille_reel*2;
        pop =(Population *) malloc(taille_total*sizeof(Population));
        g = initializeGraph(file);
        nbnode=g->nbVertices;
        pcenters = g->p;
        //afficherGraph(g); printf("\n");
        //afficherDistanceMatrix(g); printf("\n");
	t=time(NULL);
	srand(t); //randomize avec la seed t qui est soit l'heure, soit la valeur entrée en paramètre
	initstruct();
	for(int i=0; i<taille_total; i++){
		for(int j=0; j<nbnode; j++){
			pop[i].centers[j]=false;
		}
	}
	clock_t debut, fin;
	debut=clock();
	if(b){
		if(ttc && ttm) BDE(nbgen);
		else{
			fprintf(stderr, "Il vous manque -m ou -c pour lancer BDE\n");
        		exit(EXIT_FAILURE);
		}
	}
	if(ag){
		if(ttm) algogen(nbgen);
		else{
			fprintf(stderr, "Il vous manque -m pour lancer l'algogen\n");
        		exit(EXIT_FAILURE);
		}
	}
	if(pv){
		if(tta) PBIL(nbgen);
		else{
			fprintf(stderr, "Il vous manque -a pour lancer PBIL\n");
        		exit(EXIT_FAILURE);
		}
	}
	fin=clock();
	printf("%ldsec\n", (fin-debut)/CLOCKS_PER_SEC);
}
