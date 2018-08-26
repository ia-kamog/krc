#include <stdio.h>
#define MAXLINE	1000 /* maximum input line size */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main(void)
{
	int len;			/* current line length */
	int max;			/* maximum length seen so far */
	char line[MAXLINE];		/* current input line */
	char longest[MAXLINE];	/* longest line saved here */
	int c;

	max = 0;
	while ((len = getline(line, MAXLINE)) > 0) {
		if (len == MAXLINE-1 && line[MAXLINE-2] != '\n')
			for (c=EOF; c!='\n' && (c=getchar())!=EOF; ++len)
				;
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	}
	if (max > 0)	/* there was a line */
		printf("%d: %s", max, longest);
	if (max >= MAXLINE-1 && longest[MAXLINE-2] != '\n')
		putchar('\n');
	return 0;
}

/* copy:  copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
	int i;

	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}
