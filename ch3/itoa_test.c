#include <stdio.h>

void itoa(int n, char s[], int w);

/* test atoi and itoa function */
int main(void)
{
	int n, w;
	char s[100];

	while (scanf("%d%d", &w, &n) == 2) {
		itoa(n, s, w);
		printf("%s\n", s);
	}
	return 0;
}
