#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main()
{
	char fname[] = "test_a.c";
	int fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (printf("cant open: %s\n", strerror(errno)));
	char b[101];
	bzero(b, 100);
	int r = read(fd, b, 100);
	b[100] = '\0';
	while (r > 0)
	{
		printf("%s\n", b);
		if (errno)
			printf("test errno %s\n", strerror(errno));
		r = read(fd, b, 100);
		b[100] = '\0';
	}
	printf("%s\n", b);
	if (errno)
		printf("test errno %s\n", strerror(errno));
	close(fd);
	return (0);
}