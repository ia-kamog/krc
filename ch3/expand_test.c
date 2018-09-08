#include <limits.h>
#include <stdio.h>

void expand(const char s1[], char s2[]);

/* test expand function */
int main(void)
{
	char s1[CHAR_MAX], s2[CHAR_MAX];
	if (fgets(s1, CHAR_MAX, stdin) == NULL)
		return 1;
	expand(s1,s2);
	puts(s2);
}
