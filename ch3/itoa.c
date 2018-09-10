#include <limits.h>
void reverse(char []);

/* itoa:  convert n to characters in s */
void itoa(int n, char s[], int w)
{
	int i;
	unsigned a;

	a = n;
	if (n < 0)
		a = UINT_MAX - a + 1;
	i = 0;
	do {
		s[i++] = a % 10 + '0', w--;
	} while (a /= 10);
	if (n < 0)
		s[i++] = '-', w--;
	while (w-- > 0)
		s[i++] = ' ';
	s[i] = '\0';
	reverse(s);
}
