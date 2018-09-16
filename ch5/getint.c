#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int);

/* getint:  get next integer from input into *pn
	exercise 5-1:  don't treat + and - as 0 */
int
getint(int *pn)
{
	int c, sign;

	while (isspace(c = getch()))	/* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);	/* it's not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		int c2 = getch();
		if (!isdigit(c2)) {
			if (c2 != EOF)
				ungetch(c2);
			ungetch(c);
			return 0;
		} else
			c = c2;
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}
