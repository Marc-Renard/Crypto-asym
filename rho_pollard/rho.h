#ifndef RHO_H
#define RHO_H

#include <stdint.h>

void f(uint64_t *x, uint64_t a, uint64_t b, uint64_t *alpha, uint64_t *beta, uint64_t mod);

int64_t inv_mod(int64_t a, int64_t p);

#endif /*RHO_H*/