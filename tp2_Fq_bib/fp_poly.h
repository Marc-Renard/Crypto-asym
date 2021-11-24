#ifndef FP_POLY_H
#define FP_POLY_H

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

typedef struct{
	uint64_t degre;
	uint64_t carac;   // le p de Fp[X], l'espace dans lequel vivent ces polynômes
	uint64_t *coeffs; //big endian, le coefficiant dominant doit être non nul modulo carac sauf pour le polynôme identiquement nul
}fp_poly_t;


int fp_poly_print(fp_poly_t *,char ,FILE *);

void fp_poly_free(fp_poly_t *);

fp_poly_t *fp_poly_init(uint64_t, uint64_t *, uint64_t);

fp_poly_t *fp_poly_mul(const fp_poly_t *,const fp_poly_t *);

fp_poly_t *fp_poly_add(const fp_poly_t *,const fp_poly_t *);

fp_poly_t *fp_poly_sub(const fp_poly_t *,const fp_poly_t *);

int64_t inv_mod(int64_t, int64_t);

void fp_poly_div_euc(const fp_poly_t *,const fp_poly_t *, fp_poly_t **, fp_poly_t **);

void fp_poly_gcd(const fp_poly_t *,const fp_poly_t *, fp_poly_t **);


#endif /*FP_POLY_H*/
