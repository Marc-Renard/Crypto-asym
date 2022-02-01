dup_ell(P, carac, a) = {
	if( carac != 2 && carac != 3,
		if( P[2] == 0 , return ([+oo,+oo]));
		x = ((3*(P[1])^3 + a)/(2*P[2]))^2 - 2 * P[1];
		y = (((3*(P[1])^3 + a)/(2*P[2]))^2) * (P[1] - x) - P[2];
		return ([x,y]),
	\\else
		if(carac == 2,
			
		);
	);
}

add_ell(P,Q, carac, a) = {
	if(P[1] == +oo, return (Q));
	if(Q[1] == +oo, return (P));
	if( carac != 2 && carac != 3,
		if(P[1] == Q[1] && P[2]!=Q[2], return ([+oo,+oo]) );
		if( P[1] == Q[1] && P[2]==Q[2], return (dup_ell(P, carac, a)) );
		x = ((Q[2]-P[2])/(Q[1]-P[1]))^2 - P[1] - Q[1];
		y = (((Q[2]-P[2])/(Q[1]-P[1]))^2) * (P[1] - x) - P[2];
		return ([x,y]), 
	\\else
		if( carac == 2,
		
		
		
		);	
	);
}
