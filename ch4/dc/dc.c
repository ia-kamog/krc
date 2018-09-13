#include <math.h>
#include <stdio.h>
#include <stdlib.h>		/* for atof() */
#include <string.h>

#define MAXOP	100		/* max size of operand or operator */
#define NUMBER	'0'		/* signal that a number was found */
#define IDENT	'i'

int getop(char []);
void push(double);
double pop(void);
double get(void);
void pr(void);
void dup(void);
void swap(void);
void cs(void);
void print(double);
int empty(void);

/* reverse Polish calculator
	exercise 4-3: add modulus operator and negative numbers
	exercise 4-4: add stack operations */
int main(void)
{
	int type, i;
	double op2;
	char s[MAXOP];
	char *funs[] = { "pr", "dup", "swap", "cs" };
	void (*fun_ptr[])(void) = {pr,dup,swap,cs};
	enum { NFUNS = sizeof funs/sizeof *funs };
	
	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case IDENT:
			for (i = 0; i < NFUNS; i++)
				if (strcmp(funs[i], s) == 0) {
					fun_ptr[i]();
					break;
				}
			if (i == NFUNS)
				printf("error: unknown operation\n");
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			break;
		case '%':
			op2 = pop();
			if (op2 != 0.0)
				push(fmod(pop(), op2));
			else
				printf("error: zero division\n");
			break;
		case '\n':
			if (!empty())
				print(pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}

void print(double x) /* print:  output x */
{
	printf("\t%.8g\n", x);
}

#define MAXVAL	100		/* maximum depth of val stack */

int sp = 0;				/* next free stack position */
double val[MAXVAL];		/* value stack */

double get(void) /* get element without popping */
{
	if (sp > 0)
		return val[sp-1];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}
/* push: push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop:  pop and return top value from stack */
double pop(void)
{
	double x = get();
	sp = sp > 0 ? sp - 1 : sp;
	return x;
}

void cs(void) /* empty the stack */
{
	sp = 0;
}

void pr(void) /* print top element */
{
	print(get());
}

void dup(void) /* duplicate element on top */
{
	double x = get();
	if (sp > 0)
		push(get());
}

void swap(void) /* swap elements on top */
{
	double x;
	if (sp >= 2) {
		x = get();
		push(get());
		push(x);
	} else
		printf("error: swap: not enough elements\n");
}

int empty(void) /* is the stack empty? */
{
	return sp == 0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);
void skip_space(void);
int peek(void);
int getdig(char s[]);
int getident(char s[]);
int getother(char s[]);
int readpos(char s[], int lim);
int readint(char s[], int lim);

/* read positive into s, return length */
int readpos(char s[], int lim)
{
	int c, i = 0;

	while (lim > 1 && isdigit(c=getch()))
		s[i++] = c, lim--;
	if (c != EOF && lim)
		ungetch(c);
	s[i] = '\0';
	return i;
}

int readint(char s[], int lim) /* read integer into s, return length */
{
	int c;
	c = getch();
	if (c == '-' && isdigit(peek())) {
		s[0] = c;
		return 1+readpos(s+1, lim-1);
	} else {
		if (c != EOF)
			ungetch(c);
		return readpos(s, lim);
	}
}

/* getop:  get next operator or numeric operand */
int getop(char s[])
{
	int c;

	skip_space();
	c = peek();
	if (isdigit(c) || c == '.' || c == '-')
		return getdig(s);
	else if (isalpha(c) || c == '_')
		return getident(s);
	else if (c == EOF) {
		s[0] = '\0';
		return c;
	} else
		return getother(s);
}

void skip_space(void) /* skip spaces in input */
{
	int c;
	
	while ((c = getch()) == ' ' || c == '\t')
		;
	ungetch(c);
}

int getdig(char s[]) /* get number into s */
{
	int i, c;

	i = readint(s, MAXOP);
	if (i == 0 && peek() == '-')
		return getother(s);
	if (peek() == '.') {
		s[i++] = getch();
		i += readpos(s+i, MAXOP-i);
	}
	c = getch();
	if (c == 'e' || c == 'E') {
		s[i++] = c;
		i += readint(s+i, MAXOP-i);
	} else if (c != EOF)
		ungetch(c);
	
	if (i > 0 && (s[i-1] == 'e' || s[i-1] == 'E'))
		ungetch(s[--i]);
	s[i] = '\0';
	return NUMBER;		
}

int getother(char s[]) /* get other kind of character */
{
	s[0] = getch();
	s[1] = '\0';
	return s[0];
}

int getident(char s[]) /* get identifier into s, return INDENTIFIER */
{
	int c, i;

	for (i = 0; i < MAXOP-1 &&
			 (isalpha(c = getch()) ||
			  isdigit(c) ||
			  c == '-');
		 i++)
		s[i] = c;
	if (c != EOF)
		ungetch(c);
	s[i] = '\0';
	return IDENT;
}

#define BUFSIZE 100

char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

int getch(void)	/* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)	/* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

int peek(void) /* peek character */
{
	int c;
	if (bufp > 0)
		c = buf[bufp-1];
	else {
		c = getch();
		ungetch(c);
	}
	return c;
}
