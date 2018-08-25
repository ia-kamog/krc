#include <stdio.h>

#define MAXWORD 15		/* maximal length of a word */
#define COLS	80		/* columns on the terminal */
#define ROWS	24		/* rows on the terminal */
#define HEIGHT	(ROWS-4) /* height of the histogram */
#define SKIP	2		/* distance between bars */
#define BARCHAR	'*'
#define FMTSZ	8

/* exercise 1-13
	print histogram of word lengths from input */
int main(void)
{
	int wcnt[MAXWORD], i, j, max, c, wl;
	char sep[SKIP+1], fmt1[FMTSZ], fmt2[FMTSZ];
	
	for (i = 0; i < MAXWORD; ++i)
		wcnt[i] = 0;
	
	wl = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n') {
			if (wl > 0 && wl < MAXWORD)
				++wcnt[wl-1];
			else if (wl >= MAXWORD)
				++wcnt[MAXWORD-1];
			wl = 0;
		} else
			++wl;
	}

	max = wcnt[0];
	for (i = 1; i < MAXWORD; ++i)
		max = max > wcnt[i] ? max : wcnt[i];

	for (i = 0; i < MAXWORD; ++i)
		wcnt[i] = wcnt[i] * HEIGHT / max;

	snprintf(fmt1, FMTSZ, "%%%dc", SKIP+1);
	snprintf(fmt2, FMTSZ, "%%%dd", SKIP+1);
	for (i = 0; i < HEIGHT; ++i) {
		for (j = 0; j < MAXWORD; ++j) {
			printf(fmt1, (HEIGHT - wcnt[j] <= i) ? '*' : ' ');

		}
		putchar('\n');
	}
	putchar('\n');

	for (j = 0; j < MAXWORD; ++j)
		printf(fmt2, j+1);
	putchar('\n');
}
