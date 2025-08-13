/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:24:33 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/13 10:23:51 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int	ft_input_count(char **str_array)
{
	int i;

	i = 0;
	while (str_array[i])
		i++;
	return (i);
}

int	ft_tokken_counter(t_input *input, char tokken)
{
	int	i = 0;
	int	count = 0;

	while (input->word[i])
	{
		if (input->token[i] == tokken)
			count++; // Assuming input is always OK.
		i++;
	}
	return (count);
}

int	ft_search_tokken_2(t_input *input, char tokken, int *pos)
{
	while (input->word[*pos])
	{
		if (input->token[*pos] == tokken)
			return (*pos); // Assuming input is always OK.
		(*pos)++;
	}
	return (-1);
}

int	ft_search_tokken(t_input *input, char tokken)
{
	int	i = 0;
	
	while (input->word[i])
	{
		if (input->token[i] == tokken)
			return (i); // Assuming input is always OK.
		i++;
	}
	return (-1);
}