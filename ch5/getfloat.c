#include <ctype.h>
#include <math.h>
#include <stdio.h>

int getch(void);
void ungetch(int);
int getint(int *);

/* getfloat:  get next float from input into *pf */
int
getfloat(float *pf)
{
	int c, sign, p, c2;
	float power;

	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	c2 = c;
	if ((c == '+' || c == '-') &&
		!(isdigit(c2=getch()) || c2 == '.')) {
		if (c2 != EOF)
			ungetch(c2);
		ungetch(c);
		return 0;
	}
	c = c2;
	for (*pf = 0.0; isdigit(c); c = getch())
		*pf = 10.0 * *pf + (c - '0');
	power = 1.0;
	if (c == '.')
		for (; isdigit(c = getch()); power /= 10.0)
			*pf = 10.0 * *pf + (c - '0');
	*pf *= power;
	p = 0;
	if ((c == 'e' || c == 'E') && (c2 = getint(&p)) == 0) {
		ungetch(c);
		return c;
	} else
		c = c2;
	power = pow(10.0, p);
	*pf *= power * sign;
	return c;
}
