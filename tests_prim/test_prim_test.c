#include "test_prim.h"
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>


int main(int argc, char **argv){

	uint64_t a=27, b=45;
	fprintf(stdout, "gcd(%ld,%ld)=%ld\n",a,b,gcd(a,b));
	return 0;
}
