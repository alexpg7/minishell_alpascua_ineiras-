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

int	ft_readin(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		perror(str);
		return (-1);
	}
	if (dup2(fd, 0) == -1)
	{
		perror("dup2");
		return (-1);
	}
	if (close(fd) == -1)
	{
		perror("close");
		return (-1);
	}
	return (0);
}

void	ft_exec1(char **comm, t_vars *vars)
{
	int		pid;
	int		read;
	char	**envp;
	char	*path;

	read = 0;
	if (ft_strcmp(comm[0], "<") == 0 || ft_strcmp(comm[0], "<<") == 0)
		read = 1;
	if (!ft_builtin(comm + 2 * read, vars))
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (pid == 0)
		{
			if (read == 1)
			{
				if (ft_readin(comm[1]) == -1)
					ft_exit(NULL, 1, vars);
				comm = comm + 2;
			}
			envp = ft_getenv(vars->env);
			path = ft_strjoin3("/usr/bin", "/", comm[0]);//protect AND SEARCH TRUE PATH
			if (!envp || !path)
				ft_exit(NULL, 1, vars);
			if (execve(path, comm, envp) == -1)//save exit status
				ft_exit(ft_free(envp, 1), 1, vars);
		}
		else
			waitpid(pid, NULL, 0);//save exit status
	}
}

void	ft_execmore(char **comm, t_vars *vars)
{
	ft_printf("\"pipex here\" %s\npipes: %i\n", comm[0], vars->np);
}

void	ft_command(char **comm, t_vars *vars)
{
	if (vars->np == 0)
		ft_exec1(comm, vars);
	else
		ft_execmore(comm, vars);
	//BEFORE, WE SHOULD "CUT" THE ARRAY UNTIL '|' OR '>'
}

void	ft_execute(char **comm, t_vars *vars)
{
	ft_command(comm, vars);
}
