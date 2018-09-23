#ifndef CROSSREF_H
#include <stdbool.h>
#include <stddef.h>
int getch(void);
void ungetch(int);
extern long lineno;

size_t getword(char *, size_t lim);

struct linenode {
	long line;
	struct linenode *next;
};

void insert_linenode(long, struct linenode **);
void reverse_linelist(struct linenode **);

struct treenode {
	char *word;
	long count;
	struct linenode *lines;
	struct treenode *left;
	struct treenode *right;
};

void addword(const char *word, struct treenode **);
void print_tree(struct treenode *);

void sort_common_words(void);
bool iscommon(const char *);
#endif
