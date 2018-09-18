#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* getline:  read a line into s, at most lim characters, return length */
int
getline(char *s, int lim)
{
	int c, i;

	for (i = 0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; i++)
		*s++ = c;
	if (c == '\n')
		*s++ = c, i++;
	*s = '\0';
	return i;
}

/* atoi:  extract an integer from the string s */
int
atoi(const char *s)
{
	int n = 0, sign = 1;
	
	while (isspace(*s))
		s++;
	switch (*s) {
	case '-': sign = -1;
	case '+': s++;
	}		
	for (; isdigit(*s); s++)
		n = 10 * n + (*s - '0');
	return sign * n;
}
/* reverse the character string s */
void
reverse(char *s)
{
	char *p, t;
	
	for (p=s+strlen(s)-1; s < p; s++, p--)
		t = *s, *s = *p, *p = t;
}

/* itoa:  write decimal representation of the number n into s */
void
itoa(int n, char *s)
{
	char *p = s;
	bool sign = n < 0;
	unsigned m = n;
	
	if (sign)
		m = UINT_MAX - m + 1;
	do {
		*p++ = m % 10 + '0';
	} while (m /= 10);
	if (sign)
		*p++ = '-';
	*p = '\0';
	reverse(s);
}

/* strindex:  return index of t in s, -1 if none */
int strindex(char *s, char *t)
{
	char *p, *s0 = s;

	for (; *s; s++) {
		for (p = t; *p && *(p-t+s)==*p; ++p)
			;
		if (p != t && !*p)
			return s - s0;
	}
	return -1;
}

#define NUMBER '0'
int getch(void);
void ungetch(int);

/* getop:  get the next operator or numeric operand */
int
getop(char *s)
{
	int c;

	while ((*s = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c;
	if (isdigit(c))
		while (isdigit(*++s = c = getch()))
			;
	if (c == '.')
		while (isdigit(*++s = c = getch()))
			;
	*s = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}
