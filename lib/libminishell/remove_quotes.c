#include "../../src/minishell.h"

char	*ft_remove1(char *str)
{
	char	*ptr;
	int		i;

	ptr = (char *)malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (!ptr)
	{
		free(str);
		return (NULL);
	}
	i = 1;
	while (str[i] && str[i] != '\'')
	{
		ptr[i - 1] = str[i];
		i++;
	}
	ptr[i - 1] = '\0';
	free(str);
	return (ptr);
}

char	*ft_remove2(char *str)
{
	char	*ptr;
	int		i;

	ptr = (char *)malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (!ptr)
	{
		free(str);
		return (NULL);
	}
	i = 1;
	while (str[i] && str[i] != '\"')
	{
		ptr[i - 1] = str[i];
		i++;
	}
	free(str);
	ptr[i - 1] = '\0';
	return (ptr);
}

char	*ft_removequotes(char *str)
{
	if (str[0] != '\"' && str[0] != '\'')
		return (str);
	if (str[0] == '\'')
		return (ft_remove1(str));
	return (ft_remove2(str));
}
