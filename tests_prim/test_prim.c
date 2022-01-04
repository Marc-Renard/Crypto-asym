#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "test_prim.h"


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

uint64_t random_numb(uint64_t max){
	FILE *rand = fopen("/dev/urandom", "r");
	if(rand == NULL){
		fprintf(stderr,"Fail to open /dev/urandom\n");
		return 0;	
	}
	uint64_t n;
	size_t s = fread(&n,4,1,rand);
	fclose(rand);
	if( s!= 4 ){
		fprintf(stdout,"Fail to read\n");
		return 0;
	}
	return n%max;
}

int isprime_Fermat(uint64_t n, uint8_t nb_tests){
	for(uint8_t i = 0; i < nb_tests; i++){
		
	}
	return 0;
}
