#include <stdlib.h>
#include <stdio.h>
#include "tp2.h"

int main(int argc, char **argv){
	Fp_pol a;
	a.degre = 10;
	int a_pol[10] = {1,2,3,4,5,6,7,8,9,10};
	a.valeur = a_pol;
	for(int i=0; i < a.degre; i++){
		printf("X^%d +", (a.valeur)[i] );
	}
	return 0;
}


Fp_pol multi(Fp_pol poly1 , Fp_pol poly2, Fp_pol poly_mod, Fp_pol resultat){
	return poly1;
}
