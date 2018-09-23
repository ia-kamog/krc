#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100

struct tnode {			// the tree node:
	char *word;				// points to the text
	struct tnode *left;		// left child
	struct tnode *right;	// right child
	int count;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
int isreserved(char *);

char *prefix;
int preflen;
/* word frequency count 
	exercise 6-1:  extended getword
	exercise 6-2:  group by prefix */
int
main(int argc, char *argv[])
{
	struct tnode *root;
	char word[MAXWORD];
	if (argc <= 1)
		preflen = 6;
	else if	(!(preflen = abs(atoi(argv[1]))))
		return 1;
	prefix = malloc(preflen+1);
	if (!prefix)
		abort();
	prefix[0] = '\0';
	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) && !isreserved(word))
			root = addtree(root, word);
		treeprint(root);
	return 0;
}

struct tnode *talloc(void);
char *strdup(char *);

/* addtree:  add a node with w, at or below p */
struct tnode *
addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) {	// a new word has arrived
		p = talloc();
		p->word = strdup(w);
		p->left = p->right = NULL;
		p->count = 1;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if (cond < 0)	// less the into left subtree
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return p;
}

/* treeprint:  in-order print of tree p */
void
treeprint(struct tnode *p)
{
	int c;
	
	if (p != NULL) {
		treeprint(p->left);
		c = strncmp(prefix, p->word, preflen);
		if (c == 0)
			printf("\t%s\t%d\n", p->word, p->count);
		else {
			strncpy(prefix, p->word, preflen);
			prefix[preflen] = '\0';
			printf("%s\t\t%d\n", p->word, p->count);
		}
		treeprint(p->right);
	}
}
		
/* talloc:  make a tnode */
struct tnode *
talloc(void)
{
	return malloc(sizeof(struct tnode));
}

/* make a duplicate of s */
char *
strdup(char *s)
{
	char *p;

	p = malloc(strlen(s)+1);	// +1 for '\0'
	if (p != NULL)
		strcpy(p, s);
	return p;
}

/* getword:  get next word or character from input */
int
getword(char *word, int lim)
{
	enum { BEGIN, IDENT, NUMBER,
		   COMMENT_BEGIN,
		   COMMENT, STRING, CHARLIT, COMMENT_END,
		   COMMENT_LINE, PREPROC } state = BEGIN;
	static int newline = 1;
	int c, t, getch(void), escape = 0;
	void ungetch(int);
	char *w = word;

	while ((c = getch()) != EOF) {
		if (escape)
			escape = 0;
		else if (c == '\\')
			escape = 1;
		switch(state) {
		case BEGIN:
			if (c == '"') {
				state = STRING;
			} else if (c == '\'') {
				state = CHARLIT;
			} if (isalpha(c) || c == '_') {
				*w++ = c, lim--;
				state = IDENT;
				newline = 0;
			} else if (isdigit(c) || c == '.') {
				*w++ = c, lim--;
				state = NUMBER;
				newline = 0;
			} else if (c == '/') {
				state = COMMENT_BEGIN;
			} else if (c == '#' && newline) {
				state = PREPROC;
			} else if (c == '\n') {
				newline = escape ? newline : 1;
			} else if (isspace(c)) {
				;
			} else {
				*w++ = c, lim--;
				c = getch();
				goto end;
			}
			break;
		case IDENT:
			if ((isalnum(c) || c == '_') && lim > 1)
				*w++ = c, lim--;
			else
				goto end;
			break;
		case NUMBER:
			if (lim > 1 &&
				(isxdigit(c) || c == 'x' || c == 'X' ||
				 c == '.' || c == 'e'))
				*w++ = c, lim--;
			else
				goto end;
			break;
		case COMMENT_BEGIN:
			if (c == '*')
				state = COMMENT;
			else if (c == '/')
				state = COMMENT_LINE;
			else {
				*w++ = '/', lim--;
				goto end;
			}
			break;
		case COMMENT:
			if (c == '*')
				state = COMMENT_END;
			break;
		case COMMENT_END:
			state = (c == '/') ? BEGIN : COMMENT;
			break;
		case COMMENT_LINE:
			if (c == '\n') {
				newline = 1;
				state = BEGIN;
			}
			break;
		case PREPROC:
			if (c == '\n' && !escape)
				state = BEGIN;
			break;
		case STRING:
			if (c == '"' && !escape)
				state = BEGIN;
			break;
		case CHARLIT:
			if (c == '\'' && !escape)
				state = BEGIN;
			break;
		}
	}
end:
	if (c != EOF)
		ungetch(c);
	*w = '\0';
	return c;
}
			
char *keywords[] = {
	"auto", "break", "case", "char", "const", "continue", 
	"default", "do", "double", "else", "enum", "extern", 
	"float", "for", "goto", "if", "int", "long", "register", 
	"return", "short", "signed", "sizeof", "static", "struct", 
	"switch", "typedef", "union", "unsigned", "void", "volatile",
	"while"
};

/* isreserved:  check if s is a reserved word */
int
isreserved(char *s)
{
	char **begin = keywords;
	char **end = keywords + (sizeof keywords / sizeof keywords[0]);

	while (begin < end) {
		char **mid = begin + (end - begin)/2;
		int c = strcmp(s, *mid);
		if (c < 0)
			end = mid;
		else if (c > 0)
			begin = mid + 1;
		else
			return 1;
	}
	return 0;
}
