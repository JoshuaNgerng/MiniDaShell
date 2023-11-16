#include <stdio.h>

int	max(int *n, int len)
{
	int	i = 0;
	int	num = n[i];
	while (++ i < len)
		if (num < n[i])
			num = n[i];
	return (num);
}

int main()
{
	int val[] = {-1, 2, 10, -9, 5};
	printf("test %d\n", max(val, 5));
	return (0);
}