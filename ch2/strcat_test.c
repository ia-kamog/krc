#include <stdio.h>
#define MAXLINE 200

void strcat(char s[], char t[]);
void chomp(char s[]);

/* test strcat function */
int main(void)
{
	char s1[MAXLINE], s2[MAXLINE];
	if (fgets(s1, MAXLINE, stdin) == NULL ||
		fgets(s2, MAXLINE, stdin) == NULL)
		return 1;
	chomp(s1);
	strcat(s1,s2);
	fputs(s1, stdout);
	return 0;
}

/* chomp:  remove trailing '\n' from s */
void chomp(char s[])
{
	int i;

	for (i = 0; s[i] != '\0'; ++i)
		if (s[i] == '\n' && s[i+1] == '\0')
			s[i] = '\0';
}
