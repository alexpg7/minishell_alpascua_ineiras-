#include "../lib/Libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/wait.h>

// Trash List Structure:
typedef struct s_trash_lst
{
	void                *content;
    void                **content_p;
    struct s_trash_lst    *next;
}	t_lst;

typedef struct s_dollar
{
	int		varlen;
	int		vallen;
	char	*value;
}	t_dollar;
typedef struct s_vars
{
	char	*prompt;
	//t_lst	*trash;
	t_list	*env;
	t_list	*export;
	t_lst	*ts;
	t_dollar	dollar;
	int		np; //number of pipes
}	t_vars;

// TRSH LIST FUNCTIONS
t_lst	*ft_lstnew_lst(void *content, void **content_p);
void	ft_lstadd_back_lst(t_lst **lst, t_lst *new);
void	ft_lstdelone_lst(t_lst *lst);
void	ft_lstclear_lst(t_lst **lst);
void	ft_free_lst(void **ptr);

// SPLITMINI
char	**ft_splitmini(char const *s, char c, t_vars *vars);
void	ft_jumpcom(char const **s, char sep);
int		ft_special(char c);
void	ft_nextword(const char **s, char sep);

// SEARCH DOLLAR
char	*ft_searchdollar(char *str, t_vars *vars);
char	*ft_removequotes(char *str);

// COMMANDS

void	ft_exit(char *input, int ret, t_vars *vars);
char	*ft_pwd(t_vars *vars);
char	*ft_path(t_vars *vars);
void	ft_env(t_vars *vars);
void	ft_export(t_vars *vars, char *arg);
void	ft_echo(char **args);
void	ft_cd(t_vars *vars, char **argv);
char	**ft_getenv(t_list *env);

// UTILS & COMMANDS OF CD 
void	swap_pwd(t_vars *vars);
void 	change_old_pwd(t_vars *vars, char *old_pwd);
void	change_pwd(t_vars *vars, char *pwd);
int		count_args(char **argv);
char	*minus_dir(char *dir);

// PROGRAMS
void	ft_init(t_vars *vars, char **envp);

// EXECUTION
void	ft_execute(char **comm, t_vars *vars);
