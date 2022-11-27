#ifndef ALGOEVO_H_
#define ALGOEVO_H_

#include "../headers/p_center.h"

typedef struct Population Population;

struct Population{
	bool *centers;
	int Cout;
};

int sommeCout();
int comparator(const void * a, const void * b);
void initstruct();
int borne(int def);
void printInBinary(bool *center);
void printSolution(bool *center);
int count(bool *center);
bool intab(int *tab, int n);
void initGen0(int n);
bool same(bool *center1, bool *center2);
void freetab();
void freeall();

#endif
