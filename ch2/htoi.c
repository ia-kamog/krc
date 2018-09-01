#include <ctype.h>
#include <stdio.h>

int htoi(const char *s);

/* exercise 2-3
	write and test htoi function */
int main(void)
{
	int n;
	char s[30];
	
	if (!fgets(s, sizeof s, stdin)) 
		return 1;
	
	n = htoi(s);
	printf("%d\n", n);

	return 0;
}

/* htoi:  extract initial characters representing
	a integer in hexadecimal notation from s.
	case insensitive: [[:space:]]*(+|-)?(0x)?[0-9a-f]+ */
int htoi(const char *s)
{
#define HTOI_SKIP_SPACES(x) do {while (isspace(*x)) ++x;} while (0)
	const char *pr = "0x";
	int sign = 1, n = 0;

	HTOI_SKIP_SPACES(s);
	switch (*s) {
	case '-':
		sign = -1;
	case '+':
		++s;
		break;
	}
	HTOI_SKIP_SPACES(s);
	while (*s && *pr && tolower(*s)==*pr)
		++s, ++pr;
	while (isxdigit(*s)) {
		int c = tolower(*s++);
		n = 16*n + c - (isdigit(c)?'0':'a'-10); // ascii only
	}
	return sign*n;
}
