#include "../src/minishell.h"

void	ft_child(t_command *command, t_vars *vars)
{
	char	**envp;
	char	*path;

	if (!ft_builtin2(command, vars))
	{
		ft_set_redir(command, vars, 2);
		envp = ft_getenv(vars->env);
		path = ft_findpath(command->comm[0], envp, vars);// save exit status (in case the command is not found/executable)
		if (!envp || !path)
		{
			ft_freestrarr(&envp, 1);
			ft_exit(path, 1, vars);
		}
		if (execve(path, command->comm, envp) == -1)
		{
			ft_freestrarr(&envp, 1);
			ft_exit(path, 1, vars);
		}
	}
}

void	ft_exec1(t_command *command, t_vars *vars)
{
	int		pid;

	if (command->hd == 1)
	{
		if (ft_heredoc(command->infile) == -1)
			ft_exit(NULL, 1, vars);
	}
	if (!ft_builtin1(command, vars))
	{
		pid = fork();
		if (pid == 1)
			perror("fork");
		else if (pid == 0)
		{
			ft_child(command, vars);
			ft_exit(NULL, 0, vars);
		}
		else
			waitpid(pid, NULL, 0);//save exit status somewhere
	}
	if (command->hd == 1)
		unlink(".here_doc.tmp");
}

void	ft_execute(t_command *command, t_vars *vars)
{
	if (vars->np == 0)
		ft_exec1(command, vars);
	else
		ft_execmore(command, vars);
}
