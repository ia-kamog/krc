#include <stdio.h>
#define MAXLEN	80		/* the length of line above which to warn */

/* exercise 1-17
	print lines that are too long */
int main(void)
{
	int c, len, nl;
	char buffer[MAXLEN+1];

	len = 0;
	nl = 1;
	while ((c = getchar()) != EOF) {
   		if (len < MAXLEN)
			buffer[len] = c;
		else if (len == MAXLEN) {
			buffer[len] = '\0';
			printf("%d: %s", nl, buffer);
		} else
			putchar(c);
		if (c == '\n')
			len = 0, ++nl;
		else
			++len;
		}
	return 0;
}
