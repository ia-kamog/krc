#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAYSIZE	1000000
#define NTESTS		100000

int binsearch(int x, int v[], int n);
int *make_array(void);

/* test binsearch function */
int main(void)
{
	int i, *A;
	clock_t t1, t2;

	srand(time(NULL));
	A = make_array();

	t1 = clock();
	for (i = 0; i < NTESTS; ++i)
		binsearch(rand(), A, ARRAYSIZE);
	t2 = clock();
	free(A);
	printf("%f\n", (double) (t2-t1) / CLOCKS_PER_SEC);
	return 0;
}

/* make_array:  build a sorted array of integers with ARRAYSIZE size 
	needs to freed */
int *make_array(void)
{
	int *r, i, cur;
	r = malloc(ARRAYSIZE * sizeof(int));
	if (r == NULL) {
		perror(NULL);
		exit(1);
	}

	cur = 0;
	for (i = 0; i < ARRAYSIZE; ++i) {
		r[i] = cur;
		cur += rand() % 4;
	}

	return r;
}
