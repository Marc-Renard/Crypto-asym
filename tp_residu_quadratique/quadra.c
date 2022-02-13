#include <stdint.h>
#include <stdio.h>
#include "quadra.h"


uint64_t exp_bin_mod(uint64_t n, uint64_t power, uint64_t mod){
	uint64_t res = 1;
	while(power){ //ie while power!=0
		if( power & 1 ){ //power est impair
			res = (res * n ) % mod;
		}
		n = (n * n) % mod;
		power >>= 1;
	}
	return res;
}

int parite(uint64_t a){
	int compteur = 0;
	while(a>0){
		if(a & 1){
			compteur ^= 1; // + 1 mod 2
		}
		a >>= 1;
	}
	return compteur;
}

int jacobi(int64_t a,uint64_t p){
    if(a<0){
        return(jacobi(a+p,p));
    }
    if(a==1){
        return 1;
    }
    if(a==2){
    	return -1 + 2 * parite( p & 0b111 );
    }
    if(p%a==0){
        return 0;
    }
    if(a%2==0){
    	// p^2-1 mod 8 = +- 1 <=> p^2-1 & 0b111 = 0b001 ou 0b111 soit parite(p^2-1 & 0b111) = 1
    	// p^2-1 mod 8 = +- 3 <=> p^2-1 & 0b111 = 0b101 ou 0b011 soit parite(p^2-1 & 0b111) = 0
        return((jacobi(a/2,p))*(-1 + 2 * parite( p & 0b111 ) )); // (-1)^( (p^2-1)/8 )
    }else{
    	//On ne doit multiplier par -1 que si a = p = 3 mod 4 soit : les deux derniers bits de a et p sont tous des 1
        return((jacobi(p%a,a))*(1 - 2 * ( ( a & 1 ) * ( ( a >> 1 ) & 1 ) *  ( p & 1 ) * ( ( p >> 1 ) & 1 )  )));
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


uint64_t sqrt_Shanks_Tonelli(uint64_t a, uint64_t p){
	if( !a ){ //a == 0
		return 0;
	}
	if( !(exp_bin_mod( a, (p - 1)>>1 , p  ) == 1) ){ //Jacobi (On ne peut pas se fier à jacobi pour détecter un résidu quadratique)
		fprintf(stderr, "%ld n'est pas un résidu quadratique modulo %ld\n",a ,p );
		return 0;
	}

	uint64_t order = p - 1;
	uint64_t alpha = 0;
	uint64_t s = order;
	while( (s & 1) == 0 ){ //Tant que s est pair
		s >>= 1; //s = s/2
		alpha++; //on augmente la puissance de 2
	}
	// à cette étape on a p - 1 = 2^alpha * s avec s impair

	//On cherche un résidu non quadratique, on peut cette fois se fier à jacobi pour détecter un résidu non quadratique
	int n = 2;
	for( n = 2 ; n < p ; n++ ){
		if(jacobi(n,p) == -1){
			break;
		}
	}

	//n est un résidu non quadratique

	uint64_t r = exp_bin_mod(a, (s + 1) >> 1, p ); // r = a^( (s+1)/2 )

	uint64_t y = ( ( ( r * r ) % p ) * inv_mod(a , p) ) % p; // y = r^2*a^(-1) mod p

	uint64_t b = exp_bin_mod(n, s, p); // b est une racine 2^alpha ième de l'unité

	uint64_t j = 0; // j = sum_{i = 0}^{alpha - 1} 2^i * j_i   la décomposition de j en binaire

	int indice = 0;

	if( exp_bin_mod( y , (1 << ( alpha - 2 ) ), p ) != 1 ){ // y^(2^(alpha - 2)) mod p
		j = j^( 1 << indice); // j0 = 1
	}
	indice++;

	while( indice <= ( alpha - 1 ) ){
		uint64_t B = exp_bin_mod( b , j << 1 , p); // B = (b^j)^2 = b^(2j) mod p
		B = (B * y) % p; // B = b^(2j)*r^2*a^(-1) mod p
		B = exp_bin_mod( B , 1 << (  alpha - 2 - indice  ) , p );
		if( B != 1 ){
			j = j^( 1 << indice );
		}
		indice++;
	}

	// on a b^(2j)*r^2*a^(-1) = 1 mod p ainsi (b^j*r)^2 = a mod p

	uint64_t sqrt_a = ( exp_bin_mod( b , j , p) * r ) % p;

	return sqrt_a;
}

