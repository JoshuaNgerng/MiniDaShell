#include <stdio.h>

void	a(void)
{
	printf("a\n");
}

void	b(void)
{
	printf("b\n");
}

int	main(void)
{
	int	i;

	i = -1;
	while (++ i < 100)
	{
		if (i == 50)
		{
			a(), b();
			break ;
		}
	}
	return (0);
}
