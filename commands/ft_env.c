#include "../src/minishell.h"

void	ft_env(t_vars *vars)
{
	t_list	*lst;

	lst = vars->env;
	while (lst)
	{
		ft_printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
}
