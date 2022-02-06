#ifndef DSA_H
#define DSA_H

void get_random_prime(mpz_t dest, uint16_t nb_bits, gmp_randstate_t rd_state);

void gen_keys(mpz_t p, mpz_t q, mpz_t gen, mpz_t x, mpz_t y, gmp_randstate_t rd_state);

//Hachage
void h(mpz_t dest, mpz_t x);

void dsa_sig(mpz_t r, mpz_t s, mpz_t m, mpz_t p, mpz_t q, mpz_t gen, mpz_t x, gmp_randstate_t rd_state);

uint8_t dsa_sig_check(mpz_t m, mpz_t r, mpz_t s, mpz_t p, mpz_t q, mpz_t gen, mpz_t y);

#endif
