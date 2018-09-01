#include <stdio.h>
#define MAXLINE 100

int any(const char s1[], const char s2[]);

/* exercise 2-5
	test any function */
int main(void)
{
	int r;
	char s1[MAXLINE], s2[MAXLINE];

	if (fgets(s1, sizeof s1, stdin) == NULL ||
		fgets(s2, sizeof s2, stdin) == NULL)
		return 1;
	r = any(s1,s2);
	if (r >= 0)
		printf("%d\n%x\n", r, s1[r]);
	else
		puts("not found");
	return 0;
}

/* any:  find position of the first character from s2 that is found in s1 */
int any(const char s1[], const char s2[])
{
	int i, j;

	for (i = 0; s1[i] != '\0'; ++i)
		for (j = 0; s2[j] != '\0'; ++j)
			if (s1[i] == s2[j])
				return i;
	return -1;
}
