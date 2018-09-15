#include <stdio.h>

static void read_vals(int v[], int len);
static void print_vals(int v[], int len);
void qsort(int v[], int left, int right);

/* test qsort function */
int main(void)
{
	int len;
	if (scanf("%d", &len) != 1)
		return 1;

	int v[len];
	read_vals(v, len);
	qsort(v, 0, len-1);
	print_vals(v, len);
	return 0;
}

// read_vals:  fill array v with integer from stdin
void read_vals(int v[], int len)
{
	int x, cnt = 0;
	while (cnt < len && (x=scanf("%d", &v[cnt])) >= 0)
		++cnt;
	while (cnt < len)
		v[cnt++] = 0;
}

// print_vals:  print array v
void print_vals(int v[], int len)
{
	enum { NPL = 10 };
	int i;

	for (i = 0; i < len; i++)
		printf("%5d%c", v[i], (i%NPL == NPL-1 ? '\n' : ' '));
	if ((i-1)%NPL != NPL-1)
		putchar('\n');
}
