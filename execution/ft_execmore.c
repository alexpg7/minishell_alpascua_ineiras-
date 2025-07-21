#include "../src/minishell.h"

void	ft_execmore(t_command *command, t_vars *vars)
{
	ft_printf("\"pipex here\" %s\npipes: %i\n", command->comm[0], vars->np);
}
