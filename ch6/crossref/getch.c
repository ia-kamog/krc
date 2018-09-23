#include <stdio.h>
#include <stdlib.h>
#include "crossref.h"

long lineno = 1;

static int buf = '\0';

int
getch(void)
{
	int c;

	if (buf != '\0')
		c = buf, buf = '\0';
	else
		c = getchar();
	if (c == '\n')
		lineno++;
	return c;
}

void
ungetch(int c)
{
	if (buf != '\0' || c == '\0')
		abort();
	if (c == '\n')
		lineno--;
	buf = c;
}
