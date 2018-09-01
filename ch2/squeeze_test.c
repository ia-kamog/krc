#include <stdio.h>
#define MAXLINE 100

void squeeze(char  s[], int c);

/* test squeeze function */
int main(void)
{
	char fmt[20], buf[MAXLINE], c;
	snprintf(fmt, sizeof fmt, "%%%ds\n%%c", MAXLINE);
	if (scanf(fmt, buf, &c) != 2)
		return 1;
	squeeze(buf, c);
	puts(buf);
	return 0;
}
