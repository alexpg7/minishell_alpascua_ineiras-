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

void	ft_sigint_heredoc(int sig)
{
	g_signal = sig;
	ioctl(0, TIOCSTI, "\n");
}

void	ft_sigquit_heredoc(int sig)
{
	g_signal = sig;
	rl_replace_line("", 0);
}
