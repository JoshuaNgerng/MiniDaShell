#include <stdio.h>

void	p(int *in)
{
	printf("p: %d\n", *in);
}

void	l(int *in)
{
	printf("l: %d\n", in[-1]);
}

int main()
{
	int in[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	int	i = -1;
	int	lim = 12;
	int	j = lim - 1;

	while (++ i < lim)
	{
		printf("\n");
		p(&in[j - i]);
		if (i != lim - 1)
			l(&in[j - i]);
	}
}