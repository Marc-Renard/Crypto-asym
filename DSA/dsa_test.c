#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <gmp.h>
#include "dsa.h"

int main(int argc, char **argv){
	gmp_randstate_t rd_state;
  	gmp_randinit_mt(rd_state);


    //Test get_random_prime
    fprintf(stdout, "##### Test de get_random_prime #####\n");
    mpz_t test;
    mpz_init(test);
    get_random_prime(test, 160, rd_state);
    mpz_out_str(stdout, 10, test);
    fprintf(stdout,"\n");
    mpz_clear(test);
    

    //Test de gen_key
    fprintf(stdout, "\n\n##### Test de gen_key #####\n");
    mpz_t p, q, gen, x, y;
    mpz_inits(p, q, gen, x, y, NULL);

    gen_keys(p, q, gen, x, y, rd_state);

    fprintf(stdout, "p =\n");
    mpz_out_str(stdout, 10, p);
    fprintf(stdout, "\nq =\n");
    mpz_out_str(stdout, 10, q);
        fprintf(stdout, "\ngen =\n");
    mpz_out_str(stdout, 10, gen);
        fprintf(stdout, "\nx =\n");
    mpz_out_str(stdout, 10, x);
        fprintf(stdout, "\ny =\n");
    mpz_out_str(stdout, 10, y);

    //Test de signature et vérification de signature
    fprintf(stdout, "\n\n##### Test de signature et vérification de signature #####\n");
    mpz_t m, r, s;
    mpz_inits(m, r, s, NULL);
    mpz_urandomm(m, rd_state, p); //message aléatoire entre 0 et p
    dsa_sig(r, s, m, p, q, gen, x, rd_state);

    fprintf(stdout, "Messae :\n");
    mpz_out_str(stdout, 10, m);
    fprintf(stdout, "\nSignature:\n(r,s) = ");
    mpz_out_str(stdout, 10, r);
    fprintf(stdout, " , ");
    mpz_out_str(stdout, 10, s);
    fprintf(stdout, "\n\n");

    fprintf(stdout, "Vérification de la signature:\n");
    if( dsa_sig_check(m, r, s, p, q, gen, y) ){
        fprintf(stdout, "Signature valide\n");
    }else{
        fprintf(stdout, "Signature invalide\n");
    }

    mpz_add_ui(s, s, 1);
    fprintf(stdout, "Vérification d'une signature modifiée:\n");
    if( dsa_sig_check(m, r, s, p, q, gen, y) ){
        fprintf(stdout, "Signature valide\n");
    }else{
        fprintf(stdout, "Signature invalide\n");
    }

    mpz_clears(m, r, s, NULL);
    mpz_clears(p, q, gen, x, y, NULL);
    gmp_randclear(rd_state);
    return 0;
}