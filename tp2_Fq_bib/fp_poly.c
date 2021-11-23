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
	fp_poly_t *p = calloc( 1, sizeof(fp_poly_t) );
	if(!p)
	{
		return NULL;
	}
	p->degre = degre;
	uint64_t *tab = calloc( (degre + 1) , sizeof(uint64_t) );
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

//Multiplication de p par q
fp_poly_t *fp_poly_mul(const fp_poly_t *p,const  fp_poly_t *q)
{
	if( p->carac != q->carac){
		fprintf(stderr,"Les polyomes doivent être dans le même corps, et donc avoir la même caractérisqtique\n");
		return NULL;
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
	if( res == NULL){
		fprintf(stderr, "Erreur initialisation\n");
	}
	return res;
}

//Addition p1 + p2
fp_poly_t *fp_poly_add(const fp_poly_t *p1,const fp_poly_t *p2){
	if( p1->carac != p2->carac ){
		fprintf(stderr, "Les coefficients des deux polynômes doivent être dans le même corps pour l'addition.\n");
		return NULL;
	}
	uint64_t deg1 = p1->degre;
	uint64_t deg2 = p2->degre;
	uint64_t deg_res = 0;
	//On détermine le degré du résultat
	if( deg1 >= deg2){
		deg_res = deg1;
	}else{
		deg_res = deg2;
	}
	uint64_t sum[deg_res + 1];
	memset(sum, 0, sizeof(uint64_t)*(deg_res + 1));

	uint64_t i = 0;

	for(i = 0 ; i <= deg1; i++){
		sum[deg_res - i] = p1->coeffs[deg1 - i];
	}

	for( i = 0 ; i <= deg2 ; i++ ){
		sum[deg_res - i] = (sum[deg_res - i] + p2->coeffs[deg2 - i]) % (p1->carac);
	}

	fp_poly_t *res = fp_poly_init(deg_res, sum, p1->carac);
	if( res == NULL){
		fprintf(stderr, "Erreur initialisation\n");
	}
	return res;
}

//Soustraction p1 - p2
fp_poly_t *fp_poly_sub(const fp_poly_t *p1,const fp_poly_t *p2){
	if( p1->carac != p2->carac ){
		fprintf(stderr, "Les coefficients des deux polynômes doivent être dans le même corps pour la soustraction.\n");
		return NULL;
	}
	uint64_t deg1 = p1->degre;
	uint64_t deg2 = p2->degre;
	uint64_t deg_res = 0;
	//On détermine le degré du résultat
	if( deg1 >= deg2){
		deg_res = deg1;
	}else{
		deg_res = deg2;
	}
	uint64_t diff[deg_res + 1];
	memset(diff, 0, sizeof(uint64_t)*(deg_res + 1));

	uint64_t i = 0;

	for(i = 0 ; i <= deg1; i++){
		diff[deg_res - i] = p1->coeffs[deg1 - i];
	}

	for( i = 0 ; i <= deg2 ; i++ ){
		diff[deg_res - i] = (diff[deg_res - i] + p1->carac - p2->coeffs[deg2 - i]) % (p1->carac);
	}
	i = 0;
	//il faut déterminer le degré du res ici
	if(diff[i] == 0){
		//il faut déterminer le degré du res ici
		i = 1;
		while( diff[i] == 0 ){
			i++;
		}
		deg_res -= i;
		//On remplit un tableu de la bonne taille pour créer le polynôme
		uint64_t tab_res[deg_res + 1];
		for(uint64_t j = 0; j <= deg_res; j++){
			tab_res[j] = diff[ i + j ];
		}
		fp_poly_t *res = fp_poly_init(deg_res, tab_res, p1->carac);
		if( res == NULL){
			fprintf(stderr, "Erreur initialisation\n");
		}
			return res;
	}else{
		fp_poly_t *res = fp_poly_init(deg_res, diff, p1->carac);
		if( res == NULL){
			fprintf(stderr, "Erreur initialisation\n");
		}
		return res;
	}


}

//Inverse modulo p
int64_t inv_mod(int64_t a, int64_t p){
	int64_t u0 = 1, u1 = 0, r0 = a, r1 = p;
	int64_t u_tmp, r_tmp, q;
	while(r1 != 0){
		q = r0 / r1;
		r_tmp = r0;
		u_tmp = u0;
		r0 = r1;
		u0 = u1;
		r1 = r_tmp - q * r1;
		u1 = u_tmp - q * u1;
	}
	return (u0 + p)%p;



}



//Division euclidienne : a = bq + r avec deg(r)<deg(b)
void fp_poly_div(const fp_poly_t *a, const fp_poly_t *b, fp_poly_t **q, fp_poly_t **r){
	if( a->carac != b->carac ){
		fprintf(stderr, "Les coefficients des deux polynômes doivent être dans le même corps pour la division.\n");
		return;
	}
	uint64_t deg_a = a->degre;
	uint64_t deg_b = b->degre;
	if(deg_a < deg_b){
		*r = fp_poly_init(a->degre,a->coeffs, a->carac);
		uint64_t tab[1] = {0};
		*q = fp_poly_init(0, tab, a->carac);
		return;
	}
	//Ici deg a >= deg b
	
	//Récupération des deux tableaux
	uint64_t a_tab[deg_a + 1]; //contiendra le reste à la fin
	uint64_t b_tab[deg_b + 1];
	memcpy(a_tab, a->coeffs, (deg_a + 1)*sizeof(uint64_t));
	memcpy(b_tab, b->coeffs, (deg_b + 1)*sizeof(uint64_t));

	uint64_t diff = deg_a - deg_b;
	uint64_t quotient[diff + 1];
	uint64_t i_quotient = 0;
	uint64_t deg_coef_dominant_a = deg_a;
	uint64_t inv = inv_mod(b_tab[0], a->carac);
	while(deg_coef_dominant_a >= deg_b){
		if(a_tab[deg_a - deg_coef_dominant_a] != 0){
			uint64_t m = (inv * a_tab[deg_a - deg_coef_dominant_a])%(a->carac);
			for(uint64_t i = 0; i <= deg_b ; i++ ){
				a_tab[deg_a - deg_coef_dominant_a + i ] = (a_tab [ deg_a - deg_coef_dominant_a + i ] + a->carac - ((m * b_tab[i]) %a->carac) ) % a->carac;
			}
			quotient[i_quotient] = m;
		}else{
			quotient[i_quotient] = 0;
		}
		i_quotient++;
		deg_coef_dominant_a--;
	}

	*q = fp_poly_init(diff, quotient, a->carac);

	//On cherche le degré du reste
	uint64_t deg_reste = deg_b;
	while( (a_tab[ deg_a - deg_reste ] == 0) && (deg_reste>=0) ){
		deg_reste--;
	}
	if( (deg_reste == 0) && ( a_tab[deg_a] == 0 ) ){ //le reste est nul
		uint64_t r_tab[1]={0};
		*r = fp_poly_init(0,r_tab,a->carac);
		return;
	}else{
		uint64_t r_tab[deg_reste + 1];
		memcpy(r_tab, &(a_tab[deg_a - deg_reste]), (deg_reste + 1) * sizeof(uint64_t));
		*r = fp_poly_init(deg_reste, r_tab, a->carac);
		return;
	}

}