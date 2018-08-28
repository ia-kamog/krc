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
	int c1, c2;

	while ((c1 = getchar()) != EOF
		   && (c2 = getchar()) != EOF)
		if (c1 == '/' && c2 == '*')
			comment();
		else {
			ungetc(c2, stdin);
			putchar(c1);
			switch (c1) {
			case '"': string(); break;
			case '\'': chrlit(); break;
			}
		}
	if (c1 != EOF)
		putchar(c1);
}

/* string:  deal with characters in strings */
void string(void)
{
	int c;

	while ((c = getchar()) != EOF) {
		putchar(c);
		if (c == '"')
			return;
		else if (c == '\\' && (c=getchar()) != EOF)
			putchar(c);
	}
}

/* chrlit:  deal with character literals */
void chrlit(void)
{
	int c;
		
	while ((c = getchar()) != EOF) {
		putchar(c);
		if (c == '\'')
			return;
		else if (c == '\\' && (c=getchar()) != EOF)
			putchar(c);
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
