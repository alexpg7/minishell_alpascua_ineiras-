#include "../src/minishell.h"

static char	*ft_path2(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
	{
		i++;
	}
	if (envp[i])
		return (envp[i] + 5);
	ft_putstr_fd("No PATH variable found.", 2);
	return (NULL);
}

static char	*ft_checkpath(char **paths, char *comm, int *ret)
{
	int		i;
	char	*program;

	i = 0;
	while (paths[i])
	{
		program = ft_strjoin3(paths[i], "/", comm);
		if (!program)
		{
			*ret = -1;
			return (NULL);
		}
		if (access(program, F_OK) == 0)
		{
			if (access(program, X_OK) == 0)
				return (program);
			perror(program);
			//exit status 126
		}
		free(program);
		i++;
	}
	//exit status 127
	perror(comm);
	return (NULL);
}

char	*ft_findpath(char *comm, char **envp, t_vars *vars)
{
	char	**path;
	char	*ptr;
	int		ret;

	if (access(comm, X_OK) == 0)
		return (comm);
	ret = 0;
	path = ft_split(ft_path2(envp), ':');
	if (!path)//maybe there is a leak if PATH is deleted
		ft_exit(NULL, 1, vars);
	ptr = ft_checkpath(path, comm, &ret);
	ft_freestrarr(&path, 1);
	if (ret == -1)
		ft_exit(NULL, 1, vars);
	return (ptr);
}
