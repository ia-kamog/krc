#define swap(t,x,y) do { t swap_temp=x; x=y; y=swap_temp; } while (0)

/* qsort:  sort v[left]...v[right] into increasing order */
void qsort(int v[], int left, int right)
{
	int i, last;

	if (left >= right)	/* do noting if array contains */
		return;			/* fewer than two elements */
	swap(int, v[left], v[(left+right)/2]);	/* move partition elem */
	last = left;						/* to v[0] */
	for (i = left+1; i <= right; i++)	/* partition */
		if (v[i] < v[left]) {
			last++;
			swap(int, v[last], v[i]);
		}
	swap(int, v[left], v[last]);	/* restore partition elem */
	qsort(v, left, last-1);
	qsort(v, last+1, right);
}
