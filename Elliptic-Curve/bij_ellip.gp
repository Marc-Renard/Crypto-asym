f(x) = {
	x^3-x+Mod(188,751);
}

str_to_points( mot ) = {
	v = Vec(Vecsmall( mot ));
	out = Vec(0,#v);
	for(i = 1, #v, v[i] = if( lift(v[i]) <65, v[i] -= Mod(48,751), v[i] -= Mod(55,751) ); );
	for(i = 1, #v,
		for( j = 20*lift(v[i]) + 1, 20*(lift(v[i])+1),
			s = 0;
			if(issquare(f(j), &s), out[i] = [Mod(j,751), s-Mod(376,751)] ;break );		
		);	
	);
	out;
}

points_to_str( V ) = {
	for( i = 1, #V, V[i] = lift(V[i][1]));
	for( i = 1, #V,
		if( V[i] % 20 == 0, V[i] = V[i]/20 + 1,
		V[i] = floor(V[i]/20));
	);
	for( i = 1, #V, if(V[i] > 9, V[i] += 55, V[i] += 48  ););
	Strchr(V);
}

test = str_to_points("STOP007");
print(test);

test2 = [[Mod(361,751),Mod(383,751)],[Mod(241,751),Mod(605,751)],[Mod(201,751),Mod(380,751)],[Mod(461,751),Mod(467,751)],[Mod(581,751),Mod(395,751)]];

print("\nRéponse :\n")
print(points_to_str(test2));
