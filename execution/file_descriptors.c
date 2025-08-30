/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:24:25 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/25 17:13:08 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	ft_write_out(t_input *input, t_vars *vars, int pos)
{
	int	mask;

	if (access(input->word[pos], W_OK) != 0)
	{
		ft_putstr_fd("cannot write \"", 2);
		ft_putstr_fd(input->word[pos], 2);
		ft_putstr_fd("\": permission denied\n", 2);
	}
	mask = O_CREAT | O_TRUNC | O_WRONLY;
	input->last_out = open(input->word[pos], mask, 0644);
	if (input->last_out == -1)
		ft_exit(NULL, 1, vars);
	if (input->last_out <= 0)
		return ;
	if (dup2(input->last_out, STDOUT_FILENO) == -1)
	{
		close(input->last_out);
		ft_exit(NULL, 1, vars);
	}
	if (close(input->last_out) == -1)
		ft_exit(NULL, 1, vars);
}

void	ft_read_app(t_input *input, t_vars *vars, int pos)
{
	int	mask;

	if (access(input->word[pos], W_OK) != 0)
	{
		ft_putstr_fd("cannot write \"", 2);
		ft_putstr_fd(input->word[pos], 2);
		ft_putstr_fd("\": permission denied\n", 2);
	}
	mask = O_CREAT | O_WRONLY | O_APPEND;
	input->last_out = open(input->word[pos], mask, 0644);
	if (input->last_out == -1)
		ft_exit(NULL, 1, vars);
	if (input->last_out <= 0)
		return ;
	if (dup2(input->last_out, STDOUT_FILENO) == -1)
	{
		close(input->last_out);
		ft_exit(NULL, 1, vars);
	}
	if (close(input->last_out) == -1)
		ft_exit(NULL, 1, vars);
}

void	ft_read_in(t_input *input, t_vars *vars, int pos)
{
	if (access(input->word[pos], W_OK) != 0)
	{
		ft_putstr_fd("cannot read \"", 2);
		ft_putstr_fd(input->word[pos], 2);
		ft_putstr_fd("\": permission denied\n", 2);
	}
	input->last_in = open(input->word[pos], O_RDONLY);
	if (input->last_in == -1)
		ft_exit(NULL, 1, vars);
	if (input->last_in <= 0)
		return ;
	if (dup2(input->last_in, STDOUT_FILENO) == -1)
	{
		close(input->last_in);
		ft_exit(NULL, 1, vars);
	}
	if (close(input->last_in) == -1)
		ft_exit(NULL, 1, vars);
}
