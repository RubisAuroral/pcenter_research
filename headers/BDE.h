#ifndef BDE_H
#define BDE_H

#include "../headers/algoevolutionnaire.h"

void mutation_bde(int i);
void mutationv2_bde(int i);
void binomialCrossover(int i);
void selection(int i);
void correction_BDE(bool *center, bool *correcteur);
void correction_normal(int i);
void BDE(int nbgen);
#endif
