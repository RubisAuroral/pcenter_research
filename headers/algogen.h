#ifndef ALGOGEN_H_
#define ALGOGEN_H_

#include <time.h>
#include <unistd.h>
#include "../headers/algoevolutionnaire.h"

int parent(int rm, int max, int min);
void Croissement(int p1, int p2, int k);
void correction(bool *center, bool *correcteur, int pcroissement);
void mutationv2();
void mutation();
void algogen(int nbgen);

#endif
