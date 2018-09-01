#include <stdio.h>

int getline(char s[], int lim);
int atoi(char s[]);

/* test atoi function */
int main(void)
{
	char buf[20];

	while (getline(buf, sizeof buf) > 0)
		printf("%s = %d\n", buf, atoi(buf));
	return 0;
}
