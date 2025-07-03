#include "minishell.h"

void	ft_promptinfo(t_vars *vars)
{
	ft_printf("\nn_pipes: %i\n\n", vars->np);
	//All these could be implemented inside the splitmini function
}

void	do_stuff(char *str, t_vars *vars)
{
	char	**comm;

	vars->np = 0;
	comm = ft_splitmini(str, ' ', vars);
	free(str);
	if (!comm)
		ft_exit(NULL, 1, vars);
	vars->ts = ft_lstnew_lst(NULL, (void **)comm);
	ft_promptinfo(vars);
	ft_printf("%s\n", ft_searchdollar(comm[0], vars));
	if (ft_strncmp(comm[0], "env", 3) == 0)
		ft_env(vars);
	if (ft_strncmp(comm[0], "export", 6) == 0)
		ft_export(vars, comm[1]);
	if (ft_strncmp(comm[0], "pwd", 3) == 0)
		ft_printf("%s\n", ft_pwd(vars));
	ft_exit(NULL, 0, vars);
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
