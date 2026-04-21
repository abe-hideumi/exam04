#include "picoshell.h"

int	main(void)
{
	char	*cmd1[] = {"ls", "-l", NULL};
	char	*cmd2[] = {"grep", "main", NULL};
	char	**cmds[] = {cmd1, cmd2, NULL};

	return (picoshell(cmds));
}
