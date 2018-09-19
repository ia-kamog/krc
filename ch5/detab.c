#include <stdio.h>
#include <stdlib.h>

#define MAXTSTOPS 100	/* max number of tabstops */
#define TABSTOP		8	/* default tabstops are 0, TABSTOP, 2*TABSTOP, ... */

static int fillstops(int argc, char *argv[], int *stops);
static void nextstop(int *prevst, int tab_incr, int **stops);

/* convert spaces into tabs
	exercise 5-11
	exercise 5-12 */
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
			sp = tbstp;
			nextstop(&tbstp, tab_incr, &curts);
		default:
			while (sp - p > 0) {
				putchar(' ');
				p++;
			}
			if (c != '\t')
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
	char *arg;
	int *p = s, max = 0, inc = 0, end = 0;
		
	while (p-s < MAXTSTOPS-2 && --argc>0) {
		arg = *++argv;
		switch (*arg) {
		case '+':
			inc = atoi(arg+1);
			break;
		case '-':
			end = atoi(arg+1);
			break;
		default:
			*p = atoi(arg);
			if (*p < max) {
				fprintf(stderr, "non-increasing list of tabstops\n");
				exit(1);
			}
			max = *p;
			p++;
			break;
		}
	}
	if (end && end > max)
		*p++ = end;
	else if (end)
		fprintf(stderr, "bad starting tabstop %d\n", end);
	if (!inc && p == s)
		inc = TABSTOP;
	else if (!inc)
		inc = p[-1];
	if (p-s >= 2)
		inc -= p[-2];
	*p = 0;
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
