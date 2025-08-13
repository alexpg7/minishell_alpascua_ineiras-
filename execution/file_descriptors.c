/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:24:25 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/13 11:32:06 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

/*
int	ft_checkfd(char *file, int fd, int final)
{
	if (fd == -1)
	{
		perror(file);
		return (-1);
	}
	if (dup2(fd, final) == -1)
	{
		perror("dup2");
		return (-1);
	}
	if (close(fd) == -1)
	{
		perror("close");
		return (-1);
	}
	return (0);
}
*/

void	ft_read_app(t_input *input, t_vars *vars, int pos)
{
	input->last_fd = open(input->word[pos], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (input->last_fd == -1)
		ft_exit(NULL, 1, vars);
	dup2(input->last_fd, STDOUT_FILENO);
	close(input->last_fd);
}

void	ft_read_out(t_input *input, t_vars *vars, int pos)
{
	input->last_fd = open(input->word[pos], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (input->last_fd == -1)
		ft_exit(NULL, 1, vars);
	dup2(input->last_fd, STDOUT_FILENO);
	close(input->last_fd);
}

void	ft_read_in(t_input *input, t_vars *vars, int pos)
{
	input->last_fd = open(input->word[pos], O_WRONLY);
	if (input->last_fd == -1)
		ft_exit(NULL, 1, vars);
	dup2(input->last_fd, STDIN_FILENO);
	close(input->last_fd);
}