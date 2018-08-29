#include <float.h>
#include <limits.h>
#include <stdio.h>

#define	FUNC_MAX_INTEGER(type, n)	\
	type max##n(void) {				\
	type a,b,c;						\
	for (a = 1; 0 < a; a *= 2)		\
		b = a;						\
	a = b; c = b;					\
	for (a=b; a!=0; a/=2, b=c)		\
		for (c = b, b +=a; b>0 && b>c; b+=a) \
			c = b;					\
	return b; }
#define	FUNC_MIN_INTEGER(type, n)	\
	type min##n(void) {				\
	type a,b,c;						\
	for (a = -1; 0 > a; a *= 2)		\
		b = a;						\
	a = b; c = b;					\
	for (a=b; a!=0; a/=2, b=c)		\
		for (c=b, b+=a; b<0 && b<c; b+=a) \
			c = b;					\
	return b; }

#define FUNC_EPSILON(type, n)		\
	type eps ## n(void)	{			\
	type a = 1, b = 1, c = 1;		\
	while ((b=a+c) != c)			\
		a /= 2;						\
	return (b+2*a)-c; }

#define FUNC_MIN_FLOAT(type, n)		\
	type min ## n (void) {			\
	type eps = eps ## n ();			\
	type a = 1;						\
	while (a*(1+eps) != a)			\
		a /= 2;						\
	return 2*a;	}

#define FUNC_MAX_FLOAT(type, n)		\
	type max ## n(void)	{			\
	type eps = eps ## n ();			\
	type m = 2.0 - eps;				\
	type r;							\
	for (r = m/2; r == m/2; m *= 2)	\
		r = m;						\
	return r; }

FUNC_MAX_INTEGER(char, char)
FUNC_MAX_INTEGER(int, int)
FUNC_MAX_INTEGER(long, long)
FUNC_MAX_INTEGER(unsigned char, uchar)
FUNC_MAX_INTEGER(unsigned int, uint)
FUNC_MAX_INTEGER(unsigned long int, ulong)

FUNC_MIN_INTEGER(char, char)
FUNC_MIN_INTEGER(int, int)
FUNC_MIN_INTEGER(long, long)

FUNC_EPSILON(float, float)
FUNC_MAX_FLOAT(float, float)
FUNC_MIN_FLOAT(float, float)

FUNC_EPSILON(double, double)
FUNC_MAX_FLOAT(double, double)
FUNC_MIN_FLOAT(double, double)

FUNC_EPSILON(long double, ldouble)
FUNC_MAX_FLOAT(long double, ldouble)
FUNC_MIN_FLOAT(long double, ldouble)

int main(void)
{
	printf("unsigned char  %20d - %20d\n"
		   "               %20d - %20d\n"
		   "unsigned int   %20d - %20u\n"
		   "               %20d - %20u\n"
		   "unsigned long  %20d - %20lu\n"
		   "               %20d - %20lu\n"
		   "char           %20d - %20d\n"
		   "               %20d - %20d\n"
		   "int            %20d - %20d\n"
		   "               %20d - %20d\n"
		   "long           %20ld - %20ld\n"
		   "               %20ld - %20ld\n"
		   "float          %20.10g\n"
		   "               %20.10g\n"
		   "               %20.10g - %20.10g\n"
		   "               %20.10g - %20.10g\n"
		   "double         %20.10g\n"
		   "               %20.10g\n"
		   "               %20.10g - %20.10g\n"
		   "               %20.10g - %20.10g\n"
		   "long double    %20.10Lg\n"
		   "               %20.10Lg\n"
		   "               %20.10Lg - %20.10Lg\n"
		   "               %20.10Lg - %20.10Lg\n",
		   0, UCHAR_MAX, 0, maxuchar(), 0, UINT_MAX,  0, maxuint(),
		   0, ULONG_MAX, 0, maxulong(), CHAR_MIN, CHAR_MAX,
		   minchar(), maxchar(), INT_MIN, INT_MAX, minint(), maxint(),
		   LONG_MIN, LONG_MAX, minlong(), maxlong(),  FLT_EPSILON,
		   epsfloat(), FLT_MIN, FLT_MAX, minfloat(), maxfloat(),
		   DBL_EPSILON,epsdouble(),DBL_MIN,DBL_MAX,mindouble(),maxdouble(),
		   LDBL_EPSILON,epsldouble(),LDBL_MIN,LDBL_MAX,minldouble(),
		   maxldouble());
}
