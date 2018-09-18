#include <stdio.h>

int strend(const char *, const char *);

/* test strend function */
int
main(int argc, char *argv[])
{
	if (argc <= 2)
		return 1;
	printf("strend(\"%s\", \"%s\") == %d\n",
		   argv[1], argv[2], strend(argv[1],argv[2]));
	return 0;
}
