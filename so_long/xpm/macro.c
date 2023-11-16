#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

int	main(void)
{
	DIR 			*dr;
	char			*fname;
	struct dirent	*en;

	dr = opendir("."); //open all directory
	if (dr) 
	{
		while ((en = readdir(dr)) != NULL)
		{
			fname = en->d_name;
			if (strncmp(fname, "AnyConv.com__", 13))
				continue ;
			if (rename(fname, &fname[13]))
				perror("Cant rename file: ");
		}
		closedir(dr); //close all directory
	}
	return (0);
}