#ifndef ELGAMAL_H
#define ELGAMAL_H

#include <stdint.h>
#include <math.h>
#include "fp_poly.h"

#define SIG_PRIME 101
#define CARAC 2
#define P_POWER 5
#define Q_FIELD pow(CARAC,P_POWER)

uint64_t get_rand(uint64_t min, uint64_t max);

//Store private key in private and return pubKey
void gen_encrypt_key_pair(const int q, fq_poly_t *gen, uint64_t *private_key, fq_poly_t **pub_key);

//Strore the encrypted message as an array of 2 fq_poly_t
void elgamal_encrypt(const int q, fq_poly_t *gen, fq_poly_t *pub_key, fq_poly_t *message, fq_poly_t *encrypted[2]);

fq_poly_t *elgamal_decrypt(const int q, fq_poly_t *gen, const int private_key, fq_poly_t *encrypted[2]);

int fast_gcd(int a, int b);

uint64_t exp_mod(uint64_t n, uint64_t power, uint64_t mod);

uint64_t double_and_add_mod(uint64_t n, uint64_t times, uint64_t mod);

uint64_t h(uint64_t m);

void elgamal_sig(const uint64_t prime, uint64_t gen, uint64_t m, const uint64_t private_key, uint64_t sig[2]);

uint8_t elgamal_sig_check(const uint64_t prime, uint64_t gen, uint64_t m, const uint64_t pub_key, uint64_t sig[2]);

void gen_sig_key_pair(const int prime, uint64_t gen, uint64_t *private_key, uint64_t *pub_key);


#endif /*ELGAMAL_H*/