/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:54:04 by alpascua          #+#    #+#             */
/*   Updated: 2025/02/03 11:12:43 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	*ft_free_gnl(char **str, char **buff)
{
	if (*str)
		free(*str);
	*str = NULL;
	if (buff != NULL)
		free(*buff);
	return (NULL);
}

static void	*ft_reloc(char **str)
{
	char	*aux;
	size_t	start;

	start = ft_strchr(*str, '\n') - *str;
	aux = *str;
	*str = ft_substr(aux, start + 1, ft_strlen(aux) - start + 1);
	if (!(*str))
		return (ft_free_gnl(&aux, NULL));
	ft_free_gnl(&aux, NULL);
	return (*str);
}

static void	ft_bzero2(void *s, size_t n, int *r)
{
	size_t	i;
	char	*str;

	*r = 1;
	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

static void	*ft_read(char **str, int fd)
{
	char	*buff;
	char	*aux;
	int		r;

	buff = (char *)malloc(sizeof(char) *(BUFFER_SIZE + 1));
	if (!buff)
		return (ft_free_gnl(str, NULL));
	ft_bzero2(buff, BUFFER_SIZE + 1, &r);
	while (r > 0 && !ft_strchr(buff, '\n'))
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r > 0)
		{
			buff[r] = '\0';
			aux = *str;
			*str = ft_strjoin(aux, buff);
			if (!(*str))
				return (ft_free_gnl(&aux, &buff));
			free(aux);
		}
	}
	free(buff);
	if (r < 0)
		return (ft_free_gnl(str, NULL));
	return (*str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*ptr;
	size_t		len;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (ft_free_gnl(&str, NULL));
	if ((str && !ft_strchr(str, '\n')) || !str)
		if (!ft_read(&str, fd))
			return (ft_free_gnl(&str, NULL));
	if (str && !(*str))
		return (ft_free_gnl(&str, NULL));
	if (ft_strchr(str, '\n'))
		len = ft_strchr(str, '\n') - str + 1;
	else
		len = ft_strlen(str);
	ptr = ft_substr(str, 0, len);
	if (!ptr)
		return (ft_free_gnl(&str, NULL));
	if (!ft_reloc(&str))
		return (ft_free_gnl(&ptr, NULL));
	return (ptr);
}
