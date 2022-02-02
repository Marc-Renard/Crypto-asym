#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "test_prim.h"

#define NOT_PRIME 0
#define PRIME 1


uint64_t exp_mod(uint64_t n, uint64_t power, uint64_t mod){
	uint64_t res = 1;
	uint64_t tmp = res;
	while(power){ //ie while power!=0
		if( power & 1 ){ //power est impair
			res = ( res * n ) % mod;
		}
		else {
			tmp = ( res * n ) % mod; //Opération factice pour lisser la consommation
		}
		n = (n * n) % mod;
		power >>= 1;
	}
	if(tmp || !tmp){
		return res;
	}
}

uint64_t gcd(uint64_t a, uint64_t b){
	if( a == 0 ){
		return b;	
	}
	if( b == 0 ){
		return a;	
	}
	return gcd(b, a%b );
}

//Nombre aléatoire entre min et max, max exclu
uint64_t random_numb(uint64_t min, uint64_t max){
	FILE *rand = fopen("/dev/urandom", "r");
	if(rand == NULL){
		fprintf(stderr,"Fail to open /dev/urandom\n");
		return 0;	
	}
	uint64_t n;
	if(!(fread(&n, sizeof(uint64_t),1,rand))){
		fclose(rand);
		fprintf(stderr, "Cannot read in file");
		return 0;
	}
	fclose(rand);
	return ( n%(max-min) + min );
}

int isprime_Fermat(uint64_t n, uint8_t nb_tests){
	for(uint8_t i = 0; i < nb_tests; i++){
		uint64_t temoin = random_numb(2,n);
		//printf("temoin :%ld\n",temoin);
		if( gcd(temoin,n) != 1 ){
			return NOT_PRIME;
		}
		if( exp_mod(temoin, n-1, n) != 1 ){
			return NOT_PRIME;
		}
	}
	return PRIME; //Probably prime
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

int legendre(int64_t a,uint64_t p){
    if(a<0){
        return(legendre(a+p,p));
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
        return((legendre(a/2,p))*(-1 + 2 * parite( p & 0b111 ) )); // (-1)^( (p^2-1)/8 )
    }else{
    	//On ne doit multiplier par -1 que si a = p = 3 mod 4 soit : les deux derniers bits de a et p sont tous des 1
        return((legendre(p%a,a))*(1 - 2 * ( ( a & 1 ) * ( ( a >> 1 ) & 1 ) *  ( p & 1 ) * ( ( p >> 1 ) & 1 )  )));
    }
}

int isprime_Solovay_StraBen(uint64_t n, uint8_t nb_tests){
	for(uint8_t i = 0; i < nb_tests; i++){
		uint64_t b = random_numb(2,n);
		//printf("b = %d\n",b);
		if( gcd(b,n) != 1 ){
			return NOT_PRIME;
		}

		uint64_t test = exp_mod(b, (n-1)>>1, n);
		uint64_t leg = legendre(b, n);
		//printf("leg : %ld, exp : %ld\n",leg, test);
		if( (leg != test) && (test != (leg+n)) ){
			return NOT_PRIME;
		}
	}
	return PRIME;
}


uint8_t testMillerRabin(uint64_t a,uint64_t n){
    if(n==2){
        return 1;
    }
    if(!(n&1)){
        return 0;
    }

	uint64_t s = 0, t = n - 1 ;
	while( !(t & 1) ){
		t >>= 1;
		s++;
	}
	//n-1 = 2^s*t

    //int b=expmod3(a,t,n);
	uint64_t b = exp_mod(a,t,n);
    if(b==1){
        return 1;
    }
    for(uint64_t i = 0 ; i < s ; i++){
        if(b == n-1){
            return 1;
        }else if(b==1){
            return 0;
        }else{
            b = exp_mod(b, 2, n);
        }
    }
    return 0;
}

uint8_t isprime_Miller_Rabin(uint64_t n, uint64_t nb_tests){
	if( n == 2 ){
		//fprintf(stdout, "2 est premier\n");
		return 1;
	}
    if( !( n & 1 )){
        //printf("%ld est pair, il n'est pas premier\n",n);
        return 0;
    }
    uint8_t res;
    uint64_t a;
    for(uint64_t i = 0 ; i < nb_tests ; i++ ){
        a = random_numb(1, n - 1);
        res = testMillerRabin( a , n );
        if(res == 0){
            //printf("%ld n'est pas premier\n",n);
            return 0;
        }
    }
    //printf("%ld a passe %ld tests de Miller-Rabin, il y a donc une forte probabilite qu'il soit premier\n",n,nb_tests);
    return 1;
}
