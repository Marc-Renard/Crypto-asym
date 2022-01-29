#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fp_poly.h>
#include "el_gamal.h"


fq_poly_t *gen_key_pair(const int q, fq_poly_t *gen, uint32_t *private_key){
	FILE* rand = fopen("/dev/urandom", "r");
	if(rand == NULL){
		fprintf(stderr,"Cannot open /dev/urandom");
		return NULL;
	}
	uint32_t random = 0;
	if(!(fread(&random, sizeof(uint32_t),1,rand)))
	{
		fprintf(stderr, "Cannot read in file");
		fclose(rand);
		return NULL;
	}
	fclose(rand);
	*private_key = random % ( q - 2 ) + 2; //  1 < random < q
	return fq_poly_fast_exp(gen, *private_key);
}

void el_gamal_encrypt(const int q, fq_poly_t *gen, fq_poly_t *pub_key, fq_poly_t *message, fq_poly_t *encrypted[2]){
	FILE* rand = fopen("/dev/urandom", "r");
	if(rand == NULL){
		fprintf(stderr,"Cannot open /dev/urandom");
		return;
	}
	uint32_t k = 0;
	if(!(fread(&k, sizeof(uint32_t),1,rand)))
	{
		fprintf(stderr, "Cannot read in file");
		fclose(rand);
		return;
	}
	fclose(rand);
	k = k % (q - 2) + 2;
	encrypted[0] = fq_poly_fast_exp(gen, k);
	
	fq_poly_t *tmp = fq_poly_fast_exp(pub_key,k);
	encrypted[1] = fq_poly_mul(message,tmp);

	fq_poly_free(tmp);
	return;
}

fq_poly_t *el_gamal_decrypt( const int q, fq_poly_t *gen, const int private_key, fq_poly_t *encrypted[2]){
	fq_poly_t *tmp = fq_poly_fast_exp(encrypted[0], q - 1 - private_key);
	fq_poly_t *message = fq_poly_mul(tmp, encrypted[1]);
	fq_poly_free(tmp);
	return message;
}