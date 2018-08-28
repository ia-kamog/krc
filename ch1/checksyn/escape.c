#include <ctype.h>

#include "escape.h"
#include "io.h"
#include "main.h"
#include "util.h"


static int hexa(void);
static int octal(void);
static int simple(void);

/* escape:  check escape sequences for correctness */
int escape(void)
{
	int c;

	if ((c=peek()) == EOF) {
		print_err(NULL, 0, "EOF while reading escape sequence");
		return ERR_EOF;
	}
	if (c == 'x')
		return hexa();
	else if (isoctal(c))
		return octal();
	else
		return simple();
}

/* hexa:  read hexadecimal escape sequence */
int hexa(void)
{
	int c, len;

	(void) fetch();		/* is 'x' */
	for (len = 0; (c=fetch()) != EOF && isxdigit(c); ++len)
		;
	if (len == 0) {
		print_err(NULL, 0, "empty hexadecimal escape sequence");
		return ERR_ESCAPE;
	} else if (!isxdigit(c))
		putback(c);
	return SYN_OK;
}

/* octal:  read octal escape sequence */
int octal(void)
{
	int c, len;

	for (len = 0; len<3 && (c=fetch())!=EOF && isoctal(c); ++len)
		;
	/* len == 0 impossible */
	if (len != 3)
		putback(c);
	return SYN_OK;
}

/* simple:  read simple escape sequences
	handle bad escapes */
int simple(void)
{
	int c;
	switch(c = fetch()) {
	case 'a': case 'b': case 'n': case 't': case 'r': case 'v':
	case '?': case '"': case '\\': case '\'':
		return SYN_OK;
	default:
		print_err(NULL, 0, "unknown escape character '%c'", c);
		return ERR_ESCAPE;
	}
}
