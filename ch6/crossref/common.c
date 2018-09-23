#include <stdlib.h>
#include <string.h>
#include "crossref.h"

static bool sorted = false;
static char *common_words[] = {
	"a", "the", "s", "get", "do", "t", "don",
	"from", "to", "that", "this", "those", "these",
	"I", "be", "am", "is", "are", "in", "at",
	"on", "onto", "so", "for", "if", "then"
};
#define NWORDS (sizeof common_words / sizeof common_words[0])

static int
cmp(const void *a, const void *b)
{
	return strcmp(a, b);
}

void
sort_common_words(void)
{
	qsort(common_words, NWORDS, sizeof common_words[0], cmp);
	sorted = true;
}

bool
iscommon(const char *w)
{
	if (!sorted)
		abort();
	return bsearch(w, common_words, NWORDS,
				   sizeof common_words[0], cmp);
}
