#include <stdio.h>

/* exercise 1-9: deduplicate spaces */
int
main(void)
{
	int pc, c;

	for (pc = EOF; (c = getchar()) != EOF; pc = c)
		if (!(pc == ' ' && c == ' '))
			putchar(c);
}
