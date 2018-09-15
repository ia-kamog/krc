#include <limits.h>

static int utoa(unsigned n, char s[]);
/* itoa:  put string of decimal representation of 'n' in 's' */
void itoa(int n, char s[])
{
	int p;
	
	if (n < 0)
		s[0] = '-', utoa(UINT_MAX - n + 1U, s+1);
	else if (n == 0)
		s[0] = '0', s[1] = '\0';
	else
		utoa(n, s);
}

/* utoa: convert non-zero unsigned integer into its string 
	decimal representation */
static int
utoa(unsigned n, char s[])
{
	int p;

	if (n == 0) {
		s[0] = '\0';
		return 0;
	}
	p = utoa(n / 10u, s);
	s[p] = n % 10u + '0';
	s[p+1] = '\0';
	return p+1;
}
