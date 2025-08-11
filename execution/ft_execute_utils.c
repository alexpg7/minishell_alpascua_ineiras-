/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:24:25 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/11 16:40:37 by ineiras-         ###   ########.fr       */
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

int	ft_readin2(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	return (ft_checkfd(file, fd, 0));
}

int	ft_readin3(void)
{
	int	fd;

	fd = open(".here_doc.tmp", O_RDONLY);
	return (ft_checkfd(".here_doc.tmp", fd, 0));
}

int	ft_readin(char *file, int mode)
{
	if (mode == 1)
		return (ft_readin3());
	else
		return (ft_readin2(file));
	return (0);
}

int	ft_readout(char *file, int mode)
{
	int	fd;

	if (mode == 1)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	return (ft_checkfd(file, fd, 1));
	return (0);
}
*/
// ---------------------------------------------------------------------------------

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

int	ft_readin2(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	return (ft_checkfd(file, fd, 0));
}

int	ft_readin3(void)
{
	int	fd;

	fd = open(".here_doc.tmp", O_RDONLY);
	return (ft_checkfd(".here_doc.tmp", fd, 0));
}

int	ft_readin(char *file, int mode)
{
	if (mode >= 0)
		return (ft_readin3());
	else
		return (ft_readin2(file));
	return (0);
}

int	ft_readout(char *file, int mode)
{
	int	fd;

	if (mode >= 0)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	return (ft_checkfd(file, fd, 1));
	//return (0); // Why this?
}