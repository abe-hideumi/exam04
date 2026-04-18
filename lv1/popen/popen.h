#ifndef POPEN_H
# define POPEN_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# define BUF_SIZE 1000

int	ft_popen(const char *file, char *const argv[], char type);

#endif
