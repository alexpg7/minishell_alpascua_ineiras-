#include "../src/minishell.h"

void	ft_child(t_command *command, t_vars *vars)
{
	char	*path;

	vars->exit_status = 0;
	if (!ft_builtin2(command, vars))
	{
		//ft_set_redir(command, vars, 2);//if == -1 return
		vars->envp = ft_getenv(vars->env);
		path = ft_findpath(command->comm[0], vars->envp, vars);// save exit status (in case the command is not found/executable)
		if (!vars->envp || !path)
			ft_exit(path, vars->exit_status, vars);//put the exit status here, wait will collect it
		if (execve(path, command->comm, vars->envp) == -1)
			ft_exit(path, 1, vars);//put the exit status here, wait will collect it
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
		if (pid == -1)
			perror("fork");
		else if (pid == 0)
		{
			signal(SIGINT, &ft_sigkill);
			ft_child(command, vars);
			ft_exit(NULL, vars->exit_status, vars);
		}
		else
		{
			waitpid(pid, &vars->exit_status, 0);//save exit status somewhere
			vars->exit_status = exitstatus2(vars->exit_status);
			ft_printexit(vars->exit_status, 0, vars);// remember to make sigint produce exit 1
		}
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
