#include <stdio.h>
int getline(char s[], int lim);
enum { MAXLINE = 10 };
/* exercise 2-2 */
int main(void)
{
	int len;
	char buf[MAXLINE];
	while ((len=getline(buf, MAXLINE)) > 0)
		printf("%d: %s\n", len, buf);
	return 0;
}
