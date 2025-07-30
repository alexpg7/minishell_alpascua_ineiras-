#include "minishell.h"

void	ft_sigint(int sig)
{
	sig = 0;
	ft_putchar_fd('\n', 0);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}


void	ft_sigkill(int sig)
{
	ft_printf("KILL\n");
	kill(0, sig);
}



void	ft_init_sig(void)
{
	signal(SIGINT, &ft_sigint);//Ctrl+C
}
