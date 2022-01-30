compte_naif(E,n) = {
	nb_pt = 1; \\Initialisation à 1 pour compter le point infini dès le départ
	g = ffgen(n);
	g = ffprimroot(g); \\Générateur du groupe multiplicatif
	x = g;
	
	for(i=1,n-1,
		y = g;
		for(j=1,n-1,
			if(y^2 == x^3 + E[4]*x + E[5],nb_pt ++);
			y = y*g
		);
		x = x*g
	);
	if( E[5]==0 , nb_pt++); \\ [0,0] sur la courbe
	x = g;
	for(i=1 , n-1,
		if(0 == x^3 + E[4]*x + E[5],nb_pt ++);
		x = x*g;
	); 
	
	nb_pt;
}




n = 49; \\F1024
g = ffgen(n);
a = Mod(1,7);
b = g;

E = ellinit([a,b],g);
card = compte_naif(E,n);
print(card);
