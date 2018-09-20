#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE		1000000
#define MAXLINES	5000		/* max #lines to be sorted */
#define MAXFIELDS	11
#define REVFLAG		001
#define FOLDFLAG	002
#define DIRFLAG		004
#define NUMFLAG		010
#define SETFLAG		020

char *lineptr[MAXLINES];	/* pointers to text lines */
int field_flags[MAXFIELDS];
int field_order[MAXFIELDS];
int use_fields = 0;

int chcmp(const char **s1, const char **s2, int flags);
int fieldcmp(char **fields1, char **fields2, int flags);
void getargs(int argc, char *argv[]);
int readlines(char *lineptr[], int nlines, char *buf, int bufsz);
void writelines(char *lineptr[], int nlines);
double atof(const char *);
void qsort(char *lineptr[], int left, int right,
		   int (*comp)(const char *, const char *));
int numcmp(const char *, const char *);
int cmp(const char *, const char *);
void split(const char *s, const char **fields);
int issep(int);

/* sort input lines
	exercise 5-7: use local buffer instead of alloc
	exercise 5-14: add reverse flag
	exercise 5-15: add fold flag
	exercise 5-16: add directory order flag
	exercise 5-17: add field processing */
int
main(int argc, char *argv[])
{
	int nlines;		// number of input lines read
	char buf[BUFSIZE];

	getargs(argc, argv);
	if ((nlines = readlines(lineptr, MAXLINES,
							buf, BUFSIZE)) >= 0) {
		qsort(lineptr, 0, nlines-1, cmp);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

// getargs:  process command-line options
void
getargs(int argc, char *argv[])
{
	int field = 0, pos = 0, flags;
	void exit(int);
	
	while (--argc > 0 && **++argv == '-') {
		flags = 0;
		while (*++*argv) {
			switch(**argv) {
			case 'n':
				flags |= NUMFLAG;
				break;
			case 'f':
				flags |= FOLDFLAG;
				break;
			case 'd':
				flags |= DIRFLAG;
				break;
			case 'r':
				flags |= REVFLAG;
				break;
			case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8':
			case '9':
				use_fields = 1;
				field = **argv - '0';
				break;
			case '-':
				field_flags[MAXFIELDS-1] = flags | SETFLAG;
				break;
			default:
				fputs("usage: sort [-[1-9]nfdr]\n", stderr);
				exit(1);
			}
		}
		field_order[pos++] = field;
		field_flags[field] = flags;
	}
}			
			
		


// readlines:  read input lines
int
readlines(char *lineptr[], int maxlines,
		  char *buf, int bufsize)
{
	int getline(char *, int);
	int len, nlines;
	char *p = buf;

	nlines = 0;
	while (p-buf<bufsize &&
		   (len=getline(p,bufsize-(p-buf))) > 0)
		if (nlines >= maxlines)
			return -1;
		else {
			lineptr[nlines++] = p;
			p += len+1;
			if (p > buf+1 && p[-2] == '\n')
				p[-2] = '\0';
		}					
	return nlines;
}

// writelines:  write output lines
void
writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

// qsort:  sort v[left]...v[right] into increasing order
void
qsort(char *v[], int left, int right,
	  int (*comp)(const char *, const char *))
{
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)	// do nothing if array contains
		return;			// fewer than two elements
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last-1, comp);
	qsort(v, last+1, right, comp);
}

// swap:  interchange v[i] and v[j]
void
swap(char *v[], int i, int j)
{
	char *temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

// number:  compare s1 and s2 numerically
int
numcmp(const char *s1, const char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int
isdir(int c)
{
	return isalpha(c) || isdigit(c) || c == ' ' || c == '\t';
}
// cmp:  compare strings according to flags
int
cmp(const char *s1, const char *s2)
{
	const char *fields1[MAXFIELDS], *fields2[MAXFIELDS], *p1, *p2;
	int fieldind, res = 0, flagind, flags, i;
	
	memset(fields1, 0, sizeof fields1);
	memset(fields2, 0, sizeof fields2);
	split(s1, fields1);
	split(s2, fields2);
	if (use_fields) {
		fieldind = 1;
		while (!res && fieldind < MAXFIELDS-1 &&
			   (i = field_order[fieldind])) {
			p1 = fields1[fieldind];
			p2 = fields2[fieldind];
			flags = field_flags[i];
			fprintf(stderr, "%o\n", flags);
			while ((*p1 || *p2) &&
				   !issep(*p1) && !issep(*p2) &&
				   !(res = chcmp(&p1, &p2, flags)))
				;
			fieldind++;
		}
		if (res)
			return res;
		if (field_flags[MAXFIELDS-1]) {
			use_fields = 0;
			flags = field_flags[MAXFIELDS-1];
			while ((*p1 || *p2) && !(res = chcmp(&p1, &p2, flags)))
				;
			use_fields = 1;
		}
		return res;
	} else {
		flags = field_flags[0];
		while ((*s1 || *s2) && !(res = chcmp(&s1, &s2, flags)))
			;
		return res;
	}			
}

// split:  fill fields with starting pointer to each field from s
void
split(const char *s, const char **fields)
{
	int i;
	
	if (!use_fields) {
		fields[0] = s;
		return;
	}
	while (*s && issep(*s))
		s++;
	for (i = 1; i < MAXFIELDS; i++) {
		fields[i] = s;
		while (*s && !issep(*s))
			s++;
		while (*s && issep(*s))
			s++;
	}
}

//chcmp:  compare characters and advance pointers according to flags
int
chcmp(const char **s1, const char **s2, int flags)
{
	int c1 = **s1, c2 = **s2, res = 0;
	if (c1 == '\0' && c2 == '\0' ||
		use_fields && issep(c1) && issep(c2))
		res = 0;
	else if (c1 == '\0' || use_fields && issep(c1))
		res = -1;
	else if (c2 == '\0' || use_fields && issep(c2))
		res = 1;
	else if (flags & NUMFLAG)
		res = numcmp(*s1, *s2);
	else {
		if (flags & FOLDFLAG)
			c1 = tolower(c1), c2 = tolower(c2);
		if (flags & DIRFLAG) {
			if (!isdir(c1))
				++*s1;
			if (!isdir(c2))
				++*s2;
			if (!isdir(c1) || !isdir(c2))
				return 0;
		}
		++*s1, ++*s2;
		res = c1 - c2;
	}
	if (flags & REVFLAG)
		res *= -1;
	return res;
}

// issep:  return non-zero if ch is field separator
int
issep(int ch)
{
	return isspace(ch);
}
