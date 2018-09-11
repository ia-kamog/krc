#include <stdio.h>
#define BUFSZ 1000

int strrindex(const char s[], const char t[]);

/* test strrindex function */
int main(void)
{
	char s[BUFSZ], t[BUFSZ];

	while (scanf("%s%s", s, t) == 2)
		printf("%d\n", strrindex(s, t));
}	
