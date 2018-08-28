#include <limits.h>
#include <stdio.h>

#include "main.h"
#include "io.h"

#if !(0 <= EOF+1 && EOF+1 <= UCHAR_MAX)
#	define EMPTY (EOF+1)
#elif EOF != INT_MIN
#	define EMPTY (EOF-1)
#endif

static int pos = 1;			/* position on the current line */
static int prev_pos = 1;	/* last position on the previous line */
static int nline = 1;		/* number of the line */
static int buf = EMPTY;
static int unget_flag = 0;

/* fetch:  get character and set positions */
int fetch(void)
{
	int c;
	
	++pos;
	if (buf != EMPTY)
		c = buf, buf = EMPTY;
	else {
		c = getchar();
		unget_flag = 0;
	}

	if (c == '\n')
		++nline, prev_pos = pos, pos = 1;
	else if (c == '\\' && peek() == '\n') {
		(void) fetch();
		c = fetch();
	}
	return c;		
}

/* putback:  unget character c and decrement position */
int putback(int c)
{
	if (c == '\n') {
		pos = prev_pos;
		--nline;
	} else
		--pos;
	if (!unget_flag) {
		ungetc(c, stdin);
		unget_flag = 1;
	} else {
		buf = c;
	}
	return c;
}

/* peek the next character */
int peek(void)
{
	return putback(fetch());
}

/* get position on the current line */
int getpos(void)
{
	return pos;
}

/* get current line numbe */
int getlinum(void)
{
	return nline;
}
