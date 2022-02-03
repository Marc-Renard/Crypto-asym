#ifndef DSA_H
#define DSA_H

void get_random_prime(mpz_t dest, uint16_t nb_bits, gmp_randstate_t rd_state);

void gen_keys(mpz_t p, mpz_t q, mpz_t gen, mpz_t x, mpz_t y, gmp_randstate_t rd_state);

#endif
