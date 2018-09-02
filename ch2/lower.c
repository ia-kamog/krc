/* lower:  convert c to lower case; ASCII only */
int lower(int c)
{
	return ('A' <= c && c <= 'Z') ? c + 'a' - 'A' : c;
}
