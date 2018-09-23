#include <ctype.h>
#include <stdio.h>
#include "crossref.h"

static bool isword(int);

size_t
getword(char *w, size_t lim)
{
	size_t i;
	int c;
	
	while ((c=getch()) != EOF && !isword(c))
		;
	if (c == EOF)
		return 0;
	else
		ungetch(c);
	for (i = 0; i < lim-1 && isword(c = getch()); i++)
		w[i] = c;
	w[i] = '\0';
	return i;
}

static bool
isword(int c)
{
	return isalpha(c) || c == '_' || c == '-';
}
