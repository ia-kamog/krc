#include <stdio.h>

void itoa(int n, char s[]);

/* test atoi and itoa function */
int main(void)
{
	int n;
	char s[100];

	while (scanf("%d", &n) == 1) {
		itoa(n, s);
		printf("%s\n", s);
	}
	return 0;
}
