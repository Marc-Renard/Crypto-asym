#include "test_prim.h"
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>


int main(int argc, char **argv){

	printf("\nTest de primalité de Fermat\n\n");
	for(int i = 3; i < 30 ; i++){
		if(isprime_Fermat(i,20)){
			fprintf(stdout,"%d est probablement premier\n",i);
		}else{
			fprintf(stdout,"%d n'est pas premier\n",i);
		}
	}

	printf("\n##################################################\n\n");

	printf("\nTest de primalité de Solovay-StraBen\n\n");
	for(int i = 3; i < 30 ; i++){
		if(isprime_Solovay_StraBen(i,20)){
			fprintf(stdout,"%d est probablement premier\n",i);
		}else{
			fprintf(stdout,"%d n'est pas premier\n",i);
		}
	}

	printf("\n##################################################\n\n");

	//Miler Rabin

	printf("\nTest de primalité de Miller Rabin\n\n");
	for(int i = 3; i < 30 ; i++){
		if(isprime_Miller_Rabin(i,20)){
			fprintf(stdout,"%d est probablement premier\n",i);
		}else{
			fprintf(stdout,"%d n'est pas premier\n",i);
		}
	}

	printf("\n##################################################\n\n");

	return 0;
}
