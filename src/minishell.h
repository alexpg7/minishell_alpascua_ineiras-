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
	t_list	*export;
	char	first; //it can have 3 values: h "here doc (<<)", i "input (<)", c "command"
	int		np; //number of pipes
	char	last; //it can have 3 modes: a "append (>>)", o "output (>)", c "command"
}	t_vars;

// COMMANDS

void	ft_exit(char *input, int ret, t_vars *vars);

char	*ft_pwd(t_vars *vars);

void	ft_env(t_vars *vars);

void	ft_export(t_vars *vars, char *arg);

// PROGRAMS

void	ft_init(t_vars *vars, char **envp);
