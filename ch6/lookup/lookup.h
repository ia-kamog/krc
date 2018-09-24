#ifndef LOOKUP_H
#define LOOKUP_H
struct nlist {		/* table entry */
	struct nlist *next;	/* next entry in chain */
	char *name;			/* defined name */
	char *defn;			/* replacement text */
};

struct nlist *lookup(const char *s);
struct nlist *install(char *name, char *defn);
void undef(const char *name);
#endif
