/* exercise 2-6:
	setbits:  return x with right n bits an position p set to right n bits of y */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	unsigned mask = ~0 << (p+1-n) & ~(~0 << (p+1));
	y <<= p + 1 - n;
	x &= ~mask;
	y &= mask;
	return x | y;
}
