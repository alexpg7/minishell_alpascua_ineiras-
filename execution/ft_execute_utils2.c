#include "../src/minishell.h"

void	ft_set_redir(t_command *command, t_vars *vars, int mode)
{
	if (command->infile && (mode == 0 || mode == 2))
	{
		if (ft_readin(command->infile, command->hd) == -1)
			ft_exit(NULL, 1, vars);
	}
	if (command->outfile && (mode == 1 || mode == 2))
	{
		if (ft_readout(command->outfile, command->ap) == -1)
			ft_exit(NULL, 1, vars);
	}
}

int	ft_builtin2(t_command *com, t_vars *vars)
{
	char *pwd;

	ft_set_redir(com, vars, 2);
	if (ft_strcmp("echo", com->comm[0]) == 0)
		ft_echo(com->comm + 1);
	else if (ft_strcmp("pwd", com->comm[0]) == 0)
	{
		pwd = ft_pwd(com->comm + 1, vars);
		if (pwd)
			ft_printf("%s\n", pwd);
	}
	else if (ft_strcmp("env", com->comm[0]) == 0)
		ft_env(vars);
	else
		return (0);
	return (1);
}

int	ft_builtin1(t_command *com, t_vars *vars)
{
	if (ft_strcmp("cd", com->comm[0]) == 0)
		ft_cd(vars, com->comm);
	else if (ft_strcmp("export", com->comm[0]) == 0)
		ft_export(vars, com->comm[1]); //change to accept different arguments (+ not an identifier: if not valid var)
	else if (ft_strcmp("unset", com->comm[0]) == 0)
		ft_printf("\"executing unset...\"\n");
	else if (ft_strcmp("exit", com->comm[0]) == 0)
		ft_exit(NULL, 0, vars);
	else
		return (0);
	return (1);
}
