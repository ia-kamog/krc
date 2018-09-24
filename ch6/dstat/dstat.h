#ifndef CROSSREF_H
#include <stdbool.h>
#include <stddef.h>
int getch(void);
void ungetch(int);

size_t getword(char *, size_t lim);

struct treenode {
	char *word;
	long count;
	struct treenode *left;
	struct treenode *right;
};

void addword(const char *word, struct treenode **);
void print_tree(struct treenode *);
void occur_sort_tree(struct treenode *root,
					 struct treenode **pp);
#endif
