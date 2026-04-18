#include "popen.h"

int	main(void)
{
	char	line[BUF_SIZE];
	int		fd;
	int	n;

	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
	while ((n = read(fd, line, BUF_SIZE)) > 0)
		write(1, line, n);
	close(fd);
	fd = ft_popen("grep", (char *const []){"grep", "a", NULL}, 'w');
	write(fd, "hello world!\n", 13);
	write(fd, "habe\n", 5);
	close(fd);
	return (0);
}
