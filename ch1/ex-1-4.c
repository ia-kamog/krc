#include <stdio.h>

/* Celsius to Fahrenheit table;
	for celsius = -20, -10, ..., 150 */
int
main(void)
{
	float fahr, celsius;
	int lower, upper, step;

	lower = -20;
	step = 10;
	upper = 150;
	
	celsius = lower;
	while (celsius <= upper) {
		fahr = (9.0/5.0) * celsius + 32.0;
		printf("%3.0f %6.1f\n", celsius, fahr);
		celsius = celsius + step;
	}
}
