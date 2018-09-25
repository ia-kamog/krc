#include <ctype.h>
#include <stdio.h>

static void upper(void);
static void lower(void);
static void usage(void);

/* case:  convert input to a given case 
	exercise 7-1 */
int
main(int argc, char *argv[])
{
	if (argc != 2 || argv[1][0] != '-' ||
		!(argv[1][1] == 'u' || argv[1][1] == 'l') ||
		argv[1][2] != '\0') {
		fprintf(stderr, "usage: case (-l|-u)\n");
		return 1;
	}
	if (argv[1][1] == 'u')
		upper();
	else
		lower();
	return 0;
}

/* lower:  convert to lower case */
static void
lower(void)
{
	int c;

	while ((c = getchar()) != EOF)
		putchar(tolower(c));
}

/* upper:  convert to upper case */
static void
upper(void)
{
	int c;

	while ((c = getchar()) != EOF)
		putchar(toupper(c));
}
