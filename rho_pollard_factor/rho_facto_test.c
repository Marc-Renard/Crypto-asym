#include "rho_facto.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	mpz_t n,factor;
	mpz_inits(n,factor,NULL);
	mpz_set_str(n,"52590354464570687296135717939981",10);
	mpz_rho_factor(factor, n);

	if( !mpz_out_str(stdout, 10,factor)){
		fprintf(stderr, "Error while printing factor\n");
		return -1;
	}
	fprintf(stdout, "\n");
	mpz_clears(n,factor,NULL);
	return 0;
}
