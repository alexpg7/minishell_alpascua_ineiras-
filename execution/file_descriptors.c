/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:24:25 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/25 16:44:58 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	ft_write_out(t_input *input, t_vars *vars, int pos)
{
	input->last_out = open(input->word[pos], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (input->last_out == -1)
		ft_exit(NULL, 1, vars);
	if (input->last_out <= 0)
		return ;
	dup2(input->last_out, STDOUT_FILENO);
	close(input->last_out);
}

void	ft_read_app(t_input *input, t_vars *vars, int pos)
{
	input->last_out = open(input->word[pos], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (input->last_out == -1)
		ft_exit(NULL, 1, vars);
	if (input->last_out <= 0)
		return ;
	dup2(input->last_out, STDOUT_FILENO);
	close(input->last_out);
}

void	ft_read_in(t_input *input, t_vars *vars, int pos)
{
	input->last_in = open(input->word[pos], O_RDONLY);
	if (input->last_in == -1)
		ft_exit(NULL, 1, vars);
	if (input->last_in <= 0)
		return ;
	dup2(input->last_in, STDIN_FILENO);
	close(input->last_in);
}