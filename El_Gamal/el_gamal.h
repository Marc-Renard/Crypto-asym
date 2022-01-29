#ifndef EL_GAMAL_H
#define EL_GAMAL_H

#include <stdint.h>
#include <math.h>
#include <fp_poly.h>

#define CARAC 2
#define P_POWER 5
#define Q_FIELD pow(CARAC,P_POWER)

//Store private key in private and return pubKey
fq_poly_t *gen_key_pair(const int field, fq_poly_t *gen, uint32_t *private_key);

//Strore the encrypted message as an array of 2 fq_poly_t
void el_gamal_encrypt(const int q, fq_poly_t *gen, fq_poly_t *pub_key, fq_poly_t *message, fq_poly_t *encrypted[2]);

fq_poly_t *el_gamal_decrypt(const int q, fq_poly_t *gen, const int private_key, fq_poly_t *encrypted[2]);


#endif /*EL_GAMAL_H*/