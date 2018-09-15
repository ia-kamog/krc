#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>		/* for atof() */

#define MAXLINE	1000		/* max size of operand or operator */

int getline(char s[], int lim);
int getop(char [], int);
void push(double);
double pop(void);

/* reverse Polish calculator
	exercise 4-10:  getline version */
int main(void)
{
	double op2;
	char s[MAXLINE] = "";
	int i;

	i = 0;
	while (s[i] != '\0' || (i = 0, getline(s, MAXLINE) > 0)) {
		i = getop(s, i);
		switch (s[i]) {
		case '0': case '1': case '2': case '3':	case '4':
		case '5': case '6': case '7': case '8':	case '9':
		case '.':
			push(atof(&s[i]));
			while (isdigit(s[i]) || s[i] == '.')
				i++;
			break;
		case '+':
			push(pop() + pop());
			i++;
			break;
		case '*':
			push(pop() * pop());
			i++;
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			i++;
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			i++;
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			i++;
			break;
		case '\0':
			break;
		default:
			printf("error: unknown command %s\n", s+i);
			i++;
			break;
		}

	}
	return 0;
}

#define MAXVAL	100		/* maximum depth of val stack */

int sp = 0;				/* next free stack position */
double val[MAXVAL];		/* value stack */

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
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* getop:  get next operator or numeric operand */
int getop(char s[], int i)
{
	for (; s[i]==' ' || s[i]=='\t'; i++)
		;
	return i;
}
