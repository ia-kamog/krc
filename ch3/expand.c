#define term(a,i) ((a)[i] == '\0')
#define dash(a,i) ((a)[i] == '-')
#define range(a,i) (dash(a,i+1) && (a)[i] < (a)[i+2])
#define traildash(a,i) (dash(a,i) && (i == 0 || term(a,i+1)))
/* expand:  convert ranges like a-z in s1 to full form into s2
	-?([^-]|[^-]-[^-])*-? */
void expand(const char s1[], char s2[])
{
	int i, j, c;

	for (i = j = 0; !term(s1,i); i++)
		if (range(s1,i)) {
			for (c = s1[i]; c <= s1[i+2]; c++)
				s2[j++] = c;
			i += 2;
		} else if (traildash(s1,i) || !dash(s1,i))
			s2[j++] = s1[i];
		else
			; /* do nothing with bad dashes */
	s2[j] = '\0';
}
