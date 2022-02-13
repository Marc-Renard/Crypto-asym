#include "rho.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    uint64_t a = 3, b = 5, y = 2, mod = 37, alpha = 0, beta = 0;
    y = func(y, a, b, &alpha, &beta, mod);
    y = func(y, a, b, &alpha, &beta, mod);
    y = func(y, a, b, &alpha, &beta, mod);
    fprintf(stdout, "y=%ld, a=%ld, b=%ld, alpha=%ld, beta=%ld\n\n",y,a,b,alpha, beta);

    uint64_t g = 2, h = 5, n = 1019;
    uint64_t log = rho_log(h, g, n);
    fprintf(stdout, "Log_%ld(%ld mod %ld)=%ld\n", g, h, n, log);

    return 0;
}