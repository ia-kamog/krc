#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/* getop:  get next operator or numeric operand */
int getop(char s[])
{
	int i, c;
	static int buf = 0;
	c = buf == 0 ? getchar() : buf;
	buf = 0;
	while (c == ' ' || c == '\t')
		c = getchar();
	if (c == EOF)
		return c;
	s[0] = c;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c;	/* not a number */
	i = 0;
	if (isdigit(c))	/* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')	/* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	buf = c;
	return NUMBER;
}
