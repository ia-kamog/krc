#include <math.h>
#include <stdio.h>
#include <stdlib.h>		/* for atof() */
#include <string.h>

#define MAXOP	100		/* max size of operand or operator */
#define NUMBER	'0'		/* signal that a number was found */
#define IDENT	'i'
#define SETVAR	'!'
#define GETVAR	'$'

void print(double);
int getop(char []);
void push(double);
double pop(void);
double get(void);
int empty(void);
/* stack operations */
double pr(void);
double dup(void);
double swap(double, double);
double cs(void);
/* variable operations */
void setvar(char s[], double);
double fetchvar(char s[]);

struct function {
	double (*ptr)();
	char *name;
	short args:3, res:1;
} functions[] = {
	{pr, "pr", 0, 0},
	{dup, "dup", 0, 1},
	{swap, "swap", 2, 0},
	{cs, "cs", 0, 0},
	{sin, "sin", 1, 1},
	{cos, "cos", 1, 1},
	{exp, "exp", 1, 1},
	{pow, "pow", 2, 1}
};
enum { NFUNS = sizeof functions / sizeof *functions };
void call(struct function);

/* reverse Polish calculator
	exercise 4-3: add modulus operator and negative numbers
	exercise 4-4: add stack operations 
	exercise 4-5: math functions
	exercise 4-6: add variables
	exercise 4-7: add ungets
	exercise 4-9: ungetc handles EOF */
int main(void)
{
	int type, i;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case IDENT:
			for (i = 0; i < NFUNS; i++)
				if (strcmp(functions[i].name, s) == 0) {
					call(functions[i]);
					break;
				}
			if (i == NFUNS)
				printf("error: unknown operation\n");
			break;
		case SETVAR:
			setvar(s, pop());
			break;
		case GETVAR:
			push(fetchvar(s));
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

#define MAXVARTBL	100
#define MAXVAR		10
int vsz = 0;
double vartbl[MAXVARTBL];
char varnames[MAXVARTBL][MAXVAR];

/* set variable s to value x */
void setvar(char s[], double x)
{
	int i;

	for (i = 0; i < vsz; i++)
		if (strcmp(varnames[i], s) == 0) {
			vartbl[i] = x;
			break;
		}
	if (i == vsz) {
		if (vsz < MAXVARTBL) {
			strcpy(varnames[i], s);
			vartbl[i] = x;
			++vsz;
		} else
			printf("error: variable table filled\n");
	}
}

/* get variable named s */
double fetchvar(char s[])
{
	int i;

	for (i = 0; i < vsz; i++)
		if (strcmp(varnames[i], s) == 0)
			return vartbl[i];
	printf("error: unknown variable %s\n", s);
	return 0;
}

void print(double x) /* print:  output x */
{
	setvar("", x);
	printf("\t%.8g\n", x);
}

#define MAXVAL	100		/* maximum depth of val stack */

int sp = 0;				/* next free stack position */
double val[MAXVAL];		/* value stack */

/* call: perform call of f on stack arguments */
void call(struct function f)
{
	double op1, op2, op3, r;
	if (f.args > sp) {
		printf("error: not enough arguments\n");
		return;
	}
	switch (f.args) {
	case 3:
		op1 = pop(), op2 = pop(), op3 = pop();
		r = f.ptr(op1,op2,op3);
		break;
	case 2:
		op1 = pop(), op2 = pop();
		r = f.ptr(op1,op2);
		break;
	case 1:
		op1 = pop();
		r = f.ptr(op1);
		break;
	case 0:
		r = f.ptr();
	}
	if (f.res)
		push(r);
}

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

double cs(void) /* empty the stack */
{
	sp = 0;
	return 0;
}

double pr(void) /* print top element */
{
	print(get());
	return 0;
}

double dup(void) /* duplicate element on top */
{
	double x = get();
	return x;
}

double swap(double a, double b) /* swap elements on top */
{
	push(a);
	push(b);
	return 0;
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
int getident(char s[], int lim);
int getother(char s[]);
int readpos(char s[], int lim);
int readint(char s[], int lim);

/* read positive into s, return length */
int readpos(char s[], int lim)
{
	int c, i = 0;

	while (lim > 1 && isdigit(c=getch()))
		s[i++] = c, lim--;
	if (lim > 0)
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
		ungetch(c);
		return readpos(s, lim);
	}
}

/* getop:  get next operator or numeric operand */
int getop(char s[])
{
	int c;

	skip_space();
	s[0] = c = getch();
	if (isdigit(c) || c == '.' || c == '-') {
		ungetch(c);
		return getdig(s);
	} else if (isalpha(c) || c == '_')
		return getident(s+1, MAXOP-1);
	else if (c == EOF) {
		s[0] = '\0';
		return c;
	} else if (c == SETVAR) {
		getident(s, MAXVAR);
		return SETVAR;
	} else if (c == GETVAR) {
		getident(s, MAXVAR);
		return GETVAR;
	} else {
		ungetch(c);
		return getother(s);
	}
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
	} else
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

/* get identifier into s, return INDENTIFIER */
int getident(char s[], int lim) 
{
	int c, i;

	for (i = 0; i < lim-1 &&
			 (isalpha(c = getch()) ||
			  isdigit(c) ||
			  c == '-');
		 i++)
		s[i] = c;
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
	if (c == EOF)
		return;
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

/* ungets:  put s into lookahead buffer */
void ungets(const char s[])
{
	int i;

	for (i = strlen(s)-1; bufp < BUFSIZE && i >= 0; i--)
		buf[bufp++] = s[i];
}
