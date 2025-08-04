#include "../src/minishell.h"

int	exitstatus2(int status)
{
	status = (status >> 8) & 0xFF;
	return (status);
}

void	ft_printexit(int ex, int index, t_vars *vars)
{
	if (ex != 0)
		ft_putstr_fd("minishell: ", 2);
	if (ex == 1)
	{
		ft_putstr_fd(vars->command[index].comm[0] , 2);
		ft_putstr_fd(": command failed.\n", 2);
	}
	if (ex == 126)
	{
		ft_putstr_fd(vars->command[index].comm[0] , 2);
		ft_putstr_fd(": could not access.\n", 2);
	}
	if (ex == 127)
	{
		ft_putstr_fd(vars->command[index].comm[0] , 2);
		ft_putstr_fd(": command not found.\n", 2);
	}
	// 130 for killed process (Ctrl+C)
	// one for ctrl+D while process
}
