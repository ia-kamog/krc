#include <stdio.h>
#define NUMRANDS 10	/* how many random numbers to print */
int rand(void);
void srand(unsigned int seed);

/* test rand and srand functions */
int main(void)
{
	unsigned int s;	/* seed */
	int i;

	puts("enter the seed");
	if (scanf("%u", &s) != 1) {
		fputs("bad input\n", stderr);
		return 1;
	}
	srand(s);
	for (i = 1; i <= NUMRANDS; ++i)
		printf("%d\n", rand());

	return 0;
}
