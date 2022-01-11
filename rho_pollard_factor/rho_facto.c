#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "rho_facto.h"


INT f(INT a, INT n){
	return (a*a + 1)%n;
}



INT gcd(INT a, INT b){
	if( a == 0){
		return b;	
	}
	if( b == 0){
		return a;	
	}
	return gcd(b, a%b);
}


INT rho_factor(INT n){
	if( !(n&1)){
		return 2;	
	}
	INT x_j = 1, max = 1, cmpt = 0;
	INT x_k = x_j;
	while(1){
		if( cmpt == max){
			max <<= 1;
			x_j = x_k;		
		}
		x_k = f( x_k, n);
		cmpt++;
		INT g = gcd( x_k - x_j, n);
		if( ( g != 1) && ( g != n)){
			return g;
		}
	}
}


void mpz_f(mpz_t a, mpz_t n){
	mpz_t tmp, res;
	mpz_inits(res, tmp,NULL);

	mpz_mul(tmp, a, a);
	mpz_add_ui(res, tmp, 1);
	mpz_mod(a, res, n);

	mpz_clears(tmp, res,NULL);	
}

void mpz_rho_factor(mpz_t factor ,mpz_t n){
	/*
	if( mpz_divisible_ui_p( n, 2)){
		mpz_set_ui(factor, 2);
		return;	
	}
	*/	

	INT cmpt = 0, max = 1;
	mpz_t tmp, x_j, x_k;
	mpz_inits(tmp, x_k, x_j,NULL);

	mpz_set_ui(x_k,1);
	mpz_set(x_j, x_k);
	while(1){
		if( max == cmpt){
			max<<=1;
			mpz_set(x_j, x_k);		
		}
		mpz_f(x_k, n);	//x_k = f(x_k,n)
		
		cmpt++;
		
		mpz_sub(tmp, x_k, x_j);
		mpz_gcd( factor ,tmp, n);
		if( mpz_cmp_ui(factor, 1) && mpz_cmp(factor,n) ){
			break;
		}
	}
	mpz_clears(tmp, x_j, x_k, NULL);
}

