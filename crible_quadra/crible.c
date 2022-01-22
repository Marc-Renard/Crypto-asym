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
    
    
    int64_t A = 15;
    mpz_t S[A];
    mpz_t S_t[A];
    mpz_init_table(S,A);
    mpz_init_table(S_t,A);
    mpz_fill_table_S(S, A, n);
    mpz_fill_table_S(S_t, A, n);
    mpz_print_table(S, A);


    uint64_t mat[A][p];
    init_mat(A,  p, mat);
    //mpz_first_fill_mat(mat,A, S, n);
    //print_mat(A, p, mat);
    set_beta_col_pi(A, p, mat,S, S_t, B, n);

    print_mat(A, p, mat);

    fprintf(stdout,"S_t:\n");
    mpz_print_table(S_t, A);



    mpz_free_table(B, p);
    mpz_free_table(S,A);
    mpz_free_table(S_t,A);
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

void init_mat(const uint64_t row, const uint64_t col, uint64_t mat[row][col] ){
    for(uint64_t i = 0 ; i < row ; i++ ){
        for(uint64_t j = 0 ; j < col ; j++ ){
            mat[i][j] = 0;
        }
    }
    return;
}


void print_mat(const int64_t row, const int64_t col, uint64_t mat[row][col] ){
    for(int64_t i = 0 ; i < row ; i++){
        fprintf(stdout,"%ld", mat[i][0]);
        for( int64_t j = 1; j < col ; j++){
            fprintf(stdout, " | ");
            fprintf(stdout, "%ld", mat[i][j]);
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout,"\n");
    return;
}



void set_beta_col_pi(const int64_t row, const int64_t col, uint64_t mat[row][col], mpz_t S[row], mpz_t S_t[row], mpz_t B[col], const mpz_t n){
    //colonne pour 2 à part
    mpz_t tmp;
    mpz_init(tmp);
    mpz_mod_ui(tmp, n, 8);
    if(mpz_cmp_ui(tmp, 1) != 0){
        int test = 1;
        while(test){
            test = 0;
            for(int64_t i = 0 ; i < row ; i++){
            mpz_mod_ui(tmp, S_t[i],2);
            if(mpz_cmp_ui(tmp, 0) == 0 ){
                mat[i][0] ++;
                mpz_cdiv_q_ui(tmp, S_t[i], 2);
                mpz_set(S_t[i], tmp);
                test = 1;
            }else{
                //zrgf
            }
        }
        }
    }else{
            //srg
    }
    
    for(int64_t i = 1 ; i < col ; i++ ){
        for(int64_t j = 0 ; j < row ; j++){
            //int beta = 0;
            int test = 1;
            while(test){
                test = 0;
                for(int64_t k = 0 ; k < row ; k++){
                    mpz_mod(tmp, S_t[k],B[i]);
                    if(mpz_cmp_ui(tmp, 0) == 0 ){
                        mat[k][i] ++;
                        mpz_cdiv_q(tmp, S_t[k], B[i]);
                        mpz_set(S_t[k], tmp);
                        test = 1;
                    }else{
                        //zrgf
                    }
                }
            }


        }
    }
    mpz_clear(tmp);
    return;
}