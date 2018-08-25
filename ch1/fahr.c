#include <stdio.h>

#define		LOWER	0		/* lower limit of table */
#define		UPPER	300		/* upper limit */
#define		STEP	20		/* step size */

float fahr_to_cels(float fahr);

/* print Fahrenheit-Celsius table */
int main(void)
{
	int fahr;

	for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
		printf("%3d %6.1f\n", fahr, fahr_to_cels(fahr));
}

/* fahr_to_cels:  convert fahr in Fahrenheit to correspond temperature
	in Celsius */
float fahr_to_cels(float fahr)
{
	float k = 5.0 / 9.0;
	float zero = 32.0;
	return k * (fahr - zero);
}
