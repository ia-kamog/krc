void reverse(char []);

/* itoa:  convert n to characters in s */
void itoa(int n, char s[], int w)
{
	int i, sign;

	sign = n;
	i = 0;
	do {
		s[i++] = (sign > 0 ? n : -n)%10 + '0', w--;
	} while (n /= 10);
	if (sign < 0)
		s[i++] = '-', w--;
	while (w-- > 0)
		s[i++] = ' ';
	s[i] = '\0';
	reverse(s);
}
