#include "picoshell.h"

static int	setup_pipe(int pfd[], int fd_in)
{
	if (pipe(pfd) == -1)
	{
		if (fd_in != 0)
			close(fd_in);
		return (1);
	}
	return (0);
}

static void	child_exec(char **av, int pfd[], int fd_in)
{
	if (fd_in != 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (pfd[1] != -1)
	{
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		close(pfd[0]);
	}
	execvp(av[0], av);
	exit(1);
}

int	picoshell(char **cmds[])
{
	int		pfd[2];
	int		fd_in = 0;
	pid_t	pid;
	int		i = 0;
	int		status = 0;

	while (cmds[i] != NULL)
	{
		if (cmds[i + 1] != NULL)
		{
			if (setup_pipe(pfd, fd_in) == 1)
				return (1);
		}
		else
		{
			pfd[0] = -1;
			pfd[1] = -1;
		}
		pid = fork();
		if (pid == -1)
		{
			if (fd_in != 0)
				close(fd_in);
			if (pfd[1] != -1)
			{
				close(pfd[0]);
				close(pfd[1]);
			}
			return (1);
		}
		if (pid == 0)
			child_exec(cmds[i], pfd, fd_in);
		if (fd_in != 0)
			close(fd_in);
		if (pfd[1] != -1)
			close(pfd[1]);
		fd_in = pfd[0];
		i++;
	}
	if (fd_in > 0)
		close(fd_in);
	while (wait(&status) > 0)
		;
	return (0);
}
