#include <stdio.h>

int getline(char s[], int lim);
int lower(int);

/* test atoi function */
int main(void)
{
	int i;
	char buf[20];

	while (getline(buf, sizeof buf) > 0) {
		printf("%s", buf);
		for (i = 0; buf[i] != '\0'; ++i)
			buf[i] = lower(buf[i]);
		printf("= %s", buf);
	}
	return 0;
}
