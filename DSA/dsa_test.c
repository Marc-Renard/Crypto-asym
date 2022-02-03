#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <gmp.h>
#include "dsa.h"

int main(int argc, char **argv){
	gmp_randstate_t rd_state;
  	gmp_randinit_mt(rd_state);

    mpz_t test;
    mpz_init(test);
    get_random_prime(test, 160, rd_state);
    mpz_out_str(stdout, 10, test);
    
    mpz_t p, q, gen, x, y;
    mpz_inits(p, q, gen, x, y, NULL);

    gen_keys(p, q, gen, x, y, rd_state);

    fprintf(stdout, "p =\n");
    mpz_out_str(stdout, 10, p);
    fprintf(stdout, "q =\n");
    mpz_out_str(stdout, 10, q);
        fprintf(stdout, "gen =\n");
    mpz_out_str(stdout, 10, gen);
        fprintf(stdout, "x =\n");
    mpz_out_str(stdout, 10, x);
        fprintf(stdout, "y =\n");
    mpz_out_str(stdout, 10, y);

    mpz_clears(p, q, gen, x, y, NULL);
    
    mpz_clear(test);
    gmp_randclear(rd_state);
    return 0;
}