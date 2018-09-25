#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lookup/lookup.h"
#define MAXIDENT 255

static void slash(void);
static void text(void);
static void ident(void);
static void string(char);
static void comment(void);
static void comment_line(void);
static void preproc(void);
static void read_ident(char *);
static void skip_space(void);
static void trim(char *);
/* simple preprocessor for C files */
int
main(void)
{
	text();
}

void
text(void)
{
	int c;
	int newline = 1;
	bool escape = false;
	while ((c = getchar()) != EOF) {
		escape = escape ? false : (c == '\\');
		if (isalpha(c) || c == '_') {
			ungetc(c, stdin);
			ident();
		} else if (newline && c == '%') {
			newline = 1;
			preproc();
			continue;
		} else {
			putchar(c);
			if (c == '"')
				string('"');
			else if (c == '\'')
				string('\'');
			else if (c == '/')
				slash();
		}
		newline = (!escape && c == '\n') || (newline && isspace(c));
	}
}

void
read_ident(char *s)
{
	int i, c;

	for (i=0; i<MAXIDENT-1 && (c=getchar())!=EOF &&
			 (isalnum(c) || c == '_');
		 i++)
		s[i] = c;
	if (i != MAXIDENT-1)
		ungetc(c, stdin);
	s[i] = '\0';
}

void
ident(void)
{
	struct nlist *p;
	char ident[MAXIDENT];
	int c;

	read_ident(ident);
	if ((p = lookup(ident)) == NULL)
		printf("%s", ident);
	else
		printf("%s", p->defn);
}

void
preproc(void)
{
	char ident[MAXIDENT], line[1000];
	int i, c;

	read_ident(ident);
	if (strcmp(ident, "define") == 0) {
		skip_space();
		read_ident(ident);
		skip_space();
		fgets(line, sizeof line, stdin);
		trim(line);
		install(ident, line);
	} else if (strcmp(ident, "undef") == 0) {
		skip_space();
		read_ident(ident);
		undef(ident);
		while ((c=getchar()) != EOF && c!='\n')
			;
	} else
		;		
}

void
slash(void)
{
	int c;

	c = getchar();
	if (c == EOF)
		return;
	putchar(c);
	if (c == '*')
		comment();
	else if (c == '/')
		comment_line();
	else
		return;
}

void
comment(void)
{
	int c, end = 0;
	
	while ((c = getchar()) != EOF) {
		putchar(c);
		if (end && c == '/')
			return;
		end = c == '*';
	}
}

void
comment_line(void)
{
	int c;

	while ((c = getchar()) != EOF || c != '\n')
		putchar(c);
	if (c == '\n')
		ungetc(c, stdin);
}

void
string(char term)
{
	int c, esc = 0;

	while ((c = getchar()) != EOF) {
		putchar(c);
		if (!esc && c == term)
			return;
		esc = esc ? 0 : (c == '\\');
	}
}

void
trim(char *s)
{
	int i;
	for (i = strlen(s)-1; i >= 0; i--)
		if (isspace(s[i]))
			s[i] = '\0';
		else
			break;
}

void
skip_space(void)
{
	int c;

	while  ((c = getchar()) != EOF &&
			(c == ' ' || c == '\t'))
		;
	ungetc(c, stdin);
}
