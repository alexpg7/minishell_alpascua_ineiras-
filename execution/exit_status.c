/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:27:44 by alpascua          #+#    #+#             */
/*   Updated: 2025/09/07 09:53:25 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

char	*ft_firstcom(t_input *input)
{
	int	i;

	i = 0;
	while (input->token[i])
	{
		if (input->token[i] == 'c')
			return (input->word[i]);
		i++;
	}
	return (NULL);
}

int	exitstatus2(int status)
{
	int	sig;

	sig = status & 0x7F;
	if (sig != 0)
		return (128 + sig);
	status = (status >> 8) & 0xFF;
	return (status);
}

static void	ft_printerr(char *name, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_printexit(int ex, int index, t_vars *vars)
{
	if (ex == 1 || ex == 2)
		ft_printerr(ft_firstcom(vars->input[index]), "command failed.");
	else if (ex == 126)
		ft_printerr(ft_firstcom(vars->input[index]), "could not access.");
	else if (ex == 127)
		ft_printerr(ft_firstcom(vars->input[index]), "command not found.");
	else if (ex == 130)
		ft_printerr(ft_firstcom(vars->input[index]), "process interrupted.");
	else if (ex == 131)
		ft_printerr(ft_firstcom(vars->input[index]), "process quitted.");
	else if (ex == 141)
		ft_printerr(ft_firstcom(vars->input[index]), "sigpipe recieved.");
	else if (ex != 0)
		ft_printerr(ft_firstcom(vars->input[index]), "signal recieved.");
}
