compte_naif(a, b, n) = {
	if(!isprime(n), print("n n'est pas premier"); return(0));
	delta = -16 * ( 4*a^3 + 27*b^2 );
	if( delta == 0, print("Ces coefficients ne définissent pas un courbe elliptique");return(0));
	nb_pt = 1; \\Initialisation à 1 pour compter le point infini dès le départ
	g = znprimroot(n);
	x = g;
	
	for(i=1,n-1,
		test = x^3 + a*x + b;
		if(test == 0, nb_pt++,
			if( kronecker(lift(test), n) == 1, nb_pt = nb_pt + 2);
		);	
		x = x*g
	);
	if( b==0 , nb_pt++, \\ [0,0] sur la courbe
		if( kronecker( lift(b), n) == 1, nb_pt = nb_pt + 2 );
	); 
	x = g;
	
	nb_pt;
}




n = 151; \\
g = znprimroot(n);
a = g^5;
b = g^7;

card = compte_naif(a, b, n);
print(card);
