#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "rho.h"

uint64_t func(uint64_t x, uint64_t a, uint64_t b, uint64_t *alpha, uint64_t *beta, uint64_t mod){
	switch( x%3 ){
		case 0:
			x = x * x % mod;
			*alpha = 2 * (*alpha) % (mod - 1);
			*beta = 2 * (*beta) % (mod - 1); 
			return x;
		case 1:
			x = x * a % mod;
			*alpha += 1 % (mod - 1);
			return x;
		case 2:
			x = x * b % mod;
			*beta += 1 % (mod - 1);
			return x;
		default:
			fprintf(stderr, "Not possible\n");
	}
	return x;
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

int64_t gcd(int64_t a, int64_t b){
	if(a<0){
		a *= (-1);
	}
	if(b<0){
		b *= (-1);
	}
	if( a == 0 ){
		return b;	
	}
	if( b == 0 ){
		return a;	
	}
	return gcd(b, a%b );
}

uint64_t rho_log(uint64_t h, uint64_t g, uint64_t mod){
	uint64_t alpha_x = 0, beta_x = 0, alpha_y = 0, beta_y = 0;
	uint64_t x = 1;
	uint64_t y = x;

	while(1){
		x = func(x, g, h, &alpha_x, &beta_x, mod);
		y = func(y, g, h, &alpha_y, &beta_y, mod);
		y = func(y, g, h, &alpha_y, &beta_y, mod);
		while( y != x ){
			x = func(x, g, h, &alpha_x, &beta_x, mod);
			y = func(y, g, h, &alpha_y, &beta_y, mod);
			y = func(y, g, h, &alpha_y, &beta_y, mod);
		}
		if( gcd(beta_x - beta_y, mod - 1) == 1 ){
			break;
		}
	}

	return (alpha_x - alpha_y) * inv_mod(beta_y - beta_x, mod - 1 ) % (mod - 1);
}