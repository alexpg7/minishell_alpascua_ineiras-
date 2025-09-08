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

void	ft_printexit(int ex, int index, t_vars *vars)
{
	if (ex != 0)
		ft_putstr_fd("minishell: ", 2);
	if (ex == 1 || ex == 2)
	{
		ft_putstr_fd(ft_firstcom(vars->input[index]), 2);
		ft_putstr_fd(": command failed.\n", 2);
	}
	if (ex == 126)
	{
		ft_putstr_fd(ft_firstcom(vars->input[index]), 2);
		ft_putstr_fd(": could not access.\n", 2);
	}
	if (ex == 127)
	{
		ft_putstr_fd(ft_firstcom(vars->input[index]), 2);
		ft_putstr_fd(": command not found.\n", 2);
	}
	if (ex == 130)
	{
		ft_putstr_fd(ft_firstcom(vars->input[index]), 2);
		ft_putstr_fd(": process interrupted.\n", 2);
	}
}
