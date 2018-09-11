#include <string.h>

/* strrindex:  find rightmost occurence of t in s, or -1 if none */
int strrindex(const char s[], const char t[])
{
	int i, j, k;

	for (i = strlen(s)-1; i >= 0; i--) {
		for (j=0; s[i+j]!='\0'&&t[j]!='\0' && s[i+j]==t[j]; j++)
			;
		if (t[j] == '\0')
			return i;
	}
	return -1;
}
