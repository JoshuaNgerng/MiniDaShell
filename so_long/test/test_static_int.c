#include <stdio.h>

int test(int a)
{
	static int i;

	printf("static %d\n", i);
	i ++;
	return (i + a);
}

int main(void)
{
	int	b = test(1);

	printf("%d\n", test(2));
	printf("%d\n", b + test(-1));
	return (0);
}