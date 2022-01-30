#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "fp_poly.h"
#include "elgamal.h"

//Renvoie un nombre aléatoire k tel que  :  min <= k < max
uint64_t get_rand(uint64_t min, uint64_t max){
	FILE* rand = fopen("/dev/urandom", "r");
	if(rand == NULL){
		fprintf(stderr,"Cannot open /dev/urandom");
		return 0;
	}
	uint64_t random = 0;
	if(!(fread(&random, sizeof(uint64_t),1,rand)))
	{
		fprintf(stderr, "Cannot read in file");
		fclose(rand);
		return 0;
	}
	fclose(rand);
	return (random % (max - min)) + min;
}

void gen_encrypt_key_pair(const int q, fq_poly_t *gen, uint64_t *private_key, fq_poly_t **pub_key){
	*private_key = get_rand(2, q); //  1 < random < q
	*pub_key = fq_poly_fast_exp(gen, *private_key);
	return;
}

void elgamal_encrypt(const int q, fq_poly_t *gen, fq_poly_t *pub_key, fq_poly_t *message, fq_poly_t *encrypted[2]){
	uint64_t k = get_rand(2, q);

	encrypted[0] = fq_poly_fast_exp(gen, k);
	
	fq_poly_t *tmp = fq_poly_fast_exp(pub_key,k);
	encrypted[1] = fq_poly_mul(message,tmp);

	fq_poly_free(tmp);
	return;
}

fq_poly_t *elgamal_decrypt( const int q, fq_poly_t *gen, const int private_key, fq_poly_t *encrypted[2]){
	fq_poly_t *tmp = fq_poly_fast_exp(encrypted[0], q - 1 - private_key);
	fq_poly_t *message = fq_poly_mul(tmp, encrypted[1]);
	fq_poly_free(tmp);
	return message;
}


int fast_gcd(int a, int b){
	int reste = 0;
	while( b ){ // ie b!=0
		//printf("a=%d\nb=%d\n\n",a,b);
		reste = a % b;
		if(reste > (b - reste) ){
			reste = b - reste; 
		}
		a = b;
		b = reste;
	}
	return a;
}

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
	if(tmp || !tmp){ //évite un unused variable
		return res;
	}
	return res; //évite un atteint la fin d'un fonction non void sans rencontrer de return
}

uint64_t double_and_add_mod(uint64_t n, uint64_t times, uint64_t mod){
	uint64_t res = 0;
	while(times){ //ie while power!=0
		if( times & 1 ){ //power est impair
			res = ( res + n ) % mod;
		}
		n = (n * 2) % mod;
		times >>= 1;
	}
	return res;
}


uint64_t h(uint64_t m){ //identité pour le moment, mais il faut la remplacer par une focntion de hachage
	return m;
}

void elgamal_sig(const uint64_t prime, uint64_t gen, uint64_t m, const uint64_t private_key, uint64_t sig[2]){
	int gcd = 0;
	int64_t s = 0;
	uint64_t r = 0;
	while( s == 0 ){
		uint64_t k = 0;
		while(gcd != 1){
			k = get_rand(2, prime - 1);
			gcd = fast_gcd(k, prime - 1);
		}
		//fprintf(stdout,"k = %ld\n",k); 
		r = exp_mod(gen, k, prime);
		//fprintf(stdout,"private * r = %ld\n",private_key * r % (prime-1)); 

		s = h(m) + prime - 1 - double_and_add_mod(private_key,r,prime - 1 );
		uint64_t k_inv = inv_mod(k, prime - 1);
		s = double_and_add_mod(s, k_inv, prime - 1);
	}
	sig[0] = r;
	sig[1] = (uint64_t) s;
	return;
}

//renvoie 0 si la signature n'est pas valide et 1 si elle l'est
uint8_t elgamal_sig_check(const uint64_t prime, uint64_t gen, uint64_t m, const uint64_t pub_key, uint64_t sig[2]){
	uint64_t r = sig[0], s = sig[1];
	if( r >= prime || s >= (prime - 1)){
		return 0;
	}
	uint64_t left = exp_mod(gen, h(m), prime);
	uint64_t right = exp_mod(pub_key, r,  prime);
	right = double_and_add_mod(right , exp_mod(r, s, prime) , prime);
	//fprintf(stdout,"right : %ld\n", right);
	if(left == right){
		return 1;
	}
	return 0;
}


void gen_sig_key_pair(const int prime, uint64_t gen, uint64_t *private_key, uint64_t *pub_key){
	*private_key = get_rand(2, prime); //  1 < a < prime
	*pub_key = exp_mod(gen, *private_key, prime);
	fprintf(stdout,"sig_private_key = %ld, sig_pub_key = %ld\n\n",*private_key, *pub_key);
	return;
}





