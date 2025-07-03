#include "../../src/minishell.h"

void	ft_free_lst(void **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

t_lst	*ft_lstnew_lst(void *content, void **content_p)
{
	t_lst	*arr;

	arr = (t_lst *)malloc(sizeof(t_lst) * 1);
	if (!arr)
		return (NULL);
	arr->content = content;
    arr->content_p = content_p;
	arr->next = NULL;
	return (arr);
}

void	ft_lstadd_back_lst(t_lst **lst, t_lst *new)
{
	t_lst	*aux;

	aux = *lst;
	if (lst && *lst)
	{
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
		while (new->next != NULL)
			new = new->next;
		new->next = NULL;
	}
	else if (lst)
		*lst = new;
	new->next = NULL;
}

void	ft_lstdelone_lst(t_lst *lst)
{
	if (!lst)
		return ;
	if (lst->content)
		free(lst->content);
	if (lst->content_p)
		ft_free_lst(lst->content_p);
	free(lst);
}

void	ft_lstclear_lst(t_lst **lst)
{
	t_lst	*aux;

	if (!lst)
		return ;
	while (*lst)
	{
		aux = (*lst)->next;
		ft_lstdelone_lst(*lst);
		*lst = aux;
	}
}

/*
int main(void)
{
    t_lst *test;
    t_lst *test_1;
    t_lst *test_2;
    t_lst *test_3;
    t_lst *temp_node;
    int i = 0;

    char **lol;

    lol = ft_split("Hola poma pometa.", ' ');


    test = ft_lstnew_lst("Hola", NULL);
    test_1 = ft_lstnew_lst("Sec", NULL);
    test_2 = ft_lstnew_lst("Third", NULL);
    test_3 = ft_lstnew_lst(NULL, (void**)lol);
    ft_lstadd_back_lst(&test, test_1);
    ft_lstadd_back_lst(&test, test_2);
    ft_lstadd_back_lst(&test, test_3);
    temp_node = test;
    printf("Conten_p: %s\n", (char *)(temp_node->next->next->next->content_p)[0]);
    while (temp_node)
    {
        printf("Node: Content: %s\n", (char *)temp_node->content);
        temp_node = temp_node->next;
    }
    ft_free_lst((void**)lol);
    ft_lstclear_lst(&test);
    printf("%s", (char*)test);
    return 0;
}*/
