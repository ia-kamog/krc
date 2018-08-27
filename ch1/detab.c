#include <stdio.h>

#define TABSTOP 8

void fill_blanks(char s[], int len);

/* detab: replace tabs with spaces */
int main(void)
{
	int c;						/* input character */
	int pos;					/* position on the line */
	int shift;					/* shift to the next tab */
	char blanks[TABSTOP+1];

	fill_blanks(blanks, TABSTOP+1);
	pos = 0;
	while ((c = getchar()) != EOF)
		switch (c) {
		case '\n':
			pos = 0;
			putchar(c);
			break;
		case '\t':
			shift = TABSTOP - pos % TABSTOP;
			printf("%s", blanks + TABSTOP - shift);
			pos += shift;
			break;
		default:
			++pos;
			putchar(c);
			break;
		}
	return 0;
}

/* fill_blanks: fill s with blanks and terminate with \0 */
void fill_blanks(char s[], int sz)
{
	s[--sz] = '\0';
	while (sz > 0)
		s[--sz] = ' ';
}
