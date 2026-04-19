#include "picoshell.h"

static int	count_cmds(int ac, char **av)
{
	int	count = 1;
	for (int i = 1; i < ac; i++)
	{
		if (strcmp(av[i], "|") == 0)
			count++;
	}
	return (count);
}

static void	cleanup(char ***cmds, int count)
{
	for (int i = 0; i < count; i++)
		free(cmds[i]);
	free(cmds);
}

static char	***cmds_init(int ac, char **av, int cmd_count)
{
	char	***result;
	int	i = 1, j = 0;

	result = calloc(cmd_count + 1, sizeof(char **));
	if (result == NULL)
		return (perror("calloc: "), NULL);
	while (i < ac)
	{
		int	len = 0;
		while (i + len < ac && strcmp(av[i + len], "|") != 0)
			len++;
		result[j] = calloc(len + 1, sizeof(char *));
		if (result[j] == NULL)
		{
			cleanup(result, j);
			return (perror("calloc: "), NULL);
		}
		for (int k = 0; k < len; k++)
			result[j][k] = av[i + k];
		result[j][len] = NULL;
		i += len + 1;
		j++;
	}
	result[cmd_count] = NULL;
	return (result);
}

int	main(int ac, char *av[])
{
	int		cmd_count;
	int		ret;
	char	***cmds;

	if (ac < 2)
		return (printf("Error: usage\n"), 1);
	cmd_count = count_cmds(ac, av);
	cmds = cmds_init(ac, av, cmd_count);
	if (cmds == NULL)
		return (printf("Error: calloc\n"), 1);
	ret = picoshell(cmds);
	cleanup(cmds, cmd_count);
	return (ret);
}
