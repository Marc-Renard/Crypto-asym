#ifndef FP_POLY_H
#define FP_POLY_H

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

typedef struct{
	uint64_t degre;
	uint64_t carac;   // le p de Fp[X], l'espace dans lequel vivent ces polynômes
	uint64_t* coeffs; //big endian
}fp_poly_t;


int fp_poly_print(fp_poly_t *,char ,FILE *);

void fp_poly_free(fp_poly_t *);

fp_poly_t *fp_poly_init(uint64_t, uint64_t *, uint64_t);

fp_poly_t *fp_poly_mul(const fp_poly_t *,const fp_poly_t *);



#endif /*FP_POLY_H*/
