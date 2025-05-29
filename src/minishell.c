#include "minishell.h"

void	do_stuff(char *str, t_vars *vars)
{
	if (ft_strncmp(str, "exit", 4) == 0)
		ft_exit(str, 0, vars);
	free(str);
	free(vars->prompt);
}

int	main(int narg, char **argv, char **envp)
{
	char	*input;
	t_vars	vars;

	ft_printf("Welcome to minishell\n");
	while (narg == 1 && argv[0])
	{
		vars.prompt = ft_strjoin(ft_pwd(envp), "-> ");
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