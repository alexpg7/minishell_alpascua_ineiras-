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

/*static void	ft_set_redirlast(t_command *command, t_vars *vars, int mode)
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
}*/

void	ft_childlast(t_command *command, int *pip, t_vars *vars)
{
	char	**envp;
	char	*path;

	ft_checkfdpipe(pip[0], 0);//if == -1 return
	close(pip[1]);
	if (!ft_builtin2(command, vars))
	{
		//ft_set_redirlast(command, vars, 2);
		/*ft_checkfdpipe(pip[0], 0);//if == -1 return
		close(pip[1]);*/
		envp = ft_getenv(vars->env);
		path = ft_findpath(command->comm[0], envp, vars);// save exit status (in case the command is not found/executable)
		if (!envp || !path)
		{
			ft_freestrarr(&envp, 1);
			ft_exit(path, 1, vars);//put the exit status here, wait will collect it
		}
		if (execve(path, command->comm, envp) == -1)
		{
			ft_freestrarr(&envp, 1);
			ft_exit(path, 1, vars);//put the exit status here, wait will collect it
		}
	}
}

int	ft_execlast(t_command *command, int *pid, int **pip, t_vars *vars)
{
	if (command->hd == 1)
	{
		if (ft_heredoc(command->infile) == -1)
			ft_exit(NULL, 1, vars);
	}
	if (!ft_searchbuiltin(command))//some builtins are not executed if they are in a pipe
	{
		pid[0] = fork();
		if (pid[0] == -1)
			perror("fork");
		else if (pid[0] == 0)
		{
			ft_childlast(command, pip[0], vars);
			ft_exit(NULL, 0, vars);
		}
		close(pip[0][0]);
	}
	else
		pid[0] = -1;
	return (0);
}
