#include <stdlib.h>
#include <string.h>
#include "lookup.h"
#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];	/* pointer table */

static unsigned hash(const char *s);

/* undef:  make symbol named s undefined */
void
undef(const char *s)
{
	struct nlist **pp, *p;

	for (pp = &hashtab[HASHSIZE]; *pp != NULL; pp = &(**pp).next)
		if (strcmp(s, (**pp).name) == 0) {
			p = *pp;
			free(p->name);
			free(p->defn);
			*pp = p->next;
			free(p);
		}
}

/* hash:  form hash value for string s */
static unsigned
hash(const char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/* lookup:  look for s in hashtab */
struct nlist *
lookup(const char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;	/* found */
	return NULL;		/* not found */
}

/* install:  put (name, defn) in hashtab */
struct nlist *
install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {	/* not found */
		np = malloc(sizeof *np);
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else		/* already there */
		free(np->defn);		/* free previous defn */
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}
