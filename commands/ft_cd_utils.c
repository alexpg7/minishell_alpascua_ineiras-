#include "../src/minishell.h"

int count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return i;
}