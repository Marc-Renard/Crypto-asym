#ifndef RHO_H
#define RHO_H

#include <stdint.h>
#include <gmp.h>

#define INT uint64_t

INT f(INT a, INT n);

INT gcd(INT a, INT b);

INT rho_factor(INT n);

void mpz_f( mpz_t a, mpz_t n);

void mpz_rho_factor(mpz_t factor, mpz_t n);

#endif /*RHO_H*/
