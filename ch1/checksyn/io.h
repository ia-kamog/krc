#ifndef IO_H
#define IO_H
#include <stdio.h>
/* fetch:  get character and set positions */
int fetch(void);
/* putback:  unget character c and decrement position */
int putback(int c);
/* peek the next character */
int peek(void);
/* get position on the current line */
int getpos(void);
/* get current line numbe */
int getlinum(void);
#endif
