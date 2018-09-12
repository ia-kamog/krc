#include <stdio.h>

double atof(char s[]);

/* test atof function */
int main(void)
{
	char buf[100];
	while (fgets(buf, sizeof buf, stdin) != NULL)
		printf("%f\n", atof(buf));
	return 0;
}
