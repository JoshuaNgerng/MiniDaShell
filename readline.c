#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* 
used to get stdin, remove whitespaces
can react to control keys left/right arrows
complie with -lreadline
*/

/*
trying a basic history to keep track of history
and do basic getcwd and chdir
*/

void	go_cwd(char *input)
{
	int	i;

	i = 0;
	while (input[i] != ' ' && input[i])
		i ++;
	while (input[i] == ' ' && input[i])
		i ++;
	if (chdir(&input[i]))
		perror(&input[i]);
}

int main()
{
	char	s[] = "Write something LULz: ";
	char	*r;
	char	cwd[256];

	r = readline(s);
	while (strncmp(r, "exit", 5))
	{
		if (r && *r)
			add_history(r);
		if (!strncmp(r, "pwd", 4))
		{
			getcwd(cwd, sizeof(cwd));
			printf("current directory: %s\n", cwd);
		}
		if (!strncmp(r, "cd", 2))
			go_cwd(r);
		free(r);
		r = readline(s);
	}
	system("leaks a.out");
	return (0);
}