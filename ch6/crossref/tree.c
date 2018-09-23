#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crossref.h"

static struct treenode *talloc(void);

void
addword(const char *w, struct treenode **np)
{
	int c;
	
	if (np == NULL)
		return;
	if (*np == NULL) {
		if ((*np = talloc()) == NULL)
			return;
		(**np).count = 1;
		(**np).word = strdup(w);
		insert_linenode(lineno, &(**np).lines);
	} else if ((c=strcmp(w, (**np).word)) < 0)
		addword(w, &(**np).left);
	else if (*np != NULL && c > 0)
		addword(w, &(**np).right);
	else if (*np != NULL) {
		(**np).count++;
		insert_linenode(lineno, &(**np).lines);
	}
}

void
print_tree(struct treenode *t)
{
	struct linenode *p;
	
	if (t == NULL)
		return;
	print_tree(t->left);
	printf("%5ld %20s:", t->count, t->word);
	reverse_linelist(&t->lines);
	for (p = t->lines; p != NULL; p = p->next)
		printf(" %5ld", p->line);
	printf("\n");
	print_tree(t->right);
}	

static struct treenode *
talloc(void)
{
	return calloc(1, sizeof(struct treenode));
}
