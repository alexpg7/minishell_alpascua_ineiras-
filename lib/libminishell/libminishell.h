/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libminishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:08:39 by alpascua          #+#    #+#             */
/*   Updated: 2025/07/01 08:23:12 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../src/minishell.h"

// Trash List Structure:
typedef struct trash_lst
{
	void                *content;
    void                **content_p;
    struct trash_lst    *next;
}	t_lst;

// Trash List Functions:
t_lst	*ft_lstnew_lst(void *content, void **content_p);
void	ft_lstadd_back_lst(t_lst **lst, t_lst *new);
void	ft_lstdelone_lst(t_lst *lst);
void	ft_lstclear_lst(t_lst **lst);
void	ft_free_lst(void **ptr);

// Others:
char	**ft_splitmini(char const *s, char c, t_vars *vars);
void	ft_jumpcom(char const *s, int *i, char sep);
int		ft_special(char c);
void	ft_nextword(const char *s, int *i, char sep);
