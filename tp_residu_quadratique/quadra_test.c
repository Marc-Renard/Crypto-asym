#include "quadra.h"
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>


int main(int argc, char **argv){
	uint64_t a = 4,pow = 6, mod = 11;
	printf("%ld^%ld = %ld mod %ld\n\n",a,pow,exp_bin_mod(a,pow,mod),mod);

	uint64_t mod2 = 17;
	for(uint64_t i = 1 ; i < mod2 ; i++){
		uint64_t sqrt = sqrt_Shanks_Tonelli(i ,mod2);
		if(sqrt!=0){
			printf("\nUne racine de %ld mod %ld est %ld\n",i,mod2,sqrt);

			printf("Vérification :\n%ld^2=%ld mod %ld\n\n",sqrt,exp_bin_mod(sqrt , 2 , mod2), mod2);
		}
	}
	


	uint64_t b = 302, p = 2081;

	uint64_t sqrt_b = sqrt_Shanks_Tonelli(b ,p);

	printf("\nUne racine de %ld mod %ld est %ld\n",b,p,sqrt_b);

	printf("Vérification :\n%ld^2=%ld\n",sqrt_b,exp_bin_mod(sqrt_b , 2 , p));

	return 0;
}