#include <stdio.h>

void strcat(char *, const char *);
int trim(char *);

// test strcat function (exercise 5-3)
int main(void)
{
	char buf1[20], buf2[sizeof buf1/2];

	while (fgets(buf1, sizeof buf1 / 2, stdin) &&
		   fgets(buf2, sizeof buf2, stdin)) {
		trim(buf1);
		trim(buf2);
		strcat(buf1, buf2);
		puts(buf1);
	}
	return 0;
}
		
