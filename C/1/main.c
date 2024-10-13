#include <stdio.h>

int pow(int n, int m)
{
	if (m == 1)
		return n;

	return n * pow(n, m - 1);
}

int fact(int n)
{
	if (n == 0)
		return 1;

	return n * fact(n - 1);
}

float eq(int x, int n)
{
	if (n == 0)
		return 0;

	return (float)pow(x, n) / (float)fact(x + n) + eq(x, n - 1);
}

int main()
{
	int x, n;

	x = 1;
	n = 1;
	printf("%f\n", eq(x, n));
}
