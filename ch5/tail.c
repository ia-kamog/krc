/*
	tail (exercise 5-13):  print last (default 10) lines of the input
	example:
		tail -5
*/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void addline(char *);
static void getargs(int argc, char **argv);
static char *getline(void);
static void malloc_fail(void);
static void print_lines();

/* main function */
int
main(int argc, char *argv[])
{
	char *ptr;
	
	getargs(argc, argv);	
	while (ptr = getline())
		addline(ptr);
	
	print_lines();
	return 0;
}

static char **lines;
static int nlines;
static char **linep;

/* addline:  add line to lines LIFO */
static void
addline(char *ln)
{
	if (linep - lines < nlines)
		*linep++ = ln;
	else {
		free(lines[0]);
		memmove(lines, lines+1, (nlines-1)*sizeof(char *));
		linep[-1] = ln;
	}
}

/* getargs:  process command line arguments and initialize lifo */
static void
getargs(int argc, char *argv[])
{
	if (argc == 1)
		nlines = 10;
	else if (argc == 2 && argv[1][0] == '-' && isdigit(argv[1][1]))
		nlines = atoi(argv[1]+1);
	else {
		fprintf(stderr, "usage: tail [-n]\n");
		exit(1);
	}
	linep = lines = malloc(nlines * sizeof(char *));
	if (!lines)
		malloc_fail();
	memset(lines, 0, nlines * sizeof(char *));
}

#define LINESZ 100
#define GROWTH 1.5
/* getline:  allocate a line of input and return a pointer */
static char *
getline(void)
{
	char *l;
	int c, exit;
	size_t i, sz;

	if (!(l = malloc(LINESZ)))
		malloc_fail();
	sz = LINESZ;
	for (exit=i=0; !exit && (c = getchar()) != EOF; i++) {
		if (i >= sz-1 && !(l = realloc(l, sz *= GROWTH)))
			malloc_fail();
		exit = (l[i] = c) == '\n';
	}
	if (i == 0 && c == EOF) {
		free(l);
		return NULL;
	}
	l[i++] = '\0';
	if (!(l = realloc(l, i)))
		malloc_fail();
	return l;
}

/* malloc_fail:  exit and print error message */
static void
malloc_fail(void)
{
	perror(NULL);
	exit(2);
}

/* print_lines:  print and free the lines from lifo */
static void
print_lines(void)
{
	char **p;

	for (p = lines; p < linep; p++) {
		printf("%s", *p);
		free(*p);
	}
}
