#include <stdarg.h>
#include "io.h"
#include "util.h"

int isoctal(int c)
{
	return '0' <= c && c <= '7';
}

void vis(char c[], int lim)
{
}

void print_err(int *ret, int code, char *fmt, ...)
{
	va_list ap;
	if (ret != NULL)
		*ret |= code;
	va_start(ap, fmt);
	printf("%d:%d ", getlinum(), getpos());
	vprintf(fmt, ap);
	putchar('\n');
}
