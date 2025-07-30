#include "../src/minishell.h"

static int	ft_checkfdpipe(int pipe, int final)
{
	if (dup2(pipe, final) == -1)
	{
		perror("dup2");
		close(pipe);
		return (-1);
	}
	close(pipe);
	return (0);
}

void	ft_childbetween(t_command *command, int *pip0, int *pip1, t_vars *vars)
{
	char	*path;

	ft_checkfdpipe(pip1[1], 1);//if == -1 return
	close(pip0[1]);
	ft_checkfdpipe(pip0[0], 0);//if == -1 return
	close(pip1[0]);
	if (!ft_builtin2(command, vars))
	{
		//ft_set_redirfirst(command, vars, 2);
		/*ft_checkfdpipe(pip[1], 1);//if == -1 return
		close(pip[0]);*/
		vars->envp = ft_getenv(vars->env);
		path = ft_findpath(command->comm[0], vars->envp, vars);// save exit status (in case the command is not found/executable)
		if (!vars->envp || !path)
			ft_exit(path, vars->exit_status, vars);//put the exit status here, wait will collect it
		if (execve(path, command->comm, vars->envp) == -1)
			ft_exit(path, 1, vars);//put the exit status here, wait will collect it
	}
	//free pip and pid
}

int	ft_execbetween(t_command *command, int *pid, int **pip, t_vars *vars)
{
	if (command->hd == 1)
	{
		if (ft_heredoc(command->infile) == -1)
			ft_exit(NULL, 1, vars);
	}
	if (!ft_searchbuiltin(command))//some builtins are not executed if they are in a pipe
	{
		pid[0] = fork();// save pipes in trashlist?
		if (pid[0] == -1)
			perror("fork");
		else if (pid[0] == 0)
		{
			ft_childbetween(command, pip[0], pip[1], vars);
			ft_exit(NULL, 0, vars);
		}
		close(pip[0][0]);
		close(pip[1][1]);
	}
	else
		pid[0] = -1;
	return (0);
}
