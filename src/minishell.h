#include "../lib/Libft/libft.h"
#include "../lib/libminishell/libminishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdbool.h>

typedef struct s_vars
{
	char	*prompt;
	//t_lst	*trash;
	t_list	*env;
}	t_vars;

// COMMANDS

void	ft_exit(char *input, int ret, t_vars *vars);

char	*ft_pwd(char **envp);

void	ft_env(t_vars *vars);

// PROGRAMS

void	ft_init(t_vars *vars, char **envp);
