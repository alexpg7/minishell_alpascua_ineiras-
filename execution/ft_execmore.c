#include "../src/minishell.h"

static void	ft_waitall(int *pid, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (pid[i] > 0)
			waitpid(pid[i], NULL, 0);
		i++;
	}
}

static int	**ft_freepip(int **arr, int len, int index)
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

int	ft_execbetween(void)
{
	return (0);
}

int	ft_execmore2(t_command *command, int *pid, int **pip, t_vars *vars)
{
	int	i;

	if (pipe(pip[0]) == -1)
	{
		perror("pipe");
		return (-1);
	}
	ft_execfirst(command, pid, pip, vars);
	i = 1;
	while (i < vars->np)
	{
		if (pipe(pip[i]) == -1)
		{
			perror("pipe");
			return (-1);
		}
		ft_execbetween();
		i++;
	}
	ft_execlast(&command[i], pid, pip, vars);
	ft_waitall(pid, vars->np + 1);
	free(pid);
	ft_freepip(pip, vars->np, vars->np + 1);
	return (0);
}

void	ft_execmore(t_command *command, t_vars *vars)
{
	int	**pip;
	int	*pid;

	pid = (int *)malloc(sizeof(int) * (vars->np + 1));
	if (!pid)
	{
		perror("pid malloc");
		ft_exit(NULL, 1, vars);
	}
	pip = ft_pipalloc(vars->np);
	if (!pip)
	{
		free(pid);
		perror("pipes malloc");
		ft_exit(NULL, 1, vars);
	}
	if (ft_execmore2(command, pid, pip, vars) == -1)
	{
		free(pid);
		ft_freepip(pip, vars->np, vars->np + 1);
		ft_exit(NULL, 1, vars);
	}
}
