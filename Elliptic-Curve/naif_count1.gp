compte_naif(a, b, n) = {
	delta = -16 * ( 4*a^3 + 27*b^2 );
	if( delta == 0, print("Ces coefficients ne définissent pas un courbe elliptique");return(0));
	nb_pt = 1; \\Initialisation à 1 pour compter le point infini dès le départ
	if(isprime(n), g = znprimroot(n),
		g = ffgen(n);
		g = ffprimroot(g); \\Générateur du groupe multiplicatif
	);
	x = g;
	\\x!=0 && y!=0
	for(i=1,n-1,
		y = g;
		for(j=1,n-1,
			if(y^2 == x^3 + a*x + b,nb_pt ++);
			y = y*g
		);
		x = x*g
	);
	\\x==0 && y==0
	if( b==0 , nb_pt++); \\ [0,0] sur la courbe
	x = g;
	\\y==0 && x!=0
	for(i=1 , n-1,
		if(0 == x^3 + a*x + b,nb_pt ++);
		x = x*g;
	); 
	\\x==0 && y!=0
	y = g;
	for(i=1 , n-1,
		if(y^2 == b,nb_pt ++);
		y = y*g;
	); 
	
	nb_pt;
}



n = 125;
\\n = 151; 
h = ffgen(n);
g = ffprimroot(h);
\\g = znprimroot(n);
a = Mod(1,5)*g^5;
\\a = g^5;
b = g^7;

card = compte_naif(a, b, n);
print(card);
