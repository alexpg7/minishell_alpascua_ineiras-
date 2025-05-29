#include "minishell.h"

int main(void)
{
	char	*input;

	ft_printf("Welcome to minishell\n");
	while (1)
	{
		input = readline("minishell -> "); //put here directory like in bash
		if (!input)
		{
			perror("malloc");
			return (1);
		}
		add_history(input);
		if (ft_strncmp(input, "exit", 4) == 0)
			ft_exit();
	}
	return (0);
}