#include <stdio.h>
#include <string.h>

#define BUFSIZE 100000
#define MAXLINES 5000		/* max #lines to be sorted */

char *lineptr[MAXLINES];	/* pointers to text lines */

int readlines(char *lineptr[], int nlines, char *buf, int bufsz);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines
	exercise 5-7: use local buffer instead of alloc */
int
main(void)
{
	int nlines;		// number of input lines read
	char buf[BUFSIZE];
	
	if ((nlines = readlines(lineptr, MAXLINES,
							buf, BUFSIZE)) >= 0) {
		qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

int getline(char *, int);
char *alloc(int);

// readlines:  read input lines
int
readlines(char *lineptr[], int maxlines,
		  char *buf, int bufsize)
{
	int len, nlines;
	char *p = buf;

	nlines = 0;
	while (p-buf<bufsize &&
		   (len=getline(p,bufsize-(p-buf))) > 0)
		if (nlines >= maxlines)
			return -1;
		else {
			lineptr[nlines++] = p;
			p += len+1;
			if (p > buf+1 && p[-2] == '\n')
				p[-2] = '\0';
		}					
	return nlines;
}

// writelines:  write output lines
void
writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

// qsort:  sort v[left]...v[right] into increasing order
void
qsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)	// do nothing if array contains
		return;			// fewer than two elements
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last-1);
	qsort(v, last+1, right);
}

// swap:  interchange v[i] and v[j]
void
swap(char *v[], int i, int j)
{
	char *temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
