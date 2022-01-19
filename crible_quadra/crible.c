#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <gmp.h>
#include "crible.h"

int main(int argc, char **argv){
    if(argc != 3){
        fprintf(stderr, "./crible P(max of p in B) n\n");
        return -1;
    }
    int64_t p = atoi(argv[1]);
    mpz_t n;
    mpz_init(n);
    mpz_set_str(n, argv[2], 10);

    mpz_t B[p];
    mpz_fill_table_B(B, p, n);
    mpz_print_table_B(B, p);
    mpz_free_table_B(B, p);

    mpz_clear(n);
    return 0;
}

void mpz_fill_table_B(mpz_t *tab, int64_t size, mpz_t n){
    mpz_init(tab[0]);
    mpz_set_ui(tab[0], 2);
    mpz_t prime, tmp;
    mpz_inits(prime, tmp, NULL);
    mpz_set_ui(prime, 2);
    for( int64_t cmptr = 1; cmptr < size; cmptr++ ){
        mpz_init(tab[cmptr]);
        int test = 0;
        while( test != 1){
            mpz_nextprime(tmp, prime );
            mpz_set(prime, tmp);
            test = mpz_legendre(n,prime);
        }
        mpz_set(tab[cmptr], prime);        
    }
    mpz_clears(prime, tmp, NULL);
    return;
}

void mpz_print_table_B(mpz_t *tab, int64_t size){
    mpz_out_str(stdout, 10, tab [0]);
    for( int64_t i = 1; i < size ; i++){
        fprintf(stdout, " | ");
        mpz_out_str(stdout, 10, tab[i]);
    }
    fprintf(stdout, "\n");
    return;
}

void mpz_free_table_B(mpz_t *tab, int64_t size){
    for(int64_t i = 0 ; i < size ; i++){
        mpz_clear(tab[i]);
    }
    return;
}