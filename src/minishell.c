#include "minishell.h"

void	ft_promptinfo(t_vars *vars)
{
	/*int	i;
	int	npipe;

	i = 0;
	npipe = 0;
	if (ft_strlen(comm[0]) == 1 && ft_strncmp(comm[0], "<", 1) == 0)
		vars->first = 'i';
	else if (ft_strlen(comm[0]) == 2 && ft_strncmp(comm[0], "<<", 2) == 0)
		vars->first = 'h';
	else
		vars->first = 'c';
	while (comm[i])
	{
		if (ft_strlen(comm[i]) == 1 && ft_strncmp(comm[i], "|", 1) == 0)
			npipe++;
		i++;
	}
	vars->np = npipe;
	i = (i - 2) * (i >= 2);
	if (ft_strlen(comm[i]) == 1 && ft_strncmp(comm[i], ">", 1) == 0)
		vars->last = 'o';
	else if (ft_strlen(comm[i]) == 2 && ft_strncmp(comm[i], ">>", 2) == 0)
		vars->last = 'a';
	else
		vars->last = 'c';*/
	ft_printf("\nmode: %c%c\nn_pipes: %i\n\n", vars->first, vars->last, vars->np);
	//All these could be implemented inside the splitmini function
}

void	do_stuff(char *str, t_vars *vars)
{
	char	**comm;

	vars->np = 0;
	comm = ft_splitmini(str, ' ', vars);
	free(str);
	free(vars->prompt);
	if (!comm)
		ft_exit(NULL, 1, vars);
	ft_promptinfo(vars);
	/*if (ft_strncmp(comm[0], "env", 3) == 0)
		ft_env(vars);
	if (ft_strncmp(comm[0], "export", 6) == 0)
		ft_export(vars, comm[1]);
	if (ft_strncmp(comm[0], "pwd", 3) == 0)
		ft_printf("%s\n", ft_pwd(vars));*/
}

void	ft_sigint(int sig)
{
	sig = 0;
	ft_printf("^C\n");
	ft_exit(NULL, 1, NULL);
}

void	ft_init_sig(void)
{
	signal(SIGINT, &ft_sigint);
}

int	main(int narg, char **argv, char **envp)
{
	char	*input;
	t_vars	vars;

	ft_init_sig();
	ft_printf("Welcome to minishell\n");
	ft_init(&vars, envp);
	//vars.trash = create first
	while (narg == 1 && argv[0])
	{
		vars.prompt = ft_strjoin(ft_pwd(&vars), "-> ");
		if (!vars.prompt)
		{
			perror("malloc");
			ft_exit(NULL, 1, &vars);
		}
		input = readline(vars.prompt); //put here directory like in bash
		if (!input)
		{
			perror("malloc");
			ft_exit(input, 1, &vars);
		}
		add_history(input);
		do_stuff(input, &vars);
	}
	return (0);
}
