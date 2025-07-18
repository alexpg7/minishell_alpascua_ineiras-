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
	else if (ft_strcmp("exit", comm[0]) == 0)
		ft_exit(NULL, 0, vars);
	else
		return (0);
	return (1);
}

int	ft_heredoc(char *lim)
{
	ft_printf("here_doc %s\n", lim);
	return (0);
}

int	ft_readin2(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
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

int	ft_readin(char *file, int mode)
{
	if (mode == 1)
		return (ft_heredoc(file));
	else
		return (ft_readin2(file));
	return (0);
}


int	ft_readout(char *file, int mode)
{
	int	fd;

	if (mode == 1)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(file);
		return (-1);
	}
	if (dup2(fd, 1) == -1)
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

void	ft_set_redir(t_command *command, t_vars *vars)
{
	if (command->infile)
	{
		if (ft_readin(command->infile, command->hd) == -1)
			ft_exit(NULL, 1, vars);
	}
	if (command->outfile)
	{
		if (ft_readout(command->outfile, command->ap) == -1)
			ft_exit(NULL, 1, vars);
	}
}

void	ft_exec1(t_command *command, t_vars *vars)
{
	int		pid;
	char	**envp;
	char	*path;

	if (!ft_builtin(command->comm, vars))
	{
		pid = fork();
		if (pid == 1)
			perror("fork");
		else if (pid == 0)
		{
			ft_set_redir(command, vars);
			envp = ft_getenv(vars->env); //protect
			path = ft_strjoin("/usr/bin/", command->comm[0]);//protect and SEARCH FOR TRUE PATH
			if (!envp || !path)
				ft_exit(NULL, 1, vars);
			if (execve(path, command->comm, envp) == -1) //save exit status
				ft_exit(NULL, 1, vars); //SHOULD FREE ENVP AND PATH
		}
		else
			waitpid(pid, NULL, 0);//save exit status somewhere
	}
}

void	ft_execmore(t_command *command, t_vars *vars)
{
	ft_printf("\"pipex here\" %s\npipes: %i\n", command->comm[0], vars->np);
}

void	ft_execute(t_command *command, t_vars *vars)
{
	if (vars->np == 0)
		ft_exec1(command, vars);
	else
		ft_execmore(command, vars);
}
