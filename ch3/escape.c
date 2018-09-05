#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void escape(const char s[], char t[]);
void unescape(const char s[], char t[]);

/* test escape function */
int main(void)
{
	char buf[100], res[400];

	if (fgets(buf, sizeof buf, stdin) == NULL)
		return 1;
	unescape(buf, res);
	puts(res);
	return 0;
}

/* escape:  copy s to t replacing non-printable characters
	with C escape codes */
void escape(const char s[], char t[])
{
	int i, j, esc, c;

	for (i=j=0; (c=s[i]) != '\0'; i++) {
		esc = '\\';
		switch (c) {
		case '\a': c = 'a'; break;
		case '\b': c = 'b'; break;
		case '\t': c = 't'; break;
		case '\n': c = 'n'; break;
		case '\r': c = 'r'; break;
		case '\v': c = 'v'; break;
		case '\f': c = 'f'; break;
		case '\\': case '"': case '\'':
			break;
		default:
			if (isprint(c))
				esc = 0;
			break; 
		}
		if (esc)
			t[j++] = esc;
		if (isprint(s[i]))
			t[j++] = c ;
		else {
			sprintf(&t[j], "%o", c);
			while (t[++j] != '\0')
				;
		}
	}
	t[j] = '\0';
}

/* unesape:  copy from s to t, replacing C escape sequences */
void unescape(const char s[], char t[])
{
	enum { NORMAL, ESCAPE, ESCAPE_HEXA, ESCAPE_OCTA } state;
	int i, j, k, acc, len;
	char simple_seqs[] = "a\ab\bf\fn\nr\rt\tv\v''\"\"??\\\\\0";

	state = NORMAL;
	for (i = j = 0; s[i] != '\0'; i++)
		switch (state) {
		case NORMAL:
			if (s[i] != '\\')
				t[j++] = s[i];
			else
				state = ESCAPE;
			break;
		case ESCAPE:
			switch (s[i]) {
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
				state = ESCAPE_OCTA;
				len = 1;
				acc = s[i] - '0';
				break;
			case 'x': case 'X':
				state = ESCAPE_HEXA;
				acc = len = 0;
				break;
			default:
				for (k=0; simple_seqs[k] != '\0'; k+=2)
					if (simple_seqs[k] == s[i]) {
						t[j++] = simple_seqs[k+1];
						break;
					}
				if (simple_seqs[k] == '\0')
					fprintf(stderr, "unknown escape sequence '\\%c' at %d\n",
							s[i], i);
				state = NORMAL;
				break;
			}
			break;
		case ESCAPE_HEXA:
			len++;
			switch (s[i]) {
			case 'a': case 'A':
				acc = 16*acc + 10;
				break;
			case 'b': case 'B':
				acc = 16*acc + 11;
				break;
			case 'c': case 'C':
				acc = 16*acc + 12;
				break;
			case 'd': case 'D':
				acc = 16*acc + 13;
				break;
			case 'e': case 'E':
				acc = 16*acc + 14;
				break;
			case 'f': case 'F':
				acc = 16*acc + 15;
				break;
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				acc = 16*acc + (s[i] - '0');
				break;
			default:
				if (len == 1)
					fprintf(stderr, "empty hexadecimal sequence at %d\n", i);
				t[j++] = acc;
				i--;	/* reprocess this character in the normal state */
				state = NORMAL;
				break;
			}
			break;
		case ESCAPE_OCTA:
			if (len >= 3 || !('0' <= s[i] && s[i] <= '7')) {
				t[j++] = acc;
				i--;  /* reprocess this character in the normal state */
				state = NORMAL;
			} else { /* len < 3 && '0' <= s[i] && s[i] <= '7') */
				acc = 8*acc + (s[i] - '0');
				len++;
			}
			break;
		}

	t[j] = '\0';
}
