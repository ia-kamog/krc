#include <ctype.h>

/* atof:  convert string s to double */
double atof(char s[])
{
	double val, power, m;
	int i, sign, exp, atoi(char s[]);

	for (i = 0; isspace(s[i]); i++) /* skip white space */
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	if (s[i] == 'e' || s[i] == 'E') {
		exp = atoi(&s[++i]);
		if (exp < 0)
			m = 10.0, exp = -exp;
		else
			m = 0.1;
		while (exp-- > 0)
			power *= m;
	}		
	return sign * val / power;
}
