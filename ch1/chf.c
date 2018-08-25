#include <limits.h>
#include <stdio.h>

#define COLS	76		/* number of rows on the screen */
#define HEADER	2		/* header size */

/* exercise 1-14
	print histogram of character frequency */
int main(void)
{
	long cnt[UCHAR_MAX+1], max;
	int c, i, l;
	char bar[COLS+1];

	for (i = 0; i <= UCHAR_MAX; ++i)
		cnt[i] = 0;
	max = 0;
	while ((c = getchar()) != EOF)
		if (max < ++cnt[c])
			max = cnt[c];

	for (i = 0; i < COLS; ++i)
		bar[i] = '*';
	bar[COLS] = '\0';
	
	for (i = 0; i <= UCHAR_MAX; ++i) {
		 l = cnt[i] * COLS / max;
		 if (l > 0)
			 printf("%02x %s\n", i, &bar[COLS-l]);
	}
}
	
