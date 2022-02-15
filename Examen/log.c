#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include <gmp.h>


void f(mpz_t y, mpz_t x){
	mpz_mod_ui(y, x, 13);
}


void next(mpz_t x, mpz_t g, mpz_t d, mpz_t n){
	mpz_t tmp;
	mpz_init(tmp);
	f(tmp, x); //tmp = f(x)
	mpz_add(d, d, tmp); //d = d + f(x)
	mpz_powm(tmp, g, tmp , n); //tmp = g^f(x)
	mpz_mul(x, x, tmp); //x = x*g^f(x)
	mpz_clear(tmp);
}

void x_n(mpz_t x, mpz_t d, mpz_t g, mpz_t b, mpz_t N, mpz_t n){
	mpz_t counter, tmp;
	mpz_init(tmp);
	mpz_init_set_ui(counter, 0);
	mpz_powm(x, g, b, n);
	mpz_set_ui(d, 0);
	while( mpz_cmp(counter,N) < 0 ){
		next(x, g, d, n);
		mpz_add_ui(counter, counter, 1);
	}
	mpz_clears(counter, tmp, NULL);
}

void logarithme(mpz_t alpha, mpz_t h, mpz_t g, mpz_t a, mpz_t b, mpz_t N, mpz_t n){
	mpz_t x, d;
	mpz_inits(x, d, NULL);
	x_n(x, d, g, b, N, n);

	mpz_t y, dj, lim;
	mpz_inits(y, dj, lim, NULL);
	mpz_set_ui(dj, 0);
	mpz_set(y, h);
	mpz_sub(lim, b, a);
	mpz_add(lim, lim, d);

	while( !(mpz_cmp(x, y)) && !(mpz_cmp(dj, lim) > 0) ){
		next(y, g, dj, n);
	}
	if( !(mpz_cmp(x,y)) ){
		mpz_add(alpha, d, b);
		mpz_sub(alpha, alpha, dj);
		fprintf(stdout, "Succes\n");
		
	} else { 
		fprintf(stdout, "Echec\n");
	}


	mpz_clears(x, d, NULL);
	mpz_clears(y, dj, lim, NULL);

}