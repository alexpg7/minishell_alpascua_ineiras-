/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:04:46 by alpascua          #+#    #+#             */
/*   Updated: 2025/09/07 10:57:33 by ineiras-         ###   ########.fr       */
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