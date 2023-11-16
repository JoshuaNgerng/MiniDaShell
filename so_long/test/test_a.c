#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("hello\n");
	char *s=malloc (2);
	free(s);
	return (0);
}