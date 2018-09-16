#include <stdio.h>

int getfloat(float *);

/* test getfloat */
int
main(void)
{
	int s;
	float n;

	while ((s = getfloat(&n)) != 0 && s != EOF)
		printf("%g\n", n);
	return 0;
}
