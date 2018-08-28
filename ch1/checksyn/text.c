#include "comment.h"
#include "io.h"
#include "literal.h"
#include "main.h"
#include "text.h"
#include "util.h"

static int paren(int, int);
static int brace(int, int);

/* text:  function to process standard code,
	return on ')', '}' */
int text(void)
{
	int c, r;

	r = SYN_OK;
	while ((c = peek()) != EOF)
		switch (c) {
		case '(': r |= paren(getlinum(), getpos()); break;
		case '{': r |= brace(getlinum(), getpos()); break;
		case '"': r |= string(); break;
		case '\'': r |= chrlit(); break;
		case ')': case '}': return r;
		default:
			(void) fetch();
			if (c == '/' && (c=peek()) == '*')
  				comment();
		}
	return r;
}

/* paren:  read parenthesizes code from nl:p */
int paren(int nl, int p)
{
	int c, r;

	r = SYN_OK;
	(void) fetch();
	r |= text();
	c = fetch();
	if (c == EOF)
		print_err(&r, ERR_EXPECT,
				"parenthesized expression from %d:%d, "
				"unterminated",
				nl, p);
	else if (c != ')')
		print_err(&r, ERR_EXPECT,
				"parenthesized expression from %d:%d, "
				"found '%c'",nl, p, c);
	return r;
}

/* brace:  read braced code from nl:p */
int brace(int nl, int p)
{
	int c, r;

	r = SYN_OK;
	(void) fetch();
	r |= text();
	c = fetch();
	if (c == EOF)
		print_err(&r, ERR_EXPECT,
				"braced block from %d:%d, unterminated",
				nl, p);
	else if (c != '}')
		print_err(&r, ERR_EXPECT,
				"braced block from %d:%d, found '%c'", nl, p, c);
	return r;
}
	  

		
