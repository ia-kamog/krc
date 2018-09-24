#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dstat.h"

static struct treenode *talloc(void);
static void addoccur(struct treenode *n, struct treenode **pp);
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
	} else if ((c=strcmp(w, (**np).word)) < 0)
		addword(w, &(**np).left);
	else if (*np != NULL && c > 0)
		addword(w, &(**np).right);
	else if (*np != NULL) {
		(**np).count++;
	}
}

void
occur_sort_tree(struct treenode *root,
				struct treenode **pp)
{
	if (root != NULL) {
		addoccur(root, pp);
		occur_sort_tree(root->left, pp);
		occur_sort_tree(root->right, pp);
		free(root);
	}
}

void
print_tree(struct treenode *t)
{
	if (t == NULL)
		return;
	print_tree(t->right);
	printf("%5ld %20s\n", t->count, t->word);
	print_tree(t->left);
}	

static struct treenode *
talloc(void)
{
	return calloc(1, sizeof(struct treenode));
}

static void
addoccur(struct treenode *n,
			 struct treenode **pp)
{
	if (pp == NULL)
		return;
	if (*pp == NULL) {
		if ((*pp = talloc()) == NULL)
			return;
		(**pp).count = n->count;
		(**pp).word = n->word;
	} else if (n->count <= (*pp)->count)
		addoccur(n, &(*pp)->left);
	else if (n->count > (*pp)->count)
		addoccur(n, &(*pp)->right);
}
