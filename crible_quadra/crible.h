#ifndef CRIBLE_H
#define CRIBLE_H

void mpz_fill_table_B(mpz_t *tab, int64_t size, mpz_t n);

void mpz_print_table(mpz_t *tab, int64_t size);

void mpz_free_table(mpz_t *tab, int64_t size);

void mpz_init_table(mpz_t *tab, int64_t size);

void mpz_fill_table_S(mpz_t *tab, int64_t size_A, mpz_t n);

#endif /*CRIBLE_H*/