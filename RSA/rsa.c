#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "rsa.h"


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

//len = nombre d'octets maximal
void I2OSP(uint64_t n, uint8_t len, uint8_t *OS){
	if( n >> (len << 3 )){ // n > 8*len
		fprintf(stderr, "Integer too large");
		return;
	}
	uint8_t i = 0;
	while( n ){ //n > 0
		OS[len - 1 - i] = (n & 0xFF);
		n >>= 8;
		i++;
	}
	return;
}

uint64_t OS2IP(uint8_t *OS, uint8_t len){
	uint64_t n = 0;
	for(uint8_t i = 0; i < (len - 1); i++){
		n |= OS[i];
		n <<= 8;
	}
	n |= OS[len - 1];
	return n;
}

uint64_t rsa_encrypt(uint64_t clear_text, uint64_t pub_exp, uint64_t module ){
	return exp_mod(clear_text, pub_exp, module);
}

uint64_t rsa_decrypt(uint64_t cipher_text, uint64_t private_exp, uint64_t module ){
	return exp_mod(cipher_text, private_exp, module);
}

