#include <stdio.h>

void itob(int n, char s[], int b);

/* test itob function */
int main(void)
{
	int n, b;
	char s[100];

	while (scanf("%d%d", &b, &n) == 2) {
		itob(n, s, b);
		puts(s);
	}
	return 0;
}
