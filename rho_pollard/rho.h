#ifndef RHO_H
#define RHO_H

#include <stdint.h>

uint64_t func(uint64_t x, uint64_t a, uint64_t b, uint64_t *alpha, uint64_t *beta, uint64_t mod);

int64_t inv_mod(int64_t a, int64_t p);

int64_t gcd(int64_t a, int64_t b);

uint64_t rho_log(uint64_t h, uint64_t g, uint64_t mod);

#endif /*RHO_H*/