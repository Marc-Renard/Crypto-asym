f(x) = {
	x^3-x+Mod(188,751);
}

str_to_points( mot ) = {
	v = Vec(Vecsmall( mot ));
	out = Vec(0,#v);
	for(i = 1, #v, v[i] = if(lift(v[i])<65, v[i] -= Mod(48,751), v[i] -= Mod(55,751) ); );
	for(i = 1, #v,
		for( j = 20*lift(v[i]) + 1, 20*(lift(v[i])+1),
			s = 0;
			if(issquare(f(j), &s), out[i] = [Mod(j,751), s-Mod(376,751)] ;break );		
		);	
	);
	out;
}


test = str_to_points("STOP007");
print(test);

