#include "../../src/minishell.h"

static int	ft_varlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (ft_isalnum2(str[i]))
		i++;
	return (i);
}

static int	ft_isvar(char *str, t_vars *vars, int mode)
{
	t_list	*env;
	int		len;

	env = vars->env;
	//mode 1 means start with '$', mode 0 not
	if (*str == '$' && ft_isalnum2(*(str + 1)))
	{
		while (env)
		{
			len = ft_varlen(env->content);
			if (ft_strncmp(env->content, str + mode, len) == 0)
				return (len + 1);
			env = env->next;
		}
	}
	return (0);
}

static int	ft_countvars(char *str, t_vars *vars)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_isvar(&str[i], vars, 1))
			count++;
		i++;
	}
	return (count);
}

static int	ft_valuelen(char *str, t_vars *vars)
{
	t_list	*env;
	int		len;

	env = vars->env;
	while (env)
	{
		len = ft_varlen(env->content);
		if (ft_strncmp(env->content, str, len) == 0)
		{
			vars->dollar.value = env->content + 1 + len;
			return (ft_strlen(env->content + 1 + len));
		}
		env = env->next;
	}
	return (0);
}

static int	ft_calclen(char *str, t_vars *vars)
{
	int	i;

	i = 0;
	while (!ft_isvar(&str[i], vars, 1))
		i++;
	vars->dollar.vallen = ft_valuelen(&str[i + 1], vars);
	vars->dollar.varlen = ft_isvar(&str[i], vars, 1);
	return (vars->dollar.vallen - vars->dollar.varlen);
}

static void	ft_copyvar(char *dest, t_vars *vars)
{
	int		len;
	int		i;
	char	*val;

	len = vars->dollar.vallen;
	i = 0;
	val = vars->dollar.value;
	while (i < len)
	{
		dest[i] = val[i];
		i++;
	}
}

static char	*ft_subs1(char *str, t_vars *vars)
{
	int		len;
	int		i;
	int		valuelen;
	char	*ptr;

	len = ft_strlen(str) + ft_calclen(str, vars);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		ft_exit(NULL, 1, vars);
	ft_lstadd_back_lst(&vars->ts, ft_lstnew_lst(ptr, NULL));//protect
	i = 0;
	valuelen = -1;
	while (*str)
	{
		if (ft_isvar(str, vars, 1) && valuelen == -1)
		{
			valuelen = vars->dollar.vallen;
			ft_copyvar(&ptr[i], vars);
			i = i + valuelen;
			str = str + vars->dollar.varlen;
		}
		else
		{
			ptr[i] = *str;
			str++;
			i++;
		}
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_searchdollar(char *str, t_vars *vars)
{
	int		count;
	char	*new;

	new = str;
	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		return (str);
	//else, quote error?
	count = ft_countvars(str, vars);
	while (count > 0)
	{
		new = ft_subs1(new, vars);
		if (!new)
			ft_exit(NULL, 1, vars);
		count--;
	}
	//IMPLEMENT A SPECIAL CHARACTER READER
	//THEN, ERASE ALL \", \' CHARACTERS
	return (new);
}
