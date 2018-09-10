void reverse(char []);

/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
	int i, sign, d;

	i = 0;
	sign = n;
	do {
		if ((d = n % 10) < 0)
			d = -d;
		s[i++] = d + '0';
	} while ((n /= 10) != 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}
