/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:56:17 by alpascua          #+#    #+#             */
/*   Updated: 2025/08/04 18:34:52 by ineiras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../lib/Libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/ioctl.h>

// struct commands
typedef struct s_command
{
	char	**comm;
	char	*infile;
	char	*outfile; //can also be HERE_DOC if hd = 1
	int		hd; //here_doc
	int		ap; //append mode
}	t_command;

typedef struct s_input
{
	char	**word; // word[i] = "echo"		word[i] = ">>"
	char	*token;	// token[i] = 'c'		token[i] = 'a'
	int		pid;
	int		last_fd;
}	t_input;

// Trash List Structure:
typedef struct s_trash_lst
{
	void				*content;
	void				**content_p;
	struct s_trash_lst	*next;
}	t_lst;

typedef struct s_dollar
{
	int		varlen;
	int		vallen;
	char	*value;
}	t_dollar;

typedef struct s_vars
{
	char		*prompt;
	t_list		*env;
	t_lst		*ts;
	t_dollar	dollar;
	t_input		*input;
	t_command	*command;
	int			np; //number of pipes
	int			**pip; //pipes
	int			*pid;
	int			exit_status;
	char		**envp;
}	t_vars;

typedef enum e_shell_state
{
	PROMPT,
	EXEC,
	HEREDOC,
	WAIT
}	t_shell_state;

extern int	g_signal;

// TRSH LIST FUNCTIONS
t_lst		*ft_lstnew_lst(void *content, void **content_p);
void		ft_lstadd_back_lst(t_lst **lst, t_lst *new);
void		ft_lstdelone_lst(t_lst *lst);
void		ft_lstclear_lst(t_lst **lst);
void		ft_freecommand(t_command *command);
void		ft_free_lst(void **ptr);
void		ft_free_both(char *str1, char *str2);
//void	ft_free_three(char *str1, char *str2, char *str3);

// SIGNALS
void		ft_signal(int code);
void		ft_sigint_heredoc(int sig);
void		ft_sigquit_heredoc(int sig);

// SPLITMINI ///////////////////////////////////////////////
char		**ft_splitmini(char const *s, char c, t_vars *vars);
void		ft_jumpcom(char const **s, char sep);
int			ft_special(char c);
void		ft_nextword(const char **s, char sep);

// SPLITMINI2
char		**ft_splitmini2(char *str, t_vars *vars);

// STRUCT INPUT
t_input		**ft_inputstruct(char **comm, t_vars *vars);

// SEARCH DOLLAR /////////////////////////////////////////
char		*ft_searchdollar(char *str, t_vars *vars);
char		*ft_removequotes(char *str);
int			ft_varlen(char *str);
int			ft_isvar(char *str, t_vars *vars, int mode);
int			ft_countvars(char *str, t_vars *vars);
int			ft_valuelen(char *str, t_vars *vars);

// COMMANDS
void		ft_exit(char *input, int ret, t_vars *vars);
char		*ft_pwd(char **comm, t_vars *vars);
char		*ft_new_pwd(void);
char		*ft_path(t_vars *vars);
void		ft_env(t_vars *vars);
void		ft_export(t_vars *vars, char **arg, int mode);
void		ft_echo(char **args);
void		ft_cd(t_vars *vars, char **argv);
char		**ft_getenv(t_list *env);
void		ft_unset(char **args, t_vars *vars);
int			ft_strisalnum2(char *str);
char		*new_var(t_vars *vars, char *arg);

// UTILS & COMMANDS OF CD
void		swap_pwd(t_vars *vars);
void		change_old_pwd(t_vars *vars, char *old_pwd);
void		change_pwd(t_vars *vars, char *pwd);
int			count_args(char **argv);
char		*minus_dir(char *dir, t_vars *vars);
void		ft_putendl_fd2(char *s, int fd, char *var);
int			ft_free_minus_one(char *str);
void		cd_double_point(t_vars *vars);

// PROGRAMS
void		ft_init(t_vars *vars, char **envp);

// EXECUTION
void		ft_execute(t_command *command, t_vars *vars);
int			ft_heredoc(char *lim);
char		*ft_findpath(char *comm, char **envp, t_vars *vars);
int			exitstatus2(int status);
void		ft_execmore(t_command *command, t_vars *vars);
void		ft_waitall(int *pid, int len, t_vars *vars);

// EXIT STATUS
int			exitstatus2(int status);
void		ft_printexit(int ex, int index, t_vars *vars);

// EXEC FIRST
int			ft_execfirst(t_command *comm, int *pid, int **pip, t_vars *vars);

// EXEC BETWEEN
int			ft_execbetween(t_command *comm, int *pid, int **pip, t_vars *vars);

// EXEC LAST
int			ft_execlast(t_command *comm, int *pid, int **pip, t_vars *vars);

// EXECCUTION UTILS
int			ft_checkfd(char *file, int fd, int final);
int			ft_readin2(char *file);
int			ft_readin3(void);
int			ft_readin(char *file, int mode);
int			ft_readout(char *file, int mode);
void		ft_set_redir(t_command *command, t_vars *vars, int mode);
int			ft_builtin2(t_command *com, t_vars *vars);
int			ft_builtin1(t_command *com, t_vars *vars);
int			ft_searchbuiltin(t_command *com);
int			**ft_freepip(int **arr, int len, int index);

// CREATE COMMAND (struct command) /////////////////////////////////////////////
t_command	*ft_createcomm(char **comm, t_vars *vars);
int			ft_commandlen(char **comm);

#endif
