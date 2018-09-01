#include <stdio.h>
#define MAXLINE 100

void squeeze(char s1[], char s2[]);

/* test squeeze function for exercise 2-4 */
int main(void)
{
	char s1[MAXLINE], s2[MAXLINE];

	if (fgets(s1, MAXLINE, stdin) == NULL ||
		fgets(s2, MAXLINE, stdin) == NULL)
		return 1;

	squeeze(s1, s2);
	puts(s1);
	return 0;
}
