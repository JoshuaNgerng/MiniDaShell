#include <stdio.h>

void	v(void)
{
	printf("void\n");
}

void	*w(void)
{
	printf("test\n");
	return (NULL);
}

void	*f(void *a, void *b)
{
	(void)a;
	(void)b;
	return (NULL);
}

int main(void)
{
	f(f(w(), NULL), NULL);
	return (f(NULL, NULL), 0);
}