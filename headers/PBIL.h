#ifndef PBIL_H
#define PBIL_H

#include "../headers/algoevolutionnaire.h"

void initpv(double *p);
double sommep(double *p);
void generateSolution(double *p, int i, double mrdm);
void PBIL(int nbgen);

#endif
