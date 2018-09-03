#include <stdio.h>
#include <stdlib.h>
#define DO_TEST(a, sz, elt, exp) do {	\
	int v;								\
	if ((v=binsearch(elt,a,sz)) != exp) {\
	printf("%d == binsearch(%d, (int*){", v, elt);\
	print_array(a, sz);					\
	printf("}, %d) != %d\n", sz, exp); } } while (0)

int binsearch(int x, int a[], int n);
int test1(void);
void print_array(int a[], int n);

/* test binsearch function */
int main(void)
{
	int arr[] = { 1, 4, 8, 16, 32, 64 };
	DO_TEST(arr, 1, 0, -1);
	DO_TEST(arr, 1, 2, -1);
	DO_TEST(arr, 1, 1, 0);
	DO_TEST(arr, 2, 0, -1);
	DO_TEST(arr, 2, 16, -1);
	DO_TEST(arr, 2, 4, 1);
	DO_TEST(arr, 2, 1, 0);
	DO_TEST(arr, 3 , 0, -1);
	DO_TEST(arr, 3, 8, 2);
	DO_TEST(arr, 3, 32, -1);
	DO_TEST(arr, 3, 4, 1);
	DO_TEST(arr, 3, 1, 0);

}

/* print_array:  print integers from array 
	'a' up to 'n' */
void print_array(int a[], int n)
{
	int i;

	for (i = 0; i < n; ++i)
		printf("%d,", a[i]);
}
