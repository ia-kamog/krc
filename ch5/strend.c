#include <string.h>

/* strend:  return 1 if s end with t, 0 else */
int
strend(const char *s, const char *t)
{
	const char *es, *et;

	es = s+strlen(s);
	et = t+strlen(t);
	while (es > s && et > t && *--es == *--et)
		;
	return et == t && *et == *es;
}
