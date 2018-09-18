#include <stddef.h>

/* strncmp:  compare at most n character, return as strcmp */
int
strncmp(const char *cs, const char *ct, size_t n)
{
	while (n-- > 0 && *cs == *ct)
		++cs, ++ct;
	return *cs - *ct;
}

/* strncpy:  copy at most n character from t to s
	fill the rest of s with '\0', return s */
char *
strncpy(char *s, const char *t, size_t n)
{
	char *p;
	
	for (p = s; n > 0 && *t != '\0'; p++, t++, n--)
		*p = *t;
	while (n-- > 0)
		*p++ = '\0';
	return s;
}

/* strncat:  append at most n characters from t to s, then append '\0' */
char *
strncat(char *s, const char *t, size_t n)
{
	char *p = s;

	while (*p)
		p++;
	while (n-- > 0 && (*p++ = *t++))
		;
	*p = '\0';
	return s;
}
