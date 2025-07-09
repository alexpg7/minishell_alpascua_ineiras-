#include "../../src/minishell.h"

static int	ft_varlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\"')
			return (i);
		i++;
	}
	return (i);
}

static int	ft_reslen(char *str, int len, t_vars *vars)
{
	t_list	*env;
	int		c1;
	int		c2;

	env = vars->env;
	while (env)
	{
		c1 = (ft_strncmp(env->content, str, len - 1) == 0);
		c2 = (*((char *)env->content + len) == '=');
		if (c1 && c2)
			return (ft_strlen(ft_strchr(env->content, '=') + 1));
		env = env->next;
	}
	return (0);
}

static int	ft_newlen(char *str, t_vars *vars)
{
	char	*first;
	int		varlen;
	int		reslen;

	first = str;
	while (!ft_isalnum(*(ft_strchr(first, '$') + 1)))
		first = ft_strchr(first, '$') + 1;
	varlen = ft_varlen(ft_strchr(first, '$'));
	reslen = ft_reslen(first + 1, varlen, vars);
	return (reslen - varlen);
}

static char	*ft_searchvar(char *varname, int len, t_vars *vars)
{
	t_list	*env;

	env = vars->env;
	while (env)
	{
		if (ft_strncmp(env->content, varname, len) == 0 && *((char *)env->content + len) == '=')
			return (env->content + len + 1);
		env = env->next;
	}
	return (NULL);
}

void	ft_copyvar(char *dest, char *src, int *i, t_vars *vars)
{
	char	*newvar;

	newvar = ft_searchvar(src + 1, ft_varlen(src + 1), vars);
	if (newvar)
	{
		while (*newvar)
		{
			dest[*i] = *newvar;
			*i = *i + 1;
			newvar++;
		}
		dest[*i] = '\0';
	}
}

static char	*ft_subs1(char *str, t_vars *vars)
{
	int		newlen;
	int		i;
	int		flag;
	char	*ptr;

	newlen = ft_strlen(str) + ft_newlen(str, vars);
	ptr = (char *)malloc(sizeof(char) * (newlen + 2));
	if (!ptr)
		ft_exit(NULL, 1, vars);
	//add to trashlist
	i = 0;
	flag = 0;
	while (*str)
	{
		if (*str == '$' && ft_isalnum2(*(str + 1)) && flag == 0)
		{
			ft_copyvar(ptr, str, &i, vars);
			str = ft_varlen(str) + str;
			flag = 1;
		}
		else
		{
			ptr[i] = *str;
			str++;
			i++;
		}
	}
	return (ptr);
}

char	*ft_searchdollar(char *str, t_vars *vars)
{
	int		i;
	int		count;
	char	*new;

	i = 0;
	count = 0;
	new = str;
	if (str[0] == '\'' && str[ft_strlen(str)] == '\'')
		return (str);
	//else, quote error?
	while (str[i])
	{
		if (str[i] == '$' && ft_isalnum2(str[i + 1]))
			count++;
		i++;
	}
	while (count > 0)
	{
		new = ft_subs1(new, vars);
		if (!new)
			return (NULL);
		ft_lstadd_back_lst(&vars->ts, ft_lstnew_lst(new, NULL));//protect
		count--;
	}
	return (new);
}
