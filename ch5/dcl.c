#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100
#define MAXDECL 500
#define MAXOUT 2000
#define MAXELTS 100

enum { NAME, PARENS, BRACKETS, CONST };

int dcl(char *out, char *name, char *datatype);
int dirdcl(char *out, char *name, char *datatype);
int decl(char *out);

int gettoken(void);
int tokentype;			/* type of last token */
char token[MAXTOKEN];	/* last token string */
int line = 0;
int putback = 0;

/* convert declaration to words
	exercise 5-18: recover from input errors
	exercise 5-20: handle const and function parameters */
int
main(void)
{
	char out[MAXOUT];
	
	while (gettoken() != EOF) {		/* 1st token on line */
		out[0] = '\0';
		line = 0;
		decl(out);
		printf("%s\n", out);
	}
	return 0;
}

int
decl(char *out)
{
	char name[MAXTOKEN], datatype[MAXTOKEN], out2[MAXOUT];
	int curline;
	int cnst = 0;
	curline = line;
	line = 1;
	out2[0] = '\0';
	if (tokentype == CONST) {
		cnst = 1;
		tokentype = gettoken();
	}
	if (tokentype == EOF)
		return 1;
	strcpy(datatype, token);
	tokentype = gettoken();
	if (tokentype == CONST)
		cnst = 1;
	else
		putback = 1;
	if (!dcl(out2, name, datatype))
		printf("syntax error\n");
	else {
		sprintf(out+strlen(out), "%s%s: %s%s%s",
				(curline ? " ": ""),
				name, out2,
				(cnst? "const ":""), datatype);
		return 1;
	}
	return 0;
}
/* dcl:  parse a declarator */
int
dcl(char *out, char *name, char *datatype)
{
	int elts[MAXELTS], i;

	for (i = 0; gettoken() == '*' || tokentype == CONST; i++)	/* count *'s */
		elts[i] = tokentype;
	if (!dirdcl(out, name, datatype))
		return 0;
	while (--i >= 0)
		if (elts[i] == CONST)
			strcat(out, "const ");
		else
			strcat(out, "pointer to ");
	return 1;
}

/* dirdcl:  parse a direct declarator */
int
dirdcl(char *out, char *name, char *datatype)
{
	if (tokentype == '(') {			/* ( dcl ) */
		dcl(out, name, datatype);
		if (tokentype != ')') {
			printf("error: missing )\n");
			return 0;
		}
	} else if (tokentype == NAME)	/* variable name */
		strcpy(name, token);
	else {
		printf("error: expected name or (dcl)\n");
		return 0;
	}
	while ((tokentype=gettoken()) == '(' ||
		   tokentype == PARENS ||
		   tokentype == BRACKETS) {
		out += strlen(out);
		if (tokentype == PARENS)
			strcat(out, "function returning");
		else if (tokentype == '(') {
			strcat(out, "function taking");
			do {
				if (tokentype == ',')
					strcat(out, ", ");
				tokentype = gettoken();
				decl(out);
			} while (tokentype == ',');
			if (tokentype != ')') {
				printf("error: missing )\n");
				return 0;
			}
			strcat(out, " and returning ");
		} else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
	return 1;
}

/* return next token */
int
gettoken(void)
{
	int c, getch(void);
	void ungetch(int);
	char *p = token;

	if (putback) {
		putback = 0;
		return tokentype;
	}
	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		if (strcmp(token, "const") == 0)
			return tokentype = CONST;
		else
			return tokentype = NAME;
	} else
		return tokentype = c;
}
