#include <stdio.h>

/* exercise 2-2
	getline:  read a line into s, return length */
int getline(char s[], int lim)
{
	int c, i;

	for (i=0; i<lim-1; ++i) {
		c = getchar();
		if (c == EOF)
			break;
		else if (c == '\n')
			break;
		else
			s[i] = c;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
