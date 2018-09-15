#include <stdio.h>

void printd(int n);

/* test printd function */
int main(void)
{
	int n;

	while (scanf("%d", &n) == 1) {
		printd(n);
		putchar('\n');
	}
	return 0;
}
