#include <stdio.h>
#include <stdlib.h>

int	func(void)
{
	static int	var;
	static char	*ptr;

	printf("inside func %d\n", var);
	printf("inside func %p\n", ptr);
	var ++;
	if (ptr)
		free(ptr);
	ptr = malloc(100);
	printf("inside func %p\n", ptr);
	return (var);
}

int main(void)
{
	int	i;

	i = -1;
	while (++ i < 5)
		printf("output %d\n", func());
	system("leaks a.out");
	return (0);
}