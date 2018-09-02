/* exercise 2-7
	invert:  return x with n bits at position p inverted */
unsigned invert(unsigned x, int p, int n)
{
	unsigned mask = ~0 << (p+1-n) & ~(~0 << (p+1));
	return mask ^ x;
}
