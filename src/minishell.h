#include "../lib/Libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_vars
{
	char    *prompt;
}	t_vars;

// COMMANDS

void    ft_exit(char *input, int ret, t_vars *vars);

char    *ft_pwd(char **envp);