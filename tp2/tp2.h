#ifndef TP2_C
#define TP2_C

#include <math.h>

#define p 3


//typedef int Fp_pol[p];

typedef struct{
	int degre;
	int *valeur;
}Fp_pol;

Fp_pol multi(Fp_pol poly1 , Fp_pol poly2, Fp_pol poly_mod, Fp_pol resultat);

#endif /*TP2_C*/
