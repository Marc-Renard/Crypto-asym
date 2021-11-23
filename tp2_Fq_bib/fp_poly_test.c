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
	
	
	uint64_t b[2] = {1,2};
	fp_poly_t *q = fp_poly_init(1, b, carac);
	if( q == NULL){
		fprintf(stderr, "Erreur initialisation\n");
		return -1;
	}
	
	uint64_t c[3] = {1,2,4};
	fp_poly_t *r = fp_poly_init(2, c, carac);
	fp_poly_print(r,'X',stdout);

	//###############################################################################################

	
	printf("\n######## Test de la multiplication ########\n");	
	fp_poly_t *prod = fp_poly_mul(q,r);
	
	printf("La multiplication dans F_%ld[X] de\n", carac);
	fp_poly_print(q,'X',stdout);
	printf("par\n");
	fp_poly_print(r,'X',stdout);
	printf("donne\n");
	if( prod == NULL ){
		fprintf(stderr,"Erreur lors de la multiplication\n");
		return -1;
	}else{
		fp_poly_print(prod,'X',stdout);
	}
	

	//###############################################################################################

	fp_poly_t *sum = fp_poly_add(prod, r);

	printf("\n######### Test de l'addition ########\n");
	printf("L'addition dans F_%ld[X] de\n", carac);
	fp_poly_print(prod,'X',stdout);
	printf("et\n");
	fp_poly_print(r,'X',stdout);
	printf("donne\n");
	if( sum == NULL ){
		fprintf(stderr,"Erreur lors de l'addition\n");
		return -1;
	}else{
		fp_poly_print(sum,'X',stdout);
	}
	
	//###############################################################################################

	fp_poly_t *diff = fp_poly_sub(r, p);

	printf("\n######### Test de la soustraction ########\n");
	printf("La soustraction dans F_%ld[X] de\n", carac);
	fp_poly_print(r,'X',stdout);
	printf("-\n\n");
	fp_poly_print(p,'X',stdout);
	printf("donne\n\n");
	if( diff == NULL ){
		fprintf(stderr,"Erreur lors de la soustraction\n");
		return -1;
	}else{
		fp_poly_print(diff,'X',stdout);
	}
	

	//####################################################################################
	printf("\n######### Test de l'inverse de a mod p ########\n");
	int64_t aa = 3, mod = 13;
	int64_t inv = inv_mod( aa, mod);
	printf("Inv de %ld mod %ld --> %ld\n",aa,mod,inv);


	//###############################################################################################

	uint64_t poly_div[6] = {4,3,0,1,0,2};
	fp_poly_t *p_div = fp_poly_init(5,poly_div, carac);
	uint64_t poly_div2[4] = {3,0,2,4};
	fp_poly_t *p_div2 = fp_poly_init(3,poly_div2, carac);

	fp_poly_t *quotient = NULL;
	fp_poly_t *reste = NULL;
	fp_poly_div(p_div, p_div2, &quotient, &reste);

	printf("\n######### Test de la division Euclidienne ########\n");
	fp_poly_print(p_div,'X',stdout);
	printf("divisé par\n\n");
	fp_poly_print(p_div2,'X',stdout);

	printf("donne\n\nReste:\n");
	fp_poly_print(reste,'X',stdout);

	printf("Qutient:\n");
	fp_poly_print(quotient,'X',stdout);

	
	






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
	return 0;
}
