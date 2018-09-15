#include <string.h>

static void rev_h(char s[], int start, int end);

/* reverse:  overwrite s with its reversed version */
void
reverse(char s[])
{
	rev_h(s, 0, strlen(s)-1);
}

/* rev_h:  helper function to reverse character array s
	between start and end */
static void
rev_h(char s[], int start, int end)
{
	char t;
	if (start >= end)
		return;
	t = s[start], s[start] = s[end], s[end] = t;
	rev_h(s, start+1, end-1);
}
