#include "../src/minishell.h"

void	ft_command(char **comm, t_vars *vars)
{
	int	pid;
	char	**envp;
	char	*path;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0) // CHILD
	{
		envp = ft_getenv(vars->env);
		path = ft_strjoin3("/usr/bin", "/", comm[0]);//protect AND SEARCH TRUE PATH
		if (!envp || !path)
			ft_exit(NULL, 1, vars);
		if (execve(path, comm, envp) == -1)
			ft_exit(ft_free(envp, 1), 1, vars);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

void	ft_execute(char **comm, t_vars *vars)
{
	ft_command(comm, vars);
}
