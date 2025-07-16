#include "../src/minishell.h"


int	ft_builtin(char **comm, t_vars *vars)
{
	char *pwd;

	if (ft_strcmp("echo", comm[0]) == 0)
		ft_echo(comm + 1);
	else if (ft_strcmp("cd", comm[0]) == 0)
		ft_cd(vars, comm);
	else if (ft_strcmp("pwd", comm[0]) == 0)
	{
		pwd = ft_pwd(comm + 1, vars);
		if (pwd)
			ft_printf("%s\n", pwd);
	}
	else if (ft_strcmp("export", comm[0]) == 0)
		ft_export(vars, comm[1]); //change to accept different arguments (+ not an identifier: if not valid var)
	else if (ft_strcmp("unset", comm[0]) == 0)
		ft_printf("\"executing unset...\"\n");
	else if (ft_strcmp("env", comm[0]) == 0)
		ft_env(vars);
	else
		return (0);
	return (1);
}

void	ft_command(char **comm, t_vars *vars)
{
	int	pid;
	char	**envp;
	char	*path;

	//fork only if np > 0 (and builtin)
	//BEFORE, WE SHOULD "CUT" THE ARRAY UNTIL '|' OR '>'
	if (ft_strcmp(comm[0], "cd") == 0)
		ft_cd(vars, comm);
	else
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0) // CHILD
		{
			if (!ft_builtin(comm, vars))
			{
				envp = ft_getenv(vars->env);
				path = ft_strjoin3("/usr/bin", "/", comm[0]);//protect AND SEARCH TRUE PATH
				if (!envp || !path)
					ft_exit(NULL, 1, vars);
				if (execve(path, comm, envp) == -1)
					ft_exit(ft_free(envp, 1), 1, vars);
			}
			else
				ft_exit(NULL, 0, vars);
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
	}
}

void	ft_execute(char **comm, t_vars *vars)
{
	ft_command(comm, vars);
}
