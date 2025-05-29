#include "../src/minishell.h"

void    ft_exit(void)
{
    rl_clear_history();
    ft_printf("Exiting minishell\n");
    exit(0);
}