void reverse (char s[]);

/* itob:  store 'b' base representation of number 'n' into 's' */
void itob(int n, char s[], int b)
{
	int sign, d, i;
	char digs[] = "0123456789abcdefghjklmnoprstvwxyz";

	if (b >= sizeof digs|| b <= 1)
		b = 10;
	sign = n;
	i = 0;
	do {
		s[i++] = digs[(sign<0?-n:n)%b];
	} while (n /= b);
	s[i] = '\0';
	reverse(s);
}
