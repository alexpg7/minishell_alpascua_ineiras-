#include "../src/minishell.h"

char    *ft_pwd(char **envp)
{
    int i;

    i = 0;
    while (envp[i] && ft_strncmp(envp[i], "PWD=", 4) != 0)
    {
        i++;
    }
    return (envp[i] + 4);
}