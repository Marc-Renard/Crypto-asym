#include <fp_poly.h>

int main(int agrc, char **argv)
{
	uint64_t carac = 5;
	uint64_t a[3] = {1,2,1};
	fp_poly_t *p = fp_poly_init(2,a, carac);
	if( p == NULL){
		fprintf(stderr, "Erreur initialisation\n");
		return -1;
	}

	printf("######## Tests de fp_poly_print ########\n");
	fp_poly_print(p,'X',stdout);
	
	
	uint64_t b[6] = {3,0,0,0,1,3};
	fp_poly_t *q = fp_poly_init(5, b, carac);
	if( q == NULL){
		fprintf(stderr, "Erreur initialisation\n");
		return -1;
	}
	
	uint64_t c[4] = {4,4,0,1};
	fp_poly_t *r = fp_poly_init(3, c, carac);
	fp_poly_print(r,'X',stdout);

	//###############################################################################################

	
	printf("\n\n######## Test de la multiplication ########\n");	
	fp_poly_t *prod = fp_poly_mul(q,r);
	
	printf("La multiplication dans F_%ld[X] de\n\n", carac);
	fp_poly_print(q,'X',stdout);
	printf("\npar\n");
	fp_poly_print(r,'X',stdout);
	printf("\n\ndonne:\n");
	if( prod == NULL ){
		fprintf(stderr,"Erreur lors de la multiplication\n");
		return -1;
	}else{
		fp_poly_print(prod,'X',stdout);
	}
	

	//###############################################################################################

	fp_poly_t *sum = fp_poly_add(prod, r);

	printf("\n\n######### Test de l'addition ########\n");
	printf("L'addition dans F_%ld[X] de\n\n", carac);
	fp_poly_print(prod,'X',stdout);
	printf("\net\n");
	fp_poly_print(r,'X',stdout);
	printf("\n\ndonne:\n");
	if( sum == NULL ){
		fprintf(stderr,"Erreur lors de l'addition\n");
		return -1;
	}else{
		fp_poly_print(sum,'X',stdout);
	}
	
	//###############################################################################################

	fp_poly_t *diff = fp_poly_sub(r, p);

	printf("\n\n######### Test de la soustraction ########\n");
	printf("La soustraction dans F_%ld[X]\n", carac);
	fp_poly_print(r,'X',stdout);
	printf("\n-\n");
	fp_poly_print(p,'X',stdout);
	printf("\n\ndonne:\n");
	if( diff == NULL ){
		fprintf(stderr,"Erreur lors de la soustraction\n");
		return -1;
	}else{
		fp_poly_print(diff,'X',stdout);
	}
	

	//####################################################################################
	printf("\n\n######### Test de l'inverse de a mod p ########\n");
	int64_t aa = 3, mod = 13;
	int64_t inv = inv_mod( aa, mod);
	printf("Inv de %ld mod %ld --> %ld\n",aa,mod,inv);


	//###############################################################################################

	uint64_t poly_div[7] = {3,3,0,2,1,4,4};
	fp_poly_t *p_div = fp_poly_init(6,poly_div, carac);
	uint64_t poly_div2[3] = {1,1,1};
	fp_poly_t *p_div2 = fp_poly_init(2,poly_div2, carac);

	fp_poly_t *quotient = NULL;
	fp_poly_t *reste = NULL;
	fp_poly_div_euc(p_div, p_div2, &quotient, &reste);

	printf("\n######### Test de la division Euclidienne ########\n");
	fp_poly_print(p_div,'X',stdout);
	printf("\ndivisé par\n");
	fp_poly_print(p_div2,'X',stdout);

	printf("\n\ndonne\n\nReste:\n");
	fp_poly_print(reste,'X',stdout);

	printf("\nQutient:\n");
	fp_poly_print(quotient,'X',stdout);

	
	
	//###############################################################################################

	uint64_t poly_euc1[8] = {4,2,2,0,3,3,1,2};
	fp_poly_t *p_euc1 = fp_poly_init(7,poly_euc1, carac);
	uint64_t poly_euc2[9] = {2,2,0,3,4,1,2,1,3};
	fp_poly_t *p_euc2 = fp_poly_init(8,poly_euc2, carac);

	fp_poly_t *gcd = NULL;
	fp_poly_gcd(p_euc1, p_euc2, &gcd);

	printf("\n\n######### Test de l'algorithme d'Euclide / PGCD ########\n");

	printf("Le PGCD de :\n\n");
	fp_poly_print(p_euc1,'X',stdout);
	printf("\net\n");
	fp_poly_print(p_euc2,'X',stdout);

	printf("\n\nest:\n");
	fp_poly_print(gcd,'X',stdout);


	//###############################################################################################

	printf("\n\n######### Test de fq_poly_print ########\n");

	//X^5+4x+1 irréductible sur F5[X]
	uint64_t modulo[6] = {1,0,0,0,4,1};
	fp_poly_t *pmod = fp_poly_init(5, modulo, carac);
	uint64_t fq_pol_tab[3]={1,4,3};
	fp_poly_t *fq_pol = fp_poly_init(2, fq_pol_tab, carac);


	fq_poly_t *pol_fq = fq_poly_init(fq_pol, pmod);



	fq_poly_print(pol_fq,'X', stdout);

	//###############################################################################################

	printf("\n\n######### Test de fq_poly_mul ########\n");

	uint64_t fq_pol_tab2[5] = {3,1,2,0,4};
	fp_poly_t *fq_pol2 = fp_poly_init(4, fq_pol_tab2, carac);

	fq_poly_t *pol_fq2 = fq_poly_init(fq_pol2, pmod);

	fq_poly_t *multi = fq_poly_mul(pol_fq, pol_fq2);

	printf("La multiplication de :\n");
	fq_poly_print(pol_fq, 'X', stdout);
	printf("\npar:\n");
	fq_poly_print(pol_fq2, 'X', stdout);
	printf("\ndonne :\n");
	fq_poly_print(multi, 'X', stdout);

	//###############################################################################################

	printf("\n\n######### Test de fq_poly_inv ########\n");

	uint64_t test_inv_tab[5] = {4,2,0,1,4};
	fp_poly_t *test_inv_pol = fp_poly_init(4, test_inv_tab, carac);
	fq_poly_t *test_inv_fq = fq_poly_init(test_inv_pol, pmod);


	fq_poly_t *invert = fq_poly_inv(test_inv_fq);

	printf("L'inverse de :\n");
	fq_poly_print(test_inv_fq, 'X', stdout);
	printf("\nest :\n");
	fq_poly_print(invert, 'X', stdout);

	fq_poly_t *verif = fq_poly_mul(test_inv_fq, invert);

	printf("\nVérification :\n");
	fq_poly_print(verif, 'X', stdout);



	fp_poly_free(p);
	fp_poly_free(q);
	fp_poly_free(r);
	fp_poly_free(prod);
	fp_poly_free(sum);
	fp_poly_free(diff);
	fp_poly_free(quotient);
	fp_poly_free(reste);
	fp_poly_free(p_div);
	fp_poly_free(p_div2);
	fp_poly_free(p_euc1);
	fp_poly_free(p_euc2);
	fp_poly_free(gcd);

	fp_poly_free(pmod);
	fp_poly_free(fq_pol);
	fp_poly_free(fq_pol2);


	fq_poly_free(pol_fq);
	fq_poly_free(pol_fq2);
	fq_poly_free(multi);

	fp_poly_free(test_inv_pol);
	fq_poly_free(test_inv_fq);
	fq_poly_free(invert);
	fq_poly_free(verif);

	fprintf(stdout,"\n");
	return 0;
}
