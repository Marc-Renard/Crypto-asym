#ifndef TEST_PRIM_H
#define TEST_PRIM_H

#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

uint64_t exp_mod(uint64_t n, uint64_t power, uint64_t mod);

uint64_t gcd(uint64_t a, uint64_t b);

uint64_t random_numb(uint64_t max);

int isprime_Fermat(uint64_t n, uint8_t nb_tests);



#endif /* TEST_PRIM_H */
