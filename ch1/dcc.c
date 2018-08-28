#include <stdio.h>

void text(void);
void string(void);
void chrlit(void);
void comment(void);

/* delete comments from C code */
int main(void)
{
	text();
	return 0;
}

/* text: function dealing with most of C code,
	beginnings of strings, character literals and comments */
void text(void)
{
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '/') {
			if ((c = getchar()) == '*') {
				comment();
				continue;
			} else {
				ungetc(c,stdin);
				c = '/';
			}
		}

		putchar(c);
		switch (c) {
		case '"': string(); break;
		case '\'': chrlit(); break;
		}
	}
}

/* string:  deal with characters in strings */
void string(void)
{
	int c;
	int escape = 0;
	
	while ((c = getchar()) != EOF) {
		putchar(c);
		if (escape)
			escape = 0;
		else if (c == '\\')
			escape = 1;
		else if (c == '"')
			return;
	}
}

/* chrlit:  deal with character literals */
void chrlit(void)
{
	int c;
	int escape = 0;
	
	while ((c = getchar()) != EOF) {
		putchar(c);
		if (escape)
			escape = 0;
		else if (c == '\\')
			escape = 1;
		else if (c == '\'')
			return;
	}
}

/* comment:  deal with comments */
void comment(void)
{
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '*' && getchar() == '/')
			return;
	}
}
