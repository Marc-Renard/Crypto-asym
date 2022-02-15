#ifndef LOG_H
#define LOG_H

#include <gmp.h>

void f(mpz_t y, mpz_t x);

void next(mpz_t x, mpz_t g, mpz_t d, mpz_t n);

void x_n(mpz_t x, mpz_t d, mpz_t g, mpz_t b, mpz_t N, mpz_t n);

void logarithme(mpz_t alpha, mpz_t h, mpz_t g, mpz_t a, mpz_t b, mpz_t N, mpz_t n);

#endif /*LOG_H*/