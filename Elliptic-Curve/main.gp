nb = 512;
nbm = 12;
mod = 1<<nbm;
mask = 2*(4^(nbm/2)-1)/(4-1);
n = read("input.txt");
chiffre(m) = [m^2%n,kronecker(m,n),m%2];
dechiffre(c) = read("dec")(c);

m = random(1<<500)<<nb+mask;
if(dechiffre(chiffre(m)) != m,error("problème d'énoncé à signaler"));

\\La stratégie est de trouver deux chiffrés qui ne diffèrent que par le symbole de Kronecker et dont l'antécédent se termine bien par le masque 
\\comme le message origial doit forcément se terminer par un 0 alors la parité de m sera toujours 0
\\La seule chose que l'on peut faire varier dans le chiffré est donc le symbole de Kronecker


c=chiffre(m);
a=c; \\on fait une copie du chiffré
a[2]=-c[2]; \\ et on change son symbole de Kronecker


A=dechiffre(a); \\on déchiffre ce nouveau chiffré


\\ on vérifie que A on nul pour être sûr que le message soit conforme (masque) et que A est différent de C car on veut trouver deux racines distinctes de m²modn
\\les instructions dans la boucle sont les mêmes que les précédentes, et génèrent deux chiffrés
while((A==0 || A==m) ,{m=random(1<<500)<<nb+mask;c=chiffre(m); a=c;a[2]=-c[2];A=dechiffre(a);});

\\ on a a² mod n = c² mod n avec a!=c
\\ on calcule les deux facteurs non triviaux et on renvoie le plus petit des deux
p=gcd(A-m,n);
q=gcd(A+m,n);

if(p<q,print(p),print(q));

