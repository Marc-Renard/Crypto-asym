#ifndef CRIBLE_H
#define CRIBLE_H

void mpz_fill_table_B(mpz_t *tab, const int64_t size, const mpz_t n);

void mpz_print_table(const mpz_t *tab,const int64_t size);

void mpz_free_table(mpz_t *tab, const int64_t size);

void mpz_init_table(mpz_t *tab, const int64_t size);

void mpz_fill_table_S(mpz_t *tab, const int64_t size_A, const mpz_t n);

void mpz_init_mat(mpz_t **mat, const int64_t nb_row, const int64_t nb_col );

void mpz_first_fill_mat(mpz_t **mat, const int64_t size_A, const mpz_t *tab_S, const mpz_t n);

void mpz_print_mat(const mpz_t **mat, const int64_t nb_row, const int64_t nb_col );

void mpz_free_mat( mpz_t **mat, const int64_t nb_row, const int64_t nb_col );

void set_beta_col_pi(mpz_t **tab, const mpz_t n , const int64_t size_A, const int64_t indice_pi );



#endif /*CRIBLE_H*/