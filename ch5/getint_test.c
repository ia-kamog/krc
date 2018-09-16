#include <stdio.h>

int getint(int *pn);

/* test getint function */
int
main(void)
{
	int s, n;
	
	while ((s = getint(&n)) != EOF && s != 0)
		printf("%d\n", n);
	return 0;
}
