/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:05:12 by alpascua          #+#    #+#             */
/*   Updated: 2025/01/05 16:26:50 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*firstdir;

	if (!lst || !f || !del)
		return (0);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (0);
	firstdir = new;
	lst = lst->next;
	while (lst)
	{
		new->next = ft_lstnew(f(lst->content));
		if (!new)
		{
			ft_lstclear(&firstdir, del);
			return (0);
		}
		new = new->next;
		lst = lst->next;
	}
	new->next = NULL;
	return (firstdir);
}
