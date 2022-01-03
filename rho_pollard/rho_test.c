#include "rho.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    uint64_t a = 3, b = 5, y = 2, mod = 37, alpha = 0, beta = 0;
    f(&y, a, b, &alpha, &beta, mod);
    f(&y, a, b, &alpha, &beta, mod);
    f(&y, a, b, &alpha, &beta, mod);
    fprintf(stdout, "y=%ld, a=%ld, b=%ld, alpha=%ld, beta=%ld\n",y,a,b,alpha, beta);
    return 0;
}