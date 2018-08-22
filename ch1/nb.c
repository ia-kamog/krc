#include <stdio.h>

/* exercise 1-8: count blanks, tabs, and newlines */
int
main(void)
{
	int c, nb, nt, nn;

	nb = nt = nn = 0;
	while ((c = getchar()) != EOF)
		if (c == ' ')
			++nb;
		else if (c == '\t')
			++nt;
		else if (c == '\n')
			++nn;
	printf("%6s%6s%6s\n"
		   "%6d%6d%6d\n",
		   "SP", "HT", "LF",
		   nb, nt, nn);
}
