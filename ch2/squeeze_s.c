/* exercise 2-4
	squeeze:  remove characters from s1 that occur in s2 */
void squeeze(char s1[], char s2[])
{
	int i, j, k, f;

	for (i = j = 0; s1[i] != '\0'; ++i) {
		f = 0;
		for (k = 0; s2[k] != '\0'; ++k)
			if (s1[i] == s2[k])
				f = 1;
		if (!f)
			s1[j++] = s1[i];
	}
	s1[j] = '\0';
}
