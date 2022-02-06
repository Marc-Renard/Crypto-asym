#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <gmp.h>
#include "dsa.h"




void get_random_prime(mpz_t dest, uint16_t nb_bits, gmp_randstate_t rd_state){

	mpz_t tmp;
	mpz_init(tmp);



	do {
	mpz_urandomb(tmp, rd_state, nb_bits);
	mpz_nextprime(dest, tmp);
	} while (!(mpz_sizeinbase(dest, 2) == nb_bits));
	mpz_clear(tmp);

}

void gen_keys(mpz_t p, mpz_t q, mpz_t gen, mpz_t x, mpz_t y, gmp_randstate_t rd_state){

	
	mpz_t tmp, tmp2, rand;
	mpz_inits(tmp, tmp2, rand, NULL);
	
	get_random_prime(q,160, rd_state);

	do{ 
		mpz_urandomb(p, rd_state, 1024);
		mpz_mod(tmp, p, q);
		mpz_sub(tmp2, p, tmp);
		mpz_add_ui(p, tmp2, 1);
		//printf("1\n");
	}while( !mpz_probab_prime_p(p, 40) ); 



	mpz_sub_ui(gen, p, 1); //tmp2 = p-1
	mpz_fdiv_q(tmp, gen, q); // tmp = (p-1)/q
	do{
		mpz_urandomm(rand, rd_state, p );
		mpz_powm(gen, rand, tmp, p); //gen = rand^((p-1)/q) mod p
	}while( !(mpz_cmp_ui( gen, 1 )) ); //tant que gen == 1 on continue

	mpz_urandomm(x, rd_state, q);
	mpz_powm(y, gen, x, p);

	mpz_clears(tmp, tmp2, rand, NULL);

}

//Hachage
void h(mpz_t dest, mpz_t x){ //Identité dans cet exemple
	mpz_set(dest, x);
}

void dsa_sig(mpz_t r, mpz_t s, mpz_t m, mpz_t p, mpz_t q, mpz_t gen, mpz_t x, gmp_randstate_t rd_state){
	mpz_t k, tmp, tmp2;
	mpz_inits(k, tmp, tmp2, NULL);

	while( 1 ){
		mpz_urandomm(k, rd_state, q);
		mpz_powm(tmp,gen, k, p);
		mpz_mod(r, tmp, q);
		if(!mpz_cmp_ui(r,0)){ //Si r==0
			continue;
		}
		h(tmp2, m);//identité, doit être remplacé par une fonction de hachage
		mpz_mul(s, x, r); //sig = x*r
		mpz_add(tmp, tmp2, s); //tmp = h(m) + x*r
		mpz_invert(tmp2, k, q); //tmp2 = k^(-1) mod q
		mpz_mul(s, tmp, tmp2); //s = (h(m) + x*r)*k^(-1)
		mpz_swap(tmp, s);
		mpz_mod(s, tmp, q); //s =  (h(m) + x*r)*k^(-1) mod q
		if(!mpz_cmp_ui(s, 0)){
			continue;
		}
		break;
	}
	mpz_clears(k, tmp, tmp2, NULL);
}

uint8_t dsa_sig_check(mpz_t m, mpz_t r, mpz_t s, mpz_t p, mpz_t q, mpz_t gen, mpz_t y){
	if( (mpz_cmp(r, q) > 0) || (mpz_cmp_ui(r, 0) < 0) || (mpz_cmp(s, q) > 0) || (mpz_cmp_ui(s, 0) < 0) ){
		return 0;
	}
	mpz_t w, u1, u2, tmp;
	mpz_inits(w, u1, u2, tmp, NULL);
	mpz_invert(w, s, q);
	h(tmp, m); //tmp = h(m)
	mpz_mul(u1, tmp, w); //u1 = h(m)*s^(-1)
	mpz_swap(tmp, u1); 
	mpz_mod(u1, tmp, q); //u1 = h(m)*s^(-1) mod q
	mpz_mul(tmp, r, w);
	mpz_mod(u2, tmp, q); //u2 = r*s^(-1) mod q

	mpz_powm(tmp, gen, u1, p); //tmp = g^u1 mod p
	mpz_powm(u1, y, u2, p); //u1 = y^u2 mod p
	mpz_mul(u2, tmp, u1); //u2 = g^(h(m)*s^(-1) mod q) * y^(r*s^(-1) mod q)
	mpz_mod(u1, u2, p); //u1 = (g^(h(m)*s^(-1) mod q) * y^(r*s^(-1) mod q)) mod p
	mpz_mod(tmp, u1, q); //tmp = = ((g^(h(m)*s^(-1) mod q) * y^(r*s^(-1) mod q)) mod p) mod q
	
	if( !mpz_cmp(r, tmp) ){ //Si r == tmp signature ok
		mpz_clears(w, u1, u2, tmp, NULL);
		return 1;
	}
	mpz_clears(w, u1, u2, tmp, NULL);
	return 0;
}



