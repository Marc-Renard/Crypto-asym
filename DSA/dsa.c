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
		get_random_prime(p,1024, rd_state);
		mpz_mod(tmp, p, q);
		mpz_sub(tmp2, p, tmp);
		mpz_add_ui(p, tmp2, 1);
		printf("1\n");
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
