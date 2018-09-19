#include <stdio.h>
#include <stdlib.h>

#define MAXTSTOPS 100	/* max number of tabstops */
#define TABSTOP		8	/* default tabstops are 0, TABSTOP, 2*TABSTOP, ... */

static int fillstops(int argc, char *argv[], int *stops);
static void nextstop(int *prevst, int tab_incr, int **stops);

/* convert spaces into tabs
	exercise 5-11 */
int
main(int argc, char *argv[])
{
	int tabstops[MAXTSTOPS], *curts = tabstops;
	int sp, p, tbstp, tab_incr, c;
	
	tab_incr = fillstops(argc, argv, tabstops);
	tbstp = p = sp = 0;
	nextstop(&tbstp, tab_incr, &curts);
	while ((c = getchar()) != EOF)
		switch (c) {
		case '\n':
			tbstp = p = sp = 0;
			curts = tabstops;
			nextstop(&tbstp, tab_incr, &curts);
			putchar('\n');
			break;
		case '\t':
			putchar('\t');
			p = sp = tbstp;
			nextstop(&tbstp, tab_incr, &curts);
			break;
		case ' ':
			sp++;
			if (sp == tbstp) {
				putchar('\t');
				p = sp = tbstp;
				nextstop(&tbstp, tab_incr, &curts);
			}
			break;
		default:
			while (sp - p > 0) {
				putchar(' ');
				p++;
			}
			putchar(c);
			break;
		}
	return 0;
}

/* fillstops:  fill stops array from argc and argv, terminate with 0;
	return tab increment */
static int
fillstops(int argc, char *argv[], int *s)
{
	int *p, max = 0, inc;
	
	for (p = s; p-s<MAXTSTOPS-1 && --argc>0; p++) {
		*p = atoi(*++argv);
		if (*p < max) {
			fprintf(stderr, "non-increasing list of tabstops\n");
			exit(1);
		}
		max = *p;
	}
	inc = (p==s)?TABSTOP:p[-1]-((p-1!=s)?p[-2]:0);
	*(p + (p-s == MAXTSTOPS-1)) = 0;
	return inc;
}

/* nextstop:  update tabstop */
static void
nextstop(int *ts, int tab_incr, int **stops)
{
	while (**stops && **stops <= *ts)
		++*stops;
	*ts = **stops ? **stops : *ts + tab_incr;
}
