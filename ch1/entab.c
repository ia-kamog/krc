#include <stdio.h>

#define TABSTOP 8	/* tabstops are 0, TABSTOP, 2*TABSTOP, ... */

void fill_blanks(char s[], int len);

/* convert spaces into tabs */
int main(void)
{
	int pos1;				/* position starting a sequence of blanks */
	int pos2;				/* current position */
	int c;
	char blanks[TABSTOP+1];

	fill_blanks(blanks, TABSTOP+1);
	pos1 = pos2 = 0;
	while ((c = getchar()) != EOF)
		switch (c) {
		case '\t':
			putchar(c);
			pos1 = pos2 = TABSTOP*(pos2/TABSTOP+1);
			break;
		case ' ':
			++pos2;
			if (pos2 % TABSTOP == 0) {
				putchar(pos1 == pos2-1 ? ' ' : '\t');
				pos1 = pos2;
			}
			break;
		case '\n':
			printf("%s\n", blanks+TABSTOP-(pos2-pos1));
			pos1 = pos2 = 0;
			break;
		default:
			printf("%s%c", blanks+TABSTOP-(pos2-pos1), c);
			pos1 = ++pos2;
			break;
		}
}

/* fill_blanks: fill s with blanks and terminate with \0 */
void fill_blanks(char s[], int sz)
{
	s[--sz] = '\0';
	while (sz > 0)
		s[--sz] = ' ';
}
