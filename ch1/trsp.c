#include <ctype.h>
#include <stdio.h>
#define MAXLEN	1000	/* max length of a line */

int getline(char buf[], int lim);
void trsp(char buf[], int lim);

/* exercise 1-18
	remove trailing space and empty lines */
int main(void)
{
	int len;
	char buf[MAXLEN];

	while ((len = getline(buf, MAXLEN)) > 0) {
		trsp(buf, MAXLEN);
		printf("%s", buf);
	}
}

/* trsp:  remove trailing space from buf */
void trsp(char buf[], int lim)
{
	int p, i;

	p = -1;
	for (i = 0; buf[i] != '\0'; ++i)
		if (!isspace(buf[i]))
			p = i;
	if (p == -1)
		buf[0]='\0';
	else if (p < lim-2) {
		buf[p+1] = '\n';
		buf[p+2] = '\0';
	}
}
