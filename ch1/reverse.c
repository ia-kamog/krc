#include <stdio.h>
#define MAXLEN	1000	/* maximal length of lines */

int getline(char buf[], int lim);
void reverse(char s[]);

/* exercise 1-19:
	test reverse function, print every input line in reverse */
int main(void)
{
	int len;
	char buf[MAXLEN];

	while ((len = getline(buf, MAXLEN)) > 0) {
		reverse(buf);
		printf("%s", buf);
	}
	return 0;
}

/* reverse:  string s in reverse */
void reverse(char s[])
{
	int i, j;
	char t;
	
	for (i = 0; s[i] != '\0' && s[i] != '\n'; ++i)
		;
	--i;
	for (j = 0; i > j; ++j, --i) {
		t = s[i];
		s[i] = s[j];
		s[j] = t;
	}
}
