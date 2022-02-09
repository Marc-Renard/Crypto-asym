dup_ell(P, carac, a1, a2, a3, a4, a6) = {
	if( carac != 2 && carac != 3,
		if( P[2] == 0 , return ([+oo,+oo]));
		x = ((3*(P[1])^3 + a4)/(2*P[2]))^2 - 2 * P[1];
		y = (((3*(P[1])^3 + a4)/(2*P[2]))^2) * (P[1] - x) - P[2];
		return ([x,y]),
	\\else

	);
}

add_ell(P,Q, carac, a) = {
	if(P[1] == +oo, return (Q));
	if(Q[1] == +oo, return (P));
	if( carac != 2 && carac != 3,
		if(P[1] == Q[1] && P[2]!=Q[2], return ([+oo,+oo]) );
		if( P[1] == Q[1] && P[2]==Q[2], return (dup_ell(P, carac, a4)) );
		x = ((Q[2]-P[2])/(Q[1]-P[1]))^2 - P[1] - Q[1];
		y = (((Q[2]-P[2])/(Q[1]-P[1]))^2) * (P[1] - x) - P[2];
		return ([x,y]), 
	\\else

	);
}
