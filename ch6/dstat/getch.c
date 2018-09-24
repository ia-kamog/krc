#include <stdio.h>
#include <stdlib.h>
#include "dstat.h"

static int buf = '\0';

int
getch(void)
{
	int c;

	if (buf != '\0')
		c = buf, buf = '\0';
	else
		c = getchar();
	return c;
}

void
ungetch(int c)
{
	if (buf != '\0' || c == '\0')
		abort();
	buf = c;
}
