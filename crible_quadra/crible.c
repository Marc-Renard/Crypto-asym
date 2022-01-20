#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <gmp.h>
#include "crible.h"

int main(int argc, char **argv){
    if(argc != 3){
        fprintf(stderr, "./crible P(max of p in B) n\n");
        return -1;
    }
    int64_t p = atoi(argv[1]);
    mpz_t n;
    mpz_init(n);
    mpz_set_str(n, argv[2], 10);

    mpz_t B[p];
    mpz_init_table(B, p);
    mpz_fill_table_B(B, p, n);
    mpz_print_table(B, p);
    mpz_free_table(B, p);
    
    int64_t A = 6;
    mpz_t S[A];
    mpz_init_table(S,A);
    mpz_fill_table_S(S, A, n);
    mpz_print_table(S, A);
    mpz_free_table(S,A);

    mpz_t mat[p+3][A];
    mpz_init_mat(&mat, p+3, A);
    //mpz_first_fill_mat(mat,A, S, n);
    //mpz_print_mat(mat,p + 3, A);
    mpz_free_mat(mat, p+3, A);

    mpz_clear(n);

    return 0;
}

void mpz_fill_table_B(mpz_t *tab, const int64_t size, const mpz_t n){
    mpz_init(tab[0]);
    mpz_set_ui(tab[0], 2);
    mpz_t prime, tmp;
    mpz_inits(prime, tmp, NULL);
    mpz_set_ui(prime, 2);
    for( int64_t cmptr = 1; cmptr < size; cmptr++ ){
        int test = 0;
        while( test != 1){
            mpz_nextprime(tmp, prime );
            mpz_set(prime, tmp);
            test = mpz_legendre(n,prime);
        }
        mpz_set(tab[cmptr], prime);        
    }
    mpz_clears(prime, tmp, NULL);

    return;
}



void mpz_print_table(const mpz_t *tab, const int64_t size){
    mpz_out_str(stdout, 10, tab [0]);
    for( int64_t i = 1; i < size ; i++){
        fprintf(stdout, " | ");
        mpz_out_str(stdout, 10, tab[i]);
    }
    fprintf(stdout, "\n");
    return;
}

void mpz_init_table(mpz_t *tab, const int64_t size){
    for(int64_t i = 0 ; i < size ; i++){
        mpz_init_set_ui(tab[i],0);
    }
    return;
}

void mpz_free_table(mpz_t *tab, const int64_t size){
    for(int64_t i = 0 ; i < size ; i++){
        mpz_init_set_ui(tab[i],0);
    }
    return;
}

void mpz_fill_table_S(mpz_t *tab, const int64_t size_A, const mpz_t n){
    mpz_t root,tmp, tmp2;
    mpz_inits(root, tmp, tmp2, NULL);
    mpz_sqrt(root, n);

    for( int64_t cmptr = 1; cmptr <= size_A; cmptr++ ){

        mpz_add_ui(tmp,root, cmptr);

        mpz_pow_ui(tmp2, tmp, 2);

        mpz_sub(tab[cmptr-1], tmp2, n);
    }
    mpz_clears(root, tmp, tmp2, NULL);
    return;
}

void mpz_init_mat(mpz_t **mat, const int64_t nb_row, const int64_t nb_col ){
    for(int64_t i = 0 ; i < nb_row ; i++){
        for(int64_t j = 0 ; j < nb_col ; j++){
            mpz_init_set_ui(mat[i][j],0);
        }
    }
    return;
}

void mpz_first_fill_mat(mpz_t **mat, const int64_t size_A, const mpz_t *tab_S, const mpz_t n){
    mpz_t root, tmp;
    mpz_inits(root, tmp, NULL);
    mpz_sqrt(root,n);
    for(int64_t i = 0 ; i < size_A ; i++){
        mpz_set(mat[i][1], tab_S[i]);
        mpz_add_ui(tmp, root, i + 1);
        mpz_set(mat[i][0], tmp);
    }
    mpz_clears(root, tmp, NULL);
    return;
}

void mpz_print_mat(const mpz_t **mat, const int64_t nb_row, const int64_t nb_col ){
    for(int64_t i = 0 ; i < nb_row ; i++){
        mpz_out_str(stdout, 10, mat[i][0]);
        for( int64_t j = 1; j < nb_col ; j++){
            fprintf(stdout, " | ");
            mpz_out_str(stdout, 10, mat[i][j]);
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout,"\n");
    return;
}

void mpz_free_mat(mpz_t **mat, const int64_t nb_row, const int64_t nb_col ){
    for(int64_t i = 0 ; i < nb_row ; i++){
        for( int64_t j = 1; j < nb_col ; j++){
            mpz_clear(mat[i][j]);
        }
    }
    return;
}

void set_beta_col_pi(mpz_t **tab, const mpz_t n , const int64_t size_A, const int64_t indice_pi ){
    mpz_t pi, beta;
    mpz_inits(pi, beta, NULL);
    mpz_set(pi, tab[0][3+indice_pi]);
    mpz_set_ui(beta, 1);

    int sol_found = 1;
    while( sol_found ){
        break;
    }
    return;
}