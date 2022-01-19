#ifndef CRIBLE_H
#define CRIBLE_H

void mpz_fill_table_B(mpz_t *tab, int64_t size, mpz_t n);

void mpz_print_table_B(mpz_t *tab, int64_t size);

void mpz_free_table_B(mpz_t *tab, int64_t size);

#endif /*CRIBLE_H*/