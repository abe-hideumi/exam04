#include "popen.h"

int	ft_popen(const char *file, char *const argv[], char type)
{
	int	pfd[2];

	if (file == NULL || argv == NULL || (type != 'w' && type != 'r'))
		return (-1);
	pipe(pfd);
	if (fork() == 0)
	{
		if (type == 'r')
		{
			dup2(pfd[1], STDOUT_FILENO);
			close(pfd[0]);
			close(pfd[1]);
			execvp(file, argv);
			exit(1);
		}
		if (type == 'w')
		{
			dup2(pfd[0], STDIN_FILENO);
			close(pfd[0]);
			close(pfd[1]);
			execvp(file, argv);
			exit(1);
		}
	}
	if (type == 'r')
	{
		close(pfd[1]);
		return (pfd[0]);
	}
	close(pfd[0]);
	return (pfd[1]);
}
