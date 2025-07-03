#include "../lib/Libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdbool.h>

// Trash List Structure:
typedef struct trash_lst
{
	void                *content;
    void                **content_p;
    struct trash_lst    *next;
}	t_lst;
typedef struct s_vars
{
	char	*prompt;
	//t_lst	*trash;
	t_list	*env;
	t_list	*export;
	t_lst	*ts;
	int		np; //number of pipes
}	t_vars;

// Trash List Functions:
t_lst	*ft_lstnew_lst(void *content, void **content_p);
void	ft_lstadd_back_lst(t_lst **lst, t_lst *new);
void	ft_lstdelone_lst(t_lst *lst);
void	ft_lstclear_lst(t_lst **lst);
void	ft_free_lst(void **ptr);

// splitmini:
char	**ft_splitmini(char const *s, char c, t_vars *vars);
void	ft_jumpcom(char const *s, int *i, char sep);
int		ft_special(char c);
void	ft_nextword(const char *s, int *i, char sep);

// searchdollar
char	*ft_searchdollar(char *str, t_vars *vars);

// COMMANDS

void	ft_exit(char *input, int ret, t_vars *vars);
char	*ft_pwd(t_vars *vars);
void	ft_env(t_vars *vars);
void	ft_export(t_vars *vars, char *arg);

// PROGRAMS

void	ft_init(t_vars *vars, char **envp);
