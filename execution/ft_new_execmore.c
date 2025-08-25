#include "../src/minishell.h"

int	**ft_freepip(int **arr, int len, int index)
{
	int	i;
	int	**aux;

	i = 0;
	aux = arr;
	while (i < len && i < index - 1)
	{
		free(arr[i]);
		i++;
	}
	free(aux);
	return (NULL);
}

static int	**ft_pipalloc(int len)
{
	int	i;
	int	**ptr;

	i = 0;
	ptr = (int **)malloc(sizeof(int *) * len);
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = (int *)malloc(sizeof(int) * 2);
		if (!ptr[i])
			return (ft_freepip(ptr, len, i + 1));
		i++;
	}
	return (ptr);
}

void	ft_child_3(t_input *input, t_vars *vars)
{
	char	*path;

	ft_set_redir_2(input, vars);
	vars->exit_status = 0;
	if (!ft_builtin_n(input, vars))
	{
		if (!ft_builtin_2(input, vars))
		{
			vars->envp = ft_getenv(vars->env);
			path = ft_findpath(input->comm[0], vars->envp, vars);
			if (!vars->envp || !path)
				ft_exit(path, vars->exit_status, vars);
			if (execve(path, input->comm, vars->envp) == -1)
				ft_exit(path, 1, vars);
		}
	}
}

void	ft_new_execmore2(t_input *input, int **pip, int fd, t_vars *vars) // Allways assuming that string is correct.
{
	ft_command_array(input, vars);
	ft_signal(WAIT);
	input->pid = fork();
	if (input->pid == -1)
		perror("fork");//ft_exit?
	else if (input->pid == 0)
	{
		if (fd == 1 || fd == 2)
		{
			dup2(pip[0][1], 1);//protect
			close(pip[0][0]);//protect
		}
		if (fd == 2)
		{
			dup2(pip[-1][0], 0);//protect
			close(pip[-1][1]);
		}
		if (fd == 0)
		{
			dup2(pip[0][0], 0);//protect
			close(pip[0][1]);//protect
		}
		ft_child_3(input, vars);
		ft_exit(NULL, vars->exit_status, vars);
	}
}

void	ft_new_execmore(t_input **input, t_vars *vars)
{
	int	i;

	i = 1;
	vars->pip = ft_pipalloc(vars->np);
	if (!vars->np)
		ft_exit(NULL, 2, vars);
	if (pipe(vars->pip[0]) == -1)
	{
		perror("pipe");
		ft_exit(NULL, 2, vars);
	}
	ft_new_execmore2(input[0], &vars->pip[0], 1, vars);
	close(vars->pip[0][1]);
	while (i < vars->np)
	{
		if (pipe(vars->pip[i]) == -1)
		{
			perror("pipe");
			ft_exit(NULL, 2, vars);
		}
		ft_new_execmore2(input[i], &vars->pip[i], 2, vars);
		close(vars->pip[i][1]);
		close(vars->pip[i - 1][0]);
		i++;
	}
	ft_new_execmore2(input[vars->np], &vars->pip[vars->np - 1], 0, vars);
	close(vars->pip[vars->np - 1][0]);
	ft_waitall(input, vars->np + 1, vars);
}