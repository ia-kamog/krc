#include "crossref.h"

#define MAXWORD 100

int
main(void)
{
	char word[MAXWORD];
	struct treenode *root = NULL;
	
	sort_common_words();
	while (getword(word, MAXWORD) > 0)
		if (!iscommon(word))
			addword(word, &root);
	print_tree(root);
	return 0;
}
