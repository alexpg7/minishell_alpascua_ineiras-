/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:04:46 by alpascua          #+#    #+#             */
/*   Updated: 2025/07/30 20:04:50 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_sigint(int sig)
{
	sig = 0;
	if (g_shell_state == PROMPT)
	{
		ft_putchar_fd('\n', 0);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (g_shell_state == WAIT)
	{
		ft_printf("\n");
	}
}

void	ft_init_sig(void)
{
	signal(SIGINT, &ft_sigint);
}
