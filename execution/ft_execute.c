#include "../src/minishell.h"

int	ft_checkfd(char *file, int fd, int final)
{
	if (fd == -1)
	{
		perror(file);
		return (-1);
	}
	if (dup2(fd, final) == -1)
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

int	ft_readin2(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	return (ft_checkfd(file, fd, 0));
}

int	ft_readin3(char *file)
{
	int	fd;

	fd = open(".here_doc.tmp", O_RDONLY);//REMEMBER TO DELETE IT AT THE END
	return (ft_checkfd(file, fd, 0));
}

int	ft_readin(char *file, int mode)
{
	if (mode == 1)
		return (ft_readin3(file));
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
	return (ft_checkfd(file, fd, 1));
	return (0);
}

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

void	ft_exec1(t_command *command, t_vars *vars)
{
	int		pid;
	char	**envp;
	char	*path;

<<<<<<< HEAD
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
			if (!ft_builtin2(command, vars))
			{
				ft_set_redir(command, vars, 2);//for here_doc, file must be created before execution
				//(if mode == 1 condition)
				envp = ft_getenv(vars->env); //protect
				path = ft_strjoin("/usr/bin/", command->comm[0]);//protect and SEARCH FOR TRUE PATH
				if (!envp || !path)
					ft_exit(NULL, 1, vars);
				if (execve(path, command->comm, envp) == -1) //save exit status
					ft_exit(NULL, 1, vars); //SHOULD FREE ENVP AND PATH
			}
			ft_exit(NULL, 0, vars);
		}
		else
			waitpid(pid, NULL, 0);//save exit status somewhere
=======
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
>>>>>>> origin/cd_branch
	}
	if (command->hd == 1)
		unlink(".here_doc.tmp");
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
