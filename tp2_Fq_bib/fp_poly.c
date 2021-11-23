#include <fp_poly.h>
#include <string.h>

void fp_poly_free(fp_poly_t* p)
{
	free(p->coeffs);
	free(p);
	return;
}

fp_poly_t *fp_poly_init(uint64_t degre, uint64_t* coeffs, uint64_t carac)
{
	fp_poly_t *p = calloc( sizeof(fp_poly_t) );
	if(!p)
	{
		return NULL;
	}
	p->degre = degre;
	uint64_t *tab = calloc( (degre + 1) * sizeof(uint64_t) );
	memcpy(tab, coeffs, (degre + 1)  * sizeof(uint64_t));
	p->coeffs = tab;
	p->carac = carac;
	return p;
}

int fp_poly_print(fp_poly_t *p, char var, FILE * os){
	uint64_t deg = p->degre;
	if( (deg == 0) && ( p->coeffs[0] == 0 )  ){ //poly == 0
		fprintf(os, "Polynome identiquement nul :\n0\n\n");
		return 0;
	}
	if( deg == 0 ){
		fprintf(os, "%ld\n\n", p->coeffs[0]);
		return 0; 
	}
	//Le terme de plaut haut degre n'a pas de + devant lui, c'est pourquoi il est traité à part
	if( p->coeffs[0] == 1 ){
		if(deg == 1){
			fprintf(os,"%c",var);
		}else{
			fprintf(os,"%c^%ld",var , deg);
		}
	}else{
		if(deg == 1){
			fprintf(os,"%c",var );
		}else{
			fprintf(os,"%ld%c^%ld",p->coeffs[0] ,var , deg);
		}
		
	}
	if( deg == 1 ){
		if( p->coeffs[1] !=0 ){
			fprintf(os," + %ld",p->coeffs[1] );
		}
		fprintf(os,"\n\n");
		return 0;
	}
	for( int i = 1; i <= deg - 2; i++){
		if( p->coeffs[i] ){ //ie coefficient non nul
			if( p->coeffs[i] == 1 ){
				fprintf(os," + %c^%ld", var, deg - i);
			}else{
				fprintf(os," + %ld%c^%ld",p->coeffs[i] , var, deg - i);
			}

		}
	}
	
	if( p->coeffs[deg - 1] ){ // coefficient en X non nul
		fprintf(os," + %ld%c",p->coeffs[deg - 1] , var);
	}
	
	if( p->coeffs[deg] ){ // coefficient constant non nul
		fprintf(os," + %ld", p->coeffs[deg]);
	}
	
	fprintf(os,"\n\n");
	return 0;
}

fp_poly_t *fp_poly_mul(const fp_poly_t *p,const  fp_poly_t *q)
{
	if( p->carac != q->carac){
		fprintf(stderr,"Les polyomes doivent être dans le même corps, et donc avoir la même caractérisqtique\n");
	}
	uint64_t deg = p->degre + q->degre;
	uint64_t c[ deg + 1 ];
	for(uint64_t i = 0; i <= deg; i++){
		c[i] = 0;
		for(uint64_t j = 0 ; j <=i ; j++){
			if( j > (p->degre) ){
				break;
			}else{
				if( (i-j) <= ( q->degre ) ){
					c[i] = (c[i] + ( p->coeffs[j] )*( q->coeffs[i-j] ))%(p->carac);
				}
			}
		}
	}
	fp_poly_t *res = fp_poly_init(deg, c, p->carac);
	return res;
}
