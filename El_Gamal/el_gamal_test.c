#include "el_gamal.h"
#include <stdio.h>
#include <stdlib.h>
#include <fp_poly.h>

int main(int argc, char **argv){
    //X^5+X^2+1 irréductible sur F2[X]
	uint64_t modulo[6] = {1,0,0,1,0,1};
	fp_poly_t *pmod = fp_poly_init(5, modulo, CARAC);
	uint64_t fq_gen_tab[2]={1,0}; // X est un générateur de F32 ~= F2[X]/(X^5+X^2+1)
	fp_poly_t *fq_p = fp_poly_init(1, fq_gen_tab, CARAC);
	fq_poly_t *gen_fq = fq_poly_init(fq_p,pmod);

    uint32_t private = 0;
    fq_poly_t *pub_key = gen_key_pair(Q_FIELD, gen_fq, &private);

    fprintf(stdout,"Clef privée : %d\nClef publique :\n",private);
    fq_poly_print(pub_key, 'X', stdout);
    fprintf(stdout,"\n\n");

    //##############################################################
    // test encrypt
    
    uint64_t mess[4] = {1,0,1,0};
    fp_poly_t *mess_p = fp_poly_init(3, mess, CARAC);
    fq_poly_t *m = fq_poly_init(mess_p,pmod);

    fprintf(stdout,"Message en calir:\n");
    fq_poly_print(m, 'X', stdout);
    fprintf(stdout,"\n\n");

    fq_poly_t *encrypted[2];

    el_gamal_encrypt(Q_FIELD, gen_fq, pub_key, m, encrypted);

    fprintf(stdout,"Message chiffré :\n");
    fq_poly_print(encrypted[0], 'X', stdout);
    fprintf(stdout,"\n");
    fq_poly_print(encrypted[1], 'X', stdout);
    fprintf(stdout,"\n\n");

    fq_poly_t *deciphered = el_gamal_decrypt(Q_FIELD, gen_fq, private, encrypted);
    
    fprintf(stdout,"Message déchiffré :\n");
    fq_poly_print(deciphered, 'X', stdout);
    fprintf(stdout,"\n\n");



    fp_poly_free(pmod);
    fp_poly_free(fq_p);
    fq_poly_free(gen_fq);
    fq_poly_free(pub_key);
    fp_poly_free(mess_p);
    fq_poly_free(m);
    fq_poly_free(encrypted[0]);
    fq_poly_free(encrypted[1]);
    fq_poly_free(deciphered);

    return 0;
}