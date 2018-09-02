#include <stdio.h>
#include "bits.h"

/* test bit handling functions */
int main(void)
{
	unsigned x, y;
	int p, n;

	while (scanf("%o%o%d%d", &x, &y, &p, &n) == 4)
		printf("getbits(%o, %d, %d) == %o\n"
			   "setbits(%o, %d, %d, %o) == %o\n"
			   "invert(%o, %d, %d) == %o\n"
			   "rightrot(%o, %d) == %o\n"
			   "bitcount(%o) == %d\n",
			   x, p, n, getbits(x, p, n),
			   x, p, n, y, setbits(x, p, n, y),
			   x, p, n, invert(x, p, n),
			   x, n, rightrot(x, n),
			   x, bitcount(x));
	return 0;
}
