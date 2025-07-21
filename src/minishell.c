#include "minishell.h"

void	ft_printcom(t_command *command)
{
	int	i;
	int	j;

	i = 0;
	while (command[i].comm)
	{
		ft_printf("-PIPE %i:\n", i + 1);
		j = 0;
		while (command[i].comm[j])
		{
			ft_printf("%s\n", command[i].comm[j]);
			j++;
		}
		ft_printf("-RED IN: %s, mode: %i\n", command[i].infile, command[i].hd);
		ft_printf("-RED OUT: %s, mode: %i\n\n", command[i].outfile, command[i].ap);
		i++;
	}
}

void	ft_freecommand(t_command *command)
{
	int	i;

	i = 0;
	while (command[i].comm)
	{
		free(command[i].comm);
		i++;
	}
	free(command);
}

void	do_stuff(char *str, t_vars *vars, int num)
{
	char		**comm;

	vars->np = 0;
	vars->command = NULL;
	comm = ft_splitmini(str, ' ', vars);
	free(str);
	if (!comm)
		ft_exit(NULL, 1, vars);
	if (num == 0)
		vars->ts = ft_lstnew_lst(NULL, (void **)comm);//protect
	else if (num != 0)
		ft_lstadd_back_lst(&vars->ts, ft_lstnew_lst(NULL, (void **)comm));//protect
	if (vars->command)
		ft_freecommand(vars->command);
	vars->command = ft_createcomm(comm, vars);
	ft_execute(vars->command, vars);
	ft_freecommand(vars->command);
	vars->command = NULL;
	//ft_printcom(command);
	//ft_exit(NULL, 0, vars);
}

/*void	ft_sigint(int sig)
{
	sig = 0;
	ft_printf("^C\n");
	ft_exit(NULL, 1, NULL);
}

void	ft_init_sig(void)
{
	signal(SIGINT, &ft_sigint);
}*/

int	main(int narg, char **argv, char **envp)
{
	char	*input;
	char	*nul;
	int		num;
	t_vars	vars;

	//ft_init_sig();
	num = 0;
	nul = NULL;
	ft_printf("Welcome to minishell\n");
	ft_init(&vars, envp);
	//INITIALIZE TRASHLIST (IMPORTANT TO AVOID SEGFAULT)
	while (narg == 1 && argv[0])
	{
		vars.prompt = ft_strjoin(ft_pwd(&nul, &vars), "-> ");
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
		do_stuff(input, &vars, num);
		free(vars.prompt);
		num++;
	}
	return (0);
}
