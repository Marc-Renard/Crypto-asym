#include <stdint.h>
#include <stdio.h>



uint64_t sqrt_int(uint64_t);
int fast_gcd(int a, int b);


int main(void){
	uint64_t a = 65;
	uint64_t b = sqrt_int(a);
	printf("sqrt_int(%ld)=%ld\n",a,b);
	int c = 12537, d = 34356;
	int gcd = fast_gcd(c,d);
	printf("pgcd(%d,%d)=%d\n\n",c,d,gcd);
}

uint64_t sqrt_int(uint64_t a){
	int i = 63;
	while( (a>>i) ^ 1){
		i--;
	}
	//printf("bit de poids fort en position %d\n",i+1);
	//le bit de poids fort est alors en position i+1
	uint64_t sqrt = 0x0;
	/*On va désormais essayer bit par bit en partant du bit de poids fort,
	 de mettre un 1 et de regarder si le carré dépasse ou non a, s'il ne dépasse
	 pas on valide et conserve ce 1, sinon on laisse un 0*/
	for( int j = i+1; j>=0 ; j--){
		if( (sqrt ^ (1<<j))*(sqrt ^ (1<<j)) <= a ){
			sqrt = sqrt ^ (1<<j);		
		}
	}
	return sqrt;
}

//le problème de la fonction suivante est qu'elle n epermet pas d'extraire des coefficients de Bezout, elle est en revanche utile lorsque l'on veut juste calculer le pgcd car :
// par la méthode classique, on est sur que (r_i+2) < (r_1 /2) alors qu'avec cette méthode, on a (r_i+1) < (r_i/2)

int fast_gcd(int a, int b){
	int tmp = 0;
	int reste = 0;
	while( b ){ // ie b!=0
		//printf("a=%d\nb=%d\n\n",a,b);
		reste = a % b;
		if(reste > (b - reste) ){
			reste = b - reste; 
		}
		a = b;
		b = reste;
	}
	return a;
}
