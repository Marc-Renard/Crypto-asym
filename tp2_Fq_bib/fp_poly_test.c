#include <fp_poly.h>

int main(int agrc, char **argv)
{
	uint64_t carac = 5;
	uint64_t a[3] = {1,2,1};
	fp_poly_t*p = fp_poly_init(2,a, carac);
	printf("Tests de fp_poly_print :\n");
	fp_poly_print(p,'X',stdout);
	
	
	uint64_t b[2] = {1,2};
	fp_poly_t *q = fp_poly_init(1, b, carac);
	
	
	uint64_t c[3] = {1,2,3};
	fp_poly_t *r = fp_poly_init(2, c, carac);
	fp_poly_print(r,'X',stdout);
	
	
	fp_poly_t* res = fp_poly_mul(q,r);
	
	printf("La multiplication dans F_%ld[X] de\n", carac);
	fp_poly_print(q,'X',stdout);
	printf("par\n");
	fp_poly_print(r,'X',stdout);
	printf("donne\n");
	
	
	fp_poly_print(res,'X',stdout);
	fp_poly_free(p);
	fp_poly_free(q);
	fp_poly_free(r);
	fp_poly_free(res);
	return 0;
}
