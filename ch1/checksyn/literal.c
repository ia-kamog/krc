#include "escape.h"
#include "io.h"
#include "literal.h"
#include "main.h"
#include "util.h"

int chrlit(void)
{
	int c, r;

	r = SYN_OK;
	(void) fetch(); /* skip ' */
	while ((c = fetch()) != EOF) 
		switch (c) {
		case '\n':
			putback(c);
			print_err(&r, ERR_NEWLINE,
					  "newline in a character literal");
			return r;
		case '\\':
			r |= escape();
			break;
		case '\'':
			return r;
		}
	print_err(&r, ERR_EOF, "EOF encountered while reading"
			" a character literal");
	return r;
}


int string(void)
{
	int c, r;

	r = SYN_OK;
	(void) fetch(); /* skip " */
	while ((c = fetch()) != EOF) 
		switch (c) {
		case '\n':
			putback(c);
			print_err(&r, ERR_NEWLINE,
					  "newline in a string constant");
			return r;
		case '\\':
			r |= escape();
			break;
		case '"':
			return r;
		}
	print_err(&r, ERR_EOF, "EOF encountered while "
			"reading a string constant");
	return r;
}
