\\Question 5

E = ellinit([Mod(0,751),Mod(0,751),Mod(1,751),Mod(750,751),Mod(0,751)]);
Q  = [Mod(0,751),Mod(0,751)];
Qa = [Mod(201,751),Mod(380,751)];

M = [Mod(562,751),Mod(576,751)]; 
N = [Mod(581,751),Mod(395,751)];
N2 = [Mod(484,751),Mod(214,751)]; \\Il semblerait que le nom O soit impossible pour une variable
P = [Mod(501,751),Mod(220,751)];
R = [Mod(1,751),Mod(0,751)];
S = [Mod(1,751),Mod(0,751)];
T = [Mod(144,751),Mod(565,751)];

k = [386,209,118,589,312,483,335];
clair = [M,N,N2,P,R,S,T];
chiffre = clair;

for(i=1,#clair, chiffre[i] = [ellmul(E, Q, k[i]), elladd(E, clair[i] , ellmul(E, Qa, k[i] ) )];print(chiffre[i]););


