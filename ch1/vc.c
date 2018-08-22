#include <stdio.h>

/* exercise 1-10
	visualize characters */
int
main(void)
{
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			putchar('\\');
			c = 't';
		}
		if (c == '\b') {
			putchar('\\');
			c = 'b';
		}
		if (c == '\\') {
			putchar('\\');
		}
		putchar(c);
	}
}
