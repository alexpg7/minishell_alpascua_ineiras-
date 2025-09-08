/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:04:46 by alpascua          #+#    #+#             */
/*   Updated: 2025/09/07 10:15:35 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint_prompt(int sig)
{
	g_signal = sig;
	ft_putchar_fd('\n', 0);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_sigint_wait(int sig)
{
	g_signal = sig;
	ft_printf("\n");
}

void	ft_sigquit_wait(int sig)
{
	g_signal = sig;
}

void	ft_signal(int code)
{
	if (code == PROMPT)
	{
		signal(SIGINT, &ft_sigint_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (code == WAIT)
	{
		signal(SIGINT, &ft_sigint_wait);
		signal(SIGQUIT, &ft_sigquit_wait);
	}
	else if (code == HEREDOC)
	{
		signal(SIGINT, &ft_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
