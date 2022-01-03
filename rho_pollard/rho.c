#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "rho.h"


void f(uint64_t *x, uint64_t a, uint64_t b, uint64_t *alpha, uint64_t *beta, uint64_t mod){
	switch( (*x)%3 ){
		case 0:
			*x = (*x) * (*x) % mod;
			*alpha = 2 * (*alpha);
			*beta = 2 * (*beta); 
			break;
		case 1:
			*x = (*x) * a % mod;
			*alpha += 1;
			break;
		case 2:
			*x = (*x) * b % mod;
			*beta += 1;
			break;
	}
}



//Inverse modulo p
int64_t inv_mod(int64_t a, int64_t p){
	int64_t u0 = 1, u1 = 0, r0 = a, r1 = p;
	int64_t u_tmp, r_tmp, q;
	while(r1 != 0){
		q = r0 / r1;
		r_tmp = r0;
		u_tmp = u0;
		r0 = r1;
		u0 = u1;
		r1 = r_tmp - q * r1;
		u1 = u_tmp - q * u1;
	}
	return (u0 + p)%p;
}

