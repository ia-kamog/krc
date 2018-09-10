#include <stdio.h>

int atoi(const char s[]);
void itoa(int n, char s[]);

/* test atoi and itoa function */
int main(void)
{
	int n;
	char buf[100], s[100];

	while (fgets(buf, sizeof buf, stdin)) {
		n = atoi(buf);
		itoa(n, s);
		printf("%s\n", s);
	}

	return 0;
}
