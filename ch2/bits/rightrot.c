/* exercise 2-8
	rightrot:  rotate x to the right by n bits, n > 0 */
unsigned rightrot(unsigned x, int n)
{
	return ((~0u>>n)+1)*(~(~0u<<n)&x) | x>>n;
}
