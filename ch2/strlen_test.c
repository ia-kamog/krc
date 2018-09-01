int printf(const char *fmt, ...);
int getline(char s[], int lim);
int strlen(char s[]);

int main(void)
{
	enum { MAXLEN = 16 };
	int len1, len2;
	char buf[MAXLEN];

	do {
		len1 = getline(buf, MAXLEN);
		len2 = strlen(buf);
		printf("%d %d\n", len1, len2);
	} while (len1 > 0);
	return 0;
}
