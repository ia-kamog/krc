/* strcat:  concate s and t in s */
void strcat(char *s, const char *t)
{
	while (*s)
		s++;
	while (*s++ = *t++)
		;
}
