#include <stdio.h>

/* exercise 1-10
	visualize characters */
int
main(void)
{
	int c;

	while ((c = getchar()) != EOF)
		switch (c) {
		case '\t':
			printf("\\t");
			break;
		case '\b':
			printf("\\b");
			break;
		case '\\':
			printf("\\\\");
			break;
		default: putchar(c);
		}
}
