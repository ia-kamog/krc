#include <stdio.h>

#define IN	1	/* in a word */
#define OUT	0	/* out of a word */

/* exercise 1-12
	print words per line */
int main(void)
{
	int c, state;

	state = OUT;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n') {
			if (state == IN)
				putchar('\n');
			state = OUT;
		} else {
			state = IN;
			putchar(c);
		}
	}
}
