#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE];	/* storage for alloc */
static char *allocp = allocbuf;		/* next free position */

char *
alloc(int n)	// return pointer to n characters
{
	if (allocbuf + ALLOCSIZE - allocp >= n) {	// it fits
		allocp += n;
		return allocp - n; // old p
	} else	// not enough room
		return 0;
}
// free storage pointed by p
void
afree(char *p)
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}
