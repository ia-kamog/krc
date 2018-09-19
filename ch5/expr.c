#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void push(double);
double pop(void);
void print_stack(void);

/* expr:  evaluate arguments as in reverse polish notation expression
	exercise 5-10 */
int
main(int argc, char *argv[])
{
	char *a, sign;
	double op2;
	
	while (--argc > 0) {
		a = *++argv;
		if ((*a == '+' || *a == '-') && a[1] ||
			isdigit(*a) || *a == '.')
			push(atof(a));
		else
			switch (a[0]) {
			case '+':
				push(pop() + pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '*':
				push(pop() * pop());
				break;
			case '/':
				op2 = pop();
				if (op2 == 0.0)
					printf("division by zero\n");
				else
					push(pop() / op2);
				break;
			case '%':
				op2 = pop();
				if (op2 == 0.0)
					printf("division by zero\n");
				else
					push(fmod(pop(), op2));
				break;
			}
	}
	print_stack();
	return 0;
}

#define STACKSIZE 1000
double stack[STACKSIZE], *stackp = stack;

/* push:  push value x on stack */
void
push(double x)
{
	if (stackp - stack < STACKSIZE)
		*stackp++ = x;
	else
		printf("stack is full\n");
}

/* pop:  get a value from the top of a stack */
double
pop(void)
{
	if (stackp > stack)
		return *--stackp;
	else {
		printf("stack is empty\n");
		return 0.0;
	}
}

/* print_stack:  print values from stack, one per line */
void
print_stack(void)
{
	while (stackp > stack)
		printf("%g\n", *--stackp);
}
