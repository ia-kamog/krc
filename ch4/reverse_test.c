#include <stdio.h>

void reverse(char s[]);

/* test reverse function from exercise 4-13 */
int
main(int argc, char *argv[])
{
	int i;

	for (i = 1; argv[i] != NULL; i++) {
		reverse(argv[i]);
		printf("%s\n", argv[i]);
	}
	return 0;
}
