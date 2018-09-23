#include <stdlib.h>
#include "crossref.h"

static struct linenode *lalloc(void);

void
reverse_linelist(struct linenode **pp)
{
	struct linenode *r = NULL, *p = *pp;
	for ( ; p != NULL; p = p->next)
		insert_linenode(p->line, &r);
	*pp = r;
}

void
insert_linenode(long l, struct linenode **pp)
{
	struct linenode *n;

	if (*pp && (**pp).line == l)
		return;
	if ((n=lalloc()) != NULL) {
		n->next = *pp;
		n->line = l;
		*pp = n;
	}
}

static struct linenode *
lalloc(void)
{
	return malloc(sizeof(struct linenode));
}
