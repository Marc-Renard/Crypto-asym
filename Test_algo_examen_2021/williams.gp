
Ur( R , P, Q ) = {
	Udn = 0; Udnmu=0; Unpu=0; Vn=0; Vnmu=0; Vdn=0; Vdnmu=0; Vnpu=0;
	Unmu = 0; Un = 1; Vnmu = 2; Vn = P;
	n = 1;
	if( R == 0, return (0));
	if( R == 1, return (1));
	r = logint(R,2);
	
	Vdn = Vn^2-2*Q^n;
	Vdnmu = P;\\Vn*Vnmu-P*Q^(n-1);
	Udn = Un*Vn;
	Udnmu = Un^2-Q*Unmu^2;
	Unmu = Udnmu; Un = Udn;
	Vnmu = Vdnmu; Vn = Vdn;
	r--;
	n = n<<1;
	\\on est à u2
	while( r >= 0,
		if( bittest(R,r) == 1, 
			Unpu = P*Un-Q*Unmu;
			Vnpu = P*Vn-Q*Vnmu;
			Unmu = Un; Un = Unpu;
			Vnmu = Vn; Vn = Vnpu;
			n++;
		);

		if( r==0, return(Un););
	
		Vdn = Vn^2-2*Q^n;
		Vdnmu = Vn*Vnmu-P*Q^(n-1);
		Udn = Un*Vn;
		Udnmu = Un^2-Q*Unmu^2;
		Unmu = Udnmu; Un = Udn;
		Vnmu = Vdnmu; Vn = Vdn;
		r--;
		n = n<<1;
	);
	return(Un);
}

UR = Ur( 2520, 6 , 1);
print(gcd(UR,451889));
 
