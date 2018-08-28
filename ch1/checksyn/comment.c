#include "comment.h"
#include "io.h"
#include "main.h"
#include "util.h"

/* handle comment after / including the terminating *,/ */
int comment(void)
{
	int c;

	(void) fetch();
	while ((c = fetch()) != EOF)
		if (c == '*' && fetch() == '/')
			return SYN_OK;
	print_err(NULL, 0, "EOF while reading comment");
	return ERR_EOF;
}
