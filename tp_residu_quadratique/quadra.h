#ifndef QUADRA_H
#define QUADRA_H

#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

uint64_t exp_bin_mod(uint64_t n, uint64_t power, uint64_t mod);

int jacobi(int64_t a,uint64_t p);

int parite(uint64_t a);

uint64_t sqrt_Shanks_Tonelli(uint64_t a, uint64_t p);

int64_t inv_mod(int64_t a, int64_t p);


#endif /* QUADRA_H */