#include <limits.h>
#include <stdio.h>
#include <string.h>

void expand(const char s1[], char s2[]);

/* test expand function */
int main(void)
{
	char s1[CHAR_MAX], s2[CHAR_MAX], *p;
	if (fgets(s1, CHAR_MAX, stdin) == NULL)
		return 1;
	if ((p=strrchr(s1,'\n')) != NULL)
		*p = '\0';
	expand(s1,s2);
	puts(s2);
}
