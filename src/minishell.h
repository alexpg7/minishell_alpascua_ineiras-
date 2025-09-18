/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineiras- <ineiras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:56:17 by alpascua          #+#    #+#             */
/*   Updated: 2025/09/18 20:02:24 by ineiras-         ###   ########.fr       */
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
	char	**comm;
	int		pid;
	int		last_in;
	int		last_out;
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
	t_input		**input;
	t_command	*command;
	int			np; //number of pipes
	int			**pip; //pipes
	//int			*pid;
	int			exit_status;
	char		**envp;
	char		*here;
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
void		ft_freeinput(t_input ***input, int np, t_vars *vars);
void		ft_free_lst(void **ptr);
void		ft_free_both(char *str1, char *str2);
// SIGNALS
void		ft_signal(int code);
void		ft_sigint_heredoc(int sig);

// SPLITMINI2
char		**ft_splitmini2(char *str, t_vars *vars);
int			ft_nextword2(char *str, int *i);
int			ft_isop(char c);
int			ft_isquote(char c);
int			ft_checkop(char *str, int *i);

// STRUCT INPUT
t_input		**ft_inputstruct(char **comm, t_vars *vars);
int			ft_isredir(char *str);
int			ft_nextcommand(char **comm, int i);
int			ft_checkpipes(char **comm);
int			ft_checkredirs(char **comm);
int			ft_comsize(char **comm);

// CLEAN STRING
char		*ft_cleanstring(char *comm, char token, t_vars *vars);
char		*ft_cleanheredoc(char *comm, char token, t_vars *vars);
void		ft_nextvar(char *comm, int *i);
int			ft_strcmpvar(char *var, char *name, int len);
int			ft_isvar_clean(char *comm, int len, t_vars *vars);
int			ft_varlen_clean(char *comm, t_vars *vars);
int			ft_lenvars_clean(char *comm, t_vars *vars);
int			ft_isspecial2(char *c);
int			ft_countspecial(char *comm);
int			ft_countquotes(char *comm);
char		*ft_searchvar(char *comm, int len, t_vars *vars);
void		ft_copyvar(char **dest, char *src, int *i, t_vars *vars);

// COMMANDS
void		ft_exit(char *ptr, char **args, int ret, t_vars *vars);
void		ft_exitbuiltin(char *ptr, char **args, int ret, t_vars *vars);
char		*ft_pwd(char **comm, t_vars *vars);
char		*ft_new_pwd(void);
void		ft_env(t_vars *vars);
void		ft_export(t_vars *vars, char **arg, int mode);
int			ft_varlen2(char *str);
void		ft_env_export(t_vars *vars);
void		ft_printerror(t_vars *vars, char *arg);
void		ft_echo(char **args);
void		ft_cd(t_vars *vars, char **argv);
char		**ft_getenv(t_list *env);
void		ft_unset(char **args, t_vars *vars);
int			ft_strisalnum2(char *str);
void	ft_printexport(char *str);

// New CD COMMANDS
void		ft_cd(t_vars *vars, char **argv);
void		ft_cd_not_args(t_vars *vars);
void		ft_cd_two_arg(t_vars *vars, char **argv);
int			ft_cd_move_dir(t_vars *vars, char **argv, char *path);
void		ft_swap_pwd(t_vars *vars);
void		ft_cd_double_point(t_vars *vars);

// New CD UTILS
char		*ft_getenv_var(t_vars *vars, char *var_name);
int			ft_setenv_var(t_vars *vars, char *pwd, char *var_name);
void		ft_path_fail(t_vars *vars, char *pwd, char *error_m);
void		ft_create_var(t_vars *vars, char *pwd, char *var_name);
int			count_args(char **argv);
char		*minus_dir(char *dir, t_vars *vars);
void		ft_putendl_fd2(char *s, int fd, char *var);
int			ft_free_minus_one(char *str);
void		ft_cd_point(t_vars *vars);
void		ft_set_both(t_vars *vars, char *pwd);

// PROGRAMS
void		ft_init(t_vars *vars, char **envp);
void		ft_init3(t_vars *vars);

// EXIT STATUS
int			exitstatus2(int status);
void		ft_printexit(int ex, int index, t_vars *vars);

// NEW EXECUTION
void		ft_execute2(t_input **input, t_vars *vars);
void		ft_new_exec(t_input *input, t_vars *vars);
int			ft_heredoc(char *lim, char *path, t_vars *vars);
char		*ft_sufix(char *path, int tag);
char		*ft_findpath(char *comm, char **envp, t_vars *vars);
int			exitstatus2(int status);
void		ft_waitall(t_input **input, int len, t_vars *vars);
void		ft_new_execmore(t_input **input, t_vars *vars);
void		ft_makeheredoc(t_input *input, int tag, t_vars *vars);
int			**ft_freepip(int **arr, int len, int index);
int			**ft_pipalloc(int len);

// NEW EXECUTION UTILS
void		ft_command_array(t_input *input, t_vars *vars);
int			ft_builtin_n(t_input *input, t_vars *vars);
void		ft_child_2(t_input *input, char *here, t_vars *vars);
int			ft_builtin_2(t_input *input, t_vars *vars);
void		ft_set_redir_2(t_input *input, char *path, t_vars *vars);
int			**ft_freepip(int **arr, int len, int index);

// NEW EXECUTION UTILS 2
int			ft_input_count(char **str_array);
int			ft_tokken_counter(t_input *input, char tokken);
int			ft_search_tokken(t_input *input, char tokken);
int			ft_search_tokken_2(t_input *input, char tokken, int *pos);

// NEW EXECUTION 3 (FILE DESCRIPTION)
void		ft_read_in(t_input *input, t_vars *vars, int pos);
void		ft_write_out(t_input *input, t_vars *vars, int pos);
void		ft_read_app(t_input *input, t_vars *vars, int pos);

#endif
