# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>

int main()
{
	char *s = readline("test: ");
	printf("test: \n");
	free(s);
	return 0;
}