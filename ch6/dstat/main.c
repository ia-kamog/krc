#include "dstat.h"

#define MAXWORD 100

int
main(void)
{
	char word[MAXWORD];
	struct treenode *root = NULL, *new_root = NULL;
	
	while (getword(word, MAXWORD) > 0)
		addword(word, &root);
	occur_sort_tree(root, &new_root);
	print_tree(new_root);
	return 0;
}
