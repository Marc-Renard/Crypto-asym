#ifndef CRIBLE_H
#define CRIBLE_H

void mpz_fill_table_B(mpz_t *tab, const int64_t size, const mpz_t n);

void mpz_print_table(const mpz_t *tab,const int64_t size);

void mpz_free_table(mpz_t *tab, const int64_t size);

void mpz_init_table(mpz_t *tab, const int64_t size);

void mpz_fill_table_S(mpz_t *tab, const int64_t size_A, const mpz_t n);

void init_mat(const uint64_t row, const uint64_t col, uint64_t mat[row][col] );

void print_mat(const int64_t row, const int64_t col, uint64_t mat[row][col] );

void set_beta_col_pi(const int64_t row, const int64_t col, uint64_t mat[row][col], mpz_t S[row], mpz_t S_t[row], mpz_t B[col], const mpz_t n);



#endif /*CRIBLE_H*/