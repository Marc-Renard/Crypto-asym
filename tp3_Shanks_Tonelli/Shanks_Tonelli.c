#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint64_t nombre

nombre sqrt_S_T(nombre a, nombre p);



nombre sqrt_S_T(nombre a, nombre p){
	nombre order = p - 1;
	nombre power_of_2 = 0;
	nombre odd = order;
	while( (odd & 1) == 0 ){ //Tant que odd est pair
		odd >>= 1; //odd = odd/2
		power_of_2++; //on augmente la puissance de 2
	}
	// à cette étape on a p - 1 = 2^power_of_2 * odd avec odd impair

	//trouver un résidu non quadratique(Utiliser une fonction Jacobi)

}